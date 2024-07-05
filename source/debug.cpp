#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include <string>
using namespace std;

#include <stdio.h>

namespace DEBUG {
    PrintConsole topScreenConsole;
    PrintConsole bottomScreenConsole;

    void initialize_debug() {
        // Initialize console for top screen
        //consoleInit(GFX_TOP, &topScreenConsole);
        // Initialize console for bottom screen
        consoleInit(GFX_BOTTOM, &bottomScreenConsole);
    }

    void print_to_Screen(const char* message, bool clear_screen, gfxScreen_t screen) {
        // Select the appropriate console based on the screen argument
        PrintConsole* console = (screen == GFX_TOP) ? &topScreenConsole : &bottomScreenConsole;

        // Select the console to use for printing
        consoleSelect(console);

        if (clear_screen) {
            consoleClear();
        }

        printf("%s", message);
    }
}