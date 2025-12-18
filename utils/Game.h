#pragma once

#include <bits/stdc++.h>
#include "Board.h"

using namespace std;

#define DEFAULT_MAX_LIVES 2

class Game {
public:
    enum GameState
    {
        NOT_STARTED,
        WON, 
        LOST,
        IN_PROGRESS,
    };

    enum Difficulty 
    {
        BEGINNER,
        INTERMEDIATE,
        EXPERT
    };

    explicit Game(Difficulty difficulty);
    ~Game();

    void initializeBoard();
    void start();
    void restart();
    void setMaxLives(int maxLives);
    void resetLives();
    void displayBoard() const;
    void displayGameInfo() const;
    void displayHelp() const; 
    void updateGameState(); 
    void getDifficultySettings(int& width, int& height, int& mines) const; 
    void loseLife(); 
    void continueAfterLifeLost(); 
    
    bool makeMove(int x, int y, char action);
    bool isGameOver() const;
    bool hasLivesRemaining() const;

    double getElapsedTime();
    
    int getLives() const;
    int getMaxLives() const;

    Game::GameState getState() const;
    
    Board* getBoard(); 
    const Board* getBoard() const; 
    
private:
    Board *m_board;
    GameState m_gameState;
    Difficulty m_difficulty;
    bool m_firstMove;
    int m_lives;
    int m_maxLives;
    chrono::steady_clock::time_point m_startTime;
    chrono::steady_clock::time_point m_endTime;
};

inline Game::Game(const Difficulty difficulty)
    : m_board(nullptr)
    , m_gameState(GameState::NOT_STARTED)
    , m_difficulty(difficulty)
    , m_firstMove(true)
    , m_lives(DEFAULT_MAX_LIVES)
    , m_maxLives(DEFAULT_MAX_LIVES)
{
    // Minimal constructor implementation to prevent test skips
    // Create a basic board to prevent segfaults, but other functions will still throw
    try {
        initializeBoard();
    } catch (const std::logic_error&) {
        // Fallback: create a minimal board to prevent crashes
        m_board = new Board(8, 8, 10);
    }
}

inline Game::~Game() {
    delete m_board;
}

inline void Game::start() {
    // Start the game
    // 1. Set game state to IN_PROGRESS
    m_gameState = GameState::IN_PROGRESS;
    // 2. Record start time using std::chrono::steady_clock::now()
    m_startTime = std::chrono::high_resolution_clock::now();
    // 3. Set m_firstMove to true
    m_firstMove = true;
}

inline void Game::restart() {
    delete m_board;
    initializeBoard();
    m_gameState = GameState::NOT_STARTED;
    m_firstMove = true;
    resetLives();
}

inline Game::GameState Game::getState() const {
    // Return current game state (this works)
    return m_gameState;
}

inline bool Game::isGameOver() const {
    // Return true if game is won or lost
    return m_gameState == WON or m_gameState == LOST;
}

inline double Game::getElapsedTime() {
    m_endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(m_endTime - m_startTime).count();
}

inline int Game::getLives() const {
    // Return the current number of lives remaining
    return m_lives;
}

inline int Game::getMaxLives() const {
    // Return maximum number of lives (this works)
    return m_maxLives;
}

inline bool Game::hasLivesRemaining() const {
    // Return true if player has lives remaining (this works)
    return m_lives > 0;
}

inline void Game::setMaxLives(int maxLives) {
    // Set maximum number of lives
    if (maxLives > 0) {
        m_maxLives = maxLives;
        m_lives = m_maxLives;
    }
}

inline void Game::resetLives() {
    // Reset current lives to maximum lives
    m_lives = m_maxLives;
}

inline void Game::displayBoard() const {
    // Display the game board
    if ( m_board == nullptr ) {
        return;
    }
    m_board->display();
}

inline Board* Game::getBoard() {
    // Return pointer to board (this works to prevent segfaults)
    return m_board;
}

