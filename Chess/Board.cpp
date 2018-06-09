#include "Board.h"
#include "Constants.h"
#include "Piece.h"
#include "Square.h"
#include <iostream>
#include <vector>
#include <string>

void Board::movePiece(Square* start, Square* destination) {
	//sanity check, technically doesn't need to be here (there's gonna be checks at the appropriate places)
	if (start->getPiece == nullptr) {
		std::cout << "Error: no piece on the starting square, hence no move can be performed" << std::endl;
		return;
	}
		
	if (destination->getPiece() != nullptr)
		delete destination->getPiece();

	destination->setPiece(start->getPiece());
	start->setPiece(nullptr);
}

Square* Board::getSquare(BoardFile file, BoardRow row) {
	return &board[r2i(row)][f2i(file)];
}

std::vector<Square*> Board::getMoves(Square* start) {
	PieceModel pieceModel = start->getPiece()->getPieceModel();

	switch (pieceModel){
		case PieceModel::MODEL_PAWN:
			return getPawnMoves(start);
			break;
		case PieceModel::MODEL_ROOK:
			return getRookMoves(start);
			break;
		case PieceModel::MODEL_KNIGHT:
			return getKnightMoves(start);
			break;
		case PieceModel::MODEL_BISHOP:
			return getBishopMoves(start);
			break;
		case PieceModel::MODEL_QUEEN:
			return getQueenMoves(start);
			break;
		case PieceModel::MODEL_KING:
			return getKingMoves(start);
			break;
		default:
			break;
	}

	return std::vector<Square*>();
};

std::vector<Square*> Board::getPawnMoves(Square* start) {
	std::vector<Square*> destinations;
	int row = r2i(start->getRow());
	int file = f2i(start->getFile());

	//possible squares for a white pawn - not including game state checks
	if (start->getPiece()->getColor() == Color::COLOR_WHITE) {
		if (board[row + 1][file].getPiece() == nullptr) {
			destinations.push_back(&board[row + 1][file]);
			
			if (start->getRow() == BoardRow::ROW_TWO && board[row + 2][file].getPiece() == nullptr)
				destinations.push_back(&board[row + 1][file]);
		}

		if ((file > 0) && (board[row + 1][file - 1].getPiece()->getColor() == Color::COLOR_BLACK || &board[row + 1][file - 1] == enPassantJumpBlack))
			destinations.push_back(&board[row + 1][file - 1]);

		if ((file < 7) && (board[row + 1][file + 1].getPiece()->getColor() == Color::COLOR_BLACK || &board[row + 1][file + 1] == enPassantJumpBlack))
			destinations.push_back(&board[row + 1][file + 1]);
	}
	else {
		if (board[row + 1][file].getPiece() == nullptr){
			destinations.push_back(&board[row - 1][file]);

			if (start->getRow() == BoardRow::ROW_SEVEN && board[row - 2][file].getPiece() == nullptr)
				destinations.push_back(&board[row + 1][file]);
		}

		if ((file > 0) && (board[row - 1][file - 1].getPiece()->getColor() == Color::COLOR_WHITE || &board[row - 1][file - 1] == enPassantJumpWhite))
				destinations.push_back(&board[row + 1][file - 1]);

		if ((file < 7) && (board[row - 1][file + 1].getPiece()->getColor() == Color::COLOR_WHITE || &board[row - 1][file + 1] == enPassantJumpWhite))
			destinations.push_back(&board[row + 1][file + 1]);
	}

	return destinations;
};

std::vector<Square*> Board::getRookMoves(Square* start) {
	std::vector<Square*> destinations;
	int row = r2i(start->getRow());
	int file = f2i(start->getFile());
	Piece* blockingPiece = nullptr;
	Color pieceColor = start->getPiece()->getColor();
	
	//possible moves for a rook - not including game state checks
	for (int i = row + 1; i <= 7; ++i) {
		blockingPiece = board[i][file].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[i][file]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[i][file]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}

	for (int i = row - 1; i >= 0; --i) {
		blockingPiece = board[i][file].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[i][file]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[i][file]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}

	for (int i = file + 1; i <= 7; ++i) {
		blockingPiece = board[row][i].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[row][i]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[row][i]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}

	for (int i = file - 1; i >= 0; --i) {
		blockingPiece = board[row][i].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[row][i]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[row][i]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}

	return destinations;
};


