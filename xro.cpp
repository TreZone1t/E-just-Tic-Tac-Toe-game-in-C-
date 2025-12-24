/*
name : Abdulhakim hamdi abdulgani
ID : 320250201
github url :https://github.com/TreZone1t/E-just-Tic-Tac-Toe-game-in-C-.git
THE REPORT:

1. Game Description:
   This is a Tic-Tac-Toe game developed in C++. It allows a user to play against
   another human or against the Computer (AI). The game features a save/load system
   to store progress and statistics (Wins, Draws, Games played).

2. How to Play:
   - Run the program.
   - Choose '1' to start a game or '2' to exit.
   - Select Game Mode: '1' for 2 Players, '2' for AI Mode.
   - Choose your symbol: 'X', 'O', or 'R' for random.
   - On your turn, enter a number (1-9) corresponding to the grid position.
   - Options during game: Enter 'S' to Save game, or 'E' to Exit.

3. Technical Requirements Implemented:
   - Arrays: A 2D array 'board[3][3]' is used to represent the grid.
   - Pointers: A pointer '*game_stat' is used to track the game state (Win/Draw).
   - File I/O: 'fstream' library is used to Save and Load game history in 'history.txt'.
   - Functions: The code is modular, split into functions like win(), draw(), ai(), etc.

4. AI Algorithm Explanation:
    so the method is by 
    1. searching if the is a two simler symbol are nearby to block them or to win
    2. if there is not the ai() will search to see if there a x or o in the board to block the future move 
    3. if there is a x and an o are nearby there is no danger so the ai() will choose to block anthere cell nearby x
    4. if there is not x or o in the board or it the last move the update() will make the first move randomly and will choose the last cell in the last move
*/

// --- Libraries Section ---
// iostream: Essential for Input/Output (cout, cin).
#include <iostream>
// fstream: Required for File Handling (reading/writing files).
#include <fstream>
// cstdlib: Required for random number generation (rand, srand).
#include <cstdlib>

// Using the standard namespace to avoid typing std:: before cout/cin
using namespace std;

// --- Global Variables (Data Section) ---

// 1. The Game Board
// Type is 'char' to store characters '1' through '9', 'X', and 'O'.
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

// 2. Constants
// declared as 'const' because their values (X and O) should never change during the game.
const char X = 'X', O = 'O';
const int load_game = 1, AI = 2; // Simple integer codes for game modes for easier updates.

// 3. Statistics Variables
// Integers to count game events. Initialized to 0.
int wins = 0;
int draws = 0;
int loses = 0;
int games = 0;
int total_turns = 0;
int last_turn = 0;

// 4. Player  symbols Variables
// Store which character (X or O) belongs to Player 1 and Player 2 (or AI).
char sym1, sym2;
int *game_mode = new int(); // 0 = Player vs Player -pvp- , 2 = Player vs AI
// 5. The Pointer (Requirement)
// i declare a pointer '*game_stat' to store the game result character.
// 'new char()' allocates memory dynamically in the Heap.
// This pointer will hold: 'X'/'O' (Winner), 'D' (Draw), or 0 (Continue).
char *game_stat = new char();

// --- Functions Definitions ---

// Function: print()
// Purpose: clear the console visually and draw the board array.
void print()
{

    // Print new lines to push old content up
    cout << "\n\n";

    // Loop through rows (i from 0 to 2)
    for (int i = 0; i < 3; i++)
    {
        // Top padding for the cell design
        cout << "\t       |       |       \n";

        // Start of the data row
        cout << "\t   ";
        // Loop through columns (j from 0 to 2)
        for (int j = 0; j < 3; j++)
        {
            // Access the array at [row][col] and print the character
            cout << board[i][j];

            // If it's not the last column, print a vertical separator
            if (j < 2)
                cout << "   |   ";
        }
        cout << "\n"; // End of row line

        // Bottom padding
        cout << "\t       |       |       \n";

        // Print a horizontal line separator, but only between rows (not after the last one)
        if (i < 2)
        {
            cout << "\t-------+-------+-------\n";
        }
    }
    cout << "\n\n";
}

