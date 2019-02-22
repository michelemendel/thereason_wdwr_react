let reducer = (action, state: OrderFormState.state) =>
  switch (action) {
  | OrderFormState.Enter(order) =>
    let n = OrderFormUtils.toIntWithDefault(state.qtyStr, 0);
    if (n > 0 && n <= 100) {
      ReasonReact.Update({
        ...state,
        orders: Belt.Array.concat(state.orders, [|order|]),
        nextOrderNumber: state.nextOrderNumber + 1,
        errorText: "",
      });
    } else {
      ReasonReact.Update({...state, errorText: "Quantity must be between 1 and 100."});
    };
  | ChangeQty(newQty) => ReasonReact.Update({...state, qtyStr: newQty})
  | ChangeSize(newSize) => ReasonReact.Update({...state, sizeStr: newSize})
  | ChangeSleeve(newSleeve) => ReasonReact.Update({...state, sleeveStr: newSleeve})
  | ChangeColor(newColor) => ReasonReact.Update({...state, colorStr: newColor})
  | ChangePattern(newPattern) => ReasonReact.Update({...state, patternStr: newPattern})
  | Delete(order) =>
    ReasonReact.Update({
      ...state,
      orders: Belt.Array.keep(state.orders, item => item.orderNumber != order.orderNumber),
    })
  };