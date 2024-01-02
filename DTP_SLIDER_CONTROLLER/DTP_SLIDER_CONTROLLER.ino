#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//#include <AltSoftSerial.h>
//AltSoftSerial BTSerial; 

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(8, 9); // RX | TX

char c=' ';
boolean NL = true;

int input10Pin = A1; 
int input9Pin = 12;
int input8Pin = 7;
int input7Pin = 4;
int input6Pin = 11;
int input5Pin = 5;       
int input4Pin = 3;
int input3Pin = 10;
int input2Pin = 6;
int input1Pin = 2;

int buttonRef = 0;

bool macro = false;

#define LED_PIN  13
#define LED_COUNT 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


uint32_t red = strip.Color(255,0,0);
uint32_t green = strip.Color(0,255,0);
uint32_t blue = strip.Color(0,0,255);
uint32_t yellow = strip.Color(255,255,0);
uint32_t white = strip.Color(255,255,255);
uint32_t pink = strip.Color(255,0,100);
uint32_t cyan = strip.Color(0,255,255);
uint32_t orange = strip.Color(230,80,0);
uint32_t off = strip.Color(0,0,0);



char *commands[4][3] = {
                    {   "A",  "H2",    "e"}, 
                    {"x100", "t40", "x200"},
                    { "p20", "t20",  "p40"},
                    { "R",      "",     ""}
};


char *macroCommands[4][3] = {
                    //CLEAR_ARRAY,EDIT_ARRAY,EXECUTE_MOVES
                    {"C", "E", ";"},
                    //STEP_BACKWARD, ADD_POSITION, STEP_FORWARD
                    {"<", "#", ">"},
                    //JUMP_TO_END, ORIBIT_POINT, JUMP_TO_END
                    {"[", "@", "]"},
                    { "R", "",  ""}
};


int pinRead[4][3] = {
                    { input1Pin, input2Pin, input3Pin}, 
                    { input4Pin, input5Pin, input6Pin},
                    { input7Pin, input8Pin, input9Pin},
                    { input10Pin,         14,       14}
};

uint32_t commandColor[4][3] = {
                    {  red,orange, cyan}, 
                    { pink, white, pink},
                    {green, white,green},
                    {  off,  blue,  off}
};

uint32_t macroCommandColor[4][3] = {
                    { blue, blue, blue}, 
                    { blue, blue, blue},
                    { blue, blue, blue},
                    {  off,  blue,  off}
};

void setup() 
{
  Serial.begin(57600);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.println(" ");

  BTSerial.begin(57600);  
  Serial.println("BTSerial started at 57600");

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

    for(int y=0 ; y<=4 ; y++) {
      for(int x=0 ; x<=2 ; x++){
       // Serial.print(commands[y][x]);
        checkPush(x,y);
      }
    }
    delay(100);
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match

}
void checkPush(int buttonX, int buttonY)
{
  int pushed = LOW;

  pushed = digitalRead(pinRead[buttonX][buttonY]);

  if (pushed == HIGH){
    if (!macro){
      if (pinRead[buttonX][buttonY] == input10Pin){
        macro = true;
        colorWipe(yellow, 100);
      }
      else {
        Serial.println(commands[buttonX][buttonY]);
        BTSerial.write(commands[buttonX][buttonY]);
        colorWipe(commandColor[buttonX][buttonY], 100);
      }
      delay(100);
    }
    else if (macro) {
      macro = false;
      Serial.println(macroCommands[buttonX][buttonY]);
      BTSerial.write(macroCommands[buttonX][buttonY]);
      colorWipe(macroCommandColor[buttonX][buttonY], 100);
      delay(100);
    }
    
    //Serial.println(digitalRead(pinRead[buttonX][buttonY]));
    //Serial.println(pinRead[buttonX][buttonY]);
    
  }
  else{
   // digitalWrite(ledPin, LOW); // turn LED OFF
  }
  pushed = LOW;
}


