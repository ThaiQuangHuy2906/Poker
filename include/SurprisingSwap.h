#ifndef SURPRISING_SWAP_H
#define SURPRISING_SWAP_H

#include <string>
#include <vector>
#include <map>

namespace creation2
{
    struct Card
    {
        int Rank;
        int Suit;
    };

    struct player
    {
        std::string name;
        std::vector<Card> cards;
        int coins;
        int bet;
    };

    // Function declarations
    std::vector<Card> Deck();
    void deal(std::vector<Card> &deck, std::vector<Card> &hand);
    int evaluate(std::vector<Card> hand);
    bool cmp(Card x, Card y);
    int compare(std::vector<Card> p1, std::vector<Card> p2);
    std::string getRankName(int Rank);
    std::string getSuitName(int Suit);
    std::string getHandName(int handType);
    long long Rand(long long L, long long R);
    void playGame();
    void solve();
}

#endif // SURPRISING_SWAP_H
