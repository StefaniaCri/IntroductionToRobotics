const int buttonPin = 2;
byte buttonState = HIGH;
int buttonReading;

const int semaphoreCarRedLed = 8;
const int semaphoreCarYellowLed = 9;
const int semaphoreCarGreenLed = 10;
byte stateCarRedLed = LOW;
byte stateCarYellowLed = LOW;
byte stateCarGreenLed = LOW;

const int semaphorePeopleRedLed = 13;
const int semaphorePeopleGreenLed = 12;
byte statePeopleRedLed = LOW;
byte statePeopleGreenLed = LOW;

const int buzzerPin = 4;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int currentState = 0;
unsigned long timer = 0;
const unsigned long timeState1 = 8000;
const unsigned long timeState2 = 3000;
const unsigned long timeState3 = 8000;
const unsigned long timeState4 = 4000;

bool firstInState3 = true;
bool firstInState4 = true;

byte soundBeat = LOW;
unsigned long buzzingTime = 0;
const int buzzerInterval = 500;
const int buzzerFrequency = 500;
const int fastBuzzerFrequency = 1000;
const int buzzingDuration = 30;

byte blinkState = LOW;
unsigned long previousBlink = 0;
unsigned int blinkInterval = 125;

void changeLedStates(){
  digitalWrite(semaphoreCarRedLed, stateCarRedLed);
  digitalWrite(semaphoreCarYellowLed, stateCarYellowLed);
  digitalWrite(semaphoreCarGreenLed, stateCarGreenLed);

  digitalWrite(semaphorePeopleRedLed, statePeopleRedLed);
  digitalWrite(semaphorePeopleGreenLed, statePeopleGreenLed);
}
// State one
// green for cars
// red for people
// no sound 
void firstState(){
  noTone(buzzerPin);
  statePeopleRedLed = HIGH;
  stateCarGreenLed = HIGH;

  stateCarRedLed = LOW;
  stateCarYellowLed = LOW;
  statePeopleGreenLed = LOW;
  changeLedStates();
  
}
// State two
// yelow for Cars
// red for People
// no sound
void secondState(){
  stateCarYellowLed = HIGH;
  stateCarGreenLed = LOW;
  changeLedStates();
 
}
// state three
// red for Cars
// green for People
// sound playing
void thirdState(){
  if(firstInState3 == true){
    buzzingTime = millis();
    soundBeat = LOW;
    firstInState3 = false;
  }
  stateCarYellowLed = LOW;
  stateCarRedLed = HIGH;
  statePeopleGreenLed = HIGH;
  statePeopleRedLed = LOW;
  changeLedStates();
  
  if(millis() - buzzingTime >= buzzerInterval){
  	buzzingTime = millis();
    soundBeat = !soundBeat;
    if(soundBeat == LOW)
      tone(buzzerPin, buzzerFrequency, buzzingDuration); 
    else 
     noTone(buzzerPin);  
  }
}
// state four
// red for Cars
// blinking green for People
// sound at fastBuzzerFrequency hz 
void fourthState(){
  if(firstInState4 == true)
  {
    previousBlink = millis();
    firstInState4 = false;
  }
  if(millis() - previousBlink >= blinkInterval){
  	previousBlink = millis();
    blinkState = !blinkState;
    tone(buzzerPin, fastBuzzerFrequency * blinkState, buzzingDuration);
  }
  digitalWrite(semaphorePeopleGreenLed, blinkState);   
}

void setup() {
  pinMode(semaphoreCarRedLed, OUTPUT);
  pinMode(semaphoreCarYellowLed, OUTPUT);
  pinMode(semaphoreCarGreenLed, OUTPUT);

  pinMode(semaphorePeopleRedLed, OUTPUT);
  pinMode(semaphorePeopleGreenLed, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), pressedButton, HIGH);
  Serial.begin(9600);
}

// function that triggers when the button is pressed
// the code also checks if the state was change >= debounceDelay seconds ago and currentState is 0
void pressedButton(){
  Serial.println("interupt");
  if(millis() - lastDebounceTime >= debounceDelay)
  {
    	buttonState = buttonReading;
    	if(currentState == 0){
    		timer = millis();
        Serial.println("Buton pushed ");
        Serial.println(timer);
        currentState = 1;
        lastDebounceTime = millis();
       }
    }
  }

void loop() {
 
  buttonReading = digitalRead(buttonPin);

  if(currentState == 1 && millis() - timer > timeState1){
  	currentState = 2;
    Serial.println("Second state");
    timer = millis();
  }
  else if(currentState == 2 && millis()- timer > timeState2){
  	currentState = 3;
   	Serial.println("Third state");
    timer = millis(); 
  }
  else if(currentState == 3 && millis() - timer > timeState3){
  	currentState = 4;
    Serial.println("Forth state");
    timer = millis();
  }
  else if(currentState == 4 && millis() - timer > timeState4){
  	currentState = 0;
    //restart the variables for the next round
    firstInState4 = true;
    firstInState3 = true;
    buttonState = HIGH;
    timer = millis();
    Serial.println("First state");
  }
  
  switch(currentState){
  	case 1:
    	firstState();
    	break;
    case 2:
    	secondState();
    	break;
    case 3:
    	thirdState();
    	break;
    case 4:
    	fourthState();
    	break;
    default:
      firstState();
      break; 
  }
  
}
