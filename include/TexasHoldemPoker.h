#ifndef TEXAS_HOLDEM_POKER_H
#define TEXAS_HOLDEM_POKER_H

#include <string>
#include <vector>
#include <map>

namespace TexasHoldemPoker
{
    // Cấu trúc 1 lá bài
    struct Card
    {
        int Rank; // Hạng
        int Suit; // Chất
    };

    // Cấu trúc 1 người chơi
    struct Player
    {
        std::string name;
        std::vector<Card> cards;
        float coins;
        float currentPlayerBet;
        bool isFolded;
        bool isAllIn;
        bool isDealer;
        int numRound;
        float winrate;
        int rank;
        int gamesWon;
        int cnt_StraightFlush;
        int cnt_FourOfAKind;
        int cnt_FullHouse;
        int cnt_Flush;
        int cnt_Straight;
        int cnt_ThreeOfAKind;
        int cnt_TwoPair;
        int cnt_OnePair;
        int cnt_HighCard;
        std::string commonWinType;

        bool operator==(const Player &other) const;
    };

    // Cấu trúc 1 bàn chơi
    struct Table
    {
        float pot;
        std::vector<Card> communityCards;
        int currentBet;
        int dealerIndex;
    };

    // Global variables
    extern bool gameOver;
    extern int numRounds;
    extern int ante;
    extern int selected[8];
    extern std::vector<Card> strongestCards[5];
    extern std::vector<Player> players;

    // Function declarations
    std::string getRankName(int Rank);
    std::string getSuitName(int Suit);
    std::string getHandName(int handType);
    void collectAnte(std::vector<Player> &players, float &pot);
    int getDealerIndex(const std::vector<Player> &players);
    int getNextDealerIndex(int currentDealerIndex, const std::vector<Player> &players);
    std::vector<Card> Deck();
    void dealHand(std::vector<Card> &deck, std::vector<Card> &hand, int numCards);
    void dealTwoCards(std::vector<Player> &players, std::vector<Card> &deck);
    void showHiddenCards(const std::vector<Player> &players);
    void revealPlayerCards(std::vector<Player> &players, int playerIndex);
    void hidePlayerCards(std::vector<Player> &players, int playerIndex);
    int evaluate(std::vector<Card> hand);
    bool cmp(Card x, Card y);
    int compare(std::vector<Card> p1, std::vector<Card> p2);
    void solveHand(std::vector<Card> &hand, int pos);
    void generateCombinations(int n, int k, std::vector<Card> &hand, int pos);
    void burnCard(std::vector<Card> &deck);
    void revealCommunityCards(std::vector<Card> &communityCards, std::vector<Card> &deck, int numCards);
    void showCommunityCards(const std::vector<Card> &communityCards);
    void handleAction(Player &player, float &pot, float &currentBet);
    void processBettingRound(std::vector<Player> &players, float &pot, int startPlayer, float &currentBet, bool &gameOver);
    void preFlop(std::vector<Player> &players, std::vector<Card> &deck, float &pot, int &dealerIndex);
    void flop(std::vector<Player> &players, std::vector<Card> &communityCards, std::vector<Card> &deck, float &pot, int &dealerIndex);
    void turn(std::vector<Player> &players, std::vector<Card> &communityCards, std::vector<Card> &deck, float &pot, int &dealerIndex);
    void river(std::vector<Player> &players, std::vector<Card> &communityCards, std::vector<Card> &deck, float &pot, int &dealerIndex);
    void printHand(const std::vector<Card> &hand);
    std::vector<Card> determineWinnerAfterRiver(std::vector<Player> &players, std::vector<Card> &communityCards, float &pot);
    void resetPlayers(std::vector<Player> &players);
    void updateWinrate(Player &player);
    void updateFavoriteStrategy(Player &player);
    void displayLeaderboard(const std::vector<Player> &players, const std::vector<Player> &eliminatedPlayers);
    void playGameOfficial(std::vector<Player> &players, std::vector<Player> &eliminatedPlayers);
    void solve();
}

#endif // TEXAS_HOLDEM_POKER_H
