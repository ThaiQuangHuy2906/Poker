// SurprisingSwap.cpp - Implementation file

#include "../include/SurprisingSwap.h"
#include "../include/Utils.h"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <random>

using namespace std;

namespace creation2
{
    vector<Card> Deck()
    {
        vector<Card> deck;
        for (int i = 0; i <= 3; i++)
        {
            for (int j = 2; j <= 14; j++)
            {
                deck.push_back({j, i});
            }
        }
        random_device rd;                     // Tạo nguồn random an toàn
        mt19937 g(rd());                      // Sử dụng Mersenne Twister engine
        shuffle(deck.begin(), deck.end(), g); // Sử dụng std::shuffle
        return deck;
    }

    void deal(vector<Card> &deck, vector<Card> &hand)
    {
        for (int i = 0; i < 5; i++)
        {
            hand.push_back(deck.back());
            deck.pop_back();
        }
        return;
    }
    int evaluate(vector<Card> hand)
    {

        if (hand.size() == 0)
        {
            return 0;
        }
        map<int, int> rankCount;
        map<int, int> suitCount;
        vector<int> num;
        for (int card = 0; card < hand.size(); card++)
        {
            rankCount[hand[card].Rank]++;
            suitCount[hand[card].Suit]++;
            num.push_back(hand[card].Rank);
        }
        bool isFlush = (suitCount.size() == 1);
        bool isStraight = (rankCount.size() == 5 && num[4] - num[0] == 4);
        bool isFourofaKind = false;
        bool isThreeofaKind = false;
        bool isTwoPair = false;
        bool isOnePair = false;
        for (auto card : rankCount)
        {
            if (card.second == 4)
            {
                isFourofaKind = true;
            }
            if (card.second == 3)
            {
                isThreeofaKind = true;
            }
            if (card.second == 2)
            {
                if (isOnePair)
                {
                    isTwoPair = true;
                }
                else
                {
                    isOnePair = true;
                }
            }
        }
        bool isFullHouse = (isThreeofaKind && isOnePair);
        if (isFlush && isStraight)
        {
            return 8;
        }
        if (isFourofaKind)
        {
            return 7;
        }
        if (isFullHouse)
        {
            return 6;
        }
        if (isFlush)
        {
            return 5;
        }
        if (isStraight)
        {
            return 4;
        }
        if (isThreeofaKind)
        {
            return 3;
        }
        if (isTwoPair)
        {
            return 2;
        }
        if (isOnePair)
        {
            return 1;
        }
        return 0;
    }
    bool cmp(Card x, Card y)
    {
        return (x.Rank < y.Rank);
    }
    int compare(vector<Card> p1, vector<Card> p2)
    {
        if (p2.size() == 0)
        {
            return 1;
        }
        map<int, int> numCount;
        for (int i = 0; i < 5; i++)
        {
            numCount[p1[i].Rank]++;
        }
        int Four = 0;
        int Three = 0;
        int Two = 0;
        int One = 0;
        int Alone = 0;
        int Four1 = 0;
        int Three1 = 0;
        int Two1 = 0;
        int One1 = 0;
        int Alone1 = 0;
        for (int i = 0; i < 5; i++)
        {
            if (numCount[p1[i].Rank] == 4)
            {
                Four = p1[i].Rank;
            }
            if (numCount[p1[i].Rank] == 3)
            {
                Three = p1[i].Rank;
            }
            if (numCount[p1[i].Rank] == 2)
            {
                if (One)
                {
                    Two = p1[i].Rank;
                }
                else
                {
                    One = p1[i].Rank;
                }
            }
            if (numCount[p1[i].Rank] == 1)
            {
                Alone = p1[i].Rank;
            }
        }
        numCount.clear();
        for (int i = 0; i < 5; i++)
        {
            numCount[p2[i].Rank]++;
        }
        for (int i = 0; i < 5; i++)
        {

            if (numCount[p2[i].Rank] == 4)
            {
                Four1 = p2[i].Rank;
            }
            if (numCount[p2[i].Rank] == 3)
            {
                Three1 = p2[i].Rank;
            }
            if (numCount[p2[i].Rank] == 2)
            {
                if (One1)
                {
                    Two1 = p2[i].Rank;
                }
                else
                {
                    One1 = p2[i].Rank;
                }
            }
            if (numCount[p2[i].Rank] == 1)
            {
                Alone1 = p2[i].Rank;
            }
        }
        int res = evaluate(p1);
        int ans = evaluate(p2);
        if (ans < res)
        {
            return 1;
        }
        else if (ans == res)
        {
            if (res == 4 || res == 8)
            {
                if (p2[4].Rank < p1[4].Rank)
                {
                    return 1;
                }
                else if (p2[4].Rank > p1[4].Rank)
                {
                    return 2;
                }
                return 0;
            }
            else if (res == 7)
            {
                if (Four1 < Four)
                {
                    return 1;
                }
                else if (Four1 > Four)
                {
                    return 2;
                }
                return 0;
            }
            else if (res == 6 || res == 3)
            {
                if (Three1 < Three)
                {
                    return 1;
                }
                else if (Three1 > Three)
                {
                    return 2;
                }
                return 0;
            }
            else if (res == 5 || res == 0)
            {
                for (int i = 4; i >= 0; i--)
                {
                    if (p2[i].Rank < p1[i].Rank)
                    {
                        return 1;
                    }
                    else if (p2[i].Rank > p1[i].Rank)
                    {
                        return 2;
                    }
                }
                return 0;
            }
            else if (res == 2)
            {
                if (Two1 < Two)
                {
                    return 1;
                }
                else if (Two1 == Two)
                {
                    if (One1 < One)
                    {
                        return 1;
                    }
                    else if (One1 == One)
                    {
                        if (Alone1 < Alone)
                        {
                            return 1;
                        }
                        else if (Alone1 > Alone)
                        {
                            return 2;
                        }
                        return 0;
                    }
                    return 2;
                }
                return 2;
            }
            else
            {
                if (One1 < One)
                {
                    return 1;
                }
                else if (One1 == One)
                {
                    vector<int> stupid;
                    vector<int> noob;
                    for (int i = 0; i < 5; i++)
                    {
                        if (p1[i].Rank != One)
                        {
                            stupid.push_back(p1[i].Rank);
                        }
                        if (p2[i].Rank != One1)
                        {
                            noob.push_back(p2[i].Rank);
                        }
                    }
                    for (int i = 2; i >= 0; i--)
                    {
                        if (stupid[i] > noob[i])
                        {
                            return 1;
                        }
                        if (stupid[i] < noob[i])
                        {
                            return 2;
                        }
                    }
                    return 0;
                }
                return 2;
            }
        }
        return 2;
    }
    string getRankName(int Rank)
    {
        switch (Rank)
        {
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
        case 10:
            return "10";
        case 11:
            return "J";
        case 12:
            return "Q";
        case 13:
            return "K";
        case 14:
            return "A";
        default:
            return "";
        }
    }

