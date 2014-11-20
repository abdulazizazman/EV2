#include "rg_fsm.h" 

//private functions
void State::callHandler(){
	handlerIsDefined = true;
}
void State::callCheckRoutine(){
	checkRountineIsDefined = true;
}
	
bool State::getStateAssertion(){
	return nextStateAssertion;
}

bool State::getStateStatus(){
	return stateStatus;
}

void State::enableState(){
	stateStatus = true;
}

void State::disableState(){
	stateStatus = false;
}

state_id State::getStateId(){ //state id can only be set in state handler, you can think of a state to be defined by its handler, this creates robhustnest as opposed to creating a setter method to access a generic state_id member variable
    return currentState;
}

state_id State::getNextStateId(){
	return nextState;
}

void State::setStateHandler(void(*callbackFunction)(state_id&, state_id&)){
	handler = callbackFunction;
	callHandler();
}

void State::setCheckRoutines(void(*callbackFunction)(bool&)){
	checkRoutine = callbackFunction;
	callCheckRoutine();
}

void State::executeStateProcess(){ //state process will execute handler and check routine of the state
	if(stateStatus){
		if(handlerIsDefined && checkRountineIsDefined){
            handler(currentState, nextState);
            checkRoutine(nextStateAssertion);
        }
    }
}
	
	
//overall program class

void Machine::setStateInOperation(State genericState){
    stateInOperation = genericState;
    stateInOperation.enableState();
}

state_id Machine::getCurrentStateId(){
        return currentStateId;
    }

state_id Machine::getNextStateId(){
		return nextStateId;
	}

void Machine::driveMafakaas(){
	if(stateInOperation.getStateStatus()){
		stateInOperation.executeStateProcess();
		if(stateInOperation.getStateAssertion()){
            stateInOperation.disableState();
            currentStateId = stateInOperation.getStateId();
            nextStateId = stateInOperation.getNextStateId();           
        }
    }
}







