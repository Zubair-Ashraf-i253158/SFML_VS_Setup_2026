#include "SnowBall.h"
sf::Texture SnowBall::ballTexture; // static member definition
SnowBall::SnowBall()
{
	speed = 4.0f;
	// only load if not already loaded
	if (ballTexture.getSize().x == 0)
	{
		ballTexture.loadFromFile("assets/snowballs.png");
	}
	ball.setTexture(ballTexture);
	if (ballTexture.getSize().x > 0)
	{
		float sx = 28.0f / ballTexture.getSize().x;
		float sy = 28.0f / ballTexture.getSize().y;
		ball.setScale(sx, sy);
		ball.setOrigin(ballTexture.getSize().x / 2.f, ballTexture.getSize().y / 2.f);
	}
}

void SnowBall::setact(bool active)
{
	this->active = active;
}

void SnowBall::setfire(float x, float y)
{
	ball.setPosition(x, y); // snowball ki starting position set karo
}

void SnowBall::shoot(float dirX)
{
	directionX = dirX;  //if -1 go left if 1 go right
	active = true;
}

bool SnowBall::act() const      //getter
{
	return active; // batao ki snowball active hai ya nahi
}
int x = 1;

void SnowBall::update()
{
	
	if (active)
	{
		ball.move(directionX * speed, 0);

		if (directionX > 0 && ball.getPosition().x > 800) // right boundary check
			active = false;
		else if (directionX < 0 && ball.getPosition().x < 0) // left boundary check
			active = false;
	}
}

void SnowBall::draw(sf::RenderTarget& target) const
{
	
	if (active)
		target.draw(ball);
}

sf::FloatRect SnowBall::getBounds() const
{
	return ball.getGlobalBounds();
}