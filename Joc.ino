#include "LiquidCrystal.h"
#include "LedControl.h"
#include "EEPROM.h"

const int LCD_WIDTH = 16;
const int LCD_HEIGHT = 2;
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int currentMenuState = 0;
int previousMenuState = -1;
int currentSettingsState = 0;
int previousSettingState = -1;

#define LCD_CONTRAST_PIN 3
#define LCD_BRIGHTNESS_PIN A5

const int pinX = A0;
const int pinY = A1;
const int pinSW = 2;
bool joyMovedX = false, joyMovedY = false;

const int buzzerPin = 13;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
byte buttonState = HIGH;
int buttonReading;
unsigned long timer = 0;
bool buttonPressed = false;

const String menuOptions[] = { "Start game", "How to play", "Highscores", "Settings", "About" };

const String settingsOptions[] = { "Enter name", "Difficulty", "LCD contrast", "LCD Brightness", "Matrix Brightness", "Sounds", "Theme Song", "Back" };

bool inMenu = true;
bool inSetting = false;
bool inGame = false;

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
const int xPin = A0;
const int yPin = A1;
int magicSeedNumbber = 43;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);	// DIN, CLK,LOAD, No. DRIVER

byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;
const int minThreshold = 400;
const int maxThreshold = 600;
const byte moveInterval = 100;
unsigned long long lastMoved = 0;
const byte matrixSize = 8;
bool matrixChanged = true;
int minValue = 0;
int maxValue = 7;
int randomFoodXPos;
int randomFoodYPos;
int score = 0;
int lcdGameUpdate = true;
unsigned long blinkInterval = 100;
unsigned long lastBlink = 0;
bool withBussiness = false;
int numberOfLives = 3;
int numberOfsec = 0;
int time = 0;
int level = 1;

byte matrix[matrixSize][matrixSize] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte greetings[matrixSize][matrixSize] = {
		{ 1, 0, 1, 0, 1, 1, 1, 0 },
	{ 1, 1, 1, 0, 1, 0, 1, 0 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 1, 1 },
	{ 0, 1, 1, 1, 0, 1, 0, 1 },
	{ 0, 1, 0, 1, 0, 1, 1, 1 },
	{ 1, 0, 1, 0, 1, 1, 1, 0 },
	{ 1, 1, 1, 0, 1, 0, 1, 0 }
};

byte matrixOn[matrixSize][matrixSize] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 }
};

byte happyFace[matrixSize][matrixSize] = {
		{ 0, 0, 1, 1, 1, 1, 0, 0 },
	{ 0, 1, 0, 0, 0, 0, 1, 0 },
	{ 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 1, 1, 0, 0, 1 },
	{ 0, 1, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 1, 1, 1, 1, 0, 0 }
};

byte snowflake[8] = { 0b10001,
	0b01010,
	0b10101,
	0b01110,
	0b01110,
	0b10101,
	0b01010,
	0b10001
};

byte soundOn[8] = { 0b00000,
	0b00010,
	0b00111,
	0b11110,
	0b11111,
	0b11110,
	0b00111,
	0b00010
};

byte soundOff[8] = { 0b00000,
	0b00010,
	0b00110,
	0b11110,
	0b11110,
	0b11110,
	0b00110,
	0b00010
};

byte heart[8] = { 0b00000,
	0b00000,
	0b11011,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000
};

struct
{
	int contrast;
	int brightness;
	int matrixBrightness;
	int difficulty;
	int idThemeSong;
	bool sound;
	char playerName[5];
}

settings;

void playSound()
{
	Serial.println("BEEP");
	if (settings.sound)
	{
		tone(buzzerPin, 1500, 10);
		delay(10);
	}
}

void readFromEEPROM()
{
	unsigned int positionInMemory = 0;
	EEPROM.get(positionInMemory, settings);
}

void updateEEPROM()
{
	unsigned int positionInMemory = 0;
	EEPROM.put(positionInMemory, settings);
}

void updateMatrix(byte matrix[matrixSize][matrixSize] = matrix)
{
	for (int col = 0; col < matrixSize; col++)
	{
		for (int row = 0; row < matrixSize; row++)
		{
			lc.setLed(0, row, col, matrix[row][col]);
		}
	}
}

bool matrixNeedClear = false;
void matrixClear()
{
	if (matrixNeedClear)
		lc.clearDisplay(0);
}

