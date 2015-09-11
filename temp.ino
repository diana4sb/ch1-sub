int p1;

int p2;

int p3;

int p4;


void setup()  { 

 Serial.begin(9600); 

}


void loop()  { 

  if (Serial.available() >= 21) {  

    if (Serial.read() == 0x7E) { 

      for (int i = 1; i<19; i++) { 
        
        if(i == 8) { p1 = Serial.read(); }

        else if (i==9) { p2 = Serial.read(); }

        else if (i==10) { p3 = Serial.read(); }

        else if (i==11) { p4 = Serial.read(); }

        else { byte discardByte = Serial.read(); } 

      }

      int analogMSB = Serial.read(); 

      int analogLSB = Serial.read(); 

      float volt = calculateVolt(analogMSB, analogLSB);

      Serial.println(idSensor(p1,p2,p3,p4)); 

      Serial.print("Temperature in F: ");

      Serial.println(tempF(volt)); 

    }

  }

  delay(40); 

}




//selects identity of the Xbee 

String idSensor(int a, int b, int c, int d) {

  int r1[] = {#, #, #, #}; //Arrays are the 32 bit address of the two XBees routers

  int r2[] = {#, #, #, #}; 

  int r3[] = {#, #, #, #};

  int r4[] = {#, #, #, #};

  int r5[] = {#, #, #, #};

  if(a == r1[0] && b == r1[1] && c == r1[2] && d == r1[3]) { 

    return "Reading sensor 1:"; } 

  if(a == r2[0] && b == r2[1] && c == r2[2] && d == r2[3]) {

    return "Reading sensor 2:"; } //temp data is from XBee two

  if(a == r3[0] && b == r3[1] && c == r3[2] && d == r3[3]) { 

    return "Reading sensor 3:"; } 

  if(a == r4[0] && b == r4[1] && c == r4[2] && d == r4[3]) {

    return "Reading sensor 4:"; }

  if(a == r5[0] && b == r5[1] && c == r5[2] && d == r5[3]) {

    return "Reading sensor 5:"; }
}



 //calculates temperature in F 

float tempF(float v) { 

 float temp = 0;

 // .75 volts is 25 C. 10mV per degree

 if (v < .75) { temp = 25 - ((.75-v)/.01); } 

 else if (v == .75) {temp = 25; }

 else { temp = 25 + ((v -.75)/.01); } 

 temp =((temp*9)/5) + 32;

 return temp;

}




//converts an XBee analog pin reading to a voltage value

float calculateVolt(int analogMSB, int analogLSB) {

  int analogReading = analogLSB + (analogMSB * 256); 

  float volt = ((float)analogReading / 1023)*1.23; 

  return volt;

}
