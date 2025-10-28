process.env.NODE_TLS_REJECT_UNAUTHORIZED = '0';

require("dotenv").config({path: ".env.test"});
process.env.NODE_ENV = "test";

const chai = require("chai");
const expect = chai.expect;
const should = chai.should();
const chaiHttp = require("chai-http");
const app = require("../server");
const path = require("path");

//const mock = require("xhr-mock").default;
//const { postUsingXMLHttpRequest, patchUsingXMLHttpRequest, getMessageById, loadDoc } = require(path.join(__dirname, "../../../lab2/front.js"));

chai.use(chaiHttp);

let newId = "";
let insertInt = "";

describe("/First test collection", () => {

    it("Test create new user", async () => {
        let message = {
                    username: "testProfile",
                    password: "123",
                    messages: [],
                    friends: []
                }
        const res = await chai.request("https://localhost:8000").post(`/newUser`).send(message);
        res.should.have.status(201);
    });

    it("Test create second new user", async () => {
        let message = {
                    username: "testProfile2",
                    password: "123",
                    messages: [],
                    friends: []
                }
        const res = await chai.request("https://localhost:8000").post(`/newUser`).send(message);
        res.should.have.status(201);
    });

    it("Test send friend request", async () => {
        let message =
        {
            friend: "testProfile2",
            isFriend: false
        }
        const res = await chai.request("https://localhost:8000").post(`/friendRequest/testProfile/friends`).send(message);
        res.should.have.status(201);
    });

    it("Test get all messages", async () => {
    const res = await chai.request("https://localhost:8000").get("/users/testProfile");
    res.should.have.status(200);
    res.body.should.be.a("array");
    });

    it("Test POST of a valid product", async () => {
        let message = {
            "message": "Test message",
            "read": false,
            "author": "Testsson",
            "date": "today"
        }
        const res = await chai.request("https://localhost:8000").post("/postMessage/testProfile").send(message);
        res.should.have.status(201);
        newId = res._body;
        if (newId.charAt(newId.length-1) == "1")
            insertInt = "2";
        else
            insertInt = "1";
    });

    it("Test POST of a unvalid message", async () => {
        let message = {
            "message": "¡@£$€¥",
            "read": false
        }
        const res = await chai.request("https://localhost:8000").post("/postMessage/testProfile").send(message);
        res.should.have.status(400);
    });

    it("Test POST to a unvalid user", async () => {
        let message = {
            "message": "Test message",
            "read": false,
            "author": "Testsson",
            "date": "today"
        }
        const res = await chai.request("https://localhost:8000").post("/postMessage/testProfile3").send(message);
        res.should.have.status(404);
    });

    it("Test login", async () => {
        let message = {
            password: "123"
        }
        const res = await chai.request("https://localhost:8000").post("/login/testProfile").send(message);
        res.should.have.status(200);
    });

    it("Test login", async () => {
        let message = {
            password: "123"
        }
        const res = await chai.request("https://localhost:8000").post("/login/testProfil").send(message);
        res.should.have.status(400);
    });

    it("Test PATCH a read to true", async () => {
        let message = {
            read: true
        }
        const res = await chai.request("https://localhost:8000").patch(`/patchRead/testProfile/${newId}`).send(message);
        res.should.have.status(200);
    });

    it("Test PATCH a read to false", async () => {
        let message = {
            "read": false
        }
        const res = await chai.request("https://localhost:8000").patch(`/patchRead/testProfile/${newId}`).send(message);
        res.should.have.status(200);
    });

    it("Test PATCH with unvalid id", async () => {
        let message = {
            "read": true
        }
        const res = await chai.request("https://localhost:8000").patch(`/patchRead/testProfile/${newId.slice(0, -1)}`).send(message);
        res.should.have.status(400);
    });

    it("Test PATCH with unvalid username", async () => {
        let message = {
            "read": true
        }
        const res = await chai.request("https://localhost:8000").patch(`/patchRead/testProfil/${newId.slice(0, -1) + insertInt}`).send(message);
        res.should.have.status(400);
    });

    it("Test get error for unvalid username", async () => {
        const res = await chai.request("https://localhost:8000").get(`/users/testProfil`);
        res.should.have.status(400);
    });

    it("Test get error for wrong method", async () => {
        const res = await chai.request("https://localhost:8000").put(`/users`);
        res.should.have.status(405);
    });

    it("Test get friends", async () => {
        const res = await chai.request("https://localhost:8000").get(`/users/testProfile/friends`);
        res.should.have.status(200);
    });

    it("Test get friends error", async () => {
        const res = await chai.request("https://localhost:8000").get(`/users/testProfil/friends`);
        res.should.have.status(400);
    });

    it("Test check if friend", async () => {
        const res = await chai.request("https://localhost:8000").get(`/checkIfFriend/testProfile/testProfile2`);
        res.should.have.status(200);
    });

    it("Test check with wrong friend", async () => {
        const res = await chai.request("https://localhost:8000").get(`/checkIfFriend/testProfile/testFriends`);
        res.should.have.status(400);
    });

    it("Test send friend request from unvalid user", async () => {
        let message =
        {
            friend: "testProfile",
            isFriend: false
        }
        const res = await chai.request("https://localhost:8000").post(`/friendRequest/testProfile3/friends`).send(message);
        res.should.have.status(400);
    });

    it("Test search for friends", async () => {
        const res = await chai.request("https://localhost:8000").get(`/users`);
        res.should.have.status(200);
    });

    it("Test adding friend", async () => {
        const res = await chai.request("https://localhost:8000").patch(`/handleFriend/testProfile2/testProfile/${false}`);
        res.should.have.status(200);
    });

    it("Test removing friend", async () => {
        const res = await chai.request("https://localhost:8000").patch(`/handleFriend/testProfile2/testProfile/${true}`);
        res.should.have.status(200);
    });
})


