int fillFlag = 0;
float a, b, c, d, a1, b1, c1, d1;
void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re)
{
	float mx, x, temp;
	int i;
	if ((y2 - y1)<0)
	{
		temp = y1;y1 = y2;y2 = temp;
		temp = x1;x1 = x2;x2 = temp;
	}
	if ((y2 - y1) != 0)
		mx = (x2 - x1) / (y2 - y1);
	else
		mx = x2 - x1;
	x = x1;
	for (i = y1;i <= y2;i++)
	{
		if (x<(float)le[i])
			le[i] = (int)x;
		if (x>(float)re[i])
			re[i] = (int)x;
		x += mx;
	}
}
void draw_pixels(int x, int y)
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	int le[1500], re[1500];
	int i, y;
	for (i = 0;i<1500;i++)
	{
		le[i] = 1500;
		re[i] = 0;
	}
	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);
	for (y = 0;y<1500;y++)
	{
		if (le[y]<re[y])
			for (i = (int)le[y];i<(int)re[y];i++)
				draw_pixels(i, y);
	}
}
void display()
{
	a = 200.0;a1 = 200.0;b = 100.0;b1 = 300.0;c = 200.0;c1 = 400.0;d = 300.0;d1 = 300.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(a, a1);
	glVertex2f(b, b1);
	glVertex2f(c, c1);
	glVertex2f(d, d1);
	glEnd();
	if (fillFlag == 1)
		scanfill(a, a1, b, b1, c, c1, d, d1);
	glFlush();
}
void fillMenu(int option)
{
	if (option == 1)
		fillFlag = 1;
	if (option == 2)
		fillFlag = 2;
	display();
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
void main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("filling a polygon using scanline ");
	glutDisplayFunc(display);
	glutCreateMenu(fillMenu);
	glutAddMenuEntry("Fill Polygon", 1);
	glutAddMenuEntry("Empty Polygon", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myinit();
	glutMainLoop();
}
