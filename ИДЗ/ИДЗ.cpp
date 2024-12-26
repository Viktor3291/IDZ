#include <iostream>
#include <string>
#include<array>
#include<limits>
#include <initializer_list>
using namespace std;

const int numberus = 36;

enum class suits { chervi, kresty, bubny, piki };
struct card {
    suits suit;
    int numb = 0;
    bool is_trump = false;
    bool in_game = false;
};
void tbspace(card* tb, card* pl, int num) {
    for (int i = 0; i != numberus; ++i) {
        if (not tb[i].in_game)
        {
            tb[i] = pl[num];
            tb[i].in_game = true;
            pl[num].in_game = false;
            break;
        }
    }
}

void ann(suits trump) {
    switch (trump) {
    case suits::chervi: cout << "козырь это черви" << endl; break;
    case suits::kresty: cout << "козырь это крести" << endl; break;
    case suits::bubny: cout << "козырь это бубны" << endl; break;
    case suits::piki: cout << "козырь это пики" << endl; break;
    }
}

void print(card* a) {
    int num = 1;
    for (int i = 0; i != numberus; i++) {
        /*if (not a[i].in_game && a[i].numb != 0) cout << "0" << endl;*/
        if (a[i].in_game) {
            cout << num++ << ".";
            switch (a[i].suit) {
            case suits::chervi: cout << "Черви" << " "; break;
            case suits::kresty: cout << "Крести" << " "; break;
            case suits::bubny: cout << "Бубны" << " "; break;
            case suits::piki: cout << "Пики" << " "; break;
            };
            if (a[i].numb > 10) switch (a[i].numb) {
            case 11: cout << "валет" << endl; break;
            case 12: cout << "дама" << endl; break;
            case 13: cout << "король" << endl; break;
            case 14: cout << "туз" << endl; break;
            }
            else cout << a[i].numb << endl;
        }
    };
    cout << endl;
};
void mix(card* a) {
    for (int i = 0; i != numberus; i++) {
        int z = rand() % numberus;
        card b = a[i];
        a[i] = a[z];
        a[z] = b;
    };
};

void take(card* giving, card* taking) {
    int b = 0, a = 0;
    while (not giving[a].in_game) a++;
    while (taking[b].in_game) b++;
    taking[b] = giving[a];
    giving[a].in_game = false;
};

void slurp(card* giving, card* taking) {
    int b = 0;
    for (int i = 0; i != numberus; i++)
        if (giving[i].in_game) {
            while (taking[b].in_game) b++;
            taking[b] = giving[i];
            giving[i].in_game = false;
        };
};
void take_while_six(card* taker, card* giver) {
    int g = 0, t = 0;
    for (int i = 0; i != numberus; i++) if (giver[i].in_game) g++;
    for (int i = 0; i != numberus; i++) if (taker[i].in_game) t++;
    while (g != 0 && t < 6) {
        take(giver, taker);
        g--; t++;
    };
};
bool defense_is_correct(card attack, card protection) {
    setlocale(LC_ALL, "Ru");
    if ((attack.suit == protection.suit && attack.numb < protection.numb) || (protection.is_trump && not attack.is_trump)) {
        return true;
    }
    else {
        cout << "Неверный ход!";
        return false;
    };
};
bool who_is_winner(card* p2) {
    for (int i = 0; i != numberus; i++) if (p2[i].in_game) return false;
    cout << "Выйграл 2й игрок!";
    return true;
};
bool game_is_over(card* t, card* p1, card* p2) {
    for (int i = 0; i != numberus; i++) if (t[i].in_game) return false;
    for (int i = 0; i != numberus; i++) if (p1[i].in_game) who_is_winner(p2);
    cout << "Выйграл 1й игрок!";
    return true;
};

bool toss_is_correct(card* table, card carda) {
    for (int i = 0; i != numberus; ++i) {
        if (carda.numb == table[i].numb)
            return true;
        else return false;

    }

    /*  else return false;*/

}

int correctnumb(int numb, card* pl) {
    for (int k = 0; k < numberus; k++)
        for (int i = k; i < numberus - 1; i++) if (not pl[i].in_game) {
            pl[i] = pl[i + 1];
            pl[i + 1].in_game = false;
        };

    return numb;
};

