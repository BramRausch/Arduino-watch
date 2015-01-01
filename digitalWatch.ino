#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int hour = 0;
int minute = 0;
int done = 0;

void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();
}


void loop() {  
  if(done < 2){
    setTime();
  } else if(done == 2){
    showTime();
  }
  
  Serial.println(done);
}

void setTime(){
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(1);
  display.println("Set time:");
  
  display.setCursor(5,20);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if(hour < 10){
    display.print("0");
  }
  display.print(hour);
  display.print(":");
  if(minute < 10){
    display.print("0");
  }
  display.print(minute);
  display.display();
  
  if(done == 0){
    if(digitalRead(8) == HIGH){
      if(hour < 24){
       hour++;
       delay(200);
      }
    } else if(digitalRead(9) == HIGH){
      if(hour > 0){
        hour--;
        delay(200);
      }
    }
    
    if(digitalRead(6) == HIGH){
      done++;
      delay(200);
    }
  } if(done == 1){
    if(digitalRead(8) == HIGH){
      if(minute <60){
       minute++;
       delay(200);
      }
    } else if(digitalRead(9) == HIGH){
      if(minute > 0){
        minute--;
        delay(200);
      }
    }
    
    if(digitalRead(6) == HIGH){
      done++;
      delay(200);
    }
  }
}

void showTime(){
  if(hour == 23 && minute == 60){
    hour = 0;
    minute = 0;
  }else if(minute == 60 && hour != 23){
    hour++;
    minute = 0;
  }
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(1);
  display.println("Time:");
  
  display.setCursor(5,20);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if(hour < 10){
    display.print("0");
  }
  display.print(hour);
  display.print(":");
  if(minute < 10){
    display.print("0");
  }
  display.print(minute);
  display.display();
  
  delay(60000);
  minute++;
}
