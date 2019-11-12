#include <string>
#include <iostream>     
#include "Observable.h"
#include <unistd.h>
namespace engine{
	void const Observable::registerObserver (Observer* o){
		observers.push_back(o);
	}
    void const Observable::notifyUpdating (){
		for(auto observer : observers){
		observer->engineUpdating();
	}
	}
    void const Observable::notifyUpdated (){
		for(auto observer : observers){
		observer->engineUpdated();
	}
	}
}
