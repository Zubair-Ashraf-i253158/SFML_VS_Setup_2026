#pragma once
#include "Enemy.h"

class Gama : public Enemy
{
private:
	static sf::Texture rocketTexture;
	sf::Sprite  rocket[5];
	//sf::RectangleShape rocket[5]; //gamay ke 5 rockets hongee
	bool rocketactive[5]; //gamay ke 5 rockets active hongee ya nahi	

	float rocketx[5];
	float rockety[5];

	float speedX[5];     
	float speedY[5];

	float rocketTime; //time jis ke bad rocket nikle ga

	sf::RectangleShape Ghealthbar; //gamay ki health bar
	sf::RectangleShape GhealthBack; //gamay ki health bar background

	float MaxH; //gamay ki max health

	int attackP; //gamay ke attack phase

	/* Setting ROCKETS Position */
	void RocketPosition(int index)
	{
		switch (index)
		{
			//TOP OF GAMA
		case 0:
			rocketx[index] = enemy.getPosition().x + 50; //rocket center se nikle ga
			rockety[index] = enemy.getPosition().y - 10; //rocket thoda upar se nikle ga
			
			rocket[index].setPosition(rocketx[index], rockety[index]);
			break;
			//BOTTOM OF GAMA
		case 1:
			rocketx[index] = enemy.getPosition().x + 50;
			rockety[index] = enemy.getPosition().y + 110; //rocket thoda neeche se nikle ga
			rocket[index].setPosition(rocketx[index], rockety[index]);
			break;
			//LEFT OF GAMA
		case 2:
			rocketx[index] = enemy.getPosition().x - 10; //rocket left side se nikle ga
			rockety[index] = enemy.getPosition().y + 50;
			rocket[index].setPosition(rocketx[index], rockety[index]);
			break;
			//RIGHT OF GAMA
		case 3:
			rocketx[index] = enemy.getPosition().x + 110; //rocket right side se nikle ga
			rockety[index] = enemy.getPosition().y + 50;
			rocket[index].setPosition(rocketx[index], rockety[index]);
			break;
			//CENTER OF GAMA
		case 4:
			rocketx[index] = enemy.getPosition().x + 50;
			rockety[index] = enemy.getPosition().y + 50; //rocket center se nikle ga
			rocket[index].setPosition(rocketx[index], rockety[index]);
			break;
		default:
			break;
		}
	}

public:
	Gama() : Gama(0, 0) {}
	Gama(float x, float y);
	void update(Platform platforms[], int count) override;
	sf::FloatRect getRocketBounds(int i) const { return rocket[i].getGlobalBounds(); }
	bool getRocketActive(int i) const { return rocketactive[i]; }
	void setRocketInactive(int i) { rocketactive[i] = false; }

	void hitByBall() override  // no snow encasing for boss
	{
		healthE--;
		if (healthE <= 0)
			zindaE = false;
	}
	void draw(sf::RenderWindow& window) override;


};