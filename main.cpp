//
// Created by Ajay Sharma on 18/12/25.
//

#include "utils/GameConsole.h"

int main()
{
    try {
        auto *gameConsole = new GameConsole();
        gameConsole->displayWelcome();
        const Game::Difficulty difficulty = gameConsole->selectDifficulty();
        gameConsole->displayDifficultyInfo(difficulty);

        // Clear input buffer after difficulty selection
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        const Game game(difficulty);
        std::string input;

        std::cout << "\nPress Enter to start playing..." << std::endl;
        std::getline(std::cin, input);

        while (true) {
            std::cout << std::endl;
            game.displayGameInfo();
            game.displayBoard();

            if (game.isGameOver()) {
                if (game.getState() == Game::GameState::WON) {
                    std::cout << "\n🎉 CONGRATULATIONS! You won";
                    if (game.getLives() < game.getMaxLives()) {
                        std::cout << " (used " << (game.getMaxLives() - game.getLives()) << " lives)";
                    }
                    std::cout << "! 🎉" << std::endl;
                } else {
                    std::cout << "\n💀 GAME OVER - All lives lost! 💀" << std::endl;
                }
                std::cout << "Type 'n' for new game or 'q' to quit." << std::endl;
            }

            std::cout << "\nEnter command: ";
            std::getline(std::cin, input);

            if (!gameConsole->processCommand(game, input)) {

            }

            // Clear screen for better visibility (optional)
            gameConsole->clearScreen();
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
}