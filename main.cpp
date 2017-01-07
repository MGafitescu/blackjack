#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string.h>


using namespace std;
struct card
{
    int suit;
    int value;
};

void openingScreen();
void mainMenu();
void scores();
void multiPlayer();
void singlePlayer();
void playHand(char usernameSingle[10]);
void playerHits(char usernameSingle[10]);
int sum(card deck[], int number);
bool blackjack(card deck[], int number);
bool checkBust(card deck[], int number);
int cardValue(card newCard);
void addDealerCard();
void addPlayerCard();
void addPlayer1Card();
void addPlayer2Card();
void updatePlayer();
bool update(char username[10], int currentAmount);
void newPlayer();
void printCards(card deck[], int number, bool hideCard, int y);
void printCard(card newCard,int x, int y);
void newDeck();
bool cardExists(int cardNumber, card newCard);
card generateCard();
void setConsoleSize();
void gotoXY(int x, int y);
void dealerHits();
void whoWins();
void anotherHand(char username[10]);
void betting();
void playerDoubles(char usernameSingle[10]);
void anotherHandMulti();
void multiPlayerHits(card deck[], int deckSize, int number);
void printMulti();
void checking();


card deck[52];
card playerHand[5], dealerHand[5], player1Hand[5], player2Hand[5];
int deckCounter=0;
int playerHandSize=0, player1HandSize=0, player2HandSize=0,dealerHandSize=0,playerSum=0, player1Sum, player2Sum, dealerSum=0;
int playerAmount=0,  bet=0;
char hit;
bool done=false;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
}

void setConsoleSize()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, 300, 20, 800, 600, TRUE);
}

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

void printCard(card newCard,int x,int y)
{
    char suit;
    switch (newCard.suit)
    {
    case 1:
        suit='C';
        break;
    case 2:
        suit='D';
        break;
    case 3:
        suit='H';
        break;
    case 4:
        suit='S';
        break;
    }

    switch (newCard.value)
    {
    case 1:
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |"<<suit<<"    | ";
        gotoXY(x,y+2);
        cout<<" |  A  | ";
        gotoXY(x,y+3);
        cout<<" |____"<<suit<<"| ";
        break;
    case 11:
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |"<<suit<<"    | ";
        gotoXY(x,y+2);
        cout<<" |  J  | ";
        gotoXY(x,y+3);
        cout<<" |____"<<suit<<"| ";
        break;
    case 12:
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |"<<suit<<"    | ";
        gotoXY(x,y+2);
        cout<<" |  Q  | ";
        gotoXY(x,y+3);
        cout<<" |____"<<suit<<"| ";
        break;
    case 13:
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |"<<suit<<"    | ";
        gotoXY(x,y+2);
        cout<<" |  K  | ";
        gotoXY(x,y+3);
        cout<<" |____"<<suit<<"| ";
        break;
    case 10:
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |"<<suit<<"    | ";
        gotoXY(x,y+2);
        cout<<" |  10 | ";
        gotoXY(x,y+3);
        cout<<" |____"<<suit<<"| ";
        break;
    default:
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |"<<suit<<"    | ";
        gotoXY(x,y+2);
        cout<<" |  "<<newCard.value<<"  | ";
        gotoXY(x,y+3);
        cout<<" |____"<<suit<<"| ";
        break;
    }

}

void printCards(card deck[], int number, bool hideCard, int y)
{
    int x=0;
    if( hideCard)
    {
        gotoXY(x,y);
        cout<<"  _____  ";
        gotoXY(x,y+1);
        cout<<" |*    | ";
        gotoXY(x,y+2);
        cout<<" |  *  | ";
        gotoXY(x,y+3);
        cout<<" |____*| ";
    }
    else
        printCard(deck[0],x,y);
    for(int i=1; i<number; i++)
    {
        x=x+10;
        printCard(deck[i],x,y);

    }
}



