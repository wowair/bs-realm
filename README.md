# [BuckleScript](https://github.com/bloomberg/bucklescript) bindings for [realm](https://github.com/realm/realm-js)
## Getting started

#### This package has not been published yet so use with caution.

### How to install?
Navigate to your project directory and run either of the following commands:

`yarn add https://github.com/wowair/bs-realm/` 
`npm install https://github.com/wowair/bs-realm`

We will try to provide documentation for you to get up and running with Realm but with more advanced stuff we recommend the [Realm JavaScript documentation](https://realm.io/docs/javascript/latest/)

### Setting up your schema

We first start by setting up our data model. In order to do that we build something called a schema. 

A schema is an outline for our data model. Lets build a simple one for example and name the file `RealmSchema.re`.

``` 
/* RealmSchema.re */ 

open RealmRe;

/* We can aggregate the schemas to it's relative category
module BusinessSchemas = {
  let order = {
    name: "Order",
    primaryKey: None,
    properties: [
      ("name", String),
      ("date", String),
      ("paid", Bool),
      ("shipped", Bool),
    ],
  };

  let contract = {
    name: "Contract",
    primaryKey: None,
    properties: [
      ("beginDate", String),
      ("endDate", Integer),
      ("valid", Bool),
    ],
  };
};

/* Or declare the schematype within the scope of the schema module */
let clientSchema = {
  name: "Client",
  primaryKey: Some("id"),
  properties: [
    ("name", String),
    ("id", Integer),
    ("orders", List("Order"),
    ("contract", Custom("Contract"),
  ],
};

let config = {
  "schema": [|
    schema_to_json(BusinessSchemas.contract),
    schema_to_json(BusinessSchemas.order),
    schema_to_json(clientSchema),
  |],
  "schemaVersion": 1,
};
``` 
**__Important__**: 
> Whenever you make changes to your schema you will need to increment your version.
> If the version on disk does not match the schema an error will be thrown and the app will crash
> Also if you change the schema in a way that existing fields need to be updated you will need to
> provide a migration function. We will cover that below.

### Writing to the database


### Reading from the database.



