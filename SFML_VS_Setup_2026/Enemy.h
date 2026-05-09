#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"


class Enemy {

protected:
	sf::Vector2f position;
	float speedE;
	float healthE;
	bool zindaE;
	float directionE;
	bool chainKilled = false;

	
	sf::CircleShape snowcover;
	sf::Texture enemyTexture;
    sf::Sprite enemy;
	
	/*Freezing by ball*/
	int state = 0;
	int meltTime = 0;
	float roll = 1.0f;
	/*hitting and collision code*/

	bool cover = false; //enemy snow ma band naahi ha


public:
	Enemy() = default;

	Enemy(const Enemy& other) {
		position = other.position;
		speedE = other.speedE;
		healthE = other.healthE;
		zindaE = other.zindaE;
		directionE = other.directionE;
		snowcover = other.snowcover;
		enemyTexture = other.enemyTexture;
		enemy = other.enemy;
		enemy.setTexture(enemyTexture);
		state = other.state;
		meltTime = other.meltTime;
		roll = other.roll;
		cover = other.cover;
	}

	Enemy& operator=(const Enemy& other) {
		if (this != &other) {
			position = other.position;
			speedE = other.speedE;
			healthE = other.healthE;
			zindaE = other.zindaE;
			directionE = other.directionE;
		//	snowcover = other.snowcover;
			enemyTexture = other.enemyTexture;
			enemy = other.enemy;
			enemy.setTexture(enemyTexture);
			state = other.state;
			meltTime = other.meltTime;
			roll = other.roll;
			cover = other.cover;
		}
		return *this;
	}
	
	bool isChainKilled() const { return chainKilled; }
	void setChainKilled(bool c) { chainKilled = c; }
	//this is abstract class matlub ke is class ke object nahi ban sakta, iske sirf derived class ke object ban sakta hai
	virtual void update(Platform platforms[], int count) = 0;
	
	/*SNOWBALL FREEZING FUNCTIONS*/
	//state 
	// 0 ka meaning ha normal,
	// 1 ka meaning ha half encased, 
	// 2 ka meaning ha fully encased, 
	// 3 ka meaning ha rolling, 
	// 4 ka meaning ha melting
   virtual void hitByBall()
	{
		if (state == 0 || state == 1)
		{
			healthE--;
			if (healthE <= 0)
			{
				state = 2;
			}// fully covered snow ma
			else
				state = 1; // half covered snow ma
		}
	}

	void kick(float kik)
	{
		if (state == 2) 
		{ 
			state = 3; 
			roll = kik; //kik direction de ga ka kis direction ma roll hona ha
		}
	}

	int getState() const 
	{ 
		return state; 
	}
	void setVariantTexture(std::string path)
	{
		enemyTexture.loadFromFile(path);
		enemy.setTexture(enemyTexture);
		enemy.setScale(
			60.0f / enemyTexture.getSize().x,
			64.0f / enemyTexture.getSize().y
		);
	}
	//PLatform
	virtual void update(Platform platforms[], int count, sf::Vector2f playerPos)
	{
		
		update(platforms, count);
	}
	
	virtual void draw(sf::RenderWindow& window) = 0;

	void setPosition(float x, float y) {
		enemy.setPosition(x, y);
	}
	void setSpeed(float speed) {
		speedE = speed;
	}
	void setHealth(float health) {
		healthE = health;
	}
	void setdirection(float direction) {
		directionE = direction;
	}
	void setZinda(bool zinda) {  
		zindaE = zinda;
	}
	
	bool getZinda() const {    //return ka zinda ha ya mar gaya
		return zindaE;
	}

	bool getCover() const {      //return ka cover ha ya nahi
		return cover;
	}

	void damage(float howmuch) {
		
		healthE =healthE - howmuch;
		
		if (healthE <= 0) 
		{
			zindaE = false;
		}
	}
	
	
	sf::FloatRect getBounds() const {
		return enemy.getGlobalBounds();
	}
	sf::Vector2f getPosition() const {
		return enemy.getPosition();
	}	

};


