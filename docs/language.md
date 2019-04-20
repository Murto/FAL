# Language Specification


## 1. Overview

FAL is a language for modelling and executing finite automata. The specification below is written in extended [*Backus-Naur form*](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form).


# 2. Specification

```
PROGRAM           ::= STATE-DECL, {STATE-DECL | TRANSITION-DECL}* ;
STATE-DECLARATION ::= "state", [ STATE-QUALIFIERS ], STRING ;
STATE-QUALIFIERS  ::= "initial" | "accepting" | "initial accepting" | "accepting initial" ;
TRANSITION-DECL   ::= "transition", STRING, RIGHT-ARROW, ( CHARACTER | EPSILON ), RIGHT-ARROW, STRING ;
STRING            ::= '"', CHARACTER+, '"' ;
CHARACTER         ::= ? any ascii character excluding whitespace ? ;
RIGHT-ARROW       ::= "->" ;
EPSILON           ::= "epsilon" ;
```
