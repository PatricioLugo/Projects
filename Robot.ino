#include <Adafruit_MotorShield.h>


 #include <SoftwareSerial.h>
 #include <Servo.h>

 //Define miBT como nombre del BT y asigna salidas 0 y 1

 SoftwareSerial miBT(0,1);

 //Motores para transmisión 

 Adafruit_DCMotor TransIzq(3, MOTOR34_1KHZ);
 Adafruit_DCMotor TransDer(4, MOTOR34_1KHZ);

 //Motor para giro de brazo
 
 Adafruit_DCMotor GiroBrazo(1, MOTOR12_1KHZ);

//Servos para brazo

Servo Codo;
Servo Garra;

//Variables de posición codo y garra
int co;
int ga;

//Variables de selección de acción
char comando;

//Variable de tiempo
unsigned long tiempo;
unsigned long tiemporef;

//Variable autonomo
int autos=0;
 
void setup() {
  Serial.begin(9600); //ajusta velocidad de serial
  //Serial.println("Listo");//imprime Listo si todo esta correcto
  miBT.begin(38400);//velocidad de comunicación con el BT
  
  Codo.attach(13); //asigna Codo brazo a salida 9
  Garra.attach(9);//asigna Garra brazo a salida 10

  //Posiciona servos en posición inicial 1
  co=5;
  ga=1;
  Codo.write(co);
  Garra.write(ga);
  
}

void loop() {
    if(miBT.available()>0){  //Lee BT y envía a Arduino
      comando=miBT.read();
      Serial.write(comando);//imprime en monitor el valor recibido
      //parar();
      //Serial.println(comando);
    }
      switch(comando){
        case 'E':
          tiemporef=millis();
          Serial.println(tiemporef);
          if (autos==0)
            Autonomo();
          break;
        case 'A':
          avanza();
          break;
        case 'R':
          reversa();
          break;
        case 'I':
          izquierda();
          break;
        case 'D':
          derecha();
          break;
        case 'P':
          parar();
          break;
        case 'S':
          subebrazo();
          break;
        case 'B':
          bajabrazo();
          break;
        case 'C':
          cierragarra();
          break;
        case 'L':
          liberagarra();
          break;
      }
}
void Autonomo(){
  Serial.write("autonomo");
  tiempo=millis();
  Serial.println(tiempo-tiemporef);
  while (tiempo-tiemporef<15000){
    tiempo=millis();
  Serial.println(tiempo);
  Serial.println(tiemporef);
    TransIzq.setSpeed(250);
    TransIzq.run(FORWARD);
    TransDer.setSpeed(250);
    TransDer.run(FORWARD);
    delay(2000);
    TransIzq.setSpeed(0);
    TransIzq.run(RELEASE);
    TransDer.setSpeed(250);
    TransDer.run(FORWARD);
    delay(2000);
    TransIzq.setSpeed(250);
    TransIzq.run(FORWARD);
    TransDer.setSpeed(0);
    TransDer.run(RELEASE);
    delay(2000);
    Codo.write(1);
    for(co=1;co<180;co++){
      Codo.write(co);
      delay(10);
    }
    for(co=180;co>1;co--){
      Codo.write(co);
      delay(10);
    }
    Garra.write(1);
    for(ga=1;ga<180;ga++){
      Garra.write(ga);
      delay(10);
    }
    for(ga=180;ga>1;ga--){
      Garra.write(co);
      delay(10);
    }
  Serial.println(tiempo);
  Serial.println(tiemporef);
  }
  autos=1;
}
void avanza(){
  Serial.write("avanza");
  TransIzq.setSpeed(250);
  TransIzq.run(FORWARD);
  TransDer.setSpeed(250);
  TransDer.run(FORWARD);
}
void reversa(){
  Serial.write("reversa");
  TransIzq.setSpeed(250);
  TransIzq.run(BACKWARD);
  TransDer.setSpeed(250);
  TransDer.run(BACKWARD);
}
void izquierda(){
  TransIzq.setSpeed(250);
  TransIzq.run(BACKWARD);
  TransDer.setSpeed(250);
  TransDer.run(FORWARD);
}
void derecha(){
  TransIzq.setSpeed(250);
  TransIzq.run(FORWARD);
  TransDer.setSpeed(250);
  TransDer.run(BACKWARD);
}
void parar(){
  TransIzq.setSpeed(0);
  TransIzq.run(RELEASE);
  TransDer.setSpeed(0);
  TransDer.run(RELEASE);
}
void subebrazo(){
  if (co<110){
    co=co+1;
    Codo.write(co);
    delay(5);
  }
}
void bajabrazo(){
  if (co>5){
    co=co-1;
    Codo.write(co);
    delay(5);
  }
}
void cierragarra(){
  if (ga<45){
    ga=ga+1;
    Garra.write(ga);
    delay(5);
  }
}
void liberagarra(){
  if (ga>0){
    ga=ga-1;
    Garra.write(ga);
    delay(5);
  }
}
