# Language Specification


## 1. Overview

FAL is a language for modelling and executing finite automata. The specification below is written in extended [*Backus-Naur form*](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form).


# 2. Specification

```
PROGRAM          ::= STATE-DECL, { STATE-DECL | TRANSITION-DECL } ;
STATE-DECL       ::= STATE, [ STATE-QUALS ], STRING ;
STATE-QUALS      ::= INITIAL | ACCEPTING | INITIAL, ACCEPTING | ACCEPTING, INITIAL ;
TRANSITION-DECL  ::= TRANSITION, STRING, RIGHT-ARROW, ( CHARACTER | EPSILON ), RIGHT-ARROW, STRING ;
STATE            ::= "state" ;
INITIAL          ::= "initial" ;
ACCEPTING        ::= "accepting" ;
TRANSITION       ::= "transition" ;
STRING           ::= '"', CHARACTER+, '"' ;
CHARACTER        ::= ? any ascii character excluding whitespace ? ;
RIGHT-ARROW      ::= "->" ;
EPSILON          ::= "epsilon" ;
```
