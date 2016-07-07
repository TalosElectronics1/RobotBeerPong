//Sensor ultrasonico Izquierda
#define SI_Echo    13    // Pin de Eco
#define SI_Trig    12    // Pin de Disparo

//Sensor ultrasonico Centro
#define SC_Echo    11    // Pin de Eco
#define SC_Trig    10    // Pin de Disparo

//Sensor ultrasonico Derecha
#define SD_Echo    9    // Pin de Eco
#define SD_Trig    8    // Pin de Disparo

//Sensor Optico
#define Optico    7    // Sensor Optico

//Motores
#define Motor1A   3    // Señal A Motor 1 
#define Motor1B   2    // Señal B Motor 1 
#define Motor2A   4    // Señal A Motor 2 
#define Motor2B   5    // Señal B Motor 2  
#define MotorE    6    // Señal Enable Motor 1 y 2 

void Adelante();  
void Atras();  
void Derecha();
void Izquierda();
void Detenido();
void Aleatorio();

long lduration_SI   = 0;
long ldistance_SI   = 0;
long lduration_SC   = 0;
long ldistance_SC   = 0;
long lduration_SD   = 0;
long ldistance_SD   = 0;

int nAleatorio = 0;
int nContador = 0;

void setup() 
{  
  //Configuración Sensor Ultrasonico Izquierda
  pinMode(SI_Trig, OUTPUT);
  pinMode(SI_Echo, INPUT); 

  //Configuración Sensor Ultrasonico Centro
  pinMode(SC_Trig, OUTPUT);
  pinMode(SC_Echo, INPUT); 

  //Configuración Sensor Ultrasonico Derecha
  pinMode(SD_Trig, OUTPUT);
  pinMode(SD_Echo, INPUT); 

  //Configuración motores
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor2B, OUTPUT);  
  pinMode(MotorE, OUTPUT);  

  Serial.begin(9600);
}

void loop() 
{ 
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //    Genera una señal PWM en una escala de 0 a 255, sirve para regular la velucidad de los motores a pasos   //
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  analogWrite(MotorE, 200);            
  
  while(1)
  {
      ////////////////////////////////////////////////////////////////
      //    Mide la distancia a la que se encuentra el obstaculo    //
      ////////////////////////////////////////////////////////////////
      
      digitalWrite(SI_Trig, LOW);               
      delayMicroseconds(2); 
      digitalWrite(SI_Trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(SI_Trig, LOW);
      lduration_SI = pulseIn(SI_Echo, HIGH);
      ldistance_SI =  (lduration_SI/2) / 29.1;
      Serial.print("UI: ");
      Serial.print(ldistance_SI);
      Serial.print("\t");

      digitalWrite(SC_Trig, LOW);               
      delayMicroseconds(2); 
      digitalWrite(SC_Trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(SC_Trig, LOW);
      lduration_SC = pulseIn(SC_Echo, HIGH);
      ldistance_SC =  (lduration_SC/2) / 29.1;
      Serial.print("UC: ");
      Serial.print(ldistance_SC);
      Serial.print("\t");

      digitalWrite(SD_Trig, LOW);               
      delayMicroseconds(2); 
      digitalWrite(SD_Trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(SD_Trig, LOW);
      lduration_SD = pulseIn(SD_Echo, HIGH);
      ldistance_SD =  (lduration_SD/2) / 29.1;
      Serial.print("UD: ");
      Serial.print(ldistance_SD);
      Serial.print("\n");

      if(nContador > 50)
      {
        Aleatorio(); 
        nContador = 0; 
      }
        nContador++;

      //////////////////////////////////////
      //    Algoritmo evasor de bordes    //
      //////////////////////////////////////
      
      if     (ldistance_SI < 15 && ldistance_SC < 15 && ldistance_SD < 15)  // Mesa && Mesa && Mesa
      {      
          if     (nAleatorio == 0 || nAleatorio == 2)  
          {
              Adelante();
          }
          else if(nAleatorio == 1)
          {
              Izquierda();
          }
          else if(nAleatorio == 3)
          {
              Derecha();
          }
          Serial.print("Mesa  && Mesa  && Mesa \n");
      }
      else if(ldistance_SI < 15 && ldistance_SC < 15 && ldistance_SD > 15)  // Mesa && Mesa && Vacio
      {   
          Atras();
          delay(20);            
          Izquierda();
          delay(20);
          Serial.print("Mesa  && Mesa  && Vacio\n");
      }
      else if(ldistance_SI < 15 && ldistance_SC > 15 && ldistance_SD < 15)  // Mesa && Vacio && Mesa
      {     
          Adelante();
          Serial.print("Mesa  && Vacio && Mesa \n");  
      }
      else if(ldistance_SI < 15 && ldistance_SC > 15 && ldistance_SD > 15)  // Mesa && Vacio && Vacio
      {        
          Adelante();
          Serial.print("Mesa  && Vacio && Vacio\n");
      }
      else if(ldistance_SI > 15 && ldistance_SC < 15 && ldistance_SD < 15)  // Vacio && Mesa && Mesa
      {   
          Atras();
          delay(10);               
          Derecha();
          delay(10);
          Serial.print("Vacio && Mesa  && Mesa \n");
      }
      else if(ldistance_SI > 15 && ldistance_SC < 15 && ldistance_SD > 15)  // Vacio && Mesa && Vacio
      {                  
          Atras();
          Serial.print("Vacio && Mesa  && Vacio\n");
      }
      else if(ldistance_SI > 15 && ldistance_SC > 15 && ldistance_SD < 15)  // Vacio && Vacio && Mesa
      {                  
          Adelante();
          Serial.print("Vacio && Vacio && Mesa \n");
      }
      else if(ldistance_SI > 15 && ldistance_SC > 15 && ldistance_SD > 15)  // Vacio && Vacio && Vacio 
      {                  
          Detenido();
          Serial.print("Vacio && Vacio && Vacio\n");
      }
   }
}

void Adelante()
{
  digitalWrite(Motor1A, HIGH); 
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, HIGH); 
  digitalWrite(Motor2B, LOW);
  Serial.print("Adelante  \t");
}
void Atras()
{
  digitalWrite(Motor1A, LOW); 
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2A, LOW); 
  digitalWrite(Motor2B, HIGH);
  Serial.print("Atras     \t");
}
void Derecha()
{
  digitalWrite(Motor1A, LOW); 
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2A, HIGH); 
  digitalWrite(Motor2B, LOW);
  Serial.print("Derecha   \t");
}
void Izquierda()
{
  digitalWrite(Motor1A, HIGH); 
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW); 
  digitalWrite(Motor2B, HIGH);
  Serial.print("Izquierda \t");
}
void Detenido()
{
  digitalWrite(Motor1A, LOW); 
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW); 
  digitalWrite(Motor2B, LOW);
  Serial.print("Detenido  \t");
}
void Aleatorio()
{
  if(nAleatorio == 0)  
  {          
    nAleatorio = 1;
  }
  else if(nAleatorio == 1)  
  {          
    nAleatorio = 2;
  }
  else if(nAleatorio == 2)  
  {          
    nAleatorio = 3;
  }
  else if(nAleatorio == 3)  
  {          
    nAleatorio = 0;
  }
  
}

