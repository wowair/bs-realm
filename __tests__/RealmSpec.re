open Jest;

open Expect;

let _ =
  describe("Empty schema json", () => {
    let emptySchemaJson =
      Js.Json.parseExn(
        {js|
          {
            "name": "SchemaName",
            "properties": {}
          }
        |js},
      );
    let schema: RealmRe.schema = {
      name: "SchemaName",
      primaryKey: None,
      properties: [],
    };
    test("should return correct json for empty schema", () =>
      expect(RealmRe.schema_to_json(schema)) |> toEqual(emptySchemaJson)
    );
  });

let _ =
  describe("Schema json primary key", () => {
    let schemaWithPrimaryFieldJson =
      Js.Json.parseExn(
        {js|
          {
            "name": "SchemaName",
            "primaryKey": "field",
            "properties": {"field": "string"}
          }
        |js},
      );
    let schemaWithPrimaryField: RealmRe.schema = {
      name: "SchemaName",
      primaryKey: Some("field"),
      properties: [("field", String)],
    };
    let schemaWithoutPrimaryFieldJson =
      Js.Json.parseExn(
        {js|
        {
          "name": "SchemaName",
          "properties": {"field": "string"}
        }
      |js},
      );
    let schemaWithoutPrimaryField: RealmRe.schema = {
      name: "SchemaName",
      primaryKey: None,
      properties: [("field", String)],
    };
    test("should return correct json for schema with primary key", () =>
      expect(RealmRe.schema_to_json(schemaWithPrimaryField))
      |> toEqual(schemaWithPrimaryFieldJson)
    );
    test("should return correct json for schema without primary key", () =>
      expect(RealmRe.schema_to_json(schemaWithoutPrimaryField))
      |> toEqual(schemaWithoutPrimaryFieldJson)
    );
  });

let _ =
  describe("Schema property fields", () => {
    let schemaJson =
      Js.Json.parseExn(
        {js|
          {
            "name": "SchemaName",
            "properties": {
                "stringField": "string",
                "optionalStringField": "string?",
                "intField": "int",
                "optionalIntField": "int?",
                "floatField": "float",
                "optionalFloatField": "float?",
                "boolField": "bool",
                "optionalBoolField": "bool?",
                "customField": "CustomType",
                "optionalCustomField": "CustomType?",
                "listField": {
                    "objectType": "CustomType",
                    "type": "list"
                }
            }
          }
        |js},
      );
    let schema: RealmRe.schema = {
      name: "SchemaName",
      primaryKey: None,
      properties: [
        ("stringField", String),
        ("optionalStringField", OptionalString),
        ("intField", Integer),
        ("optionalIntField", OptionalInteger),
        ("floatField", Float),
        ("optionalFloatField", OptionalFloat),
        ("boolField", Bool),
        ("optionalBoolField", OptionalBool),
        ("customField", Custom("CustomType")),
        ("optionalCustomField", OptionalCustom("CustomType")),
        ("listField", List("CustomType")),
      ],
    };
    test("should equal expected schema json", () =>
      expect(RealmRe.schema_to_json(schema)) |> toEqual(schemaJson)
    );
  });
