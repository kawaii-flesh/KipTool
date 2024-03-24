
#include "menu_json_tools.h"
#include "../gfx/menus/ktMenu.h"

menu_entry_s* LocateChoosenMenu(menu_entry_s* current, uint32_t* index);
menu_entry_s* LocateUpperSelectionMenu(menu_entry_s* current, uint32_t* index);
const char* GetMenuHeaderName(menu_entry_s* current);
void PopulateMenuEntry(menu_entry_s* entity, MenuEntry* curr_element);
MenuEntry* CreateMenuEntity(menu_entry_s* current, uint32_t* menu_elements, uint32_t* reset_presented);
void DeleteMenuEntry(MenuEntry* menu_header, uint32_t count, menu_entry_s* nav_temp);
int64_t GetSelectedParameterValue(menu_entry_s* current, int selected);
uint32_t LocateChoosenInnerMenuParam(menu_entry_s* current);