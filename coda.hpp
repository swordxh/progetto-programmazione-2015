#ifndef coda_hpp
#define coda_hpp

#include "player.hpp"
#include <stdio.h>
using namespace std;

struct Node{
    Player player;
    struct Node* next;
};

class Queue{
protected:
    Node* q; //puntatore al primo nodo della lista
public:
    Queue();
    void enqueue (Player giocatore);
    void dequeue(int idPlayer);
    bool isEmpty();
    Node* Head();
};


#endif /* coda_hpp */
