/*
        Protogen specie was created and by Malice-risu on Fur Affinity      
           
           ----------------------------------------------------------
                  arduino protogen face project by Tokageki,	                  
                             You can follow me on : 	                                                         
                             Instagram : @tokagekis
                              Twitter : @Tokageki	                              
           ----------------------------------------------------------

        /!\ You need the LedControl library, don't forget to install it /!\

                                                                                  */



#include "LedControl.h"       //don't forget the ledcontrol library !!!
#include <SoftwareSerial.h>
SoftwareSerial hc06(2, 3);    //creation of a serial port for use a HC-06
String cmd = "happy"; 
   

const byte tiles[][8] = { //creation of an array containing all the expressions
{B00111100,B01111110,B01111110,B01111110,B01111110,B01111110,B01111110,B00111100} // eye normal            0
,
{B00000000,B00000000,B01100000,B11111001,B10011111,B00000110,B00000000,B00000000} // mouth normal 1        1
,
{B00000000,B00011000,B01111110,B11100111,B10000001,B00000000,B00000000,B00000000} // mouth normal 2        2
,
{B00000000,B00000001,B00000111,B10011110,B11111000,B01100000,B00000000,B00000000} // mouth normal 3        3
,
{B00000000,B10000000,B11100000,B01111001,B00011111,B00000110,B00000000,B00000000} // mouth normal 4        4
,
{B00000000,B00000000,B00000110,B10011111,B11111001,B01100000,B00000000,B00000000} // mouth normal 5        5
,
{B00111100,B01111110,B01111110,B01111110,B01111110,B01111110,B00000000,B00000000} // eye anim 1            6
,
{B00111100,B01111110,B01111110,B01111110,B00000000,B00000000,B00000000,B00000000} // eye anim 2            7
,
{B00111100,B01111110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000} // eye anim 3            8
,
{B00111100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000} // eye anim 4            9
,
{B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000} // mouth neutral        10
,
{B00000000,B00010000,B00111000,B01111100,B11111110,B11111110,B01101100,B00000000} // eye heart big        11
,
{B00000000,B00000000,B00010000,B00111000,B01111100,B01101100,B00000000,B00000000} // eye heart small      12
,
{B00111100,B01111110,B01111110,B01111100,B01111001,B01110011,B01100110,B00001100} // eye angry 1          13
,
{B00111100,B01111110,B01111110,B00111110,B10011110,B11001110,B01100110,B00110000} // eye angry 2          14
,
{B00000000,B00000000,B00000000,B01000010,B01100110,B00111100,B00011000,B00000000} // eye ^^               15
,
{B00111110,B00111110,B00111110,B00111110,B00111110,B00111000,B00111000,B00111000} // eye glitched         16
,
{B00000000,B00000110,B01000000,B11111001,B10011001,B00000110,B00000000,B00000000} // mouth glitched 1     17
,
{B00000000,B00001000,B01101110,B11100011,B10000101,B00000000,B00000000,B00000000} // mouth glitched 2     18
,
{B00000000,B00000001,B00000111,B10010110,B11110000,B01000000,B00011000,B00000000} // mouth glitched 3     19
,
{B00001100,B00001100,B01100000,B11100001,B10010111,B00000010,B00000010,B00000000} // mouth glitched 1 A1  20
,
{B00000000,B00000000,B00111000,B10111001,B10000111,B01000110,B01000000,B00000000} // mouth glitched 2 A1  21
,
{B00000000,B00000011,B01001011,B11101100,B10000000,B00001100,B00100100,B00000000} // mouth glitched 3 A1  22
,
{B00000000,B00000000,B00000011,B10001111,B01101110,B01100000,B00000000,B00000000} // mouth glitched 1 A2  23
,
{B00000000,B00001000,B01001010,B11000011,B10110001,B00110000,B00000000,B00000000} // mouth glitched 2 A2  24
,
{B00000000,B00011001,B00011011,B10000110,B11000000,B01010000,B00010000,B00000000} // mouth glitched 3 A2  25
,
{B00111100,B01000010,B10000001,B10000001,B10000001,B10000001,B01000010,B00111100} // eye surprised        26
,
{B00111100,B01111110,B01111110,B00111110,B00011110,B00001110,B00000110,B00000000} // eye sad 1            27
,
{B00111100,B01111110,B01111110,B01111100,B01111000,B01110000,B01100000,B00000000} // eye sad 2            28
,
{B00000000,B10000000,B11000001,B01100011,B00110110,B00011100,B00001000,B00000000} // mouth sad 1          29
,
{B00000000,B00000000,B00000001,B00100011,B01110110,B11011100,B10001000,B00000000} // mouth sad 2          30
,
{B00110000,B00011000,B00001100,B00000110,B00000011,B00000001,B00000000,B00000000} // mouth sad 3          31
,
{B00000000,B00000001,B10000011,B11000110,B01101100,B00111000,B00010000,B00000000} // mouth sad 4          32
,
{B00000000,B00000000,B10000000,B11000100,B01101110,B00111011,B00010001,B00000000} // mouth sad 5          33
,
{B00001100,B00011000,B00110000,B01100000,B11000000,B10000000,B00000000,B00000000} // mouth sad 6          34
,
{B00000000,B01000100,B01001010,B01001010,B01001010,B11100100,B00000000,B00000000} // overheat text 1      35
,
{B00000000,B10100001,B10100010,B11100010,B10100010,B10100001,B00000000,B00000000} // overheat text 2      36
,
{B00000000,B00010010,B10101010,B10101010,B10101010,B00010111,B00000000,B00000000} // overheat text 3      37
,
{B10011000,B11001100,B01100110,B00110011,B00000000,B00000000,B00000000,B00000000} // blush 1              38
,
{B10011001,B11001100,B01100110,B00110011,B00000000,B00000000,B00000000,B00000000} // blush 2              39
,
{B10011001,B00110011,B01100110,B11001100,B00000000,B00000000,B00000000,B00000000} // blush 3              40
,
{B00011001,B00110011,B01100110,B11001100,B00000000,B00000000,B00000000,B00000000} // blush 4              41
,
{B11110111,B11100111,B11001111,B10000001,B00000011,B11100111,B11001111,B11011111} // battery lightning    42
,
{B00000000,B00100100,B00100100,B01111110,B01111110,B00111100,B00011000,B00011000} // battery outlet       43
,
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000} // nothing (really !)   44
,
{B00000000,B00000000,B00000000,B00000011,B00000011,B00000000,B00000000,B00000000} // wait A1              45
,
{B00000000,B00000000,B00000000,B00011011,B00011011,B00000000,B00000000,B00000000} // wait A2              46
,
{B00000000,B00000000,B00000000,B11011011,B11011011,B00000000,B00000000,B00000000} // wait A3              47
,
{B00000000,B00001000,B00011100,B00111110,B01111111,B01111111,B00110110,B00000000} // eye heart big 2      48
, 
{B00000000,B00000000,B00001000,B00011100,B00111110,B00110110,B00000000,B00000000} // eye heart small 2    49
,
{B11111111,B00100100,B00010010,B00100100,B01001000,B00100100,B00010010,B00100100} // eye overheat         50
};