// Function: win()
// Purpose: Check the board logic to see if anyone has won.
// It updates the pointer '*game_stat' if a win is found.
void win()
{
    // 1. Check Horizontal Rows
    for (int i = 0; i < 3; i++)
    {
        // If all 3 cells in a row are the same...
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            // Update the value pointed to by game_stat
            if (board[i][0] == X)
                *game_stat = X;
            if (board[i][0] == O)
                *game_stat = O;
        }
    }

    // 2. Check Vertical Columns
    for (int i = 0; i < 3; i++)
    {
        // If all 3 cells in a column are the same...
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == X)
                *game_stat = X;
            if (board[0][i] == O)
                *game_stat = O;
        }
    }

    // 3. Check Main Diagonal (Top-Left to Bottom-Right)
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == X)
            *game_stat = X;
        if (board[0][0] == O)
            *game_stat = O;
    }

    // 4. Check Anti-Diagonal (Top-Right to Bottom-Left)
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == X)
            *game_stat = X;
        if (board[0][2] == O)
            *game_stat = O;
    }
}

// Function: draw()
// Purpose: Check if the game is a draw (board full, no winner).
void draw()
{
    // Iterate through the whole board
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // If any cell contains a digit (1-9), the board is NOT full.
            // In ASCII, characters '0' to '9' are less than or equal to '9'.
            if (board[i][j] <= '9')
            {
                *game_stat = 0; // 0 means game continues
                return;         // Exit function immediately
            }
        }
    }
    // If loop finishes without finding empty spots, it's a Draw.
    *game_stat = 'D'; // Set status to 'D'
}

// Function: reset()
// Purpose: Restore the board to its initial state (numbers 1-9).
void reset()
{
    char num = '1'; // Start character
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = num++; // Assign current char then increment it (1, 2, 3...)
        }
    }
    *game_stat = 0; // Reset game status
}

// Function: choose()
// Purpose: Handle character selection (X or O) and randomness.
void choose()
{
    if (*game_mode == 0) // PvP Mode
    {
        cout << "\n\t [ CHARACTER SELECTION ]\n";
        cout << "\t Choose your symbol (x / o) or (r) for random\n";
        cout << "\t Your choice > ";

        char symbol;
        cin >> symbol; // Take input

        if (symbol == 'X' || symbol == 'x')
        {
            sym1 = X;
            sym2 = O;
            cout << "\n\t You selected X. Player 2 is O.\n";
        }
        else if (symbol == 'O' || symbol == 'o')
        {
            sym1 = O;
            sym2 = X;
            cout << "\n\t You selected O. Player 2 is X.\n";
        }
        else // Random choice logic
        {
            // rand() % 2 generates either 0 or 1
            int random = rand() % 2;
            if (random == 0)
            {
                sym1 = X;
                sym2 = O;
                cout << "\n\t Randomly assigned: You are X\n";
            }
            else
            {
                sym1 = O;
                sym2 = X;
                cout << "\n\t Randomly assigned: You are O\n";
            }
        }
    }
    else // AI Mode
    {
        // Always assign randomly in AI mode for fairness
        int random = rand() % 2;
        if (random == 0)
        {
            sym1 = X;
            sym2 = O;
            cout << "\n\t Randomly assigned: You are X\n";
        }
        else
        {
            sym1 = O;
            sym2 = X;
            cout << "\n\t Randomly assigned: You are O\n";
        }
    }
}

// Function: save()
// Purpose: Write game data to "history.txt" using ofstream.
void save()
{
    // Create an output file stream
    ofstream file("history.txt");
    if (file.is_open())
    {
        // Write statistics separated by spaces
        file << games << " " << wins << " " << draws << " " << total_turns << " " << last_turn << " " << sym1 << " " << sym2 << " ";
        // Loop to write the entire board state
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                file << board[i][j] << " ";
            }
        }
        file.close(); // Close file to save changes
        cout << "\n\t >> Game saved successfully! <<\n";
    }
    else
    {
        cout << "\n\t >>  Could not save game. <<\n";
    }
}

// Function: load()
// Purpose: Read game data from "history.txt" using ifstream.
void load()
{
    // Create an input file stream
    ifstream file("history.txt");
    if (file.is_open())
    {
        // Read variables in the exact same order they were saved
        file >> games;
        file >> wins;
        file >> draws;
        file >> total_turns;
        file >> last_turn;
        file >> sym1;
        file >> sym2;

        // Calculate loses based on games and draws
        loses = games - draws;

        bool data_corrupted = false;

        // Validation: Check if symbols are valid characters
        if ((sym1 != 'X' && sym1 != 'O' && sym1 != 'x' && sym1 != 'o') ||
            (sym2 != 'X' && sym2 != 'O' && sym2 != 'x' && sym2 != 'o'))
        {
            data_corrupted = true;
        }

        int det = 0;
        // Load the board array
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                file >> board[i][j];
                // Validation: Board cells must be '1'-'9', 'X', or 'O'
                if (board[i][j] <= '9' && board[i][j] >= '1')
                    det++;
                else if (board[i][j] != 'X' && board[i][j] != 'O')
                    data_corrupted = true;
            }
        }

        // If file reading failed or data looks wrong, stop loading
        if (file.fail() || data_corrupted)
        {
            file.close();
            return;
        }

        // Check the state of the loaded game
        win();
        draw();

        // If loaded game is already finished, reset board for a new game
        if (*game_stat != 0)
        {
            reset();
        }

        file.close();
    }
}

