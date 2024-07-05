#include "included/c2d_handler.hpp"

#include <stdlib.h>
#include <string>
#include <fstream> // For checking file existence
using namespace std;

#include "included/debug.hpp"
#include "included/c2d_handler.hpp"
#include "included/app.hpp"

namespace C2D_HANDLER{

    const char* romfs_folder = "romfs:/";

    bool file_exists(const string& name) {
        ifstream f(name.c_str());
        bool exists = f.good();
        f.close(); // Ensure the file is closed after checking
        return exists;
    }

    C2D_Image load_c2d_image(const char* path){
        std::string path_string = std::string(romfs_folder) + path;
        const char* path_cstr = path_string.c_str();

        std::string loading_message = "Loading " + std::string(path_cstr) + "\n";
        DEBUG::print_to_Screen(colored_text("green", "", loading_message.c_str()), false, GFX_BOTTOM);

        // Check if file exists
        if (!file_exists(path_string)) {
            std::string error_message = "Could not find: " + path_string + "\n";
            DEBUG::print_to_Screen(colored_text("red", "", error_message.c_str()), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
            return {};
        }

        C2D_Image image;
        C2D_SpriteSheet sheet = C2D_SpriteSheetLoad(path_cstr);

        if (!sheet) {
            DEBUG::print_to_Screen(colored_text("red", "", "Failed\n"), false, GFX_BOTTOM);
            DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
            return {};
        }

        image = C2D_SpriteSheetGetImage(sheet, 0);
        C2D_SpriteSheetFree(sheet);

        DEBUG::print_to_Screen(colored_text("green", "", "Successfull\n"), false, GFX_BOTTOM);
        DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
        return image;
    }
}