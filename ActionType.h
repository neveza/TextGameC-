#pragma once

#include <string>
#include <functional>
//#include "ActionFunctions.h"

class Actor;

enum class Stances{ BALANCED, OFFENSIVE, DEFENSIVE, FLIGHTY };

class ActionType {
public:
    std::string id = "You forgot to add text, dumbshit";
    std::string typeDescript = "You forgot to add text, dumbshit";
    std::string actDescript = "You forgot to add text, dumbshit";

    std::function<void(Actor& target, Actor& self)> behavior;

    ActionType(std::string id, std::string typeDescript, std::string actDescript,
        std::function<void(Actor& target, Actor& self)> behavior);

    ActionType(std::function<void(Actor& target, Actor& self)> behavior);

    ActionType();
};