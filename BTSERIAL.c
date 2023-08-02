#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

bool awaitPayment = false;

void setup() {
  SerialBT.begin("LirioMachine");
  Serial.begin(115200);
  pinMode(21, INPUT_PULLUP);//FOTOCELULA
  pinMode(17, OUTPUT);//PULSO
  pinMode(18, OUTPUT);//LED
}

void loop() {
  int buttonState = digitalRead(21);

  digitalWrite(17, HIGH);

  if(buttonState == LOW && !awaitPayment){
    SerialBT.println("PAY"); 
    awaitPayment = true;   
    delay(1000);
  }

  if(buttonState == HIGH && awaitPayment){
    SerialBT.println("REMOVE"); 
    awaitPayment = false;   
    delay(1000);
  }

  if(SerialBT.available()){
    String recebido = SerialBT.readString();
    Serial.println(recebido);
    if(recebido == "INIT" && awaitPayment){
      Serial.println("Servindo...");
      digitalWrite(17, LOW);
      delay(2000);
      digitalWrite(17, HIGH);
      awaitPayment = false;  
      delay(15000);
    }
  }

  if (Serial.available()) {
    SerialBT.println(Serial.readString());
  }
}
