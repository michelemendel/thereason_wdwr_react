let str = ReasonReact.string;

let el = ReasonReact.element;

let arr = ReasonReact.array;

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

  let component = ReasonReact.reducerComponent("Router");

  let make = (~render, _children) => {
    ...component,

    initialState: () => {
      route: ReasonReact.Router.dangerouslyGetInitialUrl() |> Config.toRoute,
    },

    didMount: self => {
      let watchId =
        ReasonReact.Router.watchUrl(url =>
          self.send(UpdateRoute(Config.toRoute(url)))
        );
      self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
    },

    reducer: (action, _state) => {
      Js.log2("compnent:advanced:reducer:action", action);
      switch (action) {
      | UpdateRoute(route) => ReasonReact.Update({route: route})
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
  let toRoute = (url: ReasonReact.Router.url) =>
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
        ReactEventRe.Mouse.preventDefault(e);
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
        <Router
          render={({route}) =>
            switch (route) {
            | Dashboard => <Dashboard />
            | User(id) => <User id />
            | Users => <Users />
            }
          }
        />
        <Link route=Users toUrl=Config.toUrl render={() => str("Users!")} />
        <Link
          route=Dashboard
          toUrl=Config.toUrl
          render={() => str("Dashboard!")}
        />
      </div>,
  };
};
ReactDOMRe.renderToElementWithId(<App />, "root");