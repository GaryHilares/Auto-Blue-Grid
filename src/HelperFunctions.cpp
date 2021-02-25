#include "../include/HelperFunctions.hpp"
#ifdef WIN32
#include <windows.h>
#include <stdexcept>

namespace HelperFunctions
{
    void wait(int ms)
    {
        Sleep(ms);
    }
    void maximizeSFMLWindow(sf::Window& window)
    {
        ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
    }
    int getScreensAmount()
    {
        return GetSystemMetrics(SM_CMONITORS);
    }
    void saveScreenshot(const wchar_t* wPath, int screenNum)
    {
        int screensAmount = getScreensAmount();
        if(screenNum >= screensAmount)
            throw std::out_of_range("Screen number is out of valid screens range");
        BITMAPFILEHEADER bfHeader;
        BITMAPINFOHEADER biHeader;
        BITMAPINFO bInfo;
        HGDIOBJ hTempBitmap;
        HBITMAP hBitmap;
        BITMAP bAllDesktops;
        HDC hDC, hMemDC;
        LONG lWidth, lHeight;
        BYTE *bBits = NULL;
        DWORD cbBits, dwWritten = 0;
        HANDLE hFile;
        INT x = GetSystemMetrics(SM_XVIRTUALSCREEN);
        INT y = GetSystemMetrics(SM_YVIRTUALSCREEN);

        ZeroMemory(&bfHeader, sizeof(BITMAPFILEHEADER));
        ZeroMemory(&biHeader, sizeof(BITMAPINFOHEADER));
        ZeroMemory(&bInfo, sizeof(BITMAPINFO));
        ZeroMemory(&bAllDesktops, sizeof(BITMAP));

        hDC = GetDC(NULL);
        hTempBitmap = GetCurrentObject(hDC, OBJ_BITMAP);
        GetObjectW(hTempBitmap, sizeof(BITMAP), &bAllDesktops);

        lWidth = bAllDesktops.bmWidth/screensAmount;
        lHeight = bAllDesktops.bmHeight;
        x += lWidth * screenNum;

        DeleteObject(hTempBitmap);

        bfHeader.bfType = (WORD)('B' | ('M' << 8));
        bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        biHeader.biSize = sizeof(BITMAPINFOHEADER);
        biHeader.biBitCount = 24;
        biHeader.biCompression = BI_RGB;
        biHeader.biPlanes = 1;
        biHeader.biWidth = lWidth;
        biHeader.biHeight = lHeight;

        bInfo.bmiHeader = biHeader;

        cbBits = (((24 * lWidth + 31)&~31) / 8) * lHeight;

        hMemDC = CreateCompatibleDC(hDC);
        hBitmap = CreateDIBSection(hDC, &bInfo, DIB_RGB_COLORS, (VOID **)&bBits, NULL, 0);
        SelectObject(hMemDC, hBitmap);
        BitBlt(hMemDC, 0, 0, lWidth, lHeight, hDC, x, y, SRCCOPY);


        hFile = CreateFileW(wPath, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(hFile, &bfHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
        WriteFile(hFile, &biHeader, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
        WriteFile(hFile, bBits, cbBits, &dwWritten, NULL);

        CloseHandle(hFile);

        DeleteDC(hMemDC);
        ReleaseDC(NULL, hDC);
        DeleteObject(hBitmap);
    }
}
#endif //WIN32
