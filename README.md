# HomeWork1 - INE5415 : Theory of computing
##### Automata slave - Finite automata worktable

You can also:
  - Determinize finite automaton
  - Test finite automaton with N input;
  - Minimize automatons (COMING SOON)

### Version
0.9

### Info:

Dependencies:
  - C++ compiler with C++11 support
  - Make
  - We do not guarantee that works with WINDOWS OS
  
Program files:

| File              | Function                          |
| ----------------- | --------------------------------- |
| Teste1AfndAfn.in  | Input machine file                |
| Teste1AfndAfn.out | Determinized output machine file  |
| Teste.in          | List input words to test machine  |
| Teste.out         | Test output                       |
| Config            | Configuration file                |

All input files have a sample, just open and use :)

### Compilation::
```sh
$ make
```
### Help page:
```
 --HomeWork1 - INE5415 : Theory of computing

First set your machine in "test1AfndAfd.in" file

Argument flags:
    -h: Show this informations.
    -t: Test all inputs in "test.in" and put all results in "test.out."
    -o: Disable machine out file write.("test1AfndAfd.out")
    -d: Set deterministic equivalent automaton in "test1AfndAfd.out".
    -m: Minimization on.
```

*obs: if -d and -t has setted together, the test is for determinized machine.

### Todo:

 - Do minimization flag work

License
----

> ----------------------------------------------------------------------------
>
> "A LICENÇA BEER-WARE ou A LICENÇA DA CERVEJA" (Revisão 43 em Português Brasil):
> <luiz.ferreira@khomp.com> e <joaquimbbelo@gmail.com> escreveram este arquivo. Enquanto esta nota estiver na coisa você poderá 
>utilizá-la como quiser. Caso nos encontremos algum dia e você nos reconheça e ache que esta coisa tem algum valor, você poderá nos 
>pagar uma cerveja em retribuição (ou mais de uma), Luiz & Joaquim.
>
> ----------------------------------------------------------------------------



**Free Software, Hell Yeah!**
