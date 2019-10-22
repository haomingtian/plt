#include <iostream> 
#include "Castle.h"
using namespace std;

namespace state {
Castle ::Castle(CastleTypeId id, int n_x, int n_y, int n_codetuile){
	type_id=id;
	if(id==FIRSTLEVEL){
		name="FIRSTLEVEL";		
	}
	else if(id==SECONDLEVEL){
		name="SECONDLEVEL";
	}
	else if(id==THIRDLEVEL){
		name="THIRDLEVEL";
	}
	else if(id==FINALLEVEL){
		name="THIRDLEVEL";
	}
	else if(id==DEMOLISHED){
		name="DEMOLISHED";
	}
	
}
CastleTypeId  Castle::getType (){
	return type_id;
}
void Castle::setNbCastle (int n_nbcastle){
	nb_castle=n_nbcastle;
}	
}
