module RR = ReasonReact;
module RRR = RR.Router;
let str = RR.string;
let el = RR.element;
let arr = RR.array;

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

module type Config = {
  type route;
  let toUrl: route => string;
  let toRoute: ReasonReact.Router.url => route;
};

module CreateRouter = (Config: Config) => {
  type route = Config.route;

  type renderProps = {
    updateRoute: route => unit,
    route,
  };

  type state = {route};

  type action =
    | UpdateRoute(route);

  let component = RR.reducerComponent("Router");

  let make = (~render, _children) => {
    ...component,

    initialState: () => {
      route: RRR.dangerouslyGetInitialUrl() |> Config.toRoute,
    },

    didMount: self => {
      let watchId =
        RRR.watchUrl(url => self.send(UpdateRoute(Config.toRoute(url))));
      self.onUnmount(() => RRR.unwatchUrl(watchId));
    },

    reducer: (action, _state) => {
      Js.log2("compnent:reducer:action", action);
      switch (action) {
      | UpdateRoute(route) => RR.Update({route: route})
      };
    },

    render: self =>
      render({
        updateRoute: route => self.send(UpdateRoute(route)),
        route: self.state.route,
      }),
  };
};

type page =
  | Dashboard
  | Users
  | User(int);

module Config = {
  type route = page;
  let toRoute = (url: RRR.url) =>
    switch (url.path) {
    | ["user", id] => User(int_of_string(id))
    | ["users"] => Users
    | _ => Dashboard
    };
  let toUrl = route =>
    switch (route) {
    | User(id) => "/user/" ++ string_of_int(id)
    | Users => "/users"
    | Dashboard => "/"
    };
};

module Router = CreateRouter(Config);

module Link = {
  let component = ReasonReact.statelessComponent("Link");
  let make = (~route, ~toUrl, ~render, _children) => {
    ...component,
    render: _self => {
      let href = toUrl(route);
      let onClick = e => {
        ReactEvent.Mouse.preventDefault(e);
        ReasonReact.Router.push(href);
      };
      <a href onClick> {render()} </a>;
    },
  };
};

module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _self => {
    ...component,
    render: _self =>
      <div>
        <Link
          route=Dashboard
          toUrl=Config.toUrl
          render={() => str("Dashboard")}
        />
        {RR.string(" | ")}
        <Link route=Users toUrl=Config.toUrl render={() => str("Users")} />
        {RR.string(" | ")}
        <Link
          route={User(23)}
          toUrl=Config.toUrl
          render={() => str("User/1")}
        />
        {RR.string(" | ")}
        <Router
          render={({route}) =>
            switch (route) {
            | Dashboard => <Dashboard />
            | User(id) => <User id />
            | Users => <Users />
            }
          }
        />
      </div>,
  };
};
ReactDOMRe.renderToElementWithId(<App />, "root");