//--------------------  Front end ---------------------

// describe("Second test", () => {
//   it("Test CORS", async () => {
//     const res = await chai.request(app)
//       .get("/messages")
//       .set("Origin", "http://localhost:8080");

//     expect(res.headers["access-control-allow-origin"])
//         .to.equal("http://localhost:8080");
//   });
// })

// describe("Frontend testing", () => {
//     beforeEach(() => mock.setup());
//     afterEach(() => mock.teardown());

//   it("Tests POST by mock with correct payload", (done) => {
//     mock.post("/messages", (req, res) => {
//       expect(req.header("Content-Type")).to.equal("application/json");
//       expect(JSON.parse(req.body())).to.include({ message: "test" });
//       done();
//       return res.status(201).body(JSON.stringify({ insertedId: "123" }));
//     });
//     postUsingXMLHttpRequest("test");
//   });
  
//   it("Tests POST by mock with incorrect payload", (done) => {
//     mock.post("/messages", (req, res) => {
//       try {
//         expect(req.header("Content-Type")).to.equal("application/json");
//         expect(JSON.parse(req.body())).to.include({ message: "!#¤%" });
//         done();
//         return res.status(405).body(JSON.stringify({ error: "HTTP 405 Could not create object"}));
//       } catch (err) {
//         done(err);
//       }
//     });
//     postUsingXMLHttpRequest("!#¤%");
//   });
  
//   it("Tests PATCH by mock", (done) => {
//       mock.patch(`/messages/${newId}`, (req, res) => {
//           expect(req.header("Content-Type")).to.equal("application/json");
//           expect(JSON.parse(req.body())).to.include({ read: true });
//           done();
//           return res.status(200).body(JSON.stringify({ insertedId: "123" }));;
//         });
//         patchUsingXMLHttpRequest(true, newId);
//     });

//     it("Tests GET by mock with specific id", (done) => {
//       mock.get(`/messages/${newId}`, (req, res) => {
//           done();
//           return res.status(200).body(JSON.stringify({
//             _id: newId,
//             message: "Testmeddelande",
//             author: "Testsson",
//             date: "---",
//             read: false
//             }));
//         });
//         getMessageById(newId);
//     });

//     it("Tests GET by mock", (done) => {
//       mock.get(`/messages`, (req, res) => {
//           done();
//           return res.status(200).body(JSON.stringify({
//             _id: newId,
//             message: "Testmeddelande",
//             author: "Testsson",
//             date: "---",
//             read: false
//             }));
//         });
//         loadDoc();
//     });
// });