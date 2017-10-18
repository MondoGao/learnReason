Js.log "Hello, BuckleScript and Reason!";

/* Let binding */
let b = 2;

let c = {
  let a = 2;
  let b = 3;
  a + b;
};

let score: int = 10;
let total = score + (5: int);

/* String */
let oneSlash = "\\";
let twoSlash = oneSlash ^ {|\|};

let world = {|世界|};

let helloWorld = {j|你好, $world|j};

Js.log(helloWorld);

/* Boolean */
/* not same as Js' Bool */
let a = true; /* var a = 1; */

/* Number */
let temp = 0.5 +. 0.6;

/* Tuple */
let numbers = (1, 2, 3);
let (_, two, _) = numbers;
Js.log two;

/* Record */
type person = {
  age: int,
  name: string,
};

let me = {
  age: 5,
  name: "Mondo",
};

let nextMe = {
  ...me,
    age: me.age+1,
};

let nextMe = 1;

type horsePower = { power: int, metric: bool, };
let metric = true;
let someHorsePower = { power: 10, metric };
/* same as { power: 10, metric: metric } */
/* there 's no punning for a single record field */

/* Variant! */
type myResVariant =
| Yes /* this is a constructor */
| No string /* constructor argument */
| PrettyMuch;
let areUCrushingIt = No "constructorName";

/* Switch */
let msgs = switch (areUCrushingIt) {
  | No nonono => "No worries. Keep going!" ^ nonono
  | Yes => "Great!"
  | PrettyMuch => "Nice!"
};


/* Tuple */
let tup = (1, "string", true);

/* List */
/* immutable */
let lis = [1, 2, 3];
let lis2 = [4, ...lis]; /* There is only one spread-list allowed */

let msgs = switch lis {
  | [] => 1
  | [a, ...rest] => a
};

/* Array - muttable, fix-sized */
let myArr = [|"hello", "world"|];
let firstItem = myArr.(0);

/* Function */
let greet = fun name => "hello" ^ name;
greet "world";
/* curried by default */
let add = fun x y z => x + y + z;
/* same as let add x y z => x + y + z; */
add 1 2 3;

let greetMore = fun name => {
  let part1 = "Hello";
  part1 ^ " " ^ name
};

let labeledArgs = fun name::name some::some => {
  name ^ some
};
labeledArgs name::"hello" some::"world";

let shortLabeledArgs = fun ::name ::some => {
  name ^ some
};

/* funtion with no argument */
let logSomething () => {
  print_endline "hello";
  print_endline "world";
};
logSomething ();

/* radius can be omitted */
/* radius can be provided a default value, then it's not wrapped by option type */
let drawCircle ::color ::radius=? () => { /* () existing for clear the meaning of fun calls, distinct call from currying */
  Js.log color;
  switch radius {
  | None => Js.log radius;
  | Some r_ => Js.log r_;
  }
};
let color = 1;
let curriedFunction = drawCircle ::color ();
let actualResultWithoutProvidingRadius = drawCircle ::color ();

let payloadRadius: option string = None;
/* If I don't know whether payloadRadius is optional */
let result = drawCircle ::color radius::?payloadRadius ();

/* recursive function, by default, values can't see a binding points to it */
let rec neverTerminate = fun () => neverTerminate ();

/* mutually recursive funtion */
let rec callSecond = fun () => callFirst ()
and callFirst = fun () => callSecond ();

/* If-Else */
/* prefer pattern-match */
let isMorning = true;
let message = if (isMorning) {
  "Good morning!"
} else {
  "Hello!"
};

/* Type Argument */
/* like generics */
type coordinates 'a = ('a, 'a, 'a);

/* apply the coordinates "type function" and return the type (int, int, int) */
type intCoordinatesAlias = coordinates int;
let buddy: intCoordinatesAlias = (10, 20, 20);

/* mutually recursive type */
type student = {taughtBy: teacher}
and teacher = {students: list student};

/* Destruct */
module Destruct = {
  type person = {name: string, age: int};
  let somePerson = {name: "Guy", age: 30};
  let {name: n, age: a} = somePerson;
  let {name: (n: string), age: (a: int)} = somePerson;

  let someFunction person::{name} => {
    /* you can use `name` here */
    Js.log name;
  };

  let otherFunction person::({name} as thePerson) => {
    /* you can use both `name` and the whole record as `thePerson` here */
    Js.log name;
    Js.log thePerson;
  };
};

/* Pattern Matching! */
let reply =
  switch message {
  | "Reason's pretty cool" => "Yep"
  | "good night" => "See ya!"
  | "hello" | "hi" | "heya" | "hey" => "hello to you too!"
  | _ => "Nice to meet you!"
  };

/* let message = */
  /* switch data { */
  /* | GoodResult theMessage => "Success! " ^ theMessage */
  /* | BadResult (0 | 1 | 5) => "Something's wrong. It's a server side problem." */
  /* | BadResult errorCode when isServerError errorCode => "" | BadResult errorCode => "Unknown error occurred. Code: " ^ string_of_int errorCode | NoResult => "Things look fine" }; */


/* Mutate Let-binding */
let foo = ref 5;
let five = !foo; /* 5 */
foo := 6;

/* Imperative loop */
let startValue = 3;
let endValue = 4;
for myBinding in (startValue) to (endValue) {
  /* use myBinding here */
  print_int myBinding;
};
for myBinding in (startValue) downto (endValue) {
  print_int myBinding;
};
while (true) {
  print_int startValue;
};

/* Object */
type tesla 'a = {
  .. /* open obj */
  drive: int => int
} as 'a;

let obj:
  tesla {. drive: int => int, doYouWant: unit => bool}
  = {
  val hasEnvy = ref false;
  pub drive speed => {
    this#enableEnvy true;
    speed
  };
  pub doYouWant () => !hasEnvy;
  pri enableEnvy envy => {
    hasEnvy := envy
  };
};

/* Module */
module BaseComponent = {
  let defaultGreeting = "Hello";
  let getAudience ::excited => excited ? "world!" : "world";
};

BaseComponent.(
/* open module */
  defaultGreeting
);
/* open BaseComponent; => global open */

module ActualComponent = {
  /* the content is copied over */
  include BaseComponent;
  /* overrides BaseComponent.defaultGreeting */
  let defaultGreeting = "Hey";
  let render () => defaultGreeting ^ " " ^ getAudience excited::true;
};

/* signature - type module */
module type EstablishmentType = {
  type profession;
  let getProfession: profession => string;
};
/* the signature constrained what others can access */

/* Functor */
module type Comparable = {
  type t;
  let equal: t => t => bool;
};

module MakeSet = fun (Item: Comparable) => {
  /* let's use a list as our naive backing data structure */
  type backingType = list Item.t;
  let empty = [];
  let add (currentSet: backingType) (newItem: Item.t) :backingType =>
    /* if item exists */
    if (List.exists (fun x => Item.equal x newItem) currentSet) {
      currentSet /* return the same (immutable) set (a list really) */
    } else {
      [newItem, ...currentSet]; /* prepend to the set and return it */
    }
};
