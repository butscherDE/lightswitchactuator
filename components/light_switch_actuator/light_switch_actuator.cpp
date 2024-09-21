#include "light_switch_actuator.h"
#include "esphome/core/log.h"

namespace esphome {
namespace light_switch_actuator {

static const char *TAG = "light_switch_actuator.switch";

void LightSwitchActuator::setup() {
  // max 20 rpm on 5V.
  // max 30 rpm on 12V 
  myStepper.setSpeed(15);

  calibration();
}

void LightSwitchActuator::write_state(bool state) {
  if (state) {
    clickForward();
  } else {
    clickBackward();
  }

  // Acknowledge new state by publishing it
  publish_state(state);
}

void LightSwitchActuator::calibration() {
  ESP_LOGI("LightSwitchActuator", "Calibration");
  ESP_LOGI("LightSwitchActuator", "Move forward");
  int steps = static_cast<int>(0.25 * stepsPerRevolution);
  ESP_LOGI("LightSwitchActuator", "Moving %d steps", steps);
  myStepper.step(steps);
  ESP_LOGI("LightSwitchActuator", "Move to center");
  returnToCenter(true);
  ESP_LOGI("LightSwitchActuator", "Calibrated");
}

void LightSwitchActuator::returnToCenter(bool backward) {
  int steps = static_cast<int>((18.0 / 360.0) * stepsPerRevolution);
  if (backward) {
    ESP_LOGI("LightSwitchActuator", "Moving %d steps", -steps);
    myStepper.step(-steps);
  } else {
    ESP_LOGI("LightSwitchActuator", "Moving %d steps", steps);
    myStepper.step(steps);
  }
}

void LightSwitchActuator::clickForward() {
  int steps = static_cast<int>((45.0 / 360.0) * stepsPerRevolution);
  ESP_LOGI("LightSwitchActuator", "Moving %d steps", steps);
  myStepper.step(steps);
  returnToCenter(true);
}

void LightSwitchActuator::clickBackward() {
  int steps = static_cast<int>((45.0 / 360.0) * stepsPerRevolution);
  ESP_LOGI("LightSwitchActuator", "Moving %d steps", -steps);
  myStepper.step(-steps);
  returnToCenter(false);
}

}
}