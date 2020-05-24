#include "TestGameState.hpp"

void TestGameState::test_init() {
  GameState g;
  CPPUNIT_ASSERT(g.who_last == SECOND);
  CPPUNIT_ASSERT(g.move_to_draw == 0);
  CPPUNIT_ASSERT(g.type_last == 0);
  CPPUNIT_ASSERT(g.last_move == BoardCell(-1, -1));
  for (int i = 0; i < g.SIZE; i += 2) {
    CPPUNIT_ASSERT(g.board[1][i] == 'b' && g.board[g.SIZE - 1][i] == 'w' &&
                   g.board[g.SIZE - 3][i] == 'w');
    CPPUNIT_ASSERT(g.board[0][i] == '.' && g.board[2][i] == '.' &&
                   g.board[g.SIZE - 2][i] == '.');
  }
  for (int i = 1; i < g.SIZE; i += 2) {
    CPPUNIT_ASSERT(g.board[0][i] == 'b' && g.board[2][i] == 'b' &&
                   g.board[g.SIZE - 2][i] == 'w');
    CPPUNIT_ASSERT(g.board[1][i] == '.' && g.board[g.SIZE - 1][i] == '.' &&
                   g.board[g.SIZE - 3][i] == '.');
  }
  for (int i = 3; i < g.SIZE - 3; i++)
    for (int j = 0; j < g.SIZE; j++)
      CPPUNIT_ASSERT(g.board[i][j] == '.');
  return;
}

void TestGameState::calculate(GameState &G) {
  for (int i = 0; i < G.SIZE; i++)
    for (int j = 0; j < G.SIZE; j++) {
      if (i == 0 || j == 0)
        G.white_up_down[i][j] = G.black_up_down[i][j] = 0;
      else {
        G.white_up_down[i][j] = G.white_up_down[i - 1][j - 1];
        G.black_up_down[i][j] = G.black_up_down[i - 1][j - 1];
      }
      if (G.board[i][j] == 'w' || G.board[i][j] == 'W')
        G.white_up_down[i][j]++;
      if (G.board[i][j] == 'b' || G.board[i][j] == 'B')
        G.black_up_down[i][j]++;
    }

  for (int i = G.SIZE - 1; i >= 0; i--)
    for (int j = 0; j < G.SIZE; j++) {
      if (i == G.SIZE - 1 || j == 0)
        G.white_down_up[i][j] = G.black_down_up[i][j] = 0;
      else {
        G.white_down_up[i][j] = G.white_down_up[i + 1][j - 1];
        G.black_down_up[i][j] = G.black_down_up[i + 1][j - 1];
      }
      if (G.board[i][j] == 'w' || G.board[i][j] == 'W')
        G.white_down_up[i][j]++;
      if (G.board[i][j] == 'b' || G.board[i][j] == 'B')
        G.black_down_up[i][j]++;
    }
  return;
}

void TestGameState::test_ordinary() {
  GameState g;
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[0][5] = 'b';
  g.board[1][2] = 'b';
  g.board[1][4] = 'b';
  g.board[1][7] = 'b';
  g.board[2][3] = 'w';
  g.board[2][6] = 'b';
  g.board[3][2] = 'w';
  g.board[3][5] = 'w';
  g.board[4][2] = 'w';
  g.board[5][5] = 'w';
  g.board[6][4] = 'w';
  g.board[4][3] = 'b';
  calculate(g);

  bool die = false;
  CPPUNIT_ASSERT(g.check_ordinary(FIRST, BoardCell(2, 3), BoardCell(0, 1), die));
  CPPUNIT_ASSERT(g.check_ordinary(FIRST, BoardCell(3, 2), BoardCell(2, 1), die));
  CPPUNIT_ASSERT(!g.check_ordinary(FIRST, BoardCell(1, 2), BoardCell(3, 4), die));
  CPPUNIT_ASSERT(!g.check_ordinary(FIRST, BoardCell(3, 5), BoardCell(3, 7), die));
  CPPUNIT_ASSERT(!g.check_ordinary(FIRST, BoardCell(5, 5), BoardCell(6, 6), die));
  CPPUNIT_ASSERT(g.check_ordinary(FIRST, BoardCell(4, 2), BoardCell(3, 3), die));
  CPPUNIT_ASSERT(g.check_ordinary(FIRST, BoardCell(3, 2), BoardCell(5, 4), die));

  CPPUNIT_ASSERT(!g.check_ordinary(SECOND, BoardCell(4, 3), BoardCell(2, 5), die));
  CPPUNIT_ASSERT(g.check_ordinary(SECOND, BoardCell(1, 2), BoardCell(3, 4), die));
  CPPUNIT_ASSERT(!g.check_ordinary(SECOND, BoardCell(1, 2), BoardCell(2, 2), die));
  CPPUNIT_ASSERT(g.check_ordinary(SECOND, BoardCell(0, 5), BoardCell(1, 6), die));
  CPPUNIT_ASSERT(g.check_ordinary(SECOND, BoardCell(1, 2), BoardCell(2, 1), die));
  CPPUNIT_ASSERT(!g.check_ordinary(SECOND, BoardCell(1, 2), BoardCell(0, 3), die));
  CPPUNIT_ASSERT(g.check_ordinary(SECOND, BoardCell(4, 3), BoardCell(2, 1), die));
  return;
}

