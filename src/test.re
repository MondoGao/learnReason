/* radius can be omitted */
let drawCircle ::color ::radius=? () => {
  Js.log color;
  switch radius {
  | None => Js.log 1;
  | Some r_ => Js.log r_;
  }
};

let color = 1;
let curriedFun = drawCircle ::color;
