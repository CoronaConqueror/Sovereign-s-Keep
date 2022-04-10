#pragma once
#include "Player.h"
#include <fstream>
#include <string>

class DataManager
{
/*
 This class will save & load player data to & from a file.
*/
public:
	static void SavePlayerData(Player& player);
	static void LoadPlayerData(Player& player);
};