#include <iostream>
#include <Windows.h>

class Console
{
public:
    HANDLE hConsole;
    DWORD mode;
    
    Console()
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        mode = DWORD();

        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
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
};

int main(int argc, char* argv[])
{
    std::cout << "Hello World!\n";
    Console console;
    console.ShowCursor();
    
    return 0;
}
