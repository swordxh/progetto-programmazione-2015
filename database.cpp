#include "database.hpp"

databaseObject::databaseObject(){
    int i=0;
    for(i=0;i<6;i++){
        oggetto[i]=NULL;
    }
}

Object* databaseObject::slotDatabase(int slot){
    if (oggetto[slot]==NULL) {
        return NULL;
    }
    else return oggetto[slot];
}

void databaseObject::addObjectToDatabase(int slot, Object oggettoDelGioco){
    if (oggetto[slot]==NULL) {
        oggetto[slot]=new Object(oggettoDelGioco.showNameObject(),oggettoDelGioco.Damage());
    }
    else{
        delete oggetto[slot];
        oggetto[slot]=new Object(oggettoDelGioco.showNameObject(),oggettoDelGioco.Damage());
    }
}

bool databaseObject::databaseEmpty(){
    int i=0;
    bool flag=false;
    
    while(i<5 && flag==0) {
        i++;
        if (this->slotDatabase(i)!=NULL){
            flag=true;
        }
    }
    
    if (flag) {
        return false;
    }
    else return true;
}

