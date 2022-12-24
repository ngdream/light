#include <iostream>
#include "definition.h"
class Level
{
public:
    static void start(sf::RenderWindow &window, int level);

private:
    static void loadmapdatafromstring(std::string data, char map[BLOCK_NUMBER_X][BLOCK_NUMBER_Y]);
};