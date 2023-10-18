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
#define TIMEDISPLAYON 5
#define Switch 3
#define motor 12
#define TMP A3
#define fotodiodo 2

int countDigit = 0;
int countPrimos = 2;
int countImpares = 0;
int temperatura;
int lectura;
int intermitente = 0;
int tiempo1 = 0;
int tiempo2 = 0;
int tiempoSegundos = 0;
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
  tiempo1 = millis();
  Serial.begin(9600);  
}
void loop()
{
  tiempo2 = millis();
  if (tiempo2 > (tiempo1+1000))
  {
    tiempo1 = millis();
    countDigit += 1;
    countPrimos += 1;
    countImpares +=1;
  }
  lectura = analogRead(fotodiodo);
  temperatura = map(analogRead(TMP),0,1023,-5,450);
  int interruptor = digitalRead(Switch);
  if (lectura == 1)// Preunta si el fotodiodo esta encendido
  {
    if (interruptor == 1)// Pregunta si el switch esta en 1
    {
      Serial.println(countDigit);
      printCount(countDigit);
      printDigit(countDigit);// Si es asi prende los leds y muestra el contador
    }
  }
  if (lectura == 0)// Pregunta si el fotodiodo esta apagado
  {
    if (interruptor == 0)// Pregunta si el switch esta en 0
    {
      impares(countImpares);
    }    
  }
  if (temperatura > 60) // Pregunta si el sensor tiene una temperatura mayor a 60
  {
    digitalWrite(12, LOW); // Si es asi se apaga el motor
  }
  else
  {
    digitalWrite(12, HIGH);// Caso contrario se prende el motor
  }
}
void printDigit(int digit) // Funcion encargada de encender el display con la forma del numero que recibe como parametr
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
void prendeDigito(int digito)// //Esta funcion se encarga de separar los numeros por cada display y dandoles el tiempo de prenderse y apagarse
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
void printCount(int count) //Esta funcion recibre como parametro el contador y se encargara de ir sabiendo que numero es es decir del 1 al 99
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
void impares(int num)
{
  if (num % 2 != 0)
  {
	  printCount(countImpares);
      printDigit(countImpares);
  }
}
  