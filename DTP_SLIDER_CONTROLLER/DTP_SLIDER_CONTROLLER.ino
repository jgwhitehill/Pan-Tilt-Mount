#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <AltSoftSerial.h>
AltSoftSerial BTSerial; 
 
char c=' ';
boolean NL = true;

int input10Pin = A1; 	 // choose the pin for the LED
int input9Pin = 12;
int input8Pin = 11;
int input7Pin = 10;
int input6Pin = 7;
int input5Pin = 6;       // define push button input pins
int input4Pin = 5;
int input3Pin = 4;
int input2Pin = 3;
int input1Pin = 2;

int buttonRef = 0;

#define LED_PIN  13
#define LED_COUNT 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

char *commands[] = {
  "","",
  "A", "p40", "x100",
  "H2", "p30", "p20",
  "","",
  "e", "t20", "t40",
  "R"
};

uint32_t red = strip.Color(255,0,0);
uint32_t green = strip.Color(0,255,0);
uint32_t blue = strip.Color(0,0,255);
uint32_t yellow = strip.Color(255,255,0);
uint32_t white = strip.Color(255,255,255);
uint32_t pink = strip.Color(255,0,100);
uint32_t cyan = strip.Color(0,255,255);
uint32_t orange = strip.Color(230,80,0);
uint32_t off = strip.Color(0,0,0);
uint32_t* commandColor[] = {
  0,0,
  red, green, blue,
  yellow, white, pink,
  0,0,
  cyan, orange, green,
  off
};


void setup() 
{
  Serial.begin(57600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  BTSerial.begin(57600);  
  Serial.println("BTserial started at 57600");

  pinMode(input10Pin, INPUT_PULLUP);
  pinMode(input5Pin, INPUT_PULLUP); // declare push button inputs
  pinMode(input4Pin, INPUT_PULLUP);
  pinMode(input3Pin, INPUT_PULLUP);
  pinMode(input2Pin, INPUT_PULLUP);
  pinMode(input6Pin, INPUT_PULLUP);
  pinMode(input7Pin, INPUT_PULLUP);
  pinMode(input8Pin, INPUT_PULLUP);
  pinMode(input9Pin, INPUT_PULLUP);
  pinMode(input6Pin, INPUT_PULLUP);

  Serial.println("");

  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'

}
 
void loop()
{
    for(int i=2 ; i<=13 ; i++) {
    if (i == 8) {
      i = 10;
    }

    checkPush(i);
    
    // // Read from the Bluetooth module and send to the Arduino Serial Monitor
    // if (BTSerial.available())
    // {
    //     c = BTSerial.read();
    //     Serial.write(c);
    // }
 
    // // Read from the Serial Monitor and send to the Bluetooth module
    // if (Serial.available())
    // {
    //     c = Serial.read();
    //     BTSerial.write(c);   
 
    //     // Echo the user input to the main window. The ">" character indicates the user entered text.
    //     if (NL) { Serial.print(">");  NL = false; }
    //     Serial.write(c);
    //     if (c==10) { NL = true; }
    // }
     
    }
delay(150);
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void checkPush(int pinNumber)
{
  int pushed = LOW;
  if (pinNumber == 13) {
  pushed = digitalRead(input10Pin);  // read input value
  }
  else {
  pushed = digitalRead(pinNumber);
  }
  if (pushed == HIGH){ // check if the input is HIGH (button released)
    //digitalWrite(ledPin, HIGH); // turn LED ON
    Serial.println(commands[pinNumber]);
    colorWipe(commandColor[pinNumber], 100);
    BTSerial.write(commands[pinNumber]);

  }
  else{
   // digitalWrite(ledPin, LOW); // turn LED OFF
  }
  pushed = LOW;
}