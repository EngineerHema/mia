#include <Wire.h>


const float GYRO_SCALE = 131.0;
const int MPU6050 = 0x68;  
const int Power = 0x6B;    
const int GYRO_ZOUT_H = 0x47;  

float yaw = 0;
unsigned long prevTime = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
    
  // Wake up the MPU6050 (it starts in sleep mode)
  Wire.beginTransmission(MPU6050);
  Wire.write(Power); 
  Wire.write(0);          
  Wire.endTransmission();

  prevTime = millis();
}

void loop() {
  int16_t gyroZRaw = readGyroZ();
  float gyroZ = gyroZRaw / GYRO_SCALE; 

  unsigned long currentTime = millis();
  float deltaTime = (currentTime - prevTime) / 1000.0; 
  prevTime = currentTime;

  yaw += gyroZ * deltaTime;  

  Serial.println(yaw);
  delay(100);
}

int16_t readGyroZ() {
  Wire.beginTransmission(MPU6050);
  Wire.write(GYRO_ZOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050, 2, true);  

  int16_t gyroZ = Wire.read(); 
  return gyroZ;
}
