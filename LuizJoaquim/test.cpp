#include <iostream>
#include "automata.hpp"


auto main()->int
{
    auto a = Automata<char>("ini");

    // L1: (number of zeros)%2 = 0
    // L2: (number of ones)%2 = 0

    a.addState("s1");
    a.addState("s0");
    a.addState("s2");
    a.addState("s3");

    a.addEpsilonTransition("ini","s0"); // l1 or l2
    a.addEpsilonTransition("ini","s2"); // l1 or l2

    a.addTransition('0', "s0", "s1");
    a.addTransition('0', "s1", "s0");
    a.addTransition('1', "s0", "s0"); //L1
    a.addTransition('1', "s1", "s1");

    a.addTransition('1', "s2", "s3");
    a.addTransition('1', "s3", "s2");
    a.addTransition('0', "s2", "s2"); //L2
    a.addTransition('0', "s3", "s3");

    a.toggle_final("s0");
    a.toggle_final("s2");

    std::queue<char> word = std::queue<char>();

    word.push('0');
    word.push('1');
    word.push('0');
    word.push('0');
    word.push('1');
    word.push('1');
    word.push('0');
    word.push('1');
    word.push('0');
    word.push('1');
    word.push('0');
    word.push('0');
    word.push('1');
    word.push('1');

    std::cout<<(a.validateWord(word) ? "V" : "Inv")<<"alid!"<<std::endl;

    return 0;
};
