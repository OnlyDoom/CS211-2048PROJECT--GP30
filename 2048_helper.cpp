
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>

#include "2048_helper.h"

using namespace std;

// --------------------------------------------------
// Private helper function: move one row to the left.
// --------------------------------------------------
namespace
{
    bool move_line_left(int line[5], int& points_gained)
    {
        int original[5];

        // Save the original row so we can compare it later.
        for (int i = 0; i < 5; i++)
        {
            original[i] = line[i];
        }

        // Copy all nonzero tiles into a temporary array.
        int compact[5] = {};
        int count = 0;

        for (int i = 0; i < 5; i++)
        {
            if (line[i] != 0)
            {
                compact[count] = line[i];
                count++;
            }
        }

        // Merge matching neighboring tiles.
        int result[5] = {};
        int result_index = 0;
        int i = 0;

        while (i < count)
        {
            if (i + 1 < count && compact[i] == compact[i + 1])
            {
                // Merge two equal tiles into one larger tile.
                result[result_index] = compact[i] * 2;

                // Add the new tile's value to the score.
                points_gained += result[result_index];

                // Skip both tiles so neither merges again.
                i += 2;
            }
            else
            {
                // No matching neighbor: keep this tile.
                result[result_index] = compact[i];
                i++;
            }

            result_index++;
        }

        // Copy the result back into the original row.
        for (int j = 0; j < 5; j++)
        {
            line[j] = result[j];
        }

        // Report whether the row changed.
        for (int j = 0; j < 5; j++)
        {
            if (line[j] != original[j])
            {
                return true;
            }
        }

        return false;
    }
}

// --------------------------------------------------
// Move every row to the left.
// --------------------------------------------------
bool move_left(int board[][5], int numrows, int& points_gained)
{
    points_gained = 0;
    bool board_changed = false;

    for (int row = 0; row < numrows; row++)
    {
        if (move_line_left(board[row], points_gained))
        {
            board_changed = true;
        }
    }

    return board_changed;
}

// --------------------------------------------------
// Move every row to the right.
// --------------------------------------------------
bool move_right(int board[][5], int numrows, int& points_gained)
{
    points_gained = 0;
    bool board_changed = false;

    for (int row = 0; row < numrows; row++)
    {
        // Reverse the row.
        for (int left = 0, right = 4; left < right;
             left++, right--)
        {
            int temp = board[row][left];
            board[row][left] = board[row][right];
            board[row][right] = temp;
        }

        // Move the reversed row to the left.
        if (move_line_left(board[row], points_gained))
        {
            board_changed = true;
        }

        // Reverse the row again to restore its direction.
        for (int left = 0, right = 4; left < right;
             left++, right--)
        {
            int temp = board[row][left];
            board[row][left] = board[row][right];
            board[row][right] = temp;
        }
    }

    return board_changed;
}

// --------------------------------------------------
// Move every column upward.
// --------------------------------------------------
bool move_up(int board[][5], int numrows, int& points_gained)
{
    points_gained = 0;
    bool board_changed = false;

    for (int col = 0; col < 5; col++)
    {
        // Copy the column into a temporary row.
        int line[5];

        for (int row = 0; row < numrows; row++)
        {
            line[row] = board[row][col];
        }

        // Move the temporary row to the left.
        if (move_line_left(line, points_gained))
        {
            board_changed = true;
        }

        // Copy the result back into the column.
        for (int row = 0; row < numrows; row++)
        {
            board[row][col] = line[row];
        }
    }

    return board_changed;
}

// --------------------------------------------------
// Move every column downward.
// --------------------------------------------------
bool move_down(int board[][5], int numrows, int& points_gained)
{
    points_gained = 0;
    bool board_changed = false;

    for (int col = 0; col < 5; col++)
    {
        // Copy the column into a temporary row in reverse order.
        int line[5];

        for (int row = 0; row < numrows; row++)
        {
            line[row] = board[numrows - 1 - row][col];
        }

        // Move the reversed column to the left.
        if (move_line_left(line, points_gained))
        {
            board_changed = true;
        }

        // Copy the result back in reverse order.
        for (int row = 0; row < numrows; row++)
        {
            board[numrows - 1 - row][col] = line[row];
        }
    }

    return board_changed;
}

