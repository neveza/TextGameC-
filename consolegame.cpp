// consolegame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Actor.h"
#include "ActionType.h"
#include "ActionFunctions.h"
#include "CompPlayer.h"
#include <limits>

int main()
{
    Actor enemy = Actor("Kung-Fu Tommy", "He stands with his black belt fastened tight.", 50, 10, 35, 60);
    Actor player = Actor("Player", "you", 100, 60, 25, 30);

    enemy.addAction(punch);
    enemy.addDefaultAction(weep);
    enemy.addAction(yell);
    player.addAction(punch);
    player.addAction(block);
    player.addAction(yell);
    player.addAction(stanceToOffense);
    player.addAction(stanceToBalanced);
    player.addAction(stanceToDefense);
    player.addAction(stanceToFlighty);
    player.addDefaultAction(skip);

    std::cout << "                                        Welcome to the battle zone!                                          " << std::endl;
    std::cout << "                                              GET PSYCHED!!                                                  " << std::endl << std::endl;

    std::cout << "You are approached by " << enemy.name << ": " << enemy.description << std::endl << std::endl;

    int  enemyActCount = 0;
    while (player.currHealth > 0 && enemy.currHealth > 0)
    {
        //runs debuff sequence at start of round
        player.runDebuffQueue(enemy);
        enemy.runDebuffQueue(player);

        CompPlayer enemyComp = CompPlayer(enemy.actions, PriorityEnums::aggressive);
        enemyComp.generateTruthTable(enemy, player);

        enemy.printStats();

        std::cout << "Truth Table: PunchID = " << enemyComp.willAttack() << std::endl;
        std::cout << "Truth Table: BlockID = " << enemyComp.willDefend() << std::endl;
        std::cout << "Truth Table: YellID = "  << enemyComp.willBuff()    << std::endl;
        std::cout << "Trust Table Health:" << enemyComp.truthTable[statTestKey::GREAT_HEALTH] << enemyComp.truthTable[statTestKey::GOOD_HEALTH] << enemyComp.truthTable[statTestKey::BAD_HEALTH] << std::endl;

        int numberOfAction = player.calcNumOfActions(enemy.quick);

        std::cout << "Player numberOfAction: " << numberOfAction << std::endl;

        char choices[10] = { ' ', ' ', ' ', ' ', ' ', 
                            ' ', ' ', ' ', ' ', ' ' };


        for (int n = 0; n < numberOfAction; n++)
        {
            std::cout << std::endl;
            player.printStats();
            player.printActions();

            char playerAct;
            std::cout << "Choose your actions: ";
            std::cin >> playerAct;
            playerAct = tolower(playerAct);
            std::cout << std::endl;

            player.addActQueue(playerAct);
            choices[n] = playerAct;

            std::cout << "[";
            for (int i = 0; i < numberOfAction; i++)
            {
                std::cout << choices[i];
            }
            std::cout << "]" << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits <std::streamsize > ::max(), '\n');

        numberOfAction = enemy.calcNumOfActions(player.quick);

        std::cout << "Enemy's actions: " << numberOfAction << std::endl << std::endl;
        //enemyComp.decision(numberOfAction);

        for (auto action : enemyComp.decision(numberOfAction))
        {
            std::cout << "Decision actions: " << action << std::endl;
            enemy.addActQueue(action);
        }

        //runs act queue after all inputs
        player.runActQueue(enemy);
        enemy.runActQueue(player);
    }  
}

