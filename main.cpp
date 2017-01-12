#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <wincon.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string.h>
#include <math.h>


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
void playHand(char usernameSingle[11]);
void playerHits(char usernameSingle[11]);
int sum(card deck[], int number);
bool blackjack(card deck[], int number);
bool checkBust(card deck[], int number);
int cardValue(card newCard);
void addDealerCard();
void addPlayerCard();
void addPlayer1Card();
void addPlayer2Card();
void updatePlayer();
bool update(char username[11], unsigned  int currentAmount, int playerWins, int playerLosses, bool automatic);
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
void anotherHand(char username[11]);
void betting();
void playerDoubles(char usernameSingle[11]);
void anotherHandMulti();
void multiPlayerHits(card deck[], int deckSize, int number);
void printMulti();
void checking();
void whoWinsMulti();

card deck[52];
card playerHand[5], dealerHand[5], player1Hand[5], player2Hand[5];
int deckCounter=0;
int playerHandSize=0, player1HandSize=0, player2HandSize=0,dealerHandSize=0,playerSum=0, player1Sum, player2Sum, dealerSum=0;
unsigned int playerAmount=0, firstMove=0;
int bet=0, playerWins=0, playerLosses=0;
char hit;
bool player1Done=false,player2Done=false;
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
    MoveWindow(console, 300, 20,800, 600, TRUE);
    SetConsoleTitle( "Blackjack");
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
    char usernameRegister[11], usernameFile[11];
    unsigned int amount, wins, losses;
    cout<<"Inregistrare jucator";
    cin.clear();
    cout<<endl<<"Tasteaza numele jucatorului (10 caractere, continand doar litere ale alfabetului englez:)"<<endl;
    cin>>skipws>>usernameRegister;
    cin.clear();
    cin.ignore(10000,'\n');
    int letters=1;
    for(int i=0; i<strlen(usernameRegister); i++)
        if(char(usernameRegister[i])<65|| (char(usernameRegister[i])>90&&char(usernameRegister[i])<97) || char(usernameRegister[i])>122)
            letters=0;
    if(letters==0)
        newPlayer();
    else
    {
        usernameRegister[10]='\0';
        bool ok=true;
        unsigned int initialAmount=100;
        while(!fileIn.eof())
        {
            fileIn>>usernameFile>>amount>>wins>>losses;
            if(strcmp(usernameRegister,usernameFile)==0)
            {
                cout<<"Jucatorul este deja inregistrat";
                ok=false;
            }

        }
        if(ok==true)
        {
            fileOut<<usernameRegister<<"  "<<initialAmount<<"  "<<0<<"  "<<0<<endl;
            cout<<"Jucatorul a fost inregistrat cu succes cu suma de   "<<initialAmount;
            cout<<endl<<"Atentie: Daca ce ati tastat continea spatiu, tot ce urmeaza dupa primul spatiu a fost ignorat";
        }
    }
    fileIn.close();
    fileOut.close();
    cout<<endl<<endl<<"Apasati M pentru a reveni la meniul principal si N pentru a inregistra un nou jucator";
    char key;
    key=_getch();
    while(key!='m'&&key!='M'&&key!='n'&&key!='N')
        key=_getch();
    switch (key)
    {
    case 'M':
    case 'm':
        mainMenu();
        break;
    case 'n':
    case 'N':
        newPlayer();
        break;
    }

}