    // Hàm trả về tên chất bài
    string getSuitName(int Suit)
    {
        switch (Suit)
        {
        case 0:
            return "Spades";
        case 1:
            return "Clubs";
        case 2:
            return "Diamonds";
        case 3:
            return "Hearts";
        default:
            return "";
        }
    }

    // Hàm trả về trường hợp bài
    string getHandName(int handType)
    {
        switch (handType)
        {
        case 8:
            return "Straight Flush";
        case 7:
            return "Four of a Kind";
        case 6:
            return "Full House";
        case 5:
            return "Flush";
        case 4:
            return "Straight";
        case 3:
            return "Three of a Kind";
        case 2:
            return "Two Pair";
        case 1:
            return "One Pair";
        default:
            return "High Card";
        }
    }

    long long Rand(long long L, long long R)
    {
        assert(L <= R);
        return L + rand() % (R - L + 1);
    }

    void playGame()
    {
        setTextColor(14);
        int numPlayers;
        cout << "Enter number of players(2-10): ";
        cin >> numPlayers;

        vector<player> players;
        for (int i = 1; i <= numPlayers; i++)
        {
            players.push_back({to_string(i), {}, 3000, 300});
        }

        int remainingPlayers = numPlayers;
        vector<bool> check(numPlayers + 1, false);

        vector<Card> deck = Deck();

        while (remainingPlayers > 1)
        {

            for (auto &player : players)
            {
                player.cards.clear();
                deal(deck, player.cards);
                sort(player.cards.begin(), player.cards.end(), cmp);
                cout << "Player " << player.name << ": " << '\n';
                for (auto card : player.cards)
                {
                    cout << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << '\n';
                }
                cout << "\n";
            }
            setTextColor(2);
            cout << "Swap Round, vote to swap " << '\n';
            int condition = remainingPlayers / 2;
            int cnt = 0;
            char choice;
            for (int i = 0; i < players.size(); i++)
            {
                setTextColor(3);
                cout << "Player " << players[i].name << "'s choice (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y')
                {
                    ++cnt;
                }
            }
            cout << '\n';
            if (cnt > condition)
            {
                for (int i = 0; i < 20; i++)
                {
                    int x = (int)Rand(0, numPlayers - 1);
                    int y = (int)Rand(0, numPlayers - 1);
                    if (check[x] || check[y] || x == y)
                    {
                        continue;
                    }
                    swap(players[x].cards, players[y].cards);
                }
            }
            int id = -1;
            bool draw = false;
            for (int i = 0; i < players.size(); i++)
            {
                if (check[i])
                {
                    continue;
                }
                if (id == -1)
                {
                    id = i;
                }
                else
                {
                    if (compare(players[id].cards, players[i].cards) == 2)
                    {
                        id = i;
                    }
                }
            }
            for (int i = 0; i < players.size(); i++)
            {
                if (!check[i] && i != id)
                {
                    if (!compare(players[id].cards, players[i].cards))
                    {
                        draw = true;
                    }
                }
            }
            if (draw)
            {
                cout << "Draw" << '\n';
                goto ed;
            }
            for (int i = 0; i < players.size(); i++)
            {
                if (!check[i])
                {
                    if (i != id)
                    {
                        players[i].coins -= 300;
                    }
                    else
                        players[i].coins += 300;
                }
            }
            cout << '\n';
            for (int i = 0; i < players.size(); i++)
            {
                cout << "Player " << players[i].name << " has " << players[i].coins << " left" << '\n';
                if (players[i].coins < 300 && !check[i])
                {
                    check[i] = true;
                    --remainingPlayers;
                }
            }
            setTextColor(4);
            playMp3("music.mp3", 10);
            cout << "Winner this round: Player " << players[id].name << '\n';
            for (auto card : players[id].cards)
            {
                cout << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << '\n';
            }
        ed:;
            cout << '\n';
            setTextColor(2);
            cout << "Next round: " << '\n';
            deck = Deck();
        }
        for (int i = 0; i < players.size(); i++)
        {
            if (!check[i])
            {
                playMp3("music.mp3", 10);
                cout << "Last winner: Player " << players[i].name << '\n';
            }
        }
    }
    void solve()
    {
        char playAgain = 'Y';
        while (playAgain == 'Y' || playAgain == 'y')
        {
            playGame();
            setTextColor(10);
            cout << "Play again? (Y/N): ";
            cin >> playAgain;
        }
    }
}
