#ifndef _GameState_HPP_
#define _GameState_HPP_

#include "BoardCell.hpp"
#include <expat.h>
#include <fstream>
#include <iostream>
#include <vector>

enum state { GAME, FIRST_WIN, SECOND_WIN, DRAW };
enum number_of_player { FIRST, SECOND };

class GameState {
private:
  static const int SIZE = 8;
  static const int DRAW_MOVE = 15;

  number_of_player who_last;
  int move_to_draw, type_last;
  BoardCell last_move;
  char board[SIZE][SIZE];

  bool check_ordinary(number_of_player player, BoardCell from,
                      BoardCell to) const;
  bool check_queen(number_of_player player, BoardCell from, BoardCell to) const;
  bool inside(BoardCell cell) const;
  bool kill(number_of_player who, BoardCell pos) const;
  bool is_kill(number_of_player who, BoardCell from, BoardCell to) const;
  BoardCell find_kill(number_of_player who) const;

public:
  GameState();

  number_of_player who_moves() const;
  bool check_move(number_of_player player, BoardCell from, BoardCell to) const;
  void move(number_of_player player, BoardCell from, BoardCell to);
  std::vector<BoardCell> get_list_of_correct_moves(number_of_player player,
                                                   BoardCell from) const;
  state check_win() const;
  char get_cell(BoardCell cell) const;
  void show() const;

  friend bool operator!=(const GameState &fir, const GameState &sec);

  void save_to_file(std::ofstream &os) const;
  friend void XMLCALL dataElement(void *userData, const XML_Char *s, int len);

  friend class TestGameState;
  friend class CompPlayer;
};

#endif