void TestGameState::test_queen() {
  GameState g;
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][3] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][4] = 'b';
  g.board[6][7] = 'B';
  calculate(g);

  bool die = false;
  CPPUNIT_ASSERT(g.check_queen(FIRST, BoardCell(4, 6), BoardCell(0, 2), die));
  CPPUNIT_ASSERT(g.check_queen(FIRST, BoardCell(4, 6), BoardCell(2, 4), die));
  CPPUNIT_ASSERT(g.check_queen(FIRST, BoardCell(4, 6), BoardCell(5, 7), die));
  CPPUNIT_ASSERT(!g.check_queen(FIRST, BoardCell(4, 6), BoardCell(4, 5), die));
  CPPUNIT_ASSERT(!g.check_queen(FIRST, BoardCell(6, 7), BoardCell(0, 1), die));
  CPPUNIT_ASSERT(!g.check_queen(FIRST, BoardCell(1, 6), BoardCell(4, 3), die));

  CPPUNIT_ASSERT(g.check_queen(SECOND, BoardCell(1, 6), BoardCell(4, 3), die));
  CPPUNIT_ASSERT(g.check_queen(SECOND, BoardCell(1, 6), BoardCell(7, 0), die));
  CPPUNIT_ASSERT(!g.check_queen(SECOND, BoardCell(2, 6), BoardCell(4, 3), die));
  CPPUNIT_ASSERT(g.check_queen(SECOND, BoardCell(1, 3), BoardCell(5, 7), die));
  CPPUNIT_ASSERT(g.check_queen(SECOND, BoardCell(2, 6), BoardCell(5, 3), die));
  CPPUNIT_ASSERT(!g.check_queen(SECOND, BoardCell(4, 6), BoardCell(3, 7), die));
  return;
}

