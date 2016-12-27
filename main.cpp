#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstdlib>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


void setConsoleSize()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, 300, 20, 800, 600, TRUE);
}

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
}

void newPlayer()
{
    system("CLS");
    cout<<"Subprogram inregistrare jucator";
}

void updatePlayer()
{
    system("CLS");
    cout<<"Subprogram update jucator";
}

void singlePlayer()
{
    system("CLS");
    cout<<"Subprogram joc cu calculatorul";
}
void multiPlayer()
{
    system("CLS");
    cout<<"Subprogram joc cu alt jucator";
}
void scores()
{
    system("CLS");
    cout<<"Subprogram consultat scorurile";
}
void mainMenu()
{
    system("CLS");
    gotoXY(43,5);
    cout<<"Meniu";
    gotoXY(37,6);
    cout<<"1.Inregistrare jucator";
    gotoXY(37,7);
    cout<<"2.Update jucator";
    gotoXY(37,8);
    cout<<"3.Singleplayer";
    gotoXY(37,9);
    cout<<"4.Multiplayer";
    gotoXY(37,10);
    cout<<"5.Consultare scor";
    gotoXY(25,12);
    cout<<"Alegeti o optiune, tastand cifra corespunzatoare";
    gotoXY(0,14);
    char key;
    key=_getch();
    switch (key)
    {
    case '1':
        newPlayer();
        break;
    case '2':
        updatePlayer();
        break;
    case '3':
        singlePlayer();
        break;
    case '4':
        multiPlayer();
        break;
    case '5':
        scores();
        break;
    default:
        cout<<"Ai tastat gresit.Te rugam reincearca";
        Sleep(1500);
        mainMenu();
    }
}

void openingScreen()
{
    string title="Blackjack";
    gotoXY(40,5);
    cout<<title<<endl;
    gotoXY(33,10);
    cout<<"Press C to continue...";
    char key;
    key=_getch();
    if(key=='C' || key=='c')
        mainMenu();
        else
            openingScreen();
}


int main()
{

    setConsoleSize();
    openingScreen();
    return 0;
}


