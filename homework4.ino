int currentDisplay = 0;
int currentState = 1;

const int latchPin = 11; //STCP
const int clockPin = 10; //SHCP
const int dataPin = 12; //DS

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int pinX = A0;
const int pinY = A1;
const int pinSW = 2;

const byte regSize = 8;

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int displayCount = 4;
const int encodingsNumber = 16;

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};
int displayNumber[]= {0,0,0,0};

int xValue, yValue;
bool joyMoved = false;

const int minThreshold = 400;
const int maxThreshold = 600;

const unsigned long blinkOnInterval = 300;
const unsigned long blinkOffInterval = 600;
unsigned long blinkTime = 0;

long holdingTime;
long previousHoldingTime;
unsigned long firstPressTime;
byte SWState;
byte previousState = HIGH;

const unsigned long longPressedTime = 400;
const unsigned long shortDelayBetweenPressing = 50;
const unsigned long longDelayBetweenPressing = 100;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //check the state of SW
  SWPress();
  // show the display state right now
  writeDisplay(); 
  // change the state
  if(currentState == 1)
  {
    state1();
  }else if(currentState == 2){
    state2();
  }
}

void SWPress()
{
  SWState = digitalRead(pinSW);
// save the momment the SW was pressed
  if (SWState == LOW && previousState == HIGH && (millis() - firstPressTime) > longDelayBetweenPressing) 
  {
    firstPressTime = millis();
  }
  holdingTime = (millis() - firstPressTime);
// check for how long the SW was pressed
  if (holdingTime > shortDelayBetweenPressing) 
  {
    if (SWState == HIGH && previousState == LOW) 
    {
      if (holdingTime <= longPressedTime)
      {         
        Serial.println("short button press");
        // change the states
        if(currentState == 1){
          currentState = 2;
          Serial.println("State 2");
        }
        else{
          currentState = 1; 
          Serial.println("State 1");
        } 
    
      }
      if (holdingTime > longPressedTime && currentState == 1) 
      {
        Serial.println("long button press => reset");
        reset();
   
      }
    }
  }
  previousState = SWState;
  previousHoldingTime = holdingTime;
}
void state1()
{
  // state 1 = move from one display to another when moving X-axis
  xValue = analogRead(pinX); 

  if(xValue < minThreshold && !joyMoved)
  {
    currentDisplay = (currentDisplay - 1);
    if(currentDisplay < 0)
    {
      currentDisplay = 0;
    }

    joyMoved = true;
  }

  if(xValue > maxThreshold && !joyMoved)
  {
    currentDisplay = (currentDisplay + 1);
    if(currentDisplay > 3)
    {
      currentDisplay = 3;
    }
    joyMoved = true;
  }

  if(joyMoved && xValue >= minThreshold && xValue <= maxThreshold)
  {
    joyMoved = false;
  }
}

void state2()
{
  // change the number saved in the current display using the Y-axis
  yValue = analogRead(pinY); 

  if(yValue < minThreshold && !joyMoved)
  {
    displayNumber[currentDisplay]--;
    if(displayNumber[currentDisplay] < 0)
    {
      displayNumber[currentDisplay] = 0;
    }

    joyMoved = true;
  }

  if(yValue > maxThreshold && !joyMoved)
  {
    displayNumber[currentDisplay]++;
    if(displayNumber[currentDisplay] > 15)
    {
      displayNumber[currentDisplay] = 15;
    }
    joyMoved = true;
  }

  if(joyMoved && yValue >= minThreshold && yValue <= maxThreshold)
  {
    joyMoved = false;
  }

}

void activateDisplay(int display) { 
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[display], LOW);
}

void writeReg(int digit) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    digitalWrite(latchPin, HIGH);
}

void writeDisplay() {
  
  for(int displayDigit = 0; displayDigit < displayCount; displayDigit++){
    int digit = 0;
    // if the current display is selected add the dp point
    if(currentDisplay == displayDigit){
      if(currentState == 1){
        digit = byteEncodings[displayNumber[displayDigit]];
        if (millis() - blinkTime > blinkOnInterval) {
          digit = byteEncodings[displayNumber[displayDigit]] + 1; 
        } 
        if (millis() - blinkTime > blinkOffInterval) {
          digit = byteEncodings[displayNumber[displayDigit]];
          blinkTime = millis();
        }
      }else if (currentState == 2) {
        digit = byteEncodings[displayNumber[displayDigit]] + 1; 
      }
     

    }else{
      digit = byteEncodings[displayNumber[displayDigit]];
    }
    writeReg(digit);
    activateDisplay(displayDigit);
    delay(3);
  }
}

void reset()
{
  for(int displayDigit = 0; displayDigit < displayCount; displayDigit++)
  {
    displayNumber[displayDigit]= 0;
  }
  currentDisplay = 0;
}