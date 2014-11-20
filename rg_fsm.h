#include <types.h>

//state class
class State{
private:

	//member variables
	bool stateStatus;
	bool handlerIsDefined;
	bool checkRountineIsDefined;
	bool nextStateAssertion;

	state_id currentState;
	state_id nextState;

	void (*handler)(state_id&, state_id&);
	void (*checkRoutine)(bool&);


	//private functions
	void callHandler();
	void callCheckRoutine();
	
public:

	//member variable initialization
	State() : stateStatus(false) , handlerIsDefined(false) , checkRountineIsDefined(false) , nextStateAssertion(false), currentState(NULL_STATE) {}	

	bool getStateAssertion();
	bool getStateStatus();
	void enableState();	
	void disableState();
	state_id getStateId();
	state_id getNextStateId();
	void setStateHandler(void(*callbackFunction)(state_id&, state_id&));
	void setCheckRoutines(void(*callbackFunction)(bool&));
	void executeStateProcess();
};

//overall program class
class Machine{
private:
	State stateInOperation;
	state_id nextStateId;
    state_id currentStateId;

public:
    
    Machine() : currentStateId(NULL_STATE) {}

	void setStateInOperation(State genericState);
    state_id getCurrentStateId();
	state_id getNextStateId();
	void driveMafakaas();

};

class Timer{
    private:
    
};