const int matriceNumber = 8; //        <- change THIS number if you use more/less matrices
LedControl lc = LedControl(12, 10, 11, matriceNumber); // ledcontrol(DIN,CLK,LOAD,matriceNumber)
int devices = lc.getDeviceCount();




int lightLevel = 0;
int statut = 0;
int const expressionNbr = 16; //      <- change THIS if you want to add another expression

const String keyWord[] = {"happy", "upset", "love", "angry", "cute", "smug", "glitch", "surprised", "sad", "owo", "overheat", "ormarion", "blush", "battery", "absent", "boot" }; 
// ↑ list of words (once received with the HC-06) must change the leds

const byte faceList[][8] = { 
  {3,2,1,0,0,5,2,6},{10,10,10,6,6,10,10,10},{3,2,1,11,48,5,2,6},{10,10,10,13,14,10,10,10},{3,2,1,15,15,5,2,6},{11,11,17,20,19,17,11,11},{19,17,18,16,16,17,18,19},{10,10,2,26,26,2,10,10}
  ,
  {29,30,31,27,28,34,33,32},{3,2,1,25,25,1,2,3},{37,36,35,50,50,37,36,35},{40,40,41,11,48,38,39,39},{40,40,41,0,0,38,39,39},{10,10,10,42,42,10,10,10},{10,10,10,44,44,10,10,10},{0,0,0,0,0,0,0,0} 
};
// ↑ This array contains which tile each expression should use, such as: faceList[expression id][tile id]
// Expression id list : 0 = happy | 1 = upset | 2 = love | 3 = angry | 4 = cute | 5 = smug | 6 = glitch | 7 = surprised | 8 = sad | 9 = owo | 10 = overheat | 11 = ormarion | 12 = blush | 13 = battery | 14 = absent | 15 = boot


const byte animationId[] = {0, 2, 6, 13, 14}; // contains expressions must need to be animated

const byte nbrFramesAnimations[] = {6, 2, 3, 2, 4};

