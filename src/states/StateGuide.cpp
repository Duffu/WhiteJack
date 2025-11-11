#include "StateGuide.h"
#include "raylib.h"
#include "StateGameplay.h"
#include "string.h"
StateGuide::StateGuide()
{
    m_guideState = GuideState::INTRODUCTION;
    m_charCounter = 0;
    StartTimer(m_typewriterTimer, 0.01f);

    m_clickCount = 0;
    // Start the timer as "done" so it doesn't do anything
    StartTimer(m_doubleClickTimer, 0.0f);
}

StateGuide::~StateGuide()
{
}

void StateGuide::Update(float dt, Game *game)
{
    UpdateTimer(m_doubleClickTimer, dt);
    if (IsKeyPressed(KEY_ENTER))
    {
        m_charCounter = 0;
        switch (m_guideState)
        {
        case GuideState::INTRODUCTION:
            m_guideState = GuideState::PLAYGUIDE1;
            break;
        case GuideState::PLAYGUIDE1:
            m_guideState = GuideState::PLAYGUIDE2;
            break;
        case GuideState::PLAYGUIDE2:
            m_guideState = GuideState::PLAYGUIDE3;
            break;
        case GuideState::PLAYGUIDE3:
            m_guideState = GuideState::PLAYGUIDE4;
            break;
        case GuideState::PLAYGUIDE4:
            m_guideState = GuideState::END;
            break;
        case GuideState::END:
            game->ChangeState(new StateGameplay());
            break;
        }
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (TimerDone(m_doubleClickTimer))
        {
            m_clickCount = 1;
            // Start a 0.25 second window for the next click
            StartTimer(m_doubleClickTimer, 0.25f);
        }
        else
        {
            m_clickCount++;

            if (m_clickCount == 2)
            {
                game->ChangeState(new StateGameplay());
                return; // Stop processing this state
            }
        }
    }

    // TYPEWRITER LOGIC
    UpdateTimer(m_typewriterTimer, dt);
    if (TimerDone(m_typewriterTimer))
    {
        m_charCounter++;
        StartTimer(m_typewriterTimer, 0.01f);
    }
}

