
typedef struct {
  int id;
  uint8_t type;
  uint8_t set_state;
  uint8_t current_state;
  long item_value;
  char item_name[16];
  char db_name[16];
} ItemsDef;

enum ItemStates { OFF, ON, UP, DOWN };

enum ItemTypes { LIGHT, SHIELD, TEMP };

ItemsDef HomeItems[16] = {
  {1, LIGHT, OFF, OFF, 0, "Kuchnia 1", "kuchnia_1"},
  {2, LIGHT, OFF, OFF, 0, "Kuchnia 2", "kuchnia_2"},
  {3, LIGHT, OFF, OFF, 0, "Jadalnia 1", "jadalnia_1"},
  {4, LIGHT, OFF, OFF, 0, "Jadalnia 2", "jadalnia_2"},
  {5, LIGHT, OFF, OFF, 0, "Salon 1", "salon_1"},
  {6, LIGHT, OFF, OFF, 0, "Salon 2", "salon_2"},
  {7, LIGHT, OFF, OFF, 0, "Biuro", "biuro"},
  {8, LIGHT, OFF, OFF, 0, "Lazienka", "lazienka"},
  {9, LIGHT, OFF, OFF, 0, "Pom Gosp", "pom_gosp"},
  {10, LIGHT, OFF, OFF, 0, "Wiatrolap", "wiatrolap"},
  {11, LIGHT, OFF, OFF, 0, "Garaz 1", "garaz_1"},
  {12, LIGHT, OFF, OFF, 0, "Garaz 2", "garaz_2"},
  {13, LIGHT, OFF, OFF, 0, "Drzwi", "drzwi"},
  {14, LIGHT, OFF, OFF, 0, "Brama", "brama"},
  {15, LIGHT, OFF, OFF, 0, "Taras 1", "taras_1"},
  {16, LIGHT, OFF, OFF, 0, "Taras 2", "taras_2"}
};