void TestGameState::test_check_move() {
  GameState g;
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[0][5] = 'b';
  g.board[1][2] = 'b';
  g.board[1][4] = 'b';
  g.board[1][7] = 'b';
  g.board[2][3] = 'w';
  g.board[2][6] = 'b';
  g.board[3][2] = 'w';
  g.board[3][5] = 'w';
  g.board[4][2] = 'w';
  g.board[5][5] = 'w';
  g.board[6][4] = 'w';
  g.board[4][3] = 'b';
  calculate(g);

  bool die = false;
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(0, 0), BoardCell(1, 1), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(2, 3), BoardCell(0, 5), die));
  CPPUNIT_ASSERT(g.check_move(FIRST, BoardCell(2, 3), BoardCell(0, 1), die));
  CPPUNIT_ASSERT(g.check_move(FIRST, BoardCell(3, 2), BoardCell(2, 1), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(6, 4), BoardCell(8, 6), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(1, 2), BoardCell(3, 4), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(3, 5), BoardCell(3, 7), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(5, 5), BoardCell(6, 6), die));

  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(4, 3), BoardCell(2, 5), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(1, 7), BoardCell(0, 8), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(1, 4), BoardCell(3, 2), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(1, 2), BoardCell(3, 4), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(1, 2), BoardCell(2, 2), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(0, 5), BoardCell(1, 6), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(1, 2), BoardCell(2, 1), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(1, 2), BoardCell(0, 3), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(4, 3), BoardCell(2, 1), die));

  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][3] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][4] = 'b';
  g.board[6][7] = 'B';
  calculate(g);

  CPPUNIT_ASSERT(g.check_move(FIRST, BoardCell(4, 6), BoardCell(0, 2), die));
  CPPUNIT_ASSERT(g.check_move(FIRST, BoardCell(4, 6), BoardCell(2, 4), die));
  CPPUNIT_ASSERT(g.check_move(FIRST, BoardCell(4, 6), BoardCell(5, 7), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(4, 6), BoardCell(4, 5), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(4, 6), BoardCell(3, 7), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(6, 7), BoardCell(0, 1), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(1, 6), BoardCell(4, 3), die));
  CPPUNIT_ASSERT(!g.check_move(FIRST, BoardCell(4, 6), BoardCell(6, 4), die));

  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(1, 6), BoardCell(4, 3), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(1, 6), BoardCell(7, 0), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(2, 6), BoardCell(4, 3), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(1, 3), BoardCell(5, 7), die));
  CPPUNIT_ASSERT(g.check_move(SECOND, BoardCell(2, 6), BoardCell(5, 3), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(4, 6), BoardCell(3, 7), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(6, 7), BoardCell(1, 2), die));
  CPPUNIT_ASSERT(!g.check_move(SECOND, BoardCell(1, 2), BoardCell(2, 2), die));
  return;
}

void TestGameState::test_inside() {
  GameState g;
  CPPUNIT_ASSERT(g.inside(BoardCell(0, 0)));
  CPPUNIT_ASSERT(!g.inside(BoardCell(-1, 5)));
  CPPUNIT_ASSERT(g.inside(BoardCell(7, 7)));
  CPPUNIT_ASSERT(!g.inside(BoardCell(8, 0)));
  CPPUNIT_ASSERT(!g.inside(BoardCell(8, 8)));
  CPPUNIT_ASSERT(g.inside(BoardCell(0, 7)));
  return;
}

void TestGameState::test_kill() {
  GameState g;
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[0][5] = 'b';
  g.board[1][2] = 'b';
  g.board[1][4] = 'b';
  g.board[1][7] = 'b';
  g.board[2][3] = 'w';
  g.board[2][6] = 'b';
  g.board[3][2] = 'w';
  g.board[3][5] = 'w';
  g.board[4][2] = 'w';
  g.board[5][5] = 'w';
  g.board[6][4] = 'w';
  g.board[4][3] = 'b';
  calculate(g);

  CPPUNIT_ASSERT(g.kill(FIRST, BoardCell(2, 3)));
  CPPUNIT_ASSERT(!g.kill(FIRST, BoardCell(3, 5)));
  CPPUNIT_ASSERT(!g.kill(FIRST, BoardCell(6, 4)));
  CPPUNIT_ASSERT(g.kill(FIRST, BoardCell(3, 2)));

  CPPUNIT_ASSERT(g.kill(SECOND, BoardCell(1, 2)));
  CPPUNIT_ASSERT(!g.kill(SECOND, BoardCell(1, 4)));
  CPPUNIT_ASSERT(!g.kill(SECOND, BoardCell(1, 7)));
  CPPUNIT_ASSERT(g.kill(SECOND, BoardCell(4, 3)));

  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][3] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][4] = 'b';
  g.board[6][7] = 'B';
  calculate(g);

  CPPUNIT_ASSERT(g.kill(FIRST, BoardCell(4, 6)));
  CPPUNIT_ASSERT(!g.kill(FIRST, BoardCell(3, 4)));
  CPPUNIT_ASSERT(!g.kill(FIRST, BoardCell(1, 5)));
  CPPUNIT_ASSERT(!g.kill(FIRST, BoardCell(6, 7)));

  CPPUNIT_ASSERT(g.kill(SECOND, BoardCell(1, 2)));
  CPPUNIT_ASSERT(g.kill(SECOND, BoardCell(1, 3)));
  CPPUNIT_ASSERT(!g.kill(SECOND, BoardCell(4, 2)));
  CPPUNIT_ASSERT(g.kill(SECOND, BoardCell(3, 7)));
  return;
}

