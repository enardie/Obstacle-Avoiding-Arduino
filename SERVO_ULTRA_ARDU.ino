#include <Servo.h>
Servo myservo; 

#define ECHO 3 // Pin that receives the waves (and where the sensor connects to the arudino)
#define TRIGGER 2 // Pin that sends the waves (and where the sensor connects to the arudino)


int obstamax =35; // Maximum obstacle detection in centimeters
int obstamin= 5; // Minimum obstacle detection in centimeters
int i=0; // All numbers are real numbers 

//////////////////////////

int ledPin0 =  11; // pins that connect the H-Bridge to the Arduino and creates them as a variables
int ledPin1 = 10; 
int ledPin2 =  8;
int ledPin3 =  9; 

//////////////////////////

int estado = 0;
int tt = 0; 
int duracion;
int distancia;
int CMD; // Variable for cm to the right
int CMC; // Variable for cm forward
int CMI; // Variable for cm to the left
int CM; // Variables will be in centimeters

int angizq = 170; // How many degrees turned to the left of the servo 
int angdere = 10; // How many degrees turned to the right of the servo
int angcent = 90; // Middle position of the servo
int a = 0;
int velocidad = 200; // How fast wheels turn

//////////////////////////

void setup()
{

myservo.attach(4); // Pins to connect servo to arduino 
  pinMode(ECHO, INPUT); // Received the waves for sensor
  pinMode(TRIGGER, OUTPUT); // Sends the waves for sensor

pinMode(ledPin0, OUTPUT); // The H-Bridge transfers the energy of the wheels to arduino
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);

myservo.write(angcent);
delay(3000); // 3 seconds of looking forward before reacting
motor_stop();
}

void loop() 
{

        leer_obstaculo();// Reads and processes the obstacles
       
}

int DISTACM() // Starts the distance from zero so new screening can take place

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER, LOW); 
  duracion = pulseIn(ECHO, HIGH); // Waves are received by the sensor
  distancia =  (float (duracion))/53;
  delay(5);
  
  return distancia;
  
  
}
//////////////////////////

void motor_stop() // How to treat the wheels if the car has to stop
{
  analogWrite(ledPin0,0); 
  analogWrite(ledPin1,0);
  analogWrite(ledPin2,0);
  analogWrite(ledPin3,0);
}

//////////////////////////

void motor_atras() // Which wheels to use if going backwards
{
   analogWrite(ledPin0,0);
   analogWrite(ledPin1,velocidad);
   analogWrite(ledPin2,0);
   analogWrite(ledPin3,velocidad);
}

//////////////////////////

void motor_adelante() // Which wheels to use if going forward
{
   analogWrite(ledPin0,velocidad);
   analogWrite(ledPin1,0);
   analogWrite(ledPin2,velocidad);
   analogWrite(ledPin3,0);
}

//////////////////////////

void motor_izquierda() // Which wheels to use if going left

        analogWrite(ledPin0,0);
        analogWrite(ledPin1,velocidad);
        analogWrite(ledPin2,velocidad);
        analogWrite(ledPin3,0);
}

//////////////////////////

void motor_derecha() // Which wheels to use if going right
 
        analogWrite(ledPin0,velocidad);
        analogWrite(ledPin1,0);
        analogWrite(ledPin2,0);
        analogWrite(ledPin3,velocidad);
    
}
//////////////////////////

void leer_obstaculo()
{

 CM = DISTACM();// sets function for centimeters
 
if(CM <= obstamax && CM >=obstamin ) //checks if there are obstacles at 35cm of distance

        {
         motor_stop();

         myservo.write(angdere); // Servomotor right
         delay(500); // Waits 5 seconds
         
         CMD = DISTACM();// Checks how many cm are permitted 
         
         myservo.write(angizq);//servomotor right
         delay(1000);
         
         CMI = DISTACM();// Checks how many cm are permitted 
         
          if(CMI > CMD)// if there's an obstacle to the right
          {
           myservo.write(angcent); // Servo 180 degrees to the left
           delay(1000);
           motor_derecha(); // car moves to the left
           delay(3000);  
          }
          
          if(CMI < CMD) // If there's an obstacle to the left
          
          {
           myservo.write(angcent); // Servo 180 degrees to the right
           delay(1000);
           motor_izquierda(); // Car moves to the right
           delay(3000);
          }
        }
        
//////////////////////////

  else 
  
   { motor_adelante(); // If there's nothing to the sides, then car continues forward  }
   
  }
