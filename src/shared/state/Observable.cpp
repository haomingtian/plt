#include <iostream> 
#include "Observable.h"
using namespace std;
namespace state {
void Observable::registerObserver (Observer* o){
    observers.push_back(o);
}

void Observable::notifyObservers (const StateEvent& e, State& state, sf::RenderWindow& window){
	for(auto o : observers){
		o->stateChanged(e, state, window);
	}
}
}
