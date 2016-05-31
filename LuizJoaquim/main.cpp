
   /**///***************************************************************///
  /**///---------------------------------//----------------------------///
           #include <iostream>          // std::cout                   //
          #include <unistd.h>          // getopt()                    //
         #include "tester.hpp"        // Tester                      //
        #include "tableworker.hpp"   // TableWorker                 //
       #include "automataworker.hpp"// AutomataWorker              //
 /**///----------------------------//----------------------------///
/**///**********************************************************///

void help(){
    std::cout<<"HomeWork1 - INE5415 : Theory of computing"<<std::endl;
    std::cout<<std::endl<<"First set your machine in \"test1AfndAfd.in\" file"<<std::endl;
    std::cout<<std::endl<<"Argument flags:"<<std::endl;
    std::cout<<"\t-h: Show this informations."<<std::endl;
    std::cout<<"\t-t: Test all inputs in \"test.in\" and put all results in \"test.out.\""<<std::endl;
    std::cout<<"\t-o: Disable all output file write."<<std::endl;
    std::cout<<"\t-d: Set deterministic equivalent automaton in \"test1AfndAfd.out\" and make tests for this machine."<<std::endl;
    std::cout<<"\t-m: Minimization on."<<std::endl;
}

bool flagTestInputList = false;
bool flagSetOutputMachine = true;
bool flagDeterminize = false;
bool flagMinimize = false;


void setOpt(int argc, char** argv)
{
    // Shut GetOpt error messages down (return '?'):
    int opt;
    opterr = 0;

    // Retrieve the options:
    while ( (opt = getopt(argc, argv, "todmh")) != -1 ) {  // for each option...
        switch ( opt ) {
            case 'h':
                std::cout<<"Help menu:"<<std::endl;
                help();
                exit(0);
            case 't':
                    flagTestInputList = true;
                break;
            case 'o':
                    flagSetOutputMachine = false;
                break;
            case 'd':
                    flagDeterminize = true;
                break;
            case 'm':
                    flagMinimize = true;
                break;
            case '?':  // unknown option...
                    std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                break;
        }
    }
}

template<typename T>
void info(Automata<T> automaton){

}

auto main(int argc, char** argv) -> int
{
    setOpt(argc, argv);

    TableWorker tb;
    auto automata = tb.getInputMachine();



    if(flagMinimize){
        std::cout<<"Minimization : NOT DONE YET, comming soon!!!"<<std::endl;
    }

    if(flagDeterminize){
        AutomataWorker<char> aw(automata);
        automata =  aw.determinize();
    }

    if(flagTestInputList and flagSetOutputMachine){
        Tester t;
        t.test(automata);
    }

    if(flagSetOutputMachine){
        tb.setOutputMachine(automata);
    }

    return 0;
}
