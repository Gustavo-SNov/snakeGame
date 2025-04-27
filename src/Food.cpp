//
// Created by Gustavo Novais on 27/04/2025.
//
#include "Food.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <ostream>


void Food::render() {
  if (eated) {
    cout<<"Food is eated"<<endl;
  }
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex2f(this->center[0], this->center[1]);
  for (int i=0; i<=NUM_SEGMENTS;i++){
    float theta = 2.0f * M_PI * float(i)/float(NUM_SEGMENTS);
    float x = radius * cos(theta);
    float y = radius * sin(theta);
    glVertex2f(this->center[0]+x, this->center[1]+y);
  }
  glEnd();

};