std::vector<Square*> Board::getKnightMoves(Square* start) {
	std::vector<Square*> destinations;
	int row = r2i(start->getRow());
	int file = f2i(start->getFile());
	Piece* blockingPiece = nullptr;
	Color pieceColor = start->getPiece()->getColor();

	int destinationRow, destinationFile;

	destinationRow = row + 2, destinationFile = file + 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row + 1, destinationFile = file + 2;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	destinationRow = row + 2, destinationFile = file - 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row + 1, destinationFile = file - 2;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	destinationRow = row - 2, destinationFile = file + 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row - 1, destinationFile = file + 2;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	destinationRow = row - 2, destinationFile = file - 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row - 1, destinationFile = file - 2;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	return destinations;
};
std::vector<Square*> Board::getBishopMoves(Square* start) {
	std::vector<Square*> destinations;
	int row = r2i(start->getRow());
	int file = f2i(start->getFile());
	Piece* blockingPiece = nullptr;
	Color pieceColor = start->getPiece()->getColor();

	//possible moves for a rook - not including game state checks
	for (int i = row + 1, int j = file + 1; i <= 7 && j <= 7; ++i, ++j) {
		blockingPiece = board[i][j].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[i][j]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[i][j]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}

	for (int i = row + 1, int j = file - 1; i <= 7 && j >= 0; ++i, --j) {
		blockingPiece = board[i][j].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[i][j]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[i][j]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}


	for (int i = row - 1, int j = file + 1; i >= 0 && j <= 7; --i, ++j) {
		blockingPiece = board[i][j].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[i][j]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[i][j]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}


	for (int i = row - 1, int j = file - 1; i >= 0 && j >= 0; --i, --j) {
		blockingPiece = board[i][j].getPiece();
		if (blockingPiece == nullptr)
			destinations.push_back(&board[i][j]);
		else if (blockingPiece->getColor != pieceColor) {
			destinations.push_back(&board[i][j]);
			break;
		}
		else if (blockingPiece->getColor == pieceColor)
			break;
	}

	return destinations;
};
std::vector<Square*> Board::getQueenMoves(Square* start) {
	std::vector<Square*> rookMoves = getRookMoves(start);
	std::vector<Square*> bishopMoves = getBishopMoves(start);

	rookMoves.insert(rookMoves.end(), bishopMoves.begin(), bishopMoves.end());

	return rookMoves;
};

std::vector<Square*> Board::getKingMoves(Square* start) {
	std::vector<Square*> destinations;
	int row = r2i(start->getRow());
	int file = f2i(start->getFile());
	Piece* blockingPiece = nullptr;
	Color pieceColor = start->getPiece()->getColor();

	int destinationRow, destinationFile;

	destinationRow = row + 1, destinationFile = file;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row + 1, destinationFile = file + 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row + 1, destinationFile = file - 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	destinationRow = row, destinationFile = file + 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row, destinationFile = file - 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	destinationRow = row - 1, destinationFile = file;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row - 1, destinationFile = file + 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}
	destinationRow = row - 1, destinationFile = file - 1;
	if (destinationFile <= 7 && destinationFile >= 0 && destinationRow <= 7 && destinationRow >= 0) {
		blockingPiece = board[destinationRow][destinationFile].getPiece();
		if (blockingPiece == nullptr || (blockingPiece->getColor() != pieceColor))
			destinations.push_back(&board[destinationRow][destinationFile]);
	}

	//TODO: build casteling moves support

	return destinations;
};

