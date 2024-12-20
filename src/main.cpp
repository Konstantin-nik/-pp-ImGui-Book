#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <SDL_render.h>
#include <iostream>

// Функция для инициализации SDL2 и ImGui
bool InitializeSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Dear ImGui Demo", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        1280, 720, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Инициализация ImGui
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
    ImGui::StyleColorsDark();

    return true;
}

// Основной цикл приложения
void Run(SDL_Window* window, SDL_Renderer* renderer) {
    bool running = true;
    SDL_Event event;
    bool showNewWindow = false;
    
    while (running) {
        Uint32 startTime = SDL_GetTicks(); // время начала кадра

        // Обработка событий SDL
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Начало кадра
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Рисование интерфейса с использованием ImGui
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple ImGui window.");
        if (ImGui::Button("Press me")) {
            ImGui::Text("You're cool!");
        }

        if (ImGui::Button("Open New Window")) {
            showNewWindow = true; 
        }

        if (showNewWindow) {
            ImGui::SetNextWindowSize(ImVec2(200, 100));
            ImGui::Begin("New Window", &showNewWindow);

            ImGui::Text("This is a new window!");
            if (ImGui::Button("Close")) {
                showNewWindow = false;
            }

            ImGui::End();
        }
        
        if (ImGui::Button("Quit")) {
            running = false;
        }

        ImGui::End();

        // Отображение интерфейса
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);

        // Контроль FPS
        Uint32 endTime = SDL_GetTicks(); // время окончания кадра
        Uint32 frameTime = endTime - startTime; // время одного кадра
        if (frameTime < 16) { // если кадр обработан быстрее, чем 16 мс
            SDL_Delay(16 - frameTime); // Задержка для компенсации
        }

        startTime = endTime; // обновляем время начала кадра
    }
}

// Очищение ресурсов
void Cleanup(SDL_Window* window, SDL_Renderer* renderer) {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!InitializeSDL(window, renderer)) {
        return -1;
    }

    Run(window, renderer);

    Cleanup(window, renderer);
    return 0;
}
