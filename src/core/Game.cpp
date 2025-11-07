#include <iostream>
#include "Game.h"
#include "raylib.h"
#include "Constants.h"
Game::Game() : m_running(true), m_currentState(nullptr)
{
    Init();
}
Game::~Game()
{
    Shutdown();
}
void Game::Init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "WhiteJack Game");
    SetTargetFPS(60);

    Image icon = LoadImage("assets/cardBack.png");
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

        if (WindowShouldClose())
        {
            m_running = false; // This will make the loop stop
            break;
        }

        float dt = GetFrameTime();
        if (m_currentState)
        {
            m_currentState->Update(dt, this);
        }
        Draw();
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