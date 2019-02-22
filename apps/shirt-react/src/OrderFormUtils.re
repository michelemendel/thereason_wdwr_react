let convertWithDefault = (str: string, defaultValue: 'a, convert: string => option('a)): 'a => {
  Belt.Option.getWithDefault(convert(str), defaultValue);
};

let toIntWithDefault = (s: string, defaultValue: int): int => {
  switch (int_of_string(s)) {
  | result => result
  | exception (Failure("int_of_string")) => defaultValue
  };
};