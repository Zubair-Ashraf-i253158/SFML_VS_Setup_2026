#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

class SnowBall
{
private:
private:
	static sf::Texture ballTexture; // static = loaded once, shared by all snowballs
	sf::Sprite ball;
	bool active;
	float directionX;
	float directionY;
	float speed;
public:
	SnowBall();
	void setfire(float x, float y);
	void shoot(float dirX); // shoot the snowball in a direction
	void update(); // update the snowball position
	
	void setact(bool active);             // setter
	bool act() const;                   //getter
	
 void draw(sf::RenderTarget& target) const; // draw the snowball
	sf::FloatRect getBounds() const; // get the bounding box of the snowball
};