void TestGameState::test_find_kill() {
  GameState g;
  CPPUNIT_ASSERT(!g.find_kill(FIRST));
  CPPUNIT_ASSERT(!g.find_kill(SECOND));
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[0][5] = 'b';
  g.board[1][2] = 'b';
  g.board[1][4] = 'b';
  g.board[1][7] = 'b';
  g.board[2][3] = 'w';
  g.board[2][6] = 'b';
  g.board[3][2] = 'w';
  g.board[3][5] = 'w';
  g.board[4][2] = 'w';
  g.board[5][5] = 'w';
  g.board[6][4] = 'w';
  g.board[4][3] = 'b';
  calculate(g);

  CPPUNIT_ASSERT(g.find_kill(FIRST));
  CPPUNIT_ASSERT(g.find_kill(SECOND));

  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][3] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][4] = 'b';
  g.board[6][7] = 'B';
  calculate(g);

  CPPUNIT_ASSERT(g.find_kill(FIRST));
  return;
}

void TestGameState::test_who_moves() {
  GameState g;
  CPPUNIT_ASSERT(g.who_moves() == FIRST);
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[0][5] = 'b';
  g.board[1][2] = 'b';
  g.board[1][4] = 'b';
  g.board[1][7] = 'b';
  g.board[2][3] = 'w';
  g.board[2][6] = 'b';
  g.board[3][2] = 'w';
  g.board[3][5] = 'w';
  g.board[4][2] = 'w';
  g.board[5][5] = 'w';
  g.board[6][4] = 'w';
  g.board[4][3] = 'b';
  calculate(g);

  g.last_move = BoardCell(2, 3);
  g.who_last = FIRST;
  g.type_last = 1;
  CPPUNIT_ASSERT(g.who_moves() == FIRST);
  g.last_move = BoardCell(3, 5);
  CPPUNIT_ASSERT(g.who_moves() == SECOND);
  g.type_last = 0;
  g.last_move = BoardCell(2, 3);
  CPPUNIT_ASSERT(g.who_moves() == SECOND);
  g.who_last = SECOND;
  g.last_move = BoardCell(4, 3);
  g.type_last = 0;
  CPPUNIT_ASSERT(g.who_moves() == FIRST);

  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][3] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][4] = 'b';
  g.board[6][7] = 'B';
  calculate(g);

  g.last_move = BoardCell(4, 6);
  g.who_last = FIRST;
  g.type_last = 0;
  CPPUNIT_ASSERT(g.who_moves() == SECOND);
  g.type_last = 1;
  CPPUNIT_ASSERT(g.who_moves() == FIRST);
  g.who_last = SECOND;
  g.last_move = BoardCell(4, 2);
  g.type_last = 1;
  CPPUNIT_ASSERT(g.who_moves() == FIRST);
  return;
}

void TestGameState::test_move() {
  GameState g;
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][7] = 'W';
  calculate(g);

  GameState cop = g;
  g.move(FIRST, BoardCell(3, 4), BoardCell(4, 3));
  CPPUNIT_ASSERT(!(cop != g));
  cop = g;
  g.move(SECOND, BoardCell(6, 7), BoardCell(2, 3));
  CPPUNIT_ASSERT(!(cop != g));

  g.who_last = FIRST;
  g.type_last = 0;
  g.last_move = BoardCell(6, 7);
  cop = g;
  g.move(SECOND, BoardCell(1, 2), BoardCell(4, 5));
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      if (BoardCell(i, j) != BoardCell(1, 2) &&
          BoardCell(i, j) != BoardCell(3, 4) &&
          BoardCell(i, j) != BoardCell(4, 5))
        CPPUNIT_ASSERT(g.board[i][j] == cop.board[i][j]);
  CPPUNIT_ASSERT(g.board[1][2] == '.');
  CPPUNIT_ASSERT(g.board[3][4] == '.');
  CPPUNIT_ASSERT(g.board[4][5] == 'B');

  cop = g;
  g.move(FIRST, BoardCell(4, 6), BoardCell(5, 5));
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      if (BoardCell(i, j) != BoardCell(4, 6) &&
          BoardCell(i, j) != BoardCell(6, 7) &&
          BoardCell(i, j) != BoardCell(5, 5))
        CPPUNIT_ASSERT(g.board[i][j] == cop.board[i][j]);
  CPPUNIT_ASSERT(g.board[6][7] == 'W');
  CPPUNIT_ASSERT(g.board[4][6] == 'W');
  CPPUNIT_ASSERT(g.board[5][5] == '.');
  return;
}

