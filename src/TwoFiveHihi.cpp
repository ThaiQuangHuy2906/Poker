// TwoFiveHihi.cpp - Implementation file

#include "../include/TwoFiveHihi.h"
#include "../include/Utils.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <random>

using namespace std;

namespace creation1
{

    int numRounds = 0;              // Số trận chơi
    bool gameOver = false;          // Game kết thúc
    int selected[8];                // Mảng đánh dấu: đánh dấu các lá bài nào trong bộ bài được chọn
    vector<Card> strongestCards[5]; // Lưu trữ các bộ bài mạnh nhất của các người chơi từ sau mỗi vòng cược
    vector<Player> players;         // Khởi tạo mảng người chơi cố định

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

    // Hàm tạo và xóa bộ bài
    vector<Card> Deck()
    {
        vector<Card> deck; // Khởi tạo bộ bài

        for (int i = 0; i <= 3; ++i) // 4 chất: bích, chuồn, rô, cơ
        {
            for (int j = 2; j <= 14; ++j) // 13 giá trị của bộ bài: 2, ..., 10, J, Q, K, A
            {
                deck.push_back({j, i}); // Thêm lá bài vào bộ bài
            }
        }

        // Trộn bộ bài bằng std::shuffle và bộ sinh số ngẫu nhiên hiện đại
        random_device rd;                     // Thiết bị sinh số ngẫu nhiên
        mt19937 g(rd());                      // Bộ sinh số ngẫu nhiên Mersenne Twister
        shuffle(deck.begin(), deck.end(), g); // Trộn bộ bài

        return deck; // Trả về bộ bài đã trộn
    }

    // Hàm chia bài cho người chơi (nhận 3 tham số)
    // deck: Tham chiếu đến một vector chứa các lá bài đại diện cho bộ bài (deck)
    // hand: Tham chiếu đến một vector chứa các lá bài đại diện cho tay bài của người chơi (hand)
    // numCards : Số lượng lá bài cần chia cho tay bài của người chơi
    void dealHand(vector<Card> &deck, vector<Card> &hand, int numCards)
    {
        for (int i = 0; i < numCards; ++i) // Số lượng lá bài cần chia
        {
            hand.push_back(deck.back()); // Thêm lá bài vừa truy cập ở cuối bộ bài vào vector tay bài của người chơi (hand)
            deck.pop_back();             // Xóa lá bài cuối cùng của bộ bài (deck) sau khi đã chia lá bài đó cho người chơi
        }
        return;
    }

    // Hàm chia 2 lá bài cho người chơi và lưu vào tay bài của họ
    void dealTwoCards(vector<Player> &players, vector<Card> &deck)
    {
        for (auto &player : players)
        {
            dealHand(deck, player.hand, 2); // Chia 2 lá bài cho người chơi
        }
    }

    // Hàm mở bài khi tới lượt của người chơi
    void revealPlayerCards(vector<Player> &players, int playerIndex)
    {
        cout << "Player " << stoi(players[playerIndex].name) + 1 << "'s cards: \n";
        for (const auto &card : players[playerIndex].hand)
        {
            cout << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << '\n'; // Hiển thị bài người chơi
        }
    }

    // Hàm đóng bài của người chơi khi hết lượt
    void hidePlayerCards(vector<Player> &players, int playerIndex)
    {
        // Thông báo ẩn lại bài
        cout << "Player " << stoi(players[playerIndex].name) + 1 << "'s cards are hidden again.\n\n";
    }

    // Hàm hiển thị bài ẩn của người chơi trong Terminal
    void showHiddenCards(const vector<Player> &players)
    {
        for (const auto &player : players)
        {
            cout << "Player " << stoi(player.name) + 1 << "'s cards: [X] [X]\n"; // Hiển thị bài ẩn của người chơi
        }
        cout << "\n";
    }

    // Lật bài chung
    void revealCommunityCards(vector<Card> &communityCards, vector<Card> &deck, int numCards)
    {
        for (int i = 0; i < numCards; ++i)
        {
            communityCards.push_back(deck.back());
            deck.pop_back();
        }
    }

