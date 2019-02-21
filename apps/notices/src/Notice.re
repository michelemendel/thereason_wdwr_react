[@bs.val] external require: string => string = "";

require("../icons/warning.svg");
require("../icons/error.svg");
require("../icons/information.svg");

let component = ReasonReact.statelessComponent("Notice");

let noticeStyle = color =>
  ReactDOMRe.Style.make(
    ~color,
    ~clear="left",
    ~minHeight="64px",
    ~marginBottom="0.5em",
    ~width="30%",
    ~display="flex",
    ~alignItems="center",
    ~border="1px solid black",
    (),
  );

let make = (~message, ~color, ~icon, _children) => {
  ...component,
  render: _self =>
    <div style={noticeStyle(color)}>
      <img
        src={"icons/" ++ icon ++ ".svg"}
        style={ReactDOMRe.Style.make(~width="48px", ~float="left", ())}
      />
      {ReasonReact.string(message)}
    </div>,
};