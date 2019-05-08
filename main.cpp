#include <iostream>
#include <GL/glut.h>

using namespace std;

class point {
public : float x, y, z;

  point(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
  }
};

// Vertices to draw a square
point cube[8] = { point(-200.0, -200.0,200.0),
		  point(200.0, -200.0, 200.0),
		  point(200.0, -200.0, -200.0),
		  point(-200.0, -200.0, -200.0),
		  point(-200.0, 200.0, 200.0),
		  point(200.0, 200.0, 200.0),
		  point(200.0, 200.0, -200.0),
		  point(-200.0, 200.0, -200.0)};

// Variables required for menu functioning
static int menu_id;
static int window;
static int value;

/***** FUNCTION DECLARATION *****/

void menu(int);
void createMenu(void);
void display(void);
void reshape(int, int);

void draw_house(void);
void draw_building(void);

void draw_triangle(void);
void draw_text(float, float, string);

void draw_cube(void);

/***** MAIN FUNCTION *****/

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Nature Amongst Humans");
  createMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
}

/***** FUNCTION DEFINITION *****/

// Function to create the menu option.
void createMenu(void) {
  menu_id = glutCreateMenu(menu);
  glutAddMenuEntry("House", 1);
  glutAddMenuEntry("Building", 2);
  glutAddMenuEntry("Quit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Function that assigns the appropriate value for the option chosen by the user.
// It destroys or closes the window and terminates the program if "Quit" option
// is chosen.
void menu(int num) {
  if(num == 0) {
    glutDestroyWindow(window);
    exit(0);
  }
  else
    value = num;
}


// Display callback function.
void display(void) {
  int i, j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  switch(value) {
  case 1: draw_house();
    //glClearColor(1.0, 0.0, 0.0, 1.0);
    //glColor3f(0.0, 0.0, 0.0);
    //draw_text(10, 10, "A house comes here");
    break;

  case 2: draw_building();
    //glClearColor(0.0, 1.0, 0.0, 1.0);
    //glColor3f(1.0, 1.0, 1.0);
    //draw_text(10, 10, "A building comes here");
    break;
  }
}

// Function to draw text in the window.
// NOTE : This function is used only for debugging purposes during the development.
void draw_text(float x, float y, string s) {
  int i;
  glRasterPos2f(x, y);
  for(i=0; s[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

  glFlush();
  glutSwapBuffers();
}

// Function for reshape callback.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if(w <= h)
    glOrtho(-500.0, 500.0, -500.0*(GLfloat)h / (GLfloat)w, 500.0*(GLfloat)h / (GLfloat)w, -500.0, 500.0);
  else
    glOrtho(-500.0*(GLfloat)w / (GLfloat)h, 500.0*(GLfloat)w / (GLfloat)h, -500.0, 500.0, -500.0, 500.0);

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

// Function to draw triangle
// NOTE: This function is used only to check if the menu option is working or not
// during the development phase.
void draw_triangle(void) {
  glBegin(GL_POLYGON);
  glVertex3f(100, 100, 0);
  glVertex3f(300, 100, 0);
  glVertex3f(200, 200, 0);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

// Function to draw house
void draw_house(void) {
  glPushMatrix();
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glRotatef(20.0, 1.0, 0.0, 0.0);
  glRotatef(-20.0, 0.0, 1.0, 0.0);
  draw_cube();
  glPopMatrix();
}

// Function to draw a cube
void draw_cube(void) {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(cube[0].x, cube[0].y, cube[0].z);
  glVertex3f(cube[1].x, cube[1].y, cube[1].z);
  glVertex3f(cube[2].x, cube[2].y, cube[2].z);
  glVertex3f(cube[3].x, cube[3].y, cube[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(cube[4].x, cube[4].y, cube[4].z);
  glVertex3f(cube[5].x, cube[5].y, cube[5].z);
  glVertex3f(cube[6].x, cube[6].y, cube[6].z);
  glVertex3f(cube[7].x, cube[7].y, cube[7].z);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(cube[0].x, cube[0].y, cube[0].z);
  glVertex3f(cube[1].x, cube[1].y, cube[1].z);
  glVertex3f(cube[5].x, cube[5].y, cube[5].z);
  glVertex3f(cube[4].x, cube[4].y, cube[4].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(cube[3].x, cube[3].y, cube[3].z);
  glVertex3f(cube[2].x, cube[2].y, cube[2].z);
  glVertex3f(cube[6].x, cube[6].y, cube[6].z);
  glVertex3f(cube[7].x, cube[7].y, cube[7].z);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(cube[0].x, cube[0].y, cube[0].z);
  glVertex3f(cube[3].x, cube[3].y, cube[3].z);
  glVertex3f(cube[7].x, cube[7].y, cube[7].z);
  glVertex3f(cube[4].x, cube[4].y, cube[4].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(cube[1].x, cube[1].y, cube[1].z);
  glVertex3f(cube[2].x, cube[2].y, cube[2].z);
  glVertex3f(cube[6].x, cube[6].y, cube[6].z);
  glVertex3f(cube[5].x, cube[5].y, cube[5].z);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

// Function to draw building
void draw_building(void) {
  glPushMatrix();
  draw_triangle();
  glPopMatrix();
}
