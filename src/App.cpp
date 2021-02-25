#include "../include/App.hpp"
#include "../include/HelperFunctions.hpp"
#include <exception>
#include <SFML/Graphics.hpp>

const std::pair<int,int> App::windowSize = {sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height};

void App::run()
{
    this->waitForKeyPress();
}

void App::waitForKeyPress()
{
    while(true)
    {
        bool doDisplay = true;
        for(sf::Keyboard::Key key: combination)
            if(!sf::Keyboard::isKeyPressed(key))
                doDisplay = false;
        if(doDisplay)
            this->display();
    }
}

void App::display()
{
    wchar_t filenameAsWCharPtr[] = L"tmp.bmp";
    HelperFunctions::saveScreenshot(filenameAsWCharPtr);

    sf::RenderWindow window(sf::VideoMode(windowSize.first,windowSize.second),"Screenshot");
    ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    sf::Image icon;
    if(!icon.loadFromFile("icon.png"))
        throw std::exception();
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
    sf::Texture texture;
    if(!texture.loadFromFile("tmp.bmp"))
        throw std::exception();
    sf::Sprite screenshot(texture);
    screenshot.setScale(float(window.getSize().x)/screenshot.getLocalBounds().width,float(window.getSize().y)/screenshot.getLocalBounds().height);
    window.requestFocus();
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(screenshot);
        sf::RectangleShape line;
        line.setPosition(from.first,from.second);
        line.setFillColor(sf::Color(lineColor[0],lineColor[1],lineColor[2]));
        line.setSize({thickness,to.second-from.second});
        for(int x = from.first; x <= to.first; x += dimensions.first)
        {
            window.draw(line);
            line.move(dimensions.first,0);
        }
        line.setPosition(from.first,from.second);
        line.setSize({to.first-from.first,thickness});
        for(int y = from.second; y <= to.second; y += dimensions.second)
        {
            window.draw(line);
            line.move(0,dimensions.second);
        }
        window.display();
    }
    remove("tmp.bmp");
}
