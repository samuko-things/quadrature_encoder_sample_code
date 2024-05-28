#include "encoder_setup.h"
#include "l298n_motor_control.h"

///////////////////////////////////////////////////
// store encoder pulsePerRev needed by encoder
float encA_ppr = 1000.0;
float encB_ppr = 1000.0;
unsigned long encA_stopFreq = 5000; // in us
unsigned long encB_stopFreq = 5000; // in us


int encA_clkPin = 2 /*interrupt pin*/, encA_dirPin = 4;
int encB_clkPin = 3 /*interrupt pin*/, encB_dirPin = 9;

QuadEncoder encA(encA_clkPin, encA_dirPin, encA_ppr);
QuadEncoder encB(encB_clkPin, encB_dirPin, encB_ppr);



void encoderInit() {
  encA.setPulsePerRev(encA_ppr);
  encB.setPulsePerRev(encB_ppr);

  encA.setStopFreqInUs(encA_stopFreq);
  encB.setStopFreqInUs(encB_stopFreq);
  
  attachInterrupt(digitalPinToInterrupt(encA.clkPin), readEncoderA, FALLING);
  attachInterrupt(digitalPinToInterrupt(encB.clkPin), readEncoderB, FALLING);
}

void readEncoderA() {
  encA.freqPerTick = 1000000.00 / (float)(micros() - encA.oldFreqTime);
  encA.oldFreqTime = micros();
  encA.checkFreqTime = micros();

  if (digitalRead(encA.dirPin) == 1) {
    encA.tickCount += 1;
    encA.frequency = encA.freqPerTick / (float)encA.pulsePerRev;
  } else {
    encA.tickCount -= 1;
    encA.frequency = -1.00 * encA.freqPerTick / (float)encA.pulsePerRev;
  }

}

void readEncoderB() {
  encB.freqPerTick = 1000000.00 / (float)(micros() - encB.oldFreqTime);
  encB.oldFreqTime = micros();
  encB.checkFreqTime = micros();

  if (digitalRead(encB.dirPin) == 1) {
    encB.tickCount += 1;
    encB.frequency = encB.freqPerTick / (float)encB.pulsePerRev;
  } else {
    encB.tickCount -= 1;
    encB.frequency = -1.00 * encB.freqPerTick / (float)encB.pulsePerRev;
  }

}
////////////////////////////////////////////////////////////////




// motor A H-Bridge Connection
int IN1 = 7, IN2 = 8, enA = 5;
L298NMotorControl motorA(IN1, IN2, enA);

// motor B H-Bridge Connection
int IN3 = 11, IN4 = 12, enB = 6;
L298NMotorControl motorB(IN3, IN4, enB);




void setup() {
  Serial.begin(115200);
  
  encoderInit();
  /* motor needs no initialization as it has already been initialized*/
}

// please loop with millis-style not delay()-sytle

void loop() {
  ///// do not touch ////////
  ///// useful for velocity reading to check when rotation has stopped
  encA.resetFrequency();
  encB.resetFrequency();
  ///////////////////////////////////////////////////////////////////


  // forward
  motorA.sendPWM(120);
  motorB.sendPWM(120);

  float motorA_velocity_rad_per_sec = encA.getAngVel();
  float motorA_position_rad = encB.getAngPos();

  // print out the value so see it.
  Serial.println(motorA_velocity_rad_per_sec);
  Serial.println(motorA_position_rad);
}
