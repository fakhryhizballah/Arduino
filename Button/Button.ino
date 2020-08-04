const int  buttonPin = 2;// the pin that the pushbutton is attached to
const int  buttonStop = 4; 
const int ledStop = 12;
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;// current state of the button
int lastButtonState = 0;     // previous state of the button
int lastButtonStateStop = 0;
int buttonStateStop = 0;

int var = 0;

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(buttonStop, INPUT);
  pinMode(ledStop, OUTPUT);
}
void Stop(){
 buttonStateStop = digitalRead(buttonStop);
 if (buttonStateStop != lastButtonStateStop){
  if(buttonStateStop == HIGH) {
    Serial.println("Tap");
    digitalWrite(ledPin, LOW);
    digitalWrite(ledStop,HIGH);
    Start();
  } else {
    digitalWrite(ledStop  , LOW);
  }
  delay(50);
  }
  lastButtonStateStop = buttonStop;
}
void Start(){
   // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
      while (var < 100) {
  // do something repetitive 100 times
  var++;
  Serial.println("OKE");
  Serial.print(var);
      }
      digitalWrite(ledPin, LOW);
      Serial.println("Selesai");
    } else {
      // if the current state is LOW then the button went from on to off:
      digitalWrite(ledPin, LOW);
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}

void loop() {
//Start();

Stop();
}
