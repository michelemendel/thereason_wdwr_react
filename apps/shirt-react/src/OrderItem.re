open Utils;

let component = RR.statelessComponent("OrderItem");

let make =
    (
      ~order: Shirt.Order.t,
      ~deleteFunction: ReactEvent.Mouse.t => unit,
      _children,
    ) => {
  ...component,

  render: _self => {
    <tr>
      <td> {rrStringOfInt(order.quantity)} </td>
      <td> {Shirt.Size.toRRString(order.size)} </td>
      <td> {rrString(Shirt.Sleeve.toString(order.sleeve))} </td>
      <td> {rrString(Shirt.Color.toString(order.color))} </td>
      <td> {rrString(Shirt.Pattern.toString(order.pattern))} </td>
      <td>
        <button onClick=deleteFunction> {rrString("Delete")} </button>
      </td>
    </tr>;
  },
};