#include "game_manager.h"
#include <random>

using std::string;

GameManager::GameManager() = default;

GameManager::~GameManager() = default;

Game &GameManager::getCurrentGame()
{
    if(!currentGame.has_value()) {
        throw std::logic_error("No game is loaded.");
    }
    return *namedGames[currentGame.value()];
}

void GameManager::newGame(const string name, size_t size)
{
    if (namedGames.find(name) == namedGames.end()) {
        setUpGame(name, size);
        currentGame = name;
    } else {
        throw std::invalid_argument("The named game already exists, use a different name.");
    }
}

void GameManager::switchGame(string name)
{
    if (namedGames.find(name) == namedGames.end()) {
        throw std::invalid_argument("The requested game does not exist.");
    }
    currentGame = name;
}

void GameManager::restartGame()
{
    if (!isGameLoaded()) {
        throw std::logic_error("No game is loaded.");
    }
    namedGames[currentGame.value()]->placePlayer(0, 0);
}

bool GameManager::isGameLoaded()
{
    return currentGame.has_value();
}

void GameManager::gameCompleted()
{
    if (!isGameLoaded()) {
        throw std::logic_error("No game is loaded.");
    }
    removeGame(currentGame.value());
}

void GameManager::setUpGame(const std::string name, size_t size)
{
    if (size < 5) {
        size = 5;
    } else if (size > 15) {
        size = 15;
    }

    namedGames[name] = std::make_unique<Game>(size);

    namedGames[name]->placePlayer(0, 0);
    namedGames[name]->placeExit(size - 1, size - 1);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(1, size - 2);

    int wallCounter = 0;
    while (wallCounter < 6) {
        size_t x = dist(mt);
        size_t y = dist(mt);
        Board::CellType cell = namedGames[name]->getCellType(y, x);
        if (cell == Board::CellType::WALL || cell == Board::CellType::PLAYER ||
            cell == Board::CellType::EXIT)
        {
            continue;
        }
        namedGames[name]->placeWall(y, x);
        ++wallCounter;
    }
}

void GameManager::removeGame(const string name)
{
    namedGames.erase(name);
    if (name == currentGame.value()) {
        currentGame.reset();
    }
}