//
//  main.cpp
//  remember_cpp
//
//  Created by Viacheslav Matveichev on 2022-08-20.
//

#include <iostream>

#include "test.hpp"

#define OUT_TOP std::cout
#define OUT std::cout << "\t"
#define ENDL std::endl


int main(int argc, const char * argv[]) {
    // insert code here...
    OUT_TOP << "Hello, World!\n";
    
    /* my test: constructors */
    OUT_TOP << "CONSTRUCTORS" << ENDL;
    Test test;
    Test test1(10, 20);
    OUT << test.getPriv() << " " << test.pub << ENDL;
    OUT << test1.getPriv() << " " << test1.pub << ENDL;
    
    /* my test: auto */
    OUT_TOP << "AUTO" << ENDL;
    auto t_auto = 11;
    OUT << t_auto << ENDL;

    /* my test: copy/move semantics */
    OUT_TOP << "COPY/MOVE semantics" << ENDL;
    //test.copy_move(t_auto);
    OUT << t_auto << ENDL;
    test.copy_move(std::move(t_auto));
    OUT << t_auto << ENDL;

    return 0;
}

Test::Test() {
    OUT << "construct at " << this << ENDL;
    this->priv = 1;
    this->pub = 2;
}

Test::~Test() {
    OUT << "destruct at " << this << ENDL;
}

Test::Test(int priv, int pub) : Test () {
    this->priv = priv;
    this->pub = pub;
}
