#define DEFS

enum ItemStates { OFF, ON, UP, DOWN };

enum ItemTypes { LIGHT, SHIELD, TEMP }; // HIDDEN, CLOCK, PRESSURE, HUMIDITY, SOCKET

typedef struct {
  uint8_t id;
  char group_name[16];
  uint8_t no_of_items;  
} ItemsGroups;

#define SHIELD_activation_time 60000 //10s

typedef struct {
  int id;
  uint8_t group_id;
  ItemTypes type;           // see Item types
  ItemStates set_state;      // see Item states
  ItemStates current_state;
  long item_value;
  char item_name[16];
  char db_name[16];
  uint8_t floor_level;    // 0 = ground floor
  uint8_t address;        // 0 = local, xxx = last number of IP adress
  uint8_t hardware_pin_1;   // direct pin or shift register pin or temperature DS1820 1Wire address
  uint8_t hardware_pin_2;
  long activation_time;       // activation time (how much time to activate shileds / how long light is on)
  long set_time;          // predefined time value - how long to keep active/turned on
} ItemsDef;

#define NUMBER_OF_GROUPS 4
#define NUMBER_OF_ITEMS 24

ItemsGroups HomeGroups[4] = {
  {1, "Parter Osw", 16},
  {2, "Parter Rol", 8},
  {3, "Pietro Osw", 0},
  {4, "Pietro Rol", 0}
};
#define LIGHTS_OFFSET 16
#define SHIELDS_OFFSET 0

ItemsDef HomeItems[] = {
  {1, 1, LIGHT, OFF, OFF, 0, "Kuchnia 1", "o_kuchnia_1", 0, 0, 6 + LIGHTS_OFFSET, 255, 0, 0},
  {2, 1, LIGHT, OFF, OFF, 0, "Kuchnia 2", "o_kuchnia_2", 0, 0, 7 + LIGHTS_OFFSET, 255, 0, 0},
  {3, 1, LIGHT, OFF, OFF, 0, "Jadalnia 1", "o_jadalnia_1", 0, 0, 8 + LIGHTS_OFFSET, 255, 0, 0},
  {4, 1, LIGHT, OFF, OFF, 0, "Jadalnia 2", "o_jadalnia_2", 0, 0, 9 + LIGHTS_OFFSET, 255, 0, 0},
  {5, 1, LIGHT, OFF, OFF, 0, "Salon 1", "o_salon_1", 0, 0, 10 + LIGHTS_OFFSET, 255, 0, 0},
  {6, 1, LIGHT, OFF, OFF, 0, "Salon 2", "o_salon_2", 0, 0, 11 + LIGHTS_OFFSET, 255, 0, 0},
  {7, 1, LIGHT, OFF, OFF, 0, "Biuro 1", "o_biuro_1", 0, 0, 4 + LIGHTS_OFFSET, 255, 0, 0},
  {8, 1, LIGHT, OFF, OFF, 0, "Biuro 2", "o_biuro_2", 0, 0, 5 + LIGHTS_OFFSET, 255, 0, 0},
  {9, 1, LIGHT, OFF, OFF, 0, "Lazienka", "o_lazienka", 0, 0, 14 + LIGHTS_OFFSET, 255, 0, 0},
  {10, 1, LIGHT, OFF, OFF, 0, "Klatka sch", "o_klatka_d", 0, 0, 2 + LIGHTS_OFFSET, 255, 0, 0},
  {11, 1, LIGHT, OFF, OFF, 0, "Przedpok", "o_przedpok", 0, 0, 13 + LIGHTS_OFFSET, 255, 0, 0},
  {12, 1, LIGHT, OFF, OFF, 0, "Wiatrolap", "o_wiatrolap", 0, 0, 15 + LIGHTS_OFFSET, 255, 0, 0},
  {13, 1, LIGHT, OFF, OFF, 0, "Garaz 1", "o_garaz_1", 0, 0, 0 + LIGHTS_OFFSET, 255, 0, 0},
  {14, 1, LIGHT, OFF, OFF, 0, "Garaz 2", "o_garaz_2", 0, 0, 1 + LIGHTS_OFFSET, 255, 0, 0},
  {15, 1, LIGHT, OFF, OFF, 0, "Drzwi W", "o_drzwi_w", 0, 0, 12 + LIGHTS_OFFSET, 255, 0, 0},
  {16, 1, LIGHT, OFF, OFF, 0, "Taras", "o_taras", 0, 0, 3 + LIGHTS_OFFSET, 255, 0, 0},
  
  {17, 2, SHIELD, OFF, OFF, 0, "Kuchnia", "r_kuchnia", 0, 0, 5 + SHIELDS_OFFSET, 4 + SHIELDS_OFFSET, 0, 15000},
  {18, 2, SHIELD, OFF, OFF, 0, "Narozne", "r_narozne", 0, 0, 7 + SHIELDS_OFFSET, 6 + SHIELDS_OFFSET, 0, 25000},
  {19, 2, SHIELD, OFF, OFF, 0, "Jadalnia", "r_jadalnia", 0, 0, 8 + SHIELDS_OFFSET, 9 + SHIELDS_OFFSET, 0, 30000},
  {20, 2, SHIELD, OFF, OFF, 0, "Salon", "r_salon", 0, 0, 10 + SHIELDS_OFFSET, 11 + SHIELDS_OFFSET, 0, 31000},
  {21, 2, SHIELD, OFF, OFF, 0, "Ogrod HS", "r_ogrod", 0, 0, 13 + SHIELDS_OFFSET, 12 + SHIELDS_OFFSET, 0, 32000},
  {22, 2, SHIELD, OFF, OFF, 0, "Biuro", "r_biuro", 0, 0, 14 + SHIELDS_OFFSET, 15 + SHIELDS_OFFSET, 0, 23000},
  {23, 2, SHIELD, OFF, OFF, 0, "Garaz", "r_garaz", 0, 0, 1 + SHIELDS_OFFSET, 0 + SHIELDS_OFFSET, 0, 26000},
  {24, 2, SHIELD, OFF, OFF, 0, "Pom Gosp", "r_pom_gosp", 0, 0, 3 + SHIELDS_OFFSET, 2 + SHIELDS_OFFSET, 0, 15000}
};

typedef struct {
  String arg_name;
  String arg_value;
} argDef;

#define MAX_ARGUMENTS 8
argDef recArguments[MAX_ARGUMENTS];
