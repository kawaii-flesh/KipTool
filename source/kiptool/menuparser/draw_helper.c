#include "draw_helper.h"
#include "printf.h"

menu_entry_s* LocateChoosenMenu(menu_entry_s* current, int index) {
    if (current == NULL) return NULL;
    while (index != 0) {
        index--;
        current = current->item_next;
        if (current == NULL) return NULL;
    }
    return current;
}

menu_entry_s* LocateUpperSelectionMenu(menu_entry_s* current, int* index) {
    *index = 1;
    if (current->item_upper_group) {
        // current = current->item_upper_group;
        menu_entry_s* searchPtr = current->item_upper_group;
        uint32_t counter = 1;
        while (searchPtr) {
            if (searchPtr == current->item_parent) break;
            counter++;
            searchPtr = searchPtr->item_next;
        }
        if (searchPtr) {
            *index = counter;
            return current->item_upper_group;
        } else
            return NULL;
    } else
        return NULL;
}

const char* GetMenuHeaderName(menu_entry_s* current) {
    if (current->item_parent == NULL)
        return "Main menu";
    else
        return current->item_parent->menu_info.name;
}

uint32_t CalculateEntitys(menu_entry_s* nav_temp) {
    uint32_t menu_elements = 1;
    while (nav_temp) {
        if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.param_type == PARAM_RANGE_SELECTION) {
            int64_t temp = nav_temp->value_data.min_value;
            while (temp <= nav_temp->value_data.max_value)
            {
                menu_elements++;
                temp += nav_temp->value_data.step;
            }
            //menu_elements += abs((nav_temp->value_data.max_value - nav_temp->value_data.min_value) / nav_temp->value_data.step) + 1;
        } else {
            menu_elements++;
        }
        nav_temp = nav_temp->item_next;
    }
    return menu_elements;
}

#include "../../hid/hid.h"
#include "../gfx/gfx.h"

void PopulateMenuValueRange(MenuEntry* menu_header, uint32_t count, uint32_t* menu_ptr, menu_entry_s* nav_temp) {
    //gfx_printf("Min %d Max %d Step %d\r\n\0", (uint32_t)nav_temp->value_data.min_value, (uint32_t)nav_temp->value_data.max_value,
    //           (uint32_t)nav_temp->value_data.step);
    for (int32_t i = nav_temp->value_data.min_value; i <= nav_temp->value_data.max_value; i += nav_temp->value_data.step) {
        //gfx_printf("i on step %d ptr %d\r\n\0", (uint32_t)i, *menu_ptr);
        // TODO FIX MEMORY LEAK!!!!!!!
        menu_header[*menu_ptr].entry = calloc(100, 1);
        //gfx_printf("Text = %s\r\n\0", nav_temp->menu_info.name);
        if (nav_temp->value_data.delimiter == 1){
            snprintf(menu_header[*menu_ptr].entry, 100,nav_temp->menu_info.name, i);
        }
        else{
            snprintf(menu_header[*menu_ptr].entry, 100,nav_temp->menu_info.name, (float)i / (float) nav_temp->value_data.delimiter);
        }

        if (nav_temp->menu_info.entry_type == ENTRY_FOLDER) {
            menu_header[*menu_ptr].optionUnion = COLORTORGB(COLOR_GREEN);
        } else if (nav_temp->menu_info.entry_type == ENTRY_PARAM) {
            menu_header[*menu_ptr].optionUnion = COLORTORGB(COLOR_DEFAULT);
        } else {
            if (nav_temp->value_data.param_type == PARAM_MANUAL_SELECTION) {
                menu_header[*menu_ptr].optionUnion = COLORTORGB(COLOR_ORANGE);
            } else
                menu_header[*menu_ptr].optionUnion = COLORTORGB(COLOR_GREY);
        }
        menu_header[*menu_ptr].type = ETLabel;
        *menu_ptr += 1;
    }
}

void DeleteMenuEntry(MenuEntry* menu_header, uint32_t count, menu_entry_s* nav_temp) {
    // TODO IMPLEMENT (PopulateMenuValueRange leak)
    free(menu_header);
}

MenuEntry* CreateMenuEntity(menu_entry_s* current, uint32_t* menu_elements) {
    menu_entry_s* nav_temp = current;
    *menu_elements = CalculateEntitys(current);
    MenuEntry* curr_menu = (MenuEntry*)calloc(*menu_elements, sizeof(MenuEntry));
    uint32_t menu_ptr = 0;
    curr_menu[menu_ptr].entry = GetMenuHeaderName(current);
    curr_menu[menu_ptr].optionUnion = COLORTORGB(COLOR_WHITE);
    curr_menu[menu_ptr].skip = 1;
    curr_menu[menu_ptr++].type = ETLabel;
    while (nav_temp) {
        if (nav_temp->menu_info.entry_type == ENTRY_VALUE && nav_temp->value_data.param_type == PARAM_RANGE_SELECTION) {
            //gfx_printf("Min %d Max %d Step %d Ptr %d Entitys %d\r\n\0", (uint32_t)nav_temp->value_data.min_value, (uint32_t)nav_temp->value_data.max_value,
            //           (uint32_t)nav_temp->value_data.step, menu_ptr, *menu_elements);
            PopulateMenuValueRange(curr_menu, *menu_elements, &menu_ptr, nav_temp);
            //gfx_printf("Min %d Max %d Step %d Ptr %d Entitys %d\r\n\0", (uint32_t)nav_temp->value_data.min_value, (uint32_t)nav_temp->value_data.max_value,
            //           (uint32_t)nav_temp->value_data.step, menu_ptr,*menu_elements);
            //while (1) {
            //    Input_t* input = hidRead();
//
             //   if (!(input->buttons)) input = hidWait();
             //   if (input->buttons & (BtnPow | JoyB)) break;
            //}
        } else {
            PopulateMenuEntry(nav_temp, &curr_menu[menu_ptr++]);
        }
        nav_temp = nav_temp->item_next;
    }
    return curr_menu;
}

void PopulateMenuEntry(menu_entry_s* entity, MenuEntry* curr_element) {
    if (entity->menu_info.entry_type == ENTRY_FOLDER) {
        curr_element->optionUnion = COLORTORGB(COLOR_GREEN);
    } else if (entity->menu_info.entry_type == ENTRY_PARAM) {
        curr_element->optionUnion = COLORTORGB(COLOR_WHITE);
    } else {
        if (entity->value_data.param_type == PARAM_MANUAL_SELECTION) {
            curr_element->optionUnion = COLORTORGB(COLOR_ORANGE);
        } else
            curr_element->optionUnion = COLORTORGB(COLOR_GREY);
    }
    curr_element->entry = entity->menu_info.name;
    curr_element->type = ETLabel;
    return;
}
