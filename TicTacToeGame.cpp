#include <iostream>
#include <cstdlib>

class BoardGame
{
protected:
    const int BOARD_SIZE;
    char **board;
    char turn;
    mutable bool isDraw;

public:
    BoardGame(int size) : BOARD_SIZE(size), turn('X'), isDraw(false)
    {
        initializeBoard();
    }

    virtual ~BoardGame()
    {
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
    }

    void clearScreen() const
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif


    }

    void initializeBoard()
    {
        board = new char *[BOARD_SIZE];
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            board[i] = new char[BOARD_SIZE];
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                board[i][j] = '1' + i * BOARD_SIZE + j;
            }
        }
    }

    virtual void displayBoard() const = 0;
    virtual void playerTurn() = 0;
    virtual bool gameover() const = 0;
};

class TicTacToe : public BoardGame
{
private:
    int choice;
    int row, column;

public:
    TicTacToe() : BoardGame(3) {}

    void displayBoard() const override
    {
        clearScreen();
        std::cout << "T I C  -- T A C -- T O E -- G A M E\n";
        std::cout << "FOR 2 PLAYERS\n";
        std::cout << "PLAYER - 1 [X]  PLAYER - 2 [O]\n\n";

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                std::cout << "  " << board[i][j] << " ";
                if (j < BOARD_SIZE - 1)
                    std::cout << "|";
            }
            std::cout << "\n";
            if (i < BOARD_SIZE - 1)
            {
                std::cout << "_____|_____|_____\n";
            }
        }
        std::cout << "\n";
    }

    void playerTurn() override
    {
        std::cout << "Player - " << (turn == 'X' ? "1 [X]" : "2 [O]") << " turn: ";

        while (true)
        {
            std::cin >> choice;

            if (choice < 1 || choice > 9)
            {
                std::cout << "Invalid Move. Please choose a number between 1 and 9.\n";
            }
            else
            {
                row = (choice - 1) / BOARD_SIZE;
                column = (choice - 1) % BOARD_SIZE;

                if (board[row][column] != 'X' && board[row][column] != 'O')
                {
                    board[row][column] = turn;
                    turn = (turn == 'X') ? 'O' : 'X';
                    break;
                }
                else
                {
                    std::cout << "Box already filled! Please choose another.\n";
                }
            }
        }

        displayBoard();
    }

    bool gameover() const override
    {

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] ||
                board[0][i] == board[1][i] && board[0][i] == board[2][i])
            {
                return false;
            }
        }

        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] ||
            board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
            return false;
        }

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    return true;
                }
            }
        }

        isDraw = true;
        return false;
    }

    void playGame()
    {
        while (gameover())
        {
            displayBoard();
            playerTurn();
        }

        if (turn == 'X' && !isDraw)
        {
            std::cout << "\nCongratulations! Player with 'O' has won the game\n";
        }
        else if (turn == 'O' && !isDraw)
        {
            std::cout << "\nCongratulations! Player with 'X' has won the game\n";
        }
        else
        {
            std::cout << "\nGAME DRAW!!!\n";
        }
    }
};

int main()
{
    TicTacToe game;
    game.playGame();

    return 0;
}