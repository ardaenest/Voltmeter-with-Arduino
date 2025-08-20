#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
           
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 20000.0; 
float R2 = 10000.0; 
int value = 0;
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);


void draw(void) 
{
  u8g2.setFont(u8g2_font_bitcasual_t_all);        // Correct font name for U8g2
  u8g2.drawStr(18, 12, "VOLTAGE"); 
  u8g2.setCursor(33, 40);                   // Use setCursor for printing text
  u8g2.drawRFrame(15, 20, 100, 30, 10);      // Correct object name
  u8g2.println(vin);                         // Correct object name
  u8g2.setCursor(u8g2.getCursorX(), u8g2.getCursorY()); // Moves the cursor after printing the value
  u8g2.println("V");
}

void setup(){
    pinMode(analogInput, INPUT);
    u8g2.begin(); 
}

void loop(){
    // read the value at analog input
    value = analogRead(analogInput);
    vout = (value * 5.0) / 1024.0; // see text
    vin = vout / (R2/(R1+R2)); 
    if (vin<0.09) {
    vin=0.0; 
} 
    u8g2.firstPage(); 
    do 
    {
      draw();      
    } while( u8g2.nextPage() );

    delay(500);
}