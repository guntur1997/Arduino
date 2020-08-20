/*
 * Contoh program running text menggunakan 1 panel P10 dan APK android sederhana
 * Apabila ada yg kurang jelas bisa di diskusikan dengan saya melalui kontak dibawah
 * Atau anda ingin memesan project arduino / IoT / android bisa hubungi dengan saya (berbayar)
 * 
 * WA : 0895410918382
 * IG : @gunturagustap / @karyatronika.bali
 * FB : Guntur Agusta Pratama
 */

#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

#define maxChar 100 


char pesan[maxChar];    
char readChar;               
byte index = 0;            
int i;            

void ScanDMD(){ 
  dmd.scanDisplayBySPI();
}



void setup(void){

  Serial.begin(9600);
  Timer1.initialize(5000);           
  Timer1.attachInterrupt(ScanDMD);
  //dmd.clearScreen(true);   
  dmd.clearScreen(true);
  dmd.selectFont(SystemFont5x7);
  dmd.drawMarquee("Selamat Datang Di Chanel YT Guntur Agusta ", 41,(32*DISPLAYS_ACROSS)-1 ,0);
  long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+30) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }
  
}

void loop(void){
   if(Serial.available()){       
        for(i=0; i<99; i++){
            pesan[i] = '\0';
        }      
        index=0;
    }

    while(Serial.available() > 0){
       if(index < (maxChar-1)) 
       {         
           readChar = Serial.read();      
           pesan[index] = readChar;     
           index++;                     
           pesan[index] = '\0';       
       }
   }

   dmd.clearScreen(true);
   dmd.selectFont(Arial_black_16);
   dmd.drawMarquee(pesan, maxChar,(32*DISPLAYS_ACROSS)-1 ,0);
   Serial.print(pesan);
 
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+30) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }
}
