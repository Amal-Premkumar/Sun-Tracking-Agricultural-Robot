#include <LiquidCrystal_I2C.h> 
#include <Wire.h>

#define m11 12 //d9
#define m12 11 //D8 
#define m21 10//D7 
#define m22  9 //D6
#define upsw 6 //D3
#define dwnsw 7 //D4 
#define selectsw  8 //D5
#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Create an LCD object
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS); 

unsigned int en1 = 0, en2 = 0, en3 = 0, L = 1, B = 1, s3, lnth, brth, moveen = 0; 
int selectedsw = 1, chk = 1; 
String sw = "L"; 
unsigned long previousMillis1 = 0; 
unsigned int interval1 = 1000, sec = 0, alert = 0, sec1 = 0, Bcount = 1, Lcount = 1; 
String param1; 

void timer(); 
void forward(); 
void backward(); 
void left(); 
void right(); 
void stp(); 
void cycle(); 
void switchselect(); 

void setup(void) { 
    Serial.begin(9600); 
    pinMode(m11, OUTPUT); 
    pinMode(m12, OUTPUT); 
    pinMode(m21, OUTPUT); 
    pinMode(m22, OUTPUT); 
    pinMode(upsw, INPUT_PULLUP); 
    pinMode(dwnsw, INPUT_PULLUP); 
    pinMode(selectsw, INPUT_PULLUP); 
    digitalWrite(m11, LOW); 
    digitalWrite(m12, LOW); 
    digitalWrite(m21, LOW); 
    digitalWrite(m22, LOW); 
    param1 = "STP"; 
    lcd.begin(16, 2); 
    lcd.setCursor(0, 0);
    lcd.print("Farming"); 
    lcd.setCursor(0, 1);
    lcd.print(" Robot"); 
    delay(1000); 
    lcd.setCursor(0, 0);
    lcd.print(""); 
    lcd.setCursor(0, 1);
    lcd.print("Mov:C:"); 
    Bcount = 2; 
} 

void loop(void) { 
    lcd.setCursor(14, 1); 
    lcd.print(Bcount); 
    lcd.setCursor(15, 0); 
    lcd.print(moveen); 
    timer(); 
    switchselect(); 

    if (digitalRead(selectsw) == LOW) { 
        chk = 1;
        Bcount = B;
        Lcount = L * 4500; 
        lcd.setCursor(12, 0); 
        lcd.print(sec); 
        lcd.setCursor(14, 1); 
        lcd.print(Bcount); 
        if (chk == 1 && sec >= 2) { 
            Bcount = B;
            Lcount = L * 4500; 
            lcd.setCursor(12, 0);
            lcd.print(""); 
            moveen = 1;
            delay(500);
            chk = 0; 
        } 
    } else if (digitalRead(selectsw) == HIGH) { 
        chk = 0;
        sec = 0;
        chk = 1;
        lcd.setCursor(12, 0);
        lcd.print(""); 
    } 

    Serial.println(sec); 

    if (moveen == 1 && Bcount > 0) {
        cycle(); 
    } else {
        stp(); 
        moveen = 0;
    }
} 

void switchselect() { 
    if (digitalRead(selectsw) == LOW && selectedsw == 1) { 
        selectedsw = 2;
        sw = "B";
        delay(400); 
    } else if (digitalRead(selectsw) == LOW && selectedsw == 2) { 
        selectedsw = 1;
        sw = "L";
        delay(400); 
    } 

    if (selectedsw == 1) {
        if (digitalRead(upsw) == LOW && en1 == 0) {
            L++;
            delay(400);
        } 

        if (digitalRead(dwnsw) == LOW && en2 == 0) {
            L--;
            delay(400);
        }
        if (L > 9) {
            L = 1;
        } 
    } 

    if (selectedsw == 2) { 
        if (digitalRead(upsw) == LOW && en1 == 0) {
            B++;
            delay(400);
        } 
        if (digitalRead(dwnsw) == LOW && en2 == 0) {
            B--;
            delay(400);
        }
        if (B > 9) {
            B = 1;
        }
    } 

    lcd.setCursor(0, 0);
    lcd.print("L:");
    lcd.setCursor(2, 0);
    lcd.print(L); 
    lcd.setCursor(4, 0);
    lcd.print("B:");
    lcd.setCursor(6, 0);
    lcd.print(B);
    lcd.setCursor(10, 0);
    lcd.print(sw);

    lcd.setCursor(0, 1);
    lcd.print("L=");
    lcd.setCursor(2, 1);
    lcd.print(lnth);

    lcd.setCursor(6, 1);
    lcd.print("B=");
    lcd.setCursor(8, 1);
    lcd.print(brth); 
}

void cycle() { 
    forward();
    delay(Lcount); 
    right();
    delay(2360); 
    forward();
    delay(500); 
    right();
    delay(2360);
    forward();
    delay(Lcount); 
    left();
    delay(2300); 
    forward();
    delay(500); 
    left();
    delay(2300); 

    Bcount--; 
} 

void timer() { 
    unsigned long currentMillis = millis(); 
    if ((unsigned long)(currentMillis - previousMillis1) >= interval1) { 
        sec++;
        sec1++; 
        previousMillis1 = currentMillis; 
    } 
}

void forward() { 
    digitalWrite(m11, LOW); 
    digitalWrite(m12, HIGH); 
    digitalWrite(m21, LOW); 
    digitalWrite(m22, HIGH); 
    lcd.setCursor(5, 1);
    lcd.print("FWD"); 
}

void backward() { 
    digitalWrite(m11, LOW); 
    digitalWrite(m12, HIGH); 
    digitalWrite(m21, LOW); 
    digitalWrite(m22, HIGH); 
    lcd.setCursor(5, 1);
    lcd.print("BKD"); 
} 

void left() { 
    digitalWrite(m11, LOW); 
    digitalWrite(m12, HIGH); 
    digitalWrite(m21, LOW); 
    digitalWrite(m22, LOW); 
    lcd.setCursor(5, 1);
    lcd.print("LFT"); 
}

void right() { 
    digitalWrite(m11, LOW); 
    digitalWrite(m12, LOW); 
    digitalWrite(m21, LOW); 
    digitalWrite(m22, HIGH); 
    lcd.setCursor(5, 1);
    lcd.print("RGT"); 
}

void stp() { 
    digitalWrite(m11, LOW); 
    digitalWrite(m12, LOW); 
    digitalWrite(m21, LOW); 
    digitalWrite(m22, LOW); 
    lcd.setCursor(5, 1); 
    lcd.print("STP"); 
} 
