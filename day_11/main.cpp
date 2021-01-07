#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <vector>
#include <numeric>
#include <map>
#include <array>

using Seat2D = std::vector<std::vector<char>>;
const char OCCUPIED = '#';
const char EMPTY = 'L';

int countOccupied(const Seat2D &seats) {
  int occupied = 0;
  for (int r = 0; r < seats.size(); r++)
    for (int c = 0; c < seats.at(0).size(); c++)
      occupied += seats.at(r).at(c) == OCCUPIED;

  return occupied;
}

namespace Part1 {
  int countNeighborOccupied(const Seat2D &seats, int r, int c) {
    int occupied = 0;
    const int MAX_ROW = seats.size() - 1;
    const int MAX_COL = seats.at(0).size() - 1;

    if (r != 0) {
      // above seat
      occupied += seats.at(r - 1).at(c) == OCCUPIED;
      if (c != 0) {
        // top left
        occupied += seats.at(r - 1).at(c - 1) == OCCUPIED;
      }
      if (c != MAX_COL) {
        // top right
        occupied += seats.at(r - 1).at(c + 1) == OCCUPIED;
      }
    }
    if (r != MAX_ROW) {
      // below seat
      occupied += seats.at(r + 1).at(c) == OCCUPIED;
      if (c != 0) {
        // below left
        occupied += seats.at(r + 1).at(c - 1) == OCCUPIED;
      }
      if (c != MAX_COL) {
        // below right
        occupied += seats.at(r + 1).at(c + 1) == OCCUPIED;
      }
    }
    if (c != 0) {
      // middle left seat
      occupied += seats.at(r).at(c - 1) == OCCUPIED;
    }
    if (c != MAX_COL) {
      // middle right seat
      occupied += seats.at(r).at(c + 1) == OCCUPIED;
    }

    return occupied;
  }

  // returns true when iteration changes seat
  bool iteration(Seat2D &seats) {
    bool anyChange = false;
    Seat2D copy = seats;

    for (int r = 0; r < seats.size(); r++) {
      for (int c = 0; c < seats.at(0).size(); c++) {
        char &seat = seats.at(r).at(c);
        char &copySeat = copy.at(r).at(c);

        if (seat == EMPTY && countNeighborOccupied(seats, r, c) == 0) {
          anyChange = true;
          copySeat = OCCUPIED;
        } else if (seat == OCCUPIED && countNeighborOccupied(seats, r, c) >= 4) {
          anyChange = true;
          copySeat = EMPTY;
        }
      }
    }

    seats = copy;

    return anyChange;
  }
}

namespace Part2 {
  bool directionIsOccupied(const Seat2D &seats, int r, int c, int deltaR, int deltaC){
    const int MAX_ROW = seats.size() - 1;
    const int MAX_COL = seats.at(0).size() - 1;

    r += deltaR;
    c += deltaC;

    for(; r >= 0 && r <= MAX_ROW && c >= 0 && c <= MAX_COL; r += deltaR, c += deltaC){
      char seat = seats.at(r).at(c);

      if(seat == OCCUPIED){
        return true;
      }else if(seat == EMPTY){
        return false;
      }
    }
    return false;
  }

  int countNeighborOccupied(const Seat2D &seats, int r, int c){
    int occupied = 0;

    occupied += directionIsOccupied(seats, r, c, -1, 0); // up
    occupied += directionIsOccupied(seats, r, c, -1, 1); // up, right
    occupied += directionIsOccupied(seats, r, c, 0, 1); // right
    occupied += directionIsOccupied(seats, r, c, 1, 1); // down, right
    occupied += directionIsOccupied(seats, r, c, 1, 0); // down
    occupied += directionIsOccupied(seats, r, c, 1, -1); // down, left
    occupied += directionIsOccupied(seats, r, c, 0, -1); // left
    occupied += directionIsOccupied(seats, r, c, -1, -1); // up, left

    return occupied;
  }

  bool iteration(Seat2D &seats){
    bool anyChange = false;
    Seat2D copy = seats;

    for (int r = 0; r < seats.size(); r++) {
      for (int c = 0; c < seats.at(0).size(); c++) {
        char &seat = seats.at(r).at(c);
        char &copySeat = copy.at(r).at(c);

        if (seat == EMPTY && countNeighborOccupied(seats, r, c) == 0) {
          anyChange = true;
          copySeat = OCCUPIED;
        } else if (seat == OCCUPIED && countNeighborOccupied(seats, r, c) >= 5) {
          anyChange = true;
          copySeat = EMPTY;
        }
      }
    }

    seats = copy;

    return anyChange;
  }
}

int main(){
  std::ifstream input("input.txt");
  Seat2D seats;
  Seat2D copy; // for part 2

  std::string line;
  while(input >> line){
    std::vector<char> row;
    for(auto c : line){
      row.push_back(c);
    }
    seats.push_back(row);
  }
  copy = seats;


  while(Part1::iteration(seats));
  std::cout << "Part 1: " << countOccupied(seats) << "\n";

  while(Part2::iteration(copy));
  std::cout << "Part 2: " << countOccupied(copy) << "\n";
}