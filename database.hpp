#ifndef database_hpp

#include <stdio.h>
#define database_hpp
#include "oggetto.hpp"
using namespace std;

class databaseObject{
protected:
    Object* oggetto[6];
public:
    databaseObject();
    Object* slotDatabase(int slot);
    void addObjectToDatabase(int slot, Object oggetto);
    bool databaseEmpty();
};


#endif /* database_hpp */
