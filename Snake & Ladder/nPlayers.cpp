#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player {
private:
    string name;
    int position;
public:
    Player(string playerName) {
        name = playerName;
        position = 0;
    }

    string getName() {
        return name;
    }

    int getPosition() {
        return position;
    }

    void setPosition(int newPosition) {
        position = newPosition;
    }

    void rollDice() {
        int diceRoll = rand() % 6 + 1;
        cout << name << " rolled a " << diceRoll << "." << endl;
        position += diceRoll;
    }
};

class SnakeAndLadderGame {
private:
    vector<Player*> players;
    int boardSize;
    int snakesCount;
    int laddersCount;
    int* snakes;
    int* ladders;
public:
    SnakeAndLadderGame(int size, int numSnakes, int numLadders) {
        boardSize = size;
        snakesCount = numSnakes;
        laddersCount = numLadders;
        snakes = new int[boardSize + 1]; // Use boardSize + 1 to account for 0-based indexing
        ladders = new int[boardSize + 1]; // Use boardSize + 1 to account for 0-based indexing
        for (int i = 0; i <= boardSize; i++) {
            snakes[i] = -1; // -1 indicates no snake at the position
            ladders[i] = -1; // -1 indicates no ladder at the position
        }
    }

    ~SnakeAndLadderGame() {
        delete[] snakes;
        delete[] ladders;
    }

    void setSnake(int position, int tail) {
        snakes[position] = tail;
    }

    void setLadder(int position, int bottom) {
        ladders[position] = bottom;
    }

    void addPlayer(Player* player) {
        players.push_back(player);
    }

    bool isSnake(int position) {
        return snakes[position] != -1;
    }

    bool isLadder(int position) {
        return ladders[position] != -1;
    }

    int getNextPosition(int position) {
        if (isSnake(position)) {
            cout << "Oops! You encountered a snake!" << endl;
            return snakes[position];
        } else if (isLadder(position)) {
            cout << "Great! You found a ladder!" << endl;
            return ladders[position];
        }
        return position;
    }

    void playGame() {
        srand(time(NULL));
        bool gameOver = false;
        while (!gameOver) {
            for (int i = 0; i < players.size(); i++) {
                Player* currentPlayer = players[i];
                cout << currentPlayer->getName() << "'s turn." << endl;
                currentPlayer->rollDice();
                int newPosition = currentPlayer->getPosition();
                if (newPosition > boardSize) {
                    cout << currentPlayer->getName() << " rolled too high. Try again!" << endl;
                    continue;
                }
                newPosition = getNextPosition(newPosition);
                currentPlayer->setPosition(newPosition);
                cout << currentPlayer->getName() << " moved to position " << newPosition << "." << endl;
                if (newPosition == boardSize) {
                    cout << currentPlayer->getName() << " wins!" << endl;
                    gameOver = true;
                    break;
                }
            }
        }
    }
};

int main() {
    int numPlayers;
    int boardSize;
    int numSnakes;
    int numLadders;
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    cout << "Enter the board size: ";
    cin >> boardSize;

    cout << "Enter the number of snakes: ";
    cin >> numSnakes;

    cout << "Enter the number of ladders: ";
    cin >> numLadders;

    SnakeAndLadderGame game(boardSize, numSnakes, numLadders);

    for (int i = 1; i <= numPlayers; i++) {
        string playerName;
        cout << "Enter player " << i << "'s name: ";
        cin >> playerName;
        Player* player = new Player(playerName);
        game.addPlayer(player);
    }

    // Setting up snakes and ladders
    for (int i = 0; i < numSnakes; i++) {
        int snakePosition, snakeTail;
        cout << "Enter the position of snake " << i + 1 << ": ";
        cin >> snakePosition;
        cout << "Enter the tail position of snake " << i + 1 << ": ";
        cin >> snakeTail;
        game.setSnake(snakePosition, snakeTail);
    }

    for (int i = 0; i < numLadders; i++) {
        int ladderPosition, ladderBottom;
        cout << "Enter the position of ladder " << i + 1 << ": ";
        cin >> ladderPosition;
        cout << "Enter the bottom position of ladder " << i + 1 << ": ";
        cin >> ladderBottom;
        game.setLadder(ladderPosition, ladderBottom);
    }

    // Starting the game
    game.playGame();

    return 0;
}

