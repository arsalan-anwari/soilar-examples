#include "soilar-module-template/drivers/rfm95w/rfm95w.h"           
#include INIT_ENVOIRMENT

// Uno Receiver
/*
  DIO0 - D2
  RESET - D8
  NSS - D9
  SCK - D13
  MOSI - D11
  MISO - D12
*/

// Due Receiver
/*
  DIO0 - D22
  RESET - D12
  NSS - D13
  SCK - D74
  MOSI - D75
  MISO - D74
*/

LoraEndnodeSettings settings = { 
  .frequencyMHz = RFM95W_CALC_FEQ_FAST( ((long)(867E6) - 125000) ),  
  .signalBandwidthHz = RFM95W_BW_250KHZ,
  .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
  .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
  .spreadingFactor = 10,
  .codeRate = RFM95W_CODE_RATE_4_6,
  .syncWord = 0x12,
  .enableCRC = true,
  .lowPowerReceiveMode = false,
  .invertIQ = false
};

LoraEndnode transmitter;

// LoraEndnodeSettings settings1 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_1,  
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings2 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_2,  
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings3 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_3,  
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings4 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_4,  
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings5 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_5,
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings6 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_6,
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings7 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_6,
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };

// LoraEndnodeSettings settings8 = { 
//   .frequencyMHz = RFM95W_CHANNEL_868_6,
//   .signalBandwidthHz = RFM95W_BW_125KHZ,
//   .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
//   .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
//   .spreadingFactor = RFM95W_DEFAULT_SF,
//   .codeRate = RFM95W_CODE_RATE_4_6,
//   .syncWord = 0x12,
//   .enableCRC = true,
//   .lowPowerReceiveMode = false,
//   .invertIQ = false
// };


Rfm95wInterface interface = { 0, 9, 8, 2 };

uint8_t buff1[8] = {0xFF, 0x01, 0x00, 0x00, 0x0D, 0xDD, 0xFF, 0xFF};
// uint8_t buff2[8] = {0xFF, 0x02, 0x00, 0x00, 0x4C, 0x54, 0xFF, 0xFF};
// uint8_t buff3[8] = {0xFF, 0x03, 0x00, 0x00, 0x21, 0xBB, 0xFF, 0xFF};
// uint8_t buff4[8] = {0xFF, 0x04, 0x00, 0x00, 0x34, 0xA3, 0xFF, 0xFF};
// uint8_t buff5[8] = {0xFF, 0x05, 0x00, 0x00, 0xBC, 0xAF, 0xFF, 0xFF};
// uint8_t buff6[8] = {0xFF, 0x06, 0x00, 0x00, 0xAD, 0x11, 0xFF, 0xFF};
// uint8_t buff7[8] = {0xFF, 0x07, 0x00, 0x00, 0xC3, 0x65, 0xFF, 0xFF};
// uint8_t buff8[8] = {0xFF, 0x08, 0x00, 0x00, 0xDD, 0xA7, 0xFF, 0xFF};


uint8_t i = 0;
void setup(){

  Serial.begin(9600);
  Serial.println("LoRa Transmitter");


  if ( CreateRfm95W(&transmitter, &interface, &settings) == LORA_ERROR_WRONG_DEVICE ) {
    Serial.println("Starting LoRa failed!");
    while(1);
  }

}

void loop(){

  if(i > 250){ i=0; }
  
  buff1[3]=i; 
  // buff2[3]=i; 
  // buff3[3]=i; 
  // buff4[3]=i;
  // buff5[3]=i; 
  // buff6[3]=i; 
  // buff7[3]=i; 
  // buff8[3]=i;
  i++;

  transmitter.send(buff1, 8);
  Serial.print("Device [1] -- Sending packet [");
  Serial.print(buff1[3]); 
  Serial.print("] "); 
  Serial.print(buff1[4]); 
  Serial.print(" "); 
  Serial.print(buff1[5]);
  Serial.print("\r\n");
  // delay(900);
  
  // transmitter.hop(&setting2);
  // transmitter.send(buff2, 8);
  // Serial.print("Device [2] -- Sending packet [");
  // Serial.print(buff2[3]); 
  // Serial.print("] "); 
  // Serial.print(buff2[4]); 
  // Serial.print(" "); 
  // Serial.print(buff2[5]);
  // Serial.print("\r\n");
  // delay(700);

  // transmitter.hop(&settings3);
  // transmitter.send(buff3, 8);
  // Serial.print("Device [3] -- Sending packet [");
  // Serial.print(buff3[3]); 
  // Serial.print("] "); 
  // Serial.print(buff3[4]); 
  // Serial.print(" "); 
  // Serial.print(buff3[5]);
  // Serial.print("\r\n");
  // delay(800);
  
  // transmitter.hop(&settings4);
  // transmitter.send(buff4, 8);
  // Serial.print("Device [4] -- Sending packet [");
  // Serial.print(buff4[3]); 
  // Serial.print("] "); 
  // Serial.print(buff4[4]); 
  // Serial.print(" "); 
  // Serial.print(buff4[5]);
  // Serial.print("\r\n");
  // delay(1000);
  
  // transmitter.hop(&settings5);
  // transmitter.send(buff5, 8);
  // Serial.print("Device [5] -- Sending packet [");
  // Serial.print(buff5[3]); 
  // Serial.print("] "); 
  // Serial.print(buff5[4]); 
  // Serial.print(" "); 
  // Serial.print(buff5[5]);
  // Serial.print("\r\n");
  // delay(950);

  // transmitter.hop(&settings6);
  // transmitter.send(buff6, 8);
  // Serial.print("Device [6] -- Sending packet [");
  // Serial.print(buff6[3]); 
  // Serial.print("] "); 
  // Serial.print(buff6[4]); 
  // Serial.print(" "); 
  // Serial.print(buff6[5]);
  // Serial.print("\r\n");
  // delay(850);

  // transmitter.hop(&settings7);
  // transmitter.send(buff7, 8);
  // Serial.print("Device [7] -- Sending packet [");
  // Serial.print(buff7[3]); 
  // Serial.print("] "); 
  // Serial.print(buff7[4]); 
  // Serial.print(" "); 
  // Serial.print(buff7[5]);
  // Serial.print("\r\n");
  // delay(750);

  // transmitter.hop(&settings8);
  // transmitter.send(buff8, 8);
  // Serial.print("Device [8] -- Sending packet [");
  // Serial.print(buff8[3]); 
  // Serial.print("] "); 
  // Serial.print(buff8[4]); 
  // Serial.print(" "); 
  // Serial.print(buff8[5]);
  // Serial.print("\r\n");
  
  delay(5000);
  // transmitter.hop(&settings1);

  // Serial.print("\r\n");

}