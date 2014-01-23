# Compilers

Assignment 1 
------------------------ 
Thing you need to run this software :

1) nasm

2) Ubuntu 10.04 and above 

Aim
------------------------ 

To write a compiler for a given grammar which parses any program in the specified grammer and converts it to relevent x86 assembly code.

Grammer
------------------------


**stmt → ` id := expr | if expr_prime then stmt | while expr_prime do stmt | begin opt_stmts end `**

**opt_stmts  → ` stmt_list |є`**

**stmt_list  → `stmt_list ; stmt | stmt `**

**expr_prime → `expr relation expr`**

**expr  → `term expression | + term expression' |  - term expression' |  epsilon`**

**term  → `term expression | + term expression' |  - term expression' |  epsilon`**

**factor  → `term expression | + term expression' |  - term expression' |  epsilon`**

**relation → `> | < | <= | >= | = `**

**id  → `id [a-zA-Z] | id [0-9]`**
