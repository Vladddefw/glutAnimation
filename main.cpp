#define M_PI 3.14159265358979323846
#include"freeglut.h"
#include<cmath>

// C≤ œÀ¿— œÀ¿—

using namespace std;

int windowHeight = 800;
int windowWidth = 1400;
int windowPosX = 0;
int windowPosY = 0;

float cameraZoom = 5.0f;

float angle1 = 0.0f;
float angle2 = 0.0f;
float rotateSpeed = 1.0f;

void initGL()
{
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

}

void drawCube(float size)
{
	glutWireCube(size);
}
void drawCircle(float radius, float semnents)
{
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
		glBegin(GL_LINE_LOOP);
			glColor3f(1, 1, 1);

			for (int i = 0; i < semnents; ++i)
			{
				float theta = 2.0 * M_PI * static_cast<float>(i) / static_cast<float>(semnents);
				float x = radius * std::cos(theta);
				float y = radius * std::sin(theta);
				glVertex2f(x, y);
			}
		glEnd();
	glPopMatrix();
}

void drawSphere(float angle, float radius, float posX, float posY, float posZ)
{
	glPushMatrix();
		glRotatef(angle, 0, 1, 0);
		glTranslatef(posX, posY, posZ);
		glutWireSphere(radius, 20, 20);
	glPopMatrix();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(cameraZoom, cameraZoom, 5,
			0, 0, 0,
			0, 1, 0
	);

	glPushMatrix();
		glRotatef(angle1 * 0.5, 1, 1, 0);
		glColor3f(1, 1, 1);
		drawCube(2);
	glPopMatrix();

	drawCircle(5, 50);
	drawCircle(10, 50);
	drawCircle(15, 50);
	drawCircle(20, 50);


	glPushMatrix();
		glColor3f(0.4, 0.4, 0.8);
		glRotatef(angle1 * 5, 0, 1, 0);
		drawSphere(0, 1, 5, 0, 0);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.3, 0.3, 0.7);
		glRotatef(angle1 * 2, 0, 1, 0);
		drawSphere(45, 1, -10, 0, 0);
		glColor3f(0.1, 0.1, 0.5);
		drawSphere(180, 1, 20, 0, 0);
	glPopMatrix();

	glColor3f(0.2, 0.2, 0.8);
	glRotatef(angle1 * 0.5, 0, 1, 0);
	drawSphere(90, 1, 15, 0, 0);

	glutSwapBuffers();
}

void update(int value)
{
	angle1 += rotateSpeed;
	angle2 -= rotateSpeed;
	cameraZoom += 0.01;

	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / height, 0.1f, 100.f);
	glMatrixMode(GL_MODELVIEW);
}

int main(int args, char** argv)
{
	glutInit(&args, argv);
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	const int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);

	windowPosY = (SCREEN_HEIGHT - windowHeight) / 2;
	windowPosX = (SCREEN_WIDTH - windowWidth) / 2;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow("CI PLAS PLAS");

	initGL();
	glutReshapeFunc(resize);
	glutDisplayFunc(display);

	glutTimerFunc(15, update, 0);
	glutMainLoop();
	
	return 0;
}