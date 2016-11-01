#ifndef oggetto_hpp
#define oggetto_hpp

#include <stdio.h>
#include <ctime>
#include <stddef.h>
#include <cstdlib>
#include <string.h>
#include <iostream>



using namespace std;

class Object{
protected:
    char name[30];
    int damage;
public:
    Object(char nome[], int danno);
    int Damage();
    char* showNameObject();
};

#endif /* oggetto_hpp */
