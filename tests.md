# CS 211 Project 1 — 2048 Game Tests

## 1. Purpose

This document records the tests performed on the 2048 game, including the expected results and observed results.

## 2. Test Results

| Test | Action | Expected Result | Observed Result | Status |
|---|---|---|---|---|
| T01 | Compile and run the program | Program compiles and starts without errors | Program compiled and launched successfully | PASS |
| T02 | Start a new game | A 5×5 board appears with two 2 tiles, score 0, and 0 successful moves | Two 2 tiles appeared in different cells; score and moves were 0 | PASS |
| T03 | Display help using `h` | Available commands are displayed | Help menu displayed the commands | PASS |
| T04 | Enter an invalid command | Program rejects the command and continues | Invalid command message appeared | PASS |
| T05 | Make a valid movement | Tiles move according to the selected direction | Movement was performed successfully | PASS |
| T06 | Merge equal tiles | Equal adjacent tiles merge and score increases | Score increased during gameplay; highest tile reached 4 | PASS |
| T07 | Save using `s` | Current game is saved to `savegame.txt` | Program reported that the game was saved | PASS |
| T08 | Load using `o` | Saved board, score, and move count are restored | Loading succeeded and restored saved game data | PASS |
| T09 | Start a new game and confirm with `y` | Board and counters reset; two new 2 tiles appear | New game started with two 2 tiles, score 0, and 0 moves | PASS |
| T10 | Cancel a new game by entering `n` at the confirmation prompt | Current game remains unchanged | Program displayed "Continuing the current game." A subsequent unsuccessful move confirmed the original board, score (32), and move count (13) were preserved | PASS |
| T11 | Exit using `e` | Program displays an exit message and terminates | "Thanks for playing 2048!" appeared | PASS |
| T12 | Attempt to load an invalid save file | Load fails and current game remains unchanged | Current score remained 4, successful moves remained 3, and highest tile remained 4 after the invalid-file test | PASS |
| T13 | Restart the program and load a valid save | Saved game data is restored | Game launched again and loading worked | PASS |
| T14 | Reach a tile of 2048 | Program announces the win and allows continued play | Loaded a board containing 2048. Program announced the win, accepted a right movement, moved the tiles, and added a new tile | PASS |
| T15 | Fill the board with no possible merges | Game announces game over and blocks movement commands | Loaded a full 5×5 board with no adjacent matching tiles. Program displayed the Game Over message and rejected the `l` movement command | PASS |
| T16 | Attempt an unsuccessful move | Board, score, and move count remain unchanged, with no new tile inserted | Board remained unchanged; score stayed 32, moves stayed 13, and no new tile was added | PASS |

## 3. Save File Format

The save file uses the following structure:

1. File marker: `CS211_2048_V1`
2. Score and successful move count on the second line.
3. Five rows containing five integer values each.

Example:

```text
CS211_2048_V1
4 3
0 0 0 0 0
0 2 0 0 0
0 0 0 0 0
4 0 0 0 0
2 0 2 0 0
```

The values above are an example of the format, not a required game state.

## 4. Conclusion

The program successfully compiled and launched. All 16 tests passed. Basic gameplay, movement, scoring, help, invalid-command handling, saving, loading, starting a new game, exiting, win detection, game-over detection, unsuccessful moves, and canceling a new game were tested successfully.

The tests also confirmed that invalid save files do not overwrite the current game state and that the game can continue after reaching a tile of 2048.