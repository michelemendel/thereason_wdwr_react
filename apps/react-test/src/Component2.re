/* State declaration */
type state = {
  count: int,
  show: bool,
};

/* Action declaration */
type action =
  | Click
  | Set(int)
  | Toggle;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Component2");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~greeting, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {count: 0, show: true},

  /* State transitions */
  reducer: (action, state) => {
    Js.log2("REDUCER:action", action);
    Js.log2("REDUCER:state", state);

    switch (action) {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Set(n) => ReasonReact.Update({...state, count: n})
    | Toggle => ReasonReact.Update({...state, show: !state.show})
    };
  },

  render: self => {
    Js.log2("RENDER:self", self);

    let message = "You've clicked this " ++ string_of_int(self.state.count) ++ " times(s)";
    <>
      <div> <button onClick={_event => self.send(Click)}> {ReasonReact.string(message)} </button> </div>
      <div> <button onClick={_event => self.send(Set(0))}> {ReasonReact.string("Reset")} </button> </div>
      <div>
        <button onClick={_event => self.send(Toggle)}> {ReasonReact.string("Toggle greeting")} </button>
      </div>
      <div> {self.state.show ? ReasonReact.string(greeting) : ReasonReact.null} </div>
    </>;
  },
};