void TestGameState::test_get_list() {
  GameState g;
  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  g.board[1][2] = 'B';
  g.board[1][3] = 'B';
  g.board[1][5] = 'w';
  g.board[1][6] = 'B';
  g.board[2][6] = 'B';
  g.board[3][4] = 'w';
  g.board[3][7] = 'b';
  g.board[4][2] = 'w';
  g.board[4][6] = 'W';
  g.board[6][4] = 'b';
  g.board[6][7] = 'W';
  calculate(g);

  std::vector<BoardCell> A;
  std::vector<BoardCell> B{BoardCell(5, 5)};
  std::vector<BoardCell> C;
  std::vector<BoardCell> D{BoardCell(7, 3), BoardCell(0, 2)};
  
  std::vector <BoardCell> result;
  g.get_list_of_correct_moves(FIRST, BoardCell(6, 7), result);
  CPPUNIT_ASSERT(result == A);
  result.clear();
  
  g.get_list_of_correct_moves(FIRST, BoardCell(4, 6), result);
  CPPUNIT_ASSERT(result == D);
  result.clear();

  g.who_last = FIRST;
  g.get_list_of_correct_moves(SECOND, BoardCell(3, 7), result);
  CPPUNIT_ASSERT(result == B);
  result.clear();
  
  g.get_list_of_correct_moves(SECOND, BoardCell(6, 4), result);
  CPPUNIT_ASSERT(result == C);
  result.clear();
  return;
}

void TestGameState::test_check_win() {
  GameState g;
  CPPUNIT_ASSERT(g.check_win() == GAME);
  g.move_to_draw = 20;
  CPPUNIT_ASSERT(g.check_win() == DRAW);
  g.move_to_draw = 0;

  for (int i = 0; i < g.SIZE; i++)
    for (int j = 0; j < g.SIZE; j++)
      g.board[i][j] = '.';
  for (int i = 0; i < g.SIZE; i++)
    g.board[0][i] = 'b', g.board[1][i] = 'w';
  calculate(g);

  g.who_last = SECOND;
  CPPUNIT_ASSERT(g.check_win() == SECOND_WIN);
  g.who_last = FIRST;
  CPPUNIT_ASSERT(g.check_win() == GAME);
  return;
}

void TestGameState::test_get_cell() {
  GameState g;
  for (int i = 0; i < g.SIZE; i += 2) {
    CPPUNIT_ASSERT(g.get_cell(BoardCell(0, i)) == '.');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(1, i)) == 'b');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(2, i)) == '.');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(g.SIZE - 3, i)) == 'w');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(g.SIZE - 2, i)) == '.');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(g.SIZE - 1, i)) == 'w');
  }
  for (int i = 1; i < g.SIZE; i += 2) {
    CPPUNIT_ASSERT(g.get_cell(BoardCell(0, i)) == 'b');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(1, i)) == '.');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(2, i)) == 'b');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(g.SIZE - 3, i)) == '.');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(g.SIZE - 2, i)) == 'w');
    CPPUNIT_ASSERT(g.get_cell(BoardCell(g.SIZE - 1, i)) == '.');
  }
  return;
}

void TestGameState::test_neq() {
  GameState g1, g2, g3;
  g3.move_to_draw++;
  CPPUNIT_ASSERT(!(g1 != g2));
  CPPUNIT_ASSERT(g1 != g3);
  return;
}
