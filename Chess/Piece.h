#ifndef PIECE_H
#define PIECE_H

#include "Constants.h"

class Piece
{
public:
	Piece(Color color) { this->color = color; };
	virtual PieceModel getPieceModel() const = 0;
	Color getColor() const { return color; };

protected:
	Color color;
};

class Pawn : public Piece {
public:
	Pawn(Color color) : Piece(color) {};
	virtual PieceModel getPieceModel() const { return PieceModel::MODEL_PAWN; };
};

class Rook : public Piece {
public:
	Rook(Color color) : Piece(color) {};
	virtual PieceModel getPieceModel() const { return PieceModel::MODEL_ROOK; };
};

class Bishop : public Piece {
public:
	Bishop(Color color) : Piece(color) {};
	virtual PieceModel getPieceModel() const { return PieceModel::MODEL_BISHOP; };
};

class Knight : public Piece {
public:
	Knight(Color color) : Piece(color) {};
	virtual PieceModel getPieceModel() const { return PieceModel::MODEL_KNIGHT; };
};

class Queen : public Piece {
public:
	Queen(Color color) : Piece(color) {};
	virtual PieceModel getPieceModel() const { return PieceModel::MODEL_QUEEN; };
};

class King : public Piece {
public:
	King(Color color) : Piece(color) {};
	virtual PieceModel getPieceModel() const { return PieceModel::MODEL_KING; };
};

#endif // ! PIECE_H