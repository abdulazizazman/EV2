#include <rg_fsm.h>
#include <SimpleTimer.h>
#include <Firmata.h>

//------------------------------------
byte portStatus[TOTAL_PORTS];	// each bit: 1=pin is digital input, 0=other/ignore
byte previousPINs[TOTAL_PORTS];

void sendPort(byte portNumber, byte portValue)
{
  portValue = portValue & portStatus[portNumber];
  if (previousPINs[portNumber] != portValue) {
    Firmata.sendDigitalPort(portNumber, portValue);
    previousPINs[portNumber] = portValue;
  }
}

//---------------------------------

//types.h removed as already included in rg_fsm.h

#define PWM_FREQUENCY               2
#define MAX_DUTY_CYCLE              1000
#define BIT_CONVERSION_CONSTANT (3.3/1024)
 
//ADC CHANNELS
float CHANNEL_0_REG = 0; 
float CHANNEL_1_REG = 0;
float CHANNEL_2_REG = 0;
float CHANNEL_3_REG = 0;
float CHANNEL_4_REG = 0;
float CHANNEL_5_REG = 0;
float CHANNEL_6_REG = 0;
float CHANNEL_7_REG = 0;
float CHANNEL_8_REG = 0;
float CHANNEL_9_REG = 0;

//STATE DECLARATION
State startUpState;
State driveState;
State shutDownState;
State idleState;


//FSM DECLARATION
Machine car;

//ARDUINO OUTPUT
int led1 = 13;
int led2 = 12;

int dig7 = 7;
int dig2 = 2;
int dig3 = 3;

byte pin;

//timer objec
SimpleTimer printVals;
SimpleTimer readVals;

void analogWriteCallback(byte pin, int value)
{
  if (IS_PIN_PWM(pin)) {
    pinMode(PIN_TO_DIGITAL(pin), OUTPUT);
    analogWrite(PIN_TO_PWM(pin), value);
  }
}

void setup() 
{
  
  byte i, port, status;
  
  
  // put your setup code here, to run once:
  Firmata.setFirmwareVersion(0, 1);
  
   for (pin = 0; pin < TOTAL_PINS; pin++) {
    if IS_PIN_DIGITAL(pin) pinMode(PIN_TO_DIGITAL(pin), INPUT);
  }

  for (port = 0; port < TOTAL_PORTS; port++) {
    status = 0;
    for (i = 0; i < 8; i++) {
      if (IS_PIN_DIGITAL(port * 8 + i)) status |= (1 << i);
    }
    portStatus[port] = status;
  }

  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  
  Firmata.begin(57600);
  
  //assigning handler and check routine functions
  startUpState.setCheckRoutines(startUpStateCheckRoutine);
  startUpState.setStateHandler(startUpStateHandler);

  driveState.setCheckRoutines(driveStateCheckRoutine);
  driveState.setStateHandler(driveStateHandler);

  shutDownState.setCheckRoutines(shutDownStateCheckRoutine);
  shutDownState.setStateHandler(shutDownStateHandler);
  
  idleState.setCheckRoutines(idleStateCheckRoutine);
  idleState.setStateHandler(idleStateHandler);
  
  //arduino output setup
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  //timer output
  //printVals.setInterval(1000,printValsHandler);
  readVals.setInterval(100,readValsHandler);
  
  //default initial state is idel state
  car.setStateInOperation(idleState);
  
}

byte analogPin = 0;
byte digitalPin = 0;

void loop() 
{
  
  //printADC(); 
  car.driveMafakaas();
  //printVals.run();
  readVals.run();
  
  while (Firmata.available()) {
    Firmata.processInput();
  }
  
  
  
  // do one analogRead per loop, so if PC is sending a lot of
  // analog write messages, we will only delay 1 analogRead
  byte digitalPin;

  for (digitalPin = 0; digitalPin < TOTAL_PORTS; digitalPin++) {
    sendPort(digitalPin, readPort(digitalPin, 0xff));
  }
  
  
  Firmata.sendAnalog(analogPin, CHANNEL_7_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_6_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_5_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_4_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_3_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_2_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_1_REG);
  analogPin = analogPin + 1;
  Firmata.sendAnalog(analogPin, CHANNEL_0_REG);
  analogPin = 0;
  

  if(car.getNextStateId() == STARTUP_STATE)
    car.setStateInOperation(startUpState);
  if(car.getNextStateId() == DRIVE_STATE)
    car.setStateInOperation(driveState);
  if(car.getNextStateId() == SHUT_DOWN_STATE)
    car.setStateInOperation(shutDownState);
  if(car.getNextStateId() == IDLE_STATE)
    car.setStateInOperation(idleState);
    
  //printCurrentState(car);
}


void readValsHandler(){
  analogReadResolution(10);
  CHANNEL_0_REG = analogRead(7);
  CHANNEL_1_REG = analogRead(6);
  CHANNEL_2_REG = analogRead(5);
  CHANNEL_3_REG = analogRead(4);
  CHANNEL_4_REG = analogRead(3);
  CHANNEL_5_REG = analogRead(2);
  CHANNEL_6_REG = analogRead(1);
  CHANNEL_7_REG = analogRead(0);
}
  
//state handlers, state handlers contain current state and next state id

void startUpStateHandler(state_id &currentState, state_id &nextState){
  
  currentState = STARTUP_STATE;
  nextState = DRIVE_STATE;
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  
  //Serial.print("start up state handler\n");
  
}

void driveStateHandler(state_id &currentState, state_id &nextState){

  currentState = DRIVE_STATE;
  nextState = SHUT_DOWN_STATE;

  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);

  //Serial.print("drive state handler\n");
}
void shutDownStateHandler(state_id &currentState, state_id &nextState){

  currentState = SHUT_DOWN_STATE;
  nextState = IDLE_STATE;

  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);

  //Serial.print("shut down state handler\n"); 
}

void idleStateHandler(state_id &currentState, state_id &nextState){

  currentState = IDLE_STATE;
  nextState = STARTUP_STATE;
        
  digitalWrite(led2,LOW);
  digitalWrite(led1,LOW);
  //Serial.print("state handler functoin\n");

}

//state check routines
void startUpStateCheckRoutine(bool &nextStateAssert){
  
  //Serial.print("Start up state check routine\n");
  
  if(CHANNEL_0_REG*BIT_CONVERSION_CONSTANT < 2.2)
    nextStateAssert = true;
  else
    nextStateAssert = false;
  
}
void driveStateCheckRoutine(bool &nextStateAssert){
  
  //Serial.print("drive state check routine\n");

  if(CHANNEL_1_REG*BIT_CONVERSION_CONSTANT < 2.2)
    nextStateAssert = true;
  else
    nextStateAssert = false;
		
}
void shutDownStateCheckRoutine(bool &nextStateAssert){

  //Serial.print("shut down state check routine\n"); 
	
  if(CHANNEL_2_REG*BIT_CONVERSION_CONSTANT < 2.2)
    nextStateAssert = true;
  else
    nextStateAssert = false;
			
}

void idleStateCheckRoutine(bool &nextStateAssert){
  
  //Serial.print("idle state check routine\n");

  if(CHANNEL_3_REG*BIT_CONVERSION_CONSTANT < 2.2)
    nextStateAssert = true;
  else
    nextStateAssert = false;
	
}
