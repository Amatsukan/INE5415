
   /**///***************************************************************///
  /**///---------------------------------//----------------------------///
           #include <iostream>          // std::cout                   //
          #include <unistd.h>          // getopt()                    //
         #include "tester.hpp"        // Tester                      //
        #include "tableworker.hpp"   // TableWorker                 //
       #include "automataworker.hpp"// AutomataWorker              //
 /**///----------------------------//----------------------------///
/**///**********************************************************///
namespace std{
    string tab = "\t";
};

void help(){
    std::cout<<"HomeWork1 - INE5415 : Theory of computing"<<std::endl;
    std::cout<<std::endl<<"First set your machine in \"test1AfndAfd.in\" file"<<std::endl;
    std::cout<<std::endl<<"Argument flags:"<<std::endl;
    std::cout<<std::tab<<"-h: Show this informations."<<std::endl;
    std::cout<<std::tab<<"-t: Test all inputs in \"test.in\" and put all results in \"test.out.\""<<std::endl;
    std::cout<<std::tab<<"-o: Disable machine out file write.(\"test1AfndAfd.out\")"<<std::endl;
    std::cout<<std::tab<<"-d: Set deterministic equivalent automaton in \"test1AfndAfd.out\" and make tests for this machine."<<std::endl;
    std::cout<<std::tab<<"-m: Minimization on."<<std::endl;
 }

bool flagTestInputList = false;
bool flagSetOutputMachine = true;
bool flagDeterminize = false;
bool flagMinimize = false;

//mão faça isso em casa '-'
//faço mas não aconselho kkkkkkkkk

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
            default:  // unknown option...
                    std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                break;
        }
    }
};

template<typename T>
void info(Automata<T> automaton){

    std::cout<<"Machine info:"<<std::endl;
    std::cout<<std::tab<<"States : "<<automaton.getStates_str()<<std::endl;
    std::cout<<std::tab<<"Alphabeth : "<<automaton.getAlphabet()<<std::endl;
    std::cout<<std::tab<<"Initial state : "<<automaton.getInitial_str()<<std::endl;
    std::cout<<std::tab<<"Final states : "<<automaton.getFinals_str()<<std::endl;
    std::cout<<std::endl<<std::endl;
}

auto main(int argc, char** argv) -> int
{
    setOpt(argc, argv);

    TableWorker tb;
    auto automata = tb.getInputMachine();

    std::cout<<"Input machine info:"<<std::endl;

    info(automata);

    if(flagMinimize){
        std::cout<<"Minimization : NOT DONE YET, comming soon!!!"<<std::endl;
    }

    if(flagDeterminize){
        AutomataWorker<char> aw(automata);
        automata =  aw.determinize();
        std::cout<<"Deterministic machine info:"<<std::endl;
        info(automata);
    }

    if(flagTestInputList){
        Tester t;
        t.test(automata);
    }

    if(flagSetOutputMachine){
        std::cout<<"Write machine in \"test1AfndAfd.out\" file..."<<std::endl;
        tb.setOutputMachine(automata);
    }

    return 0;
}
