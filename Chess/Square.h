#ifndef SQUARE_H
#define SQUARE_H

#include "Constants.h"
#include "Piece.h"
#include <stdio.h>
#include <string>


class Square
{
public:
	Square() = default;

	Square(BoardRow row, BoardFile file, Color color, Piece* piece) {
		this->row = row;
		this->file = file;
		this->color = color;
		this->piece = piece;
	};

	Square(BoardRow row, BoardFile file, Color color) {
		this->row = row;
		this->file = file;
		this->color = color;
		this->piece = nullptr;
	};

	BoardFile getFile() const {
		return this->file;
	};

	BoardRow getRow() const {
		return this->row;
	};

	Color getColor() const {
		return this->color;
	}

	void setPiece(Piece* piece) {
		this->piece = piece;
	};

	Piece* getPiece() {
		return piece;
	};

	std::string toString() const{
		char buffer[10];
		sprintf_s(buffer, "%c%i", (char)this->file, (int)this->row);
		return std::string(buffer);
	}

private:
	BoardRow row;
	BoardFile file;
	Color color;
	Piece* piece;
};


#endif // ! SQUARE_H