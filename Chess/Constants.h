#ifndef CONSTANTS_H
#define CONSTANTS_H

enum class BoardRow { ROW_ONE = 1, ROW_TWO, ROW_THREE, ROW_FOUR, ROW_FIVE, ROW_SIX, ROW_SEVEN, ROW_EIGHT };
enum class BoardFile { FILE_A = 'A', FILE_B = 'B', FILE_C = 'C', FILE_D = 'D', FILE_E = 'E', FILE_F = 'F', FILE_G = 'G', FILE_H = 'H' };
enum class Color {COLOR_WHITE = 'W', COLOR_BLACK='B'};
enum class PieceModel { MODEL_PAWN = 'P', MODEL_ROOK = 'R', MODEL_KNIGHT = 'N', MODEL_BISHOP = 'B', MODEL_QUEEN = 'Q', MODEL_KING = 'K' };
enum class GameState { REGULAR, WHITE_IN_CHECK, BLACK_IN_CHECK, WHITE_MATED, BLACK_MATED, WHITE_IN_STALEMATE, BLACK_IN_STALEMATE};

int f2i(BoardFile file) { return (char)file - (char)BoardFile::FILE_A; };
int r2i(BoardRow row) { return (int)row - 1; };

#endif