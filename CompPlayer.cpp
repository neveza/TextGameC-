#include "CompPlayer.h"
#include <iostream>

using std::cin; using std::cout; using std::endl;

//std::vector<char> CompPlayer::decision(int nActions)
//{
//	std::vector<char> decision;
//	for (int n = 0; n < nActions; ++n)
//	{
//		for (std::string priorityId : priority)
//		{
//			if (truthTable[priorityId])
//			{
//				decision.push_back(actionInterface[priorityId]);
//				break;
//			}
//		}
//	}
//	return decision;
//};
//
//void CompPlayer::generateTruthTable(Actor& self, Actor& target)
//{
//	truthTable = {
//		{ActionIds::PUNCH_ID, (self.power > target.physique)},
//		{ActionIds::BLOCK_ID, (self.physique < self.power)},
//		{ActionIds::YELL_ID, (self.power < target.power)},
//	};
//}

bool CompPlayer::willAttack() {
	return ((truthTable[statTestKey::POWER_VS_PHYSIQUE] & 
		     (truthTable[statTestKey::GREAT_HEALTH] | truthTable[statTestKey::GOOD_HEALTH])
		   ));
}

bool CompPlayer::willDefend() {
	return ( ~(truthTable[statTestKey::PHYSIQUE_VS_POWER]) |
		      (truthTable[statTestKey::BAD_HEALTH] | truthTable[statTestKey::NEAR_DEATH_HEALTH])
		   );
}

bool CompPlayer::willBuff() {
	return (~(truthTable[statTestKey::POWER_VS_PHYSIQUE] | truthTable[statTestKey::PHYSIQUE_VS_POWER]));
}

std::vector<char> CompPlayer::decision(int nActions)
{
	std::vector<char> decision;
	int n = 0;

	while (n < nActions)
	{
		for(auto behave : priority)
		{ 
			switch (behave)
			{
			case PriorityEnums::priorities::FIGHT:
				if (willAttack())
				{
					decision.push_back(actionInterface[ActionIds::PUNCH_ID]);
					break;
				}
			case PriorityEnums::priorities::DEFEND:
				if (willDefend())
				{
					auto opt = actionInterface.find(ActionIds::BLOCK_ID);
					if (opt != actionInterface.end())
					{
						decision.push_back(opt->second);
						break;
					}
				}
			case PriorityEnums::priorities::BUFF:
				if (willBuff())
				{
					decision.push_back(actionInterface[ActionIds::YELL_ID]);
					break;
				}

			default: //unsure at this point for default. Debating either do an auto top priority or leave it as nothing
				break;
			}

			++n;
			if (!(n < nActions)) break;
		}
	}
	return decision;
};

void CompPlayer::generateTruthTable(Actor& self, Actor& target)
{
	truthTable = {
		(self.power > target.physique), //powerToPhys test
		(self.physique > self.power),   //physiqueToPower test
		(self.quick > target.quick),    //quickToQuick test
		(self.getHealthPercent() > 80), //Great Health
		(50 < self.getHealthPercent() && self.getHealthPercent() < 80), // okay Health
		(40 < self.getHealthPercent() && self.getHealthPercent() < 50), // bad Health
		(self.getHealthPercent() < 40), //near death Health
	};
}


void CompPlayer::setPriority(const std::vector<int> newPriority)
{
	priority = newPriority;
};

CompPlayer::CompPlayer(std::map<char, ActionType> actions, std::vector <int> initPriority)
{
	priority = initPriority;

	for (auto& it : actions)
	{
		actionInterface.emplace(it.second.id, it.first);
	}
}