// Function: input()
// Purpose: Handle user input for moves (1-9) or commands (E).
void input(char symbol)
{
    char in; // Variable to store single character input
    int move = '0';
    while (true) // Infinite loop until valid input is given
    {
        cin >> in; // Read input

        // Switch statement to map input char to board position
        switch (in)
        {
        case '1':
            move = 1;
            break;
        case '2':
            move = 2;
            break;
        case '3':
            move = 3;
            break;
        case '4':
            move = 4;
            break;
        case '5':
            move = 5;
            break;
        case '6':
            move = 6;
            break;
        case '7':
            move = 7;
            break;
        case '8':
            move = 8;
            break;
        case '9':
            move = 9;
            break;
        // Case for Exit commands
        case 'E':
        case 'e':
            save();
            exit(0); // Using the exit(0) to exit with no error (0)
        default:
            cout << "\t Invalid move. Enter a number between 1-9: ";
            break; // Restart loop
        }

        if (move != '0')
        {

            // Convert move (1-9) to Array Indices (Row 0-2, Col 0-2)
            // Formula: Row = (n-1)/3, Col = (n-1)%3
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            // Check if the cell is already occupied
            if (board[row][col] == X || board[row][col] == O)
            {
                cout << "\t Cell already taken. Choose another: ";
            }
            else
            {
                // Update board and break the loop
                board[row][col] = symbol;
                break;
            }
        }
    }
}

// Function: update()
// Purpose: Update the board for the AI's move.
void update(char symbol, int move ,int turn)
{
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;
    if (turn == 0)
    {
         move = rand() % 10 + 1;
    }
    
    // Safety check (should not happen with correct AI logic)
    if (board[row][col] == X || board[row][col] == O)
    {
        // Linearly find the first empty spot
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] <= '9')
                {
                    board[i][j] = symbol;
                    return; // Exit after placing
                }
            }
        }
    }
    else
    {
        // Place symbol normally
        board[row][col] = symbol;
    }
}

