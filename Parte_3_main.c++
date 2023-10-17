#define A 10
#define B 11
#define C 5
#define D 6
#define E 7
#define F 9
#define G 8
#define UNIDAD A4
#define DECENA A5
#define APAGADOS 0
#define TIMEDISPLAYON 200
#define Switch 3
#define motor 12
#define TMP A3
#define fotodiodo 2

int countDigit = 0;
int countPrimos = 2;
int temperatura;
int lectura;
int intermitente = 0;
unsigned long tiempo;
unsigned long tiempo2 = 0;
void setup()
{
  pinMode(Switch, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(UNIDAD, OUTPUT);
  pinMode(DECENA, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(fotodiodo, INPUT_PULLUP); 
  printDigit(0);
  Serial.begin(9600);  
}
void loop()
{
  tiempo = millis();
  //Serial.println(tiempo);
  if (tiempo-tiempo2>=2000)
  {
    tiempo2 = tiempo;
    //Serial.println(tiempo);
  }
  
  lectura = analogRead(fotodiodo);
  //Serial.println(lectura);
  temperatura = map(analogRead(TMP),0,1023,-5,450);
  int interruptor = digitalRead(Switch);
  if (lectura == 1)
  {
    if (interruptor == 1)
    {
      countDigit += 1;
      Serial.println(countDigit);
      printCount(countDigit);
      printDigit(countDigit);
    }
  }
  if (lectura == 0)
  {
    if (interruptor == 0)
    {
      countPrimos += 1;
      delay(500);
      bool primos = num_primos(countPrimos);
      if (primos == true)
      {
        printCount(countPrimos);
      }
    }
  }
  if (temperatura > 60)
  {
    digitalWrite(12, LOW);
  }
  else
  {
    digitalWrite(12, HIGH);
  }
}
void printDigit(int digit)
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  switch (digit)
  {
    case 1:
    
    	digitalWrite(B, HIGH);
    	digitalWrite(C, HIGH);
      	break;
    
    case 2:
    
    	digitalWrite(A, HIGH);
    	digitalWrite(B, HIGH);
    	digitalWrite(D, HIGH);
    	digitalWrite(E, HIGH);
    	digitalWrite(G, HIGH);
      	break;
    
    case 3:
    
    	digitalWrite(A,HIGH);
      	digitalWrite(B,HIGH);
      	digitalWrite(G,HIGH);
      	digitalWrite(C,HIGH);
      	digitalWrite(D,HIGH);
        break;
    
    case 4:
        	digitalWrite(F,HIGH);
      		digitalWrite(G,HIGH);
      		digitalWrite(B,HIGH);
      		digitalWrite(C,HIGH);
      	break;
    case 5:
    
      	digitalWrite(A,HIGH);
      	digitalWrite(F,HIGH);
      	digitalWrite(G,HIGH);
      	digitalWrite(C,HIGH);
      	digitalWrite(D,HIGH);
      	break;
    
    case 6:
    
      	digitalWrite(A,HIGH);
      	digitalWrite(F,HIGH);
      	digitalWrite(G,HIGH);
      	digitalWrite(E,HIGH);
      	digitalWrite(C,HIGH);
      	digitalWrite(D,HIGH);
      	break;
    
    case 7:
    
      	digitalWrite(A,HIGH);
      	digitalWrite(B,HIGH);
      	digitalWrite(C,HIGH);
      	break;
    
    case 8:
    
      	digitalWrite(A,HIGH);
      	digitalWrite(B,HIGH);
      	digitalWrite(C,HIGH);
      	digitalWrite(D,HIGH);
      	digitalWrite(E,HIGH);
      	digitalWrite(F,HIGH);
      	digitalWrite(G,HIGH);
      	break;
    
    case 9:
    
      	digitalWrite(A,HIGH);
      	digitalWrite(F,HIGH);
      	digitalWrite(G,HIGH);
      	digitalWrite(B,HIGH);
      	digitalWrite(C,HIGH);
        break;
    
    case 0:
    
      	digitalWrite(A, HIGH);
      	digitalWrite(B, HIGH);
      	digitalWrite(C, HIGH);
      	digitalWrite(D, HIGH);
      	digitalWrite(E, HIGH);
      	digitalWrite(F, HIGH);
      	break;
    
  }
}
void prendeDigito(int digito)
{
  	if (digito == UNIDAD)
    {
      	digitalWrite(UNIDAD, LOW); 
      	digitalWrite(DECENA, HIGH);
      	digito == DECENA;
      	delay(TIMEDISPLAYON);
    }
  	else if (digito == DECENA)
    {
      	digitalWrite(UNIDAD, HIGH);
      	digitalWrite(DECENA, LOW); 
      	digito == UNIDAD; 
      	delay(TIMEDISPLAYON);
    }
  else
  	{
      	digitalWrite(UNIDAD, HIGH);
      	digitalWrite(DECENA, HIGH);
    	delay(TIMEDISPLAYON);
  	}
}
void printCount(int count) 
{
  prendeDigito(APAGADOS); 
  delay(TIMEDISPLAYON);
  printDigit((int)count/10);
  prendeDigito(DECENA);
  prendeDigito(APAGADOS);
  delay(TIMEDISPLAYON);
  printDigit(count - 10*((int)count/10));
  prendeDigito(UNIDAD);
}
bool num_primos(int num)
{
  if (num <= 1) {
    return false;
  }

  for (int i = 2; i <= num / 2; i++) {
    if (num % i == 0) {
      return false; 
    }
  }
  return true;
}