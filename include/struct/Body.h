//
// Created by Gustavo Novais on 27/04/2025.
//

#ifndef BODY_H
#define BODY_H

#include <vector>
#include "Movement.h"
#include "enums/Direction.h"
using namespace std;

struct Body{
  vector<vector<float>> vertices;
  Movement movement;
  Direction direction;
  bool isHead;
};

#endif //BODY_H
