//
int LED_G_PIN = 9;
int LED_R_PIN = 10;
int ECHO_PIN = 12;
int TRIGGER_PIN = 13;

int maximumRange = 6; // max 174
int minimumRange = 0; // Minimum range needed
long duration, distance;

//
void setup()
{
  Serial.begin(9600);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  digitalWrite(LED_R_PIN, HIGH);
  digitalWrite(LED_G_PIN, LOW);
}

//
void loop() 
{
  digitalWrite(TRIGGER_PIN, LOW); 
  delayMicroseconds(2); 

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 

  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58.2;

  Serial.println(distance);

  if (distance > maximumRange) {
    digitalWrite(LED_R_PIN, HIGH);
    digitalWrite(LED_G_PIN, LOW);
  }
  else {
    digitalWrite(LED_R_PIN, LOW);
    digitalWrite(LED_G_PIN, HIGH);
  }

  delay(200);
}

