#ifndef TWO_FIVE_HIHI_H
#define TWO_FIVE_HIHI_H

#include <string>
#include <vector>
#include <map>

namespace creation1
{
    // Cấu trúc 1 lá bài
    struct Card
    {
        int Rank;
        int Suit;
    };

    struct Player
    {
        std::string name;
        std::vector<Card> hand;
        float coins;
        bool isFolded;
    };

    // Global variables
    extern int numRounds;
    extern bool gameOver;
    extern int selected[8];
    extern std::vector<Card> strongestCards[5];
    extern std::vector<Player> players;

    // Function declarations
    std::string getRankName(int Rank);
    std::string getSuitName(int Suit);
    std::string getHandName(int handType);
    std::vector<Card> Deck();
    void dealHand(std::vector<Card> &deck, std::vector<Card> &hand, int numCards);
    void dealTwoCards(std::vector<Player> &players, std::vector<Card> &deck);
    void revealPlayerCards(std::vector<Player> &players, int playerIndex);
    void hidePlayerCards(std::vector<Player> &players, int playerIndex);
    void showHiddenCards(const std::vector<Player> &players);
    void revealCommunityCards(std::vector<Card> &communityCards, std::vector<Card> &deck, int numCards);
    int calculatePoints(const std::vector<Card> &hand);
    int evaluateHand(std::vector<Card> hand);
    bool cmp(Card x, Card y);
    int compare(std::vector<Card> p1, std::vector<Card> p2);
    void solveHand(std::vector<Card> &hand, int pos);
    void generateCombinations(int n, int k, std::vector<Card> &hand, int pos);
    void removeBankruptPlayers(std::vector<Player> &players);
    void printHand(const std::vector<Card> &hand);
    std::vector<Card> determineWinner(std::vector<Player> &players, std::vector<Card> &communityCards, float &pot);
    void resetPlayers(std::vector<Player> &players);
    void playGame(std::vector<Player> &players);
    void solve();
}

#endif // TWO_FIVE_HIHI_H
