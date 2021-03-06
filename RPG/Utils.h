#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include "Case.h"
#include "Log.h"

enum ItemTypes
{
    SWORD,
    WOOD,
    IRON,
    WATER_BUCKET,
    ITEM_NONE
};

enum EnemiTypes
{
    GOBLIN_S,
    GOBLIN_L,
    GOBLIN_R,
    GOBLIN_WATER,
    ENIMIES_NONE
};

enum PlayerStates
{
    STATIC_R,
    STATIC_L,


    S_ATTACK_R,
    S_ATTACK_L,


    S_DEFEND_R,
    S_DEFEND_L,


    S_N_ATTACK,

    S_LIGHT,
    S_BAG,
    S_WATER,

    DEAD,
};

struct ChunkUpdate {
    bool EnemyUpdate = false;
    bool ItemUpdate = false;
    std::vector<std::pair<ItemTypes,sf::Vector2f>> ItemsCollect;
};


struct PlayerObject
{
    bool isRight;
    sf::Vector2f position;
    bool isCTRL;
    PlayerStates state;
    bool isNight;
};

struct EnemyUpdate
{
    bool hasUpdate = false;
};

struct ItemUpdate {
    bool hasUpdate = false;
    ItemTypes type;
};

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


static bool isTypeEnemy( EnemiTypes* enemy, EnemiTypes& type,int size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (type == enemy[i])
        {
            return true;
        }
    }

    return false;
}

static bool isPlayerAround(sf::Vector2f& player, sf::Vector2f& enemy, int r)
{
    int dist = (int)sqrt(pow(player.x - enemy.x, 2) + pow(player.y - enemy.y, 2));
    if (dist < r)
    {
        return true;
    }
    return false;
}

static sf::Vector2f moveEnemyToPlayer(sf::Vector2f& player, sf::Vector2f& enemy, float move)
{
    sf::Vector2f m = enemy;

    if (player.x != enemy.x)
    {
        if (player.x > enemy.x)
        {
            m.x += move;
        }
        else
        {
            m.x -= move;
        }
    }

    if (player.y != enemy.y)
    {
        if (player.y > enemy.y)
        {
            m.y += move;
        }
        else
        {
            m.y -= move;
        }
    }

   
    return m;
}

static sf::Vector2f movePlayerToEnemyDist(sf::Vector2f& player, sf::Vector2f& enemy, float move,int dist)
{
    sf::Vector2f m = enemy;
    sf::Vector2f future = moveEnemyToPlayer(player, enemy, move);

    if (dist < sqrt(pow(player.x - future.x, 2) + pow(player.y - future.y, 2)))
    {
        m = future;
    }

    return m;
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

static void resizeImage(const sf::Image& originalImage, sf::Image& resizedImage)
{
    const sf::Vector2u originalImageSize{ originalImage.getSize() };
    const sf::Vector2u resizedImageSize{ resizedImage.getSize() };
    for (unsigned int y{ 0u }; y < resizedImageSize.y; ++y)
    {
        for (unsigned int x{ 0u }; x < resizedImageSize.x; ++x)
        {
            unsigned int origX{ static_cast<unsigned int>(static_cast<double>(x) / resizedImageSize.x * originalImageSize.x) };
            unsigned int origY{ static_cast<unsigned int>(static_cast<double>(y) / resizedImageSize.y * originalImageSize.y) };
            resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
        }
    }
}