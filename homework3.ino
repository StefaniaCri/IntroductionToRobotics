const int pinSW = 2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
const unsigned long debounceDelayTillRestart = 3000;
byte swState = HIGH;
bool switchState;
int currentState = 1;
int restart = 1;
// if restart == 1 means that can restart
// if restart == 2 meand the restart will be made
// if restart == 3 meand the restart has been performed

const int segSize = 8;
bool commonAnode = false;
const int minThreshold = 400;
const int maxThreshold = 600;
bool movedJoystick;

int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
byte segmentsState[segSize] = {
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

int xValue, yValue;
const int noWhere = -1;
const int ledNeighbours[segSize][4]{ 
    // up         // down         // left         // right 
  { noWhere,      pinG - pinA,  	pinF - pinA,    pinB - pinA   },
  { pinA - pinA,  pinG - pinA,    pinF - pinA,    noWhere       },
  { pinG - pinA,  pinD - pinA,    pinE - pinA,    pinDP - pinA  },
  { pinG - pinA,  noWhere,        pinE - pinA,    pinC - pinA   },
  { pinG - pinA,  pinD - pinA,    noWhere,        pinC - pinA   },
  { pinA - pinA,  pinG - pinA,    noWhere,        pinB - pinA   },
  { pinA - pinA,  pinD - pinA,    noWhere,        noWhere       },
  { noWhere,      noWhere,        pinC - pinA,    noWhere       }
};

int currentPosition = pinDP - pinA;

const unsigned long blinkInterval = 250;
unsigned long blinkTime = 0;
byte blinkState = LOW;

void setup() {
  
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  if(commonAnode == true)
  {
    for(int i = 0; i <= segSize; i++)
    {
      segmentsState[i] = HIGH;
    }
  }

  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pinSW), pressedSW, CHANGE);
  //togle when the SW button change state and verify time at that moment
}

void loop() {
  changeStates();
  xValue = analogRead(A0);
  yValue = analogRead(A1);
  updateSegments();
   if(currentState == 1 && restart == 2)
  {
    restartSegments();
    switchState = false;
  }

  if(currentState == 1 && switchState == true)
  {
    currentState = 2;
    switchState = false;
  }
 
  if(currentState == 2 && switchState == true)
  {
    currentState = 1;
    switchState = false;
  }

  switch (currentState) {
  case 1:
    state1();
    break;
  case 2:
    state2();
    break;  
  }
}

void state1()
{
  if(!movedJoystick){
    if(xValue > maxThreshold){                     // when moved up 
      currentPosition = (ledNeighbours[currentPosition][0] != noWhere) ? ledNeighbours[currentPosition][0] : currentPosition;
    }  
  
    if(xValue < minThreshold){                   // when moved down
      currentPosition = (ledNeighbours[currentPosition][1] != noWhere) ? ledNeighbours[currentPosition][1] : currentPosition;
    }  
    
    if(yValue > maxThreshold){                    // when moved right
      currentPosition = (ledNeighbours[currentPosition][3] != noWhere) ?ledNeighbours[currentPosition][3] : currentPosition;
    }  
   
    if(yValue < minThreshold){                  // when moved left
      currentPosition = (ledNeighbours[currentPosition][2] != noWhere) ?ledNeighbours[currentPosition][2] : currentPosition;
    }
    movedJoystick = true;  
  }

  //if the joystick wasn't moved
  if (xValue >= minThreshold && xValue <= maxThreshold && yValue >= minThreshold && yValue <= maxThreshold) {
    movedJoystick = false;
  }

  blinkLed(currentPosition + pinA); 
}

void state2()
{
  if(!movedJoystick)
  {
    if(yValue > maxThreshold){                    // when moved right
      segmentsState[currentPosition] = LOW;
    }  
   
    else if(yValue < minThreshold){                  // when moved left
      segmentsState[currentPosition] = HIGH;
    }
    movedJoystick = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
    movedJoystick = false;
  } 
}

void pressedSW()
{
  lastDebounceTime = millis();
}

void changeStates()
{
  byte currentStateSW = digitalRead(pinSW);
  //read the state of SW button atm to check for difference
  if(millis() - lastDebounceTime >= debounceDelay)
  { 
    if(swState != currentStateSW)
    {
      swState = currentStateSW;
      if(swState == HIGH){
        // check if we restart in a previous state 
        if(restart == 3){
          restart = 1;
        }
        else{
        switchState = true; 
        }
      }  
    } else if (currentState == 1 && currentStateSW == LOW && restart == 1 && millis() - lastDebounceTime >= debounceDelayTillRestart ) {
        restart = 2;
    }

  }
}

void blinkLed(int pin)
{
  digitalWrite(pin, blinkState);
  
  if(millis() - blinkTime > blinkInterval)
  {
    blinkTime = millis();
    blinkState = !blinkState;
  }
  
}

// write the chenges from 7 segments display;
void updateSegments()
{
  for (int i = 0; i < segSize; i++)
  {
    digitalWrite(segments[i], segmentsState[i]);
  }
}

//reset function and go back to dp pin
void restartSegments()
{
  for (int i = 0; i < segSize; i++)
  {
    segmentsState[i] = LOW;
  }
  currentPosition = pinDP - pinA;
  restart = 3;
}