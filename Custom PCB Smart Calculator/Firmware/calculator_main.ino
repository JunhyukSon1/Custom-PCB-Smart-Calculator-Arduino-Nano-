#include <Wire.h>              // I2C Communication (A4=SDA, A5=SCL)
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

// ─────────────────────────────────────────
// OLED Configuration (I2C)
// SDA -> A4, SCL -> A5 (Arduino Nano hardware I2C pins)
// DC and CS pins are not used in I2C mode
// ─────────────────────────────────────────
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1      // RST not connected
#define OLED_ADDRESS  0x3C    // DFR0650 default I2C address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ─────────────────────────────────────────
// Buzzer Configuration
// ─────────────────────────────────────────
#define BUZZER_PIN 10

// ─────────────────────────────────────────
// 4x4 Matrix Keypad Configuration
// ─────────────────────────────────────────
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ─────────────────────────────────────────
// Calculator Variables
// ─────────────────────────────────────────
String currentInput = "";
String operatorStr  = "";
float  num1         = 0;
float  num2         = 0;
bool   isResult     = false;

// ─────────────────────────────────────────
// Function Declarations
// ─────────────────────────────────────────
void playBeep();
void updateDisplay(String text);

// ─────────────────────────────────────────
// setup()
// ─────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  Serial.println("System Start!");

  // Startup buzzer sound
  pinMode(BUZZER_PIN, OUTPUT);
  tone(BUZZER_PIN, 800, 150);
  delay(500);

  // Initialize OLED (I2C)
  Serial.println("OLED Initializing...");

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("Error: OLED Failed!");
    for (;;); // System halts here if OLED initialization fails
  }

  Serial.println("OLED Success!");

  // Startup screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 15);
  display.println("Calculator");
  display.setTextSize(1);
  display.setCursor(25, 50);
  display.println("Ready!");
  display.display();
  delay(1500);

  updateDisplay("0");
}

// ─────────────────────────────────────────
// loop()
// ─────────────────────────────────────────
void loop() {
  char key = keypad.getKey();

  if (key) {
    playBeep();

    // C: Clear / Reset
    if (key == 'C') {
      currentInput = "";
      operatorStr  = "";
      num1         = 0;
      num2         = 0;
      isResult     = false;
      updateDisplay("0");
    }

    // Operator input
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (currentInput != "") {
        num1        = currentInput.toFloat();
        operatorStr = String(key);
        currentInput = "";
        updateDisplay(String(num1) + " " + operatorStr);
      }
    }

    // = : Calculate
    else if (key == '=') {
      if (currentInput != "" && operatorStr != "") {
        num2 = currentInput.toFloat();
        float result = 0;

        if      (operatorStr == "+") result = num1 + num2;
        else if (operatorStr == "-") result = num1 - num2;
        else if (operatorStr == "*") result = num1 * num2;
        else if (operatorStr == "/") {
          if (num2 == 0) {
            // Exception handling: Prevent division by zero
            updateDisplay("Err:Div0");
            delay(2000);
            currentInput = "";
            operatorStr  = "";
            updateDisplay("0");
            return;
          }
          result = num1 / num2;
        }

        // If integer, display without decimal point
        if (result == (long)result) {
          updateDisplay(String((long)result));
          currentInput = String((long)result);
        } else {
          updateDisplay(String(result));
          currentInput = String(result);
        }

        operatorStr = "";
        isResult    = true;
      }
    }

    // Number input
    else {
      if (isResult) {
        currentInput = "";
        isResult     = false;
      }
      currentInput += key;

      if (operatorStr == "") {
        updateDisplay(currentInput);
      } else {
        updateDisplay(String(num1) + " " + operatorStr + " " + currentInput);
      }
    }
  }
}

// ─────────────────────────────────────────
// Buzzer Function (800Hz = Soft sound)
// ─────────────────────────────────────────
void playBeep() {
  tone(BUZZER_PIN, 800, 30);
}

// ─────────────────────────────────────────
// Update OLED (Auto-adjust text size based on length)
// ─────────────────────────────────────────
void updateDisplay(String text) {
  display.clearDisplay();

  if (text.length() <= 6) {
    display.setTextSize(3);
    display.setCursor(0, 20);
  } else if (text.length() <= 10) {
    display.setTextSize(2);
    display.setCursor(0, 25);
  } else {
    display.setTextSize(1);
    display.setCursor(0, 28);
  }

  display.setTextColor(SSD1306_WHITE);
  display.println(text);
  display.display();
}
