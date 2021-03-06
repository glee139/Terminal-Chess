#include "board.hpp"
#include <iostream>
#include <sstream>
using std::stringstream;

//constructor
Board::Board()  {
    board.resize(8);
    for (int i=0; i<board.size(); ++i) {
        board[i].resize(8);
        for (int j=0; j<board[0].size(); ++j) {
            board[i][j]=nullptr;
        }
    }
}

Board::~Board() {
    for (int i=0; i<board.size(); ++i) {
        for (int j=0; j<board[i].size(); ++j) {
            delete board[i][j];
        }
    }
}

void Board::addPiece(Piece* p)  {
    if (!p) return;
    board[p->getRow()-'1'][p->getCol()-'a']=p;
}

Piece* Board::getCell(char l, char n)  {
    if (l>'h' || n>'8' || l<'a' || n<'1') {
        return nullptr;
    }
    return board[n-'1'][l-'a'];
}

void Board::setCellNull(char l, char n) {
    board[n-'1'][l-'a']=nullptr;
}

void Board::move(char startL, char startN, char endL, char endN) {
    //turn char coords into 0-8 index coords
    int startRow=startN-'1';
    int startCol=startL-'a';
    int endRow=endN-'1';
    int endCol=endL-'a';
    //if there is a piece at (endL, endN) delete it to avoid memory leaks
    if (board[endRow][endCol]!=nullptr) delete board[endRow][endCol];

    //change piece coords
    board[startRow][startCol]->setRow(endN);
    board[startRow][startCol]->setCol(endL);
    //update board position
    board[endRow][endCol]=board[startRow][startCol];
    board[startRow][startCol]=nullptr;
}

void Board::drawBoard(char c) {
    for (int i=0; i<board.size(); ++i) {
        for (int j=0; j<board[0].size(); ++j) {
            //if white is moving next
            if (i%2==j%2) cout << "\33[44m";
            else cout << "\33[42m";
            if (c=='w') {
                if (board[board.size()-1-i][j]==nullptr) cout << " ";
                else {
                    if (board[board.size()-1-i][j]->getColor()=='b') cout << "\33[30m";
                    else cout << "\33[37m";
                    cout << board[board.size()-1-i][j]->getPiece();
                }
            } else { //if black is moving next
                if (board[i][board[0].size()-1-j]==nullptr) cout << " ";
                else cout << board[i][board[0].size()-1-i]->getPiece();
            }
        }
        cout << "\33[49m" << endl;
    }
    cout << "\33[49m" << "\33[39m" << endl;
}
//for testing, removed the coloring to make things easier to test
void Board::drawBoard2(char c, stringstream& os) {
    for (int i=0; i<board.size(); ++i) {
        for (int j=0; j<board[0].size(); ++j) {
            if (c=='w') {
                if (board[board.size()-1-i][j]==nullptr) os << " ";
                else {
                    os << board[board.size()-1-i][j]->getPiece();
                }
            } else { //if black is moving next
                if (board[i][board[0].size()-1-j]==nullptr) os << " ";
                else os << board[i][board[0].size()-1-i]->getPiece();
            }
        }
        os << "\n";
    }
}

void Board::drawBoard(std::ostream& out,char c) {
    for (int i=0; i<board.size(); ++i) {
        for (int j=0; j<board[0].size(); ++j) {
            
            if (c=='w') {
                if (board[board.size()-1-i][j]==nullptr) out << "*";
                else out << board[board.size()-1-i][j]->getPiece();
            } else { 
                if (board[i][board[0].size()-1-j]==nullptr) out << "*";
                else out << board[i][board[0].size()-1-i]->getPiece();
            }
        }
        out << endl;
    }
}