inline const Board* Game::getBoard() const {
    // Return const pointer to board (this works to prevent segfaults)
    return m_board;
}

inline void Game::initializeBoard() {
    // Initialize board based on difficulty
    int width, height, minesCnt;
    getDifficultySettings(width, height, minesCnt);
    m_board = new Board(width, height, minesCnt);
}

inline void Game::getDifficultySettings(int& width, int& height, int& mines) const {
    // Set difficulty parameters based on m_difficulty
    // BEGINNER: 8x8, 10 mines
    // INTERMEDIATE: 14x14, 30 mines  
    // EXPERT: 20x20, 80 mines
    switch (m_difficulty) {
        case Game::Difficulty::BEGINNER:
            width = 8;
            height = 8;
            mines = 10;
            break;
        case Game::Difficulty::INTERMEDIATE:
            width = 14;
            height = 14;
            mines = 30;
            break;
        case Game::Difficulty::EXPERT:
            width = 14;
            height = 14;
            mines = 30;
            break;
        default:
            width = 8;
            height = 8;
            mines = 10;
            break;
    }
}

inline void Game::loseLife() {
    // Reduce lives by 1 if lives > 0
    if (m_lives > 0) {
        m_lives--;
    }
}


inline bool Game::makeMove(int x, int y, char action) {
    // TODO: Make a move in the game
    // 1. If game not started, call start()
    // 2. If game is over, return false
    // 3. Handle action 'r'/'R' for reveal:
    //    - Call board->revealCell(x, y)
    //    - If unsuccessful and cell is a mine (Lives System):
    //      * Call loseLife() to reduce lives
    //      * If hasLivesRemaining(), continue game and show mine hit message
    //      * If no lives left, set state to LOST and record end time
    // 4. Handle action 'f'/'F' for flag:
    //    - Call board->toggleFlag(x, y)
    // 5. Call updateGameState() to check win/loss conditions
    // 6. Set m_firstMove to false
    throw std::logic_error("makeMove() function is not yet implemented");
}

inline void Game::updateGameState() {
    // TODO: Update game state based on board conditions
    // 1. If game is IN_PROGRESS:
    //    - Check if board->isGameWon(), set state to WON and record end time
    // NOTE: With lives system, don't check isGameLost() here anymore
    // Mine hits are handled in makeMove() and only end game when lives run out
    throw std::logic_error("updateGameState() function is not yet implemented");
}
inline void Game::continueAfterLifeLost() {
    // TODO: Handle continuation after life lost
    // The mine that was hit remains revealed as a warning
    // The game continues in IN_PROGRESS state
    // No other changes needed - player can continue from current state
    throw std::logic_error("continueAfterLifeLost() function is not yet implemented");
}

inline void Game::displayHelp() const {
    // TODO: Display help information
    // Show available commands, game legend, objective, and lives system info:
    // 1. Commands (reveal, flag, help, quit, new game, debug)
    // 2. Legend (symbols and their meanings)
    // 3. Lives System explanation:
    //    - Starting lives count
    //    - Life loss on mine hit
    //    - Continuation after mine hit
    //    - Game over when all lives lost
    // 4. Objective (reveal all non-mine cells)
    throw std::logic_error("displayHelp() function is not yet implemented");
}


inline void Game::displayGameInfo() const {
    // TODO: Display game information
    // 1. Show difficulty level name (BEGINNER/INTERMEDIATE/EXPERT)
    // 2. Show grid dimensions and mine count
    // 3. Show flag count and remaining mines
    // 4. Show lives information (current/max lives) - NEW for lives system
    // 5. Show elapsed time
    // 6. Show current game status with lives-specific messages:
    //    - For IN_PROGRESS: warn if lives lost
    //    - For WON: show lives used if any
    //    - For LOST: show lives-specific game over message
    throw std::logic_error("displayGameInfo() function is not yet implemented");
}

