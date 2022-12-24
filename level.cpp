#include "level.h"

bool checkwin(char map[BLOCK_NUMBER_X][BLOCK_NUMBER_Y])
{
    for (int i = 0; i < BLOCK_NUMBER_X; i++)
        for (int j = 0; j < BLOCK_NUMBER_Y; j++)
        {
            if (map[i][j] == '1')
                return false;
        }
    return true;
}

void changecasestatus(int x, int y, char map[BLOCK_NUMBER_X][BLOCK_NUMBER_Y], bool propagate)
{

    if ((y < BLOCK_NUMBER_Y && y >= 0) && (x < BLOCK_NUMBER_X && x >= 0) && map[x][y] != '0')
    {

        switch (map[x][y])
        {
        case '1':
            map[x][y] = '2';
            break;

        case '2':
            map[x][y] = '1';
            break;
        default:
            break;
        }
        if (propagate)
        {
            changecasestatus(x + 1, y, map, false);
            changecasestatus(x + 1, y + 1, map, false);
            changecasestatus(x + 1, y - 1, map, false);
            changecasestatus(x, y + 1, map, false);
            changecasestatus(x, y - 1, map, false);
            changecasestatus(x - 1, y + 1, map, false);
            changecasestatus(x - 1, y - 1, map, false);
            changecasestatus(x - 1, y, map, false);
        }
    }
}

void Level::start(sf::RenderWindow &window, int level)
{
    std::cout << level << "jjjj";
    std::fstream data_file;
    data_file.open("data", std::ios::in);
    int current_line = 0;
    std::string line;
    while (!data_file.eof())
    {
        current_line++;
        std::getline(data_file, line);
        if (current_line == level)
        {
            break;
        }
    }
    char map_data[BLOCK_NUMBER_X][BLOCK_NUMBER_Y];
    loadmapdatafromstring(line, map_data);

    while (window.isOpen())
    {
        sf::Vector2i mouseposition;
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    changecasestatus(event.mouseButton.x / BLOCK_SIZE, event.mouseButton.y / BLOCK_SIZE, map_data, true);
                }
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color(100, 100, 100));
        for (int i = 0; i < BLOCK_NUMBER_X; i++)
        {
            for (int j = 0; j < BLOCK_NUMBER_Y; j++)
            {

                sf::RectangleShape rectangle(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                rectangle.setPosition(BLOCK_SIZE * i, BLOCK_SIZE * j);
                sf::Color a(50, 50, 50);
                mouseposition = sf::Mouse::getPosition(window);
                if (map_data[i][j] == '1')
                {
                    a = sf::Color(0, 0, 0);
                    if (i == mouseposition.x / BLOCK_SIZE && j == mouseposition.y / BLOCK_SIZE)
                        a = sf::Color(30, 30, 30);
                }

                else if (map_data[i][j] == '2')
                {
                    a = sf::Color(255, 255, 255);
                    if (i == mouseposition.x / BLOCK_SIZE && j == mouseposition.y / BLOCK_SIZE)
                        a = sf::Color(200, 200, 200);
                }

                rectangle.setFillColor(a);
                window.draw(rectangle);
                if (checkwin(map_data))
                    window.close();
            }
        }

        window.display();
    }
}

void Level::loadmapdatafromstring(std::string data, char map[BLOCK_NUMBER_X][BLOCK_NUMBER_Y])
{
    for (int i = 0; i < BLOCK_NUMBER_X * BLOCK_NUMBER_Y; i++)
    {
        map[i % BLOCK_NUMBER_X][i / BLOCK_NUMBER_X] = (i < data.size()) ? data[i] : '0';
    }
}