/*** header block ***
 * code file name--------: Red, Green, Yellow LED Blink
 * code description------: Red, Green and Yellow LED will light up after holding down button
 * development board-----: MEGA 2560
 * sensors/devices needed:
 * IDE version-----------: 2.3.10
 * programmer(s) name----: Kevin Herrera Morales
 * date created/modified-: 9/16/2026
 * code version/revision-: 9/16/2026
 ***/

/* compiler directives */

// include libraries

const int buttonPin = 2;    // Push button connected to digital pin 2
const int redLedPin = 11;    // Red LED connected to digital pin 8
const int yellowLedPin = 10; // Yellow LED (wired in circuit)
const int greenLedPin = 9; // Green LED (wired in circuit)

void setup() {
  // Initialize Serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  
  // Initialize the LED pins as outputs
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}
void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    // 1. Green LED ON for 3 seconds
    if (!runTrafficStep(1, 3000)) return;

    // 2. Yellow LED ON for 1 second
    if (!runTrafficStep(2, 1000)) return;

    // 3. Red LED ON for 3 seconds
    if (!runTrafficStep(3, 3000)) return;
  } 
  else {
    setAllLEDs(LOW, LOW, LOW);
    Serial.print("Button Input: ");
    Serial.print(buttonState);
    Serial.println(" - All LEDs: OFF");
    delay(100);
  }
}

void setAllLEDs(int redState, int yellowState, int greenState) {
  digitalWrite(redLedPin, redState);
  digitalWrite(yellowLedPin, yellowState);
  digitalWrite(greenLedPin, greenState);
}

bool runTrafficStep(int colorCode, int duration) {
  if (colorCode == 1) {
    setAllLEDs(LOW, LOW, HIGH); // Green
  } else if (colorCode == 2) {
    setAllLEDs(LOW, HIGH, LOW); // Yellow
  } else if (colorCode == 3) {
    setAllLEDs(HIGH, LOW, LOW); // Red
  }

  int elapsed = 0;
  int interval = 100;

  while (elapsed < duration) {
    int currentButtonState = digitalRead(buttonPin);
    
    if (currentButtonState == LOW) {
      setAllLEDs(LOW, LOW, LOW);
      return false; 
    }

    Serial.print("Button Input: ");
    Serial.print(currentButtonState);
    Serial.print(" - Active LED Code: ");
    Serial.println(colorCode);

    delay(interval);
    elapsed += interval;
  }

  return true;
}
/* user defined functions */
