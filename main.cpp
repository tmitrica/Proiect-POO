#include <algorithm>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cassert>
using namespace std;

/*
    acest cod simuleaza un joc simplificat de monopoly; voi face cateva precizari referitoare la ordinea casutelor de pe tabla si efectul acestora
    tabla va avea 36 de proprietati indexate de la 0,1,2....,35

    ~START~ se afla la pozitia 0 si mereu cand un jucator trece peste sau aterizeaza pe ea va primi 200$
    ~gara~ va muta jucatorul pana la urmatoarea gara; acestea sa vor afla mereu pe pozitiile 4 12 24 32
    ~sansa si cufarul comunitatii~ nu au fost implementate inca si le putem considera casute neutre(nu au niciun efect asupra jucatorului)
    ~parcare si inchisoare(vizita)~ sunt casute neutre
    ~go_to_jail~ va trimite jucatorul la inchisoare care se va afla mereu pe pozitia 9; aici jucatorul va astepta 3 ture pana sa poata juca iar

    jocul se va desfasura pe un numar stabilit de ture intrucat sfarsitul(atunci cand ramane un singur jucator cu bani)
    si conceptul de plata chirie si implicit faliment nu a fost implementat

    proprietatile vor fi citite din fisierul board.txt sub forma: *nume* *pret(intreg>10)* *chirie(intreg)*
    numarul de jucatori si jucatorii vor fi cititi din fisierul players.txt

    in urma unor dificultati tehnice ambele fisiere au trebuit sa fie plasate in folderul de debug pentru a fi recunoscute de program(????)

 */


class Player {

    string name;
    int money, position, jail = 0;

public:
    explicit Player(const string &name = "", const int money = 1500,const int position = 0, const int jail = 0){
        this->name = name;
        this->money = money;
        this->position = position;
        this->jail = jail;
    }///constructor parametrizat; jucatorii vor incepe by default cu 1500$ si la pozitia 0(START) dar putem schimba asta daca dorim

    Player(const Player &other) {
        this->name = other.name;
        this->money = other.money;
        this->position = other.position;
        this->jail = other.jail;
    }/// constructor copiere

    void move(const int pos) {
        if(position +pos >= 36) {
            cout<<name<<" collected 200$ by going over START\n";
            money += 200;
        }

        position = (position + pos) % 36;
    }/// pentru mutat pe tabla(tinand cont de start)

    int move_train() {
        if(position == 4) position = 12;
        else if(position == 12) position = 24;
        else if(position == 24) position = 32;
        else if(position == 32){
            position = 4;
            money += 200;
            cout<<"(collected 200$ from START)\n";
        }
        return position;
    }///functie pentru mutat pe tabla folosind garile de tren

    void move_jail() {
        if(jail < 2) {
            position = 9;
            jail++;
            cout<<name<<" is in jail and cannot throw the dices\n";
        }
        else if(jail == 2) {
            jail = 0;
            cout<<name<<" can throw the dices again next round\n";
        }
    }///functie pentru verificat daca un jucator este in inchisoare si cate ture mai trebuie sa astepte

    int buy(const int price) {

        if(price == 0) return 0;

        if(money >= price) {
            money -= price;
            return 1;
        }
        else return 0;
    }///functie pentru verificat balanta in cazul unei proprietati libere

    [[nodiscard]] int getPosition() const {
        return position;
    }

    [[nodiscard]] const string& getName() const {
        return name;
    }

    [[nodiscard]] int getJail() const {
        return jail;
    }
    ///getters pentru nume pozitie si variabila care ne arata daca jucatorul curent este in inchisoare sau nu

    friend std::ostream & operator<<(std::ostream &os, const Player &obj) {
        return os
               << "name: " << obj.name
               << " money: " << obj.money
               << " position: " << obj.position;

    }///operator <<

    Player& operator=(const Player &other) {
        if (this != &other) {
            name = other.name;
            money = other.money;
            position = other.position;
            jail = other.jail;
        }
        return *this;
    }///operator= de copiere

    ~Player() = default;///destructor
};

class Property {