void lcdAtStart()
{
	lcd.clear();
	Serial.println("Show greeting");
	lcd.setCursor(2, 0);
	lcd.print("Santa Rusher");
	lcd.setCursor(0, 1);
	for (int i = 0; i < LCD_WIDTH; i++)
	{
		lcd.write((uint8_t) 0);
	}

	updateMatrix(greetings);
	matrixNeedClear = true;
	delay(2000);
}

int change()
{
	return (buttonPressed || previousMenuState != currentMenuState || previousSettingState != currentSettingsState);
}

void setup()
{
	lc.shutdown(0, false);

	lc.clearDisplay(0);	// clear screen
	generateFood();
	matrix[xPos][yPos] = 1;
	// if analog input pin 0 is unconnected, random analog
	// noise will cause the call to randomSeed() to generate
	// different seed numbers each time the sketch runs.
	// randomSeed() will then shuffle the random function.
	randomSeed(magicSeedNumbber);

	lcd.begin(LCD_HEIGHT, LCD_WIDTH);
	lcd.createChar(0, snowflake);
	lcd.createChar(1, soundOn);
	lcd.createChar(2, soundOff);
	lcd.createChar(3, heart);
	lcd.noCursor();
	lcd.noBlink();
	lcd.noAutoscroll();
	analogWrite(LCD_BRIGHTNESS_PIN, settings.brightness);
	analogWrite(LCD_CONTRAST_PIN, settings.contrast);

	pinMode(buzzerPin, OUTPUT);

	Serial.begin(9600);
	pinMode(pinSW, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pinSW), SWPress, FALLING);
	readFromEEPROM();
	lc.setIntensity(0, settings.matrixBrightness);
	lcdAtStart();
}

void updatePositions()
{
	int xValue = analogRead(xPin);
	int yValue = analogRead(yPin);
	xLastPos = xPos;
	yLastPos = yPos;
	if (xValue < minThreshold)
	{
		if (xPos < matrixSize - 1)
		{
			xPos++;
		}
		else
		{
			xPos = 0;
		}
	}

	if (xValue > maxThreshold)
	{
		if (xPos > 0)
		{
			xPos--;
		}
		else
		{
			xPos = matrixSize - 1;
		}
	}

	if (yValue > maxThreshold)
	{
		if (yPos < matrixSize - 1)
		{
			yPos++;
		}
		else
		{
			yPos = 0;
		}
	}

	if (yValue < minThreshold)
	{
		if (yPos > 0)
		{
			yPos--;
		}
		else
		{
			yPos = matrixSize - 1;
		}
	}

	if (xPos != xLastPos || yPos != yLastPos)
	{
		matrixChanged = true;
		matrix[xLastPos][yLastPos] = 0;
		matrix[xPos][yPos] = 1;
	}
}

void SWPress()
{
	if (millis() - lastDebounceTime >= debounceDelay)
	{
		buttonPressed = true;
		lastDebounceTime = millis();
	}

	playSound();
}

int getXValue()
{
	return getValue(pinX, joyMovedX);
}

int getYValue()
{
	return getValue(pinY, joyMovedY);
}

int getValue(int pin, bool &joyMoved)
{
	int val = analogRead(pin);

	if (val >= maxThreshold && joyMoved == false)
	{
		joyMoved = true;
		return 1;
	}

	if (val <= minThreshold && joyMoved == false)
	{
		joyMoved = true;
		return -1;
	}

	if (val < maxThreshold && val > minThreshold)
		joyMoved = false;
	return 0;
}

void instructions()
{
	lcd.clear();
	lcd.setCursor(1, 0);
	//now showing instructions for the dot game 
	lcd.print("Use the joystick to guide the player");
	lcd.setCursor(1, 1);
	lcd.print("Eat the dot to get more points");
	for (int positionCount = 0; positionCount < 57; positionCount++)
	{
		lcd.scrollDisplayLeft();
		delay(200);
	}

	delay(10);
	menu();
}

void about()
{
	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("You play SantaRusher");
	lcd.setCursor(1, 1);
	lcd.print("Find me on GitHub: StefaniaCri");
	for (int positionCount = 0; positionCount < 25; positionCount++)
	{
		lcd.scrollDisplayLeft();
		delay(300);
	}

	delay(10);
	menu();
}

void menu()
{
	lcd.clear();
	lcd.print("Menu");
	lcd.setCursor(1, 1);
	lcd.print(">");
	lcd.print(menuOptions[currentMenuState]);
}

