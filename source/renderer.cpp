#include <3ds.h>
#include <string>
#include <chrono>
#include <thread>

#include <citro2d.h>
#include <citro3d.h>

#include "included/debug.hpp"
#include "included/renderer.hpp"
#include "included/c2d_handler.hpp"

C3D_RenderTarget* targetTop;
C3D_RenderTarget* targetBottom;

// Assuming these are declared somewhere
extern PrintConsole topScreenConsole;
extern PrintConsole bottomScreenConsole;

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

namespace RENDERER{
    void initialize_renderer(){
        romfsInit();
        //gfxInitDefault();
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
        C2D_Prepare();

        targetTop = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
        targetBottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    }

    void exit_renderer(){
        C3D_RenderTargetDelete(targetTop);
        C3D_RenderTargetDelete(targetBottom);
        gfxExit();
    }

    void run(gfxScreen_t screen, C2D_Image image_target, float x, float y, float d, float sx, float sy){
        C3D_RenderTarget* target = (screen == GFX_TOP) ? targetTop : targetBottom;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(target, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(target);
        C2D_DrawImageAt(image_target, x, y, d, nullptr, sx, sy);
		C3D_FrameEnd(0);
    }
}

namespace LAUNCHER{
    const char* launcher_background_path = "gfx/launcher.t3x";
    C2D_Image launcher_background;

    void load_launcher_background(){
        launcher_background = C2D_HANDLER::load_c2d_image(launcher_background_path);
    }

    void render_launcher_background(gfxScreen_t screen) {
        RENDERER::run(screen, launcher_background, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    }
}