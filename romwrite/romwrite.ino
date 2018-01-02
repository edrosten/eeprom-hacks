/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
static const int led = 13;

static const int CS = 4;
static const int CK = 5;
static const int mMOSI = 6;
static const int mMISO = 7;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  pinMode(CS, OUTPUT);
  pinMode(CK, OUTPUT);
  pinMode(mMOSI, OUTPUT);
  pinMode(mMISO, INPUT);
  Serial.begin(9600);  
}



//Write out the N low order bits of data as MSB first
//and return the collected data.
uint32_t write_N_MSB_first(uint32_t data, int n)
{
  uint32_t ret = 0;
  
  //First shift everything to the 16th bit
  data <<= (32-n);
  digitalWrite(mMOSI, LOW); //Make the scope trace look nice
  delay(1);
  
  for(int i=0; i < n; i++)
  {
    digitalWrite(mMOSI, (bool)(data& (uint32_t(1)<<31)));
    delay(1);
    digitalWrite(CK, HIGH);
    delay(1);
    digitalWrite(CK, LOW);
    delay(1);
    int r = digitalRead(mMISO);
    ret <<=1;
    ret |= r;
    data<<=1;   
  }
  digitalWrite(mMOSI, LOW); //Make the scope trace look nice  
  return ret;
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
//  Serial.write("hello, world\n");
  
  digitalWrite(CS,1);
  write_N_MSB_first(0x360, 10);
  write_N_MSB_first(0, 8);
  digitalWrite(CS, 0);


}