    string name;
    int price, rent;
    bool owned;
    Player *owner;

public:
    explicit Property(const string &name = "", const int price = 0, const int rent = 0, const bool owned = false, Player * const owner = nullptr) {
        this->name = name;
        this->price = price;
        this->rent = rent;
        this->owned = owned;
        this->owner = owner;
    }///constructor parametrizat

    int buy(Player *player) {
        if(price == 3)
            return 3;///cufar
        else if(price == 4)
            return 4;///sansa
        else if(price == 5)
            return 5;///gara
        else if(price == 2)
            return 2;///parcare; vizita la inchisoare; start
        else if(price == 6)
            return 6;//go_to_jail
        if(owned == false && player->buy(price)) {
            owned = true;
            owner = player;
            return 1;
        }
        else return 0;
    }///functie pentru verificat daca proprietatea pe care a aterizat un jucator este o casuta cu atribute speciale(start gara inchisoare etc)
     /// daca proprietatea este libera si jucatorul are balanta necesara aceasta va fi trecuta ca fiind detinuta de el

    friend std::ostream & operator<<(std::ostream &os, const Property &obj) {
        return os
               << "name: " << obj.name
               << " price: " << obj.price
               << " rent: " << obj.rent
               << " owned: " << obj.owned
               << " owner: " << obj.owner;
    }///operator <<

    [[nodiscard]] const string& getName() const {
        return name;
    }///geter pentru nume ca sa stim pe ce proprietate a aterizat un jucator

    ~Property() = default;///destructor

};

class Board {

    Property* properties;

public:
    explicit Board(const string &f) {
        properties = new Property[36];///vom crea o tabla formata din 36 de proprietati pe care le vom citi din fisier

        ifstream file(f);
        if (!file.is_open()) {
            cout << "file error" << f << '\n';
            exit(1);
        }
        string name;
        int price, rent;

        for (int i = 0; i < 36; ++i) {

            file >> name >> price >> rent;
            properties[i] = Property(name, price, rent);
        }
        file.close();
        }

    Board(const Board &other) {
        this->properties = new Property[36];
        copy_n(other.properties,other.properties+36,this->properties);
    }///constructor de copiere; vom declara o noua zona de memorie pentru a evita conflictele de memorie

    [[nodiscard]] const Property& getProperty(const int position) const {
        return properties[position];
    }///aflam proprietatea curenta pe care a aterizat un jucator

    friend void Turn(int currentPlayer, Player *players, const Board &board);
    ///detalii despre declararea ca functie prietena a functiei Turn mai jos in dreptul ei

    friend std::ostream & operator<<(std::ostream &os, const Board &obj) {
        return os << "properties: " << obj.properties;
    }///operator<<

    Board &operator=(const Board &other) {
        if (this == &other)
            return *this;
        properties = other.properties;
        return *this;
    }///operator= copiere

    ~Board() {
        delete[] properties;///destructor
    }
};

class Game {

    Player *players;
    int players_number = 0;
    Board board;

public:
    explicit Game(const string &f, const string &g):board(g){
        ifstream file(f);
        if (!file.is_open()) {
            cout << "file error" << f << '\n';
            exit(2);
        }

        string name;
        file >> players_number;
        players = new Player[players_number];

        for (int i = 0; i < players_number; ++i) {
            file >> name;
            players[i] = Player(name);
        }
        file.close();
    }///constructor pentru initializarea tablei dar si citirea jucatorilor din fisier si respectiv numarul acestor

    Game(const Game &other): board(other.board) {
        this->players = new Player[other.players_number];
        copy_n(other.players,other.players+other.players_number,this->players);
        this->players_number = other.players_number;
    }///constructor copiere;pentru players vom aloca o noua zona de memorie la fel ca la board

