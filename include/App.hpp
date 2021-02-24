#include <SFML/Window/Keyboard.hpp>
#include <array>

/**
  * @class Auto_Blue_Grid
  *
  * @brief When "Ctrl + L" is pressed: Takes a screenshot and displays it
  *        in a new window with a blue grid over it.
  *
  * @author GProject Revolution.
  * @date Started: 23-02-2021.
  *       Finished: 24-02-2021.
  *
  **/
class App
{
    static constexpr std::array<sf::Keyboard::Key,2> combination = {sf::Keyboard::Key::LControl,sf::Keyboard::Key::L};
    static constexpr std::array<int,3> lineColor = {0,0,255};
    static constexpr std::pair<int,int> windowSize = {1600,900};
    static constexpr std::pair<int,int> from = {100,100};
    static constexpr std::pair<int,int> to = {1500,800};
    static constexpr std::pair<int,int> dimensions = {50,50};
    static constexpr int thickness = 1;
    static_assert(from.first < to.first,"Error: Invalid region (from.first >= to.first)");
    static_assert(from.second < to.second,"Error: Invalid region (from.second >= to.second)");
    /**
      * Waits until "Ctrl + L" is pressed, then calls "App::display()".
      *
      * @relatesalso App::display().
      *
      **/
    void waitForKeyPress();
    /**
      * Takes a screenshot and displays it in a new
      * window with a blue grid over it.
      *
      * @warning Overrides "/tmp.bmp" if exists.
      * @relatesalso HelperFunctions::SaveBitmap().
      *
      **/
    void display();
public:
    /**
      * Runs the app by calling "App::waitForKeyPress()".
      *
      * @relatesalso App::waitForKeyPress().
      *
      **/
    void run();
};