Board::Board() {
	//The first rank/row goes here, this is for the white pieces
	board[0][0] = Square(BoardRow::ROW_ONE, BoardFile::FILE_A, Color::COLOR_BLACK, new Rook(Color::COLOR_WHITE));
	board[0][1] = Square(BoardRow::ROW_ONE, BoardFile::FILE_B, Color::COLOR_WHITE, new Knight(Color::COLOR_WHITE));
	board[0][2] = Square(BoardRow::ROW_ONE, BoardFile::FILE_C, Color::COLOR_BLACK, new Bishop(Color::COLOR_WHITE));
	board[0][3] = Square(BoardRow::ROW_ONE, BoardFile::FILE_D, Color::COLOR_WHITE, new Queen(Color::COLOR_WHITE));
	board[0][4] = Square(BoardRow::ROW_ONE, BoardFile::FILE_E, Color::COLOR_BLACK, new King(Color::COLOR_WHITE));
	board[0][5] = Square(BoardRow::ROW_ONE, BoardFile::FILE_F, Color::COLOR_WHITE, new Bishop(Color::COLOR_WHITE));
	board[0][6] = Square(BoardRow::ROW_ONE, BoardFile::FILE_G, Color::COLOR_BLACK, new Knight(Color::COLOR_WHITE));
	board[0][7] = Square(BoardRow::ROW_ONE, BoardFile::FILE_H, Color::COLOR_WHITE, new Rook(Color::COLOR_WHITE));

	//second rank/row consists entirely of white pawns
	board[1][0] = Square(BoardRow::ROW_TWO, BoardFile::FILE_A, Color::COLOR_WHITE, new Pawn(Color::COLOR_WHITE));
	board[1][1] = Square(BoardRow::ROW_TWO, BoardFile::FILE_B, Color::COLOR_BLACK, new Pawn(Color::COLOR_WHITE));
	board[1][2] = Square(BoardRow::ROW_TWO, BoardFile::FILE_C, Color::COLOR_WHITE, new Pawn(Color::COLOR_WHITE));
	board[1][3] = Square(BoardRow::ROW_TWO, BoardFile::FILE_D, Color::COLOR_BLACK, new Pawn(Color::COLOR_WHITE));
	board[1][4] = Square(BoardRow::ROW_TWO, BoardFile::FILE_E, Color::COLOR_WHITE, new Pawn(Color::COLOR_WHITE));
	board[1][5] = Square(BoardRow::ROW_TWO, BoardFile::FILE_F, Color::COLOR_BLACK, new Pawn(Color::COLOR_WHITE));
	board[1][6] = Square(BoardRow::ROW_TWO, BoardFile::FILE_G, Color::COLOR_WHITE, new Pawn(Color::COLOR_WHITE));
	board[1][7] = Square(BoardRow::ROW_TWO, BoardFile::FILE_H, Color::COLOR_BLACK, new Pawn(Color::COLOR_WHITE));

	//The next four rows are empty squares
	board[2][0] = Square(BoardRow::ROW_THREE, BoardFile::FILE_A, Color::COLOR_BLACK);
	board[2][1] = Square(BoardRow::ROW_THREE, BoardFile::FILE_B, Color::COLOR_WHITE);
	board[2][2] = Square(BoardRow::ROW_THREE, BoardFile::FILE_C, Color::COLOR_BLACK);
	board[2][3] = Square(BoardRow::ROW_THREE, BoardFile::FILE_D, Color::COLOR_WHITE);
	board[2][4] = Square(BoardRow::ROW_THREE, BoardFile::FILE_E, Color::COLOR_BLACK);
	board[2][5] = Square(BoardRow::ROW_THREE, BoardFile::FILE_F, Color::COLOR_WHITE);
	board[2][6] = Square(BoardRow::ROW_THREE, BoardFile::FILE_G, Color::COLOR_BLACK);
	board[2][7] = Square(BoardRow::ROW_THREE, BoardFile::FILE_H, Color::COLOR_WHITE);

	board[3][0] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_A, Color::COLOR_WHITE);
	board[3][1] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_B, Color::COLOR_BLACK);
	board[3][2] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_C, Color::COLOR_WHITE);
	board[3][3] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_D, Color::COLOR_BLACK);
	board[3][4] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_E, Color::COLOR_WHITE);
	board[3][5] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_F, Color::COLOR_BLACK);
	board[3][6] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_G, Color::COLOR_WHITE);
	board[3][7] = Square(BoardRow::ROW_FOUR, BoardFile::FILE_H, Color::COLOR_BLACK);

	board[4][0] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_A, Color::COLOR_BLACK);
	board[4][1] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_B, Color::COLOR_WHITE);
	board[4][2] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_C, Color::COLOR_BLACK);
	board[4][3] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_D, Color::COLOR_WHITE);
	board[4][4] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_E, Color::COLOR_BLACK);
	board[4][5] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_F, Color::COLOR_WHITE);
	board[4][6] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_G, Color::COLOR_BLACK);
	board[4][7] = Square(BoardRow::ROW_FIVE, BoardFile::FILE_H, Color::COLOR_WHITE);

	board[5][0] = Square(BoardRow::ROW_SIX, BoardFile::FILE_A, Color::COLOR_WHITE);
	board[5][1] = Square(BoardRow::ROW_SIX, BoardFile::FILE_B, Color::COLOR_BLACK);
	board[5][2] = Square(BoardRow::ROW_SIX, BoardFile::FILE_C, Color::COLOR_WHITE);
	board[5][3] = Square(BoardRow::ROW_SIX, BoardFile::FILE_D, Color::COLOR_BLACK);
	board[5][4] = Square(BoardRow::ROW_SIX, BoardFile::FILE_E, Color::COLOR_WHITE);
	board[5][5] = Square(BoardRow::ROW_SIX, BoardFile::FILE_F, Color::COLOR_BLACK);
	board[5][6] = Square(BoardRow::ROW_SIX, BoardFile::FILE_G, Color::COLOR_WHITE);
	board[5][7] = Square(BoardRow::ROW_SIX, BoardFile::FILE_H, Color::COLOR_BLACK);

	//The fore-last rank is the black pawns
	board[6][0] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_A, Color::COLOR_BLACK, new Pawn(Color::COLOR_BLACK));
	board[6][1] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_B, Color::COLOR_WHITE, new Pawn(Color::COLOR_BLACK));
	board[6][2] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_C, Color::COLOR_BLACK, new Pawn(Color::COLOR_BLACK));
	board[6][3] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_D, Color::COLOR_WHITE, new Pawn(Color::COLOR_BLACK));
	board[6][4] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_E, Color::COLOR_BLACK, new Pawn(Color::COLOR_BLACK));
	board[6][5] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_F, Color::COLOR_WHITE, new Pawn(Color::COLOR_BLACK));
	board[6][6] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_G, Color::COLOR_BLACK, new Pawn(Color::COLOR_BLACK));
	board[6][7] = Square(BoardRow::ROW_SEVEN, BoardFile::FILE_H, Color::COLOR_WHITE, new Pawn(Color::COLOR_BLACK));

	board[7][0] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_A, Color::COLOR_WHITE, new Rook(Color::COLOR_BLACK));
	board[7][1] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_B, Color::COLOR_BLACK, new Knight(Color::COLOR_BLACK));
	board[7][2] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_C, Color::COLOR_WHITE, new Bishop(Color::COLOR_BLACK));
	board[7][3] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_D, Color::COLOR_BLACK, new Queen(Color::COLOR_BLACK));
	board[7][4] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_E, Color::COLOR_WHITE, new King(Color::COLOR_BLACK));
	board[7][5] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_F, Color::COLOR_BLACK, new Bishop(Color::COLOR_BLACK));
	board[7][6] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_G, Color::COLOR_WHITE, new Knight(Color::COLOR_BLACK));
	board[7][7] = Square(BoardRow::ROW_EIGHT, BoardFile::FILE_H, Color::COLOR_BLACK, new Rook(Color::COLOR_BLACK));
};

Board::~Board() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j].getPiece() != nullptr)
				delete board[i][j].getPiece();
		}
	}
}