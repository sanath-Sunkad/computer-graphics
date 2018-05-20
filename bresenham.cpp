
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>		
#include <stdlib.h>		
#include <math.h>
#include <stdio.h>
#include <string.h>


int a, b, c, d;
void drawpixel(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void bresnham(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int m = dy / dx;
	if (m < 1)
	{
		int dp = 2*dy - dx;
		int x = x1;
		int y = y1;
		if (dx < 0)
		{
			x = x2;
			y = y2;
			x2 = x1;
		}
		drawpixel(x, y);
		while (x>x2)
		{
			if (dp >= 0)
			{
				x = x + 1;
				y = y + 1;
				dp = dp + 2*dy - 2*dx;
			}
			else 
			{
				x = x + 1;
				y = y;
				dp = dp + 2 * dy;
			}
			drawpixel(x,y);
		}
	}
	if (m > 1)
	{
		int dp = 2 * dx - dy;
		int x = x1;
		int y = y1;
		if (dy < 0)
		{
			x = x2;
			y = y2;
			y2 = y1;
		}
		drawpixel(x, y);
		while (y>y2)
		{
			if (dp >= 0)
			{
				x = x + 1;
				y = y + 1;
				dp = dp + 2 * dx - 2 * dy;
			}
			else
			{
				x = x;
				y = y+1;
				dp = dp + 2 * dx;
			}
			drawpixel(x, y);
		}
	}
	if (m == 1)
	{
		int x = x1;
		int y = y1;
		drawpixel(x, y);
		while (x < x2)
		{
			x = x + 1;
			y = y + 1;
			drawpixel(x, y);
		}
	}
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	bresnham(a, b, c, d);
	glFlush();
}

int main(int argc, char** argv)
{
	printf("Enter Scan Points (x1,y1) ");
	scanf_s("%d%d", &a, &b);
	printf("Enter Scan Points (x2,y2) ");
	scanf_s("%d%d", &c, &d);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Brezenham");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
