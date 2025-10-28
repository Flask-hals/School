// Maybe remove mongoose and istanbul dependencies, also move all dev packages to devDependencies

const dotenv = require("dotenv");
const express = require("express")
const path = require("path");

const cors = require("cors");

const corsOptions = {
  origin: 'http://localhost:8080', // Frontend access
	optionsSuccessStatus: 200,
  methods: ['GET', 'POST', 'PATCH']
};


const { connectToDb, getDb } = require("./db")
const { ObjectId } = require("mongodb")

const regex = /[!@#$%^&*()\-+={}[\]:;"'<>,.?\/|\\]/;

const envFile = process.env.NODE_ENV === "test" ? ".env.test" : ".env.development";
dotenv.config({path: envFile});

const app = express();
app.use(cors(corsOptions));
app.use(express.json())
app.use(express.static(path.join(__dirname, "../../lab2")));

let db

connectToDb((err) => {
  //console.log("Connecting to:", process.env.MONGODB_URI);
  if(!err) {
    app.listen(3000, () => {
      console.log("http://localhost:3000")
    })
    db = getDb()

  }
})

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "../../lab2/index.html"));
});

app.get("/messages", (req, res) => {
  
  let messages = []
  
  db.collection("messages")
    .find()
    .forEach(message => messages.push(message))
    .then(() => {
      res.status(200).json(messages)
    })
    .catch(() => {
      res.status(500).json({error: "HTTP 500 Could not fetch"})
    })
});

app.get("/messages/:id", (req, res) => {

  if (ObjectId.isValid(req.params.id)) {
    db.collection("messages")
      .findOne({_id: new ObjectId(req.params.id)})
      .then(doc => {
        if (doc == null)
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

app.post("/messages", (req, res) => {
  const message = req.body
  
  if (!regex.test(message.message) && "message" in message && "read" in message && typeof message.read === "boolean" &&
      typeof message.message === "string" && Object.keys(message).length == 4){
    db.collection("messages")
      .insertOne(message)
      .then(result => {
        res.status(201).json(result)
      })
      .catch(err => {
        res.status(405).json({error: "HTTP 405 Could not create object"})
      })
    }
  else{
    res.status(400).json({error: "HTTP 400 Not valid"})
  }  
});

app.patch("/messages/:id", (req, res) => {
  const update = req.body

  if (ObjectId.isValid(req.params.id) && "read" in update && typeof update.read === "boolean" && Object.keys(update).length == 1) {
    db.collection("messages")
      .updateOne({_id: new ObjectId(req.params.id)}, {$set: update})
      .then(result => {
        if (result.matchedCount == 0)
          res.status(400).json({error: "HTTP 400 No ID match"})
        else
          res.status(200).json(result)
      })
      .catch(err => {
        res.status(400).json({error: "HTTP 400 No ID match"})
      })
  }
  else {
    res.status(400).json({error: "HTTP 400 Not a valid id or update status"})
  }
});

app.all(/messages.*/, (req, res) => {
  res.status(405).json({error: "HTTP 405 Wrong method"})
  });

app.use((err, req, res, next) => {
      console.error(err.stack);
      res.status(500).json('Something broke!');
    });

module.exports = app;