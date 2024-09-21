#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include <Stepper.h>

namespace esphome {
namespace light_switch_actuator {
class LightSwitchActuator : public esphome::Component, public esphome::switch_::Switch {
 public:
  void setup() override;
  void write_state(bool state) override;
 
 private:
  void calibration();
  void returnToCenter(bool backward);
  void clickForward();
  void clickBackward();

  static const int IN1 = 5;
  static const int IN2 = 18;
  static const int IN3 = 19;
  static const int IN4 = 21;
  static const int stepsPerRevolution = 2048;

  Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN2, IN3, IN4);
};
}
}