#include <iostream>
#include "automata.hpp"


auto main()->int
{
    auto a = Automata<bool>("s0");

    //TEST LANGUAGE: (number of zeros)%2 = 0

    a.addState("s1");
    // a.addState("s1");

    a.addTransition(0, "s0", "s1");
    a.addTransition(0, "s1", "s0");
    a.addTransition(1, "s0", "s0");
    a.addTransition(1, "s1", "s1");

    a.set_unset_final("s0");

    return 0;
};
