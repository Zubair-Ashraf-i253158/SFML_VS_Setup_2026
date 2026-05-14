#include "Enemy.h"
#include "GamaKichi.h"
sf::Texture Gama::rocketTexture;

Gama::Gama(float x, float y)
{

    enemyTexture.loadFromFile("assets/gamakichi.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(
       90.0f / enemyTexture.getSize().x,  // auto fit to 90px wide
        94.0f / enemyTexture.getSize().y   // auto fit to 94px tall
    );
    enemy.setPosition(x, y);                   
    MaxH = 20.0f;    // maximum health 20
    healthE = 20.0f;    // shuru mein full health
    zindaE = true;     

    // Gama halta nahi hai isliye direction 0
    directionE = 0.0f;

    // Timer aur phase setup
    rocketTime = 0.0f; // rocket fire karne ka timer
    attackP = 0;       // shuru mein phase 1

	//only load once ya static texture ke liye
    if (rocketTexture.getSize().x == 0)
        rocketTexture.loadFromFile("assets/rocket.png");

    for (int i = 0; i < 5; i++)
    {
        rocketactive[i] = false;
        if (rocketTexture.getSize().x > 0)
        {
            rocket[i].setTexture(rocketTexture);
            float sx = 30.0f / rocketTexture.getSize().x;
            float sy = 30.0f / rocketTexture.getSize().y;
            rocket[i].setScale(sx, sy);
        }
    }
    // Front Health Bar
    
    Ghealthbar.setSize(sf::Vector2f(200, 50));     
    Ghealthbar.setPosition(300, 50);                // screen ke top centre mein
    Ghealthbar.setFillColor(sf::Color(200, 200, 200)); // grey colour

    
    GhealthBack.setSize(sf::Vector2f(200, 50));    // same size
    GhealthBack.setFillColor(sf::Color::Black);    // kala background
    GhealthBack.setPosition(300, 50);              // same position

}

void Gama::update(Platform platforms[], int count)
{
    // ager gama mar gaya to kuch mat karo
    if (!zindaE) return;

   
    // Attack Phase Check
    // health ke hisaab se phase badalta hai
   
    if (healthE > 666)      
       attackP = 0; // phase 1 slow fire
    
    else if (healthE > 333) 
        attackP = 1; // phase 2 medium fire
    
    else                   
        attackP = 2; // phase 3 fast fire

    
    rocketTime++;

    
    //Phase Ke Hisaab Se Fire Karo
   
    if ((attackP == 0 && rocketTime > 120) ||
        (attackP == 1 && rocketTime > 80) ||
        (attackP == 2 && rocketTime > 40))
    {
        // har rocket ko activate karo
        for (int i = 0; i < 5; i++)
        {
            // sirf tab set karo jab rocket inactive ho
            // warna rocket reset ho jata hai beech mein
            if (!rocketactive[i])
            {
                RocketPosition(i);      // rocket ki starting position set karo
                rocketactive[i] = true; // rocket ko active karo
            }
        }

       
        // har rocket ko alag direction do
        speedX[0] = 0;   speedY[0] = -5; // rocket 0 upar jaye ga
        speedX[1] = 0;   speedY[1] = 5;  // rocket 1 neeche jaye ga
        speedX[2] = -5;  speedY[2] = 0;  // rocket 2 left jaye ga
        speedX[3] = 5;   speedY[3] = 0;  // rocket 3 right jaye ga
        speedX[4] = 4;   speedY[4] = -4; // rocket 4 diagonal jaye ga

        // timer reset karo agla fire ke liye
        rocketTime = 0;
    }

    for (int i = 0; i < 5; i++)
    {
        if (rocketactive[i]) // sirf active rockets move karo
        {
            // rocket ko uski speed se move karo
            rocket[i].move(speedX[i], speedY[i]);

            // ager rocket screen se bahar chala gaya to deactivate karo
            if (rocket[i].getPosition().x < 0 ||    
                rocket[i].getPosition().x > 800 || 
                rocket[i].getPosition().y < 0 ||    
                rocket[i].getPosition().y > 600)    
                rocketactive[i] = false;
        }
    }

    float percent = healthE / MaxH;                         
    Ghealthbar.setSize(sf::Vector2f(200.0f * percent, 20)); // bar choti karo
}

void Gama::draw(sf::RenderWindow& window)
{
   if (!zindaE)
       return; 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            window.draw(enemy); //NORMAL enemy sprite ko pehle 
            window.draw(GhealthBack); // health bar background 
            window.draw(Ghealthbar); // health bar 

            
            sf::RectangleShape box;

            //enemy sprite ke height aur width ke hisab se box ka size set karo
            box.setSize(sf::Vector2f( enemy.getGlobalBounds().width  ,  enemy.getGlobalBounds().height));

            box.setPosition(enemy.getPosition()); //enemy sprite ke position par box set karo
            box.setFillColor(sf::Color::Transparent); //box transparent
            box.setOutlineColor(sf::Color::Red); //red color 
            box.setOutlineThickness(5); //box outline thickness

            window.draw(box); 


            //ROCKETS
            for (int i = 0; i < 5; i++) 
            {
                if (rocketactive[i]) //rocket active
                {
                    window.draw(rocket[i]); //rocket sprite

                    //rocket hitbox
                    sf::RectangleShape rBox;

                   
                    rBox.setSize(sf::Vector2f( rocket[i].getGlobalBounds().width , rocket[i].getGlobalBounds().height));

                    rBox.setPosition(rocket[i].getPosition()); 
                    rBox.setFillColor(sf::Color::Transparent);
                    rBox.setOutlineColor(sf::Color::Yellow); // yellow 
                    rBox.setOutlineThickness(5);

                    window.draw(rBox); //rocket hitbox draw karo
                }
            }
        }
        else
        {
            window.draw(enemy); //NORMAL enemy draw karo
            window.draw(GhealthBack); 
            window.draw(Ghealthbar); 

            // rockets draw karo
            for (int i = 0; i < 5; i++)
            {
                if (rocketactive[i])
                    window.draw(rocket[i]); // rocket sprite draw karo
            }
        }
}