// --------------------------------------------------
// Print the board.
// --------------------------------------------------
void print_board(int board[][5], int numrows)
{
    cout << "\n";

    for (int row = 0; row < numrows; row++)
    {
        cout << "+------+------+------+------+------+\n";

        for (int col = 0; col < 5; col++)
        {
            if (board[row][col] == 0)
            {
                cout << "|" << setw(6) << " ";
            }
            else
            {
                cout << "|" << setw(6) << board[row][col];
            }
        }

        cout << "|\n";
    }

    cout << "+------+------+------+------+------+\n";
}

// --------------------------------------------------
// Insert a random tile with value 2 into an empty cell.
// Return false if the board has no empty cells.
// --------------------------------------------------
bool insert_random(int board[][5], int numrows)
{
    int empty_count = 0;

    // Count the empty cells.
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (board[row][col] == 0)
            {
                empty_count++;
            }
        }
    }

    // No empty cells means no tile can be inserted.
    if (empty_count == 0)
    {
        return false;
    }

    // Generate a random empty-cell position.
    static mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(0, empty_count - 1);

    int target = distribution(generator);
    int current_empty = 0;

    // Find the selected empty cell and insert a 2.
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (board[row][col] == 0)
            {
                if (current_empty == target)
                {
                    board[row][col] = 2;
                    return true;
                }

                current_empty++;
            }
        }
    }

    return false;
}

// --------------------------------------------------
// Display the available commands.
// --------------------------------------------------
void show_help()
{
    cout << "\n2048 COMMANDS\n";
    cout << "u - Move up\n";
    cout << "d - Move down\n";
    cout << "l - Move left\n";
    cout << "r - Move right\n";
    cout << "s - Save game\n";
    cout << "o - Open/load saved game\n";
    cout << "n - Start a new game\n";
    cout << "h - Show help\n";
    cout << "e - Exit game\n";
}

// --------------------------------------------------
// Check whether any tile is at least 2048.
// --------------------------------------------------
bool has_won(int board[][5], int numrows)
{
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (board[row][col] >= 2048)
            {
                return true;
            }
        }
    }

    return false;
}

// --------------------------------------------------
// Check whether the board is full and no moves remain.
// --------------------------------------------------
bool is_game_over(int board[][5], int numrows)
{
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            // An empty cell means the game is not over.
            if (board[row][col] == 0)
            {
                return false;
            }

            // Check the tile to the right.
            if (col + 1 < 5 &&
                board[row][col] == board[row][col + 1])
            {
                return false;
            }

            // Check the tile below.
            if (row + 1 < numrows &&
                board[row][col] == board[row + 1][col])
            {
                return false;
            }
        }
    }

    // The board is full and has no adjacent matching tiles.
    return true;
}

// --------------------------------------------------
// Save the game to savegame.txt.
// --------------------------------------------------
bool save_game(int board[][5], int numrows,
               int score, int successful_moves)
{
    ofstream file("savegame.txt");

    if (!file.is_open())
    {
        return false;
    }

    file << "CS211_2048_V1\n";
    file << score << " " << successful_moves << "\n";

    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            file << board[row][col];

            if (col < 4)
            {
                file << " ";
            }
        }

        file << "\n";
    }

    file.close();

    return !file.fail();
}

// --------------------------------------------------
// Load and validate a saved game.
// Do not change the current game unless loading succeeds.
// --------------------------------------------------
bool load_game(int board[][5], int numrows,
               int& score, int& successful_moves)
{
    ifstream file("savegame.txt");

    if (!file.is_open())
    {
        return false;
    }

    string marker;
    int loaded_score;
    int loaded_moves;
    int loaded_board[5][5];

    // Check the save-file version marker.
    if (!(file >> marker) || marker != "CS211_2048_V1")
    {
        return false;
    }

    // Read and validate the score and move count.
    if (!(file >> loaded_score >> loaded_moves))
    {
        return false;
    }

    if (loaded_score < 0 || loaded_moves < 0)
    {
        return false;
    }

    // Read and validate all 25 board cells.
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (!(file >> loaded_board[row][col]))
            {
                return false;
            }

            int tile = loaded_board[row][col];

            // A valid tile is zero or a power of two >= 2.
            if (tile != 0 &&
                (tile < 2 || (tile & (tile - 1)) != 0))
            {
                return false;
            }
        }
    }

    // Reject extra content after the 25 board cells.
    string extra_content;

    if (file >> extra_content)
    {
        return false;
    }

    if (!file.eof())
    {
        return false;
    }

    // Only now is it safe to replace the current game.
    for (int row = 0; row < numrows; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            board[row][col] = loaded_board[row][col];
        }
    }

    score = loaded_score;
    successful_moves = loaded_moves;

    return true;
}