void settingsMenu()
{
	lcd.clear();
	lcd.print("Settings");
	lcd.setCursor(1, 1);
	lcd.print(">");
	lcd.print(settingsOptions[currentSettingsState]);
}

void gameLCDdisplay()
{
	lcd.setCursor(0, 0);
	for (int i = 0; i < numberOfLives; i++)
		lcd.write(3);
	lcd.setCursor(4, 0);
	lcd.print(score);
	lcd.print(" lvl.");
	lcd.print(level);
	lcd.setCursor(10, 1);
	lcd.print(time);
	if (millis() - numberOfsec >= 1000)
	{
		time++;
		numberOfsec = millis();
	}
}

void goBackToSettingsMenu()
{
	withBussiness = false;
	inSetting = true;
	buttonPressed = false;
	previousSettingState = -1;
	lcd.noCursor();
}

void enterName()
{
	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print(settings.playerName);
	lcd.setCursor(4, 0);
	lcd.cursor();

	int positionInName = 0;
	char copyName[5];
	strcpy(copyName, settings.playerName);
	Serial.println(copyName);

	Serial.println(copyName);
	while (!buttonPressed)
	{
		int x = getXValue();
		int y = getYValue();
		if (x != 0)
		{
			positionInName += x;
			if (positionInName > 4)
			{
				positionInName = 4;
			}

			if (positionInName < 0)
			{
				positionInName = 0;
			}

			lcd.setCursor(positionInName + 4, 0);
		}

		if (y != 0)
		{
			copyName[positionInName] += y;

			if (copyName[positionInName] == 'z' + 1)
			{
				copyName[positionInName] = 'a';
			}

			if (copyName[positionInName] == 'a' - 1)
			{
				copyName[positionInName] = 'z';
			}

			lcd.print(copyName[positionInName]);
			lcd.setCursor(positionInName + 4, 0);
		}

		delay(20);
	}

	strcpy(settings.playerName, copyName);
	updateEEPROM();
	goBackToSettingsMenu();
}

void generateFood()
{
	randomFoodXPos = random(minValue, maxValue);
	randomFoodYPos = random(minValue, maxValue);

	while (randomFoodXPos == xPos && randomFoodYPos == yPos)
	{
		randomFoodXPos = random(minValue, maxValue);
		randomFoodYPos = random(minValue, maxValue);
	}

	matrix[randomFoodXPos][randomFoodYPos] = 1;
	matrixChanged = true;
}

void soundON()
{
	lcd.clear();
	lcd.setCursor(1, 0);
	lcd.print("Sound");

	while (!buttonPressed)
	{
		lcd.setCursor(7, 0);
		int x = getXValue();
		if (x == 1)
			settings.sound = true;
		if (x == -1)
			settings.sound = false;
		if (settings.sound)
			lcd.write(1);
		else lcd.write(2);
	}

	updateEEPROM();
	goBackToSettingsMenu();
	delay(30);
}

void printIntensity(int length)
{
	lcd.clear();
	lcd.print("- ");
	lcd.setCursor(14, 0);
	lcd.print(" +");
	lcd.setCursor(2, 0);
	for (byte i = 2; i <= 14; i++)
	{
		if (i - 2 < length)
		{
			lcd.write(255);
		}
		else
		{
			lcd.print(" ");
		}
	}
}

void changeDifficulty()
{
	printIntensity(settings.difficulty);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.difficulty += xValue * 4;
			if (settings.difficulty > 12)
			{
				settings.difficulty = 12;
			}

			if (settings.difficulty < 4)
			{
				settings.difficulty = 4;
			}

			printIntensity(settings.difficulty);
		}
	}

	updateEEPROM();
	goBackToSettingsMenu();
	delay(30);
};

void changeBrightness()
{
	printIntensity(settings.brightness);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.brightness += xValue;
			if (settings.brightness > 12)
			{
				settings.brightness = 12;
			}

			if (settings.brightness < 1)
			{
				settings.brightness = 1;
			}

			printIntensity(settings.brightness);
			analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
		}
	}
  settings.brightness = map(settings.brightness, 1, 12, 1, 255);
	updateEEPROM();
	analogWrite(LCD_BRIGHTNESS_PIN, settings.brightness);
	goBackToSettingsMenu();
	delay(30);
};

