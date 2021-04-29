#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>

static std::vector<std::string> split(const std::string& txt, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    std::vector<std::string> strs;

    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
        pos = txt.find(ch, initialPos);
    }
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs;
}


static bool getTexture(std::vector<std::pair<int,sf::Texture*>> textures, int index, sf::Texture*& texture)
{
    for (std::pair<int, sf::Texture*> p : textures)
    {
        if (p.first == index)
        {
            texture = p.second;
            return true;
        }
    }

    return false;
}


static Case* getCaseByPosition(std::vector<Case*> cases, sf::Vector2f pos)
{
    sf::Vector2f iPos = sf::Vector2f(0, 0);
    for (int i = 0; i < 100; i += 10)
    {
        for (int j = 0; j < 10; j++)
        {
            if (iPos == pos)
            {
                return cases[static_cast<__int64>(i) + j];
            }
            iPos.x++;
        }

        iPos.y++;
        iPos.x = 0;
    }

    Case* none = new Case(50);
    return none;
}