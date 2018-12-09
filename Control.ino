#ifndef DEFS
#include "defs.h"
#endif

static bool state_change = 0;
/**
 * Read GET arguments and change Items states/requests accordingly
 */
void getRequestExec() {
  //Serial.println(sizeof(getArgument("item")));
  if (server.args() == 0)
    return;
  if (getArgument("item") == "all_lights") {
    for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++)
      if (HomeItems[i].type == LIGHT) {
        HomeItems[i].set_state = (getArgument("value") == "ON" ? ON : OFF);
      }
  } else {
    
    String arg_item = getArgument("item");
    String arg_value = getArgument("value");
    for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++)
      if (arg_item)
        if (HomeItems[i].id == ( arg_item.toInt() )) {
          Serial.printf("Current state: %d", HomeItems[i].set_state);
            bool last_state = HomeItems[i].set_state;
            if (arg_value == "ON") HomeItems[i].set_state = ON;
            else if (arg_value == "OFF") HomeItems[i].set_state = OFF;
            else if (arg_value == "STOP") HomeItems[i].set_state = OFF;
            else if (arg_value == "UP") HomeItems[i].set_state = UP;
            else if (arg_value == "DOWN") HomeItems[i].set_state = DOWN;
          Serial.printf(", New state: %d\n", HomeItems[i].set_state);
          if (last_state != HomeItems[i].set_state)
            state_change = true;
          else
            state_change = false;
        }
  }
  
  
  /*
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
  */
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
          Serial.printf("HW PIN: %d\n", HomeItems[i].hardware_pin_1);
          regWrite(HomeItems[i].hardware_pin_1, 0);
          HomeItems[i].activation_time = millis();
          HomeItems[i].current_state = ON;
        }
        if ((HomeItems[i].current_state == ON) && (HomeItems[i].set_state == OFF)) {    // Turn OFF
          regWrite(HomeItems[i].hardware_pin_1, 1);
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
         * - ON and set OFF (STOP) => activation_time = 0, set state OFF
         * 
         * Future:
         * - use rid-swtich sensor to leave SHIELD slightly open
         */
         /*
        if (HomeItems[i].current_state != HomeItems[i].set_state) {
          Serial.print(" --> CUR: "); Serial.print(HomeItems[i].current_state);
          Serial.print(", SET: "); Serial.println(HomeItems[i].set_state);
        }
        */
        if (HomeItems[i].set_state == OFF) {
          regWrite(HomeItems[i].hardware_pin_1, 1);     // Turn OFF both relays
          regWrite(HomeItems[i].hardware_pin_2, 1);
          HomeItems[i].activation_time = 0;
          HomeItems[i].current_state = OFF;
          //Serial.println("Shields relays OFF");
          //writeLine("Shields relays OFF");
        }
        // request to go UP
        if (HomeItems[i].set_state == UP) {
          // if gowing down => STOP (OFF) first
          if ( (HomeItems[i].current_state == DOWN) ){
            regWrite(HomeItems[i].hardware_pin_1, 1);     // Turn OFF both relays
            regWrite(HomeItems[i].hardware_pin_2, 1);
            print_shift_registers();
            Serial.printf(HomeItems[i].item_name);
            Serial.printf(", PIN: %d, %d\n", HomeItems[i].hardware_pin_1, HomeItems[i].hardware_pin_2);
            HomeItems[i].current_state = OFF;
            Serial.println("Shields go down -> STOP");
            writeLine("Shields go down -> STOP");
          }
          // if STOPPED (OFF) go UP, start count
          if (HomeItems[i].current_state == OFF) {
            regWrite(HomeItems[i].hardware_pin_2, 1); // Keep OFF relay DOWN
            regWrite(HomeItems[i].hardware_pin_1, 0);     // Turn ON relay UP
            print_shift_registers();
            Serial.printf(HomeItems[i].item_name);
            Serial.printf(", PIN: %d, %d\n", HomeItems[i].hardware_pin_1, HomeItems[i].hardware_pin_2);
            HomeItems[i].current_state = ON;
            HomeItems[i].activation_time = millis() + HomeItems[i].set_time;
            Serial.println("Shields STOP -> go UP");
            writeLine("Shields STOP -> go UP");
          }
          // If time is up, set position is known, stop
          if ((HomeItems[i].current_state == ON) && (HomeItems[i].activation_time < millis())) {
            regWrite(HomeItems[i].hardware_pin_1, 1);     // Turn OFF both relays
            regWrite(HomeItems[i].hardware_pin_2, 1);
            print_shift_registers();
            Serial.printf(HomeItems[i].item_name);
            Serial.printf(", PIN: %d, %d\n", HomeItems[i].hardware_pin_1, HomeItems[i].hardware_pin_2);
            HomeItems[i].current_state = UP;
            HomeItems[i].activation_time = 0;
            Serial.println("Shields UP -> STOP UP");
            writeLine("Shields UP -> STOP UP");
          }
        }

        // request to go DOWN
        if (HomeItems[i].set_state == DOWN) {
          // if gowing up => STOP (OFF) first
          if ( (HomeItems[i].current_state == UP) ) {
            regWrite(HomeItems[i].hardware_pin_1, 1);     // Turn OFF both relays
            regWrite(HomeItems[i].hardware_pin_2, 1);
            print_shift_registers();
            Serial.printf(HomeItems[i].item_name);
            Serial.printf(", PIN: %d, %d\n", HomeItems[i].hardware_pin_1, HomeItems[i].hardware_pin_2);
            HomeItems[i].current_state = OFF;
            Serial.println("Shields go up -> STOP");
            writeLine("Shields go up -> STOP");
          }
          // if STOPPED (OFF) go DOWN, start count
          if (HomeItems[i].current_state == OFF) {
            regWrite(HomeItems[i].hardware_pin_1, 1); // Keep OFF relay UP
            regWrite(HomeItems[i].hardware_pin_2, 0);     // Turn ON relay DOWN
            print_shift_registers();
            Serial.printf(HomeItems[i].item_name);
            Serial.printf(", PIN: %d, %d\n", HomeItems[i].hardware_pin_1, HomeItems[i].hardware_pin_2);
            HomeItems[i].current_state = ON;
            HomeItems[i].activation_time = millis() + HomeItems[i].set_time;
            Serial.println("Shields STOP -> go DOWN");
            writeLine("Shields STOP -> go DOWN");
          }
          // If time is up, set position is known, stop
          if ((HomeItems[i].current_state == ON) && (HomeItems[i].activation_time < millis())) {
            regWrite(HomeItems[i].hardware_pin_1, 1);     // Turn OFF both relays
            regWrite(HomeItems[i].hardware_pin_2, 1);
            print_shift_registers();
            Serial.printf(HomeItems[i].item_name);
            Serial.printf(", PIN: %d, %d\n", HomeItems[i].hardware_pin_1, HomeItems[i].hardware_pin_2);
            HomeItems[i].current_state = DOWN;
            HomeItems[i].activation_time = 0;
            Serial.println("Shields DOWN -> STOP DOWN");
            writeLine("Shields DOWN -> STOP DOWN");
          }
        }
        //set_state
        //current_state
        //long activation_time;
        //uint8_t hardware_pin_1;
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