    void Turn(const int currentPlayer) const {
        Player &player = players[currentPlayer];

        if(player.getJail() == 0) {
            const int dice1 = rand() % 6 + 1;
            const int dice2 = rand() % 6 + 1;
            const int dice = dice1 + dice2;
            player.move(dice);

            auto &property = const_cast<Property&>(board.getProperty(player.getPosition()));

            int landed = property.buy(&player);
            if(landed == 1)
                cout <<player.getName()<<" at position "<<player.getPosition() << " bought property "<<property.getName()<<'\n';
            else if(landed == 3)
                cout <<player.getName()<<" at position "<<player.getPosition()<<" landed on a community chest\n";
            else if(landed == 4)
                cout <<player.getName()<<" at position "<<player.getPosition()<<" landed on a chance\n";
            else if(landed == 5)
                cout <<player.getName()<<" at position "<<player.getPosition()<<" landed on a train station and got moved to "
                <<player.move_train()<<'\n';
            else if(landed == 2)
                cout <<player.getName()<<" at position "<<player.getPosition()<<" landed on a neutral space\n";
            else if(landed == 6) {
                cout<<player.getName()<<" must go to jail for 3 rounds\n";
                player.move_jail();
            }
            else
                cout <<player.getName()<<" at position "<<player.getPosition()<<" property owned or insufficient founds\n";

        }else player.move_jail();
    }
    ///aceasta functie simuleaza o tura de joc a unui jucator; prima data verificam daca jucatorul curent este in inchisoare
    ///daca este in inchisoare actualizam numarul de ture ramase pana poate juca iar
    ///daca nu este apelam zarurile generate cu functia random apoi mutam jucatorul conform lor; verificam pe ce casuta a aterizat jucatorul
    ///aplicam efectele casutei asupra jucatorului si afisam la finalul turei ce s-a intamplat

    friend std::ostream & operator<<(std::ostream &os, const Game &obj) {
        return os
               << "players: " << obj.players
               << " players_number: " << obj.players_number
               << " board: " << obj.board;
    }///operator<<

    Game & operator=(const Game &other) {
        if (this == &other)
            return *this;
        players = other.players;
        players_number = other.players_number;
        board = other.board;
        return *this;
    }

    ~Game() {
        delete[] players;
    }///destructor
};


void testPlayer() {
    Player player("Teodor");
    player.move(15);
    assert(player.getPosition() == 15);

    player.move(30);
    assert(player.getPosition() == 9);/// va trece de 36 de casute ale tablei deci 45 % 36 = 9
    cout << "movement passed\n";

    const int result1 = player.buy(500);
    assert(result1 == 1);///vor fi fonduri suficiente

    const int result2 = player.buy(1200);
    assert(result2 == 1);/// vor fi fonduri suficiente cu cei 200$ de la start

    const int result3 = player.buy(100);
    assert(result3 == 0);/// fonduri insuficiente

    cout << "buying passed\n";
}/// testam functiile de mutare pe harta, de colectare 200$ de la start si de cumparare a proprietatilor

void testOwnership() {
    Player player("Teodor", 1500);
    Property property("Rahova", 500, 50);

    const int result1 = property.buy(&player);
    assert(result1 == 1);///poate fi cumparata

    const int result2 = property.buy(&player);
    assert(result2 == 0);///nu mai poate fi cumparata(este deja detinuta)

    cout << "ownership passed\n";
}///testam detinerea proprietatilor

void testJail() {
    Player player("Teodor");
    player.move_jail();
    assert(player.getPosition() == 9);///jucatorul se afla in inchisoare
    assert(player.getJail() == 1);

    player.move_jail();///se modifica numarul de ture pana cand jucatorul poate juca iar
    assert(player.getJail() == 2);

    player.move_jail();///jucatorul poate juca iar
    assert(player.getJail() == 0);
    cout << "jail passed\n";
}

void testTrain() {
    Player player("Teodor", 1500, 4);///incepem de la o gara
    player.move_train();

    assert(player.getPosition() == 12);
    player.move_train();
    assert(player.getPosition() == 24);///urmatoarele gari
    player.move_train();
    assert(player.getPosition() == 32);

    player.move_train();
    assert(player.getPosition() == 4);///verificam ca jucatorul poate trece prin toate garile si la ultima va primi 200$ pentru ca trece peste start
    cout << "train stations passed\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));///initializare seed pentru random

    testPlayer();
    testOwnership();
    testJail();
    testTrain();


    ///testam jocul in sine pentru functionalitatea functiei Turn si initializarea tablei
    const Game game("players.txt", "board.txt");///generam jocul cu ajutorul fisierelor
    cout<<'\n';

    for (int i = 0; i < 15; ++i) {
        game.Turn(i%3);///simulam 15 ture de joc pentru 3 jucatori
    }

    return 0;
}


