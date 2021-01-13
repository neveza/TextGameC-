#pragma once
#include <string>
#include <map>
#include "ActionType.h"
#include <functional>
#include <vector>
#include <array>
#include "ActionConstants.h"
#include "Actor.h"

enum statTestKey {POWER_VS_PHYSIQUE, PHYSIQUE_VS_POWER, QUICK_VS_QUICK, GREAT_HEALTH, GOOD_HEALTH, BAD_HEALTH, NEAR_DEATH_HEALTH};

namespace PriorityEnums
{
	enum priorities{ FIGHT, DEFEND, BUFF, }; // May update with stance change and behavior change

	//behaviors
	static const std::vector<int> aggressive = { FIGHT, DEFEND, BUFF };
	static const std::vector<int> defensive = { DEFEND, BUFF, FIGHT };
	static const std::vector<int> buffer = { BUFF, FIGHT, DEFEND };
};

//The brain of the enemy actor class
class CompPlayer {
public:
	bool willAttack();
	bool willDefend();
	bool willBuff();
	std::map<std::string, char> actionInterface; //ActionType.id -> alpha

	std::vector<int> priority;

	std::vector <std::function<bool()>> decisionPaths = { };
	//std::function<bool()> blah = willAttack;

	//std::map<std::string, bool> truthTable;
	std::vector<bool> truthTable;

	std::vector<char> decision(int nActions);

	void setPriority(const std::vector<int> newPriority);

	void generateTruthTable(Actor& self, Actor& target);

	CompPlayer(std::map<char, ActionType> action, const std::vector<int> initPriority);
};