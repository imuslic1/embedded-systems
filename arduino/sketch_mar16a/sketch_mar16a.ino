const short a = 4;
const short b = 5;
const short dp = 6;
const short c = 7;
const short d = 8;
const short e = 9;
const short f = 10;
const short g = 11;

int timeDelay = 1000;

void setup() {
  // put your setup code here, to run once:
  for(int thisPin = 4; thisPin <= 11; ++thisPin) 
    pinMode(thisPin, OUTPUT);
  pinMode(3, INPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digital_0(); delay(1000);
  digital_1(); delay(1000);
  digital_2(); delay(1000);
  digital_3(); delay(1000);
  digital_4(); delay(1000);
  digital_5(); delay(1000);
  digital_6(); delay(1000);
  digital_7(); delay(1000);
  digital_8(); delay(1000);
  digital_9(); delay(1000);



}

void digital_0(void) // nula
{ digitalWrite(a,HIGH); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,HIGH);
digitalWrite(e,HIGH); digitalWrite(f,HIGH);
digitalWrite(g,LOW); digitalWrite(dp,LOW);
}
void digital_1(void) // jedan
{ digitalWrite(a,LOW); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,LOW);
digitalWrite(e,LOW); digitalWrite(f,LOW);
digitalWrite(g,LOW); digitalWrite(dp,LOW);
}
void digital_2(void) // dva
{ digitalWrite(a,HIGH); digitalWrite(b,HIGH);
digitalWrite(c,LOW); digitalWrite(d,HIGH);
digitalWrite(e,HIGH); digitalWrite(f,LOW);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
void digital_3(void) // tri
{ digitalWrite(a,HIGH); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,HIGH);
digitalWrite(e,LOW); digitalWrite(f,LOW);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
void digital_4(void) // cetiri
{ digitalWrite(a,LOW); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,LOW);
digitalWrite(e,LOW); digitalWrite(f,HIGH);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
void digital_5(void) // pet
{ digitalWrite(a,HIGH); digitalWrite(b,LOW);
digitalWrite(c,HIGH); digitalWrite(d,HIGH);
digitalWrite(e,LOW); digitalWrite(f,HIGH);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
void digital_6(void) // sest
{ digitalWrite(a,HIGH); digitalWrite(b,LOW);
digitalWrite(c,HIGH); digitalWrite(d,HIGH);
digitalWrite(e,HIGH); digitalWrite(f,HIGH);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
void digital_7(void) // sedam
{ digitalWrite(a,HIGH); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,LOW);
digitalWrite(e,LOW); digitalWrite(f,LOW);
digitalWrite(g,LOW); digitalWrite(dp,LOW);

}
void digital_8(void) // osam
{ digitalWrite(a,HIGH); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,HIGH);
digitalWrite(e,HIGH); digitalWrite(f,HIGH);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
void digital_9(void) // devet
{ digitalWrite(a,HIGH); digitalWrite(b,HIGH);
digitalWrite(c,HIGH); digitalWrite(d,HIGH);
digitalWrite(e,LOW); digitalWrite(f,HIGH);
digitalWrite(g,HIGH); digitalWrite(dp,LOW);
}
