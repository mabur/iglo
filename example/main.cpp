#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iglo/input.hpp>
#include <iglo/window.hpp>

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        handleSdlError("SDL_Init");
    }
    const auto window = makeFullScreenWindow(320, 200, "Example");
    for (;;) {
        registerFrameInput(window.renderer);
        if (hasReceivedQuitEvent()) {
            break;
        }
        if (isKeyClicked(SDL_SCANCODE_ESCAPE)) {
            break;
        }
        if (isLeftMouseButtonClicked()) {
            break;
        }
        presentWindow(window);
    }
    destroyWindow(window);
    return 0;
}
