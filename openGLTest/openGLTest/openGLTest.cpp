#include <iostream>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "openGLTest.h"

using namespace std;
void display(void);
void init(void);
void idle(void);
void mouse(int a, int b, int c, int d);
void keyboard(unsigned char c, int x, int y);

unsigned int defaults(unsigned int d,int & w, int & h);
void reshape(int w, int h);
#define X .525731112119133606 
#define Z .850650808352039932
static GLfloat vdata[12][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

static GLuint tindices[20][3] = { 
  {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},    
  {1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},    
  {3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0}, 
  {10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7} 
};

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -3.0, 3.0);
}
static int rot = 0;
static float xaxis = 0;
static float yaxis = 0;

static int mouseDown = 0;
static int mouseX = 0;
static int mouseY = 0;

void display(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	if (mouseDown)
		if (mouseX != 0 && mouseY != 0)
			glRotatef(10, mouseX, mouseY, 0.0);
	glBegin(GL_TRIANGLES);    
	int i;
	for (i = 0; i < 20; i++) {
	   glColor3f(0, (GLfloat)i / 20 + 0.1,(GLfloat)i / 20 + 0.1);
	   glVertex3fv(&vdata[tindices[i][0]][0]); 
	   glVertex3fv(&vdata[tindices[i][1]][0]); 
	   glVertex3fv(&vdata[tindices[i][2]][0]); 
	}
	glEnd();

	glFlush();
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);

	int width = 500;
	int height = 500;
	unsigned int displayMode = GLUT_SINGLE | GLUT_RGB;
	displayMode = defaults(displayMode, width, height);

	glutInitDisplayMode (displayMode);
	glutInitContextVersion (3, 0);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

#ifdef DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitWindowSize (width, height); 
	glutInitWindowPosition (250, 250);
	int window = glutCreateWindow (argv[0]);
	init();
	cout << "Hello world!!!" << endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {
	return displayMode;
}
static int previousTime = 0;

void idle(void) {
	int tickTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = tickTime - previousTime;
	if (interval >= 1000 / 60) {
		previousTime = tickTime;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y) {
	xaxis = 0.0;
	yaxis = 0.0;
	switch(key) {
	case 'd':
		rot = (rot + 10) % 360;
		yaxis = 1.0;
		glutPostRedisplay();
		break;
	case 'w':
		rot = (rot + 10) % 360;
		xaxis = 1.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		mouseDown = 1;
		mouseY = x - 250;
		mouseX = y - 250;
		cout << mouseY << " " << mouseX << "\n";
	}
	else {
		mouseDown = 0;
	}
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glOrtho(-2.0, 2.0, -2.0, 2.0, -3.0, 3.0);
	glPopMatrix();
}