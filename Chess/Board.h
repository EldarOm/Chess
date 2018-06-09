#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"
#include "Piece.h"
#include "Square.h"
#include <vector>
#include <string>


class Board
{
public:
	Board();
	~Board();
	bool performMove(Square* start, Square* destination);
	std::vector<Square*> getPossibleSquares(Square* start);
	std::string getPossibleMoves(Square* start) const;

private:
	void movePiece(Square* start, Square* destination);
	std::vector<Square*> getMoves(Square* start);
	GameState getGameState() const;
	Square* getSquare(BoardFile file, BoardRow row);

	std::vector<Square*> getPawnMoves(Square*);
	std::vector<Square*> getRookMoves(Square*);
	std::vector<Square*> getKnightMoves(Square*);
	std::vector<Square*> getBishopMoves(Square*);
	std::vector<Square*> getQueenMoves(Square*);
	std::vector<Square*> getKingMoves(Square*);

	Square board[8][8];
	Square* enPassantJumpWhite = nullptr;
	Square* enPassantDestinationWhite = nullptr;
	Square* enPassantJumpBlack = nullptr;
	Square* enPassantDestinationBlack = nullptr;

};

#endif // !BOARD_H

