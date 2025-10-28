const dotenv = require("dotenv");
const express = require("express");
const https = require("https");
const bcrypt = require("bcryptjs");
const fs = require("fs");
const { Server } = require("socket.io");

const cors = require("cors");

const options = {
  key: fs.readFileSync("./certs/key.pem"),
  cert: fs.readFileSync("./certs/cert.pem")
};

const corsOptions = {
  origin: 'https://localhost:3000',
	optionsSuccessStatus: 200,
  methods: ['GET', 'POST', 'PATCH', 'DELETE']
};

const { connectToDb, getDb } = require("./db")
const { ObjectId } = require("mongodb");

const regex = /[!@#$%^&*()\-\+={}\[\]:;"'<>,.?\/|\\]/;

const envFile = process.env.NODE_ENV === "test" ? ".env.test" : ".env.development";
dotenv.config({path: envFile});

const app = express();
app.use(cors(corsOptions));
app.use(express.json())

let db

connectToDb((err) => {
  if(!err) {
    const server = https.createServer(options, app);
    const io = new Server(server, {cors: corsOptions});

    io.on("connection", (socket) => {

      socket.on("joinRoom", (data) => {
        socket.join(data);
      });

      socket.on("sendMessage", (data) => {
        socket.to(data.room).emit("receivedMessage", data)
      });

      socket.on("disconnect", () => {
        });
    });

    server.listen(8000, () => {
    });

    db = getDb()
  }
})

//logga in
app.post("/login/:username", async (req, res) => {
  const message = req.body;
  if (!regex.test(req.params.username))
  {
    try
    {
      const dbs = db.collection("users")
      const doc = await dbs.findOne({ username: req.params.username });
      if (doc)
      {
        const match = await bcrypt.compare(message.password, doc.password);
        if(match)
        {
          return res.status(200).json({ username: req.params.username });
        }
      }
      else
      {
        return res.status(400).json({ error: "HTTP 400 No user found" });
      }
    }
    catch(err)
    {
      res.status(500).json({ error: "HTTP 500 Could not fetch" });
    }
  }
  else
  {
    return res.status(400).json({error: "Unvalid username"});
  }
});


//kollar om användaren redan finns vid registrering?
app.get("/users/:username", (req, res) => {
  db.collection("users")
    .findOne({"username": req.params.username})
    .then(doc => {
      if (doc != null)
        res.status(200).json(doc.messages)
      else
        res.status(400).json({newUser: "New user"})
    })
    .catch(() => {
      res.status(500).json({error: "No user found"})
    })
});

//hämtar vänner för inloggade användaren
app.get("/users/:username/friends", (req, res) => {
  db.collection("users")
    .findOne({"username": req.params.username})
    .then(doc => {
      if (doc != null)
      {
        res.status(200).json(doc.friends)
      }
      else
      {
        res.status(400).json({newUser: "New user"})
      }
    })
    .catch(() => {
      res.status(500).json({error: "No friends found"})
    })
});

app.get("/checkIfFriend/:username/:friend", (req, res) => {
  db.collection("users")
    .findOne({username: req.params.username, "friends.friend": req.params.friend})
    .then(doc => {
      if (doc != null)
      {
        res.status(200).json({isFriend: true})
      }
      else
      {
        res.status(400).json({isFriend: false})
      }
    })
    .catch(() => {
      res.status(500).json({error: "No friends found"})
    })
});

app.patch("/patchRead/:username/:id", (req, res) => {
  const message = req.body;
  if (ObjectId.isValid(req.params.id) && "read" in message && typeof message.read === "boolean") {
    db.collection("users")
       .updateOne(
        { username: req.params.username },
        { $set: { "messages.$[msg].read": req.body.read } },
        { arrayFilters: [ { "msg._id": new ObjectId(req.params.id) } ] }
        )
      .then(doc => {
        if (doc.matchedCount === 0)
          res.status(400).json({error: "HTTP 400 No ID match"})
        else {
          res.status(200).json(doc)
        }
      })
      .catch(err => {
        res.status(500).json({error: "HTTP 500 Could not fetch"})
      })
  }
  else {
    res.status(400).json({error: "HTTP 400 Not a valid id"})
  }
});

//för att lägga till vänner
app.post("/friendRequest/:username/friends", (req, res) => {
  const message = req.body
  
  db.collection("users")
    .updateOne(
    { username: req.params.username },
    { $push: {friends :  message} }  
    )
    .then(result => {
      if (result.matchedCount == 0)
        return res.status(400).json({error: "No match"})
      else
        return res.status(201).json(result)
    })
    .catch(err => {
      res.status(405).json({error: "HTTP 405 Could not create object"})
    })
});

app.post("/postMessage/:user", (req, res) => {
  const message = req.body
  const trimmedMessage = message.message.trim();
  if (!regex.test(trimmedMessage) && "message" in message && "read" in message && typeof message.read === "boolean" &&
  typeof message.message === "string" && Object.keys(message).length == 4 && trimmedMessage.length <= 140 &&
  trimmedMessage.length > 0)
  {
    message._id = new ObjectId();

    db.collection("users")
    .updateOne({username: req.params.user}, {$push: {messages: message}})
    .then(result => {
      if(result.matchedCount === 0) {
        return res.status(404).json({error: "User not found"})
      }
      else
      {
        res.status(201).json(message._id)
      }
    })
      .catch(err => {
        res.status(405).json({error: "HTTP 405 Could not create object"})
      })
    }
  else{
    res.status(400).json({error: "HTTP 400 Not valid"})
  } 
});

app.get("/users", (req, res) => {
  let users = []
  db.collection("users")
    .find()
    .forEach(user => users.push(user))
    .then(() => {
      res.status(200).json(users)
    })
    .catch(() => {
      res.status(500).json({error: "HTTP 500 Could not fetch"})
    })
});

app.post("/newUser", async (req, res) => {
  let message = req.body
  try
  {
    const hashedPassword = await bcrypt.hash(message.password, 10);
    const dbs = db.collection("users")
    const doc = await dbs.insertOne({username: message.username, password: hashedPassword, messages: message.messages, friends: message.friends});
    if (doc)
    {
      return res.status(201).json(doc)
    }
  }
  catch(err)
  {
    res.status(405).json({error: "HTTP 405 Could not create object"})
  }
});

//uppdatera en friendRequest
app.patch("/handleFriend/:username/:friend/:isFriend", async (req, res) => {
  const {username, friend, isFriend} = req.params;
  //const update = req.body;

  if(isFriend === "false")
  {
    try
    {
      await db.collection("users")
      .updateOne({"username": username, "friends.friend": friend},
                  {$set: {"friends.$.isFriend": true}})

      const result = db.collection("users")
      .updateOne(
        { username: friend },
        { $push: { friends: { friend: username, isFriend: true } } }
        );
      if (result.modifiedCount === 0) {
        return res.status(404).json({ error: "No friend found!" });
      }
      res.status(200).json({ message: "Friendship updated successfully" });
    }
    catch(error)
    {
      console.error(error);
      res.status(500).json({ error: "Something broke!" });
    }
  }
  else
  {
    await db.collection("users")
    .updateOne({"username": username}, {$pull: {friends: {friend: friend}}});

    const result = db.collection("users")
    .updateOne({"username": friend}, {$pull: {friends: {friend: username}}})
    .then(result => {
      if (result.modifiedCount === 0) {
        return res.status(404).json({error: "No friend found!"})
      }
      else{
        res.status(200).json(result)
      }
    })
      .catch(err => {
        console.error(err);
        res.status(500). json({error : "Something broke!"})
    });
  }
});

app.all(/users.*/, (req, res) => {
  res.status(405).json({error: "HTTP 405 Wrong method"})
  });

app.use((err, req, res, next) => {
      console.error(err.stack);
      res.status(500).json('Something broke!');
    });

module.exports = app;