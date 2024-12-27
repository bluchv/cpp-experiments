#include "games/number_guessing.cpp"
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Game
{
    std::function<int()> startGame;
    std::string description;
};

int main()
{
    std::unordered_map<std::string, Game> gameFunctionsMap = {
        {"number-guess", {start_guess_game, "Guess a number to win or lose cash!"}}};

    int gamesPlayed = 0;
    int cash = 0;
    int size = gameFunctionsMap.size();
    int i = 0;

    string game;
    string allowedGames = "";
    std::ostringstream oss;
    auto start = std::chrono::high_resolution_clock::now();

    // Compile a list of games
    for (auto it = gameFunctionsMap.begin(); it != gameFunctionsMap.end(); ++it)
    {
        if (it != gameFunctionsMap.begin())
            oss << ", ";
        oss << it->first;
    }
    allowedGames = oss.str() + ". ";

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "CPU time used: " << duration.count() << " ms" << std::endl;

    // Main loop - Await user input, find the game, play the game, continue
    while (true)
    {
        std::cout << "Choose your game type. Options: " << allowedGames;
        std::cin >> game;

        if (game == "exit")
        {
            std::cout << "Exiting the program. Thanks for playing!" << std::endl;
            break;
        }

        if (!gameFunctionsMap.contains(game))
        {
            std::cout << "Invalid option. Game doesn't exist!\n" << std::endl;
        }
        else
        {
            auto gameCallbackFunction = gameFunctionsMap[game].startGame;
            std::cout << "Starting game...\n" << std::endl;

            if (gameCallbackFunction != nullptr)
            {
                int cashToAward = gameCallbackFunction();
                cash += cashToAward;
                gamesPlayed += 1;
                std::cout << "You now have " << cash << " cash left." << " You've played "
                          << gamesPlayed << (gamesPlayed != 1 ? " games" : " game") << std::endl;
            }
        }
    }

    return 0;
}