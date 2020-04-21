//
// Created by pospelov on 21.04.2020.
//

#include "Player.hpp"

using namespace Controller;

IPlayer::IPlayer(number_of_player turn) : turn(turn) {}

void IPlayer::add_move(const board_cell &from, const board_cell &to) {
  moves.push({from, to});
}

bool IPlayer::check_move() const { return !moves.empty(); }

std::pair<board_cell, board_cell> IPlayer::get_move() const {
  return moves.top();
}

void IPlayer::pop_move() { moves.pop(); }

Player::Player(number_of_player turn, Game_state &game_state)
    : IPlayer(turn), game_state(game_state) {}

bool Player::send_move(const board_cell &from, const board_cell &to) {
  game_state.move(game_state.who_moves(), from, to);
  return true;
}

NetworkPlayer::NetworkPlayer(number_of_player turn, Network &network)
    : IPlayer(turn), network(network) {}

bool NetworkPlayer::send_move(const board_cell &from, const board_cell &to) {
  return network.send_move(from, to);
}