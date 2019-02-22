let component = ReasonReact.reducerComponent("OrderForm");

let make = _children => {
  ...component,
  initialState: () => OrderFormState.initialState(),
  reducer: (action, state) => OrderFormReducer.reducer(action, state),
  render: ({state, send}) => OrderFormView.view(state, send),
};