void changeContrast()
{
	printIntensity(settings.contrast);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.contrast += xValue;
			if (settings.contrast > 12)
			{
				settings.contrast = 12;
			}

			if (settings.contrast < 1)
			{
				settings.contrast = 1;
			}

			printIntensity(settings.contrast);
			analogWrite(LCD_CONTRAST_PIN, map(settings.contrast, 1, 12, 1, 150));
		}
	}
  settings.contrast = map(settings.contrast, 1, 12, 1, 150);
	updateEEPROM();
	analogWrite(LCD_CONTRAST_PIN, settings.contrast);
	goBackToSettingsMenu();
	delay(30);
};

void changeMatrixBright()
{
	updateMatrix(matrixOn);
	printIntensity(settings.matrixBrightness);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.matrixBrightness += xValue;
			if (settings.matrixBrightness > 12)
			{
				settings.matrixBrightness = 12;
			}

			if (settings.matrixBrightness < 1)
			{
				settings.matrixBrightness = 1;
			}

			printIntensity(settings.matrixBrightness);
			lc.setIntensity(0, settings.matrixBrightness);
		}
	}

	updateEEPROM();
	matrixNeedClear = true;
	goBackToSettingsMenu();
	delay(30);
};

void game()
{
	//  updateByteMatrix();
	if (millis() - lastMoved > moveInterval)
	{
		// game logic
		updatePositions();
		lastMoved = millis();
	}

	if (millis() - lastBlink > blinkInterval)
	{
		matrix[randomFoodXPos][randomFoodYPos] = !matrix[randomFoodXPos][randomFoodYPos];
		matrixChanged = true;
		lastBlink = millis();
	}

	if (matrixChanged == true)
	{
		// matrix display logic
		updateMatrix();
		matrixChanged = false;
	}

	if (randomFoodXPos == xPos && randomFoodYPos == yPos)
	{
		score++;
		lcdGameUpdate = true;
		Serial.println(score);
		generateFood();
	}
}

void MenuDisplay()
{
	currentMenuState += getYValue();
	currentMenuState = abs(currentMenuState % 5);
	if (currentMenuState != previousMenuState)
	{
		menu();
		playSound();
	}

	if (buttonPressed)
	{
		switch (currentMenuState)
		{
			case 0:
				Serial.println("Incep jocul");
				game();
				inMenu = false;
				inGame = true;
				break;
			case 1:
				instructions();
				break;
			case 2:
				Serial.println("show highscores");
				break;
			case 3:
				inSetting = true;
				inMenu = false;
				break;
			case 4:
				about();
				break;
		}

		buttonPressed = false;
	}

	previousMenuState = currentMenuState;

}

void SettingsDisplay()
{
	currentSettingsState += getYValue();
	currentSettingsState = abs(currentSettingsState % 8);
	if (currentSettingsState != previousSettingState)
	{
		playSound();
		settingsMenu();
	}

	if (buttonPressed)
	{
		withBussiness = true;
		inSetting = false;
		buttonPressed = false;
	}

	previousSettingState = currentSettingsState;

}

void doingBussiness()
{
	switch (currentSettingsState)
	{
		case 0:
			enterName();
			Serial.println(settings.playerName);
			break;
		case 1:
			Serial.println("Dificulty");
			changeDifficulty();
			break;
		case 2:
			Serial.println("LCD contrast");
			changeContrast();
			break;
		case 3:
			Serial.println("LCD brightness");
			changeBrightness();
			break;
		case 4:
			changeMatrixBright();
			Serial.println("Matrix brightness");
			break;
		case 5:
			soundON();
			Serial.println("Sounds");
			break;
		case 6:
			Serial.println("Theme Song");
			break;
		case 7:
			inMenu = true;
			withBussiness = false;
			previousMenuState = -1;
			currentSettingsState = 0;
			break;
	}
}

int firstInLoop = true;
void loop()
{
  Serial.println(settings.contrast);
  Serial.println(settings.brightness);
	matrixClear();
	if (inGame == true)
	{
		if (firstInLoop)
		{
			lcd.clear();
			firstInLoop = false;
		}

		game();
		gameLCDdisplay();
	}
	else if (inMenu == true)
	{
		MenuDisplay();
	}
	else if (inSetting == true)
	{
		SettingsDisplay();
	}
	else if (withBussiness == true)
	{
		doingBussiness();
	}
}