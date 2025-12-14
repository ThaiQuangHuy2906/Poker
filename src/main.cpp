#include "../include/Utils.h"
#include "../include/TexasHoldemPoker.h"
#include "../include/TwoFiveHihi.h"
#include "../include/SurprisingSwap.h"
#include <iostream>

using namespace std;

int main()
{
    setTextColor(3);
    cout << "Menu Game: \n";
    setTextColor(4);
    cout << "1. Texas Hold'em Poker\n";
    cout << "2. Two Five Hihi\n";
    cout << "3. Surprising Swap\n";
    setTextColor(5);
    cout << "Your choice: ";
    char choice;
    cin >> choice;

    if (choice == '1')
    {
        TexasHoldemPoker::solve();
    }
    else if (choice == '2')
    {
        creation1::solve();
    }
    else
    {
        creation2::solve();
    }

    return 0;
}
