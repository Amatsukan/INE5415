#include <iostream>
#include "tableworker.hpp"


auto test(Automata<char> a, int nOf0, int nOf1) -> void 
{
    std::queue<char> word = std::queue<char>();

    std::cout<<"Test for "<<nOf0<<" zeros and "<<nOf1<<" ones is:"<<std::endl;

    while(nOf0-->0){
        word.push('0');
    }
    while(nOf1-->0){
        word.push('1');
    }

    std::cout<<(a.validateWord(word) ? " V" : " Inv")<<"alid!"<<std::endl;
}


auto main()->int
{
    TableWorker tb;
    //auto a = tb.getInputMachine();

    auto a = Automata<char>(std::vector<char>({'0', '1'}));

    a.addState("s1");
    a.addState("s0");
    a.addState("s2");
    a.addState("s3");
    a.addState("s4");


    // a.addEpsilonTransition("s0","s1"); // l1 or l2
    // a.addEpsilonTransition("s0","s3"); // l1 or l2
    a.addTransition('1', "s0", "s1");
    a.addTransition('1', "s1", "s1");
    a.addTransition('1', "s2", "s2");
    a.addTransition('0', "s1", "s2"); //L1
    a.addTransition('0', "s2", "s1");

    a.addTransition('0', "s0", "s3");
    a.addTransition('0', "s3", "s3");
    a.addTransition('0', "s4", "s4");
    a.addTransition('1', "s3", "s4"); //L2
    a.addTransition('1', "s4", "s3");

    a.toggle_final("s1");
    a.toggle_final("s3");
    a.toggle_initial("s0");

    std::cout<<"States : "<<a.getStates_str()<<std::endl;

    std::cout<<"Alphabeth : "<<a.getAlphabet()<<std::endl;

    std::cout<<"Initial state : "<<a.getInitial_str()<<std::endl;

    std::cout<<"Final states : "<<a.getFinals_str()<<std::endl;

    for (int ones = 0; ones <= 4; ++ones)
    {
        for (int zeros = 0; zeros <= 4; ++zeros)
        {
            test(a, ones, zeros);
        }
    }
    
    tb.setOutputMachine(a);
    return 0;
};


// auto main()->int
// {
//     auto a = Automata<char>("ini");

//     // L1: (number of zeros)%2 = 0
//     // L2: (number of ones)%2 = 0

//     a.addState("s1");
//     a.addState("s0");
//     a.addState("s2");
//     a.addState("s3");

//     a.addEpsilonTransition("ini","s0"); // l1 or l2
//     a.addEpsilonTransition("ini","s2"); // l1 or l2

//     a.addTransition('0', "s0", "s1");
//     a.addTransition('0', "s1", "s0");
//     a.addTransition('1', "s0", "s0"); //L1
//     a.addTransition('1', "s1", "s1");

//     a.addTransition('1', "s2", "s3");
//     a.addTransition('1', "s3", "s2");
//     a.addTransition('0', "s2", "s2"); //L2
//     a.addTransition('0', "s3", "s3");

//     a.toggle_final("s0");
//     a.toggle_final("s2");

//     std::queue<char> word = std::queue<char>();

//     word.push('0');
//     word.push('1');
//     word.push('0');
//     word.push('0');
//     word.push('1');
//     word.push('1');
//     word.push('0');
//     word.push('1');
//     word.push('0');
//     word.push('1');
//     word.push('0');
//     word.push('0');
//     word.push('1');
//     word.push('1');

//     std::cout<<(a.validateWord(word) ? "V" : "Inv")<<"alid!"<<std::endl;

//     return 0;
// };
