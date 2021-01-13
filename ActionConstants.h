#pragma once
#include <string>

//might consider having these in text or data files
struct ActionIds
{
    constexpr static char PUNCH_ID[] = "Punch";
    constexpr static char BLOCK_ID[] = "Block";
    constexpr static char YELL_ID[] = "Yell";
    constexpr static char WEEP_ID[] = "Weep";
    constexpr static char SKIP_ID[] = "Skip";
    constexpr static char OFFENSIVE_STANCE_ID[] = "Offensive Stance";
    constexpr static char DEFENSIVE_STANCE_ID[] = "Defensive Stance";
    constexpr static char BALANCED_STANCE_ID[] = "Balanced Stance";
    constexpr static char FLIGHTY_STANCE_ID[] = "Flighty Stance";
};