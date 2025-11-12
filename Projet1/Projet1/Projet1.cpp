#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "File.h"

class Settings
{
private:
    HANDLE hConsole;
    DWORD mode;
    
    std::vector<char> _pixels;
    
    int _height = 20;
    int _width = 100;
public:

    Settings(int argc, char* argv[])
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        mode = DWORD();

        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
            if (arg == "-h" && i+1 < argc)
            {
                _height = std::atoi(argv[i+1]);
                i++;
            }
            else if (arg == "-w" && i+1 < argc)
            {
                _width = std::atoi(argv[i+1]);
                i++;
            }
        }
    }

    void HideCursor()
    {
        std::cout << "\033[?25l";
    }

    void ShowCursor()
    {
        std::cout << "\033[?25h";
    }
    
    void ResetCursortPosition()
    {
        std::cout << "\033[H";
    }
    
    void Clear()
    {
        std::cout << "\033[2J";
    }
    
    void CreateScreen()
    {
        for (int y = 0; y < _height; y++)
        {
            for (int x = 0; x < _width; x++)
            {
                _pixels.push_back('.');
            }
            _pixels.push_back('\n');
        }
    }
    
    void Draw()
    {
        Clear();
        ResetCursortPosition();
        HideCursor();
        
        for (char pixel : _pixels)
        {
            std::cout << pixel;
        }
        
        ShowCursor();
    }

    void SetHeight(int n)
    {
        _height = n;
    }
    
    void SetWidth(int n)
    {
        _width = n;
    }
    
    int GetHeight() const
    {
        return _height;
    }
    
    int GetWidth() const
    {
        return _width;
    }

    std::vector<char> GetPixels()
    {
        return _pixels;
    }
};

int main(int argc, char* argv[])
{
    Settings settings(argc,argv);
    
    settings.CreateScreen();
    settings.Draw();
    
    return 0;
}
