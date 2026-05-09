#include "LevelSystem.h"
#include "Platform.h"
#include "Player.h"
#include "Botom.h"
#include "FlyingFooga.h"
#include "Tornado.h"
#include "MOGERA.h"
#include "MogeraBabies.h"
#include "GamaKichi.h"
#include "Collision.h"
#include "InvisibleEnemy.h"
#include"item.h"
#include <SFML/Graphics.hpp>

Level::Level() : m(0.0, 0.0), g(0.0, 0.0)  // boss default position
{
    gemTexture.loadFromFile("assets/gem.png");
    starTexture.loadFromFile("assets/star.png");
    currentLevel = 1;
    bCount = 0;
    fCount = 0;
    tCount = 0;

    platformCount = 0;
    loadLevel(1); // level 1 se shuru karo
}


// now ab her level ko uski properties ke saath load karna hai, jaise background, platforms, enemies

void Level::loadLevel(int levelNum)
{
    currentLevel = levelNum;
    bCount = 0;
    fCount = 0;
    tCount = 0;
    invCount = 0;
    platformCount = 0;

    //LEVEL 1 
    //Sirf Botom enemies
    if (levelNum == 4 || levelNum == 9) {
        bgTexture.loadFromFile("assets/lvl bonus.png");
        background.setTexture(bgTexture);
        background.setScale(
            800.0f / bgTexture.getSize().x,
            600.0f / bgTexture.getSize().y
        );
        platformCount = 10; platforms[0] = Platform(0, 567, 800, 10);   // ground
        platforms[1] = Platform(207, 480, 420, 10);   // bottom long left
        platforms[2] = Platform(307, 400, 300, 10); // mid right 
        platforms[3] = Platform(207, 310, 300, 10); // mid long
        platforms[4] = Platform(307, 230, 300, 10); // upper right
        platforms[5] = Platform(107, 230, 90, 70);   // upper left small
        platforms[6] = Platform(159, 140, 338, 10); // top long
        platforms[7] = Platform(107, 397, 90, 70);   // bottom left small
        platforms[8] = Platform(607, 310, 90, 70);   // bottom right small
        platforms[9] = Platform(607, 140, 90, 70);   // upper right small
        //only bonus
        //spread across all platforms 
        for (int p = 0; p < platformCount; p++)
        {
            sf::FloatRect pl = platforms[p].getBounds();
            int gemsOnPlatform = 5; //har platform par 5 gems
            for (int g = 0; g < gemsOnPlatform; g++)
            {
                float gemX = pl.left + (pl.width / gemsOnPlatform) * g + 10;
                float gemY = pl.top - 30; //platform ke upar
                spawnItem(gemX, gemY, GEM);
            }
        }
    }
    else
    {
        if (levelNum == 1)
        {
            //background load karo
            bgTexture.loadFromFile("assets/lvl1.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );

            //platforms set karo
            platformCount = 10;
            platforms[0] = Platform(0, 524, 800, 10);    //ground floor
            platforms[1] = Platform(0, 450, 190, 10);    //bottom left
            platforms[2] = Platform(320, 450, 180, 10);  //bottom middle
            platforms[3] = Platform(620, 450, 180, 10);  //bottom right
            platforms[4] = Platform(160, 370, 485, 12);  //middle row
            platforms[5] = Platform(0, 290, 340, 10);    //upper left
            platforms[6] = Platform(200, 160, 390, 8);   //upper middle
            platforms[7] = Platform(460, 290, 340, 10);  //upper right
            platforms[8] = Platform(100, 200, 125, 10);  //top left
            platforms[9] = Platform(570, 200, 125, 10);  //top right

            //enemies set karo
            bCount = 5;

            b[0] = Botom(50, 450);
            b[1] = Botom(50, 400);
            b[2] = Botom(700, 400);
            b[3] = Botom(500, 300);
            b[4] = Botom(600, 50);

            b[1].setdirection(-1.0f); //left
            b[2].setdirection(-1.0f); //left

        }


        //LEVEL 2 
        //Botom and FlyingFooga

        else if (levelNum == 2)
        {
            bgTexture.loadFromFile("assets/lvl2.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );

            platformCount = 9;


            platforms[0] = Platform(0, 569, 800, 10);
            platforms[1] = Platform(100, 483, 247, 10);    //bottom left
            platforms[2] = Platform(460, 483, 243, 10);  //bottom right
            platforms[3] = Platform(0, 397, 347, 10);    //mid left
            platforms[4] = Platform(455, 399, 350, 10);  //mid right
            platforms[5] = Platform(150, 310, 47, 10);    //upper left
            platforms[6] = Platform(354, 310, 307, 10);  //upper long
            platforms[7] = Platform(106, 223, 436, 10);   //top left
            platforms[8] = Platform(255, 137, 437, 10); //top right
            //enemies

            bCount = 3;             //BOTOM
            b[0] = Botom(100, 50);
            b[1] = Botom(400, 50);
            b[2] = Botom(600, 50);
            b[1].setdirection(-1.0f);

            fCount = 2;             //FLY FOOGA
            f[0] = FlyingFooga(200, 50);
            f[1] = FlyingFooga(500, 50);
            f[1].setdirection(-1.0f);
        }


        //LEVEL 3
        //Botom , FlyingFooga and Tornado

        else if (levelNum == 3)
        {
            bgTexture.loadFromFile("assets/level 3.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );



            platformCount = 11;

            //ground
            platforms[0] = Platform(0, 567, 800, 10);
            platforms[1] = Platform(210, 490, 387, 10);
            platforms[2] = Platform(0, 400, 110, 10);
            platforms[3] = Platform(0, 310, 110, 10);
            platforms[4] = Platform(700, 400, 130, 10);
            platforms[5] = Platform(700, 310, 130, 10);
            platforms[6] = Platform(215, 310, 140, 10);
            platforms[7] = Platform(455, 310, 140, 10);
            platforms[8] = Platform(0, 225, 205, 10);
            platforms[9] = Platform(600, 225, 210, 10);
            platforms[10] = Platform(167, 140, 470, 10);

            bCount = 2;
            b[0] = Botom(100, 50);
            b[1] = Botom(400, 50);
            b[1].setdirection(-1.0f);

            fCount = 2;
            f[0] = FlyingFooga(200, 50);
            f[1] = FlyingFooga(500, 50);

            tCount = 2;
            t[0] = Tornado(300, 50);
            t[1] = Tornado(600, 50);
            t[1].setdirection(-1.0f);
        }


        //LEVEL 4
        //Special enemy




        //LEVEL 5
        //Boss Mogera

        else if (levelNum == 5)
        {
            bgTexture.loadFromFile("assets/lvl5boss.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );
            platformCount = 6; //boss

            //Ground
            platforms[0] = Platform(0, 567, 800, 40);
            platforms[1] = Platform(215, 470, 220, 15);//lowest
            platforms[2] = Platform(0, 397, 335, 15);   //left
            platforms[3] = Platform(560, 354, 240, 15); //right
            platforms[4] = Platform(166, 307, 270, 15); //center
            platforms[5] = Platform(0, 211, 330, 15);   //top
            // sirf mogera hai

            m = Mogera(360, 150);

        }


        // LEVEL 6 
        // Green Color Variants


        else if (levelNum == 6)
        {

            bgTexture.loadFromFile("assets/lvl5.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );

            platformCount = 11;
            platforms[0] = Platform(0, 579, 800, 10);//ground
            platforms[1] = Platform(117, 494, 230, 10);//first two platforms
            platforms[2] = Platform(465, 494, 230, 10);
            platforms[3] = Platform(0, 405, 200, 10);//small left
            platforms[4] = Platform(620, 405, 200, 10);//small right
            platforms[5] = Platform(117, 320, 200, 10);//mid two platforms 
            platforms[6] = Platform(492, 320, 200, 10);
            platforms[7] = Platform(0, 230, 200, 10);//top right
            platforms[8] = Platform(610, 230, 200, 10);//top left 
            platforms[9] = Platform(110, 140, 580, 10);//top
            platforms[10] = Platform(350, 150, 100, 355);//top sa nichay vertical
            //faster speed

            bCount = 2;
            b[0] = Botom(200, 50);
            b[1] = Botom(300, 50);
            b[2] = Botom(400, 50);
            b[3] = Botom(500, 50);
            b[4] = Botom(600, 50);
            b[1].setdirection(-1.0f);

            for (int i = 0; i < bCount; i++)
            {
                b[i].setSpeed(3.0f * 1.25f);  //1.25x faster
                b[i].setHealth(3.0f);          //+1 hit to encase
                // b[i].setColor(sf::Color::Green); //green colour
            }

            //CUSTOMIZED ENEMy 
            invCount = 2;
            inV[0] = Invisible(150, 50);
            inV[1] = Invisible(350, 50); 
            //new variants
            for (int i = 0; i < bCount; i++)
                b[i].setVariantTexture("assets/enemy 5.png");
       
        }


        //LEVEL 7
        //Blue Color Variants

        else if (levelNum == 7)
        {
            //background load karo
            bgTexture.loadFromFile("assets/lvl 7.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );
            platformCount = 15;

            platforms[0] = Platform(0, 571, 800, 15); // ground
            platforms[1] = Platform(0, 440, 145, 22);    //bottom small  left
            platforms[2] = Platform(655, 440, 145, 15);  //bottom small right
            platforms[3] = Platform(145, 480, 165, 22);  //bottom left 
            platforms[4] = Platform(490, 480, 165, 15);  //bottom right
            platforms[5] = Platform(110, 310, 80, 22);  //mid left 
            platforms[6] = Platform(160, 350, 145, 22);  //mid left
            platforms[7] = Platform(510, 310, 130, 22);  //mid right
            platforms[8] = Platform(640, 350, 160, 12);  //mid right
            platforms[9] = Platform(160, 225, 180, 12);  //top low
            platforms[10] = Platform(375, 184, 150, 12); //top middle
            platforms[11] = Platform(505, 145, 180, 12); //top
            platforms[12] = Platform(0, 145, 240, 12);   //top left small
            platforms[13] = Platform(620, 225, 180, 12); //top right high
            platforms[14] = Platform(315, 390, 170, 72);   //clock

            bCount = 5;
            b[0] = Botom(100, 50);
            b[1] = Botom(300, 50);
            b[1].setdirection(-1.0f);

            for (int i = 0; i < bCount; i++)
            {
                b[i].setSpeed(3.0f * 1.5f);   //1.5x faster
                b[i].setHealth(4.0f);          //+2 hits
                // b[i].setColor(sf::Color::Blue);
            }

            fCount = 2;
            f[0] = FlyingFooga(200, 50);
            f[1] = FlyingFooga(600, 50);
            for (int i = 0; i < fCount; i++)
            {
                f[i].setSpeed(2.0f * 1.5f);
                f[i].setHealth(4.0f);
                // f[i].setColor(sf::Color::Blue);
            }

            tCount = 2;
            t[0] = Tornado(300, 50);
            t[1] = Tornado(500, 50);
            for (int i = 0; i < tCount; i++)
            {
                t[i].setSpeed(2.0f * 1.5f);
                t[i].setHealth(5.0f);
                //  t[i].setColor(sf::Color::Blue);
            }


            //new variants
            for (int i = 0; i < bCount; i++)
                b[i].setVariantTexture("assets/enemy 5.png");
            for (int i = 0; i < fCount; i++)
                f[i].setVariantTexture("assets/ff 6.png");
            for (int i = 0; i < tCount; i++)
                t[i].setVariantTexture("assets/tor 6.png");
        }


        //LEVEL 8
        //Purple Color Variants

        else if (levelNum == 8)
        {
            bgTexture.loadFromFile("assets/lvl 6.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );

            platformCount = 11;

            //ground
            platforms[0] = Platform(0, 567, 800, 10);
            platforms[1] = Platform(210, 490, 387, 10);
            platforms[2] = Platform(0, 400, 110, 10);
            platforms[3] = Platform(0, 310, 110, 10);
            platforms[4] = Platform(700, 400, 130, 10);
            platforms[5] = Platform(700, 310, 130, 10);
            platforms[6] = Platform(215, 310, 140, 10);
            platforms[7] = Platform(455, 310, 140, 10);
            platforms[8] = Platform(0, 225, 205, 10);
            platforms[9] = Platform(600, 225, 210, 10);
            platforms[10] = Platform(167, 140, 470, 10);


            bCount = 5;
            b[0] = Botom(100, 50);
            b[1] = Botom(250, 50);
            b[2] = Botom(400, 50);
            b[3] = Botom(600, 50);
            b[4] = Botom(700, 50);
            b[1].setdirection(-1.0f);

            for (int i = 0; i < bCount; i++)
            {
                b[i].setSpeed(3.0f * 1.75f);      //1.75x faster
                b[i].setHealth(5.0f);              //+3 hits
                // b[i].setColor(sf::Color(128, 0, 128)); //purple
            }

            fCount = 2;
            f[0] = FlyingFooga(200, 50);
            f[1] = FlyingFooga(600, 50);
            for (int i = 0; i < fCount; i++)
            {
                f[i].setSpeed(2.0f * 1.75f);
                f[i].setHealth(5.0f);
                // f[i].setColor(sf::Color(128, 0, 128));
            }

            tCount = 2;
            t[0] = Tornado(300, 50);
            t[1] = Tornado(500, 50);
            for (int i = 0; i < tCount; i++)
            {
                t[i].setSpeed(2.0f * 1.75f);
                t[i].setHealth(6.0f);
                // t[i].setColor(sf::Color(128, 0, 128));
            }
            //new extreme variants
            for (int i = 0; i < bCount; i++)
                b[i].setVariantTexture("assets/enemy 8.png");
            for (int i = 0; i < fCount; i++)
                f[i].setVariantTexture("assets/ff 8.png");
            for (int i = 0; i < tCount; i++)
                t[i].setVariantTexture("assets/tor 8.png");
        }


        //LEVEL 9 
        //All Variants Mixed



        //LEVEL 10 
        //Boss Gamakichi

        else if (levelNum == 10)
        {
            bgTexture.loadFromFile("assets/lvlten.png");
            background.setTexture(bgTexture);
            background.setScale(
                800.0f / bgTexture.getSize().x,
                600.0f / bgTexture.getSize().y
            );
            platformCount = 11;

            platforms[0] = Platform(0, 567, 800, 10);
            platforms[1] = Platform(210, 490, 387, 10);
            platforms[2] = Platform(0, 400, 110, 10);
            platforms[3] = Platform(0, 310, 110, 10);
            platforms[4] = Platform(700, 400, 130, 10);
            platforms[5] = Platform(700, 310, 130, 10);
            platforms[6] = Platform(215, 310, 140, 10);
            platforms[7] = Platform(455, 310, 140, 10);
            platforms[8] = Platform(0, 225, 205, 10);
            platforms[9] = Platform(600, 225, 210, 10);
            platforms[10] = Platform(167, 140, 470, 10);

            g = Gama(350, 150);

        }
    }
}
// UPDATE 
//enemies update karo

void Level::update(Player& player)
{
    // botom update karo
    for (int i = 0; i < bCount; i++)
        b[i].update(platforms, platformCount);

    // flyingfooga update karo
    for (int i = 0; i < fCount; i++)
        f[i].update(platforms, platformCount);

    // tornado update karo
    for (int i = 0; i < tCount; i++)
        t[i].update(platforms, platformCount, player.getPosition());

    //invisible update karo
    for (int i = 0; i < invCount; i++)
        inV[i].update(platforms, platformCount, player.getPosition());

    // sirf level 5 par mogera update karo
    if (currentLevel == 5)
        m.update(platforms, platformCount, player.getPosition());

    // sirf level 10 par gama update karo
    if (currentLevel == 10)
        g.update(platforms, platformCount);
}


// DRAW
// sab draw karo

void Level::draw(sf::RenderWindow& window)
{
    // background draw karo
    window.draw(background);

    // platforms draw karo
    for (int i = 0; i < platformCount; i++)
        platforms[i].draw(window);

    // botom draw karo
    for (int i = 0; i < bCount; i++)
        b[i].draw(window);

    // flyingfooga draw karo
    for (int i = 0; i < fCount; i++)
        f[i].draw(window);

    // tornado draw karo
    for (int i = 0; i < tCount; i++)
        t[i].draw(window);

    // invisible draw karo
    for (int i = 0; i < invCount; i++)
        inV[i].draw(window);
    //Draw items on ALL levels
    for (int i = 0; i < maxItems; i++) {
        if (items[i].active) {
            window.draw(items[i].sprite);
        }
    }
    // sirf level 5 par mogera draw karo
    if (currentLevel == 5)
        m.draw(window);

    // sirf level 10 par gama draw karo
    if (currentLevel == 10)
        g.draw(window);
}



// sare enemies mare mar gae to level complete, check karo

bool Level::isComplete()
{
    if (currentLevel == 4 || currentLevel == 9) {
        //saray uha lai
        for (int i = 0; i < maxItems; i++) {
            if (items[i].active) {
                return false;
            }
        }
        return true;
    }
    // botom check karo
    for (int i = 0; i < bCount; i++)
        if (b[i].getZinda())
            return false;

    // flyingfooga check karo
    for (int i = 0; i < fCount; i++)
        if (f[i].getZinda())
            return false;

    // tornado check karo
    for (int i = 0; i < tCount; i++)
        if (t[i].getZinda())
            return false;

    // invisible enemies check karo
    for (int i = 0; i < invCount; i++)
        if (inV[i].getZinda())
            return false;

    // sirf level 5 par mogera check karo
    if (currentLevel == 5 && m.getZinda())
        return false;

    // sirf level 10 par gama check karo
    if (currentLevel == 10 && g.getZinda())
        return false;


    return true; // sab mar gaye level complete
}


// NEXT LEVEL 
// agla level load karo
void Level::nextLevel()
{
    currentLevel++;

    if (currentLevel > 10)
    {
        currentLevel = 10;
        return; // yahan ruk jao
    }
    loadLevel(currentLevel);
}