#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "File.h"

class Console
{
private:
    HANDLE hConsole;
    DWORD mode;
    File file_;
    
    std::vector<char> _pixels;


    struct SETTINGS
    {
        int _height;
        int _width;
    };
    SETTINGS _settings;
public:
    
    Console()
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        mode = DWORD();

        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        _settings._height = 20;
        _settings._width = 100;
        
         if (file_.Open("./Setting.txt", FileMode::ReadWriteBinary) == false) // if file do not exist
         {
             file_.Open("./Setting.txt", FileMode::WriteReadBinary); // create a new file and write the default content
             UpdateSettings();
         };
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
        file_.Read(&_settings, sizeof(SETTINGS), 1);
        file_.Close();
        std::cout << _settings._height << '\n';
        std::cout << _settings._width << '\n';
        
        for (int y = 0; y < _settings._height; y++)
        {
            for (int x = 0; x < _settings._width; x++)
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
        _settings._height = n;
        UpdateSettings();
        file_.Close();
    }
    
    void SetWidth(int n)
    {
        _settings._width = n;
        UpdateSettings();
        file_.Close();
    }

    void UpdateSettings()
    {
        file_.Write(&_settings, sizeof(SETTINGS), 1);
    }
    
    int GetHeight() const
    {
        return _settings._height;
    }
    
    int GetWidth() const
    {
        return _settings._width;
    }

    std::vector<char> GetPixels()
    {
        return _pixels;
    }
};

int main(int argc, char* argv[])
{
    Console console;
    
    if ( argc == 1 )
    {
        console.CreateScreen();
        console.Draw();
        
        return 0;
    }
    
    std::string const& action = argv[1];
    if ( action == "-h" )
    {
        console.SetHeight(reinterpret_cast<int>(argv[2]));
        std::cout << "Height has been set !"; return 0;
    }
    if ( action == "-w" )
    {
        console.SetWidth(reinterpret_cast<int>(argv[2]));
        std::cout << "Width has been set !"; return 0;
    }
    
    return 0;
}
