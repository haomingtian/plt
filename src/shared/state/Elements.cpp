#include <iostream> 

#include "Elements.h"

using namespace std;

namespace state {

Elements::Elements (){
	name="";
	position.setX(0);
	position.setY(0);
	statistics.setCurrentLife(0);
	statistics.setAttack(0);
	statistics.setDefense(0);
}
//bool isStatic ();
Position& Elements::getPosition (){
	Position & refPosition = position;
	return refPosition;
}
int Elements::getCodeTuile (){
	return codetuile;
}
void Elements::setCodeTuile (int n_codetuile){
	codetuile=n_codetuile;	
}
std::string Elements::getName (){
	return name;
}

bool Elements::equals (Elements& o){
	bool resultat;
	if(this->position.equals(o.getPosition())==1){
		resultat = true;}
	else{
		resultat = false;
	}
	//return resultat;
}
Statistics& Elements::getStatistics (){
	Statistics & ref_stat = statistics;
	return ref_stat ;
}
bool Elements::isField (){
	return false;
}
}
