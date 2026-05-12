#pragma once
#include "Enemy.h"
#include "Platform.h"

class Botom : public Enemy
{	
protected:

	sf::Texture halfTexture;
	sf::Sprite  halfSprite;
	sf::Texture fullTexture;
	sf::Sprite  fullSprite;
	   float jumpE;    // jump strength
	   bool groundE;     // fall speed
	   int animFrame = 0;
	   int animTimer = 0;

   public:
	   Botom() : Botom(0, 0) {}
	   Botom(float x, float y);
       Botom(const Botom& other) : Enemy(other)
       {
           jumpE = other.jumpE;
           groundE = other.groundE;
           animFrame = other.animFrame;
           animTimer = other.animTimer;
           // reload textures fresh — SFML textures can't be safely copied
           halfTexture.loadFromFile("assets/half.png");
           halfSprite.setTexture(halfTexture);
           fullTexture.loadFromFile("assets/snowballs.png");
           fullSprite.setTexture(fullTexture);
           // repoint sprite to our local texture
           halfSprite.setScale(other.halfSprite.getScale());
           fullSprite.setScale(other.fullSprite.getScale());
       }

       Botom& operator=(const Botom& other)
       {
           if (this != &other)
           {
               Enemy::operator=(other);
               jumpE = other.jumpE;
               groundE = other.groundE;
               animFrame = other.animFrame;
               animTimer = other.animTimer;
               halfTexture.loadFromFile("assets/half.png");
               halfSprite.setTexture(halfTexture);
               fullTexture.loadFromFile("assets/snowballs.png");
               fullSprite.setTexture(fullTexture);
           }
           return *this;
       }
	   void update(Platform platforms[],int count) override;
	   void draw(sf::RenderWindow& window) override;
};
