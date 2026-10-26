// Switch replacements for the recompui calls and the banjo config getters of the PC port.
// CV64's patches read none of the PC menu's gameplay options, so the getters return the PC defaults;
// the Switch options live in the NX Options menu (nx_settings.cpp).
#include <cstdio>

#include <SDL.h>
#include <switch.h>

#include "banjo_config.h"
#include "banjo_sound.h"
#include "recomp.h"
#include "recompui/recompui.h"
#include "recompui/renderer.h"

extern SDL_Window* cvnx_window;
extern const char* cvnx_game_title;  // main_switch.cpp

void recompui::message_box(const char* msg) {
    fprintf(stderr, "[CVNX] %s\n", msg);
    ErrorApplicationConfig config;
    errorApplicationCreate(&config, cvnx_game_title, msg);
    errorApplicationShow(&config);
}

void recompui::get_window_size(int& width, int& height) {
    if (cvnx_window == nullptr) {
        width = 1280;
        height = 720;
        return;
    }
    SDL_GetWindowSize(cvnx_window, &width, &height);
}

bool recompui::renderer::RT64HighPrecisionFBEnabled() {
    return false;
}

void banjo::init_config() {}

void banjo::open_quit_game_prompt() {}

banjo::CameraInvertMode banjo::get_camera_invert_mode() { return CameraInvertMode::InvertX; }
banjo::CameraInvertMode banjo::get_third_person_camera_mode() { return CameraInvertMode::InvertX; }
banjo::CameraInvertMode banjo::get_flying_and_swimming_invert_mode() { return CameraInvertMode::InvertY; }
banjo::CameraInvertMode banjo::get_first_person_invert_mode() { return CameraInvertMode::InvertY; }
banjo::AnalogCamMode banjo::get_analog_cam_mode() { return AnalogCamMode::Off; }
uint32_t banjo::get_analog_cam_sensitivity() { return 3; }
banjo::NoteSavingMode banjo::get_note_saving_mode() { return NoteSavingMode::Off; }
banjo::CutsceneAspectRatioMode banjo::get_cutscene_aspect_ratio_mode() { return CutsceneAspectRatioMode::Clamp16x9; }
int banjo::get_bgm_volume() { return 100; }

// Pumps RmlUi callbacks registered by mods; there is no RmlUi on Switch.
extern "C" void recomp_run_ui_callbacks(uint8_t*, recomp_context*) {}

// The PC port's patches print debug text every frame through recomp_puts, one character at a time. On Switch stdout
// is the unbuffered log on the SD card, so that was hundreds of SD writes per frame on the game thread. The game's
// own text goes nowhere here; src/game/recomp_api.cpp's version is renamed away in switch/CMakeLists.txt.
extern "C" void recomp_puts(uint8_t*, recomp_context*) {}
