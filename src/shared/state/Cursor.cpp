#include "state.h"

using namespace state;
using namespace std;

Cursor::Cursor(int x, int y){
    name = "";
    statistics.setPV(0);
    statistics.setAttack(0);
    statistics.setDefense(0);
    statistics.setDodge(0);
    statistics.setCritical(0);
    position.setX(0);
    position.setY(0);
    codeTuile=0;
}

bool Cursor::isField(){
    return false;
}

void Cursor::move(Position& destination){
    position.setX(destination.getX());
    position.setY(destination.getY());
}

Cursor::~Cursor() {}