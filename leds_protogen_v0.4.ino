/*     
      d8888b. d8888b.  .d88b.  d888888b  .d88b.   d888b  d88888b d8b   db 
      88  `8D 88  `8D .8P  Y8. `~~88~~' .8P  Y8. 88' Y8b 88'     888o  88 
      88oodD' 88oobY' 88    88    88    88    88 88      88ooooo 88V8o 88 
      88~~~   88`8b   88    88    88    88    88 88  ooo 88~~~~~ 88 V8o88 
      88      88 `88. `8b  d8'    88    `8b  d8' 88. ~8~ 88.     88  V888 
      88      88   YD  `Y88P'     YP     `Y88P'   Y888P  Y88888P VP   V8P 
          Protogen specie was created by Malice-risu on Fur Affinity      
           
           ----------------------------------------------------------
                  arduino protogen face project by Tokageki,
                             You can follow me on : 
                             Instagram : @tokagekis
                              Twitter : @Tokageki
           ----------------------------------------------------------
           
        /!\ You need the LedControl library, don't forget to install it /!\
        
  


#include "LedControl.h"
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3);
String cmd = "happy";
float sensor_val = 0;

const byte oeil[][8] = { //definition des motifs de la matrice dans un tableau à constance (contrairement à une variable, une constante ne bouge pas [elle reste ... constante])
  {
    B00111100,    //normal oeil         0
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00111100
  }
  ,
  { B00000000,    //normal bouche 1     1
    B00000000,
    B01100000,
    B11111001,
    B10011111,
    B00000110,
    B00000000,
    B00000000
  }
  ,
  { B00000000,    //normal bouche 2     2
    B00011000,
    B01111110,
    B11100111,
    B10000001,
    B00000000,
    B00000000,
    B00000000
  }
  ,
  { B00000000,    //normal bouche 3     3
    B00000001,
    B00000111,
    B10011110,
    B11111000,
    B01100000,
    B00000000,
    B00000000
  }
  ,
  { B00111100,    //oeil grand fermé    4
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00000000,
    B00000000
  } 
  ,
  { B00111100,    //oeil grand fermé 2  5
    B01111110,
    B01111110,
    B01111110,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
  ,
  { B00111100,    //oeil petit 3         6
    B01111110,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
  ,
  { B01111110,    //oeil fermé 4         7
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
  ,
  { B00000000,    //bouche bouge 1       8
    B00000000,
    B10000001,
    B11100111,
    B01111110,
    B00011000,
    B00000000,
    B00000000
  }
  ,
  { B00000000,    //bouche bouge 2       9
    B00000000,
    B10000000,
    B11100000,
    B01111001,
    B00011111,
    B00000110,
    B00000000
  }
  ,
  { B00000000,    //bouche bouge 3      10
    B00000000,
    B00011000,
    B01111110,
    B11100111,
    B10000001,
    B00000000,
    B00000000
  }
  ,
  { B00000000,    //bouche neutre       11
    B00000000,
    B00000000,
    B11111111,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
  }
  ,
  { B00111100,    //oeil neutre         12
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B01111110,
    B00000000,
    B00000000
  }
  ,
  { B00000000,    //oeil amoureux       13
    B00010000,
    B00111000,
    B01111100,
    B11111110,
    B11111110,
    B01101100,
    B00000000
  }
  ,
  { B00111100,    //oeil faché          14
    B01111110,
    B01111110,
    B01111100,
    B01111001,
    B01110011,
    B01100110,
    B00001100
  }
  ,
  { B00000000,    //oeil coeur animation 15
    B00000000,
    B00010000,
    B00111000,
    B01111100,
    B01101100,
    B00000000,
    B00000000
  }
  ,
  { B00111100,    //faché côté 2         16
    B01111110,
    B01111110,
    B00111110,
    B10011110,
    B11001110,
    B01100110,
    B00110000
  }  
  ,
  { B00011000,    //bouche content bout  17 
    B00111100,
    B01100110,
    B11000011,
    B10000001,
    B00000000,
    B00000000,
    B00000000
  }
  ,
  {
    B00000000,    //oeil ^w^             18
    B00000000,
    B00000000,
    B01000010,
    B01100110,
    B00111100,
    B00011000,
    B00000000
  }
  ,
  {
    B00000000,    //oeil smug            19
    B00000000,
    B00001100,
    B00011110,
    B10011110,
    B10001101,
    B01111110,
    B00000000
  }
  ,
  {
    B00000000,    //oeil smug 2          20
    B00000000,
    B00110000,
    B01111000,
    B11111000,
    B10110001,
    B01111110,
    B00000000
  }  
  ,
  { B00111110,    //buggé oeil           21
    B00111110,
    B00111110,
    B00111110,
    B00111110,
    B00111000,
    B00111000,
    B00111000
  }
  ,
  { B00000000,    //buggé bouche         22
    B10000000,
    B00100101,
    B11110010,
    B10011111,
    B00100010,
    B00000000,
    B00000000
  }
  ,
  { 
    B00100000,    //buggé bouche 2       23
    B00001000,
    B01111110,
    B10100011,
    B11001101,
    B01000000,
    B00000000,
    B00000000 
},{
    B00000000,    //buggé bouche 3       24
    B00010010,
    B00010100,
    B01001111,
    B11111100,
    B01000000,
    B00110000,
    B00000000
  }
  ,
  {
    B00111100,    //oeil étonné           25
    B01000010,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B01000010,
    B00111100
   }
   ,
   {
    B00111100,    //oeil triste           26
    B01111110,
    B01111110,
    B00111110,
    B00011110,
    B00001110,
    B00000110,
    B00000000
   }
   ,
   {
    B00000000,    //bouche 1 triste       27
    B10000000,
    B11000001,
    B01100011,
    B00110110,
    B00011100,
    B00001000,
    B00000000
   }
   ,
   {
    B00000000,    //bouche 2 triste       28
    B00000000,
    B00000001,
    B00100011,
    B01110110,
    B11011100,
    B10001000,
    B00000000
   }
   ,
   {
    B00110000,    //bouche 3 triste       29
    B00011000,
    B00001100,
    B00000110,
    B00000011,
    B00000001,
    B00000000,
    B00000000
   }
   ,
   {
    B00111100,    //oeil 2 triste         30
    B01111110,
    B01111110,
    B01111100,
    B01111000,
    B01110000,
    B01100000,
    B00000000
   }
   ,
   {
    B00000000,    //bouche 1 triste 2     31
    B00000001,
    B10000011,
    B11000110,
    B01101100,
    B00111000,
    B00010000,
    B00000000
   }
   ,
   {
    B00000000,    //bouche 2 triste 2     32
    B00000000,
    B10000000,
    B11000100,
    B01101110,
    B00111011,
    B00010001,
    B00000000
   }
   ,
   {
    B00001000,    //bouche 3 triste 2     33
    B00011000,
    B00110000,
    B01100000,
    B11000000,
    B10000000,
    B00000000,
    B00000000
   }
   ,
   {
    B11111111,    //trop chaud oeil      34
  B00100100,
  B01001000,
  B00100100,
  B00010010,
  B00100100,
  B01001000,
  B00100100
   }
   , 
   {
    B00000000,    //trop chaud bouche 1  35
  B01000100,
  B01001010,
  B01001010,
  B01001010,
  B11100100,
  B00000000,
  B00000000
   }
   ,
   {
    B00000000,    //trop chaud bouche 2   36
  B10100001,
  B10100010,
  B11100010,
  B10100010,
  B10100001,
  B00000000,
  B00000000
   }
   ,
   {
    B00000000,    //trop chaud bouche 3   37
  B00010010,
  B10101010,
  B10101010,
  B10101010,
  B00010111,
  B00000000,
  B00000000
   }
   ,
   {
   B10011000,     //bouche orma 1         38
  B11001100,
  B01100110,
  B00110011,
  B00000000,
  B00000000,
  B00000000,
  B00000000
   }
   , 
   {
   B10011001,     //orma bouche 2          39
  B11001100,
  B01100110,
  B00110011,
  B00000000,
  B00000000,
  B00000000,
  B00000000
   }
   ,
   {
    B10011001,    //orma bouche 3          40
  B00110011,
  B01100110,
  B11001100,
  B00000000,
  B00000000,
  B00000000,
  B00000000
   }
   ,
   {
    B00011001,    //orma bouche 4          41
  B00110011,
  B01100110,
  B11001100,
  B00000000,
  B00000000,
  B00000000,
  B00000000
   }
   ,
   {
  B01111110,    //oeil batterie            42
  B01000010,
  B01011010,
  B01000010,
  B01011010,
  B01000010,
  B01011010,
  B01000010
},{
  B01111110,                              //43
  B01000010,
  B01011010,
  B01000010,
  B01011010,
  B01000010,
  B01000010,
  B01000010
},{
  B01111110,                              //44
  B01000010,
  B01011010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010
},{
  B01111110,                              //45
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010,
  B01000010
   }
   ,
   {
    B00000000,    //vide                    46
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{ 
  B00000000,      // points 1               47
  B00000000,
  B00000000,
  B00000011,
  B00000011,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,      // points 2               48
  B00000000,
  B00011011,
  B00011011,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,      // points 3               49
  B00000000,
  B11011011,
  B11011011,
  B00000000,
  B00000000,
  B00000000
   }
};

int nombreMatrice = 8;
// ledcontrol(DataIn,CLK,LOAD,nombreafficheur)
LedControl lc = LedControl(12, 10, 11, nombreMatrice);

void setup() {
  //Initialize Serial Monitor
  Serial.begin(9600);
  //Initialize Bluetooth Serial Port
  hc06.begin(9600);
  int devices = lc.getDeviceCount();                   //recupere le nombre de matrice
  for (int address = 0; address < devices; address++) { //boucle d'initialisation des boucles
    lc.shutdown(address, false);                       //mise en route des afficheurs
    lc.setIntensity(address, 0 );                      //Reglage luminosité
    lc.clearDisplay(address);                          // nettoyage matrice, vider
  }

}


int devices = lc.getDeviceCount();
int etat = 0;   //0=content 1=neutre 2=amoureux 3=faché 4=owo 5=smug 6=glitch 7=surpris 8=triste 9=owo 10=overheat 11=ormarion 12=blush 13=batterie 14=absent
int compteur = 0;
int compteuramour = 0;
int compteur_bouche = 0;
int lumiere = 0;


void loop() {
    if ((etat == 0 ) && (compteur>=80)) {
      compteur=0;
      eye_animation();
      normal();
    }
    if ((etat == 6 ) && (compteur>=10)) {
      compteur=0;
      glitch_anim();
      glitch();
    }
    if ((etat == 13 ) && (compteur>=5)) {
      battery_anim();
      compteur=0;
    }
    if ((etat == 14 ) && (compteur>=5)) {
      absent_anim();
      compteur=0;
      absent();
    }
    if ((etat == 2 ) && (compteur>=10)) {
      compteur=0;
      coeur_animation();
      amoureux();
    }
    if ((etat == 11 ) && (compteur>=5)) {
      compteur=0;
      coeur_animation();
      ormarion();
    }
    if ((etat == 0 ) && (compteur_bouche>=400)) {
      compteur_bouche=0;
      mouth_animation();
      normal();
    }
    if (etat == 0) {
      compteur++;
      compteur_bouche++;
      delay(50);
    }
    
    if (etat == 6) {
      compteur++;
      delay(50);
    }

    if (etat == 13) {
      compteur++;
      delay(50);
    }

    if (etat == 14) {
      compteur++;
      delay(50);
    }
    
    if (etat == 2) {
      compteur++;
      delay(100);
      }
    if (etat == 11) {
      compteur++;
      delay(100);
      }
      
  int devices = lc.getDeviceCount();
  for (int address = 0; address < devices; address++) {
    lc.setIntensity(address, lumiere );
  }
  //Read data from HC06
  while (hc06.available() > 0) {
    cmd += (char)hc06.read();
  }
  //Select function with cmd
  if (cmd != "") {
    Serial.print("Command recieved : ");
    Serial.println(cmd);
    // We expect ON or OFF from bluetooth
    
    if (cmd == "happy") {
      normal();
      etat=0;
    }
    else if (cmd == "upset") {
      neutre();
      etat=1;
    }
    else if (cmd == "love") {
      amoureux();
      etat=2;
    }
    else if (cmd == "angry") {
      fache();
      etat=3;
    }
    if (cmd == "cute") {
      cute();
      etat=4;
    }
    if (cmd == "smug") {
      smug();
      etat=5;
    }
    if (cmd == "glitch") {
      glitch();
      etat=6;
    }
    if (cmd == "surprised") {
      surprised();
      etat=7;
    }
    if (cmd == "sad") {
      sad();
      etat=8;
    }
    if (cmd == "owo") {
      owo();
      etat=9;
    }
    if (cmd == "overheat") {
      overheat();
      etat=10;
    }
    if (cmd == "ormarion") {
      ormarion();
      etat=11;
    }
    if (cmd == "blush") {
      blush();
      etat=12;
    }
    if (cmd == "battery") {
      battery();
      etat=13;
    }
    if (cmd == "absent") {
      absent();
      etat=14;
    }
    if (cmd == "lumiere0") {
      lumiere = 0;
    }
    if (cmd == "lumiere5") {
      lumiere = 5;
    }
    if (cmd == "lumiere10") {
      lumiere = 10;
    }
    if (cmd == "lumiere15") {
      lumiere = 15;
    }
    cmd = ""; //reset cmd
  }
  // Simulate sensor measurement
  sensor_val = (float)random(256); // random number between 0 and 255

  //Write sensor data to HC06
  hc06.print(sensor_val);
  delay(100);
}


void normal() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[3][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[2][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[1][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[0][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[0][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[1][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[2][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[3][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}
void battery() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[42][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[42][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void absent() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[46][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[46][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void ormarion() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[40][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[40][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[41][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[13][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[13][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[38][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[39][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[39][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void blush() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[40][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[40][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[41][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[0][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[0][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[38][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[39][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[39][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}


void overheat() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[37][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[36][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[35][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[34][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[34][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[37][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[36][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[35][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void owo() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[3][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[2][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[1][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[25][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[25][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[1][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[2][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[3][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void surprised() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[17][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[25][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[25][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[17][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void sad() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[27][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[28][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[29][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[26][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[30][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[33][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[32][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[31][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void glitch() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[23][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[22][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[21][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[21][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[23][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[22][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void glitch_anim() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[22][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[23][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[21][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[21][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[23][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[22][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
  delay(200);
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[22][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[21][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[21][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[24][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[22][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[23][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
  delay(200);
}

void battery_anim() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[42][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[42][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[43][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[43][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[44][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[44][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[45][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[45][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
}

void absent_anim() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[47][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[47][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[48][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[48][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[49][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[49][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
  }
  delay(500);
}

void smug() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[17][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[20][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[19][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[17][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void amoureux() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[3][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[2][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[1][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[13][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[13][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[1][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[2][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[3][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void coeur_animation() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(3, ligne, oeil[15][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 
      lc.setRow(4, ligne, oeil[15][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 
      
  }
  delay(400);
}

void fache() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[14][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[16][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void neutre() {
  for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(1, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(2, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(3, ligne, oeil[12][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      lc.setRow(4, ligne, oeil[12][ligne]);            //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
      lc.setRow(5, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
      lc.setRow(6, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
      lc.setRow(7, ligne, oeil[11][ligne]);            //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
  }
}

void mouth_animation() {
  for ( int ligne = 0; ligne < 8; ligne++) {
    lc.setRow(0, ligne, oeil[10][ligne]);
    lc.setRow(1, ligne, oeil[9][ligne]);
    lc.setRow(2, ligne, oeil[8][ligne]);
    lc.setRow(3, ligne, oeil[0][ligne]);
    lc.setRow(4, ligne, oeil[0][ligne]);
    lc.setRow(5, ligne, oeil[8][ligne]);
    lc.setRow(6, ligne, oeil[9][ligne]);
    lc.setRow(7, ligne, oeil[10][ligne]);
  }
  delay(1500);
}

void cute() {
    for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(0, ligne, oeil[3][ligne]);            
      lc.setRow(1, ligne, oeil[2][ligne]);           
      lc.setRow(2, ligne, oeil[2][ligne]);         
      lc.setRow(3, ligne, oeil[18][ligne]);          
      lc.setRow(4, ligne, oeil[18][ligne]);        
      lc.setRow(5, ligne, oeil[2][ligne]);            
      lc.setRow(6, ligne, oeil[2][ligne]);            
      lc.setRow(7, ligne, oeil[3][ligne]);            
  }
}

    

  
void eye_animation() {
  for ( int b = 4; b < 8; b++) {
    for ( int c = 0; c < 8; c++) {
      lc.setRow(3, c, oeil[b][c]);
      lc.setRow(4, c, oeil[b][c]);
    }
    delay(50);
  }
  for ( int c = 0; c < 8; c++) {
    lc.setRow(3, c, oeil[5][c]);
    lc.setRow(4, c, oeil[5][c]);
  }
  delay(50);
  for ( int c = 0; c < 8; c++) {
    lc.setRow(3, c, oeil[4][c]);
    lc.setRow(4, c, oeil[4][c]);
  }
  delay(50);
  for ( int c = 0; c < 8; c++) {
    lc.setRow(3, c, oeil[0][c]);
    lc.setRow(4, c, oeil[0][c]);
  }
}
