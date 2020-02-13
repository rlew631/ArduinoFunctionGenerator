float sin0_180[]={0.000000,0.018530,0.037053,0.055564,0.074055,0.092521,
0.110956,0.129352,0.147704,0.166005,0.184249,0.202430,0.220541,0.238577,
0.256531,0.274396,0.292168,0.309839,0.327403,0.344856,0.362189,0.379399,
0.396478,0.413421,0.430222,0.446876,0.463375,0.479716,0.495892,0.511898,
0.527728,0.543377,0.558839,0.574109,0.589183,0.604053,0.618717,0.633168,
0.647401,0.661413,0.675197,0.688749,0.702065,0.715140,0.727969,0.740548,
0.752873,0.764939,0.776743,0.788280,0.799546,0.810538,0.821252,0.831683,
0.841829,0.851686,0.861250,0.870519,0.879488,0.888156,0.896519,0.904573,
0.912318,0.919749,0.926864,0.933661,0.940137,0.946290,0.952119,0.957621,
0.962793,0.967635,0.972145,0.976321,0.980162,0.983666,0.986833,0.989661, 
0.992148,0.994295,0.996101,0.997565,0.998686,0.999464,0.999899,0.999991,
0.999739,0.999144,0.998206,0.996925,0.995302,0.993337,0.991031,0.988384,
0.985398,0.982074,0.978413,0.974416,0.970084,0.965419,0.960422,0.955096,
0.949442,0.943461,0.937157,0.930531,0.923585,0.916323,0.908745,0.900856,
0.892657,0.884152,0.875343,0.866233,0.856826,0.847125,0.837133,0.826854,
0.816290,0.805447,0.794326,0.782933,0.771272,0.759345,0.747157,0.734713,
0.722017,0.709073,0.695885,0.682458,0.668797,0.654907,0.640791,0.626456,
0.611905,0.597144,0.582178,0.567013,0.551652,0.536102,0.520368,0.504456,
0.488370,0.472116,0.455701,0.439128,0.422405,0.405537,0.388530,0.371389,
0.354121,0.336731,0.319226,0.301611,0.283892,0.266076,0.248169,0.230176,
0.212105,0.193960,0.175749,0.157477,0.139152,0.120778,0.102364,0.083914,
0.065435,0.046934,0.028416,0.009889
};
//there are 171 total values which are based on a 5 us delay at 523.25hz (C note)
//this allows for close to 180 intervals from sin(0) to sin(180)
float ramp[]={
  
};

int i = 0;
int j = 0;
int outvalue = 0;
const int AnalogOutPinR = 9; //this is the output for the positive PWM
const int AnalogOutPinL = 10; //this is the output for the negative PWM
const int GNDR = 7;
const int GNDL = 6;
//int button1;
//int button2;
//int button3;


void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setup() {
Serial.begin(9600);
pinMode(GNDL, OUTPUT);
pinMode(GNDR, OUTPUT);
pinMode(AnalogOutPinL, OUTPUT);
setPwmFrequency(10,1);
pinMode(AnalogOutPinR, OUTPUT);
setPwmFrequency(9,1);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);

}


void loop() {
  
//positive half
  if(digitalRead(2)==LOW || digitalRead(3)==LOW || digitalRead(4)==LOW)
    {
     digitalWrite(GNDL, HIGH);
     digitalWrite(GNDR, LOW);
    }
    else
    {
     digitalWrite(GNDL, LOW);
     digitalWrite(GNDR, LOW);
    }
  while (i<171)
    { if(digitalRead(2)==LOW && digitalRead(3)==HIGH && digitalRead(4)==HIGH)
        {outvalue = (int) 255*sin0_180[i];
   //     Serial.println("sinpos");//sin value
        }
      else if(digitalRead(2)==HIGH && digitalRead(3)==LOW && digitalRead(4)==HIGH)
        {if(i<=85) {outvalue=(int) 255*i/85;}//ramp up
        else if(i>85) {outvalue=(int) 255-(255*(i-85)/85);}
   //     Serial.println("ramppos");//ramp down
        }
      else if(digitalRead(2)==HIGH && digitalRead(3)==HIGH && digitalRead(4)==LOW)
        {outvalue= (int) 0.6*255;
   //     Serial.println("squarepos");//square wave
        }  
      else{
        outvalue=0;
   //     Serial.println("nothingpos");
      }
      analogWrite(AnalogOutPinR, outvalue);
      i++;
   //   Serial.println(i);
      delayMicroseconds(5);
    }
i=0;

//negative half
  if(digitalRead(2)==LOW || digitalRead(3)==LOW || digitalRead(4)==LOW)
    {
     digitalWrite(GNDL, LOW);
     digitalWrite(GNDR, HIGH);
    }
    else
    {
     digitalWrite(GNDL, LOW);
     digitalWrite(GNDR, LOW);
    }
  while (i<171) 
    { if(digitalRead(2)==LOW && digitalRead(3)==HIGH && digitalRead(4)==HIGH)
        {outvalue = (int) 255*sin0_180[i];//sin value
   //     Serial.println("sinneg");//sin value
        }
      else if(digitalRead(2)==HIGH && digitalRead(3)==LOW && digitalRead(4)==HIGH)
        {if(i<=85) {outvalue=(int) 255*i/85;}//ramp up
        else if(i>85) {outvalue=(int) 255-(255*(i-85)/85);}
   //     Serial.println("rampneg");//ramp down
        }
      else if(digitalRead(2)==HIGH && digitalRead(3)==HIGH && digitalRead(4)==LOW)
        {outvalue= (int)0.6*255;
   //     Serial.println("squareneg");//square wave  
        }
      else{
   //     Serial.println("nothingneg");
          outvalue=0;
          digitalWrite(GNDR, LOW);
      }
      analogWrite(AnalogOutPinL, outvalue);
      i++;
   //   Serial.println(i);
      delayMicroseconds(5);
    }
  i=0;

}
