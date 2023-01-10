#include "soilar-module-template/drivers/rfm95w/rfm95w.h"             
#include INIT_ENVOIRMENT

// Uno Tranceiver
/*
  DIO0 - D2
  RESET - D8
  NSS - D9
  SCK - D13
  MOSI - D11
  MISO - D12
*/

// Due Tranceiver
/*
  DIO0 - D22
  RESET - D12
  NSS - D13
  SCK - D74
  MOSI - D75
  MISO - D74
*/



LoraEndnode transceiver;

// TX settings
LoraEndnodeSettings settings = { 
  .frequencyMHz = RFM95W_CALC_FEQ_FAST( ((long)(867E6) - 125000) ),  
  .signalBandwidthHz = RFM95W_BW_250KHZ,
  .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
  .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
  .spreadingFactor = 10,
  .codeRate = RFM95W_CODE_RATE_4_6,
  .syncWord = 0x12,
  .enableCRC = true,
  .lowPowerReceiveMode = true,
  .invertIQ = false
};

// RX settings
LoraEndnodeSettings settings2 = { 
  .frequencyMHz = RFM95W_CHANNEL_868_1,  
  .signalBandwidthHz = RFM95W_BW_125KHZ,
  .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
  .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
  .spreadingFactor = RFM95W_DEFAULT_SF,
  .codeRate = RFM95W_CODE_RATE_4_6,
  .syncWord = 0x12,
  .enableCRC = true,
  .lowPowerReceiveMode = false,
  .invertIQ = false
};

Rfm95wInterface interface = { 0, 9, 8, 2 };

uint8_t buff[11] = {0}; // RX BUFF
uint8_t buff2[8] = {0xFF, 0x01, 0x00, 0x00, 0x0D, 0xDD, 0xFF, 0xFF}; // TX BUFF


uint8_t change = 0;
uint8_t i=0;
bool txMode = true;

ISR_CODE void received(void);

void received(void){

  // received a packet
  print("Received packet '");
  if ( transceiver.read(buff, 11) == LORA_PKG_CORRUPTED ){
    Serial.println("Corrupted");
  } else{
    Serial.print("Received packet '");
    Serial.print(buff[4]); 
    Serial.print("-");
    Serial.print(buff[5]); 
    Serial.print("-"); 
    Serial.print(buff[6]); 
    Serial.print("-"); 
    Serial.print(buff[7]); 
    Serial.print("-");
    Serial.print(buff[8]); 
    Serial.print("'\r\n");   
    change++;
  }
  
}

void setup(){

  Serial.begin(9600);
  Serial.println("LoRa Receiver");


  if ( CreateRfm95W(&transceiver, &interface, &settings2) == LORA_ERROR_WRONG_DEVICE ) {
    Serial.println("Starting LoRa failed!");
    while(1);
  }

  transceiver.setOnReceiveCallback( received );

}

void loop(){
  
  if (txMode){
    if(i > 250){ i=0; }
    buff2[3]=i;
    transceiver.send(buff2, 8);
    Serial.print("Device [1] -- Sending packet [");
    Serial.print(buff2[3]); 
    Serial.print("] "); 
    Serial.print(buff2[4]); Serial.print(" "); Serial.print(buff2[5]);
    Serial.print("\r\n");
    i++;
    delay(5000);
  }

  if (change >= 10){
    transceiver.setMode( LORA_TX_MODE );
    transceiver.hop( &settings2 );
    txMode = true;
    change = 0;
    delay(20000);
  }
  
}