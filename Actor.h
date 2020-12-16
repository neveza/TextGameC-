#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "ActionType.h"

const int ALPHA_MIN = 97;
const int ALPHA_MAX = 122;

class Actor
{
public:
    std::string name = "NoName";
    std::string description = "You forgot to add text, dumbshit";
    int health = 0;
    int defense = 0;//base defense
    int attack = 0; //base attck

    int power = 0; //for attack calc
    int physique = 0; // for defensive calc
    int quick = 0; // for rounds of action

    Stances stance = Stances::BALANCED;

    std::map<char, ActionType> actions;
    int numActOptions = 0;
    char actNext = '0';

    //std::vector<std::function<void(Actor& target, Actor& self)>> actQueue;
    //std::vector<std::function<void(Actor& target, Actor& self)>> debuffQueue;
    std::vector<ActionType> actQueue;
    std::vector<ActionType> debuffQueue;

    int calcNumOfActions(int oppossingQuick);

    void addDebuffQueue(std::function<void(Actor& target, Actor& self)> action);
    void runDebuffQueue(Actor& target);

    void addActQueue(char actSymbol);
    void runActQueue(Actor& target);

    void addAction(ActionType& act);

    void addAction(char key, ActionType& act);

    void addDefaultAction(ActionType& act);

    //void action(Actor& target);

    void printStats();

    void printActions();

    Actor(std::string name, std::string description, int health, int defense, int strength, int quick);
};