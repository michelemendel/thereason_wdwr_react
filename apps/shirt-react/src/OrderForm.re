open Utils;

let component = ReasonReact.reducerComponent(__MODULE__);

let make = (~onClick, _children) => {
  let click = (_event, self) => {
    onClick();
    self.ReasonReact.send(OrderFormState.ChangeQty("10"));
    self.ReasonReact.send(
      OrderFormState.ChangeSize(Shirt.Size.toString(Shirt.Size.Large)),
    );
  };
  {
    ...component,
    initialState: () => OrderFormState.initialState(),
    reducer: (action, state) => OrderFormReducer.reducer(action, state),
    render: self =>
      <div>
        <div> {OrderFormView.view(self.state, self.send)} </div>
        <div>
          <button onClick={self.handle(click)}>
            {rrString("Set Qty and Size, and log something to console")}
          </button>
        </div>
      </div>,
    /*didMount: self => self.send(OrderFormState.ChangeQty("1")),*/
  };
};