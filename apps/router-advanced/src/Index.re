/*
 * Link Behavior
 * https://accessibility.oit.ncsu.edu/it-accessibility-at-nc-state/developers/accessibility-handbook/mouse-and-keyboard-events/links/link-behavior/
 *
 */

module RR = ReasonReact;
module RRR = RR.Router;
let str = RR.string;
let el = RR.element;
let arr = RR.array;

type page =
  | Dashboard
  | Users
  | User(int);

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

module type Mapper = {
  let toPage: RRR.url => page;
  let toUrl: page => string;
};

module Mapper: Mapper = {
  let toPage = (url: RRR.url) => {
    let urlHash =
      Js.String.split("/", url.hash)->Belt.Array.keep(it => it != "");

    Js.log("--------Mapper---------");
    Js.log2("Mapper:url.path", url.path);
    Js.log2("Mapper:url.path", url.path);
    Js.log2("Mapper:url.hash:split", urlHash);
    /* Js.log2("Mapper:url.search", url.search); */

    switch (urlHash) {
    | [|"users"|] => Users
    | [|"user", id|] => User(int_of_string(id))
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

module App = {
  type state = {route: page};

  type action =
    | UpdatePage(page);

  let navigate = (path, _event) => {
    Js.log("--------NAVIGATE---------");
    Js.log2("path", path);
    /* ReactEvent.Mouse.preventDefault(event); */
    ReasonReact.Router.push(path);
  };

  let component = RR.reducerComponent("App");

  let make = _children => {
    ...component,

    initialState: () => {
      Js.log("--------INITIALIZE STATE---------");
      Js.log2("init:route", RRR.dangerouslyGetInitialUrl());
      {route: Mapper.toPage(RRR.dangerouslyGetInitialUrl())};
    },

    reducer: (action, _state) => {
      Js.log("--------REDUCER---------");
      Js.log2("reducer:action", action);
      switch (action) {
      | UpdatePage(route) =>
        Js.log2("reducer:route", route);
        RR.Update({route: route});
      };
    },

    didMount: self => {
      Js.log("--------DID MOUNT---------");
      let watchId =
        RRR.watchUrl(url => {
          Js.log("--------WATCH---------");
          Js.log2("watch:path", url.path);
          self.send(UpdatePage(Mapper.toPage(url)));
        });
      self.onUnmount(() => RRR.unwatchUrl(watchId));
    },

    render: ({state}) => {
      <div>
        <input
          type_="button"
          className="button"
          onClick={navigate("/#/dashboard?hello=world#home/")}
          value="Dashboard"
        />
        {RR.string(" | ")}
        <input
          type_="button"
          className="button"
          onClick={navigate("/#/users/")}
          value="Users"
        />
        {RR.string(" | ")}
        <input
          type_="button"
          className="button"
          onClick={navigate("/#/user/19/")}
          value="User 1"
        />
        {Js.log2("View:route", state.route)
         switch (state.route) {
         | Dashboard => <Dashboard />
         | Users => <Users />
         | User(id) => <User id />
         }}
      </div>;
    },
  };
};

Js.log("--------START---------");
Js.log2("url", RRR.dangerouslyGetInitialUrl());

ReactDOMRe.renderToElementWithId(<App />, "root");