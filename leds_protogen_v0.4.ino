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
        
                                                                                   */

#include "LedControl.h"
#include <avr/pgmspace.h>

const byte oeil[][8]={   //definition des motifs de la matrice dans un tableau à constance (contrairement à une variable, une constante ne bouge pas [elle reste ... constante])
  {
  B00111100,    //normal oeil         0
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100}
  ,    
{ B00000000,    //normal bouche 1     1
  B00000000,
  B01100000,
  B11111001,
  B10011111,
  B00000110,
  B00000000,
  B00000000} 
  ,
{ B00000000,    //normal bouche 2     2
  B00000000,
  B00000000,
  B10000001,
  B11100111,
  B01111110,
  B00011000,
  B00000000} 
  ,
{ B00000000,    //normal bouche 3     3
  B00000000,
  B00000110,
  B00011111,
  B01111001,
  B11100000,
  B10000000,
  B00000000}
  ,
{ B00000000,    //oeil grand fermé 1  4
  B01000000,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100}  
  ,
{ B00000000,    //oeil oeil moitié 2  5
  B00000000,
  B00000000,
  B01000000,
  B01111110,
  B01111110,
  B01111110,
  B00111100}   
  ,
{ B00000000,    //oeil petit 3         6
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B01111110,
  B00111100}
  ,
{ B00000000,    //oeil fermé 4         7
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B00111110}
  ,   
{ B00000000,    //bouche bouge 1       8
  B00000000,
  B00000001,
  B00000111,
  B10011110,
  B11111000,
  B01100000,
  B00000000} 
  ,
{ B00000000,    //bouche bouge 2       9
  B00000000,
  B00011000,
  B01111110,
  B11100111,
  B10000001,
  B00000000,
  B00000000} 
  ,
{ B00000000,    //bouche bouge 3      10
  B00000000,
  B10000000,
  B11100000,
  B01111001,
  B00011111,
  B00000110,
  B00000000}
  };
int nombreMatrice = 4;
// ledcontrol(DataIn,CLK,LOAD,nombreafficheur)
LedControl lc=LedControl(12,10,11,nombreMatrice);

void setup() {
  int devices=lc.getDeviceCount();                     //recupere le nombre de matrice
  for(int address=0;address<devices;address++) {       //boucle d'initialisation des boucles
    lc.shutdown(address,false);                        //mise en route des afficheurs
    lc.setIntensity(address,0 );                       //Reglage luminosité
    lc.clearDisplay(address);                          // nettoyage matrice, vider
  } 

}

int temps = 0;

void loop() {
  normal();               //set matrix on the normal position
  delay(15000);           //time between animations                                                                                          
  eye_animation();        //start animation of eye
  temps++;
  if(temps==5) {         
    mouth_animation();
    temps=0;
  }
}


void normal(){
   for( int ligne=0; ligne<8; ligne++) {
      for(int afficheur=0; afficheur<4; afficheur++) {
        lc.setRow(0,ligne,oeil[0][ligne]);              //displays on line (defined by ligne variable) of matrix 0, the line in table number 0
        lc.setRow(1,ligne,oeil[1][ligne]);              //displays on line (defined by ligne variable) of matrix 1, the line in table number 1
        lc.setRow(2,ligne,oeil[2][ligne]);              //displays on line (defined by ligne variable) of matrix 2, the line in table number 2
        lc.setRow(3,ligne,oeil[3][ligne]);              //displays on line (defined by ligne variable) of matrix 3, the line in table number 3
      }
    }
}

void mouth_animation(){
      for( int ligne=0; ligne<8; ligne++) {
        lc.setRow(0,ligne,oeil[0][ligne]); 
        lc.setRow(1,ligne,oeil[8][ligne]); 
        lc.setRow(2,ligne,oeil[9][ligne]); 
        lc.setRow(3,ligne,oeil[10][ligne]); 
    }
    delay(1500);
}

void eye_animation(){
    for( int b=4;b<8; b++){
      for( int c=0;c<8;c++){
        lc.setRow(0,c,oeil[b][c]); 
    }
    delay(75);
  }
    for( int c=0;c<8;c++){
     lc.setRow(0,c,oeil[5][c]);
  }
  delay(75);
     for( int c=0;c<8;c++){
     lc.setRow(0,c,oeil[4][c]);
  }
  delay(75);
}
