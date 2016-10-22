/*
 * main.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: swordxh
 */

#include "game.hpp"
#include "battle.hpp"
#include "boss.hpp"

int main(){
    Object spada=Object("spada",30);
    Object piccone=Object("piccone",10);
    Manage g=Manage();
    
    g.setDefaultObject(piccone); //carico oggetto di base
    g.fetchDatabaseObjects(spada);
    g.fetchDatabaseObjects(spada);
    
    g.startGame();
    return 0;
}

    p1.TakeObject(piccone);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone3);
    g.spawnMonsterOrObject(&p1);
    finale boss1(&p1);
    boss1.battleManager();
    /*Queue q=Queue();
    q.enqueue(&p1);
    q.enqueue(&p2);
    q.enqueue(&p3);
    q.dequeue(&p3);
    q.dequeue(&p2);
     */
    /*if (!q.isEmpty()) {
        cout<<"non è vuota";
    }*/

    return 0;
}
