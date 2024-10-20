
#include <thread>

#include <Util/Common.hpp>
#include <Core/Window.hpp>
#include <Core/Input.hpp>
#include <Core/Text.hpp>
#include <Core/Sound.hpp>

#include <Bat.hpp>
#include <Ball.hpp>

using namespace blox;

int main()
{
    try {
        // Create window
        Window window("Pong", 1920, 1080, WindowStyle::FULLSCREEN);

        int score = 0;
        int lives = 3;

        Bat bat;
        Ball ball;

        Font font("Pong/Assets/Font/DS-DIGI.ttf", 75);

        Text hudText("", font);
        hudText.SetAnchor({ 0.0f, 1.0f });
        hudText.SetPosition({ 20, 1080 });

        Text messageText("PRESS ENTER TO START!", font);
        messageText.SetPosition({ 960, 540 });

        Text fpsText("FPS: 9999", font);
        fpsText.SetAnchor({ 0.0f, 1.0f });
        fpsText.SetPosition({ 1600, 1080 });

        // Game over sound
        Sound gameOverSound("Pong/Assets/Audio/game_over.wav");
        gameOverSound.SetVolume(0.3f);

        bool paused = true;

        while (window.IsOpen())
        {
            Time::Update();
            window.UpdateFPS();

            if (Input::KeyPressed(Key::ESCAPE))
            {
                window.Close();
                continue;
            }

            if (Input::KeyPressed(Key::ENTER) || Input::KeyPressed(Key::NUMPAD_ENTER))
            {
                score = 0;
                lives = 3;
                bat.Reset();
                ball.Reset();
                paused = false;
            }

            if (!paused)
            {
                if (Input::KeyHeld(Key::ARROW_LEFT))
                {
                    bat.MoveLeft();
                }
                else
                {
                    bat.StopLeft();
                }

                if (Input::KeyHeld(Key::ARROW_RIGHT))
                {
                    bat.MoveRight();
                }
                else
                {
                    bat.StopRight();
                }

                bat.Update();
                ball.Update(bat);

                if (ball.HasHitBat())
                {
                    ++score;
                    bat.SpeedUp();
                }

                if (ball.HasHitBottom())
                {
                    if (--lives == 0)
                    {
                        paused = true;
                        messageText.SetText("GAME OVER!");
                        gameOverSound.Play();
                    }
                }
            }

            std::stringstream ss;
            ss << "SCORE: " << score << "  |  LIVES: " << lives;
            hudText.SetText(ss.str());

            fpsText.SetText("FPS: " + std::to_string(window.GetFPS()));

            window.Clear();

            if (!paused)
            {
                bat.Render();
                ball.Render();
            }

            hudText.Render();
            fpsText.Render();

            if (paused)
                messageText.Render();
            
            window.Update();

            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
    }

    Window::Destroy();

    return 0;
}