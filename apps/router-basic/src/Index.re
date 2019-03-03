module RR = ReasonReact;
module RRR = RR.Router;

let str = ReasonReact.string;
let el = ReasonReact.element;
let arr = ReasonReact.array;

type page =
  | Dashboard
  | Users;

module type Mapper = {
  let toPage: RRR.url => page;
  let toUrl: page => string;
  let toUrlHash: page => string;
};

module Mapper: Mapper = {
  let toPage = (url: RRR.url) => {
    Js.log2("Mapperurl", url);
    Js.log2("Mapper:url.hash", url.hash);
    Js.log2("Mapper:dangerUrl", RRR.dangerouslyGetInitialUrl());

    switch (url.hash) {
    | "users" => Users
    | _ => Dashboard
    };
  };
  let toUrl = page =>
    switch (page) {
    | Users => "users"
    | _ => "dashboard"
    };
  let toUrlHash = page =>
    switch (page) {
    | Users => "#users"
    | _ => "#dashboard"
    };
};

module Dashboard = {
  let component = RR.statelessComponent("Dashboard");
  let make = _children => {
    ...component,
    render: _self => <div> <h2> {str("Dashboard")} </h2> </div>,
  };
};

module Users = {
  let component = RR.statelessComponent("Users");
  let make = _children => {
    ...component,

    render: _self => {
      let gotoDB = _event => {
        RRR.push(Mapper.toUrlHash(Dashboard));
      };

      <div>
        <h2> {str("Users")} </h2>
        <div>
          <button onClick=gotoDB> {RR.string("Go to Dashboard")} </button>
        </div>
      </div>;
    },
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
      {route: RRR.dangerouslyGetInitialUrl() |> Mapper.toPage};
    },

    reducer: (action, _state) => {
      Js.log2("Basic:reducer:action", action);
      switch (action) {
      | UpdatePage(route) => RR.Update({route: route})
      };
    },

    didMount: self => {
      Js.log("Basic:didMount");
      let watchId =
        RRR.watchUrl(url => {
          Js.log("Basic:watch");
          self.send(UpdatePage(Mapper.toPage(url)));
        });
      self.onUnmount(() => RRR.unwatchUrl(watchId));
    },

    render: ({state}) => {
      <div>
        <div>
          <a href="#dashboard"> {str("Dashboard")} </a>
          {RR.string(" | ")}
          <a href="#users"> {str("Users")} </a>
        </div>
        /* Pages */
        {switch (state.route) {
         | Dashboard => <Dashboard />
         | Users => <Users />
         }}
      </div>;
    },
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");