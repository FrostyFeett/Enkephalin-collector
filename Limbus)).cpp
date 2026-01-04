#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <thread>
#include <conio.h>
#include <vector>
#include <filesystem>

using namespace std;

class Point {
public:
    int X = 0;
    int Y = 0;
};

void ClickAt(int x, int y, bool left = true) {
    SetCursorPos(x, y);
    Sleep(200);

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = left ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    input.mi.dwFlags = left ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));

    Sleep(200);
}

void SafeSleep(int time) {
    int check = 100;
    while (time > 0) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 27) { // ESC
                cout << "Interrupt";
                exit(0);
            }
        }
        Sleep(check);
        time -= check;
    }
}

vector <wstring> PossiblePath = {
    L"C:\\Program Files (x86)\\Steam\\steamapps\\common\\Limbus Company\\LimbusCompany.exe",
    L"D:\\steam\\steamapps\\common\\Limbus Company\\LimbusCompany.exe",
    L"E:\\Steam\\steamapps\\common\\Limbus Company\\LimbusCompany.exe",
    L"F:\\steamapps\\common\\Limbus Company\\LimbusCompany.exe",
};

int main()
{
    SafeSleep(5000); // Выруби нахуй за 5 сек))
    wstring fileName = L"";
    for (auto& choose : PossiblePath) {
        if (filesystem::exists(choose)) {
            fileName = choose;
        }
    }

    if (fileName.empty()) {
        cout << "Unable to find path in file";
        exit(0);
    }

    HINSTANCE result = ShellExecute(
        NULL,
        L"open",
        fileName.c_str(),
        NULL,
        NULL,
        SW_SHOWNORMAL
    );

    if ((intptr_t)result <= 32) {
        wcout << L"Error" << endl;
    }

    int Login = 80; // Время (Сек.) до входа в игру
    int Wait = 130; // Время (Сек.) до перехода из меню в саму игру
    bool leftClick = true;

    Point LoginButton, EnkephalinButton, ChooseMax, Accept, Return, Options, Exit;

    LoginButton.X = 950; LoginButton.Y = 850;
    EnkephalinButton.X = 600; EnkephalinButton.Y = 980;
    ChooseMax.X = 1200; ChooseMax.Y = 490;
    Accept.X = 1125; Accept.Y = 800;
    Return.X = 800; Return.Y = 800;
    Options.X = 1800; Options.Y = 185;
    Exit.X = 980; Exit.Y = 700;

    SafeSleep(Login * 1000);

    ClickAt(LoginButton.X, LoginButton.Y);
    SafeSleep(Wait * 1000);

    ClickAt(EnkephalinButton.X, EnkephalinButton.Y);
    SafeSleep(10000);
    ClickAt(ChooseMax.X, ChooseMax.Y);
    ClickAt(Accept.X, Accept.Y);
    SafeSleep(10000);
    ClickAt(Return.X, Return.Y);
    SafeSleep(5000);
    ClickAt(Options.X, Options.Y);
    SafeSleep(5000);
    ClickAt(Exit.X, Exit.Y);

    cout << "Complete";
    return 0;
}