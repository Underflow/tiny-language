program: { vardecl | fundecl };

- vardecl: type "id" [ "=" exp ] ";";

- fundecl: proto ";";

type: "int" | "float";
- block: instr | "{" { comp_exp } "}";

- comp_exp: instr;
-   | "if" "(" exp ")" block [ "else" block ];
-   | "while" "(" exp ")" block;

- instr: exp ";" | vardecl | "return" exp;

- exp: affect;
- affect: ["id" "="] logic;
- logic: comp { ("or" | "and") low_exp }
- comp: low_exp { ("<" | "==" | ">" | ">=" | "<=") low_exp }
- low_exp: high_exp { ("+"|"-") high_exp };
- high_exp: pren { ("/" | "*" | "%") paren };
- paren: term | "-" low_exp | "(" low_exp ")";
- term: "id"
-     | "num"
-     | funcall;
- funcall: "id" "(" [ exp { "," exp } ] ")";

- num: float | int | bool;

proto: type "id" "(" {"type" "id" ","} ")";
fundef: proto block;
