#include <windows.h>

namespace HelperFunctions
{
    /**
     * saveScreenshot
     * Takes a screenshot and saves it to the given path.
     *
     * @param A path to save the screenshot as a WCHAR*.
     * @author Govind Parmar.
     * @note Extracted from https://stackoverflow.com/a/53421510.
     *       Includes minor modifications
     *
     **/
    void saveScreenshot(const WCHAR *wPath);
}
