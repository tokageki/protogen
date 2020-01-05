#include "LedControl.h"

const byte oeil[][4][8]={   //definition des motifs de la matrice dans un tableau à constance (contrairement à une variable, une constante ne bouge pas [elle reste ... constante])
  {
  {
  B00111100,   //normal 0
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100}
  ,    
{ B00000000,
  B00000000,
  B01100011,
  B11111001,
  B10011111,
  B00000110,
  B00000000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000000,
  B10000001,
  B11100111,
  B01111110,
  B00011000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000110,
  B00011111,
  B01111001,
  B11100000,
  B10000000,
  B00000000}
  }
  ,
  {
{ B00000000,    //oeil grand fermé 1
  B01000000,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100}
 ,    
{ B00000000,
  B00000000,
  B01100011,
  B11111001,
  B10011111,
  B00000110,
  B00000000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000000,
  B10000001,
  B11100111,
  B01111110,
  B00011000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000110,
  B00011111,
  B01111001,
  B11100000,
  B10000000,
  B00000000}
  }
  ,
  {
{ B00000000,    //oeil oeil moitié 2
  B00000000,
  B00000000,
  B01000000,
  B01111110,
  B01111110,
  B01111110,
  B00111100}
 ,    
{ B00000000,
  B00000000,
  B01100011,
  B11111001,
  B10011111,
  B00000110,
  B00000000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000000,
  B10000001,
  B11100111,
  B01111110,
  B00011000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000110,
  B00011111,
  B01111001,
  B11100000,
  B10000000,
  B00000000}
  }
  ,
  {
{ B00000000,    //oeil petit 3
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B01111110,
  B00111100}
  ,    
{ B00000000,
  B00000000,
  B01100011,
  B11111001,
  B10011111,
  B00000110,
  B00000000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000000,
  B10000001,
  B11100111,
  B01111110,
  B00011000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000110,
  B00011111,
  B01111001,
  B11100000,
  B10000000,
  B00000000}
  }
  ,
  {
{ B00000000,    //oeil fermé 4
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B00111110}
  ,    
{ B00000000,
  B00000000,
  B01100011,
  B11111001,
  B10011111,
  B00000110,
  B00000000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000000,
  B10000001,
  B11100111,
  B01111110,
  B00011000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00000110,
  B00011111,
  B01111001,
  B11100000,
  B10000000,
  B00000000}
  }
  ,
  {
{ B00111100,   //bouche bouge 5
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100}
  ,    
{ B00000000,
  B00000011,
  B00000001,
  B00000111,
  B10011110,
  B11111000,
  B01100000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B00011000,
  B01111110,
  B11100111,
  B10000001,
  B00000000,
  B00000000} 
  ,
{ B00000000,
  B00000000,
  B10000000,
  B11100000,
  B01111001,
  B00011111,
  B00000110,
  B00000000}
  }
  };

int nombreMatrice = 4;
// ledcontrol(DataIn,CLK,LOAD,nombreafficheur)
LedControl lc=LedControl(12,10,11,nombreMatrice);

void setup() {
  int devices=lc.getDeviceCount();                     //recupere le nombre de matrice
  for(int address=0;address<devices;address++) {       //boucle d'initialisation des boucles
    lc.shutdown(address,false);                        //mise en route des afficheurs
    lc.setIntensity(address,2 );                       //Reglage luminosité
    lc.clearDisplay(address);                          // nettoyage matrice, vider
  } 

}

int temps = 0;

void loop() {
  for( int afficheur=0; afficheur<nombreMatrice; afficheur++) {
    for( int ligne=0; ligne<8; ligne++) {
      lc.setRow(afficheur,ligne,oeil[0][afficheur][ligne]);           //affiche sur la ligne de l'afficheur défini par la var afficheur et ligne, l'élément 0 puis DANS 0 l'élément correspondant à la vaiable afficheur puis Dans afficheur la ligne
    }
  }
  delay(5000);                                                        
  animation();
  temps++;
  if(temps==5) {
    temps=0;
    for( int afficheur=0; afficheur<nombreMatrice; afficheur++) {
      for( int ligne=0; ligne<8; ligne++) {
        lc.setRow(afficheur,ligne,oeil[5][afficheur][ligne]); 
      }
    }
    delay(500);
  }
}

void animation(){
  for( int a=0; a<5; a++){
    for( int b=0;b<nombreMatrice; b++){
      for( int c=0;c<8;c++){
        lc.setRow(b,c,oeil[a][b][c]);
      }    
    }
    delay(75);
  }
  for( int matrice=0; matrice<nombreMatrice; matrice++) {
    for( int barre=0; barre<8; barre++) {
      lc.setRow(matrice,barre,oeil[2][matrice][barre]);
    }
  }
  delay(75);
}
