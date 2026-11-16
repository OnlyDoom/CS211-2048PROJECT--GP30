
#ifndef GAME2048_HELPER_H
#define GAME2048_HELPER_H

// Movement functions
bool move_left(int board[][5], int numrows, int& points_gained);
bool move_right(int board[][5], int numrows, int& points_gained);
bool move_up(int board[][5], int numrows, int& points_gained);
bool move_down(int board[][5], int numrows, int& points_gained);

// Board display and random tile insertion
void print_board(int board[][5], int numrows = 5);
bool insert_random(int board[][5], int numrows = 5);

// Help command
void show_help();

// Win and game-over checks
bool has_won(int board[][5], int numrows = 5);
bool is_game_over(int board[][5], int numrows = 5);

// Save and load functions
bool save_game(int board[][5], int numrows,
               int score, int successful_moves);

bool load_game(int board[][5], int numrows,
               int& score, int& successful_moves);

#endif
