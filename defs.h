#define DEFS

enum ItemStates { OFF, ON, UP, DOWN };

enum ItemTypes { LIGHT, SHIELD, TEMP };

typedef struct {
  int id;
  ItemTypes type;           // see Item types
  ItemStates set_state;      // see Item states
  ItemStates current_state;
  long item_value;
  char item_name[16];
  char db_name[16];
  uint8_t floor_level;    // 0 = ground floor
  uint8_t address;        // 0 = local, xxx = last number of IP adress
  uint8_t hardware_pin;   // direct pin or shift register pin or temperature DS1820 1Wire address
  long activation_time;       // active time (how much time to activate shileds / how much time light is on)
} ItemsDef;

#define NUMBER_OF_ITEMS 16

ItemsDef HomeItems[NUMBER_OF_ITEMS] = {
  {1, LIGHT, OFF, OFF, 0, "Kuchnia 1", "kuchnia_1", 0, 0, 1, 0},
  {2, LIGHT, OFF, OFF, 0, "Kuchnia 2", "kuchnia_2", 0, 0, 1, 0},
  {3, LIGHT, OFF, OFF, 0, "Jadalnia 1", "jadalnia_1", 0, 0, 1, 0},
  {4, LIGHT, OFF, OFF, 0, "Jadalnia 2", "jadalnia_2", 0, 0, 1, 0},
  {5, LIGHT, OFF, OFF, 0, "Salon 1", "salon_1", 0, 0, 1, 0},
  {6, LIGHT, OFF, OFF, 0, "Salon 2", "salon_2", 0, 0, 1, 0},
  {7, LIGHT, OFF, OFF, 0, "Biuro", "biuro", 0, 0, 1, 0},
  {8, LIGHT, OFF, OFF, 0, "Lazienka", "lazienka", 0, 0, 1, 0},
  {9, LIGHT, OFF, OFF, 0, "Pom Gosp", "pom_gosp", 0, 0, 1, 0},
  {10, LIGHT, OFF, OFF, 0, "Wiatrolap", "wiatrolap", 0, 0, 1, 0},
  {11, LIGHT, OFF, OFF, 0, "Garaz 1", "garaz_1", 0, 0, 1, 0},
  {12, LIGHT, OFF, OFF, 0, "Garaz 2", "garaz_2", 0, 0, 1, 0},
  {13, LIGHT, OFF, OFF, 0, "Drzwi", "drzwi", 0, 0, 1, 0},
  {14, LIGHT, OFF, OFF, 0, "Brama", "brama", 0, 0, 1, 0},
  {15, LIGHT, OFF, OFF, 0, "Taras 1", "taras_1", 0, 0, 1, 0},
  {16, LIGHT, OFF, OFF, 0, "Taras 2", "taras_2", 0, 0, 1, 0}
};

typedef struct {
  String arg_name;
  String arg_value;
} argDef;

argDef recArguments[6];