    // Tính điểm bài theo Nút
    int calculatePoints(const vector<Card> &hand)
    {
        int totalPoints = 0;
        for (const Card &card : hand)
        {
            if (card.Rank >= 2 && card.Rank <= 10)
            {
                totalPoints += card.Rank;
            }
            else if (card.Rank == 14)
            {
                totalPoints += 1;
            }
            else
            {
                totalPoints += 10;
            }
        }
        return totalPoints % 10;
    }

    // Hàm tính giá trị của một tay bài theo Poker
    int evaluateHand(vector<Card> hand)
    {

        if ((int)hand.size() == 0) // Nếu tay bài rỗng, trả về giá trị 0
        {
            return 9;
        }
        map<int, int> rankCount; // Khởi tạo một map để đếm số lần xuất hiện của từng HẠNG bài
        map<int, int> suitCount; // Khởi tạo một map để đếm số lần xuất hiện của từng CHẤT bài
        vector<int> num;         // Khởi tạo một vector để lưu trữ HẠNG bài

        for (const auto &card : hand) // Vòng lặp qua từng lá bài trong tay bài
        {
            rankCount[card.Rank]++;   // Tăng đếm số lần xuất hiện của HẠNG bài
            suitCount[card.Suit]++;   // Tăng đếm số lần xuất hiện của CHẤT bài
            num.push_back(card.Rank); // Thêm HẠNG bài vào vector num
        }

        sort(num.begin(), num.end()); // Sắp xếp HẠNG bài

        bool isFlush = ((int)suitCount.size() == 1);                              // Cùng Chất
        bool isStraight = ((int)rankCount.size() == 5 && (num[4] - num[0] == 4)); // Tạo thành Sảnh
        bool isFourofaKind = false;                                               // Tứ quý
        bool isThreeofaKind = false;                                              // Bộ ba
        bool isTwoPair = false;                                                   // Hai đôi
        bool isOnePair = false;                                                   // Một đôi

        for (auto card : rankCount) // Vòng lặp qua từng hạng bài trong rankCount
        {
            if (card.second == 4)
                isFourofaKind = true; // Kiểm tra tứ quý
            if (card.second == 3)
                isThreeofaKind = true; // Kiểm tra bộ ba
            if (card.second == 2)      // Kiểm tra 2 đôi hay 1 đôi
            {
                if (isOnePair)
                    isTwoPair = true;
                else
                    isOnePair = true;
            }
        }
        bool isFullHouse = (isThreeofaKind && isOnePair); // Kiểm tra cù lũ (Bộ ba và 1 đôi)

        if (isFlush && isStraight)
            return 8; // Thùng phá sảnh
        if (isFourofaKind)
            return 7; // Tứ quý
        if (isFullHouse)
            return 6; // Cù lũ
        if (isFlush)
            return 5; // Thùng
        if (isStraight)
            return 4; // Sảnh
        if (isThreeofaKind)
            return 3; // Bộ ba
        if (isTwoPair)
            return 2; // 2 đôi
        if (isOnePair)
            return 1; // 1 đôi
        return 0;     // Bài cao hơn thì win
    }

    // Hàm kiểm tra hạng bài cao hơn
    bool cmp(Card x, Card y) // Compare Rank
    {
        return (x.Rank < y.Rank);
    }