int correct() {
    int numb;
    while (true) {
        cin >> numb;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "введите ЦИФРУ" << endl;
        }
        else {
            if (numb < 0) {
                cout << "-карт нету";
            }
            else break;
        }

    }
    return numb;
}
void stp(card* pla, card* pld, card* dec, card* table, suits trump, int* step) {
    int numb1;
    int numb2;
    string vvod;
    cout << "ход атакующего игрока" << endl;
    ann(trump);
    print(pla);
    numb1 = correct();
    correctnumb(numb1, pla);
    --numb1;
    tbspace(table, pla, numb1);
    while (numb1 >= 0) {
        system("cls");
        cout << "защита" << endl;
        ann(trump);
        print(table);
        print(pld);
        numb2 = correct();
        correctnumb(numb2, pld);
        --numb2;
        if (numb2 >= 0) {
            while (1) {
                if (defense_is_correct(pla[numb1], pld[numb2])) {
                    system("cls");
                    tbspace(table, pld, numb2);
                    break;
                }
                else {
                    cout << "Неправильный ход - выберите другую карту" << endl;
                    numb2 = correct();
                    correctnumb(numb2, pld);
                    --numb2;
                    if (numb2 < 0) {
                        break;

                    }

                }
            }
        }
        do {
            system("cls");
            ann(trump);
            print(table);
            cout << "Подброс" << endl;
            print(pla);
            numb1 = correct();
            correctnumb(numb1, pla);
            --numb1;
            if (numb1 >= 0) {
                while (1) {
                    if (toss_is_correct(table, pla[numb1])) {
                        system("cls");
                        tbspace(table, pla, numb1);
                        print(table);
                        break;
                    }
                    else {
                        cout << "Неправильный ход - выберите другую карту" << endl;
                        numb1 = correct();
                        correctnumb(numb1, pla);
                        --numb1;
                        if (numb1 < 0) break;

                    }
                }
            }
            else {
                ++step;
                break;
            }
        }

        while (numb2 < 0 && numb1 >= 0);
        if (numb2 < 0) slurp(table, pld);
    };

    take_while_six(pla, dec);
    take_while_six(pld, dec);
    system("cls");
    for (int i = 0; i != numberus; i++)  table[i].in_game = false;
}

void game() {
    setlocale(LC_ALL, "Ru");
    srand(time(0));

    card table[numberus];
    card player1[numberus];
    card player2[numberus];
    card deck[numberus];

    suits trump = suits(rand()%4);

    int numb1;
    int numb2;
    int step = 1;
    int* c = &step;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < numberus/4; j++) {
            switch (i) {
            case 0: deck[i * numberus/4 + j].suit = { suits::chervi }; break;
            case 1: deck[i * numberus/4 + j].suit = { suits::kresty }; break;
            case 2: deck[i * numberus/4 + j].suit = { suits::bubny }; break;
            case 3: deck[i * numberus/4 + j].suit = { suits::piki }; break;
            };
            switch (trump) {
            case suits::chervi: deck[0 * numberus/4 + j].is_trump = true; break;
            case suits::kresty: deck[1 * numberus/4 + j].is_trump = true; break;
            case suits::bubny: deck[2 * numberus/4 + j].is_trump = true; break;
            case suits::piki: deck[3 * numberus/4 + j].is_trump = true; break;
            };
            if (j > 9) j = 0;
            deck[i * numberus/4 + j].numb = j + 6;
            deck[i * numberus/4 + j].in_game = true;
        };

    mix(deck);
    take_while_six(player1, deck);
    take_while_six(player2, deck);
    int numdeck = 0;
    cout << "добро пожаловать в игру - переводной дурак." << endl << "Правила - стандартные." << endl << " Чтобы разыграть карту введите её номер, написанный слева. чтобы спасовать(если вы атакующий игрок) или затянуть(если вы защищающийся игрок) введите ноль."<< endl <<"Введите любой символ чтобы начать игру " << endl;
    string start;
    cin >> start;
    while (not game_is_over(deck, player1, player2)) {
        if (step % 2 == 1) {
            cout << "Ход первого игрока(первый игрок - атакующий, второй - защищающийся)" << endl;
            stp(player1, player2, deck, table, trump, c);
        }
        else {
            cout << "Ход второго игрока(второй игрок - атакующий, первый - защищающийся" << endl;
            stp(player2, player1, deck, table, trump, c);
        }
    }
}
int main() {
    game();
};
