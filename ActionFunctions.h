#pragma once
#include <iostream>
#include "ActionConstants.h"
//#include "Actor.h"

//class Actor;
void attack(Actor& target, Actor& self)
{
    int attackMod = (self.power + self.attack)/10 * -1;
    int healthMod = attackMod + (target.physique + target.defense)/10;
    if ((healthMod > 0))
    {
        healthMod = 0;
    }
    else if (healthMod == 0)
    {
        healthMod = -1;
    }
    std::cout << " inflicts " << healthMod * -1 << " damage to " << target.name << std::endl;
    target.currHealth += healthMod;
    //std::cout << target.name << " now has " << target.health << std::endl << std::endl;
    return;
}


void changeStance(Actor& self)
{
    switch (self.stance)
    {
    case Stances::BALANCED: {break; }
    case Stances::OFFENSIVE: { self.power += 50; self.quick -= 20;  break; }
    case Stances::DEFENSIVE: {self.physique += 50; self.power -= 50; self.quick -= 10; break; }
    case Stances::FLIGHTY: {self.quick += 15; self.defense += 10; self.power -= 25; break; }
    }
}

void undoStance(Actor& self)
{
    switch (self.stance)
    {
    case Stances::BALANCED: {break; }
    case Stances::OFFENSIVE: {self.power -= 50; self.quick += 20;  break; }
    case Stances::DEFENSIVE: {self.physique -= 50; self.power += 50; self.quick += 10; break; }
    case Stances::FLIGHTY: {self.quick -= 15; self.defense -= 10; self.power += 25; break; }
    }
    return;
}

void changeBalancedStance(Actor& target, Actor& self)
{
    undoStance(self);
    self.stance = Stances::BALANCED;
    changeStance(self);
    return;
}

void changeOffensiveStance(Actor& target, Actor& self)
{
    undoStance(self);
    self.stance = Stances::OFFENSIVE;
    changeStance(self);
    return;
}

void changeDefensiveStance(Actor& target, Actor& self)
{
    undoStance(self);
    self.stance = Stances::DEFENSIVE;
    changeStance(self);
    return;
}

void changeFlightyStance(Actor& target, Actor& self)
{
    undoStance(self);
    self.stance = Stances::FLIGHTY;
    changeStance(self);
    return;
}

void defendNegate(Actor& target, Actor& self)
{
    std::cout << "Your guard drops" << std::endl;
    self.defense -= 10;
    return;
}

void defend(Actor& target, Actor& self)
{
    self.defense += 10;
    self.addDebuffQueue(defendNegate);
    return;
};

void powerUp(Actor& target, Actor& self)
{
    self.power += 5;
    self.quick += 1;
    std::cout << " gains +5 power." << std::endl;
    return;
}

void doNothing(Actor& target, Actor& self) { return; };


//global declaration of ActionTypes - would rather in class, but not sure how yet
//another possiblity is to create a tool that will seralize ActionType and just make a lookup table.
//Possibly a look-up table that returns a created object than having objects in global space?
ActionType punch = ActionType(ActionIds::PUNCH_ID, "A right hook to the face", " hurls back and hits hard into the face", attack);
ActionType block = ActionType(ActionIds::BLOCK_ID, "A firm stance to resist damage", " raises arms up and prepares to take a strike\n", defend);
ActionType skip = ActionType(ActionIds::SKIP_ID, "invalid action or skipped turn", " does nothing wasting their valuable time\n", doNothing);
ActionType weep = ActionType(ActionIds::WEEP_ID, "Weeping", " weeps uncontrollably\n", doNothing);
ActionType yell = ActionType(ActionIds::YELL_ID, "Yell to strengthen", " screeches to the sky to gain strength.", powerUp);
ActionType stanceToOffense = ActionType(ActionIds::OFFENSIVE_STANCE_ID, "Shift to offensive stance", "You shift your weight to your lead foot.", changeOffensiveStance);
ActionType stanceToBalanced = ActionType(ActionIds::BALANCED_STANCE_ID, "Shift to Balanced stance", "You shift your weight equally between your feet.", changeBalancedStance);
ActionType stanceToDefense = ActionType(ActionIds::DEFENSIVE_STANCE_ID, "Shift to Defensive stance", "You shift your weight to your rear foot.", changeDefensiveStance);
ActionType stanceToFlighty = ActionType(ActionIds::FLIGHTY_STANCE_ID, "Shift to Flight stance", "You bounce on your feet", changeFlightyStance);