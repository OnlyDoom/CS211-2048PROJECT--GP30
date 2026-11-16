#include <iostream>
#include <cctype>
#include "2048_helper.h"
#include <iostream>
#include <cctype>
#include "2048_helper.h"

using namespace std;

int main()
{
    // Board dimensions
    const int SIZE = 5;

    // Game information
    int board[SIZE][SIZE] = {};
    int score = 0;
    int successful_moves = 0;
    bool win_announced = false;

    // Start a new game by inserting two tiles.
    insert_random(board, SIZE);
    insert_random(board, SIZE);

    // Display the starting board and game information.
    cout << "Welcome to 2048!\n";
    print_board(board, SIZE);
    cout << "Score: " << score << '\n';
    cout << "Successful moves: " << successful_moves << '\n';

    // Find and display the highest tile.
    int highest_tile = 0;

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] > highest_tile)
            {
                highest_tile = board[row][col];
            }
        }
    }

    cout << "Highest tile: " << highest_tile << '\n';

    // Announce a win if the starting board already has a winning tile.
    if (has_won(board, SIZE))
    {
        cout << "Congratulations! You reached 2048 or higher!\n";
        win_announced = true;
    }

    // Main game loop.
    char choice;

    while (true)
    {
        cout << "\nEnter a command (h for help): ";

        // Stop safely if the input ends.
        if (!(cin >> choice))
        {
            cout << "\nInput ended. Exiting game.\n";
            break;
        }

        // Allow uppercase and lowercase commands.
        choice = static_cast<char>(
            tolower(static_cast<unsigned char>(choice))
        );

        // Show help.
        if (choice == 'h')
        {
            show_help();
            continue;
        }

        // Save the current game.
        if (choice == 's')
        {
            if (save_game(board, SIZE, score, successful_moves))
            {
                cout << "Game saved to savegame.txt.\n";
            }
            else
            {
                cout << "Error: Could not save the game.\n";
            }

            continue;
        }

        // Load a previously saved game.
        if (choice == 'o')
        {
            if (load_game(board, SIZE, score, successful_moves))
            {
                cout << "Game loaded successfully.\n";

                // Display the restored game.
                print_board(board, SIZE);
                cout << "Score: " << score << '\n';
                cout << "Successful moves: "
                     << successful_moves << '\n';

                highest_tile = 0;

                for (int row = 0; row < SIZE; row++)
                {
                    for (int col = 0; col < SIZE; col++)
                    {
                        if (board[row][col] > highest_tile)
                        {
                            highest_tile = board[row][col];
                        }
                    }
                }

                cout << "Highest tile: " << highest_tile << '\n';

                // Avoid repeating the win announcement for an
                // already-winning saved game.
                win_announced = has_won(board, SIZE);

                if (win_announced)
                {
                    cout << "This game has already reached 2048 or higher!\n";
                }

                if (is_game_over(board, SIZE))
                {
                    cout << "Game over! No more moves are possible.\n";
                }
            }
            else
            {
                cout << "Error: The save file is missing or invalid. "
                     << "Your current game was not changed.\n";
            }

            continue;
        }

        // Start a new game after confirmation.
        if (choice == 'n')
        {
            char confirmation;

            cout << "Start a new game? Your current game will be lost. "
                 << "(y/n): ";

            if (!(cin >> confirmation))
            {
                cout << "\nInput ended. Exiting game.\n";
                break;
            }

            confirmation = static_cast<char>(
                tolower(static_cast<unsigned char>(confirmation))
            );

            if (confirmation == 'y')
            {
                // Reset every board cell to zero.
                for (int row = 0; row < SIZE; row++)
                {
                    for (int col = 0; col < SIZE; col++)
                    {
                        board[row][col] = 0;
                    }
                }

                // Reset the game statistics.
                score = 0;
                successful_moves = 0;
                win_announced = false;

                // Add two starting tiles.
                insert_random(board, SIZE);
                insert_random(board, SIZE);

                cout << "\nNew game started!\n";
                print_board(board, SIZE);
                cout << "Score: " << score << '\n';
                cout << "Successful moves: "
                     << successful_moves << '\n';

                highest_tile = 0;

                for (int row = 0; row < SIZE; row++)
                {
                    for (int col = 0; col < SIZE; col++)
                    {
                        if (board[row][col] > highest_tile)
                        {
                            highest_tile = board[row][col];
                        }
                    }
                }

                cout << "Highest tile: " << highest_tile << '\n';
            }
            else if (confirmation == 'n')
            {
                cout << "Continuing the current game.\n";
            }
            else
            {
                cout << "Invalid confirmation. Current game unchanged.\n";
            }

            continue;
        }

        // Exit the game.
        if (choice == 'e')
        {
            cout << "Thanks for playing 2048!\n";
            break;
        }

        // Check whether the player entered a movement command.
        if (choice != 'u' && choice != 'd' &&
            choice != 'l' && choice != 'r')
        {
            cout << "Invalid command. Enter h to see the commands.\n";
            continue;
        }

        // A game-over board cannot be moved.
        if (is_game_over(board, SIZE))
        {
            cout << "Game over! You cannot move this board anymore.\n";
            cout << "You can still save, load, start a new game, "
                 << "view help, or exit.\n";
            continue;
        }

        // Store the score earned from this move.
        int points_gained = 0;

        // Perform the requested movement.
        bool board_changed = false;

        if (choice == 'l')
        {
            board_changed = move_left(board, SIZE, points_gained);
        }
        else if (choice == 'r')
        {
            board_changed = move_right(board, SIZE, points_gained);
        }
        else if (choice == 'u')
        {
            board_changed = move_up(board, SIZE, points_gained);
        }
        else if (choice == 'd')
        {
            board_changed = move_down(board, SIZE, points_gained);
        }

        // Only successful moves change the score and move count
        // or create a new tile.
        if (board_changed)
        {
            score += points_gained;
            successful_moves++;

            insert_random(board, SIZE);
        }
        else
        {
            cout << "The board did not change. No new tile was added.\n";
        }

        // Display the board and statistics after the movement attempt.
        print_board(board, SIZE);
        cout << "Score: " << score << '\n';
        cout << "Successful moves: " << successful_moves << '\n';

        highest_tile = 0;

        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                if (board[row][col] > highest_tile)
                {
                    highest_tile = board[row][col];
                }
            }
        }

        cout << "Highest tile: " << highest_tile << '\n';

        // Announce the win once, but allow the game to continue.
        if (has_won(board, SIZE) && !win_announced)
        {
            cout << "Congratulations! You reached 2048 or higher!\n";
            cout << "You can continue playing.\n";
            win_announced = true;
        }

        // Check whether the player has any legal moves left.
        if (is_game_over(board, SIZE))
        {
            cout << "Game over! No more moves are possible.\n";
            cout << "Your final score is " << score << ".\n";
        }
    }

    return 0;
}