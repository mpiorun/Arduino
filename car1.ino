#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 
char readChar;

//Definicja pinów, tutaj zmienić w razie potrzeby
#define LEFT_PIN_A 4
#define LEFT_PIN_B 6
#define RIGHT_PIN_A 3
#define RIGHT_PIN_B 5

//Definicja znaków przekazywanych z BT, tutaj zmienić jeśli potrzeba
#define FORWARD 'F' // Do przodu
#define BACKWARD 'B' // Do tyłu
#define LEFT 'L' // W lewo
#define RIGHT 'R' // W prawo
#define STOP 'S' // Zatrzymaj

bool backIsPressed = false;

void setup() {
  BT.begin(57600);
  Serial.begin(9600);
  //Podłączenie silników w zależności od wariantu do l293 lub do modułu HG7881
  pinMode(RIGHT_PIN_A, OUTPUT); 
  pinMode(LEFT_PIN_A, OUTPUT); 
  pinMode(RIGHT_PIN_B, OUTPUT); 
  pinMode(LEFT_PIN_B, OUTPUT); 
}

void loop() {

  if(BT.available()){
    
      readChar = BT.read(); //odczytujemy wartość przesłaną przez BT
      
      switch(readChar){
        case FORWARD: moveForward();break;
        case BACKWARD: moveBackward();break;
        case LEFT: moveLeft();break;
        case RIGHT: moveRight(); break;
        case STOP: moveStop();break;
      }
  }
}

void moveForward(){
  backIsPressed = false;
  Serial.println("moveForward");
  digitalWrite(RIGHT_PIN_A, HIGH);
  digitalWrite(LEFT_PIN_A, HIGH);
  digitalWrite(RIGHT_PIN_B,LOW);
  digitalWrite(LEFT_PIN_B,LOW);
}
void moveBackward(){
  backIsPressed = true;
  Serial.println("moveBackward");
  digitalWrite(RIGHT_PIN_A, LOW);
  digitalWrite(LEFT_PIN_A, LOW);
  digitalWrite(RIGHT_PIN_B, HIGH);
  digitalWrite(LEFT_PIN_B,HIGH);
}
void moveLeft(){
  Serial.println("moveLeft");
  if(backIsPressed){
    digitalWrite(RIGHT_PIN_A, LOW);
    digitalWrite(LEFT_PIN_A, LOW);
    digitalWrite(RIGHT_PIN_B, LOW);
    digitalWrite(LEFT_PIN_B, HIGH);
  } else {
    digitalWrite(RIGHT_PIN_A, LOW);
    digitalWrite(LEFT_PIN_A, HIGH);
    digitalWrite(RIGHT_PIN_B, LOW);
    digitalWrite(LEFT_PIN_B, LOW);
  }
}
void moveRight(){
  Serial.println("moveRight");
  if(backIsPressed){
    digitalWrite(RIGHT_PIN_A,LOW);
    digitalWrite(LEFT_PIN_A,LOW);
    digitalWrite(RIGHT_PIN_B,HIGH);
    digitalWrite(LEFT_PIN_B,LOW);
  } else {
    digitalWrite(RIGHT_PIN_A,HIGH);
    digitalWrite(LEFT_PIN_A,LOW);
    digitalWrite(RIGHT_PIN_B,LOW);
    digitalWrite(LEFT_PIN_B,LOW);
  }
}
void moveStop(){ 
  backIsPressed = false;
  Serial.println("moveStop");
  digitalWrite(RIGHT_PIN_A, LOW);
  digitalWrite(LEFT_PIN_A, LOW);
  digitalWrite(RIGHT_PIN_B, LOW);
  digitalWrite(LEFT_PIN_B, LOW); 
}
