#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int coin_flip()
{
    srand(static_cast<unsigned int>(time(0)));
    return rand() % 2;
}

int start_coin_flip_game()
{
    string playerGuess;
    int flipResult;
    int cash = 100;
    int wager;

    cout << "Welcome to Heads or Tails!\n";
    cout << "You have " << cash << " cash.\n";

    // Main game loop
    while (cash > 0)
    {
        cout << "\nEnter your guess (heads or tails, exit to leave): ";
        cin >> playerGuess;

        // Convert to lowercase to make the guess case-insensitive
        for (auto &c : playerGuess)
        {
            c = tolower(c);
        }

        // Check if the player's guess is valid
        if (playerGuess != "heads" && playerGuess != "tails")
        {
            if (playerGuess == "exit")
            {
                break;
            }
            cout << "Invalid guess. Please enter 'heads' or 'tails'.\n";
            continue;
        }

        cout << "How much do you want to wager? You have " << cash << " cash: ";
        cin >> wager;

        // Check if the wager is valid
        if (wager <= 0 || wager > cash)
        {
            cout << "Invalid wager. You can only wager an amount you have.\n";
            continue;
        }

        // Flip the coin
        flipResult = coin_flip();

        // Display the result
        cout << "\nFlipping the coin...\n";
        if (flipResult == 0)
            cout << "Result: Heads!\n";
        else
            cout << "Result: Tails!\n";

        // Check if the player won or lost
        if ((playerGuess == "heads" && flipResult == 0) ||
            (playerGuess == "tails" && flipResult == 1))
        {
            cout << "You won! You gain " << wager << " cash.\n";
            cash += wager;
        }
        else
        {
            cout << "You lost! You lose " << wager << " cash.\n";
            cash -= wager;
        }

        // Check if the player has run out of cash
        if (cash <= 0)
        {
            cout << "\nYou ran out of cash! Game over.\n";
            break;
        }
    }

    return cash;
}