bool update(char username[11], unsigned  int currentAmount, int playerWins, int playerLosses, bool automatic)
{
    char usernameFile[11];
    unsigned int  amountFile, wins, losses;
    fstream fileIn("f.txt", ios::in);
    fstream auxFileOut("faux.txt", ios::out);
    bool ok=false;
    fileIn>>usernameFile>>amountFile>>wins>>losses;
    while(!fileIn.eof())
    {
        if(strcmp(usernameFile,username)==0)
        {
            if(automatic==true)
                auxFileOut<<username<<"  "<<currentAmount<<" "<<playerWins<<"  "<<playerLosses<<endl;
            else
                auxFileOut<<username<<"  "<<currentAmount<<" "<<wins<<"  "<<losses<<endl;
            ok=true;
        }
        else
            auxFileOut<<usernameFile<<"  "<<amountFile<<" "<<wins<<"  "<<losses<<endl;
        fileIn>>usernameFile>>amountFile>>wins>>losses;
    }
    auxFileOut<<EOF;
    fstream auxFileIn("faux.txt", ios::in);
    fstream fileOut("f.txt", ios::out);
    auxFileIn>>usernameFile>>amountFile>>wins>>losses;
    while(!auxFileIn.eof())
    {
        fileOut<<usernameFile<<"   "<<amountFile<<" "<<wins<<"  "<<losses<<endl;
        auxFileIn>>usernameFile>>amountFile>>wins>>losses;
    }
    return ok;
}

void updatePlayer()
{
    system("CLS");
    char username[11];
    int amount;
    cout<<"Tastati numele jucatorului pentru care se va face update"<<endl;
    cin>>skipws>>username;
    int letters=1;
    for(int i=0; i<strlen(username); i++)
        if(char(username[i])<65|| (char(username[i])>90&&char(username[i])<97) || char(username[i])>122)
            letters=0;
    if(letters==0)
        updatePlayer();
    else
    {
        cin.clear();
        cin.ignore(10000,'\n');
        cout<<"Tasteaza noua suma:"<<endl;
        cin>>amount;
        while(cin.fail()||amount<0||amount>32000)
        {
            cin.clear();
            cin.ignore(1000,'\n');
            system("cls");
            cout<<"Ai tastat gresit.Mai incearca."<<endl;
            cout<<endl<<"Tasteaza noua suma: ";
            cin>>amount;
        }
        cin.clear();
        cin.ignore(1000,'\n');
        if(update(username,amount,0,0,false))
            cout<<"Update facut cu succes";
        else
        {
            cout<<"Jucatorul nu este inregistrat";
            cout<<endl<<"Doriti inregistrarea?(D/N)";
            char registration=_getch();
            while(registration!='D'&&registration!='d'&&registration!='n'&&registration!='N')
                registration=_getch();
            if(registration=='D'||registration=='d')
                newPlayer();
            else if(registration=='N'||registration=='n')
                mainMenu();
        }
    }
    cout<<endl<<"Apasati M pentru a reveni la meniul principal si U pentru a face update la un nou jucator";
    char key;
    key=_getch();
    while(key!='m'&&key!='M'&&key!='u'&&key!='U')
        key=_getch();
    switch (key)
    {
    case 'M':
    case 'm':
        mainMenu();
    case 'u':
    case 'U':
        updatePlayer();
    }
}

void addPlayerCard()
{
    if(deckCounter==51)
    {
        newDeck();
        deckCounter=0;
    }

    playerHand[playerHandSize]=deck[deckCounter];
    deckCounter++;
    playerHandSize++;

}

void addPlayer1Card()
{
    if(deckCounter==51)
    {
        newDeck();
        deckCounter=0;
    }

    player1Hand[player1HandSize]=deck[deckCounter];
    deckCounter++;
    player1HandSize++;

}
void addPlayer2Card()
{
    if(deckCounter==51)
    {
        newDeck();
        deckCounter=0;
    }

    player2Hand[player2HandSize]=deck[deckCounter];
    deckCounter++;
    player2HandSize++;

}

void addDealerCard()
{
    if(deckCounter==51)
    {
        newDeck();
        deckCounter=0;
    }
    dealerHand[dealerHandSize]=deck[deckCounter];
    deckCounter++;
    dealerHandSize++;

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

    if(sum(deck,number)==21)
        return true;
    return false;

}

