#ifndef CHECKERS_CONTROLLER_PLAYER_HPP_
#define CHECKERS_CONTROLLER_PLAYER_HPP_

#include "Game.hpp"

#include <queue>

class Network;

namespace controller {

class IPlayer {
private:
  mutable std::queue<std::pair<BoardCell, BoardCell>> moves;

public:
  number_of_player turn;

  bool enemyGaveUp;
  bool meGaveUp;

public:
  IPlayer(number_of_player);
  virtual ~IPlayer();

  virtual bool send_move(const BoardCell &, const BoardCell &) = 0;
  virtual void add_move(const BoardCell &, const BoardCell &);
  virtual bool check_move();
  virtual std::pair<BoardCell, BoardCell> get_move() const;
  virtual void pop_move();

  virtual void enemy_gave_up();
};

class Player : public IPlayer {
private:
public:
  Player(number_of_player);
  ~Player() override;

  bool send_move(const BoardCell &, const BoardCell &) override;
};

class NetworkPlayer : public IPlayer {
private:
  Network &network;

public:
  NetworkPlayer(number_of_player, Network &);
  ~NetworkPlayer() override;

  bool send_move(const BoardCell &, const BoardCell &) override;

  void enemy_gave_up() override;
};

} // namespace controller

#endif // CHECKERS_CONTROLLER_PLAYER_HPP_
