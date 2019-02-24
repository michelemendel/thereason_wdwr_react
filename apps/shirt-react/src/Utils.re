/*
 * ReasonReact utils
 */

module RR = ReasonReact;
let rrString = s => RR.string(s);
let rrStringOfInt = i => RR.string(string_of_int(i));
let rrArray = arr => RR.array(arr);
let rrUpdate = r => ReasonReact.Update(r);

/*
 * Misc utils
 */

let convertWithDefault =
    (str: string, defaultValue: 'a, convert: string => option('a)): 'a => {
  Belt.Option.getWithDefault(convert(str), defaultValue);
};

let toIntWithDefault = (s: string, defaultValue: int): int => {
  switch (int_of_string(s)) {
  | result => result
  | exception (Failure("int_of_string")) => defaultValue
  };
};