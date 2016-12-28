#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;


struct card
{
    int suit;
    int value;
};

card deck[52];
card playerHand[5], dealerHand[5];
int deckCounter=0;
int playerHandSize=0,dealerHandSize=0,playerSum=0,dealerSum=0;

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
    for(int i=0; i<=cardNumber; i++)
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
            cout<<"C ";
            break;
        case 2:
            cout<<"D ";
            break;
        case 3:
            cout<<"H ";
            break;
        case 4:
            cout<<"S ";
            break;
        }
        switch (deck[i].value)
        {
        case 1:
            cout<<"A"<<endl;
            break;
        case 11:
            cout<<"J"<<endl;
            break;
        case 12:
            cout<<"Q"<<endl;
            break;
        case 13:
            cout <<"K"<<endl;
            break;
        default:
            cout<<deck[i].value<<endl;
            break;
        }

    }
}

void printCard(card newCard)
{
    switch (newCard.value)
    {
    case 1:
        cout<<"A";
        break;
    case 11:
        cout<<"J";
        break;
    case 12:
        cout<<"Q";
        break;
    case 13:
        cout <<"K";
        break;
    default:
        cout<<newCard.value;
        break;
    }
    switch (newCard.suit)
    {
    case 1:
        cout<<"C";
        break;
    case 2:
        cout<<"D";
        break;
    case 3:
        cout<<"H";
        break;
    case 4:
        cout<<"S";
        break;
    }
}

void printCards(card deck[], int number, bool hideCard)
{
    if( hideCard)
    {
        cout<<" **";
    }
    else
        printCard(deck[0]);
    cout<<"   ";
    for(int i=1; i<number; i++)
    {
        printCard(deck[i]);
        cout<<"   ";
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

void addPlayerCard()
{
    if(deckCounter==52)
    {
        newDeck();
        deckCounter=0;
    }
    else
    {
        playerHand[playerHandSize]=deck[deckCounter];
        deckCounter++;
        playerHandSize++;
    }
}

void addDealerCard()
{
    if(deckCounter==52)
    {
        newDeck();
        deckCounter=0;
    }
    else
    {
        dealerHand[dealerHandSize]=deck[deckCounter];
        deckCounter++;
        dealerHandSize++;
    }
}

int cardValue(card newCard)
{
    int cardVal;
    switch(newCard.value)
    {
    case 11:
        cardVal=10;
        break;
    case 12:
        cardVal=10;
        break;
    case 13:
        cardVal=10;
        break;
    default:
        cardVal=newCard.value;
        break;
    }
    return cardVal;
}

bool checkBust(card deck[], int number)
{
    int sum=0;
    for(int i=0; i<number; i++)
        sum=sum+cardValue(deck[i]);
    if(sum>21)
        return true;
    return false;

}

void playHand()
{
    system("CLS");
    newDeck();
    playerHandSize=0;
    dealerHandSize=0;
    playerSum=0;
    dealerSum=0;
    system("CLS");
    addPlayerCard();
    addPlayerCard();
    cout<<"Your hand : ";
    printCards(playerHand,playerHandSize, false);
    for(int i=0; i<playerHandSize; i++)
        playerSum=playerSum+cardValue(playerHand[i]);
    cout<<"  Your sum: "<<playerSum<<endl;
    addDealerCard();
    addDealerCard();
    cout<<"Dealer hand : ";
    printCards(dealerHand,dealerHandSize, true);
    for(int i=0; i<dealerHandSize; i++)
        dealerSum=dealerSum+cardValue(dealerHand[i]);
    cout<<endl<<"Press H to hit and S to stand";
    char hit;
    hit=_getch();

    while((hit=='h'||hit=='H')&&playerHandSize!=5)
    {
        system("CLS");
        addPlayerCard();
        playerSum=0;
        cout<<"Your hand : ";
        printCards(playerHand,playerHandSize, false);
        for(int i=0; i<playerHandSize; i++)
            playerSum=playerSum+cardValue(playerHand[i]);
        cout<<"  Your sum: "<<playerSum<<endl;
        cout<<"Dealer hand : ";
        printCards(dealerHand,dealerHandSize, true);
        if(checkBust(playerHand,playerHandSize))
        {
            cout<<endl<<"You lost!";
            hit='n';
            cout<<endl<<"Play another hand? (Y/N)";
            char anotherHand=_getch();
            if(anotherHand=='y' || anotherHand=='Y')
                playHand();

        }
        else if(playerSum==21)
            cout<<endl<<"Blackjack! You win!";
        else
        {
            cout<<endl<<"Press H to hit and S to stand";
            hit=_getch();
        }
    }
    while(dealerSum<17&&dealerHandSize!=5)
    {
        addDealerCard();
        dealerSum=0;
        playerSum=0;
        system("cls");
        cout<<"Your hand : ";
        printCards(playerHand,playerHandSize, false);
        for(int i=0; i<playerHandSize; i++)
            playerSum=playerSum+cardValue(playerHand[i]);
        cout<<"  Your sum: "<<playerSum<<endl;
        cout<<"Dealer hand : ";
        printCards(dealerHand,dealerHandSize, false);
        for(int i=0; i<dealerHandSize; i++)
            dealerSum=dealerSum+cardValue(dealerHand[i]);
    }
    system("cls");
    cout<<"Your hand : ";
    printCards(playerHand,playerHandSize, false);
    cout<<"  Your sum: "<<playerSum<<endl;
    cout<<"Dealer hand : ";
    printCards(dealerHand,dealerHandSize, false);
    cout<<"Dealer sum: "<<dealerSum<<endl;
    if(checkBust(dealerHand,dealerHandSize))
        cout<<endl<<"You win";
    else if(dealerSum<playerSum)
        cout<<endl<<"You win!";
    else
        if(dealerSum==playerSum)
        cout<<endl<<"It's a tie!";
     else
        cout<<endl<<"You lost!";
    cout<<endl<<"Play another hand? (Y/N)";
    char anotherHand=_getch();
    if(anotherHand=='y' || anotherHand=='Y')
        playHand();
}

void singlePlayer()
{
    playHand();
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


