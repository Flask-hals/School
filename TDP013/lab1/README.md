# Set up database

Currently the database which we use is a local mongoDB database, which means that to run the server you need to create your own database.
For simplicity, use the database name `tdp013` and add a collection called `messages`.

To connect with the database, use:

```bash
sudo systemctl start mongod
```

## How to run

Make sure you have set up a local database with the correct names for database and collection. To see info about this, see **Database**.
When the database is set up you are ready to run the server.
Run the server using the following command:

```bash
npm start
```

To run the tests you will neeed another local database named `tdp013-test`, which also should contain a collection called `messages`.

## How to run tests

Make sure you have set up a local database with the correct names for database and collection. To see info about this, see **Database**.
When the database is set up you are ready to run the tests.
Run the tests using the following command:

```bash
npm test
```

To use the coverage tool along with the tests, use the following command:

```bash
nyc npm test
```

## Requirements

Make sure you have all the necessary packages.
To see all the packages needed, check the `dependencies` section, in the `package.json` file.
For testing you also need the packages in the `devDependencies` section.

To install the packages run the following command:

```
npm install
```

Make sure you run the command in the same folder as `package.json`.

## Specification used

We have decided to follow specification 1, which can be seen on the course web page.