void StateGuide::Draw()
{

    DrawText("double click to skip the Guide", 955, 680, 20, WHITE);
    int y = 100;
    int fontSize = 20;
    int headerSize = 25;
    int titleSize = 30;
    int x = 100;
    bool ending = false;

    bool isTypingDone = false;
    switch (m_guideState)
    {
    case GuideState::INTRODUCTION:
    {
        int charCount = m_charCounter; // Store a copy for this frame

        const char *line1 = "Welcome to WhiteJack (Demo)";
        const char *line2 = "This guide will take less than a minute.";
        const char *line3 = "This is just a simple demo to show the core logic. No fancy graphics, just the mechanics.";
        const char *line4 = "This game is made with C++ without an engine.";

        // Draw the text
        DrawText(TextSubtext(line1, 0, charCount), 350, y, 40, YELLOW);
        y += 80;
        charCount -= strlen(line1);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line2, 0, charCount), x, y, fontSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line2);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line3, 0, charCount), x, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line3);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line4, 0, charCount), x, y, fontSize, WHITE);
            y += 150;
        }
        charCount -= strlen(line4);

        if (charCount > 0)
            isTypingDone = true; // All text is drawn
    }
    break;
    case GuideState::PLAYGUIDE1:
    {
        int charCount = m_charCounter;

        const char *line1 = "Basic Controls (a normal BlackJack game but as a dirty dealer)";
        const char *line2 = "[H] - Hit: Take another card.";
        const char *line3 = "[S] - Stand: End your turn.";
        const char *line4 = "[F] - Flip: Flips your last card (you must flip to Hit).";
        const char *line5 = "WARNING: Hitting over 17 or Standing under 17 is illegal.";
        const char *line6 = "Illegal moves are ignored and you will lose a Trust Heart.";

        // Draw the text
        DrawText(TextSubtext(line1, 0, charCount), (1600 - MeasureText(line1, 40)) / 2, y, 30, YELLOW);
        y += 80;
        charCount -= strlen(line1);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line2, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line2);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line3, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line3);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line4, 0, charCount), x, y, headerSize, WHITE);
            y += 80;
        }
        charCount -= strlen(line4);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line5, 0, charCount), x, y, fontSize, RED);
            y += 30;
        }
        charCount -= strlen(line5);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line6, 0, charCount), x, y, fontSize, RED);
            y += 30;
        }
        charCount -= strlen(line6);

        if (charCount > 0)
            isTypingDone = true; // All text is drawn
    }
    break;
    case GuideState::PLAYGUIDE2:
    {

        const char *title = "Punishments & Mechanics";

        // Patience Meter
        const char *line1 = "Patience Meter (Top-Left, Red)";
        const char *line2 = "This is the client's patience.";
        const char *line3 = "It goes UP when the client wins, and DOWN when they lose or tie.";
        const char *line4 = "If it hits Null, the client leaves and you lose.";
        const char *line5 = "Tip: If it gets low, let the client win to calm them down. you can do it by cheating";

        // Trust Hearts
        const char *line6 = "Trust Hearts (Top-Right, Red Hearts)";
        const char *line7 = "These are your 'lives'.";
        const char *line8 = "You lose a heart if you get caught cheating or make an 'illegal' move...";
        const char *line9 = "...(like hitting on 17). Lose them all, and it's Game Over";
        const char *line10 = "Goal: Make the client lose, but keep their patience high enough to stay..";

        // Cheating minigames explained

        int charCount = m_charCounter;

        DrawText(TextSubtext(title, 0, charCount), (1280 - MeasureText(title, titleSize)) / 2, y, titleSize, YELLOW);
        y += 80;
        charCount -= strlen(title);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line1, 0, charCount), x, y, headerSize, RED);
            y += 40;
        }
        charCount -= strlen(line1);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line2, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line2);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line3, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line3);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line4, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line4);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line5, 0, charCount), x + 40, y, fontSize, SKYBLUE);
            y += 80;
        } // Tip color
        charCount -= strlen(line5);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line6, 0, charCount), x, y, headerSize, GREEN);
            y += 40;
        }
        charCount -= strlen(line6);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line7, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line7);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line8, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line8);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line9, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 30;
        }
        charCount -= strlen(line9);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line10, 0, charCount), x + 40, y, fontSize, WHITE);
        }
        charCount -= strlen(line10);

        if (charCount > 0)
            isTypingDone = true; // All text is drawn
    }

    break;
    case GuideState::PLAYGUIDE3:
    {
        int charCount = m_charCounter;

        const char *title = "Cheats & Combos";
        const char *line1 = "[P] - Peek at Deck";
        const char *line2 = "Lets you see the *next* card in the deck.";
        const char *line3 = "[M] - Peek at Hand";
        const char *line4 = "Lets you see your *own* face-down hole card.";
        const char *line5 = "[L] - Swap Card";
        const char *line6 = "Lets you swap your hole card with the top card of the deck.";
        const char *line7 = "Tip: Use [P] and [M] first to know if the [L] swap is a good idea!";

        // Draw the text
        DrawText(TextSubtext(title, 0, charCount), (1280 - MeasureText(title, 40)) / 2, y, 40, YELLOW);
        y += 80;
        charCount -= strlen(title);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line1, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line1);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line2, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line2);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line3, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line3);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line4, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line4);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line5, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line5);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line6, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 60;
        }
        charCount -= strlen(line6);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line7, 0, charCount), x, y, 25, GREEN);
            y += 30;
        } // Tip color
        charCount -= strlen(line7);

        if (charCount > 0)
            isTypingDone = true; // All text is drawn
    }
    break;
    case GuideState::PLAYGUIDE4:
    {
        int charCount = m_charCounter;

        const char *title = "Cheat Minigames";
        const char *line1 = "Each cheat opens a fast-paced minigame.";
        const char *line2 = "Peek at Deck [P]:";
        const char *line3 = "A bar with a moving arrow. Hit SPACE in the green zone.";
        const char *line4 = "Peek at Hand [M]:";
        const char *line5 = "A harder version. You must hit 3 smaller, random zones.";
        const char *line6 = "Swap Card [L]:";
        const char *line7 = "A card appears randomly. Click it 5 times before the timer runs out.";

        DrawText(TextSubtext(title, 0, charCount), (1280 - MeasureText(title, titleSize)) / 2, y, titleSize, YELLOW);
        y += 80;
        charCount -= strlen(title);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line1, 0, charCount), x, y, 25, WHITE);
            y += 60;
        }
        charCount -= strlen(line1);
        if (charCount > 0)
        {
            DrawText(TextSubtext(line2, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line2);
        if (charCount > 0)
        {
            DrawText(TextSubtext(line3, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 60;
        }
        charCount -= strlen(line3);
        if (charCount > 0)
        {
            DrawText(TextSubtext(line4, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line4);
        if (charCount > 0)
        {
            DrawText(TextSubtext(line5, 0, charCount), x + 40, y, fontSize, WHITE);
            y += 60;
        }
        charCount -= strlen(line5);
        if (charCount > 0)
        {
            DrawText(TextSubtext(line6, 0, charCount), x, y, headerSize, WHITE);
            y += 40;
        }
        charCount -= strlen(line6);
        if (charCount > 0)
        {
            DrawText(TextSubtext(line7, 0, charCount), x + 40, y, fontSize, WHITE);
        }
        charCount -= strlen(line7);

        if (charCount > 0)
            isTypingDone = true;
    }

    break;
    case GuideState::END:
    {
        int charCount = m_charCounter;

        const char *title = "That's It!";
        const char *line1 = "Future features will include a Mainmenu, leveling system and more complex cheats.";
        const char *line2 = "Have fun, and don't get caught.";
        // Draw the text
        DrawText(TextSubtext(title, 0, charCount), (1280 - MeasureText(title, 40)) / 2, y, 40, YELLOW);
        y += 80;
        charCount -= strlen(title);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line1, 0, charCount), x, y, fontSize, WHITE);
            y += 60;
        }
        charCount -= strlen(line1);

        if (charCount > 0)
        {
            DrawText(TextSubtext(line2, 0, charCount), x, y, 30, GREEN);
            y += 150;
        }
        charCount -= strlen(line2);
        if (charCount > 0)
            isTypingDone = true; // All text is drawn
    }
    }
    if (isTypingDone && !(ending))
    {
        DrawText("Press [ENTER] to continue...", 450, 600, 30, GREEN);
    }
}
void StateGuide::OnEnter()
{
    Music &bgm = ResourceManager::GetInstance().GetBackgroundMusic();
    SetMusicVolume(bgm, 0.02f);
}
void StateGuide::OnExit() {}