#include <iostream>
#include "Game.h"
#include "raylib.h"
#include "Constants.h"
#include "managers/ResourceManager.h"

Game::Game() : m_running(true), m_currentState(nullptr), m_debugUpdateDuration(0.0), m_debugDrawDuration(0.0)
{
    Init();
    PlayMusicStream(ResourceManager::GetInstance().GetBackgroundMusic());
}

Game::~Game()
{
    Shutdown();
}

void Game::Init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "WhiteJack Game");

    SetTargetFPS(60);

    Image icon = LoadImage("assets/01_kerenel_Cards.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
}

void Game::Shutdown()
{

    CloseWindow();
}

void Game::Run()
{
    while (m_running)
    {
        UpdateMusicStream(ResourceManager::GetInstance().GetBackgroundMusic());

        if (WindowShouldClose())
        {
            m_running = false;
            break;
        }

        float dt = GetFrameTime();

        double timeStart = GetTime();
        if (m_currentState)
        {
            m_currentState->Update(dt, this);
        }
        m_debugUpdateDuration = GetTime() - timeStart; // Store duration in seconds

        // MEASURE DRAW
        timeStart = GetTime();
        Draw();
        m_debugDrawDuration = GetTime() - timeStart;
    }
}

void Game::Update(float dt)
{
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    if (m_currentState)
    {
        m_currentState->Draw();
    }

    int fps = GetFPS();
    Color fpsColor = (fps > 50) ? GREEN : RED;

    double updateMS = m_debugUpdateDuration * 1000.0;
    double drawMS = m_debugDrawDuration * 1000.0;

    Color updateColor = (updateMS > 8.0) ? RED : WHITE;
    Color drawColor = (drawMS > 8.0) ? RED : WHITE;

    DrawText(TextFormat("FPS: %d", fps), 10, 500, 10, fpsColor);
    DrawText(TextFormat("Update: %.2f ms", updateMS), 10, 520, 10, updateColor);
    DrawText(TextFormat("Draw: %.2f ms", drawMS), 10, 540, 10, drawColor);

    EndDrawing();
}

void Game::ChangeState(IGameState *newState)
{
    if (m_currentState)

    {
        m_currentState->OnExit();
        delete m_currentState;
    }

    m_currentState = newState;

    if (m_currentState)
    {
        m_currentState->OnEnter();
    }
}