void newPlayer()
{
    system("CLS");
    fstream fileOut("f.txt", ios::app);
    fstream fileIn("f.txt", ios::in);
    char username[10], usernameFile[10];
    int initialAmount=100;
    int amount;
    cout<<"Inregistrare jucator";
    cout<<endl<<"Tasteaza numele jucatorului: ";
    cin>>username;
    bool ok=true;
    while(!fileIn.eof())
    {
        fileIn>>usernameFile>>amount;
        if(strcmp(username,usernameFile)==0)
        {
            cout<<"Jucatorul este deja inregistrat";
            ok=false;
        }

    }
    if(ok==true)
    {
        fileOut<<username<<"  "<<initialAmount<<endl;
        cout<<"Jucatorul a fost inregistrat cu succes cu suma de   "<<initialAmount;
    }
    fileIn.close();
    fileOut.close();
    cout<<endl<<"Apasati M pentru a reveni la meniul principal";
    char key;
    key=_getch();
    mainMenu();

}

bool update(char username[10], int currentAmount)
{
    char usernameFile[10];
    int  amountFile;
    fstream fileIn("f.txt", ios::in);
    fstream auxFileIn("faux.txt", ios::in);
    fstream auxFileOut("faux.txt", ios::out);
    bool ok=false;
    fileIn>>usernameFile>>amountFile;
    while(!fileIn.eof())
    {
        if(strcmp(usernameFile,username)==0)
        {
            auxFileOut<<username<<"  "<<currentAmount<<endl;
            ok=true;
        }
        else
            auxFileOut<<usernameFile<<"  "<<amountFile<<endl;
        fileIn>>usernameFile>>amountFile;
    }

    fstream fileOut("f.txt", ios::out);
    auxFileIn>>usernameFile>>amountFile;
    while(!auxFileIn.eof())
    {
        fileOut<<usernameFile<<"   "<<amountFile<<endl;
        auxFileIn>>usernameFile>>amountFile;
    }
    return ok;
}

