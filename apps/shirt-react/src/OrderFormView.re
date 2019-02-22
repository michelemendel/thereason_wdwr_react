open OrderFormState;
module U = OrderFormUtils;

let makeSelect = (label: string, choices: array(string), value: string, changeFcn) => {
  let makeOptionElement = (value: string) => {
    <option key=value value> {ReasonReact.string(value)} </option>;
  };

  let menuOptionElements = Belt.Array.map(choices, makeOptionElement);

  <span className="item">
    <label> {ReasonReact.string(" " ++ label ++ ": ")} </label>
    <select value onChange=changeFcn> {ReasonReact.array(menuOptionElements)} </select>
  </span>;
};

let createOrder = (state: state): Shirt.Order.t => {
  {
    orderNumber: state.nextOrderNumber,
    quantity: U.toIntWithDefault(state.qtyStr, 0),
    size: U.convertWithDefault(state.sizeStr, Shirt.Size.Medium, Shirt.Size.fromString),
    sleeve: U.convertWithDefault(state.sleeveStr, Shirt.Sleeve.Long, Shirt.Sleeve.fromString),
    color: U.convertWithDefault(state.colorStr, Shirt.Color.White, Shirt.Color.fromString),
    pattern: U.convertWithDefault(state.patternStr, Shirt.Pattern.Solid, Shirt.Pattern.fromString),
  };
};

let view = (state, send) => {
  let orderItems =
    Belt.Array.map(state.orders, order =>
      <OrderItem
        key={string_of_int(order.orderNumber)}
        order
        deleteFunction={_event => send(Delete(order))}
      />
    );

  let orderTable =
    if (Belt.Array.length(state.orders) > 0) {
      <table>
        <thead>
          <tr>
            <th> {ReasonReact.string("Qty")} </th>
            <th> {ReasonReact.string("Size")} </th>
            <th> {ReasonReact.string("Sleeve")} </th>
            <th> {ReasonReact.string("Color")} </th>
            <th> {ReasonReact.string("Pattern")} </th>
            <th> {ReasonReact.string("Action")} </th>
          </tr>
        </thead>
        <tbody> {ReasonReact.array(orderItems)} </tbody>
      </table>;
    } else {
      <p> {ReasonReact.string("No orders entered yet.")} </p>;
    };

  <div>
    <p className="flex">
      <span className="item">
        {ReasonReact.string("Qty: ")}
        <input
          type_="text"
          size=4
          value={state.qtyStr}
          onChange={event => send(ChangeQty(ReactEvent.Form.target(event)##value))}
        />
      </span>
      {makeSelect("Size", [|"XS", "S", "M", "L", "XL", "XXL", "XXXL"|], state.sizeStr, event =>
         send(ChangeSize(ReactEvent.Form.target(event)##value))
       )}
      {makeSelect("Sleeve", [|"Short sleeve", "Long sleeve", "Extra-long sleeve"|], state.sleeveStr, event =>
         send(ChangeSleeve(ReactEvent.Form.target(event)##value))
       )}
      {makeSelect("Color", [|"White", "Blue", "Red", "Green", "Brown"|], state.colorStr, event =>
         send(ChangeColor(ReactEvent.Form.target(event)##value))
       )}
      {makeSelect("Pattern", [|"Solid", "Pinstripe", "Checked"|], state.patternStr, event =>
         send(ChangePattern(ReactEvent.Form.target(event)##value))
       )}
      <span className="item">
        <button
          onClick={_event => {
            let order = createOrder(state);
            send(Enter(order));
          }}>
          {ReasonReact.string("Add")}
        </button>
      </span>
    </p>
    <p id="errorText"> {ReasonReact.string(state.errorText)} </p>
    orderTable
  </div>;
};