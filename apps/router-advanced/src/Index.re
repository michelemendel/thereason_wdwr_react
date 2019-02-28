let str = ReasonReact.string;

let el = ReasonReact.element;

let arr = ReasonReact.array;

module Dashboard = {
  let component = ReasonReact.statelessComponent("Dashboard");
  let make = _children => {...component, render: _self => <div> <h2> {str("Dashboard")} </h2> </div>};
};

module Users = {
  let component = ReasonReact.statelessComponent("Users");
  let make = _children => {...component, render: _self => <div> <h2> {str("Users")} </h2> </div>};
};

module User = {
  let component = ReasonReact.statelessComponent("User");
  let make = (~id, _children) => {
    ...component,
    render: _self => <div> <h2> {str("User : " ++ string_of_int(id))} </h2> </div>,
  };
};

type page =
  | Dashboard
  | Users
  | User(int);

module type Mapper = {
  let toPage: ReasonReact.Router.url => page;
  let toUrl: page => string;
};

module Mapper: Mapper = {
  let toPage = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | ["users"] => Users
    | ["user", id] => User(int_of_string(id))
    | _ => Dashboard
    };
  let toUrl = page =>
    switch (page) {
    | Users => "users"
    | User(id) => "user/" ++ string_of_int(id)
    | _ => "dashboard"
    };
};

module App = {
  type state = {route: page};

  type action =
    | UpdatePage(page);

  let component = ReasonReact.reducerComponent("App");

  let make = _children => {
    ...component,

    initialState: () => {route: ReasonReact.Router.dangerouslyGetInitialUrl() |> Mapper.toPage},

    reducer: (action, _state) =>
      switch (action) {
      | UpdatePage(route) => ReasonReact.Update({route: route})
      },

    didMount: self => {
      let watchId = ReasonReact.Router.watchUrl(url => self.send(UpdatePage(Mapper.toPage(url))));
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
    },

    render: ({state}) =>
      <div>
        {switch (state.route) {
         | Dashboard => <Dashboard />
         | Users => <Users />
         | User(id) => <User id />
         }}
        <a href="dashboard"> {str("Dashboard")} </a>
        <a href="user/1"> {str("Users")} </a>
        <a href="users"> {str("Users")} </a>
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");