int sum(card deck[], int number)
{
    int sum=0;
    int ace=0;
    for(int i=0; i<number; i++)
    {
        sum=sum+cardValue(deck[i]);
        if(cardValue(deck[i])==1)
            ace=1;
    }
    if(sum+10<=21&&ace==1)
        sum=sum+10;

    return sum;
}

void playerHits(char usernameSingle[11])
{
    system("CLS");
    addPlayerCard();
    cout<<"Suma disponibila: "<<playerAmount<<"   "<<"Suma pariata: "<<bet<<endl<<endl;
    cout<<"Cartile tale : ";
    printCards(playerHand,playerHandSize, false,3);
    playerSum=sum(playerHand,playerHandSize);
    cout<<"  Suma cartilor tale: "<<playerSum<<endl<<endl;
    cout<<"Cartile dealerului: ";
    printCards(dealerHand,dealerHandSize, true, 9);
    if(checkBust(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Ai pierdut!";
        playerLosses++;
        hit='n';
        anotherHand(usernameSingle);
    }
    else if(blackjack(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Blackjack! Ai castigat!";
        playerAmount=playerAmount+2*bet;
        playerWins++;
    }
    else
    {
        cout<<endl<<endl<<"Apasa H pentru Hit si S pentru Stand";
        hit=_getch();
        while(hit!='h'&&hit!='H'&&hit!='s'&&hit!='S')
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
        playerWins++;
    }
    else if(dealerSum<playerSum&&!checkBust(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Ai castigat!";
        playerAmount=playerAmount+2*bet;
        playerWins++;
    }
    else if(dealerSum==playerSum)
    {
        cout<<endl<<endl<<"Egalitate!";
        playerAmount=playerAmount+bet;
    }
    else
    {
        cout<<endl<<endl<<"Ai pierdut!";
        playerLosses++;
    }

}

void anotherHand(char username[11])
{
    update(username, playerAmount, playerWins, playerLosses, true);
    cout<<endl<<endl<<"Joci inca un joc? (D/N)";
    char anotherHand=_getch();
    while(anotherHand!='d'&&anotherHand!='D'&&anotherHand!='n'&&anotherHand!='N')
        anotherHand=_getch();
    if(anotherHand=='D' || anotherHand=='d')
        playHand(username);
    else if(anotherHand=='n' || anotherHand=='N')
        mainMenu();
}

void betting()
{
    system("CLS");
    if(playerAmount==0)
    {
        cout<<"Suma disponibila prea mica";
        cout<<endl<<"Apasa M pentru a reveni la meniu sau U pentru a face update la suma ";
        char key=_getch();
        while(key!='m'&&key!='M'&&key!='u'&&key!='U')
            key=_getch();
        switch (key)
        {
        case 'm':
        case 'M':
            mainMenu();
            break;
        case 'u':
        case 'U':
            updatePlayer();
            break;
        }
    }
    else
    {
        cout<<"Suma disponibila: "<<playerAmount;
        cout<<endl<<"Cat vrei sa pariezi? ";
        cin>>bet;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            system("cls");
            cout<<"Suma disponibila: "<<playerAmount;
            cout<<endl<<"Cat vrei sa pariezi? ";
            cin>>bet;
        }

        if(bet>playerAmount)
            betting();
        else if(bet<=0)
            betting();
        else
            playerAmount=playerAmount-bet;
    }
    cin.clear();
    cin.ignore(1000,'\n');
}

void playerDoubles(char usernameSingle[11])
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
    printCards(dealerHand,dealerHandSize, true, 9);
    if(checkBust(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Ai pierdut!";
        anotherHand(usernameSingle);
    }
    else if(blackjack(playerHand,playerHandSize))
    {
        cout<<endl<<endl<<"Blackjack! Ai castigat!";
        playerAmount=playerAmount+2*bet;
        anotherHand(usernameSingle);
    }
}

void playHand(char usernameSingle[11])
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
    printCards(dealerHand,dealerHandSize, true, 9);
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
    while(hit!='d'&&hit!='D'&&hit!='h'&&hit!='H'&&hit!='S'&&hit!='s')
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
    char usernameSingle[11],usernameFile[11];
    int amount, wins, losses;
    bool ok=false;
    cout<<"Tasteaza numele :";
    cin>> skipws >>usernameSingle;
    cin.clear();
    cin.ignore(1000,'\n');
    while(!fileIn.eof()&&ok==0)
    {
        fileIn>>usernameFile>>amount>>wins>>losses;
        if(strcmp(usernameSingle,usernameFile)==0)
        {
            playerAmount=amount;
            playerWins=wins;
            playerLosses=losses;
            cout<<endl<<"Suma disponibila este: "<<playerAmount;
            ok=true;
        }
    }
    if(ok==false)
    {
        cout<<endl<<"Jucatorul nu este inregistrat.Doriti inregistrarea?(D/N)";
        char registration=_getch();
        while(registration!='D'&&registration!='d'&&registration!='n'&&registration!='N')
            registration=_getch();
        if(registration=='D'||registration=='d')
            newPlayer();
        else if(registration=='N'||registration=='n')
            mainMenu();
    }
    else if(ok==true && playerAmount==0)
    {
        cout<<"Suma disponibila este prea mica.Vrei sa faci update?(D/N)";
        char update=_getch();
        while(update!='D'&&update!='d'&&update!='N'&&update!='n')
            update=_getch();
        switch (update)
        {
        case 'd':
        case 'D':
            updatePlayer();
            break;
        case 'n':
        case 'N':
            mainMenu();
            break;
        }
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
    while(anotherHand!='d'&&anotherHand!='D'&&anotherHand!='n'&&anotherHand!='N')
        anotherHand=_getch();
    if(anotherHand=='D' || anotherHand=='d')
        multiPlayer();
    else if(anotherHand=='N' || anotherHand=='n' )
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
        player1Done=true;
        player2Done=true;
        anotherHandMulti();
    }
    if(checkBust(player2Hand,player2HandSize))
    {
        cout<<endl<<endl<<"Jucatorul 2 a pierdut!";
        player1Done=true;
        player2Done=true;
        anotherHandMulti();
    }
    if(blackjack(player1Hand,player1HandSize))
    {
        cout<<endl<<endl<<"Blackjack! Jucatorul 1 a castigat!";
        player1Done=true;
        player2Done=true;
        anotherHandMulti();
    }
    if(blackjack(player2Hand,player2HandSize))
    {
        cout<<endl<<endl<<"Blackjack! Jucatorul 2 a castigat!";
        player1Done=true;
        player2Done=true;
        anotherHandMulti();
    }
}

void whoWinsMulti()
{
    if(player1Sum<player2Sum)
    {
        cout<<endl<<endl<<"Jucatorul 2 a castigat!";
    }
    else if(player1Sum>player2Sum)
    {
        cout<<endl<<endl<<"Jucatorul 1 a castigat!";
    }
    else
        cout<<endl<<endl<<"Egalitate!";
}

void multiPlayer()
{
    newDeck();
    system("cls");
    player1Sum=0;
    player1HandSize=0;
    player2Sum=0;
    player2HandSize=0;
    firstMove=0;
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
    player1Done=false;
    player2Done=false;
    while(player1Done==false || player2Done==false)
    {
        system("cls");
        firstMove++;
        printMulti();
        if(player1Done==false)
        {
            cout<<endl<<"Este randul jucatorului 1";
            if(firstMove==1) cout<<endl<<"Apasa H pentru Hit, S pentru Stand si D pentru Double";
            else
                cout<<endl<<"Apasa H pentru Hit si S pentru Stand";
            char player1Option=_getch();
            while(player1Option!='d'&&player1Option!='D'&&player1Option!='h'&&player1Option!='H'&&player1Option!='S'&&player1Option!='s')
                player1Option=_getch();
            if(player1Option=='H' || player1Option=='h')
                multiPlayerHits(player1Hand,player1HandSize,1);
            if(player1Option=='D' || player1Option=='d')
            {
                multiPlayerHits(player1Hand,player1HandSize,1);
                player1Done=true;
            }
            if(player1Option=='S' || player1Option=='s')
                player1Done=true;
            checking();
        }

        system("cls");
        printMulti();
        if(player2Done==false)
        {
            cout<<endl<<"Este randul jucatorului 2";
            if(firstMove==1) cout<<endl<<"Apasa H pentru Hit, S pentru Stand si D pentru Double";
            else
                cout<<endl<<"Apasa H pentru Hit si S pentru Stand";
            char player2Option=_getch();
            while(player2Option!='d'&&player2Option!='D'&&player2Option!='h'&&player2Option!='H'&&player2Option!='S'&&player2Option!='s')
                player2Option=_getch();
            if(player2Option=='H' || player2Option=='h')
                multiPlayerHits(player2Hand,player2HandSize,2);
            if(player2Option=='D' || player2Option=='d')
            {
                multiPlayerHits(player2Hand,player2HandSize,2);
                player2Done=true;
            }
            if(player2Option=='s' || player2Option=='S')
                player2Done=true;
            checking();

        }
    }
    whoWinsMulti();
    anotherHandMulti();

}


void scores()
{
    system("CLS");
    fstream fileIn("f.txt", ios::in);
    cout<<"Tasteaza numele utilizatorului sau ''toti'' pentru a vedea toti utilizatorii: "<<endl;
    char username[11];
    char usernameFile[11];
    int amount, wins, losses;
    int ok=0;
    cin>>skipws>>username;
    int letters=1;
    for(int i=0; i<strlen(username); i++)
        if(char(username[i])<65|| (char(username[i])>90&&char(username[i])<97) || char(username[i])>122)
            letters=0;
    if(letters==0)
        scores();
    cout<<endl;
    char check=fileIn.peek();
    if(check==EOF)
        cout<<"Nu exista utilizatori.";
    else
    {
        if(strcmp(username,"toti")==0)
        {

            fileIn>>usernameFile>>amount>>wins>>losses;
            while(!fileIn.eof()&&ok==0)
            {
                cout<<"User: "<<usernameFile<<"  Suma: "<<amount<<" Jocuri castigate: "<<wins<<" Jocuri pierdute: "<<losses<<endl;
                fileIn>>usernameFile>>amount>>wins>>losses;
            }
        }
        else
        {

            while(!fileIn.eof()&&ok==0)
            {
                fileIn>>usernameFile>>amount>>wins>>losses;
                if(strcmp(username,usernameFile)==0)
                {
                    cout<<"User: "<<username<<"  Suma: "<<amount<<" Jocuri castigate: "<<wins<<" Jocuri pierdute: "<<losses<<endl;
                    ok=1;
                }
            }
            if(ok==0)
                cout<<endl<<"Jucatorul nu este inregistrat";
        }
    }
    cout<<endl<<"Apasati M pentru a reveni la meniul principal sau R pentru a reconsulta scorul";
    char key;
    key=_getch();
    while(key!='r'&&key!='R'&&key!='M'&&key!='m')
        key=_getch();
    if(key=='m' || key=='M')
        mainMenu();
    else if(key=='r'||key=='R')
        scores();
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
        exit(0);
    default:
        mainMenu();
    }
}

void openingScreen()
{
    string title="Blackjack";
    gotoXY(40,5);
    cout<<title<<endl;
    gotoXY(32,10);
    cout<<"Apasa C pentru a continua...";
    char key;
    key=_getch();
    while(key!='C' && key!='c')
        key=_getch();
    mainMenu();

}

int main()
{
    setConsoleSize();
    openingScreen();
    return 0;
}


