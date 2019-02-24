open Utils;
open Belt;

let reducer = (action, state: OrderFormState.state) =>
  switch (action) {
  | OrderFormState.Enter(order) =>
    let n = toIntWithDefault(state.qtyStr, 0);
    if (n > 0 && n <= 100) {
      rrUpdate({
        ...state,
        orders: Belt.Array.concat(state.orders, [|order|]),
        nextOrderNumber: state.nextOrderNumber + 1,
        errorText: "",
      });
    } else {
      rrUpdate({...state, errorText: "Quantity must be between 1 and 100."});
    };
  | ChangeQty(newQty) => rrUpdate({...state, qtyStr: newQty})
  | ChangeSize(newSize) => rrUpdate({...state, sizeStr: newSize})
  | ChangeSleeve(newSleeve) => rrUpdate({...state, sleeveStr: newSleeve})
  | ChangeColor(newColor) => rrUpdate({...state, colorStr: newColor})
  | ChangePattern(newPattern) => rrUpdate({...state, patternStr: newPattern})
  | Delete(order) =>
    rrUpdate({
      ...state,
      orders:
        Array.keep(state.orders, item =>
          item.orderNumber != order.orderNumber
        ),
    })
  };