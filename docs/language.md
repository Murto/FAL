# Language Specification


## 1. Overview

FAL is a language for modelling and executing finite automata. The specification below is written in extended *Backus-Naur form*.


# 2. Specification

```
PROGRAM           ::= STATE-DECL, {STATE-DECL | TRANSITION-DECL}* ;
STATE-DECLARATION ::= [ STATE-QUALIFIERS ] "state" NAME ;
STATE-QUALIFIERS  ::= "initial" | "accepting" | "initial accepting" | "accepting initial"
TRANSITION-DECL   ::= "transition" NAME RIGHT-ARROW ( CHARACTER | EPSILON ) RIGHT-ARROW NAME
STRING            ::= '"' CHARACTER+ '"'
CHARACTER         ::= ? any ascii character excluding whitespace ?
RIGHT-ARROW       ::= "->"
EPSILON           ::= "epsilon"
```
