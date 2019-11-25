#include <iostream> 
#include "Cursor.h" 
using namespace std;
namespace state{
	Cursor::Cursor(int x , int y ){
		name="";
		statistics.getCurrentLife();
		statistics.getDefense();
		statistics.getAttack();
		position.setX(0);
		position.setY(0);
		codetuile=0;
	}
	void Cursor::move (Position& destination){
		position.setX(destination.getX());
		position.setY(destination.getY());
	}
	bool Cursor::isField (){
		return false;
	}
	Cursor::~Cursor(){
	}
}
