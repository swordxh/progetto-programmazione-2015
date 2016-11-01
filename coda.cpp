#include "coda.hpp"


Queue::Queue(){
    q=NULL;
}

void Queue::enqueue (Player giocatore){
    if (q==NULL) {
        q=new Node;
        q->player=giocatore;
        q->next=q;
    }
    else{
        Node* app=q;
        while (app->next!=q) {
            app=app->next;
        }
        Node* nodo=new Node;
        nodo->player=giocatore;
        nodo->next=q;
        app->next=nodo;
        nodo=NULL;
    }
}

void Queue::dequeue(int idPlayer){
    if (q!=NULL) {
        if ((q->player).showId()==idPlayer && q->next==q){ //caso in cui c'è solo primo elemento
            Node* app=q;
            q=NULL;
            delete app;
            app=NULL;
        }
        else{
            if ((q->player).showId()==idPlayer) { //caso in cui elimino elemento in testa in una lista di elementi
                Node* track=q; //faccio puntare ultimo elemento al nuovo primo elemento visto che sto eliminando testa
                while (track->next!=q) {
                    track=track->next;
                }
                
                track->next=q->next;
                track=NULL;
                
                Node* app; //elimino elemento di testa
                app=q;
                q=q->next;
                delete app;
                app=NULL;
                
            }
            else{ //caso generale eliminazione nodo
                Node* p=q;
                
                while ((p->next->player).showId()!=idPlayer && p->next->next!=q) {//inizio a controllare dall'elemento dopo la testa visto che quest'ultima è già stata controllata nei casi prima. Caso in cui ho due elementi: non entro nel while
                    p=p->next;
                }
                if ((p->next->player).showId()==idPlayer) { //devo controllare che non sia finito nel caso in cui non c'è elemento cercato e abbia solo due nodi
                    Node* app=new Node;
                    app=p->next;
                    p->next=p->next->next;
                    delete app;
                    app=NULL;
                }
            }
            
        }
    }
}

Node* Queue::Head(){
    return q;
}

bool Queue::isEmpty(){
    if (q!=NULL) {
        return false;
    }
    return true;
}
