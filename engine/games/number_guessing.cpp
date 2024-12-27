#include <iostream>
#include <cstdlib>
#include <ctime>
#include <format>
#include <chrono>
#include <thread>

using namespace std;

void print(string msg, int guesses, int maxGuesses)
{
    printf("%s (%d/%d) ", msg.c_str(), guesses, maxGuesses);
}

int start_guess_game()
{
    srand(static_cast<unsigned int>(time(0)));

    // Random number between 1 and 100
    int secretNumber = rand() % 100 + 1;
    int guess = 0;
    int maxGuesses = 10;
    int numberOfGuesses = 0;
    int prize = rand() % 50 + 1;
    bool guessedCorrectly = false;

    std::cout << "A number between 1 and 100 has been generated" << std::endl;
    std::cout << "Can you guess the number? You have " << maxGuesses << " guesses" << "(dev mode - " << secretNumber << ")" << std::endl;

    while (guess != secretNumber)
    {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        numberOfGuesses += 1;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Error - You input a letter!" << std::endl;
            break;
        }

        if (numberOfGuesses > maxGuesses + 1)
        {
            std::cout << "Too many guesses! The number was " << secretNumber << std::endl;
            break;
        }

        if (guess > 100 || guess < 1)
        {
            std::cout << "Number must be between 1-100!" << std::endl;
            continue;
        }

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
            printf("Good job! You guessed the number. +%d cash\n", prize);
        }
    }

    if (!guessedCorrectly)
    {
         printf("You failed to guess the number :(. -%d cash\n", prize);
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