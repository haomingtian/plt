#include <iostream>
#include "NonPraticable.h"
 
using namespace std;
namespace state {

NonPraticable::NonPraticable (TypeNonPraticableId id, int x, int y, int codetuile):Field (x, y, codetuile){
	type_id=id;
	if(id==TREE){
		name="TREE";
	}
	else if(id==WATER){
		name="WATER";
	}
	else if(id==WALL){
		name="WALL";
	}
	else if(id==HOLE){
	    name="HOLE";
	}
}
bool NonPraticable::isPraticable (){
	return false;
}

TypeNonPraticableId NonPraticable::getTypeId(){
	return type_id;
}

bool NonPraticable::equals(state::Elements &other) {
    bool resultat;
    if(other.isField()){
        Field& other_terrain = static_cast<Field&>(other);
        if(!other_terrain.isPraticable()){
            NonPraticable& other_terrain_non_praticable=static_cast<NonPraticable&>(other_terrain);
            if(	this->Elements::equals(other_terrain_non_praticable) &&
                   type_id==other_terrain_non_praticable.getTypeId()){
                resultat=true;
            }
            else{resultat=false;}
        }
        else{ resultat=false;}
    }
    else{resultat=false;}

    return resultat;
}
}
