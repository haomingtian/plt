#include <iostream> 
#include "Event.h" 
using namespace std;
namespace state{
	Event::Event (EventId e):event_id(e){
	}
	void Event::setEventId (EventId n_id){
		event_id=n_id;
	}
}
