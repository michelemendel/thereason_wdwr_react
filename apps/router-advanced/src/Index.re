module RR = ReasonReact;
module RRR = RR.Router;

let str = ReasonReact.string;
let el = ReasonReact.element;
let arr = ReasonReact.array;

type page =
  | Dashboard
  | Users
  | User(int);

module type Mapper = {
  let toPage: RRR.url => page;
  let toUrl: page => string;
};

module Mapper: Mapper = {
  let toPage = (url: RRR.url) => {
    Js.log2("Mapper:url", url);
    Js.log2("Mapper:url.path", url.path);
    Js.log2("Mapper:dangerUrl", RRR.dangerouslyGetInitialUrl());

    switch (url.path) {
    | ["users"] => Users
    | ["user", id] => User(int_of_string(id))
    | _ => Dashboard
    };
  };
  let toUrl = page =>
    switch (page) {
    | Users => "users"
    | User(id) => "user/" ++ string_of_int(id)
    | _ => "dashboard"
    };
};
module Dashboard = {
  let component = ReasonReact.statelessComponent("Dashboard");
  let make = _children => {
    ...component,
    render: _self => <div> <h2> {str("Dashboard")} </h2> </div>,
  };
};
module Users = {
  let component = ReasonReact.statelessComponent("Users");
  let make = _children => {
    ...component,
    render: _self => <div> <h2> {str("Users")} </h2> </div>,
  };
};

module User = {
  let component = ReasonReact.statelessComponent("User");
  let make = (~id, _children) => {
    ...component,
    render: _self =>
      <div> <h2> {str("User : " ++ string_of_int(id))} </h2> </div>,
  };
};

module App = {
  type state = {route: page};

  type action =
    | UpdatePage(page);

  let component = RR.reducerComponent("App");

  let make = _children => {
    ...component,

    initialState: () => {
      route: RRR.dangerouslyGetInitialUrl() |> Mapper.toPage,
    },

    reducer: (action, _state) => {
      Js.log2("advanced:reducer:action", action);
      switch (action) {
      | UpdatePage(route) => RR.Update({route: route})
      };
    },

    didMount: self => {
      let watchId =
        RRR.watchUrl(url => self.send(UpdatePage(Mapper.toPage(url))));
      self.onUnmount(() => RRR.unwatchUrl(watchId));
    },

    render: ({state}) =>
      <div>
        <a href="dashboard"> {str("Dashboard")} </a>
        {RR.string(" | ")}
        <a href="users"> {str("Users")} </a>
        {RR.string(" | ")}
        <a href="user/1"> {str("User 1")} </a>
        {Js.log2("View:route", state.route)
         switch (state.route) {
         | Dashboard => <Dashboard />
         | Users => <Users />
         | User(id) => <User id />
         }}
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");