// Function: ai()
// Purpose: Determine the best move for the Computer.
// Returns an integer (1-9) representing the move.
int ai()
{
    char targets[2] = {sym1, sym2}; // sym1 is Player, sym2 is AI

    // Loop twice:
    // k=0: Check if 'sym1' (Player) is winning -> Block them.
    // k=1: Check if 'sym2' (AI) is winning -> Win the game.
    for (int k = 0; k < 2; k++)
    {
        char c = targets[k];
        char op = (c == X) ? O : X;

        // Phase 1: Check Rows, Columns, Diagonals logic
        for (int i = 0; i < 3; i++)
        {
            // Check Rows: If 2 are 'c' and 3rd is empty ('<=9'), return empty spot
            if (board[i][0] == c && board[i][1] == c && board[i][2] <= '9')
                return i * 3 + 3;
            if (board[i][0] == c && board[i][2] == c && board[i][1] <= '9')
                return i * 3 + 2;
            if (board[i][1] == c && board[i][2] == c && board[i][0] <= '9')
                return i * 3 + 1;

            // Check Columns
            if (board[0][i] == c && board[1][i] == c && board[2][i] <= '9')
                return 2 * 3 + i + 1;
            if (board[0][i] == c && board[2][i] == c && board[1][i] <= '9')
                return 1 * 3 + i + 1;
            if (board[1][i] == c && board[2][i] == c && board[0][i] <= '9')
                return 0 * 3 + i + 1;

            // Check Diagonals
            if (board[0][0] == c && board[1][1] == c && board[2][2] <= '9')
                return 9;
            if (board[0][0] == c && board[2][2] == c && board[1][1] <= '9')
                return 5;
            if (board[1][1] == c && board[2][2] == c && board[0][0] <= '9')
                return 1;

            if (board[0][2] == c && board[1][1] == c && board[2][0] <= '9')
                return 7;
            if (board[0][2] == c && board[2][0] == c && board[1][1] <= '9')
                return 5;
            if (board[1][1] == c && board[2][0] == c && board[0][2] <= '9')
                return 3;
        }

        // Phase 2: Strategic Patterns (Hardcoded Logic)
        // If opponent is in a corner or edge, pick a specific counter-move.
        if (board[0][0] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[0][1] <= '9' && board[0][2] <= '9')
                    return 2;
            case 2:
                if (board[1][0] <= '9' && board[2][0] <= '9')
                    return 4;
            case 3:
                if (board[1][1] <= '9' && board[2][2] <= '9')
                    return 5;
            }
        }
        // ... (Repeating similar logic for other cells to check availability)
        if (board[0][1] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[1][1] <= '9' && board[2][1] <= '9')
                    return 5;
            case 2:
                if (board[0][0] <= '9' && board[0][2] <= '9')
                    return 1;
            case 3:
                if (board[0][2] <= '9' && board[0][0] <= '9')
                    return 3;
            }
        }
        if (board[0][2] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[0][1] <= '9' && board[0][0] <= '9')
                    return 2;
            case 2:
                if (board[1][2] <= '9' && board[2][2] <= '9')
                    return 6;
            case 3:
                if (board[1][1] <= '9' && board[2][0] <= '9')
                    return 5;
            }
        }
        if (board[1][0] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[1][1] <= '9' && board[1][2] <= '9')
                    return 5;
            case 2:
                if (board[0][0] <= '9' && board[2][0] <= '9')
                    return 1;
            case 3:
                if (board[2][0] <= '9' && board[0][0] <= '9')
                    return 7;
            }
        }
        // Center Strategy (most complex, tries to surround)
        if (board[1][1] == c)
        {
            int ran = rand() % 8 + 1;
            switch (ran)
            {
            case 1:
                if (board[0][0] <= '9' && board[2][2] != op)
                    return 1;
            case 2:
                if (board[0][1] <= '9' && board[2][1] != op)
                    return 2;
            case 3:
                if (board[0][2] <= '9' && board[2][0] != op)
                    return 3;
            case 4:
                if (board[1][0] <= '9' && board[1][2] != op)
                    return 4;
            case 5:
                if (board[1][2] <= '9' && board[1][0] != op)
                    return 6;
            case 6:
                if (board[2][0] <= '9' && board[0][2] != op)
                    return 7;
            case 7:
                if (board[2][1] <= '9' && board[0][1] != op)
                    return 8;
            case 8:
                if (board[2][2] <= '9' && board[0][0] != op)
                    return 9;
            }
        }
        if (board[1][2] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[1][1] <= '9' && board[1][0] <= '9')
                    return 5;
            case 2:
                if (board[0][2] <= '9' && board[2][2] <= '9')
                    return 3;
            case 3:
                if (board[2][2] <= '9' && board[0][2] <= '9')
                    return 9;
            }
        }
        if (board[2][0] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[2][1] <= '9' && board[2][2] <= '9')
                    return 8;
            case 2:
                if (board[1][0] <= '9' && board[0][0] <= '9')
                    return 4;
            case 3:
                if (board[1][1] <= '9' && board[0][2] <= '9')
                    return 5;
            }
        }
        if (board[2][1] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[1][1] <= '9' && board[0][1] <= '9')
                    return 5;
            case 2:
                if (board[2][0] <= '9' && board[2][2] <= '9')
                    return 7;
            case 3:
                if (board[2][2] <= '9' && board[2][0] <= '9')
                    return 9;
            }
        }
        if (board[2][2] == c)
        {
            int ran = rand() % 3 + 1;
            switch (ran)
            {
            case 1:
                if (board[2][1] <= '9' && board[2][0] <= '9')
                    return 8;
            case 2:
                if (board[1][2] <= '9' && board[0][2] <= '9')
                    return 6;
            case 3:
                if (board[1][1] <= '9' && board[0][0] <= '9')
                    return 5;
            }
        }
    }

    // Phase 3: Fallback (Random/First Available)
    // If no strategic move was found, just pick the first empty cell.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] <= '9')
            {
                return ((i * 3) + 1);
            }
        }
    }
    return 0;
}

