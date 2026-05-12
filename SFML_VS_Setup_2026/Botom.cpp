#include "Botom.h"
#include"Collision.h"

Botom::Botom(float x, float y)
{ 
    // texture load karo agar nahi mila to rectangle use karo
    if (!enemyTexture.loadFromFile("assets/enemy.png"))
    {
        // texture nahi mila to phr rectangle use karo
        // sprite transparent
        enemy.setColor(sf::Color::Transparent);
    }
    else
    {
        // texture mil gaya to sprite set karo
        enemy.setTexture(enemyTexture);
        enemy.setScale(
            60.0f / enemyTexture.getSize().x,
            64.0f / enemyTexture.getSize().y
        );
    }
	
    enemy.setPosition(400, 400);
    
    snowcover.setFillColor(sf::Color::White);
	enemy.setPosition(x, y);
    if (!halfTexture.loadFromFile("assets/half.png"))
        std::cerr << "ERROR: half.png not found!\n";
    halfSprite.setTexture(halfTexture);

    if (!fullTexture.loadFromFile("assets/snowballs.png"))
        std::cerr << "ERROR: snowballs.png not found!\n";
    fullSprite.setTexture(fullTexture);
	
    speedE = 2.0f;  
	healthE = 2.0f; //heaalth 
	zindaE = true;
	directionE = 1.0f; // Start moving right
	jumpE = 0;
	groundE = false;            
}

void Botom::update(Platform platforms[], int count)
{
    if (state == 0 ) // normal ya half encased can walk
    {
        enemy.move(speedE * directionE, 0);
        enemy.move(0, jumpE);
        jumpE += 0.3f;
        groundE = false;
        
        for (int i = 0; i < count; i++)
        {
            sf::FloatRect pl = platforms[i].getBounds();
            sf::FloatRect eb = enemy.getGlobalBounds();
           
            bool side = (eb.left < pl.left + pl.width) && (eb.left + eb.width > pl.left);
            bool top = (eb.top + eb.height >= pl.top) && (eb.top + eb.height <= pl.top + 30);
            
            if (side && top) 
            { 
                enemy.setPosition(enemy.getPosition().x, pl.top - eb.height);
                jumpE = 0; 
                groundE = true; 
            }
        }
        if (enemy.getPosition().x < 0) 
        { 
            enemy.setPosition(0, enemy.getPosition().y);
            directionE = 1.0f; 
        }
        else if (enemy.getPosition().x > 770)
        {
            enemy.setPosition(770, enemy.getPosition().y); 
            directionE = -1.0f;
        }
    }
   
    else if (state == 2 || state == 1) // full snow ma cover ha to still rahay 
    {
        enemy.move(0, jumpE);
        jumpE += 0.3f;
       
        for (int i = 0; i < count; i++)
        {
            sf::FloatRect pl = platforms[i].getBounds();
            sf::FloatRect eb = enemy.getGlobalBounds();
           
            bool side = (eb.left < pl.left + pl.width) && (eb.left + eb.width > pl.left);
            bool top = (eb.top + eb.height >= pl.top) && (eb.top + eb.height <= pl.top + 30);
            
            if (side && top) 
            {
                enemy.setPosition(enemy.getPosition().x, pl.top - eb.height);
                jumpE = 0;
            }
        }
        meltTime++;
        if (meltTime > 300)
        { 
            state = 4; 
            meltTime = 0; 
        } //snow melt hona shuru 
    }
    
    else if (state == 3) // rolling ,fast move karay and wall ka sath takrai to mar jai
    {
        enemy.move(roll * 5.0f, 0);
        enemy.move(0, jumpE);
        jumpE += 0.3f;
        
        for (int i = 0; i < count; i++)
        {
            
            sf::FloatRect pl = platforms[i].getBounds();
            sf::FloatRect eb = enemy.getGlobalBounds();
            
            bool side = (eb.left < pl.left + pl.width) && (eb.left + eb.width > pl.left);
            bool top = (eb.top + eb.height >= pl.top) && (eb.top + eb.height <= pl.top + 30);
            
            if (side && top) 
            {
                enemy.setPosition(enemy.getPosition().x, pl.top - eb.height); 
                jumpE = 0; 
            }
        }
        if (enemy.getPosition().x <= 0 || enemy.getPosition().x >= 770)
			zindaE = false; // wall hit karay to mar jai
    }
    else if (state == 4) // melt hona shuru 
    {
        meltTime++;
        if (meltTime > 200) 
        {
            state = 0;
            meltTime = 0; 
            healthE = 2.0f; 
        }
    }
}

void Botom::draw(sf::RenderWindow& window)
{
    if (!zindaE) return;

    sf::FloatRect e = enemy.getGlobalBounds();

    if (state == 0) // normal - just draw enemy
    {
        window.draw(enemy);
    }
    else if (state == 1) // half snow - enemy + half.png on bottom half
    {
        window.draw(enemy);
        // scale half.png to fit enemy width, half height
        halfSprite.setScale(
            e.width / halfTexture.getSize().x,
            (e.height * 0.6f) / halfTexture.getSize().y
        );
        halfSprite.setPosition(e.left, e.top + e.height * 0.4f);
        window.draw(halfSprite);
    }
    else if (state == 2 || state == 3) // fully encased - just snow.png, no enemy visible
    {
        fullSprite.setScale(
            e.width / fullTexture.getSize().x,
            e.height / fullTexture.getSize().y
        );
        fullSprite.setPosition(e.left, e.top);
        window.draw(fullSprite);
    }
    else if (state == 4) // melting - snow shrinks away, enemy reappears
    {
        window.draw(enemy);
        float meltPercent = 1.0f - (meltTime / 200.0f);
        float sw = (e.width / fullTexture.getSize().x) * meltPercent;
        float sh = (e.height / fullTexture.getSize().y) * meltPercent;
        fullSprite.setScale(sw, sh);
        // keep centered while shrinking
        fullSprite.setPosition(
            e.left + (e.width * (1.f - meltPercent)) / 2.f,
            e.top + (e.height * (1.f - meltPercent)) / 2.f
        );
        window.draw(fullSprite);
    }

    // H key hitbox debug overlay
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        sf::RectangleShape box;
        box.setSize(sf::Vector2f(e.width, e.height));
        box.setPosition(e.left, e.top);
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color::Red);
        box.setOutlineThickness(3);
        window.draw(box);
    }
}