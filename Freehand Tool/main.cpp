#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>

GLuint framebuffer;
const int screenWidth = 800;
const int screenHeight = 600;
const float PI = 3.141592;

int mouseButtonDown = 0;
float prevX = 0.0f;
float prevY = 0.0f;

void addBlob(int x, int y){
	float normalizedX = (float)x / ((float)screenWidth / 2) - 1.0f;
	float normalizedY = -((float)y / ((float)screenHeight / 2) - 1.0f);
	const int Radius = 3;

	glColor3f(1.0f, 0.5f, 0.0f);

	glBegin(GL_LINE_LOOP);
	for (int y = -Radius; y < Radius + 1; y++){
		for (int x = -Radius; x < Radius + 1; x++){
			if (!(abs(x) == Radius && abs(y) == Radius)){
				glVertex2f(normalizedX + (float)x / screenWidth, normalizedY + (float)y / screenHeight);
			}
		}
	}

	glEnd();

	glFlush();
}

void mousePointer(int x, int y){
	glFlush();
}

void motionFunc(int x, int y){
	float dispX = (float)x - prevX;
	float dispY = (float)y - prevY;
	float trigonolen = sqrt((float)pow(dispX, 2) + (float)pow(dispY, 2));

	for (int i = 0; i <= trigonolen; i++){
		addBlob(x - (dispX * i / trigonolen), y - (dispY * i / trigonolen));
	}

	/*printf("current: %f, %f\n", (float)x, (float)y);
	printf("prev: %f, %f\n", prevX, prevY);
	printf("disp: %f, %f\n", dispX, dispY);*/

	prevX = (float)x;
	prevY = (float)y;
}

void mouseFunc(int button, int state, int x, int y){
	prevX = (float)x;
	prevY = (float)y;

	glutMotionFunc(motionFunc);
}


int main(int argc, char **argv){
	glutInit(&argc, argv);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("OpenGL Pen");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 

	glutSetCursor(GLUT_CURSOR_SPRAY);

	glutPassiveMotionFunc(mousePointer);
	glutMouseFunc(mouseFunc);

	glutMainLoop();

	return 0;
}