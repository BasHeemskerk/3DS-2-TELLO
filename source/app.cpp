#include "included/app.hpp"

#include <cstring>
#include <string>
#include <map>
using namespace std;

COLORS color;

const char* colored_text(const std::string& input_color, const std::string& special_effect, const char* input){
    std::map<std::string, const char*> color_map = {
        {"red", color.RED},
        {"green", color.GREEN},
        {"yellow", color.YELLOW},
        {"blue", color.BLUE},
        {"magenta", color.MAGENTA},
        {"cyan", color.CYAN},
        {"white", color.WHITE},
        {"reset", color.RESET},
        {"bold", color.BOLD},
        {"faint", color.FAINT},
        {"italic", color.ITALIC},
        {"underline", color.UNDERLINE},
        {"blink", color.BLINK},
        {"rapid_blink", color.RAPID_BLINK},
        {"reverse", color.REVERSE},
        {"hidden", color.HIDDEN},
        {"strikethrough", color.STRIKETHROUGH},
        {"double_underline", color.DOUBLE_UNDERLINE},
        {"normal", color.NORMAL},
        {"no_italic", color.NO_ITALIC},
        {"no_underline", color.NO_UNDERLINE},
        {"no_blink", color.NO_BLINK},
        {"no_reverse", color.NO_REVERSE},
        {"no_hidden", color.NO_HIDDEN},
        {"no_strikethrough", color.NO_STRIKETHROUGH},
        {"fg_black", color.FG_BLACK},
        {"fg_red", color.FG_RED},
        {"fg_green", color.FG_GREEN},
        {"fg_yellow", color.FG_YELLOW},
        {"fg_blue", color.FG_BLUE},
        {"fg_magenta", color.FG_MAGENTA},
        {"fg_cyan", color.FG_CYAN},
        {"fg_white", color.FG_WHITE},
        {"bg_black", color.BG_BLACK},
        {"bg_red", color.BG_RED},
        {"bg_green", color.BG_GREEN},
        {"bg_yellow", color.BG_YELLOW},
        {"bg_blue", color.BG_BLUE},
        {"bg_magenta", color.BG_MAGENTA},
        {"bg_cyan", color.BG_CYAN},
        {"bg_white", color.BG_WHITE},
        {"bg_reset", color.BG_RESET},
        {"end", color.END}
    };

    std::string new_string = color.PREFIX;
    if (color_map.find(input_color) != color_map.end()){
        new_string += color_map[input_color];
    }

    new_string += input;
    new_string += color.END;

    char* result = new char[new_string.length() + 1];
    std::strcpy(result, new_string.c_str());
    return result;
}