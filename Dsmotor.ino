#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
Servo myservo;
/*
 * AUTHORS NIYOMUKIZA EGIDE && IRANKUNDA FABRICE.
 
  ------ALL PORTS AND VARIABLES INITIALIZATION-------
  SERVO_PIN -> FOR SERVO PIN ON ARDUINO
  LCD_* -> PINS FOR LCD CONNECTION
  PASSWORD -> SECRET KEY TO OPEN THE DOOR
  POS -> POSITION OF THE SERVO MOTOR
*/
int pos=0;
int SERVO_PIN = 7;
int LCD_RS = 13;
int LCD_ENABLE = 12;
int LCD_D4 = 11;
int LCD_D5 = 10;
int LCD_D6 = 9;
int LCD_D7 = 8;
char* password="4567";
int currentposition=0;
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
const byte rows=4;
const byte cols=3;
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={3,2,1,0};
byte colPins[cols]={4,5,6};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
void setup()
{
displayScreen();
myservo.attach(SERVO_PIN); //Servo motor connection
lcd.begin(16,2);
}
 
void loop()
{
if( currentposition==0)
{
displayScreen();
}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
lcd.print("*");
}
 
if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
openDoor();
currentposition=0;
} 
}
else
{
wrongPassword();
currentposition=0;
}}}
 
//--------------- Function - OPEN THE DOOR-------------//
 
void openDoor()
{
delay(1000);
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");

for(pos = 180; pos>=0; pos-=5) // open the door
{
myservo.write(pos); 
delay(5); 
}
delay(2000);
delay(1000);
counterbeep();
delay(1000);
for(pos = 0; pos <= 180; pos +=5) // close the door
{ // in steps of 1 degree
myservo.write(pos); 
delay(15);
currentposition=0;
lcd.clear();
displayScreen();
}
}
 
//--------------------Function- Wrong Password--------------//
 
void wrongPassword()
{
delay(500);
lcd.clear();
lcd.println("*CODE INCORRECT*");
lcd.setCursor(1 ,1);
 
lcd.println("ACCESS DENIED!!");
delay(3000);
lcd.clear();
displayScreen();
}

//-------Function - CLEAR THE SCREEN--------------------/
void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}

//------------Function - DISPLAY FUNCTION--------------------//
void displayScreen()
{
 
lcd.setCursor(0,0);
lcd.println("*ENTER THE CODE*");
lcd.setCursor(1 ,1);
 
lcd.println("TO OPEN DOOR!!");
}

//--------------Function - Count down------------------//
void counterbeep()
{
delay(1200);
lcd.clear();
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(2,0);
delay(200);
lcd.println("GET IN WITHIN:::");
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); //2
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN:");
delay(1000);

lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(2,0);
lcd.println("GET IN WITHIN::");

delay(1000);
delay(40);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
delay(440);
}
