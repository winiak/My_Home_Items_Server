#define DEFS

enum ItemStates { OFF, ON, UP, DOWN };

enum ItemTypes { LIGHT, SHIELD, TEMP };

typedef struct {
  uint8_t id;
  char group_name[16];
  uint8_t no_of_items;  
} ItemsGroups;

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
  uint8_t hardware_pin;   // direct pin or shift register pin or temperature DS1820 1Wire address
  long activation_time;       // active time (how much time to activate shileds / how much time light is on)
} ItemsDef;

#define NUMBER_OF_ITEMS 24

ItemsGroups HomeGroups[2] = {
  {1, "OSW parter", 16},
  {2, "ROL parter", 8}
};

ItemsDef HomeItems[] = {
  {1, 1, LIGHT, OFF, OFF, 0, "Kuchnia 1", "o_kuchnia_1", 0, 0, 1, 0},
  {2, 1, LIGHT, OFF, OFF, 0, "Kuchnia 2", "o_kuchnia_2", 0, 0, 2, 0},
  {3, 1, LIGHT, OFF, OFF, 0, "Jadalnia 1", "o_jadalnia_1", 0, 0, 3, 0},
  {4, 1, LIGHT, OFF, OFF, 0, "Jadalnia 2", "o_jadalnia_2", 0, 0, 4, 0},
  {5, 1, LIGHT, OFF, OFF, 0, "Salon 1", "o_salon_1", 0, 0, 5, 0},
  {6, 1, LIGHT, OFF, OFF, 0, "Salon 2", "o_salon_2", 0, 0, 6, 0},
  {7, 1, LIGHT, OFF, OFF, 0, "Biuro", "o_biuro", 0, 0, 7, 0},
  {8, 1, LIGHT, OFF, OFF, 0, "Lazienka", "o_lazienka", 0, 0, 8, 0},
  {9, 1, LIGHT, OFF, OFF, 0, "Pom Gosp", "o_pom_gosp", 0, 0, 9, 0},
  {10, 1, LIGHT, OFF, OFF, 0, "Wiatrolap", "o_wiatrolap", 0, 10, 1, 0},
  {11, 1, LIGHT, OFF, OFF, 0, "Garaz 1", "o_garaz_1", 0, 0, 11, 0},
  {12, 1, LIGHT, OFF, OFF, 0, "Garaz 2", "o_garaz_2", 0, 0, 12, 0},
  {13, 1, LIGHT, OFF, OFF, 0, "Drzwi", "o_drzwi", 0, 0, 13, 0},
  {14, 1, LIGHT, OFF, OFF, 0, "Brama", "o_brama", 0, 0, 14, 0},
  {15, 1, LIGHT, OFF, OFF, 0, "Taras 1", "o_taras_1", 0, 0, 15, 0},
  {16, 1, LIGHT, OFF, OFF, 0, "Taras 2", "o_taras_2", 0, 0, 0, 0},
  {17, 2, SHIELD, OFF, OFF, 0, "Kuchnia", "r_kuchnia", 0, 0, 1, 0},
  {18, 2, SHIELD, OFF, OFF, 0, "Narozne", "r_narozne", 0, 0, 2, 0},
  {19, 2, SHIELD, OFF, OFF, 0, "Jadalnia", "r_jadalnia", 0, 0, 3, 0},
  {20, 2, SHIELD, OFF, OFF, 0, "Salon", "r_salon", 0, 0, 4, 0},
  {21, 2, SHIELD, OFF, OFF, 0, "Ogrod HS", "r_ogrod", 0, 0, 5, 0},
  {22, 2, SHIELD, OFF, OFF, 0, "Biuro", "r_biuro", 0, 0, 6, 0},
  {23, 2, SHIELD, OFF, OFF, 0, "Garaz", "r_garaz", 0, 0, 7, 0},
  {24, 2, SHIELD, OFF, OFF, 0, "Pom Gosp", "r_pom_gosp", 0, 0, 8, 0}
};

typedef struct {
  String arg_name;
  String arg_value;
} argDef;

argDef recArguments[6];
