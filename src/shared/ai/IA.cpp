#include <string>
#include <iostream> 
#include "IA.h"
using namespace std;
using namespace engine;
namespace ai { 
	bool IA::getCamp (){
		return camp;
	}
	void IA::setCamp (bool newCamp){
		camp=newCamp;
	}
}
