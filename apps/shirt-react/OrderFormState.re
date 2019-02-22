type state = {
  qtyStr: string,
  sizeStr: string,
  sleeveStr: string,
  colorStr: string,
  patternStr: string,
  nextOrderNumber: int,
  orders: array(Shirt.Order.t),
  errorText: string,
};

type action =
  | Enter(Shirt.Order.t)
  | ChangeQty(string)
  | ChangeSize(string)
  | ChangeSleeve(string)
  | ChangeColor(string)
  | ChangePattern(string)
  | Delete(Shirt.Order.t);

let initialState = () => {
  qtyStr: "1",
  sizeStr: Shirt.Size.toString(Shirt.Size.Medium),
  sleeveStr: Shirt.Sleeve.toString(Shirt.Sleeve.Long),
  colorStr: Shirt.Color.toString(Shirt.Color.White),
  patternStr: Shirt.Pattern.toString(Shirt.Pattern.Solid),
  orders: [||],
  nextOrderNumber: 1,
  errorText: "",
};