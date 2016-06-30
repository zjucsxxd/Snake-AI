#include "GameCtrl.h"

int main() {
    auto game = GameCtrl::getInstance();

    // Set map's size. Default is 20*20
    game->setMapRow(20);
    game->setMapColumn(20);

    // Set FPS. Default is 60.0
    game->setFPS(60.0);

    // Set whether to make the snake automove. Default is false
    game->setAutoMoveSnake(false);

    // Set interval time for automove. Default is 200.
    // If setAutoMoveSnake(false), this interval is useless.
    game->setAutoMoveInterval(200);

    // Set whether to use keyboard instructions. Default is true
    game->setEnableKeyboard(true);

    return game->run();
}
