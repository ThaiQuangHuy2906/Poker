#include "../include/TexasHoldemPoker.h"
#include "../include/Utils.h"
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

namespace TexasHoldemPoker
{
    // Global variables
    bool gameOver = false;
    int numRounds = 0;
    int ante = 5;
    int selected[8];
    vector<Card> strongestCards[5];
    vector<Player> players;

    // Player operator==
    bool Player::operator==(const Player &other) const
    {
        return name == other.name;
    }

    // Hàm trả về tên hạng bài
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

    // Hàm xử lý cược Ante
    void collectAnte(vector<Player> &players, float &pot)
    {
        cout << "== Collect Ante Bet ==\n";
        for (auto &player : players)
        {
            if (player.coins >= ante)
            {
                player.coins -= ante;
                pot += ante;
                cout << "Player " << stoi(player.name) + 1 << " has placed an Ante bet: " << ante << "\n";
            }
            else
            {
                player.isAllIn = true;
                pot += player.coins;
                cout << "Player " << stoi(player.name) + 1 << " doesn't have enough money to place an Ante bet.\n";
                player.coins = 0;
            }
        }
        cout << "Current Pot: " << pot << "\n\n";
    }

    // Hàm chọn ngẫu nhiên Dealer
    int getDealerIndex(const vector<Player> &players)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, (int)players.size() - 1);
        return dist(gen);
    }

    // Hàm chọn Dealer tiếp theo
    int getNextDealerIndex(int currentDealerIndex, const vector<Player> &players)
    {
        return (currentDealerIndex + 1) % (int)players.size();
    }

    // Hàm tạo bộ bài
    vector<Card> Deck()
    {
        vector<Card> deck;
        for (int i = 0; i <= 3; ++i)
            for (int j = 2; j <= 14; ++j)
                deck.push_back({j, i});

        random_device rd;
        mt19937 g(rd());
        shuffle(deck.begin(), deck.end(), g);
        return deck;
    }

    // Hàm chia bài
    void dealHand(vector<Card> &deck, vector<Card> &hand, int numCards)
    {
        for (int i = 0; i < numCards; ++i)
        {
            hand.push_back(deck.back());
            deck.pop_back();
        }
    }

    void dealTwoCards(vector<Player> &players, vector<Card> &deck)
    {
        for (auto &player : players)
        {
            dealHand(deck, player.cards, 2);
        }
    }

    void showHiddenCards(const vector<Player> &players)
    {
        for (const auto &player : players)
        {
            cout << "Player " << stoi(player.name) + 1 << "'s cards: [X] [X]\n";
        }
        cout << "\n";
    }

    void revealPlayerCards(vector<Player> &players, int playerIndex)
    {
        cout << "Player " << stoi(players[playerIndex].name) + 1 << "'s cards: \n";
        for (const auto &card : players[playerIndex].cards)
        {
            cout << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << '\n';
        }
    }

    void hidePlayerCards(vector<Player> &players, int playerIndex)
    {
        cout << "Player " << stoi(players[playerIndex].name) + 1 << "'s cards are hidden again.\n\n";
    }

    // Hàm tính giá trị tay bài
    int evaluate(vector<Card> hand)
    {
        if ((int)hand.size() == 0)
            return 9;

        map<int, int> rankCount;
        map<int, int> suitCount;
        vector<int> num;

        for (const auto &card : hand)
        {
            rankCount[card.Rank]++;
            suitCount[card.Suit]++;
            num.push_back(card.Rank);
        }

        sort(num.begin(), num.end());

        bool isFlush = ((int)suitCount.size() == 1);
        bool isStraight = ((int)rankCount.size() == 5 && (num[4] - num[0] == 4));
        bool isFourofaKind = false;
        bool isThreeofaKind = false;
        bool isTwoPair = false;
        bool isOnePair = false;

        for (auto card : rankCount)
        {
            if (card.second == 4)
                isFourofaKind = true;
            if (card.second == 3)
                isThreeofaKind = true;
            if (card.second == 2)
            {
                if (isOnePair)
                    isTwoPair = true;
                else
                    isOnePair = true;
            }
        }
        bool isFullHouse = (isThreeofaKind && isOnePair);

        if (isFlush && isStraight)
            return 8;
        if (isFourofaKind)
            return 7;
        if (isFullHouse)
            return 6;
        if (isFlush)
            return 5;
        if (isStraight)
            return 4;
        if (isThreeofaKind)
            return 3;
        if (isTwoPair)
            return 2;
        if (isOnePair)
            return 1;
        return 0;
    }

    bool cmp(Card x, Card y)
    {
        return (x.Rank < y.Rank);
    }

    // Hàm so sánh 2 tay bài
    int compare(vector<Card> p1, vector<Card> p2)
    {
        if ((int)p2.size() == 0)
            return 1;

        map<int, int> numCount;
        for (int i = 0; i < 5; ++i)
            ++numCount[p1[i].Rank];

        int Four1 = 0, Three1 = 0, Two1 = 0, One1 = 0, Alone1 = 0;
        int Four2 = 0, Three2 = 0, Two2 = 0, One2 = 0, Alone2 = 0;

        for (int i = 0; i < 5; i++)
        {
            if (numCount[p1[i].Rank] == 4)
                Four1 = p1[i].Rank;
            if (numCount[p1[i].Rank] == 3)
                Three1 = p1[i].Rank;
            if (numCount[p1[i].Rank] == 2)
            {
                if (One1)
                    Two1 = p1[i].Rank;
                else
                    One1 = p1[i].Rank;
            }
            if (numCount[p1[i].Rank] == 1)
                Alone1 = p1[i].Rank;
        }

        numCount.clear();
        for (int i = 0; i < 5; ++i)
        {
            numCount[p2[i].Rank]++;
        }

        for (int i = 0; i < 5; ++i)
        {
            if (numCount[p2[i].Rank] == 4)
                Four2 = p2[i].Rank;
            if (numCount[p2[i].Rank] == 3)
                Three2 = p2[i].Rank;
            if (numCount[p2[i].Rank] == 2)
            {
                if (One2)
                    Two2 = p2[i].Rank;
                else
                    One2 = p2[i].Rank;
            }
            if (numCount[p2[i].Rank] == 1)
                Alone2 = p2[i].Rank;
        }

        int value1 = evaluate(p1);
        int value2 = evaluate(p2);

        if (value2 < value1)
            return 1;
        else if (value2 == value1)
        {
            if (value1 == 4 || value1 == 8)
            {
                if (p2[4].Rank < p1[4].Rank)
                    return 1;
                else if (p2[4].Rank > p1[4].Rank)
                    return 2;
                return 0;
            }
            else if (value1 == 7)
            {
                if (Four2 < Four1)
                    return 1;
                else if (Four2 > Four1)
                    return 2;
                return 0;
            }
            else if (value1 == 6 || value1 == 3)
            {
                if (Three2 < Three1)
                    return 1;
                else if (Three2 > Three1)
                    return 2;
                return 0;
            }
            else if (value1 == 5 || value1 == 0)
            {
                for (int i = 4; i >= 0; --i)
                {
                    if (p2[i].Rank < p1[i].Rank)
                        return 1;
                    if (p2[i].Rank > p1[i].Rank)
                        return 2;
                }
                return 0;
            }
            else if (value1 == 2)
            {
                if (Two2 < Two1)
                    return 1;
                else if (Two2 == Two1)
                {
                    if (One2 < One1)
                        return 1;
                    else if (One2 == One1)
                    {
                        if (Alone2 < Alone1)
                            return 1;
                        else if (Alone2 > Alone1)
                            return 2;
                        return 0;
                    }
                    return 2;
                }
                return 2;
            }
            else
            {
                if (One2 < One1)
                    return 1;
                else if (One2 == One1)
                {
                    vector<int> stupid;
                    vector<int> noob;
                    for (int i = 0; i < 5; ++i)
                    {
                        if (p1[i].Rank != One1)
                            stupid.push_back(p1[i].Rank);
                        if (p2[i].Rank != One2)
                            noob.push_back(p2[i].Rank);
                    }
                    for (int i = 2; i >= 0; --i)
                    {
                        if (stupid[i] > noob[i])
                            return 1;
                        if (stupid[i] < noob[i])
                            return 2;
                    }
                    return 0;
                }
                return 2;
            }
        }
        return 2;
    }

    void solveHand(vector<Card> &hand, int pos)
    {
        vector<Card> choosen;
        int count = 0;
        for (Card card : hand)
        {
            ++count;
            if (selected[count])
                choosen.push_back(card);
        }
        sort(choosen.begin(), choosen.end(), cmp);
        if (compare(choosen, strongestCards[pos]))
            strongestCards[pos] = choosen;
    }

    void generateCombinations(int n, int k, vector<Card> &hand, int pos)
    {
        if (k == 5)
        {
            solveHand(hand, pos);
            return;
        }
        if (n > 7)
            return;
        for (int i = 0; i <= 1; ++i)
        {
            selected[n] = i;
            if (i)
            {
                generateCombinations(n + 1, k + 1, hand, pos);
            }
            else
            {
                generateCombinations(n + 1, k, hand, pos);
            }
            selected[n] = 0;
        }
    }

    void burnCard(vector<Card> &deck)
    {
        if (!deck.empty())
        {
            deck.pop_back();
            cout << "Burned 1 card." << endl;
        }
    }

    void revealCommunityCards(vector<Card> &communityCards, vector<Card> &deck, int numCards)
    {
        burnCard(deck);
        for (int i = 0; i < numCards; ++i)
        {
            communityCards.push_back(deck.back());
            deck.pop_back();
        }
    }

    void showCommunityCards(const vector<Card> &communityCards)
    {
        cout << "Flop cards: \n";
        for (const auto &card : communityCards)
        {
            cout << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << "\n";
        }
        cout << endl;
    }

    void handleAction(Player &player, float &pot, float &currentBet)
    {
        int action;
        bool validAction = false;

        while (!validAction)
        {
            cout << "\tChoose action (1 = Fold, 2 = Call, 3 = Raise, 4 = All In, 5 = Check, 6 = Bet): ";
            cin >> action;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\tInvalid input. Please enter a valid number (1-6).\n";
                continue;
            }

            if (action == 1)
            {
                player.isFolded = true;
                validAction = true;
                cout << "\tPlayer " << stoi(player.name) + 1 << " Folded.\n";
                cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
            }
            else if (action == 2)
            {
                if (currentBet == 0)
                {
                    cout << "\tNo bet to call. Must Fold, Bet, Check or All-in\n";
                    continue;
                }
                float callAmount = currentBet;
                if (player.coins >= callAmount)
                {
                    validAction = true;
                    player.currentPlayerBet = callAmount;
                    player.coins -= callAmount;
                    pot += callAmount;
                    cout << "\tPlayer " << stoi(player.name) + 1 << " called with " << callAmount << ".\n";
                    cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
                }
                else
                {
                    player.isAllIn = true;
                    validAction = true;
                    player.currentPlayerBet = player.coins;
                    pot += player.coins;
                    cout << "\tPlayer " << stoi(player.name) + 1 << " does not have enough coins to Call so ...\n";
                    cout << "\tPlayer " << stoi(player.name) + 1 << " went All-in with " << player.coins << ".\n";
                    player.coins = 0;
                    cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
                }
            }
            else if (action == 3)
            {
                if (currentBet == 0)
                {
                    cout << "\tCannot raise as no one has bet before. You can only Bet or Check.\n";
                    continue;
                }
                float raiseAmount;
                cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
                cout << "\tEnter raise amount: ";
                cin >> raiseAmount;
                if (raiseAmount + currentBet > player.coins)
                {
                    cout << "\tNot enough coins to raise. Please choose again or re-raise the amount\n";
                    continue;
                }
                validAction = true;
                player.currentPlayerBet = currentBet + raiseAmount;
                player.coins -= currentBet;
                pot += currentBet;
                cout << "\tPlayer " << stoi(player.name) + 1 << " raised the bet to " << currentBet + raiseAmount << ".\n";
                cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
            }
            else if (action == 4)
            {
                validAction = true;
                player.isAllIn = true;
                float allInAmount = player.coins;
                player.currentPlayerBet = player.coins;
                currentBet = max(currentBet, allInAmount);
                pot += allInAmount;
                player.coins = 0;
                cout << "\tPlayer " << stoi(player.name) + 1 << " went all-in with " << allInAmount << ".\n";
                cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
            }
            else if (action == 5)
            {
                if (currentBet == 0)
                {
                    validAction = true;
                    player.currentPlayerBet = 0;
                    cout << "\tPlayer " << stoi(player.name) + 1 << " checked.\n";
                    cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
                }
                else
                {
                    cout << "\tPlayer " << stoi(player.name) + 1 << " cannot check, must Call, Raise, Fold or All in.\n";
                    cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
                }
            }
            else if (action == 6)
            {
                if (currentBet > 0)
                {
                    cout << "\tCannot bet when there is already a current bet. Must Call, Raise, Fold or All-in.\n";
                    continue;
                }
                float betAmount;
                cout << "\tCurrent player " << stoi(player.name) + 1 << "'s amount: " << player.coins << ".\n";
                cout << "\tEnter bet amount: ";
                cin >> betAmount;
                if (betAmount > player.coins)
                {
                    cout << "\tNot enough coins to bet.\n";
                    continue;
                }
                validAction = true;
                currentBet = betAmount;
                player.currentPlayerBet = betAmount;
                player.coins -= betAmount;
                pot += betAmount;
                if (betAmount == player.coins)
                    cout << "\tPlayer " << stoi(player.name) + 1 << " went all-in with " << betAmount << ".\n";
                else
                    cout << "\tPlayer " << stoi(player.name) + 1 << " bet " << betAmount << ".\n";
            }
            else
            {
                cout << "\tInvalid action. Please choose a valid action.\n";
                continue;
            }
        }
    }

    void processBettingRound(vector<Player> &players, float &pot, int startPlayer, float &currentBet, bool &gameOver)
    {
        vector<int> activePlayers;
        for (int i = 0; i < (int)players.size(); ++i)
        {
            if (!players[i].isFolded && !players[i].isAllIn)
            {
                activePlayers.push_back(i);
            }
        }

        int lastRaiser = -1;
        int lastCaller = -1;
        bool raisedDuringRound = false;
        bool activeRound = true;

        while (activeRound)
        {
            activeRound = false;
            raisedDuringRound = false;
            vector<int> sidePlayers;

            for (int offset = 0; offset < (int)activePlayers.size(); ++offset)
            {
                int i = activePlayers[(startPlayer + offset) % (int)activePlayers.size()];

                cout << "Player " << stoi(players[i].name) + 1 << "'s turn. Current Bet: " << currentBet << '\n';

                revealPlayerCards(players, i);
                handleAction(players[i], pot, currentBet);
                hidePlayerCards(players, i);

                if (!players[i].isFolded && !players[i].isAllIn)
                {
                    sidePlayers.push_back(i);
                }

                int remainingPlayers = 0;
                int winnerIndex = -1;
                for (int j = 0; j < (int)players.size(); ++j)
                {
                    if (!players[j].isFolded && !players[j].isAllIn)
                    {
                        remainingPlayers++;
                        winnerIndex = j;
                    }
                }
                if (remainingPlayers == 1)
                {
                    cout << "Player " << stoi(players[winnerIndex].name) + 1 << " wins the game as the last remaining player!" << endl;
                    players[winnerIndex].coins += pot;
                    pot = 0;
                    gameOver = true;
                    return;
                }

                if (players[i].currentPlayerBet > currentBet)
                {
                    currentBet = players[i].currentPlayerBet;
                    lastRaiser = i;
                    raisedDuringRound = true;
                    activeRound = true;
                }
                else if (players[i].currentPlayerBet == currentBet)
                {
                    lastCaller = i;
                    if (raisedDuringRound && i == activePlayers.back())
                    {
                        activeRound = false;
                        break;
                    }
                }
            }

            activePlayers = sidePlayers;

            if (raisedDuringRound && activeRound)
            {
                setTextColor(14);
                startPlayer = (find(activePlayers.begin(), activePlayers.end(), lastRaiser) - activePlayers.begin() + 1) % (int)activePlayers.size();
                cout << "== Side Betting Round ==\n";
            }
        }
    }

    void preFlop(vector<Player> &players, vector<Card> &deck, float &pot, int &dealerIndex)
    {
        cout << "== Pre-flop Betting Round ==\n";
        collectAnte(players, pot);

        int smallBlindIndex = (dealerIndex + 1) % (int)players.size();
        int bigBlindIndex = (smallBlindIndex + 1) % (int)players.size();

        float smallBlind = 10;
        float bigBlind = 20;

        players[smallBlindIndex].coins -= smallBlind;
        players[bigBlindIndex].coins -= bigBlind;
        pot += smallBlind + bigBlind;
        float currentBet = bigBlind;

        cout << "Player " << dealerIndex + 1 << " has received the Dealer button!\n";
        cout << "Small Blind is Player " << stoi(players[smallBlindIndex].name) + 1 << "\n";
        cout << "\tCurrent Player " << stoi(players[smallBlindIndex].name) + 1 << "'s amount: " << players[smallBlindIndex].coins << ".\n";
        cout << "Big Blind is Player " << stoi(players[bigBlindIndex].name) + 1 << "\n";
        cout << "\tCurrent Player " << stoi(players[bigBlindIndex].name) + 1 << "'s amount: " << players[bigBlindIndex].coins << ".\n";
        cout << "Current Pot: " << pot << "\n\n";

        dealTwoCards(players, deck);
        showHiddenCards(players);

        int startPlayer = (bigBlindIndex + 1) % (int)players.size();
        processBettingRound(players, pot, startPlayer, currentBet, gameOver);
    }

    void flop(vector<Player> &players, vector<Card> &communityCards, vector<Card> &deck, float &pot, int &dealerIndex)
    {
        if (gameOver)
            return;
        cout << "== Flop Betting Round ==\n";
        revealCommunityCards(communityCards, deck, 3);
        showCommunityCards(communityCards);
        float currentBet = 0;
        int startPlayer = (dealerIndex + 1) % players.size();
        processBettingRound(players, pot, startPlayer, currentBet, gameOver);
        cout << "Current Pot: " << pot << '\n';
    }

    void turn(vector<Player> &players, vector<Card> &communityCards, vector<Card> &deck, float &pot, int &dealerIndex)
    {
        if (gameOver)
            return;
        cout << "== Turn Betting Round ==\n";
        revealCommunityCards(communityCards, deck, 1);
        cout << "Turn card: \n"
             << getRankName(communityCards.back().Rank) << " of " << getSuitName(communityCards.back().Suit) << "\n\n";
        float currentBet = 0;
        int startPlayer = (dealerIndex + 1) % players.size();
        processBettingRound(players, pot, startPlayer, currentBet, gameOver);
        cout << "Pot: " << pot << '\n';
    }

    void river(vector<Player> &players, vector<Card> &communityCards, vector<Card> &deck, float &pot, int &dealerIndex)
    {
        if (gameOver)
            return;
        cout << "== River Betting Round ==\n";
        revealCommunityCards(communityCards, deck, 1);
        cout << "River card: \n"
             << getRankName(communityCards.back().Rank) << " of " << getSuitName(communityCards.back().Suit) << endl;
        float currentBet = 0;
        int startPlayer = (dealerIndex + 1) % players.size();
        processBettingRound(players, pot, startPlayer, currentBet, gameOver);
        cout << "Current Pot: " << pot << '\n';
    }

    void printHand(const vector<Card> &hand)
    {
        for (const auto &card : hand)
        {
            cout << "\t" << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << endl;
        }
        cout << "\n";
    }

    vector<Card> determineWinnerAfterRiver(vector<Player> &players, vector<Card> &communityCards, float &pot)
    {
        vector<Card> strongestHand;
        int activePlayers = 0;
        int winningHandType = -1;
        vector<Player *> winners;

        for (int i = 0; i < (int)players.size(); ++i)
        {
            if (!players[i].isFolded)
            {
                activePlayers++;
                vector<Card> fullHand = players[i].cards;
                fullHand.insert(fullHand.end(), communityCards.begin(), communityCards.end());
                generateCombinations(1, 0, fullHand, i);
                memset(selected, 0, sizeof(selected));
                int handType = evaluate(strongestCards[i]);
                cout << "Player " << stoi(players[i].name) + 1 << "'s strongest hand: \n";
                printHand(strongestCards[i]);
                cout << "Hand type: " << getHandName(handType) << "\n\n";

                if (winners.empty() || compare(strongestCards[i], strongestHand) == 1)
                {
                    winners.clear();
                    winners.push_back(&players[i]);
                    strongestHand = strongestCards[i];
                    winningHandType = handType;
                }
                else if (compare(strongestCards[i], strongestHand) == 0)
                {
                    winners.push_back(&players[i]);
                }
            }
        }

        if (activePlayers >= 2)
        {
            if (!winners.empty())
            {
                cout << "\nResult:\n";
                if (winners.size() > 1)
                {
                    cout << "It's a tie! The following players share the pot:\n";
                    for (const auto &winPlayer : winners)
                    {
                        cout << "\tPlayer " << stoi(winPlayer->name) + 1 << " with hand type: " << getHandName(winningHandType) << "\n";
                        printHand(strongestCards[stoi(winPlayer->name)]);
                        cout << "\n";
                        winPlayer->gamesWon++;
                    }
                    float share = pot / winners.size();
                    for (const auto &winPlayer : winners)
                    {
                        winPlayer->coins += share;
                        cout << "\tCurrent Player " << stoi(winPlayer->name) + 1 << "'s amount: " << winPlayer->coins << ".\n\n";
                    }
                }
                else
                {
                    cout << "Winner: \n";
                    for (const auto &winPlayer : winners)
                    {
                        cout << "\tPlayer " << stoi(winPlayer->name) + 1 << " with: \n";
                        cout << "\tHand type: " << getHandName(winningHandType) << "\n";
                        printHand(strongestHand);
                        cout << "\n";
                        winPlayer->gamesWon++;
                        winPlayer->coins += pot;
                        cout << "\tCurrent Player " << stoi(winPlayer->name) + 1 << "'s amount: " << winPlayer->coins << ".\n\n";
                    }
                }

                for (auto &winPlayer : winners)
                {
                    switch (winningHandType)
                    {
                    case 8:
                        winPlayer->cnt_StraightFlush++;
                        break;
                    case 7:
                        winPlayer->cnt_FourOfAKind++;
                        break;
                    case 6:
                        winPlayer->cnt_FullHouse++;
                        break;
                    case 5:
                        winPlayer->cnt_Flush++;
                        break;
                    case 4:
                        winPlayer->cnt_Straight++;
                        break;
                    case 3:
                        winPlayer->cnt_ThreeOfAKind++;
                        break;
                    case 2:
                        winPlayer->cnt_TwoPair++;
                        break;
                    case 1:
                        winPlayer->cnt_OnePair++;
                        break;
                    default:
                        winPlayer->cnt_HighCard++;
                        break;
                    }
                }
                playMp3("music.mp3", 10);
            }
            else
            {
                cout << "No winner, all players have folded.\n";
            }
        }
        else
        {
            cout << "Not enough players to determine a winner.\n";
        }
        return strongestHand;
    }

    void resetPlayers(vector<Player> &players)
    {
        for (auto &player : players)
        {
            player.currentPlayerBet = 0;
            player.isFolded = false;
            player.isAllIn = false;
            player.cards.clear();
        }
    }

    void updateWinrate(Player &player)
    {
        if (player.numRound > 0)
        {
            player.winrate = (float)player.gamesWon / player.numRound * 100;
        }
        else
        {
            player.winrate = 0.0f;
        }
    }

    void updateFavoriteStrategy(Player &player)
    {
        map<string, int> handCounts = {
            {"Straight Flush", player.cnt_StraightFlush},
            {"Four of a Kind", player.cnt_FourOfAKind},
            {"Full House", player.cnt_FullHouse},
            {"Flush", player.cnt_Flush},
            {"Straight", player.cnt_Straight},
            {"Three of a Kind", player.cnt_ThreeOfAKind},
            {"Two Pair", player.cnt_TwoPair},
            {"One Pair", player.cnt_OnePair},
            {"High Card", player.cnt_HighCard}};

        string favoriteHand = "None";
        int maxCount = 0;

        for (auto it = handCounts.begin(); it != handCounts.end(); ++it)
        {
            if (it->second > maxCount)
            {
                maxCount = it->second;
                favoriteHand = it->first;
            }
        }
        player.commonWinType = favoriteHand;
    }

    void displayLeaderboard(const vector<Player> &players, const vector<Player> &eliminatedPlayers)
    {
        cout << "================================== Leaderboard ===================================\n\n";
        vector<Player> allPlayers = players;
        allPlayers.insert(allPlayers.end(), eliminatedPlayers.begin(), eliminatedPlayers.end());
        sort(allPlayers.begin(), allPlayers.end(), [](const Player &a, const Player &b)
             { return a.gamesWon > b.gamesWon; });

        cout << left << setw(10) << "Player"
             << setw(15) << "Status"
             << setw(10) << "Wins"
             << setw(10) << "Games"
             << setw(10) << "Winrate"
             << setw(10) << "Coins"
             << setw(20) << "Favorite Strategy" << "\n";
        cout << "----------------------------------------------------------------------------------\n";

        for (const auto &player : allPlayers)
        {
            string status = (find(players.begin(), players.end(), player) != players.end()) ? "Active" : "Eliminated";
            cout << setw(10) << stoi(player.name) + 1
                 << setw(15) << status
                 << setw(10) << player.gamesWon
                 << setw(10) << player.numRound;
            if (player.winrate == int(player.winrate))
            {
                cout << setw(10) << player.winrate;
            }
            else
            {
                cout << setw(10) << player.winrate;
            }
            cout << setw(10) << player.coins
                 << setw(20) << player.commonWinType << "\n";
        }
        cout << "----------------------------------------------------------------------------------\n\n\n";
    }

    void playGameOfficial(vector<Player> &players, vector<Player> &eliminatedPlayers)
    {
        resetPlayers(players);
        float pot = 0;
        vector<Card> deck = Deck();
        vector<Card> communityCards;

        int dealerIndex = getDealerIndex(players);
        players[dealerIndex].isDealer = true;

        setTextColor(13);
        preFlop(players, deck, pot, dealerIndex);
        setTextColor(12);
        flop(players, communityCards, deck, pot, dealerIndex);
        setTextColor(11);
        turn(players, communityCards, deck, pot, dealerIndex);
        setTextColor(10);
        river(players, communityCards, deck, pot, dealerIndex);

        if (gameOver)
        {
            for (int i = 0; i < (int)players.size(); ++i)
            {
                if (!players[i].isFolded)
                {
                    cout << "\tPlayer " << stoi(players[i].name) + 1 << " win!\n";
                    ++players[i].gamesWon;
                    players[i].coins += pot;
                    cout << "\tCurrent Player " << stoi(players[i].name) + 1 << "'s amount: " << players[i].coins << ".\n\n";
                }
            }

            auto it = players.begin();
            while (it != players.end())
            {
                if (it->coins == 0)
                {
                    eliminatedPlayers.push_back(*it);
                    it = players.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            for (auto &player : players)
            {
                player.numRound++;
                updateWinrate(player);
                updateFavoriteStrategy(player);
            }

            pot = 0.0;

            if (players.size() == 1)
            {
                cout << "\n=== GAME OVER ===\n";
                cout << "Final Winner: Player " << stoi(players.front().name) + 1 << "!\n";
                displayLeaderboard(players, eliminatedPlayers);
                return;
            }

            dealerIndex = getNextDealerIndex(dealerIndex, players);
            for (auto &player : players)
            {
                player.isDealer = false;
            }
            players[dealerIndex].isDealer = true;

            displayLeaderboard(players, eliminatedPlayers);
            resetPlayers(players);
            return;
        }

        setTextColor(9);
        vector<Card> strongestHand = determineWinnerAfterRiver(players, communityCards, pot);
        playSoundEffect();

        auto it = players.begin();
        while (it != players.end())
        {
            if (it->coins == 0)
            {
                eliminatedPlayers.push_back(*it);
                it = players.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto &player : players)
        {
            player.numRound++;
            updateWinrate(player);
            updateFavoriteStrategy(player);
        }

        pot = 0.0;

        if (players.size() == 1)
        {
            cout << "\n=== GAME OVER ===\n";
            cout << "Final Winner: Player " << stoi(players.front().name) + 1 << "!\n";
            displayLeaderboard(players, eliminatedPlayers);
            return;
        }

        dealerIndex = getNextDealerIndex(dealerIndex, players);
        for (auto &player : players)
        {
            player.isDealer = false;
        }
        players[dealerIndex].isDealer = true;

        displayLeaderboard(players, eliminatedPlayers);
    }

    void solve()
    {
        setTextColor(14);
        bool gameOver = false;
        int numPlayers;
        cout << "Enter number players (2 - 10): ";
        cin >> numPlayers;

        vector<Player> players;
        vector<Player> eliminatedPlayers;
        int dealerIndex = -1;

        for (int i = 0; i < numPlayers; ++i)
        {
            players.push_back({to_string(i), {}, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {}});
        }

        char playAgain;
        do
        {
            fill(begin(selected), end(selected), 0);
            for_each(begin(strongestCards), end(strongestCards), [](vector<Card> &cards)
                     { cards.clear(); });

            playGameOfficial(players, eliminatedPlayers);
            gameOver = false;

            cout << "Do you want to play again? (Y/N): ";
            cin >> playAgain;
        } while (playAgain == 'y' || playAgain == 'Y');
    }
}
