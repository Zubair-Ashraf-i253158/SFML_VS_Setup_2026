#include "LevelSystem.h"
#include "Collision.h"
#include "HUD.h"
#include "SplashScreen.h"
#include "LoginScreen.h"
#include "SignupScreen.h"
#include "AuthSystem.h"
#include "LevelSelect.h"
#include "MainMenu.h"
#include "Leaderboard.h"
#include "Shop.h"
#include "Player.h"
#include"item.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    Player player;
    Player player2;
    Level level;
    HUD h;
    SplashScreen splash;
    LoginScreen loginScreen;
    SignupScreen signupScreen;
    AuthSystem auth;
    MainMenu mainMenu;
    Shop shop;
    LevelSelect levelSelect;
    Leaderboard leaderboard;
    bool multiPl = false;
    bool paused = false;
    sf::Music music;
    int currentTrack = -1; //-1 nothing playing yet
    //0 menu, 1 level, 2 boss
     //alive 
    bool botomAlive[5] = {}, foogaAlive[2] = {},
        tornadoAlive[2] = {}, invAlive[5] = {};
    bool mogeraAlive = false, gamaAlive = false;

    auto playTrack = [&](int track) {
        if (currentTrack == track) return; //already playing this one
        currentTrack = track;
        music.stop();
        if (track == 0) music.openFromFile("assets/Music/menu.ogg");
        else if (track == 1) music.openFromFile("assets/Music/level.ogg");
        else if (track == 2) music.openFromFile("assets/Music/boss.ogg");
        music.setLoop(true);
        music.setVolume(60);
        music.play();
        };

    Item* items = level.getItems();
    int maxItems = level.getMaxItems();
    player.setPos(500, 400);
    player2.setPlayer2(true);
    player2.setPos(200, 400);

    // 0=splash 1=login 2=signup 3=mainmenu
    // 4=levelselect 5=playing 6=leaderboard
	//7=shop
    int gameState = 0;

    while (window.isOpen())
    {
        sf::Event event;
        event.type = sf::Event::Count;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			//escape key se pause/unpause karo
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape &&
                gameState == 5)
            {
                paused = !paused;
            }

            if (gameState == 5 && paused) {
                if (event.key.code == sf::Keyboard::S) {
                    paused = false;
                    gameState = 7;
                }
                else if (event.key.code == sf::Keyboard::M) {
                    paused = false;
                    gameState = 3;
                }
                else if (event.key.code == sf::Keyboard::X)
                    window.close();
            }
            if (gameState == 7 &&
                (event.key.code == sf::Keyboard::Escape ||
                    event.key.code == sf::Keyboard::Q))
            {
                gameState = 5;
                paused = true;
            }
        }

    
       

        window.clear();
		//Music switch karo game state ke hisab sa
        if (gameState == 0 || gameState == 1 || gameState == 2 ||
            gameState == 3 || gameState == 4 || gameState == 6 || gameState == 7)
        {
            playTrack(0); //menu music
        }
        else if (gameState == 5 || gameState == 8)
        {
            int lvl = level.getCurrentLevel();
            if (lvl == 5 || lvl == 10)
                playTrack(2); //boss music
            else
                playTrack(1); //level music
        }


        if (gameState == 0) //splash
        {
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed)
                gameState = 1;
            splash.draw(window);
        }
        else if (gameState == 1) //login
        {
            int result = loginScreen.update(event, auth);
            if (result == 3) gameState = 3;
            if (result == 2) gameState = 2;
            loginScreen.draw(window);
        }
        else if (gameState == 2) //signup
        {
            int result = signupScreen.update(event, auth);
            if (result == 1) gameState = 1;
            signupScreen.draw(window);
        }
        else if (gameState == 3) //main menu
        {
            int result = mainMenu.update(event);
            if (result == 1) //story yani start
            {
                multiPl = false;
                player = Player();
                player.setPos(500, 400);
                level.loadLevel(1);
                gameState = 5;
            }
            if (result == 2) //multiplayer
            {
                multiPl = true;
                player = Player();
                player2 = Player();
                player.setPos(500, 400);
                player2.setPlayer2(true);
                player2.setPos(200, 400);
                level.loadLevel(1);
                gameState = 5;
            }
            if (result == 3) gameState = 4; //level select
            if (result == 4)
            {
                gameState = 7;
               
            }
            if (result == 5) gameState = 6; // leaderboard
            if (result == 6) gameState = 1; // logout
            mainMenu.draw(window);
        }
        else if (gameState == 4) // level select
        {
            int lvl = levelSelect.update(event);
            if (lvl > 0)
            {
                level.loadLevel(lvl);
                gameState = 5;
            }
            levelSelect.draw(window);
        }
        else if (gameState == 5) // playing
        {
           



            if (!paused)
            {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape)
                    paused = true;
                Enemy* enemies[20];
                int ecount = 0;
                for (int i = 0; i < level.getBotomCount(); i++)
                    enemies[ecount++] = &level.getBotoms()[i];
                for (int i = 0; i < level.getFoogaCount(); i++)
                    enemies[ecount++] = &level.getFoogas()[i];
                for (int i = 0; i < level.getTornadoCount(); i++)
                    enemies[ecount++] = &level.getTornados()[i];
                for (int i = 0; i < level.getInvCount(); i++)
                    enemies[ecount++] = &level.getInvisibles()[i];
                if (level.getCurrentLevel() == 5)
                    enemies[ecount++] = &level.getMogera();
                if (level.getCurrentLevel() == 10)
                    enemies[ecount++] = &level.getGama();

               

                for (int i = 0; i < level.getBotomCount(); i++)
                    botomAlive[i] = level.getBotoms()[i].getZinda();
                for (int i = 0; i < level.getFoogaCount(); i++)
                    foogaAlive[i] = level.getFoogas()[i].getZinda();
                for (int i = 0; i < level.getTornadoCount(); i++)
                    tornadoAlive[i] = level.getTornados()[i].getZinda();
                for (int i = 0; i < level.getInvCount(); i++)
                    invAlive[i] = level.getInvisibles()[i].getZinda();
                if (level.getCurrentLevel() == 5)
                    mogeraAlive = level.getMogera().getZinda();
                if (level.getCurrentLevel() == 10)
                    gamaAlive = level.getGama().getZinda();

                for (int i = 0; i < maxItems; i++) {//power
                    //Player 1 Collision
                    if (items[i].active && player.getBounds().intersects(items[i].getBounds())) {
                        if (items[i].type == GEM) {
                            items[i].active = false;
                            player.addScore(100);
                            player.addGem(1);
                        }
                        else if (items[i].type == STAR) {
                            items[i].active = false;
                            player.applyPowerUp();
                        }
                    }
                    //Player 2 Collision
                    if (multiPl && items[i].active && player2.getBounds().intersects(items[i].getBounds())) {
                        if (items[i].type == GEM) {
                            items[i].active = false;
                            player2.addScore(100);
                            player2.addGem(1);
                        }
                        else if (items[i].type == STAR) {
                            items[i].active = false;
                            player2.applyPowerUp();
                        }
                    }
                }  //update
                            // player update mein ye sab hota hai
            // player movement (left right jump)
            // gravity apply hoti hai
            // platform collision check hoti hai
            // snowball throw hoti hai
            // snowball enemy ko hit karta hai
            // player encased enemy ko kick karta hai
            // rolling snowball chain kill karta hai
            // player enemy ko touch kare to life down
            //hover effect
                player.update(level.getPlatforms(), level.getPlatformCount(), enemies, ecount);
                if (multiPl)
                    player2.update(level.getPlatforms(), level.getPlatformCount(), enemies, ecount);

                level.update(player);

                //score
                for (int i = 0; i < level.getBotomCount(); i++)
                    if (botomAlive[i] && !level.getBotoms()[i].getZinda())
                    {
                        int p = 100 + rand() % 401; player.addScore(p);
                        if (multiPl) player2.addScore(p);
                        //item drop ho jaia
                        float dropX = level.getBotoms()[i].getBounds().left;
                        float dropY = level.getBotoms()[i].getBounds().top;

                        if (level.getBotoms()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }

                    }

                for (int i = 0; i < level.getFoogaCount(); i++)
                    if (foogaAlive[i] && !level.getFoogas()[i].getZinda())
                    {
                        int p = 200 + rand() % 601; player.addScore(p);
                        if (multiPl) player2.addScore(p);
                        float dropX = level.getFoogas()[i].getBounds().left;
                        float dropY = level.getFoogas()[i].getBounds().top;

                        if (level.getFoogas()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
                    }

                for (int i = 0; i < level.getTornadoCount(); i++)
                    if (tornadoAlive[i] && !level.getTornados()[i].getZinda())
                    {
                        int p = 300 + rand() % 901; player.addScore(p);
                        if (multiPl) player2.addScore(p);
                        float dropX = level.getTornados()[i].getBounds().left;
                        float dropY = level.getTornados()[i].getBounds().top;

                        if (level.getTornados()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
                    }

                for (int i = 0; i < level.getInvCount(); i++)
                    if (invAlive[i] && !level.getInvisibles()[i].getZinda())
                    {
                        int p = 500 + rand() % 1001; player.addScore(p);
                        if (multiPl) player2.addScore(p);
                        float dropX = level.getInvisibles()[i].getBounds().left;
                        float dropY = level.getInvisibles()[i].getBounds().top;

                        if (level.getInvisibles()[i].isChainKilled())
                        {
                            level.spawnItem(dropX, dropY, STAR); //drop
                        }
                        //star 20% chance se drop hoga
                        if (rand() % 100 < 20) {
                            level.spawnItem(dropX, dropY, STAR);
                        }
                    }

                if (level.getCurrentLevel() == 5 && mogeraAlive && !level.getMogera().getZinda())
                {
                    player.addScore(5000); 
                    if (multiPl) player2.addScore(5000);
                    for (int i = 0; i < 10; i++)
                        level.spawnItem(300 + i * 20, 300, GEM);
                }

                if (level.getCurrentLevel() == 10 && gamaAlive && !level.getGama().getZinda())
                {
                    player.addScore(10000);
                    if (multiPl) player2.addScore(10000);
                    for (int i = 0; i < 20; i++)
                        level.spawnItem(200 + i * 20, 300, GEM);
                }

                //real time leaderboard update
                leaderboard.updateScore(auth.getUser(), player.getScore());

                if (level.isComplete())
                {
                    if (level.getCurrentLevel() >= 10)
                    {
                        //game complete
                        level.getCurrentLevel(),
                            player.getScore(),
                            player.getGem(),
                            player.getLive();
                        leaderboard.updateScore(auth.getUser(), player.getScore());
                        gameState = 8; //end screen
                    }
                    else
                        level.nextLevel();
                }

                h.update(player.getScore(), player.getLive(), level.getLevel(), player.getGem(),
                    player2.getScore(), player2.getLive(), player2.getGem(), multiPl);

                level.draw(window);
                h.draw(window);
                window.draw(player);
                if (multiPl) window.draw(player2);

                // game over check
                bool p1Dead = player.getDead();
                bool p2Dead = !multiPl || player2.getDead();
                if (p1Dead && p2Dead)
                {
                    //save progress and go to main menu

                    level.getCurrentLevel(),
                        player.getScore(),
                        player.getGem(),
                        player.getLive();
                    gameState = 3;
                }

            }
           else // PAUSED - draw game then overlay
           {
               level.draw(window);
               h.draw(window);
               window.draw(player);
               if (multiPl) window.draw(player2);

               sf::RectangleShape overlay(sf::Vector2f(400, 350));
               overlay.setPosition(200, 125);
               overlay.setFillColor(sf::Color(0, 0, 0, 210));
               overlay.setOutlineColor(sf::Color::Cyan);
               overlay.setOutlineThickness(2);
               window.draw(overlay);

               sf::Font pFont;
               pFont.loadFromFile("assets/FONT/BubbleBobble-rg3rx.ttf");

               sf::Text pt("PAUSED", pFont, 45);
               pt.setFillColor(sf::Color::Cyan);
               pt.setPosition(310, 140);
               window.draw(pt);

               std::string opts[4] = {
                   "ESC - Continue",
                   "S   - Shop",
                   "M   - Main Menu",
                   "X   - Exit"
               };
               sf::Color cols[4] = {
                   sf::Color::Green,
                   sf::Color::Yellow,
                   sf::Color::White,
                   sf::Color::Red
               };
               for (int i = 0; i < 4; i++)
               {
                   sf::Text opt(opts[i], pFont, 28);
                   opt.setFillColor(cols[i]);
                   opt.setPosition(250, 230 + i * 55);
                   window.draw(opt);
               }

               
        }
    }
         else if (gameState == 6) // leaderboard
         {
             int result = leaderboard.update(event);
             if (result == 1) gameState = 3;
             leaderboard.draw(window);
    }
         else if (gameState == 7) // shop
         {
           
                 shop.update(event, player, &player2, multiPl);

             shop.draw(window);
    }

		
		else if (gameState == 8) //end screen
        {
            window.clear(sf::Color(10, 10, 40));

            sf::Font font;
            font.loadFromFile("assets/FONT/BubbleBobble-rg3rx.ttf");

            sf::Text congrats("GAME COMPLETE!", font, 50);
            congrats.setFillColor(sf::Color::Cyan);
            congrats.setPosition(160, 150);
            window.draw(congrats);

            sf::Text scoreText("Final Score: " + std::to_string(player.getScore()), font, 35);
            scoreText.setFillColor(sf::Color::Yellow);
            scoreText.setPosition(220, 250);
            window.draw(scoreText);

            sf::Text gemsText("Gems Collected: " + std::to_string(player.getGem()), font, 30);
            gemsText.setFillColor(sf::Color::Green);
            gemsText.setPosition(240, 310);
            window.draw(gemsText);

            sf::Text menuText("Press ENTER for Main Menu", font, 28);
            menuText.setFillColor(sf::Color::White);
            menuText.setPosition(200, 420);
            window.draw(menuText);

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Enter)
            {
                player = Player();
                player.setPos(500, 400);
                gameState = 3;
            }
        }

        window.display();
    }
}