require("dotenv").config({path: ".env.test"});
process.env.NODE_ENV = "test";

const chai = require("chai");
const expect = chai.expect;
const should = chai.should();
const chaiHttp = require("chai-http");
const app = require("../app");
const path = require("path");

const mock = require("xhr-mock").default;
const { postUsingXMLHttpRequest, patchUsingXMLHttpRequest, getMessageById, loadDoc } = require(path.join(__dirname, "../../../lab2/new.js"));

chai.use(chaiHttp);

let newId = "";
let insertInt = "";


describe("/First test collection", () => {

    it("Test get all messages", async () => {
    const res = await chai.request(app).get("/messages");
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
        const res = await chai.request(app).post("/messages").send(message);
        res.should.have.status(201);
        newId = res.body.insertedId;
        if (newId.charAt(newId.length-1) == "1")
            insertInt = "2";
        else
            insertInt = "1";
    });

    it("Test POST of a valid message", async () => {
        let message = {
            "message": "¡@£$€¥",
            "read": false
        }
        const res = await chai.request(app).post("/messages").send(message);
        res.should.have.status(400);
    });

    it("Test PATCH a read to true", async () => {
        let message = {
            "read": true
        }
        const res = await chai.request(app).patch(`/messages/${newId}`).send(message);
        res.should.have.status(200);
    });

    it("Test get specific message with read to be true", async () => {
        const res = await chai.request(app).get(`/messages/${newId}`);
        res.should.have.status(200);
        expect(res.body.read).to.be.true;
    });

    it("Test PATCH a read to false", async () => {
        let message = {
            "read": false
        }
        const res = await chai.request(app).patch(`/messages/${newId}`).send(message);
        res.should.have.status(200);
    });

    it("Test PATCH with unvalid id", async () => {
        let message = {
            "read": true
        }
        const res = await chai.request(app).patch(`/messages/${newId.slice(0, -1)}`).send(message);
        res.should.have.status(400);
    });

    it("Test get specific message with unvalid id", async () => {
        const res = await chai.request(app).get(`/messages/${newId.slice(0, -1) + insertInt}`);
        res.should.have.status(400);
    });

    it("Test PATCH with valid id but no id match", async () => {
        let message = {
            "read": true
        }
        const res = await chai.request(app).patch(`/messages/${newId.slice(0, -1) + insertInt}`).send(message);
        res.should.have.status(400);
    });

    it("Test get read = false", async () => {
        const res = await chai.request(app).get(`/messages/${newId}`);
        res.should.have.status(200);
        expect(res.body.read).to.be.false;
    });

    it("Test get error for unvalid id", async () => {
        const res = await chai.request(app).get(`/messages/${newId+insertInt}`);
        res.should.have.status(400);
    });

    it("Test get error for wrong method", async () => {
        const res = await chai.request(app).put(`/messages`);
        res.should.have.status(405);
    });
})

describe("Second test", () => {
  it("Test CORS", async () => {
    const res = await chai.request(app)
      .get("/messages")
      .set("Origin", "http://localhost:8080");

    expect(res.headers["access-control-allow-origin"])
        .to.equal("http://localhost:8080");
  });
})

describe("Frontend testing", () => {
    beforeEach(() => mock.setup());
    afterEach(() => mock.teardown());

  it("Tests POST by mock with correct payload", (done) => {
    mock.post("/messages", (req, res) => {
      expect(req.header("Content-Type")).to.equal("application/json");
      expect(JSON.parse(req.body())).to.include({ message: "test" });
      done();
      return res.status(201).body(JSON.stringify({ insertedId: "123" }));
    });
    postUsingXMLHttpRequest("test");
  });
  
  it("Tests POST by mock with incorrect payload", (done) => {
    mock.post("/messages", (req, res) => {
      try {
        expect(req.header("Content-Type")).to.equal("application/json");
        expect(JSON.parse(req.body())).to.include({ message: "!#¤%" });
        done();
        return res.status(405).body(JSON.stringify({ error: "HTTP 405 Could not create object"}));
      } catch (err) {
        done(err);
      }
    });
    postUsingXMLHttpRequest("!#¤%");
  });
  
  it("Tests PATCH by mock", (done) => {
      mock.patch(`/messages/${newId}`, (req, res) => {
          expect(req.header("Content-Type")).to.equal("application/json");
          expect(JSON.parse(req.body())).to.include({ read: true });
          done();
          return res.status(200).body(JSON.stringify({ insertedId: "123" }));;
        });
        patchUsingXMLHttpRequest(true, newId);
    });

    it("Tests GET by mock with specific id", (done) => {
      mock.get(`/messages/${newId}`, (req, res) => {
          done();
          return res.status(200).body(JSON.stringify({
            _id: newId,
            message: "Testmeddelande",
            author: "Testsson",
            date: "---",
            read: false
            }));
        });
        getMessageById(newId);
    });

    it("Tests GET by mock", (done) => {
      mock.get(`/messages`, (req, res) => {
          done();
          return res.status(200).body(JSON.stringify({
            _id: newId,
            message: "Testmeddelande",
            author: "Testsson",
            date: "---",
            read: false
            }));
        });
        loadDoc();
    });
});