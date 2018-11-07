type t;

module Result = {
  type t = array(Js.Json.t);
  [@bs.send] external addListener : (t, (t, 'c) => unit) => unit = "";
  [@bs.send] external removeListener : (t, (t, 'c) => unit) => unit = "";
  [@bs.send] [@bs.splice]
  external filtered : (t, string, array(string)) => t = "";
};

[@bs.module "realm"]
external openRealm : Js.t('a) => Js.Promise.t(t) = "open";

[@bs.module]
[@bs.new] external realm : Js.t('a) => t = "";

[@bs.send] external objects : (t, string) => Result.t = "";

[@bs.send] external objectForPrimaryKey : (t, string, 'a) => Js.Json.t = "";

[@bs.send] external write : (t, unit => unit) => unit = "";

[@bs.get] external schemaVersion : t => int = "";

[@bs.send] external create : (t, string, Js.Json.t, bool) => Js.Json.t = "";

[@bs.send] external delete : (t, array(Js.Json.t)) => unit = "";

[@bs.send] external deleteAll : (t) => unit = "";

type schemaDataType =
  | String
  | OptionalString
  | Integer
  | OptionalInteger
  | Float
  | OptionalFloat
  | Bool
  | OptionalBool
  | Custom(string)
  | OptionalCustom(string)
  | List(string);

type schema = {
  name: string,
  primaryKey: option(string),
  properties: list((string, schemaDataType)),
};

let data_type_to_json = schemaDataType =>
  switch (schemaDataType) {
  | String => Js.Json.string("string")
  | OptionalString => Js.Json.string("string?")
  | Integer => Js.Json.string("int")
  | OptionalInteger => Js.Json.string("int?")
  | Float => Js.Json.string("float")
  | OptionalFloat => Js.Json.string("float?")
  | Bool => Js.Json.string("bool")
  | OptionalBool => Js.Json.string("bool?")
  | Custom(name) => Js.Json.string(name)
  | OptionalCustom(name) => Js.Json.string(name ++ "?")
  | List(name) =>
    Js.Json.object_(
      Js.Dict.fromArray([|
        ("type", Js.Json.string("list")),
        ("objectType", Js.Json.string(name)),
      |]),
    )
  };

let schema_to_json = (schema: schema) => {
  let propertyJson =
    schema.properties
    |> List.map(((key, value)) => (key, data_type_to_json(value)))
    |> Array.of_list
    |> Js.Dict.fromArray
    |> Js.Json.object_;
  Js.Json.object_(
    switch (schema.primaryKey) {
    | Some(primaryKey) =>
      Js.Dict.fromArray([|
        ("name", Js.Json.string(schema.name)),
        ("primaryKey", Js.Json.string(primaryKey)),
        ("properties", propertyJson),
      |])
    | None =>
      Js.Dict.fromArray([|
        ("name", Js.Json.string(schema.name)),
        ("properties", propertyJson),
      |])
    },
  );
};
