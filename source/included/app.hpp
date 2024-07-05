#include <string>
using namespace std;

const char* colored_text(const std::string& input_color, const std::string& special_effect, const char* input);

class COLORS{
    public:

        const char* PREFIX = "\033[0;";
        const char* SPECIAL = "\033[";

        const char* RED = "31m";
        const char* GREEN = "32m";
        const char* YELLOW = "33m";
        const char* BLUE = "34m";
        const char* MAGENTA = "35m";
        const char* CYAN = "36m";
        const char* WHITE = "37m";
        const char* RESET = "0m";
        const char* BOLD = "1m";
        const char* FAINT = "2m";
        const char* ITALIC = "3m";
        const char* UNDERLINE = "4m";
        const char* BLINK = "5m";
        const char* RAPID_BLINK = "6m";
        const char* REVERSE = "7m";
        const char* HIDDEN = "8m";
        const char* STRIKETHROUGH = "9m";
        const char* DOUBLE_UNDERLINE = "21m";
        const char* NORMAL = "22m";
        const char* NO_ITALIC = "23m";
        const char* NO_UNDERLINE = "24m";
        const char* NO_BLINK = "25m";
        const char* NO_REVERSE = "27m";
        const char* NO_HIDDEN = "28m";
        const char* NO_STRIKETHROUGH = "29m";
        const char* FG_BLACK = "30m";
        const char* FG_RED = "31m";
        const char* FG_GREEN = "32m";
        const char* FG_YELLOW = "33m";
        const char* FG_BLUE = "34m";
        const char* FG_MAGENTA = "35m";
        const char* FG_CYAN = "36m";
        const char* FG_WHITE = "37m";
        const char* BG_BLACK = "40m";
        const char* BG_RED = "41m";
        const char* BG_GREEN = "42m";
        const char* BG_YELLOW = "43m";
        const char* BG_BLUE = "44m";
        const char* BG_MAGENTA = "45m";
        const char* BG_CYAN = "46m";
        const char* BG_WHITE = "47m";
        const char* BG_RESET = "49m";

        const char* END = "\x1b[0m";
};