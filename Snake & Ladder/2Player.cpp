#include<bits/stdc++.h>
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
    Player* players[2];
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
        snakes = new int[snakesCount];
        ladders = new int[laddersCount];
        for (int i = 0; i < snakesCount; i++) {
            snakes[i] = -1; // -1 indicates snake's tail position
        }
        for (int i = 0; i < laddersCount; i++) {
            ladders[i] = -1; // -1 indicates ladder's bottom position
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

    void addPlayer(Player* player, int playerIndex) {
        players[playerIndex] = player;
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
            for (int i = 0; i < 2; i++) {
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
    SnakeAndLadderGame game(100, 3, 3); // Board size: 100 snakes: 3 ladder: 3
        // Setting up snakes and ladders
    game.setSnake(16, 6);
    game.setSnake(47, 26);
    game.setSnake(49, 11);
    game.setLadder(4, 14);
    game.setLadder(9, 31);
    game.setLadder(20, 38);

    // Creating players
    Player player1("Player 1");
    Player player2("Player 2");

    // Adding players to the game
    game.addPlayer(&player1, 0);
    game.addPlayer(&player2, 1);

    // Starting the game
    game.playGame();

    return 0;
}