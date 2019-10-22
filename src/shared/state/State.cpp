#include <iostream> 
#include "State.h"
 
using namespace std;
namespace state {
int State::getRound (){
	return num_round;
}
bool State::isFin (){
	return fin;
}
std::vector<std::vector<std::unique_ptr<Field>>>& State::getGrid (){
}
}
