#include <iostream>
#include "game_manager.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main()
{
    GameManager manager;
    while (true) {
        char command;
        string name;
        size_t size;
        cout << "------------------------------------------------------" << endl;
        if (manager.isGameLoaded()) {
            Game &game = manager.getCurrentGame();
            game.printBoard();
            cout << "r - restart game, t - switch to another game, z - create new game, x - "
                    "exit"
                 << endl;
            cout << "w - up, s - down, a - left, d - right" << endl;
            cout << "Enter command: " << endl;
            cin >> command;
            try {
                switch (command) {
                    case 'w':
                        game.moveUp();
                        break;
                    case 's':
                        game.moveDown();
                        break;
                    case 'a':
                        game.moveLeft();
                        break;
                    case 'd':
                        game.moveRight();
                        break;
                    case 'r':
                        manager.restartGame();
                        break;
                    case 't':
                        cout << "Enter a name of an existing game:" << endl;
                        cin >> name;
                        manager.switchGame(name);
                        break;
                    case 'z':
                        cout << "Enter a new name for a new game:" << endl;
                        cin >> name;
                        cout << "Enter size for a new game: " << endl;
                        cin >> size;
                        manager.newGame(name, size);
                        break;
                    case 'x':
                        return 0;
                    default:
                        cout << "Wrong command" << endl;
                        continue;
                }
            } catch (Game::wallhit_exception) {
                cout << "You have hit a wall, game over." << endl;
                manager.gameCompleted();
                continue;
            } catch (Game::exitreach_exception) {
                cout << "You have reached the exit, game finished." << endl;
                manager.gameCompleted();
                continue;
            } catch (std::out_of_range e) {
                cout << e.what() << endl;
                continue;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
                continue;
            }
        } else {
            cout << "Create a new game or switch to an existing one." << endl;
            cout << "z - create new game, t - switch to another game, x - exit" << endl;
            cout << "Enter command: " << endl;
            cin >> command;
            try {
                switch (command) {
                    case 't':
                        cout << "Enter a name of an existing game:" << endl;
                        cin >> name;
                        manager.switchGame(name);
                        break;
                    case 'z':
                        cout << "Enter a new name for a new game:" << endl;
                        cin >> name;
                        cout << "Enter size for a new game: " << endl;
                        cin >> size;
                        manager.newGame(name, size);
                        break;
                    case 'x':
                        return 0;
                    default:
                        cout << "Wrong command" << endl;
                        continue;
                }
            } catch (std::out_of_range e) {
                cout << e.what() << endl;
                continue;
            } catch (std::invalid_argument e) {
                cout << e.what() << endl;
                continue;
            }
        }
    }
    return 0;
}