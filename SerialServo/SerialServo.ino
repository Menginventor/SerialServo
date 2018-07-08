/*
  Controller Servo signal via serial monitor.
  By Dhamdhawach Horsuwan
  2 July 2018 Bangkok Thailand
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo


float crr_val = 0;
float set_val = 0;
unsigned long timer = millis();
void setup() {
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  Serial.begin(115200);

  Serial.println(F("Serial Servo Begin Please enter value (0 - 100) with NL"));

}

void loop() {
  static String dataStr = "";
  if (Serial.available() > 0) {
    char charIn = Serial.read();
    if ((charIn == '\r' || charIn == '\n') ) {
      if (dataStr.length() > 0) {
        Serial.print("rx:");
        Serial.println(dataStr);

        if (strIsNum(dataStr)) {
          set_val = dataStr.toFloat();
          if (set_val >= 0.0 && set_val <= 100.0) {
            Serial.print(F("Set servo to"));
            Serial.print(set_val);
            Serial.println(F("%"));

          } else {
            Serial.print(F("Error , value over range!"));
          }

        } else {
          Serial.print(F("Error , please enter only Number"));
        }
      }

      dataStr = "";
    }
    else {
      dataStr += charIn;
    }
  }

  if (millis() - timer > 100) {
    timer += 100;
    if (abs (crr_val - set_val) < 1 && abs (crr_val - set_val) >0) {
      crr_val = set_val;
      Serial.println(crr_val*10+1000);
    }
    else if (crr_val > set_val) {
      crr_val -= 0.5;
      Serial.println(crr_val*10+1000);
    }
    else if (crr_val < set_val) {
      crr_val += 0.5;
      Serial.println(crr_val*10+1000);
    }
    myservo.writeMicroseconds(crr_val*10+1000);
    
  }
}

bool chIsNum (char ch) {
  return ch >= '0' && ch <= '9';
}
bool strIsNum (String str) {
  for (byte i = 0; i < str.length(); i++) {
    if (!chIsNum(str.charAt(i)) && str.charAt(i)!= '.' )return false;
  }
  return true;
}