// Function: play()
// Purpose: Main game loop. Controls turns, calls functions, handles end game.
void play()
{
    int turn = 0;
    choose();    // Set up X and O
    while (true) // Infinite loop until break
    {
        print(); // Draw Board

        cout << "\t ----------------------------------- \n";
        cout << "\t Turn: " << turn + 1 << "\n";
        cout << "\t ----------------------------------- \n";

        // Determine current player (Even turn = X, Odd turn = O)
        int current_sym;
        if (turn % 2 == 0)
            current_sym = X;
        else
            current_sym = O;

        // Check if it's the User's turn
        bool is_your_turn = (current_sym == sym1);

        if (is_your_turn) // User Turn
        {
            cout << "\t [Options]:To Save and Exit Enter (E) \n";
            if (sym1 == X)
                cout << "\t >> X's turn. Enter move (1-9): ";
            else
                cout << "\t >> O's turn. Enter move (1-9): ";

            input(sym1);
        }
        else // AI (or Player 2) Turn
        {
            if (*game_mode == AI)
            {
                cout << "\t >> AI is thinking...\n";
                int move = ai();    // Get AI move
                update(sym2, move,turn); // Apply move
            }
            else // 2 Player Mode
            {
                if (sym2 == X)
                    cout << "\t >> X's turn. Enter move (1-9): ";
                else
                    cout << "\t >> O's turn. Enter move (1-9): ";
                input(sym2);
            }
        }

        // Check for Win
        win();
        if (*game_stat != 0) // If game_stat is set (X or O)
        {
            print();
            cout << "\n\t *********************************** \n";
            if (*game_stat == X)
                cout << "\t * X  WINS !             * \n";
            else if (*game_stat == O)
                cout << "\t * O  WINS !             * \n";
            cout << "\t *********************************** \n\n";

            // Update stats
            if ((*game_stat == X && sym1 == X) || (*game_stat == O && sym1 == O))
                wins++;

            games++;
            total_turns += turn + 1;
            save(); // Save stats
            break;  // End Game
        }

        // Check for Draw
        draw();
        if (*game_stat != 0 && *game_stat != X && *game_stat != O)
        {
            print();
            cout << "\n\t *********************************** \n";
            cout << "\t * IT'S A DRAW !         * \n";
            cout << "\t *********************************** \n\n";
            games++;
            total_turns += turn + 1;
            save();
            break;
        }

        turn++; // Next turn
    }

    // Important: Delete dynamically allocated memory to prevent leaks
    delete game_stat;
    game_stat = nullptr;
    delete game_mode;
    game_mode = nullptr;
}

// Function: start()
// Purpose: Ask user to load old game or start new.
void start()
{
    char choice;
    cout << "\n\t ----------------------------------- \n";
    cout << "\t Load previous game? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        *game_mode = load_game;
        play();
    }
    else
    {
        reset();
        play();
    }
}

// Function: game()
// Purpose: Display Main Menu and stats.
void game()
{
    load(); // Load previous stats on startup
    *game_mode = 0;
    cout << "\n";
    cout << "\t ......................................... \n";
    cout << "\t :             TIC TAC TOE               : \n";
    cout << "\t :.......................................: \n";
    cout << "\n";

    cout << "\t +-------------- STATS ------------------+ \n";
    cout << "\t |  Total Games  : " << games << "\t\t\t | \n";
    cout << "\t |  Total Wins   : " << wins << "\t\t\t | \n";
    cout << "\t +---------------------------------------+ \n";
    cout << "\n";

    cout << "\t [ MAIN MENU ] \n";
    cout << "\t  1. Start New Game \n";
    cout << "\t  2. Exit Game \n";
    cout << "\n";
    cout << "\t Select option > ";

    int option;
    cin >> option;

    if (option == 1)
    {
        // Sub-menu for Game Mode
        cout << "\n";
        cout << "\t ......................................... \n";
        cout << "\t :           CHOOSE GAME MODE            : \n";
        cout << "\t :.......................................: \n";
        cout << "\n";
        cout << "\t  1. Player vs Player (2 Players)\n";
        cout << "\t  2. Player vs Computer (AI Mode)\n";
        cout << "\n";
        cout << "\t Select mode > ";

        int gmode;
        cin >> gmode;
        if (gmode == 2)
        {
            *game_mode = AI;
        }
        start();
    }
    else
    {
        cout << "\n\t Thanks for playing! \n\n";
        return;
    }
}

// Function: main()
// Purpose: Entry point of the program.
int main()
{
    game();
    return 0;
}
