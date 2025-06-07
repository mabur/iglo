#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iglo/input.hpp>
#include <iglo/window.hpp>

Uint32 packColorArgb(Uint32 a, Uint32 r, Uint32 g, Uint32 b) {
    return (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

uint32_t* generateExamplePixels(int width, int height) {
    auto pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    for (auto y = 0; y < height; ++y) {
        for (auto x = 0; x < width; ++x) {
            auto alpha = 255;
            auto red = 255;
            auto green = y * 255 / height;
            auto blue = x * 255 / width;
            pixels[y * width + x] = packColorArgb(alpha, red, green, blue);
        }
    }
    return pixels;
}

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        handleSdlError("SDL_Init");
    }
    auto WIDTH = 320;
    auto HEIGHT = 240;
    auto SCALE = 5;
    auto TITLE = "Iglo Example";
    auto window = makeDesktopWindow(WIDTH, HEIGHT, SCALE, TITLE);
    auto pixels = generateExamplePixels(WIDTH, HEIGHT);
    for (;;) {
        registerFrameInput(window.renderer);
        if (hasReceivedQuitEvent() || isKeyClicked(SDL_SCANCODE_ESCAPE)) {
            break;
        }
        drawPixels(window, pixels);
        presentWindow(window);
    }
    destroyWindow(window);
    return 0;
}
