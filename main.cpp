#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstdlib>
#include <ctime>

struct card
{
    int suit;
    int value;
};


card deck[52];
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

card generateCard()
{
    card newCard;
    newCard.suit=rand()%4+1;
    newCard.value=rand()%13+1;
    return newCard;
}

bool cardExists(int cardNumber, card newCard)
{
    for(int i=0; i<cardNumber; i++)
        if(deck[i].suit==newCard.suit && deck[i].value==newCard.value)
            return false;
    return true;
}

void newDeck()
{
    srand(time(NULL));
    card newCard=generateCard();
    deck[0].value=newCard.value;
    deck[0].suit=newCard.suit;
    int cardNumber=1;
    while(cardNumber!=52)
    {
        newCard=generateCard();
        while(!cardExists(cardNumber, newCard))
            newCard=generateCard();
        deck[cardNumber].value=newCard.value;
        deck[cardNumber].suit=newCard.suit;
        cardNumber++;

    }

}


void printDeck()
{
    for(int i=0; i<52; i++)
    {

        switch (deck[i].suit)
        {
        case 1:
            cout<<"inima ";
            break;
        case 2:
            cout<<"trifoi ";
            break;
        case 3:
            cout<<"romb ";
            break;
        case 4:
            cout<<"spada ";
            break;
        }
        switch (deck[i].value)
        {
        case 1:
            cout<<"as"<<endl;
            break;
        case 11:
            cout<<"jalet"<<endl;
            break;
        case 12:
            cout<<"dama"<<endl;
            break;
        case 13:
            cout<<"as"<<endl;
            break;
        default:
            cout<<deck[i].value<<endl;
            break;
        }

    }
}
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
    //openingScreen();
    newDeck();
    printDeck();
    return 0;
}


