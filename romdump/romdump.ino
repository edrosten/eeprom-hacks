// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
static const int led = 13;

static const int CS = 4;
static const int CK = 5;
static const int mMOSI = 6;
static const int mMISO = 7;

static const int BUTTON = 2;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  pinMode(CS, OUTPUT);
  pinMode(CK, OUTPUT);
  pinMode(mMOSI, OUTPUT);
  pinMode(mMISO, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);  
  Serial.write("Booted...\n");
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

uint8_t read(uint8_t addr)
{
  digitalWrite(CS,1);
  write_N_MSB_first(0x300 | (addr&0x7f), 10);
  int v = write_N_MSB_first(0, 8);
  digitalWrite(CS, 0);
  delay(1);
  return v;
}


// the loop routine runs over and over again forever:
void loop() {
  if(!digitalRead(BUTTON))
  {
    delay(200);
    Serial.write("Sequence begin\n");
    while(!digitalRead(BUTTON))
    {}
    
    unsigned char data[128];
    for(int i=0; i < 128; i++)
      data[i] = read(i);
     
    for(int i=0; i < 128; i++)
    {
      if(i % 16 == 0)
      {
        Serial.print("\n0x");
        Serial.print(i, HEX);   
        Serial.print(":");
      }
     
      Serial.write(" 0x");
      Serial.print(data[i], HEX);
    }
  }
  else
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);               // wait for a second
  }

}
