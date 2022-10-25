const int numberOfPinsUsedInput = 3;
const int numberOfPinsUsedOutput = 3;

const int ledPins[numberOfPinsUsedOutput] = {11, 10, 9};

// array of signal pins 
const int analogInputPins[numberOfPinsUsedInput] = {A0, A1, A2};

const int minAnalogValue = 0, maxAnalogValue = 1023, minVoltageValue = 0, maxVoltageValue = 128; 

// initialize pins from an array
void setPinModeArray(int arrayOfPins[], int arrayLength, int modeOfPin){
  for(int i = 0; i < arrayLength; i++){
    pinMode(arrayOfPins[i], modeOfPin);
  }
}

void turnOnLed(int analogInputPin, int ledPin){
  // read the analog input value
  int analogValue = analogRead(analogInputPin);
  // adjust the led brightness like the value of analog input
  int ledBrightness = map(analogValue, minAnalogValue, maxAnalogValue, minVoltageValue, maxVoltageValue);
  // write the analog output value to ledPin
  analogWrite(ledPin, ledBrightness);
}

void setup() {
  setPinModeArray(analogInputPins, numberOfPinsUsedInput, INPUT); 
  
  setPinModeArray(ledPins, numberOfPinsUsedOutput, OUTPUT); 
}

void loop() {
  for (int i = 0; i < numberOfPinsUsedInput; i++){
    // for every analog input we turn on a led 
    turnOnLed(analogInputPins[i], ledPins[i]);
  }
}