    // Hàm so sánh 2 tay bài, người 1 > người 2 thì trả về Đúng
    int compare(vector<Card> p1, vector<Card> p2)
    {
        if ((int)p2.size() == 0) // Nếu bài thằng 2 rỗng thì trả về 1
            return 1;

        map<int, int> numCount; // Khởi tạo một map để đếm số lần xuất hiện của mỗi hạng bài trong tay bài

        for (int i = 0; i < 5; ++i) // Đếm số lần xuất hiện của mỗi hạng bài trong tay bài thằng 1
            ++numCount[p1[i].Rank];

        int Four1 = 0, Three1 = 0, Two1 = 0, One1 = 0, Alone1 = 0; // Khởi tạo các biến để lưu trữ giá trị của tứ quý, bộ ba, hai đôi, một đôi và lá bài đơn lẻ cho p1
        int Four2 = 0, Three2 = 0, Two2 = 0, One2 = 0, Alone2 = 0; // bộ ba, hai đôi, một đôi và lá bài đơn lẻ cho thằng 1 và 2

        // Kiểm tra và lưu trữ giá trị của tứ quý, bộ ba, hai đôi, một đôi và lá bài đơn lẻ cho thằng 1
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

        // map và lặp lại quá trình tương tự cho thằng 2
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

        // Tính giá trị của hai thằng 1 và 2
        int value1 = evaluateHand(p1); // Giá trị bài thằng 1
        int value2 = evaluateHand(p2); // Giá trị bài thằng 2

        if (value2 < value1) // Nếu thằng 2 < thằng 1 thì trả về giá trị Đúng
            return 1;
        else if (value2 == value1)
        {
            if (value1 == 4 || value1 == 8)
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
            else if (value1 == 7)
            {
                if (Four2 < Four1)
                {
                    return 1;
                }
                else if (Four2 > Four1)
                {
                    return 2;
                }
                return 0;
            }
            else if (value1 == 6 || value1 == 3)
            {
                if (Three2 < Three1)
                {
                    return 1;
                }
                else if (Three2 > Three1)
                {
                    return 2;
                }
                return 0;
            }
            else if (value1 == 5 || value1 == 0)
            {
                for (int i = 4; i >= 0; --i)
                {
                    if (p2[i].Rank < p1[i].Rank)
                    {
                        return 1;
                    }
                    if (p2[i].Rank > p1[i].Rank)
                    {
                        return 2;
                    }
                }
                return 0;
            }
            else if (value1 == 2)
            {
                if (Two2 < Two1)
                {
                    return 1;
                }
                else if (Two2 == Two1)
                {
                    if (One2 < One1)
                    {
                        return 1;
                    }
                    else if (One2 == One1)
                    {
                        if (Alone2 < Alone1)
                        {
                            return 1;
                        }
                        else if (Alone2 > Alone1)
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
                if (One2 < One1)
                {
                    return 1;
                }
                else if (One2 == One1)
                {
                    vector<int> stupid;
                    vector<int> noob;
                    for (int i = 0; i < 5; ++i)
                    {
                        if (p1[i].Rank != One1)
                        {
                            stupid.push_back(p1[i].Rank);
                        }
                        if (p2[i].Rank != One2)
                        {
                            noob.push_back(p2[i].Rank);
                        }
                    }
                    for (int i = 2; i >= 0; --i)
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

    // Tạo ra một danh sách các lá bài đã chọn từ tay bài (hand), sắp xếp chúng và
    // cập nhật danh sách các lá bài mạnh nhất nếu bộ mới mạnh hơn
    // hand: Tham chiếu đến một vector chứa các lá bài đại diện cho tay bài của người chơi
    // pos : Chỉ số vị trí của người chơi trong danh sách những người chơi
    void solveHand(vector<Card> &hand, int pos)
    {
        vector<Card> choosen;  // Khởi tạo một vector choosen để lưu trữ các lá bài được chọn từ tay bài
        int count = 0;         // Khởi tạo biến đếm count với giá trị ban đầu là 0
        for (Card card : hand) // Vòng lặp qua từng lá bài trong tay bài hand
        {
            ++count;
            if (selected[count])         // Kiểm tra xem lá bài tại vị trí count có được chọn không (dựa trên mảng selected đã khai báo ở cục bộ)
                choosen.push_back(card); // Thêm lá bài đó vào vector choosen
        }
        sort(choosen.begin(), choosen.end(), cmp); // Sắp xếp các lá bài trong vector choosen theo thứ tự hạng tăng dần bằng cách sử dụng hàm so sánh cmp
        if (compare(choosen, strongestCards[pos])) // Gọi hàm compare để so sánh vector choosen và strongestCards[pos]
            strongestCards[pos] = choosen;         // Gán choosen cho strongestCards[pos]
        return;
    }

    // Hàm duyệt tổ hợp các lá bài (tạo ra tất cả các tổ hợp có 5 lá từ 7 lá
    // và gọi hàm solve để xử lý từng tổ hợp
    // n	: Chỉ số hiện tại trong quá trình duyệt các lá bài
    // k	: Số lượng lá bài hiện tại trong tổ hợp được chọn
    // hand	: Tham chiếu đến vector chứa các lá bài của tay bài người chơi
    // pos	: Chỉ số vị trí của người chơi trong danh sách những người chơi
    void generateCombinations(int n, int k, vector<Card> &hand, int pos)
    {
        if (k == 5)
        {
            solveHand(hand, pos); // Xử lý tổ hợp 5 lá bài mạnh nhất
            return;
        }
        if (n > 7)
            return; // Nếu đã duyệt hết 7 lá bài mà chưa chọn đủ 5 lá bài, kết thúc hàm
        for (int i = 0; i <= 1; ++i)
        {
            selected[n] = i; // Đánh dấu lá bài được chọn
            if (i)
            {
                generateCombinations(n + 1, k + 1, hand, pos); // Chọn lá bài
            }
            else
            {
                generateCombinations(n + 1, k, hand, pos); // Bỏ qua lá bài
            }
            selected[n] = 0; // Reset sau mỗi lần duyệt
        }
    }

    // Hàm xóa người chơi hết tiền
    void removeBankruptPlayers(vector<Player> &players)
    {
        players.erase(remove_if(players.begin(), players.end(), [](const Player &player)
                                {
                                    return player.coins == 0; // Loại bỏ người chơi có coins = 0
                                }),
                      players.end());
    }

    void printHand(const vector<Card> &hand)
    {
        for (const auto &card : hand)
        {
            cout << "\t" << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << endl;
        }
        cout << "\n";
    }

    vector<Card> determineWinner(vector<Player> &players, vector<Card> &communityCards, float &pot)
    {
        vector<Card> strongestHand;
        int activePlayers = 0;
        int winningHandType = -1; // Lưu loại hand thắng
        vector<Player *> winners; // Danh sách người thắng

        // Tạo tay bài hoàn chỉnh cho mỗi người chơi bằng cách kết hợp bài riêng và bài chung
        for (int i = 0; i < (int)players.size(); ++i)
        {
            if (!players[i].isFolded) // Nếu người chơi không bỏ bài
            {
                activePlayers++; // Số người chơi tăng lên 1

                // Kết hợp bài riêng và bài chung
                vector<Card> fullHand = players[i].hand;                                       // Sao chép nội dung của players[i].cards vào fullHand
                fullHand.insert(fullHand.end(), communityCards.begin(), communityCards.end()); // Thêm các lá bài chung (communityCards) vào cuối fullHand

                // Tạo các tổ hợp bài mạnh nhất
                generateCombinations(1, 0, fullHand, i); // Tạo ra các tổ hợp bài mạnh nhất cho người chơi tại vị trí i
                memset(selected, 0, sizeof(selected));   // Đặt lại tất cả giá trị trong mảng selected về 0

                int handType = evaluateHand(strongestCards[i]); // Tính giá trị tay bài mạnh nhất

                // In thông tin tay bài để debug
                cout << "Player " << stoi(players[i].name) + 1 << "'s strongest hand: \n";
                printHand(strongestCards[i]);
                cout << "Hand type: " << getHandName(handType) << "\n\n";

                if (winners.empty() || compare(strongestCards[i], strongestHand) == 1)
                {
                    winners.clear(); // Xóa danh sách cũ nếu có tay bài mạnh hơn
                    winners.push_back(&players[i]);
                    strongestHand = strongestCards[i];
                    winningHandType = handType;
                }
                else if (compare(strongestCards[i], strongestHand) == 0)
                {
                    winners.push_back(&players[i]); // Hòa bài, thêm người chơi vào danh sách
                }
            }
        }

        setTextColor(6);
        // Kiểm tra nếu có đủ 2 người chơi
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
                    }

                    // Cộng pot chia đều cho người thắng
                    float share = pot / (int)winners.size();
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

                        // Cộng pot cho người thắng
                        winPlayer->coins += pot;
                        cout << "\tCurrent Player " << stoi(winPlayer->name) + 1 << "'s amount: " << winPlayer->coins << ".\n\n";
                    }
                }
                // Phát nhạc trong 10s để chúc mừng người chiến thắng
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

    // Hàm reset dữ liệu người chơi
    void resetPlayers(vector<Player> &players)
    {
        for (auto &player : players)
        {
            player.hand.clear();
        }
    }

    // Hàm bắt đầu game
    void playGame(vector<Player> &players)
    {
        resetPlayers(players);
        // Khởi tạo lại Pot = 0 mỗi trận;
        float pot = 0;
        vector<Card> deck = Deck();
        vector<Card> communityCards;

        // Phát 2 lá cho từng nguời chơi và hiển thị ra màn hình lá bài ẩn
        dealTwoCards(players, deck);
        showHiddenCards(players);

        int agreeCount = 0;

        for (int i = 0; i < players.size(); ++i)
        {
            char agree;
            revealPlayerCards(players, i);
            cout << "Player " << i + 1 << " , do you agree to play by button scoring rules? (Y/N): ";
            cin >> agree;
            if (agree == 'y' || agree == 'Y')
            {
                agreeCount++;
            }
            hidePlayerCards(players, i);
        }

        if (agreeCount >= (1.0 * players.size() / 2))
        {
            // Chơi theo luật tính điểm bằng nút
            setTextColor(1);
            cout << "==== Play by button scoring rules ====\n\n"
                 << "Betting is in process\n";

            for (int i = 0; i < players.size(); ++i)
            {
                players[i].coins -= 300;
                pot += 300;
                cout << "Current player " << i + 1 << "'s amount: " << players[i].coins << endl;
            }
            cout << "\n";

            vector<int> points;
            for (int i = 0; i < players.size(); ++i)
            {
                int point = calculatePoints(players[i].hand);
                points.push_back(point);
                cout << "Player " << i + 1 << " has " << point << " points." << endl;
            }

            int maxPoints = *max_element(points.begin(), points.end());
            vector<int> winners;
            for (int i = 0; i < players.size(); ++i)
            {
                if (points[i] == maxPoints)
                {
                    winners.push_back(i);
                }
            }
            setTextColor(4);
            if (winners.size() > 1)
            {
                cout << "Multiple players with the same button. Split the bet equally." << endl;
                float share = pot / (int)winners.size();
                for (int winner : winners)
                {
                    players[winner].coins += share;
                    cout << "Player " << winner + 1 << " got " << share << " chip." << endl;
                }
            }
            else
            {
                int winner = winners[0];
                players[winner].coins += pot;
                cout << "Player " << winner + 1 << " won with " << maxPoints << " points and got " << pot << " chip." << endl;
            }
            cout << '\n';
        }
        else
        {
            // Chơi theo luật Poker Texas Hold'em
            setTextColor(1);
            cout << "Play by Poker Texas Hold'em rules\n";
            revealCommunityCards(communityCards, deck, 5); // Lật 5 lá bài chung
            setTextColor(2);
            cout << "Community Cards: \n";
            for (const Card &card : communityCards)
            {
                cout << getRankName(card.Rank) << " of " << getSuitName(card.Suit) << "\n";
            }
            cout << endl;

            // Người chơi cược
            for (int i = 0; i < players.size(); ++i)
            {
                players[i].coins -= 300;
                pot += 300;
                cout << "Current player " << i + 1 << "'s amount: " << players[i].coins << endl;
            }
            cout << "\n";

            setTextColor(3);
            // Xác định người chiến thắng và lấy bộ bài mạnh nhất
            vector<Card> strongestHand = determineWinner(players, communityCards, pot);

            // Reset pot sau khi xác định người thắng
            pot = 0;

            // Loại bỏ người chơi hết tiền
            removeBankruptPlayers(players);

            // Kiểm tra nếu chỉ còn một người chơi
            if (players.size() <= 1)
            {
                cout << "Game over! Winner is " << players.front().name << "!\n";
                gameOver = true;
            }
        }
    }

    void solve()
    {
        int numPlayers;
        setTextColor(14);
        cout << "Enter number players (2-10): ";
        cin >> numPlayers;

        vector<Player> players;

        // Khởi tạo dữ liệu người chơi
        for (int i = 0; i < numPlayers; ++i)
        {
            players.push_back({to_string(i), {}, 10000.0, false});
        }

        char playAgain; // Biến có tiếp tục chơi hay không?
        do
        {
            // Xóa mảng selected
            fill(begin(selected), end(selected), 0);
            for_each(begin(strongestCards), end(strongestCards), [](vector<Card> &cards)
                     { cards.clear(); });

            playGame(players); // Tiếp tục trò chơi

            gameOver = false; // Cập nhật lại gameOver

            setTextColor(14);
            cout << "Do you want to play again? (Y/N): ";
            cin >> playAgain;

        } while (playAgain == 'y' || playAgain == 'Y');
    }
}
