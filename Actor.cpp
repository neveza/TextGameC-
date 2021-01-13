#include <iostream>
#include <iomanip>
#include "Actor.h"


//It'll drop decimal, but not important.
int Actor::getHealthPercent(){return ((currHealth * 100)/maxHealth);}

int Actor::calcNumOfActions(int oppossingQuick)
{
    //int num = ((2*quick - oppossingQuick) / 10);  // faster change
    //int num = (quick - opposingQuick)/10; // slower change

    int num = quick / 10; //temp resolve to make the game playable and not overly difficult

    if (num <= 0)
    {
        num = 1; //min actions possible
    }
    else if (num >= 10)
    {
        num = 10; // max actions possible
    }

    return num;
}

void Actor::addDebuffQueue(std::function<void(Actor& target, Actor& self)> action)
{
    debuffQueue.push_back(ActionType(action));
}

void Actor::runDebuffQueue(Actor& target)
{
    if (debuffQueue.size() > 0)
    {
        debuffQueue.front().behavior(target, *this);
        debuffQueue.pop_back();
    }
}

void Actor::addAction(ActionType& act)
{
    actions.emplace(ALPHA_MIN + numActOptions++, act);
}

void Actor::addAction(char key, ActionType& act)
{
    actions.emplace(key, act);
}

void Actor::addDefaultAction(ActionType& act)
{
    actions.emplace('0', act);
}

void Actor::addActQueue(char actSymbol)
{

    auto it = actions.find(actSymbol);
    if (it == actions.end()) {
        it = actions.find('0');
    }
    ActionType& act = it->second;

    actQueue.push_back(act);

    //actNext = '0';
};

void Actor::runActQueue(Actor& target)
{
    if (actQueue.size() > 0)
    {
        std::cout << std::endl << name << ":" << std::endl;
        for (int n = 0; n < actQueue.size(); n++)
        {
            ActionType act = actQueue[n];
            std::cout << act.actDescript << std::endl;
            act.behavior(target, *this);
            std::cout << std::endl;
        }
        actQueue.clear();
    }
}

void Actor::printStats()
{
    std::string stanceText = " ";
    switch (stance)
    {
        case Stances::BALANCED: { stanceText = "Balanced"; break; }
        case Stances::OFFENSIVE: { stanceText = "Offensive"; break; }
        case Stances::DEFENSIVE: { stanceText = "Defensive"; break; }
        case Stances::FLIGHTY: { stanceText = "Flighty"; break; }
    }
    std::cout << "Current Stance: " << stanceText << std::endl << std::endl;

    std::cout << "Health: " << currHealth << std::endl;
    std::cout << "Physique: " << physique << std::endl;
    std::cout << "Power: " << power << std::endl;
    std::cout << "Quick: " << quick << std::endl;
    std::cout << std::endl;

}

void Actor::printActions()
{
    std::cout << "****************************Available Actions!*************************" << std::endl;
    for (int i = 0; i < numActOptions; i++)
    {

        int maxIndent = 30;

        std::cout << static_cast<char>(ALPHA_MIN + i) << " " << actions[ALPHA_MIN + i].id;
        int width = (maxIndent - actions[ALPHA_MIN + i].id.length());
        i++;
        if (i >= numActOptions)
        {
            break;
        }
        std::cout << std::setw(width) << static_cast<char>(ALPHA_MIN + i) << " " << actions[ALPHA_MIN + i].id << std::endl;
    }

    std::cout << std::endl;
}

Actor::Actor(std::string name, std::string description, int health, int physique, int power, int quick)
{
    this->name = name;
    this->maxHealth = health;
    this->currHealth = this->maxHealth;
    this->physique = physique;
    this->power = power;
    this->quick = quick;
    this->description = description;
}