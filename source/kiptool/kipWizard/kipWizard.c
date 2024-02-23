#include "kipWizard.h"

#include "../../hid/hid.h"

int kipWizard(char *path, FSEntry_t entry) {
    gfx_clearscreen();
    gfx_printf("Kip Wizard");
    Input_t *input = hidRead();

    while (input->buttons & (BtnPow | JoyB)) hidRead();
    while (1) {
        input = hidRead();
        if (!(input->buttons)) input = hidWait();
        if (input->buttons & (BtnPow | JoyB)) break;
    }
    return 0;
}