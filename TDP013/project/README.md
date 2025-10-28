# Set up database

Currently the database which we use is a local mongoDB database, which means that to run the server you need to create your own database.
For simplicity, use the database name `tdp013` and add a collection called `users`.

To connect with the database, use:

```bash
sudo systemctl start mongod
```

## Requirements

Make sure you have all the necessary packages.
To see all the packages needed, check the `dependencies` section, in the `package.json` file.
For testing you also need the packages in the `devDependencies` section.

To install the packages run the following command:

```bash
npm install
```

Remember to run:

```bash
npm install
```

in the front folder aswell.

Make sure you run the command in the same folder as `package.json`.

## How to run

We have been running this project with https, we have used self certified keys. Which means if you want to run the server the same as we have done,
you will need keys.

To create a local key, run the following command:
```bash
openssl req -nodes -new -x509 -keyout key.pem -out cert.pem
```
create a new folder in back called `certs` and place the two files there.

This is not automaticlly a trusted certificate by the browser. You will need to go to `https://localhost:8000` and accept the certifiacte.

### Backend
    Make sure you have set up a local database with the correct names for database and collection. To see info about this, see **Database**.
    When the database is set up you are ready to run the server.
    Run the server using the following command:

    ```bash
    npm start
    ```

### Frontend
    When you have downloaded all the necessary packages, start the frontend server by running the following command in the `front` folder:

    ```bash
    HTTPS=true npm start
    ```

To run the tests you will neeed another local database named `tdp013-test`, which also should contain a collection called `users`.

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