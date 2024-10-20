
#include <iostream>
#include <chrono>
#include <thread>
#include <Core/Window.hpp>
#include <Core/Input.hpp>
#include <Core/Texture.hpp>
#include <Core/Sound.hpp>
#include <Core/Text.hpp>

using namespace blox;

#define TARGET_FPS 240
#define NUM_OF_BRANCHES 6

enum class Side { LEFT, RIGHT, NONE };

Side branchPositions[NUM_OF_BRANCHES];

void updateBranches(int seed);

int main()
{
    try {
        // Create window
        Window window("Timber!!!", 1920, 1080, WindowStyle::FULLSCREEN);

//*************************************************************************************************************************

        // Create background texture
        Texture backgroundTexture;
        Texture::LoadFromFile(&backgroundTexture, "Timber/Assets/Texture/background.png");

        // Create background sprite
        Sprite backgroundSprite;
        backgroundSprite.SetTexture(&backgroundTexture);
        backgroundSprite.SetPosition({ 960, 540 });

//*************************************************************************************************************************

        // Create tree texture
        Texture treeTexture;
        Texture::LoadFromFile(&treeTexture, "Timber/Assets/Texture/tree2.png");

        // Create tree sprite
        Sprite treeSprite;
        treeSprite.SetTexture(&treeTexture);
        treeSprite.SetPosition({ 960, 630 });

        // Create tree 2 sprite
        Sprite tree2Sprite;
        tree2Sprite.SetTexture(&treeTexture);
        tree2Sprite.SetPosition({ 1350, 730 });
        tree2Sprite.SetScale({ 0.6, 1.0f });

        // Create tree 3 sprite
        Sprite tree3Sprite;
        tree3Sprite.SetTexture(&treeTexture);
        tree3Sprite.SetPosition({ 1590, 835 });
        tree3Sprite.SetScale({ 0.7, 1.0f });

        // Create tree 4 sprite
        Sprite tree4Sprite;
        tree4Sprite.SetTexture(&treeTexture);
        tree4Sprite.SetPosition({ 400, 780 });
        tree4Sprite.SetScale({ 0.6, 1.0f });

        // Create tree 5 sprite
        Sprite tree5Sprite;
        tree5Sprite.SetTexture(&treeTexture);
        tree5Sprite.SetPosition({ 100, 700 });
        tree5Sprite.SetScale({ 0.5, 1.1f });

//*************************************************************************************************************************

        // Create bee texture
        Texture beeTexture;
        Texture::LoadFromFile(&beeTexture, "Timber/Assets/Texture/bee.png");

        // Create bee sprite
        Sprite beeSprite;
        beeSprite.SetTexture(&beeTexture);
        beeSprite.SetPosition({ -2000, -2000 });

        // Bee properties
        bool isBeeActive = false;
        float beeSpeed = 0.0f;

//*************************************************************************************************************************

        // Create cloud texture
        Texture cloudTexture;
        Texture::LoadFromFile(&cloudTexture, "Timber/Assets/Texture/cloud.png");

        // Create cloud 1 sprite
        Sprite cloud1Sprite;
        cloud1Sprite.SetTexture(&cloudTexture);
        cloud1Sprite.SetPosition({ -2000, -2000 });

        // Cloud 1 properties
        bool isCloud1Active = false;
        float cloud1Speed = 0.0f;

        // Create cloud 2 sprite
        Sprite cloud2Sprite;
        cloud2Sprite.SetTexture(&cloudTexture);
        cloud2Sprite.SetPosition({ -2000, -2000 });

        // Cloud 2 properties
        bool isCloud2Active = false;
        float cloud2Speed = 0.0f;

        // Create cloud 3 sprite
        Sprite cloud3Sprite;
        cloud3Sprite.SetTexture(&cloudTexture);
        cloud3Sprite.SetPosition({ -2000, -2000 });

        // Cloud 3 properties
        bool isCloud3Active = false;
        float cloud3Speed = 0.0f;

//*************************************************************************************************************************

        Sprite branches[NUM_OF_BRANCHES];

        // Create branche texture
        Texture branchTexture;
        Texture::LoadFromFile(&branchTexture, "Timber/Assets/Texture/branch.png");

        // Crate branch sprites
        for (int i = 0; i < NUM_OF_BRANCHES; i++)
        {
            branches[i].SetTexture(&branchTexture);
            branches[i].SetPosition({ -2000, -2000 });
        }

//*************************************************************************************************************************

        // Create player texture
        Texture playerTexture;
        Texture::LoadFromFile(&playerTexture, "Timber/Assets/Texture/player.png");

        // Create player sprite
        Sprite playerSprite;
        playerSprite.SetTexture(&playerTexture);
        playerSprite.SetPosition({ 655, 264 });
        playerSprite.SetRotation({ 0, 180, 0 });

        // Player data
        Side playerSide = Side::LEFT;

        // Create RIP texture
        Texture ripTexture;
        Texture::LoadFromFile(&ripTexture, "Timber/Assets/Texture/rip.png");

        // Create player sprite
        Sprite ripSprite;
        ripSprite.SetTexture(&ripTexture);
        ripSprite.SetPosition({ -2000, -2000 });

        // Create Axe texture
        Texture axeTexture;
        Texture::LoadFromFile(&axeTexture, "Timber/Assets/Texture/axe.png");

        // Create player sprite
        Sprite axeSprite;
        axeSprite.SetTexture(&axeTexture);
        axeSprite.SetPosition({ -2000, 236 });

        const float AXE_POSITION_LEFT = 776;
        const float AXE_POSITION_RIGHT = 1151;

        // Create Axe texture
        Texture logTexture;
        Texture::LoadFromFile(&logTexture, "Timber/Assets/Texture/log.png");

        // Create player sprite
        Sprite logSprite;
        logSprite.SetTexture(&logTexture);
        logSprite.SetPosition({ -2000, 300 });

        // Log data
        bool logActive = false;
        float logSpeedX = 1000;
        float logSpeedY = -1500;

//*************************************************************************************************************************

        // Create time bar sprite
        Sprite timeBarSprite;
        timeBarSprite.SetColor(Color::RED);
        timeBarSprite.SetSize({ 600, 60 });
        timeBarSprite.SetPosition({ 960, 80 });

//*************************************************************************************************************************

        // Chop sound
        Sound chopSound("Timber/Assets/Audio/chop.wav");
        chopSound.SetVolume(0.3f);

        // Death sound
        Sound deathSound("Timber/Assets/Audio/death.wav");
        deathSound.SetVolume(0.2f);

        // Out of time sound
        Sound outOfTimeSound("Timber/Assets/Audio/out_of_time.wav");
        outOfTimeSound.SetVolume(0.3f);

//*************************************************************************************************************************

        // Create font
        Font font;
        Font::Load(&font, "Timber/Assets/Font/KOMIKAP.ttf", 64);

        // Create message text
        Text messageText("PRESS ENTER TO START!", font);
        messageText.SetPosition({ 960, 540 });

        // Create score text
        Text scoreText("SCORE: 0", font);
        scoreText.SetAnchor({ 0, 1 });
        scoreText.SetPosition({ 20, 1080 });

        // Create fps text
        Text fpsText("FPS: 9999", font);
        fpsText.SetAnchor({ 0, 1 });
        fpsText.SetPosition({ 1900 - fpsText.GetSize().width, 1080});

//*************************************************************************************************************************

        bool paused = true;
        bool firstRender = true;

        // Control the player input
        bool acceptInput = false;

        int score = 0;

        float resetTime = 6;
        float remainingTime = resetTime;

        int framesCount = 0;
        float framesTime = 0.0f;


        // Game loop
        while (window.IsOpen())
        {            
            // Update time
            Time::Update();

            // Update fps
            ++framesCount;
            framesTime += Time::GetDeltaTime();
            if (framesTime >= 1.0)
            {
                int fps = framesCount / framesTime;
                framesCount = 0;
                framesTime = 0.0f;

                std::stringstream ss;
                ss << "FPS: " << fps;
                fpsText.SetText(ss.str());
            }

            /***************
            * Handle Input *
            ****************/
            if (Input::KeyPressed(Key::ESCAPE))
            {
                window.Close();
                continue;
            }

            if (Input::KeyPressed(Key::ENTER))
            {
                paused = false;

                for (int i = 1; i < NUM_OF_BRANCHES; i++)
                {
                    branchPositions[i] = Side::NONE;
                }


                // Move the player into position
                playerSprite.SetPosition({ 655, 264 });
                playerSprite.SetRotation({ 0, 180, 0 });

                // Hide other
                ripSprite.SetPosition({ -2000, ripSprite.GetPosition().y });
                axeSprite.SetPosition({ -2000, axeSprite.GetPosition().y });
                logSprite.SetPosition({ -2000, logSprite.GetPosition().y });

                // Reset time
                remainingTime = resetTime;

                // Reset score
                score = 0;
                scoreText.SetText("SCORE: 0");

                acceptInput = true;
            }

            if (!paused)
            {
                if (acceptInput)
                {
                    if (Input::KeyPressed(Key::ARROW_RIGHT))
                    {
                        playerSide = Side::RIGHT;
                        playerSprite.SetPosition({ 1275, 264 });
                        playerSprite.SetRotation({ 0, 0, 0 });

                        axeSprite.SetPosition({ AXE_POSITION_RIGHT, axeSprite.GetPosition().y });
                        axeSprite.SetRotation({ 0, 0, 0 });

                        updateBranches(++score);

                        // Lunch log
                        logSprite.SetPosition({ 960, 300 });
                        logSpeedX = -5000;
                        logActive = true;

                        // Play chop sound
                        chopSound.Play();

                        // Increment score and time
                        std::stringstream ss;
                        ss << "SCORE: " << score;
                        scoreText.SetText(ss.str());

                        remainingTime += (1.0f / score) + 0.1;

                        acceptInput = false;
                    }

                    if (Input::KeyPressed(Key::ARROW_LEFT))
                    {
                        playerSide = Side::LEFT;

                        playerSprite.SetPosition({ 655, 264 });
                        playerSprite.SetRotation({ 0, 180, 0 });

                        axeSprite.SetPosition({ AXE_POSITION_LEFT, axeSprite.GetPosition().y });
                        axeSprite.SetRotation({ 0, 180, 0 });

                        updateBranches(++score);

                        // Lunch log
                        logSprite.SetPosition({ 960, 300 });
                        logSpeedX = 5000;
                        logActive = true;

                        // Play chop sound
                        chopSound.Play();

                        // Increment score and time
                        std::stringstream ss;
                        ss << "SCORE: " << score;
                        scoreText.SetText(ss.str());

                        remainingTime += (1.0f / score) + 0.1;

                        acceptInput = false;
                    }
                }

                if (Input::IsKeyReleased(Key::ARROW_RIGHT) || Input::IsKeyReleased(Key::ARROW_LEFT))
                {
                    axeSprite.SetPosition({ -2000, axeSprite.GetPosition().y });
                    acceptInput = true;
                }

                /***************
                * Update Scene *
                ****************/

                // Update the branch sprites
                for (int i = 0; i < NUM_OF_BRANCHES; i++)
                {
                    float height = 1080 - i * 150;
                    if (branchPositions[i] == Side::LEFT)
                    {
                        // Move the sprite to the left side
                        branches[i].SetPosition({ 610, height });
                        // Flip the sprite round the other way
                        branches[i].SetRotation({ 0, 0, 180 });
                    }
                    else if (branchPositions[i] == Side::RIGHT)
                    {
                        // Move the sprite to the right side
                        branches[i].SetPosition({ 1330, height });
                        // Set the sprite rotation to normal
                        branches[i].SetRotation({ 0, 0, 0 });
                    }
                    else
                    {
                        // Hide the branch
                        branches[i].SetPosition({ 3000, height });
                    }
                }

                // Update bee
                if (!isBeeActive)
                {
                    // Reset seed
                    srand((int)Time::GetTime() * 10);

                    beeSpeed = (rand() % 200) + 200; // [200, 400)
                    float beeHeight = (rand() % 500) + 80; // [80, 580)
                    beeSprite.SetPosition({ 2000, beeHeight });
                    isBeeActive = true;
                }
                else {
                    beeSprite.Move({ -beeSpeed * Time::GetDeltaTime(), 0});
                    if (beeSprite.GetPosition().x < -100)
                        isBeeActive = false;
                }

                if (!isCloud1Active)
                {
                    // Reset seed
                    srand((int)Time::GetTime() * 20);

                    cloud1Speed = (rand() % 200) + 200; // [200, 400)
                    float cloudHeight = (rand() % 300) + 700; // [700, 1000)
                    cloud1Sprite.SetPosition({ -200, cloudHeight });
                    isCloud1Active = true;
                }
                else {
                    cloud1Sprite.Move({ cloud1Speed * Time::GetDeltaTime(), 0 });
                    if (cloud1Sprite.GetPosition().x > 2000)
                        isCloud1Active = false;
                }

                if (!isCloud2Active)
                {
                    // Reset seed
                    srand((int)Time::GetTime() * 30);

                    cloud2Speed = (rand() % 200) + 200; // [200, 400)
                    float cloudHeight = (rand() % 300) + 700; // [700, 1000)
                    cloud2Sprite.SetPosition({ -200, cloudHeight });
                    isCloud2Active = true;
                }
                else {
                    cloud2Sprite.Move({ cloud2Speed * Time::GetDeltaTime(), 0 });
                    if (cloud2Sprite.GetPosition().x > 2000)
                        isCloud2Active = false;
                }

                if (!isCloud3Active)
                {
                    // Reset seed
                    srand((int)Time::GetTime() * 40);

                    cloud3Speed = (rand() % 200) + 200; // [200, 400)
                    float cloudHeight = (rand() % 300) + 700; // [700, 1000)
                    cloud3Sprite.SetPosition({ -200, cloudHeight });
                    isCloud3Active = true;
                }
                else {
                    cloud3Sprite.Move({ cloud3Speed * Time::GetDeltaTime(), 0 });
                    if (cloud3Sprite.GetPosition().x > 2000)
                        isCloud3Active = false;
                }

                if (logActive)
                {
                    logSprite.SetPosition({
                        logSprite.GetPosition().x + logSpeedX * Time::GetDeltaTime(),
                        logSprite.GetPosition().y + logSpeedY * Time::GetDeltaTime()
                    });

                    // Has the log reached the right hand edge?
                    if (logSprite.GetPosition().x < -100 ||
                        logSprite.GetPosition().x > 2000)
                    {
                        // Set it up ready to be a whole new log next frame
                        logActive = false;
                        logSprite.SetPosition({ -2000, -2000 });
                    }
                }

                // Handle hit
                if (branchPositions[NUM_OF_BRANCHES - 1] == playerSide)
                {
                    // death
                    paused = true;
                    acceptInput = false;

                    // Draw the gravestone
                    ripSprite.SetPosition(playerSprite.GetPosition());

                    // Hide other
                    playerSprite.SetPosition({ -2000, playerSprite.GetPosition().y });
                    axeSprite.SetPosition({ -2000, axeSprite.GetPosition().y });
                    logSprite.SetPosition({ -2000, logSprite.GetPosition().y });

                    // Play death sound
                    deathSound.Play();

                    messageText.SetText("YOU GOT HIT!");
                }

                // Update time bar
                remainingTime = Math::Max(remainingTime - Time::GetDeltaTime(), 0.0f);

                timeBarSprite.SetScale({
                    remainingTime / resetTime,
                    timeBarSprite.GetScale().y
                });

                if (remainingTime <= 0.0f)
                {
                    // death
                    paused = true;
                    acceptInput = false;

                    // Hide other
                    axeSprite.SetPosition({ -2000, axeSprite.GetPosition().y });
                    logSprite.SetPosition({ -2000, logSprite.GetPosition().y });

                    // Play death sound
                    outOfTimeSound.Play();

                    messageText.SetText("OUT OF TIME!");
                }
            }

            /***************
            * Render Scene *
            ****************/
            window.Clear();

            backgroundSprite.Render();
            cloud1Sprite.Render();
            cloud2Sprite.Render();
            cloud3Sprite.Render();

            tree2Sprite.Render();
            tree3Sprite.Render();
            tree4Sprite.Render();
            tree5Sprite.Render();

            // Update the branch sprites
            for (int i = 0; i < NUM_OF_BRANCHES; i++)
                branches[i].Render();

            treeSprite.Render();
            logSprite.Render();

            playerSprite.Render();
            axeSprite.Render();
            ripSprite.Render();

            beeSprite.Render();

            // GUI
            if (paused)
                messageText.Render();

            if (!paused)
                timeBarSprite.Render();

            scoreText.Render();
            fpsText.Render();

            window.Update();

            if (firstRender)
                firstRender = false;

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
    }

    Window::Destroy();

    return 0;
}

void updateBranches(int seed)
{
    // Move all the branches down one place
    for (int i = NUM_OF_BRANCHES - 1; i > 0; i--) {
        branchPositions[i] = branchPositions[i - 1];
    }
    // Spawn a new branch at position 0
    // LEFT, RIGHT or NONE
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
    case 0:
        branchPositions[0] = Side::LEFT;
        break;
    case 1:
        branchPositions[0] = Side::RIGHT;
        break;
    default:
        branchPositions[0] = Side::NONE;
        break;
    }
}
