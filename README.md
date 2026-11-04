## **OUTPUT COMMANDS**

### **Lex program**
 ```
 lex prog_name.l
 gcc lex.yy.c
 ./a.out
 ```

 ### **YACC program**
 ```
 lex prog_name.l
 yacc -d prog_name.y
 gcc lex.yy.c y.tab.c -w
 ./a.out
 ```

 ### **C program**
 ```
 gcc prog_name.c
 ./a.out
 ```