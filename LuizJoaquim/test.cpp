#include <iostream>
#include "automata.hpp"


auto main()->int
{
    auto a = Automata<char>("s0");

    // TEST LANGUAGE: (number of zeros)%2 = 0

    a.addState("s1");

    a.addTransition('0', "s0", "s1");
    a.addTransition('0', "s1", "s0");
    a.addTransition('1', "s0", "s0");
    a.addTransition('1', "s1", "s1");

    a.set_unset_initial("s0");

    a.set_unset_final("s0");

    std::queue<char> word = std::queue<char>();

    word.push('0');
    // word.push('1');
    word.push('0');
    // word.push('1');
    // word.push('0');
    // word.push('0');
    // word.push('1');
    // word.push('1');

    std::cout<<a.validateWord(word)<<std::endl;

    return 0;
};
