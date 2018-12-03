#ifndef DEFS
#include "defs.h"
#endif

/**
 * Read GET arguments and change Items states/requests accordingly
 */
void getRequestExec() {
  
  if (recArguments[0].arg_name == "item") {
    if (recArguments[0].arg_value == "all_lights") {
      for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++)
        if (HomeItems[i].type == LIGHT) {
          HomeItems[i].set_state = (recArguments[1].arg_value == "ON" ? ON : OFF);
        }
    }
    else {
        for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++)
          if (HomeItems[i].id == (recArguments[0].arg_value).toInt()) {
            HomeItems[i].set_state = (recArguments[1].arg_value == "ON" ? ON : OFF);
          }
    }
  }

}

/**
 * Execute requests coming from external
 * Observer if current state is != from set state
 */
void requestExecution() {
  for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++)
    switch (HomeItems[i].type) {
      case LIGHT:         // ONLY LOCAL AT THE MOMENT
//        Serial.print("CUR: "); Serial.print(HomeItems[i].current_state);
//        Serial.print(", SET: "); Serial.print(HomeItems[i].set_state);
        if ((HomeItems[i].current_state == OFF) && (HomeItems[i].set_state == ON)) {    // Turn ON
          regWrite(HomeItems[i].hardware_pin, 0);
          HomeItems[i].activation_time = millis();
          HomeItems[i].current_state = ON;
        }
        if ((HomeItems[i].current_state == ON) && (HomeItems[i].set_state == OFF)) {    // Turn OFF
          regWrite(HomeItems[i].hardware_pin, 1);
          HomeItems[i].activation_time = 0;
          HomeItems[i].current_state = OFF;
        }
//        Serial.print(" --> CUR: "); Serial.print(HomeItems[i].current_state);
//        Serial.print(", SET: "); Serial.println(HomeItems[i].set_state);
        break;
      case SHIELD:      // // ONLY LOCAL AT THE MOMENT
        /**
         * Possible states: 
         * - UP, activation_time = 0
         * - DOWN, activation_time = 0
         * - UP and set DOWN, activation_time++ => set state ON
         * - ON and set DOWN, check if activation_time < max_activation_time => set state DOWN
         * - DOWN and set UP, activation_time++ => set state ON
         * - ON and set UP, check if activation_time < max_activation_time => set state UP
         * - ON and set OFF => activation_time = 0, set state OFF
         * Future:
         * - use rid-swtich sensor to leave SHIELD slightly open
         */
        break;
    }
}

/**
 *   shields UP/DOWN control, time upddate
 *   LIGHTs time update
 *   Temperature update
 */
void timedExecution() {

}