const byte animationTilesList[][6][8] = { {{3,2,1,6,6,5,2,6},{3,2,1,7,7,5,2,6},{3,2,1,8,8,5,2,6},{3,2,1,9,9,5,2,6},{3,2,1,7,7,5,2,6},{3,2,1,0,0,5,2,6}}
                                          ,
                                          {{3,2,1,12,49,5,2,6},{3,2,1,11,48,5,2,6}}
                                          ,
                                          {{22,20,21,16,16,20,21,22},{18,22,20,16,16,21,19,20},{19,17,18,16,16,17,18,19}}
                                          ,
                                          {{10,10,10,43,43,10,10,10},{10,10,10,42,42,10,10,10}}
                                          ,
                                          {{10,10,10,45,45,10,10,10},{10,10,10,46,46,10,10,10},{10,10,10,47,47,10,10,10},{10,10,10,44,44,10,10,10}}};


const byte animationDelaysBeforePlay[] = {250, 20, 20, 20, 20}; // you just need ton convert your delay into ms and divide by 20 (like 1 sec = 1000ms, 1000/20=50)

int timerBeforePlay = 0;

const int animationDelays[] = {10, 500, 400, 800, 800};

int counter = 0;

const String lightWord[] = {"light0", "light5","light10", "light15"};
// ↑ list of words (once received with the HC-06) must change the brightness


int delayAnimation;








void setup() 
{
  Serial.begin(9600);     
  hc06.begin(9600);                                     // Initialize Bluetooth Serial Port    
  int devices = lc.getDeviceCount();                    // get the number of matrices
  for (int address = 0; address < devices; address++)
  {
    lc.shutdown(address, false);                       // Initialize matrices
    lc.setIntensity(address, 10 );                     // ↑
    lc.clearDisplay(address);                          // ↑ 
  }
  
}


void loop()
{
  for (int address = 0; address < devices; address++) {   
    lc.setIntensity(address, lightLevel ); // set the brightness from the variable "lightlevel"
  }

  while (hc06.available() > 0) {
    cmd += (char)hc06.read(); // Read data from HC06
  }

  if (cmd != "") {   
    for (int i = 0; i < expressionNbr; i++) {      // check if the word in "cmd" matches with a word in "keyWord[]"
        statut = i;                     // ↑
        if (cmd == keyWord[statut]) {   // ↑
            setFace(statut);  // set the expression corresponding to the value of "cmd" (cmd contains the message send with the phone to the Bluetooth module)
            counter = 0;
            timerBeforePlay = 0;
            break;
        }
      
    }
    for (int i = 0; i < 4; i++){    // check if the word in "cmd" matches with a word in "lightword[]"
      if (cmd == lightWord[i]) {    // ↑
        lightLevel = i * 5;
        break;
      }
    }
    cmd = ""; // reset cmd
  }
  


  for (int i = 0; i <= 4; i++){
    int nbr = i;
    if (statut == animationId[nbr]){
      delayAnimation = animationDelays[nbr];
      timerBeforePlay++;
      if (timerBeforePlay > animationDelaysBeforePlay[nbr] && counter == 0){
        setFaceAnimation(nbr, counter);
        counter++;
        while (hc06.available() > 0) {
          cmd += (char)hc06.read(); // Read data from HC06
        }
        if (cmd == ""){
          delay(delayAnimation);
        }
      }
      else if (counter > 0 && counter < nbrFramesAnimations[nbr]){
        setFaceAnimation(nbr, counter);
        counter++;
        while (hc06.available() > 0) {
          cmd += (char)hc06.read(); // Read data from HC06
        }
        if (cmd == ""){
          delay(delayAnimation);
        }
      }
      else if (timerBeforePlay > animationDelaysBeforePlay[nbr]){
        timerBeforePlay = 0;
        counter = 0;
      }
    }
  }
      
}

void setFace(int expressionId)
{
  for ( int matrixId = 0; matrixId < 8; matrixId++) {   
    int tileId = faceList[expressionId][matrixId];  // set the expression corresponding to the value of "statut" for a single matrix (statut is defined with "keyword[]")
    for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(matrixId, ligne, tiles[tileId][ligne]);   // set the expression on the corresponding matrix
    }
  }
}


void setFaceAnimation(int expressionId, int animationExpressionId)
{
  for ( int matrixId = 0; matrixId < 8; matrixId++) {   
    int tileId = animationTilesList[expressionId][animationExpressionId][matrixId];  // set the expression corresponding to the value of "statut" for a single matrix (statut is defined with "keyword[]")
    for ( int ligne = 0; ligne < 8; ligne++) {
      lc.setRow(matrixId, ligne, tiles[tileId][ligne]);   // set the expression on the corresponding matrix
    }
  }
}

