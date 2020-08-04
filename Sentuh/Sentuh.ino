#include <UTFT.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];



UTFT        myGLCD(ILI9341_16,38,39,40,41); 
URTouch      myTouch(6,5,4,3,2);
UTFT_Buttons  myButtons(&myGLCD, &myTouch);


int pressed_button, butmenu, butdht, butbmp, butldr;

void start()
{
  myButtons.deleteAllButtons();
     //set colour for the title, display title and position on x axis(center) and position on y axis(0, 16)
   
    myGLCD.setColor(0, 0, 255);                         
    myGLCD.print("WEATHER STATION", CENTER, 0);
    myGLCD.print("PROJECT", CENTER, 16); 
//set colour to red, name and sensor names with positions
    myGLCD.setColor(255, 0, 50);                       
    myGLCD.print("By Simon Bradley", CENTER, 32);   
    myGLCD.print("  -DHT22", CENTER, 48);
    myGLCD.print("  -BMP108", CENTER, 64);
    myGLCD.print("  -LDR", CENTER, 80); 
//set colour to green, more names and positions 
    myGLCD.setColor(0, 255, 0);                         
    myGLCD.print("ARDUINO PROJECT", CENTER, 112);
    myGLCD.print("Engineering Science", CENTER, 144);
     butmenu = myButtons.addButton( 10, 180, 300, 30, "Menu");
  myButtons.drawButtons();
 
  while (1)
{
  if (myTouch.dataAvailable() == true)
   
    {
      pressed_button = myButtons.checkButtons();
      if (pressed_button==butmenu)
    {
      menu();
     myButtons.deleteButton(butmenu);
    }
    }
}
}
   




void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myButtons.setTextFont(BigFont);
 

}

void loop()
{
     
  boolean default_colors = true;
 
start();



}       
   

   
         
         

       
   void bmp()
       {
         
         
           myGLCD.clrScr();
          myGLCD.print("BMP", CENTER, 0);
          delay(1000);
         
       }
         
   void ldr()     
      {
         
         
           myGLCD.clrScr();
          myGLCD.print("LDR", CENTER, 0);
          delay(1000);
           
      }
   

 
 
      void menubutton()
   {
 
      if (pressed_button==butmenu)
      myGLCD.clrScr();
    myButtons.deleteButton(butmenu);
     menu();
   }

void menu()
{
   
    myGLCD.clrScr();
      myButtons.deleteButton(butmenu);
          myGLCD.print("Menu", CENTER, 0);
          butdht = myButtons.addButton( 10, 20, 300, 30, "DHT22");
          butbmp = myButtons.addButton( 10, 90, 300, 30, "BMP");
          butldr = myButtons.addButton( 10, 160, 300, 30, "LDR");
          myButtons.drawButtons();
         
            delay(3000);       
          myGLCD.clrScr();
          start();

  if (myTouch.dataAvailable() == true)
    myButtons.enableButton(butdht, true);
    {
      pressed_button = myButtons.checkButtons();
      if (pressed_button==butdht)
    {
      dhtmenu();
     myButtons.deleteButton(butdht);
    }
    }

}



void dhtmenu()

{

          myGLCD.clrScr();
          myGLCD.print("DHT22", CENTER, 0);
          delay(3000);
          menu();
         
}
