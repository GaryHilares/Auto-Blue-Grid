#include <SFML/Window.hpp>

namespace HelperFunctions
{
    /**
     * wait
     * Makes the program sleep for the given amount of milliseconds.
     *
     * @param The amount of milliseconds as an int.
     *
     */
    void wait(int ms);
    /**
     * maximizeSFMLWindow
     * Maximizes a SFML window.
     *
     * @param The window to maximize as a reference to a sf::Window.
     *
     **/
    void maximizeSFMLWindow(sf::Window& window);
    /**
     * getScreensAmount
     * Returns the amount of visible monitors.
     *
     * @return The amount of visible monitors as an int.
     *
     **/
    int getScreensAmount();
    /**
     * saveScreenshot
     * Takes a screenshot of any screen and saves it to the given path.
     *
     * @param The path to save the screenshot as a wchar_t*.
     * @param The 0-indexed number of the screen to capture as an int.
     * @author Govind Parmar.
     * @note Extracted from https://stackoverflow.com/a/53421510.
     *       Includes minor modifications
     *
     **/
    void saveScreenshot(const wchar_t* wPath, int screenNum);
}
