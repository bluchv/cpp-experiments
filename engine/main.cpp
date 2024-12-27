#include <iostream>
#include <array>
#include <unordered_map>
#include <map>
#include <functional>
#include "games/number_guessing.cpp"

using namespace std;

int main()
{
	std::unordered_map<std::string, std::function<int()>> gameFunctionsMap;
	gameFunctionsMap["number-guess"] = start_guess_game;

	int gamesPlayed = 0;
	int cash = 0;
	int size = gameFunctionsMap.size(); 
	int i = 0;

	string game;
	string allowedGames = "";

	// Compile a list of games
	for (auto [validGame, fn] : gameFunctionsMap) {
		i += 1;
		if (allowedGames != "")
		{
			if (i + 1 >= size)
			{
				allowedGames = allowedGames + " " + validGame + ". ";
			}
			else
			{
				allowedGames = allowedGames + " " + validGame + ",";
			}
		}
		else {
			if (i + 1 >= size)
			{
				allowedGames = validGame + ". ";
			}
			else
			{
				allowedGames = validGame + ",";
			}
		}
	}


	// Main loop - Await user input, find the game, play the game, continue
	while (true)
	{
		std::cout << "Choose your game type. Options: " << allowedGames;
		std::cin >> game;

		if (!gameFunctionsMap.contains(game))
		{
			std::cout << "Invalid option. Game doesn't exist!\n" << std::endl;
		}
		else 
		{
			auto gameCallbackFunction = gameFunctionsMap[game];
			std::cout << "Starting game...\n" << std::endl;

			if (gameCallbackFunction)
			{
				int cashToAward = gameCallbackFunction();
				cash += cashToAward;
				gamesPlayed += 1;
				std::cout << "You now have " << cash << " cash left." << " You've played " << gamesPlayed << (gamesPlayed != 1 ? " games" : " game") << std::endl;
			}
		}
	}
	
	return 0;
}