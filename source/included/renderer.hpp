#include <citro2d.h>
#include <citro3d.h>

namespace RENDERER{
    extern void initialize_renderer();
    extern void exit_renderer();
    extern void run(gfxScreen_t screen, C2D_Image image_target, float x, float y, float d, float sx, float sy);
}

namespace LAUNCHER{
    extern void load_launcher_background();
    extern void render_launcher_background(gfxScreen_t screen);
}