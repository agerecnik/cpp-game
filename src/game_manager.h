#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <optional>
#include <memory>
#include "game.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    Game &getCurrentGame();
    void newGame(const std::string name, size_t size);
    void switchGame(const std::string name);
    void restartGame();
    void gameCompleted();
    bool isGameLoaded();

private:
    std::optional<std::string> currentGame;
    std::map<std::string, std::unique_ptr<Game>> namedGames;

    void setUpGame(const std::string name, size_t size);
    void removeGame(const std::string);
};

#endif