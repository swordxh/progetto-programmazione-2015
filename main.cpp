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
    Inventory a;
    Player p1(1);
    Player p2(2);
    Player p3(3);
    char bach[16];
    strcpy(bach, "bacchetta");
    char ex[16];
    strcpy(ex, "excalibur");
    char poi[16];
    strcpy(poi, "potion");
    Object piccone(bach,10);
    Object piccone2(ex,1);
    Object piccone3(poi,0);

    Manage g=Manage();

    //g.builtQueue();
    g.fetchDatabaseObjects(&piccone3);
    g.fetchDatabaseObjects(&piccone2);
    g.fetchDatabaseObjects(&piccone);
    /*g.fetchDatabaseObjects(&piccone);
    g.fetchDatabaseObjects(&piccone);
    g.fetchDatabaseObjects(&piccone);
    g.fetchDatabaseObjects(&piccone);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);
    p1.TakeObject(piccone2);

    g.spawnMonsterOrObject(&p1);

*/

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
