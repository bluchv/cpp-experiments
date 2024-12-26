#include <iostream>
#include <array>
#include <unordered_map>
#include <functional>
#include "games/number_guessing.cpp"
 
using namespace std;

string validGames[] = {
	"number-guessing"
};

int main()
{
	std::unordered_map<std::string, std::function<int()>> funcMap;
	funcMap["number-guessing"] = start_guess_game;

	int gamesPlayed = 0;
	int cash = 0;
	int size = sizeof(validGames) / sizeof(validGames[0]); 

	string game;
	string allowedGames = "";
	
	for (int i = 0; i < size; i++) {
		string validGame = validGames[i];
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

		if (std::find(std::begin(validGames), std::end(validGames), game) == std::end(validGames))
		{
			std::cout << "You idiot thats not a valid option" << std::endl;
		}
		else 
		{
			auto fn = funcMap[game];
			std::cout << "Starting game..." << std::endl;

			if (fn)
			{
				int cashToAward = fn();
				cash += cashToAward;
				gamesPlayed += 1;
				std::cout << "You now have " << cash << " cash left." << " You've played " << gamesPlayed << " games" << std::endl;
			}
		}
	}
	
	return 0;
}