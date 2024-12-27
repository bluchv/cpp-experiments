#include <chrono>
#include <cstdlib>
#include <ctime>
#include <format>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

void print(string msg, int guesses, int maxGuesses)
{
    std::cout << std::format("{} ({}/{}) ", msg, guesses, maxGuesses);
}

int start_guess_game()
{
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister random number generator
    std::uniform_int_distribution<> dis(1, 100);
    std::uniform_int_distribution<> rewardGeneration(1, 50);

    // Random number between 1 and 100
    int secretNumber = dis(gen);
    int guess = 0;
    int maxGuesses = 10;
    int numberOfGuesses = 0;
    int prize = rewardGeneration(gen);
    bool guessedCorrectly = false;

    std::cout << "A number between 1 and 100 has been generated" << std::endl;
    std::cout << "Can you guess the number? You have " << maxGuesses << " guesses"
              << " (it's def not - " << secretNumber << ")" << std::endl;

    while (guess != secretNumber)
    {
        // Clear buffer and prompt for input
        std::cin.clear();
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        numberOfGuesses++;

        // Handle invalid input
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Error - You input a letter!\n";
            continue;
        }

        // Check if guesses exceed max guesses
        if (numberOfGuesses > maxGuesses)
        {
            std::cout << std::format("You failed to guess the number! It was {}. As a result, you "
                                     "have lost {} cash :(\n",
                                     secretNumber, prize);
            break;
        }

        // Validate guess range
        if (guess > 100 || guess < 1)
        {
            std::cout << "Number must be between 1 and 100!\n";
            continue; // Ask the player to guess again
        }

        // Provide feedback on the guess
        if (guess > secretNumber)
        {
            print("Too high! Try again!", numberOfGuesses, maxGuesses);
        }
        else if (guess < secretNumber)
        {
            print("Too low! Try again!", numberOfGuesses, maxGuesses);
        }
        else
        {
            guessedCorrectly = true;
            std::cout << std::format("Good job! You guessed the number. +{} cash\n", prize);
        }
    }

    std::cin.ignore();
    std::cin.get();

    if (guessedCorrectly)
    {
        return prize;
    }
    else
    {
        return -prize;
    }
}