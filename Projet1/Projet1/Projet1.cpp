#include <iostream>
#include <Windows.h>
#include <vector>

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


    void Draw()
    {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                std::cout << '.';
            }
            std::cout << '\n';
        }
    }
};

int main(int argc, char* argv[])
{
    std::vector<char> pixels;
    
    Console console;
    console.HideCursor();

    console.Clear();
    console.ResetCursortPosition();
    
    console.Draw();
    
    console.ShowCursor();
    std::cin.get();
    return 0;
}
