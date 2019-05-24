#ifndef __KOLEJKA_HPP
#define __KOLEJKA_HPP

#include <iostream>
#include <iomanip>
#include "debug.hpp"
using namespace std;


class KolejkaP{
private:
    node *top;
    bool high_priority;
public:
    KolejkaP(bool priority);
    void push(zadanie item);
    zadanie pop();
    zadanie peek();
    void display(ostream &out);
    bool isEmpty();

};





#endif // __KOLEJKA_HPP


