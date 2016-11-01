#ifndef inventario_hpp
#define inventario_hpp

#include "oggetto.hpp"
using namespace std;

class Inventory{
protected:
    Object *oggetto[5]; //l'inventario è composto al massimo da 5 oggetti
public:
    Inventory();
    bool slotIsFull(int slotInventario);
    int AccessObjectFromInventory (int slotInventario);
    void insertObject(Object oggettoDaInserire, int slotInventario);
    void deleteObject(int slotInventario);
    char* getName(int slotInventario);
};




#endif /* inventario_hpp */