void updatePlayer()
{
    system("CLS");
    char username[10];
    int amount;
    cout<<"Tastati numele jucatorului pentru care se va face update"<<endl;
    cin>>username;
    cout<<"Tastati noua suma"<<endl;
    cin>>amount;
    if(update(username,amount))
        cout<<"Update facut cu succes";
    else cout<<"Jucatorul nu este inregistrat";
    cout<<endl<<"Apasati M pentru a reveni la meniul principal";
    char key;
    key=_getch();
    if(key=='m' || key=='M')
        mainMenu();
    else
        cout<<endl<<"Ati tastat gresit";
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

void addPlayer1Card()
{
    if(deckCounter==52)
    {
        newDeck();
        deckCounter=0;
    }
    else
    {
        player1Hand[player1HandSize]=deck[deckCounter];
        deckCounter++;
        player1HandSize++;
    }
}
void addPlayer2Card()
{
    if(deckCounter==52)
    {
        newDeck();
        deckCounter=0;
    }
    else
    {
        player2Hand[player2HandSize]=deck[deckCounter];
        deckCounter++;
        player2HandSize++;
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
    if(sum(deck,number)>21)
        return true;
    return false;
}

bool blackjack(card deck[], int number)
{
    int sum=0;
    for(int i=0; i<number; i++)
        sum=sum+cardValue(deck[i]);
    if(sum==21)
        return true;
    return false;

}

int sum(card deck[], int number)
{
    int sum=0;
    for(int i=0; i<number; i++)
        sum=sum+cardValue(deck[i]);
    return sum;
}

void playerHits(char usernameSingle[10])
{
    system("CLS");
    addPlayerCard();
    cout<<"Suma disponibila: "<<playerAmount<<"   "<<"Suma pariata: "<<bet<<endl<<endl;
    cout<<"Cartile tale : ";
    printCards(playerHand,playerHandSize, false,3);
    playerSum=sum(playerHand,playerHandSize);
    cout<<"  Suma cartilor tale: "<<playerSum<<endl<<endl;
    cout<<"Cartile dealerului: ";
    printCards(dealerHand,dealerHandSize, false, 9);
    if(checkBust(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Ai pierdut!";
        hit='n';
        anotherHand(usernameSingle);
    }
    else if(blackjack(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Blackjack! Ai castigat!";
        playerAmount=playerAmount+2*bet;
    }
    else
    {
        cout<<endl<<endl<<"Apasa H pentru Hit si S pentru Stand";
        hit=_getch();
    }
}

void dealerHits()
{
    addDealerCard();
    system("cls");
    cout<<"Suma disponibila: "<<playerAmount<<"   "<<"Suma pariata: "<<bet<<endl<<endl;
    cout<<"Cartile tale : ";
    printCards(playerHand,playerHandSize, false,3);
    playerSum=sum(playerHand,playerHandSize);
    cout<<"  Suma cartilor tale: "<<playerSum<<endl<<endl;
    cout<<"Cartile dealerului: ";
    printCards(dealerHand,dealerHandSize, false, 9);
    dealerSum=sum(dealerHand,dealerHandSize);
    Sleep(500);
}

void whoWins()
{
    if(checkBust(dealerHand,dealerHandSize))
    {
        cout<<endl<<endl<<"Ai castigat";
        playerAmount=playerAmount+2*bet;
    }
    else if(dealerSum<playerSum&&!checkBust(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Ai castigat!";
        playerAmount=playerAmount+2*bet;
    }
    else if(dealerSum==playerSum)
    {
        cout<<endl<<endl<<"Egalitate!";
        playerAmount=playerAmount+bet;
    }
    else
        cout<<endl<<endl<<"Ai pierdut!";

}

void anotherHand(char username[10])
{
    update(username, playerAmount);
    cout<<endl<<endl<<"Joci inca un joc? (D/N)";
    char anotherHand=_getch();
    if(anotherHand=='D' || anotherHand=='d')
        playHand(username);
    else
        mainMenu();
}

void betting()
{
    system("CLS");
    if(playerAmount==0)
    {
        cout<<"Suma disponibila prea mica";
        cout<<endl<<"Apasa orice tasta pentru a reveni la meniu";
        char key=_getch();
        mainMenu();
    }
    else
    {
        cout<<"Suma disponibila: "<<playerAmount;
        cout<<endl<<"Cat vrei sa pariezi? ";
        cin>>bet;
        if(bet>playerAmount)
            betting();
        else
            playerAmount=playerAmount-bet;
    }
}

void playerDoubles(char usernameSingle[10])
{
    system("CLS");
    addPlayerCard();
    playerAmount=playerAmount-bet;
    bet=bet*2;
    cout<<"Suma disponibila: "<<playerAmount<<"   "<<"Suma pariata: "<<bet<<endl<<endl;
    cout<<"Cartile tale : ";
    printCards(playerHand,playerHandSize, false,3);
    playerSum=sum(playerHand,playerHandSize);
    cout<<"  Suma cartilor tale: "<<playerSum<<endl<<endl;
    cout<<"Cartile dealerului: ";
    printCards(dealerHand,dealerHandSize, false, 9);
    if(checkBust(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Ai pierdut!";
        hit='n';
        anotherHand(usernameSingle);
    }
    else if(blackjack(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Blackjack! Ai castigat!";
        playerAmount=playerAmount+2*bet;
    }
}

void playHand(char usernameSingle[10])
{
    newDeck();
    playerHandSize=0;
    dealerHandSize=0;
    playerSum=0;
    dealerSum=0;
    betting();
    system("CLS");
    addPlayerCard();
    addPlayerCard();
    addDealerCard();
    addDealerCard();
    cout<<"Suma disponibila: "<<playerAmount<<"   "<<"Suma pariata: "<<bet<<endl<<endl;
    cout<<"Cartile tale : ";
    printCards(playerHand,playerHandSize, false,3);
    playerSum=sum(playerHand,playerHandSize);
    cout<<"  Suma cartilor tale: "<<playerSum<<endl<<endl;
    cout<<"Cartile dealerului: ";
    printCards(dealerHand,dealerHandSize, false, 9);
    dealerSum=sum(dealerHand,dealerHandSize);
    if(blackjack(playerHand, playerHandSize))
    {
        cout<<endl<<endl<<"Blackjack!Ai castigat!";
        playerAmount=playerAmount+2.5*bet;
        anotherHand(usernameSingle);
    }
    if(blackjack(dealerHand,dealerHandSize))
    {
        cout<<endl<<endl<<"Blackjack la dealer!Ai pierdut!";
        anotherHand(usernameSingle);
    }
    cout<<endl<<endl<<"Apasa H pentru Hit,  S pentru Stand si D pentru Double";
    hit=_getch();

    if(hit=='D'|| hit=='d')
        playerDoubles(usernameSingle);
    while((hit=='h'||hit=='H')&&playerHandSize!=5)
    {
        playerHits(usernameSingle);
    }

    while(dealerSum<17&&dealerHandSize!=5)
    {
        dealerHits();
    }
    system("cls");
    cout<<"Suma disponibila: "<<playerAmount<<"   "<<"Suma pariata: "<<bet<<endl<<endl;
    cout<<"Cartile tale : ";
    printCards(playerHand,playerHandSize, false,3);
    playerSum=sum(playerHand,playerHandSize);
    cout<<"  Suma cartilor tale: "<<playerSum<<endl<<endl;
    cout<<"Cartile dealerului: ";
    printCards(dealerHand,dealerHandSize, false, 9);
    dealerSum=sum(dealerHand,dealerHandSize);
    cout<<"Suma cartilor dealerului: "<<dealerSum;
    whoWins();
    anotherHand(usernameSingle);
}

void singlePlayer()
{
    system("cls");
    fstream fileIn("f.txt", ios::in);
    char usernameSingle[10],usernameFile[10];
    int amount;
    bool ok=false;
    cout<<"Tasteaza numele :";
    cin>>usernameSingle;
    while(!fileIn.eof()&&ok==0)
    {
        fileIn>>usernameFile>>amount;
        if(strcmp(usernameSingle,usernameFile)==0)
        {
            playerAmount=amount;
            cout<<endl<<"Suma disponibila este: "<<playerAmount;
            ok=true;
        }
    }
    if(ok==false)
    {
        cout<<endl<<"Jucatorul nu este inregistrat.Doriti inregistrarea?(D/N)";
        char registration=_getch();
        if(registration=='D'||registration=='d')
            newPlayer();
        else
            mainMenu();
    }
    else if(ok==true && playerAmount==0)
    {
        cout<<"Suma disponibila este prea mica.";
        mainMenu();
    }
    else
        playHand(usernameSingle);
}

void printMulti()
{
    cout<<"Cartile jucatorului 1: "<<endl;
    printCards(player1Hand, player1HandSize, false,2);
    player1Sum=sum(player1Hand,player1HandSize);
    cout<<" Suma cartilor jucatorului 1: "<<player1Sum<<endl<<endl;
    cout<<"Cartile jucatorului 2: "<<endl;
    printCards(player2Hand, player2HandSize, false, 8);
    player2Sum=sum(player2Hand,player2HandSize);
    cout<<" Suma cartilor jucatorului 2: "<<player2Sum<<endl;
}
void anotherHandMulti()
{
    cout<<endl<<endl<<"Jucati inca un joc? (D/N)";
    char anotherHand=_getch();
    if(anotherHand=='D' || anotherHand=='d')
        multiPlayer();
    else
        mainMenu();
}

void multiPlayerHits(card deck[], int deckSize, int number)
{
    if(number==1)
        addPlayer1Card();
    else
        addPlayer2Card();
    printMulti();

}

void checking()
{
    system("cls");
    printMulti();
    if(checkBust(player1Hand,player1HandSize))
    {
        cout<<endl<<endl<<"Jucatorul 1 a pierdut!";
        done=true;
        anotherHandMulti();
    }
    if(checkBust(player2Hand,player2HandSize))
    {
        cout<<endl<<endl<<"Jucatorul 2 a pierdut!";
        done=true;
        anotherHandMulti();
    }
    if(blackjack(player1Hand,player1HandSize))
    {
        cout<<endl<<endl<<"Blackjack! Jucatorul 1 a castigat!";
        done=true;
        anotherHandMulti();
    }
    if(blackjack(player2Hand,player2HandSize))
    {
        cout<<endl<<endl<<"Blackjack! Jucatorul 2 a castigat!";
        done=true;
        anotherHandMulti();
    }
}

void multiPlayer()
{
    newDeck();
    system("cls");
    player1Sum=0;
    player1HandSize=0;
    player2Sum=0;
    player2HandSize=0;
    addPlayer1Card();
    addPlayer1Card();
    addPlayer2Card();
    addPlayer2Card();
    printMulti();
    if(blackjack(player1Hand,player1HandSize))
    {
        cout<<endl<<"Jucatorul 1 castiga";
        anotherHandMulti();
    }
    if(blackjack(player2Hand,player2HandSize))
    {
        cout<<endl<<"Jucatorul 2 castiga";
        anotherHandMulti();
    }
    done=false;
    while(done==false)
    {
        system("cls");
        printMulti();
        cout<<endl<<"Apasa H pentru Hit, S pentru Stand si D pentru Double";
        char player1Option=_getch();
        if(player1Option=='H' || player1Option=='h')
            multiPlayerHits(player1Hand,player1HandSize,1);
        checking();
        system("cls");
        printMulti();
        cout<<endl<<"Este randul jucatorului 2";
        cout<<endl<<"Apasa H pentru Hit, S pentru Stand si D pentru Double";
        char player2Option=_getch();
        if(player2Option=='H' || player2Option=='h')
            multiPlayerHits(player2Hand,player2HandSize,2);
        checking();
        if((player1Option=='s'||player1Option=='S')&&(player2Option=='s'||player2Option=='S'))
            done=true;
    }
    anotherHandMulti();

}


void scores()
{
    system("CLS");
    fstream fileIn("f.txt", ios::in);
    cout<<"Tasteaza numele utilizatorului sau ''toti'' pentru a vedea toti utilizatorii: "<<endl;
    char username[10];
    char usernameFile[10];
    int amount;
    int ok=0;
    cin>>username;
    cout<<endl;
    char check=fileIn.peek();
    if(check==EOF)
        cout<<"Nu exista utilizatori.";
    else
    {


        if(strcmp(username,"toti")==0)
        {

            fileIn>>usernameFile>>amount;
            while(!fileIn.eof()&&ok==0)
            {
                cout<<"User: "<<usernameFile<<"  Suma: "<<amount<<endl;
                fileIn>>usernameFile>>amount;
            }

        }
        else
        {

            while(!fileIn.eof()&&ok==0)
            {
                fileIn>>usernameFile>>amount;
                if(strcmp(username,usernameFile)==0)
                {
                    cout<<"User: "<<username<<"  Suma: "<<amount<<endl;
                    ok=1;
                }
            }
            if(ok==0)
                cout<<endl<<"Jucatorul nu este inregistrat";
        }
    }
    cout<<endl<<"Apasati M pentru a reveni la meniul principal";
    char key;
    key=_getch();
    if(key=='m' || key=='M')
        mainMenu();

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
    gotoXY(20,12);
    cout<<"Alegeti o optiune, tastand cifra corespunzatoare sau E pentru Exit";
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
    case 'E':
    case 'e':
        system("cls");
        gotoXY(40,5);
        cout<<"La revedere!";
        gotoXY(0,12);
        cout<<endl;
        break;
    default:
        mainMenu();
    }
}

void openingScreen()
{
    string title="Blackjack";
    gotoXY(40,5);
    cout<<title<<endl;
    gotoXY(33,10);
    cout<<"Apasa C pentru a continua...";
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


