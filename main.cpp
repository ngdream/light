#include <SFML/Graphics.hpp>
#include "level.h"

class Button
{
    sf::Texture *m_image;
    sf::Sprite *m_sprite;

public:
    Button(std::string path)
    {
        m_image = new sf::Texture;
        m_sprite = new sf::Sprite;
        m_image->loadFromFile(path);
        m_sprite->setTexture(*m_image);
    }

    sf::Sprite *getSprite()
    {

        return m_sprite;
    }
    ~Button()
    {
    }
};

void showmainmenu();

int getlevelnumber()
{
    int number_of_lines = 0;
    std::string line;
    std::ifstream data_file("data");

    while (std::getline(data_file, line))
        ++number_of_lines;
    data_file.close();
    return number_of_lines;
}
void showlevelmenu(sf::RenderWindow &window)
{
    std::vector<Button> level_buttons;
    int level_number = getlevelnumber();
    for (int i = 0; i < level_number; i++)
    {
        level_buttons.push_back(Button("assets/level_ctn.png"));
    }

    window.clear();
    int i = 0;
    for (Button &button : level_buttons)
    {
        button.getSprite()->setPosition(sf::Vector2f{float(186 + (i % 6) * 100), float(120 + (i / 6) * 100)});
        window.draw(*button.getSprite());
        i++;
    }

    window.display();
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f mouseposition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                std::cout << mouseposition.x << " " << mouseposition.y << std::endl;
                int i = 1;
                for (Button &button : level_buttons)
                {
                    if (button.getSprite()->getGlobalBounds().contains(mouseposition))
                    {
                        Level::start(window, i);

                        std::cout << i << std::endl;
                    }

                    i++;
                }

                if (level_buttons[3].getSprite()->getGlobalBounds().contains(mouseposition))
                    Level::start(window, 4);
            }
        }
    }
}

void showmainmenu(sf::RenderWindow &window)
{
    Button button[] = {Button("assets/play.png"), Button("assets/credit.png"), Button("assets/quit.png")};
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f mouseposition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (button[0].getSprite()->getGlobalBounds().contains(mouseposition))
                {
                    showlevelmenu(window);
                }
            }

            window.clear();
            for (int i = 0; i < 3; i++)
            {
                button[i].getSprite()->setPosition(sf::Vector2f(sf::Vector2i{256, 120 + i * 200}));
                window.draw(*button[i].getSprite());
            }

            window.display();
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "light");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        showmainmenu(window);

        window.display();
    }

    return 0;
}