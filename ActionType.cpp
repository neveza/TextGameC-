#include <functional>
#include "ActionType.h"

ActionType::ActionType(std::string id, std::string typeDescript, std::string actDescript,
    std::function<void(Actor& target, Actor& self)> behavior) {
    this->id = id;
    this->typeDescript = typeDescript;
    this->actDescript = actDescript;
    this->behavior = std::move(behavior);
}

ActionType::ActionType(std::function<void(Actor& target, Actor& self)> behavior) {
    this->id = "NA";
    this->typeDescript = "NA";
    this->actDescript = "NA";
    this->behavior = std::move(behavior);
}

ActionType::ActionType() {};