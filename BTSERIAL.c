#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

void setup() {
  SerialBT.begin("LirioMachine");
  Serial.begin(115200);
  pinMode(21, INPUT_PULLUP);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(21);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  if(buttonState == HIGH){
    SerialBT.println("PAY");    
  }

  if(SerialBT.available()){
    Serial.write(SerialBT.readString());
    String recebido = SerialBT.readString();
    if(recebido == "INIT"){
      digitalWrite(17, LOW);
      digitalWrite(18, LOW);
      delay(2000);
    }
  }
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  delay(20);
}
