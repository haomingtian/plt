#include "state.h"

using namespace state;

StateEvent::StateEvent (StateEventId se):eventId(se){

}

void StateEvent::setEventId(StateEventId newID){
    eventId=newID;
}
