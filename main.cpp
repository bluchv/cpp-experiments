#include <iostream>
#include <array>
#include <unordered_map>
#include <map>
#include <functional>
#include "games/number_guessing.cpp"

using namespace std;

int main()
{
	std::unordered_map<std::string, std::function<int()>> funcMap;
	funcMap["number-guess"] = start_guess_game;

	int gamesPlayed = 0;
	int cash = 0;
	int size = funcMap.size(); 
	int i = 0;

	string game;
	string allowedGames = "";

	for (auto [validGame, fn] : funcMap) {
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


	while (true)
	{
		std::cout << "Choose your game type. Options: " << allowedGames;
		std::cin >> game;

		if (!funcMap.contains(game))
		{
			std::cout << "Invalid option. Game doesn't exist!\n" << std::endl;
		}
		else 
		{
			auto fn = funcMap[game];
			std::cout << "Starting game...\n" << std::endl;

			if (fn)
			{
				int cashToAward = fn();
				cash += cashToAward;
				gamesPlayed += 1;
				std::cout << "You now have " << cash << " cash left." << " You've played " << gamesPlayed << " games\n" << std::endl;
			}
		}
	}
	
	return 0;
}