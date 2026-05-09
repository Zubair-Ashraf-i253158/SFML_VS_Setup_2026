#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Shop {
private:
    sf::Font font;
    sf::Text title;
    sf::Text gemDisplay;
    sf::Text msg; // feedback message

    sf::RectangleShape itemBoxes[4];
    sf::Text itemNames[4];
    sf::Text itemPrices[4];
    sf::Text itemDesc[4];
    sf::Text backText;

    sf::RectangleShape background;

    std::string names[4] = { "Extra Life",  "Speed Boost", "Jump Boost",  "Snowball Power" };
    std::string descs[4] = { "+1 Life",     "Faster move", "Higher jump", "1-hit encase" };
    int         costs[4] = { 40,            25,            20,            30 };
    int msgTimer = 0;

public:
    Shop()
    {
        font.loadFromFile("assets/FONT/BubbleBobble-rg3rx.ttf");

        background.setSize(sf::Vector2f(800, 600));
        background.setFillColor(sf::Color(10, 10, 40));

        title.setFont(font);
        title.setString("SHOP");
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(340, 20);

        gemDisplay.setFont(font);
        gemDisplay.setCharacterSize(28);
        gemDisplay.setFillColor(sf::Color::Yellow);
        gemDisplay.setPosition(20, 20);

        msg.setFont(font);
        msg.setCharacterSize(24);
        msg.setFillColor(sf::Color::Green);
        msg.setPosition(250, 530);

        backText.setFont(font);
        backText.setString("Press ESC or Q to go back");
        backText.setCharacterSize(22);
        backText.setFillColor(sf::Color::White);
        backText.setPosition(220, 565);

        // 4 item boxes - 2x2 grid
        for (int i = 0; i < 4; i++)
        {
            int col = i % 2;
            int row = i / 2;
            float x = 80 + col * 330;
            float y = 120 + row * 190;

            itemBoxes[i].setSize(sf::Vector2f(290, 160));
            itemBoxes[i].setPosition(x, y);
            itemBoxes[i].setFillColor(sf::Color(30, 30, 80));
            itemBoxes[i].setOutlineColor(sf::Color::Cyan);
            itemBoxes[i].setOutlineThickness(2);

            itemNames[i].setFont(font);
            itemNames[i].setString(std::to_string(i + 1) + ". " + names[i]);
            itemNames[i].setCharacterSize(24);
            itemNames[i].setFillColor(sf::Color::White);
            itemNames[i].setPosition(x + 10, y + 10);

            itemDesc[i].setFont(font);
            itemDesc[i].setString(descs[i]);
            itemDesc[i].setCharacterSize(20);
            itemDesc[i].setFillColor(sf::Color(180, 180, 255));
            itemDesc[i].setPosition(x + 10, y + 50);

            itemPrices[i].setFont(font);
            itemPrices[i].setString("Cost: " + std::to_string(costs[i]) + " Gems");
            itemPrices[i].setCharacterSize(22);
            itemPrices[i].setFillColor(sf::Color::Yellow);
            itemPrices[i].setPosition(x + 10, y + 90);
        }
    }

    // returns 0=stay, 3=back to menu
    int update(sf::Event& event, Player& p1, Player* p2 = nullptr, bool multi = false)
    {
        gemDisplay.setString("Gems: " + std::to_string(p1.getGem()));

        if (msgTimer > 0) msgTimer--;
        else msg.setString("");

        if (event.type != sf::Event::KeyPressed &&
            event.type != sf::Event::MouseButtonPressed)
            return 0;

        if (event.type == sf::Event::KeyPressed) {
            // press 1-4 to buy
            int buy = -1;
            if (event.key.code == sf::Keyboard::Num1) buy = 0;
            if (event.key.code == sf::Keyboard::Num2) buy = 1;
            if (event.key.code == sf::Keyboard::Num3) buy = 2;
            if (event.key.code == sf::Keyboard::Num4) buy = 3;

            if (buy >= 0)
            {
                if (p1.getGem() >= costs[buy])
                {
                    p1.addGem(-costs[buy]);
                    if (buy == 0) p1.addLive(1);
                    else          p1.applyPowerUp();
                    msg.setString("Bought: " + names[buy] + "!");
                    msg.setFillColor(sf::Color::Green);
                    msgTimer = 120;
                }
                else
                {
                    msg.setString("Not enough gems!");
                    msg.setFillColor(sf::Color::Red);
                    msgTimer = 120;
                }
            }

        }
        //mouse click on boxes
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 4; i++)
            {
                if (itemBoxes[i].getGlobalBounds().contains(click))
                {
                    if (p1.getGem() >= costs[i])
                    {
                        p1.addGem(-costs[i]);
                        if (i == 0) p1.addLive(1);
                        else        p1.applyPowerUp();
                        msg.setString("Bought: " + names[i] + "!");
                        msg.setFillColor(sf::Color::Green);
                    }
                    else
                    {
                        msg.setString("Not enough gems!");
                        msg.setFillColor(sf::Color::Red);
                    }
                    msgTimer = 120;
                }
            }
        }
        return 0;
    }
    

    void draw(sf::RenderWindow& window)
    {
        window.draw(background);
        window.draw(title);
        window.draw(gemDisplay);
        window.draw(backText);
        window.draw(msg);
        for (int i = 0; i < 4; i++)
        {
            window.draw(itemBoxes[i]);
            window.draw(itemNames[i]);
            window.draw(itemDesc[i]);
            window.draw(itemPrices[i]);
        }
    }
};