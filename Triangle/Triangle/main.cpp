//
//  main.cpp
//  Triangle
//
//  Created by redknot on 8/8/16.
//  Copyright © 2016 redknot. All rights reserved.
//
#include <GLUT/GLUT.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}

int main(int argc, char *argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    
    return 0;
}
