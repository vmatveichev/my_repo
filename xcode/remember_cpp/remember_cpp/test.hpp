//
//  test.hpp
//  remember_cpp
//
//  Created by Viacheslav Matveichev on 2022-08-20.
//

#ifndef test_h
#define test_h

class Test {
    int priv;
public:
    int pub;
    Test();
    Test(int priv, int pub);
    ~Test();

    int getPriv() {return priv;}
//    void copy_move(int a) {pub = a;}
//    void copy_move(int &a) {pub = a;}
    void copy_move(int &&a) {pub = a;}
};

#endif /* test_h */
