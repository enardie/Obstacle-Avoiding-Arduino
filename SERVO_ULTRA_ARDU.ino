#include <Servo.h>
Servo myservo; 

#define ECHO 3       // Pin para recibir el pulso de eco
#define TRIGGER 2 //2     // Pin para enviar el pulso de disparo


int obstamax =35;//14
int obstamin= 5;//2
int i=0;
////////////////////////////////////////



//////////////////////////////////
int ledPin0 =  11; 
int ledPin1 = 10; 
int ledPin2 =  8;
int ledPin3 =  9; 

//////////////////////////

int kk = 0; 
int dato1=0;
int dato2=0;
int dato3=0;
//////////////////////////
int estado =0; 
int tt = 0; 
int duracion;
int distancia;
int CMD;
int CMC;
int CMI;
int CM;

int angizq= 170;//150
int angdere= 10;//20
int angcent=90;//90
int a = 0;
int velocidad =200;//  255

void setup()
{

myservo.attach(4);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);

pinMode(ledPin0, OUTPUT);
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);

myservo.write(angcent);
delay(3000);
motor_stop();
}

void loop() 
{

        leer_obstaculo();// lee distancia y almacena obstaculo
       
}

int DISTACM()//funcion que regresa un valor entero de la distancia para su comparacion
{
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW); 
  duracion = pulseIn(ECHO, HIGH); //Medición del ancho de pulso recibido en el pin Echo
  distancia =  (float (duracion))/53;
  delay(5);
  
  return distancia;
  
  
}
////////////////////////////////////////////////
void motor_stop()
{
  analogWrite(ledPin0,0);//motor parado
  analogWrite(ledPin1,0);
  analogWrite(ledPin2,0);
  analogWrite(ledPin3,0);
}
/////////////////////////////////////////////////
void motor_atras()
{
   analogWrite(ledPin0,0);//atras
   analogWrite(ledPin1,velocidad);
   analogWrite(ledPin2,0);
   analogWrite(ledPin3,velocidad);
}
////////////////////////////////////////////////
void motor_adelante()
{
   analogWrite(ledPin0,velocidad);//adelante
   analogWrite(ledPin1,0);
   analogWrite(ledPin2,velocidad);
   analogWrite(ledPin3,0);
}
//////////////////////////////////
void motor_izquierda()//gerena un pequeño tiempo girando debe parar
{
        analogWrite(ledPin0,0);
        analogWrite(ledPin1,velocidad);
        analogWrite(ledPin2,velocidad);
        analogWrite(ledPin3,0);
   
  
}
//////////////////////////////////
void motor_derecha()//gerena un pequeño tiempo girando debe parar
{
 
        analogWrite(ledPin0,velocidad);
        analogWrite(ledPin1,0);
        analogWrite(ledPin2,0);
        analogWrite(ledPin3,velocidad);
    
}
//////////////////////////////////
void leer_obstaculo()
{

 CM = DISTACM();//lee la funcion de leer los centimetros
 
if(CM <= obstamax && CM >=obstamin )//verifica si hay obstaculos menos a 35 cm
        {
 
         
         motor_stop();

         myservo.write(angdere);//servomotor derecha
         delay(500);//1000
         CMD = DISTACM();//lee la funcion de leer los centimetros
         myservo.write(angizq);//servomotor derecha
         delay(1000);
         CMI = DISTACM();//lee la funcion de leer los centimetros
         
          if(CMI > CMD)//HAY OBSTA EN DERECHA
          {
           myservo.write(angcent);//servomotor en 180 grados izquierda
           delay(1000);

        
           motor_derecha();
           delay(3000);

          
          
           
          }
          if(CMI < CMD)//OBSTA IZQ
          {
           myservo.write(angcent);//servomotor en 180 grados izquierda
           delay(1000);


           
           motor_izquierda();
           delay(3000);//1000
          
           
          
          }
        }
//////////////////////////////////////

  else 
   {
   
      motor_adelante();
      

   }
  }
 

