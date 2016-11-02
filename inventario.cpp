#include "inventario.hpp"

Inventory::Inventory(){ //inventario ha 5 oggetti 
    int i=0;
    for (i=0;i<5;i++){
        oggetto[i]=NULL;
    }
}

bool Inventory::slotIsFull(int slotInventario){ //controlla se uno specifico slot dell'inventario è pieno
    if (oggetto[slotInventario]!=NULL) {
        return 1;
    }
    else return 0;
}

int Inventory::AccessObjectFromInventory (int slotInventario){
    return oggetto[slotInventario]->Damage();
}
void Inventory::insertObject(Object oggettoDaInserire, int slotInventario){
    oggetto[slotInventario]=new Object(oggettoDaInserire.showNameObject(),oggettoDaInserire.Damage());
    *oggetto[slotInventario]=oggettoDaInserire;
}

void Inventory::deleteObject(int slotInventario){
    Object* app=oggetto[slotInventario];
    delete app;
    oggetto[slotInventario]=NULL;
}
char* Inventory::getName(int slotInventario){
    return oggetto[slotInventario]->showNameObject();
}




