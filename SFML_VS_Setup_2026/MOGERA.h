#pragma once


#include "Enemy.h"	
#include "Platform.h"
#include "MogeraBabies.h"

//khud asan tornado bana kr zubair bhai ne boss merey mathey mardia 
//rona nahi -Call karu bacha :D

class Mogera : public Enemy
{
protected:

	//AS the mogera and mogera child have composition relationship, mogera class ke andar hi mogera child ka object ha
	Mchild babies[50]; //mogera ke 50 babies hongee;
	int babyCount; //mogera ke kitne babies zinda hain
	
	sf::RectangleShape Hbar; //health bar
	sf::RectangleShape HbarBack; //health bar background 

	float Health; //mogera ki health
	float timeB; //time jis ke bad baby phainkni hai

public:
	Mogera() : Mogera(0, 0) {}
	Mogera(float x, float y);
	
	// base class ka update override karo - ZARURI HAI
	void update(Platform platforms[], int count) override
	{
		// khali rehne do ya playerPos ke bagair call karo
	}
	
	int getBabyCount() const { return babyCount; }
	Mchild& getBaby(int i) { return babies[i]; }
	virtual void hitByBall() override
	{
		Health -= 1.0f;
		healthE = Health; 
		if (Health <= 0)
			zindaE = false;
	}
	void update(Platform platforms[], int count, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window) override;
	float getHealth() const;

};
