#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

const float PI = 3.141;

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

// Vertices to draw a door for the house
point door[4] = { point(-50.0, -200.0, 201.0),
		  point(50.0, -200.0, 201.0),
		  point(-50.0, 75.0, 201.0),
		  point(50.0, 75.0, 201.0)};

// Vertices to draw a pot
point pot[4] = { point(-10.0, 0.0, 0.0),
		 point(10.0, 0.0, 0.0),
		 point(20.0, 30.0, 0.0),
		 point(-20.0, 30.0, 0.0)};

// Vertices for the ramps
point face1_ramp1[] = { 
  // Front
  point(-200.0, -100.0, 220.0),
  point(150.0, -100.0, 220.0),
  point(150.0, -90.0, 220.0),
  point(-200.0, -90.0, 220.0),
  // Side 1
  point(-200.0, -100.0, 200.0),
  point(-200.0, -100.0, 220.0),
  point(-200.0, -90.0, 220.0),
  point(-200.0, -90.0, 200.0),
  // Side 2
  point(150.0, -100.0, 200.0),
  point(150.0, -90.0, 200.0),
  point(150.0, -90.0, 220.0),
  point(150.0, -100.0, 220.0)};

point face1_ramp2[] = {
  // Front
  point(-150.0, 0.0, 220.0),
  point(200.0, 0.0, 220.0),
  point(200.0, 10.0, 220.0),
  point(-150.0, 10.0, 220.0),
  // Side 
  point(-150.0, 0.0, 200.0),
  point(-150.0, 0.0, 220.0),
  point(-150.0, 10.0, 220.0),
  point(-150.0, 10.0, 200.0),
  // Side 2
  point(200.0, 0.0, 200.0),
  point(200.0, 10.0, 200.0),
  point(200.0, 10.0, 220.0),
  point(200.0, 0.0, 220.0)};

point face1_ramp3[] = {
  // Front
  point(-200.0, 100.0, 220.0),
  point(150.0, 100.0, 220.0),
  point(150.0, 110.0, 220.0),
  point(-200.0, 110.0, 220.0),
  // Side 1
  point(-200.0, 100.0, 200.0),
  point(-200.0, 100.0, 220.0),
  point(-200.0, 110.0, 220.0),
  point(-200.0, 110.0, 200.0),
  // Side 2
  point(150.0, 100.0, 200.0),
  point(150.0, 110.0, 200.0),
  point(150.0, 110.0, 220.0),
  point(150.0, 100.0, 220.0)};

point face2_ramp1[] = {
  // Front
  point(220.0, -100.0, 200.0),
  point(220.0, -100.0, -150.0),
  point(220.0, -90.0, -150.0),
  point(220.0, -90.0, 200.0),
  // Side 1
  point(200.0, -100.0, 200.0),
  point(220.0, -100.0, 200.0),
  point(220.0, -90.0, 200.0),
  point(200.0, -90.0, 200.0),
  // Side 2
  point(200.0, -100.0, -150.0),
  point(220.0, -100.0, -150.0),
  point(220.0, -90.0, -150.0),
  point(200.0, -90.0, -150.0)};

point face2_ramp2[] = {
  // Front
  point(220.0, 0.0, 150.0),
  point(220.0, 0.0, -200.0),
  point(220.0, 10.0, -200.0),
  point(220.0, 10.0, 150.0),
  // Side 1
  point(200.0, 0.0, 150.0),
  point(220.0, 0.0, 150.0),
  point(220.0, 10.0, 150.0),
  point(200.0, 10.0, 150.0),
  // Side 2
  point(200.0, 0.0, -200.0),
  point(220.0, 0.0, -200.0),
  point(220.0, 10.0, -200.0),
  point(200.0, 10.0, -200.0)};

point face2_ramp3[] = {
  // Front
  point(220.0, 100.0, 200.0),
  point(220.0, 100.0, -150.0),
  point(220.0, 110.0, -150.0),
  point(220.0, 110.0, 200.0),
  // Side 1
  point(200.0, 100.0, 200.0),
  point(220.0, 100.0, 200.0),
  point(220.0, 110.0, 200.0),
  point(200.0, 110.0, 200.0),
  // Side 2
  point(200.0, 100.0, -150.0),
  point(220.0, 100.0, -150.0),
  point(220.0, 110.0, -150.0),
  point(200.0, 110.0, -150.0)};

// Color of the house in RGB format
GLfloat house_color[3][3] = {{1.0, 0.6, 0.2},
		       {1.0, 0.7, 0.4},
		       {0.9, 0.61, 0.32}};

// Color of the building in RGB format
GLfloat building_color[3][3] = {{96/255.0, 96/255.0, 96/255.0},
				{96/255.0, 96/255.0, 96/255.0},
				{64/255.0, 64/255.0, 64/255.0}};

// Variables required for menu functioning
static int menu_id;
static int window;
static int value;
static int key_input;
static int theta;

/***** FUNCTION DECLARATION *****/

void menu(int);
void createMenu(void);
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);

void draw_text(float x, float y, string);
void draw_triangle(void);

void draw_house(void);
void draw_building(void);

void draw_cube(GLfloat colors[][3]);
void draw_door(void);
void draw_pot(void);
void draw_circle(float, float, float);

void draw_ramps(void);

/***** MAIN FUNCTION *****/

int main(int argc, char **argv) {
  key_input = 0;
  theta = 0;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Nature Amongst Humans");
  createMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
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
  case 1: key_input = 0;
    draw_house();
    break;

  case 2: key_input = 1;
    draw_building();
    break;

  case 3: draw_triangle();
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

// Function to draw triangle.
// NOTE : This function is used only for debugging purposes during the development.
void draw_triangle(void) {
  cout << "Triangle start" << endl;
  glBegin(GL_POLYGON);
  glVertex3f(-100.0, 0.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);
  glVertex3f(0.0, 100.0, 0.0);
  glEnd();

  glFlush();
  glutSwapBuffers();

  cout << "Triangle end" << endl;
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

// Function for keyboard callback
void keyboard(unsigned char key, int x, int y) {
  if(key == 'q' || key == 'Q') {
    cout << "Terminating the window." << endl;
    glutDestroyWindow(window);
    exit(0);
  }

  if(key == 'h' || key == 'H') {
    value = 1;
    display();
  }

  if(key == 'b' || key == 'B') {
    value = 2;
    display();
  }

  if(key_input == 1) {
    switch(key) {
    case 'A':
    case 'a':
      theta += 10.0;
      display();
      break;

    case 'D':
    case 'd':
      theta -= 10.0;
      display();
      break;

    default:
      cout << "Invalid key input." << endl;
      glutPostRedisplay();
      break;
    }
  }
  else {
    cout << "Keyboard input is considered only for buildings." << endl;
    glutPostRedisplay();
  }
}

// Function to draw a cube
void draw_cube(GLfloat colors[][3]) {
  glColor3fv(colors[0]);
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

  glColor3fv(colors[1]);
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

  glColor3fv(colors[2]);
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

// Function to draw house
void draw_house(void) {
  glPushMatrix();
  glClearColor(115/255.0, 230/255.0, 0.0, 1.0);
  glRotatef(20.0, 1.0, 0.0, 0.0);
  glRotatef(-20.0, 0.0, 1.0, 0.0);
  glScalef(1.5, 1.0, 1.3);
  draw_cube(house_color);

  //glRotatef(20.0, 1.0, 0.0, 0.0);
  //glRotatef(-20.0, 0.0, 1.0, 0.0);
  draw_door();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, 215.0, 0.0);
  glScalef(1.5, 1.5, 1.5);
  draw_pot();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0, 200.0, 0.0);
  glScalef(1.5, 1.5, 1.5);
  draw_circle(0.0, 50.0, 20.0);
  glPopMatrix();
}


// Function to draw a door
void draw_door(void) {
  glColor3f(0.58, 0.23, 0.06);
  glBegin(GL_POLYGON);
  glVertex3f(door[0].x, door[0].y, door[0].z);
  glVertex3f(door[1].x, door[1].y, door[1].z);
  glVertex3f(door[3].x, door[3].y, door[3].z);
  glVertex3f(door[2].x, door[2].y, door[2].z);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

// Function to draw pots
void draw_pot(void) {
  glColor3f(0.58, 0.23, 0.06);
  glBegin(GL_POLYGON);
  glVertex3f(pot[0].x, pot[0].y, pot[0].z);
  glVertex3f(pot[1].x, pot[1].y, pot[1].z);
  glVertex3f(pot[2].x, pot[2].y, pot[2].z);
  glVertex3f(pot[3].x, pot[3].y, pot[3].z);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

// Function to draw circle
void draw_circle(float x, float y, float r) {
  glColor3f(51/255.0, 102/255.0, 0.0);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x, y);
  
  for(float i = 0; i <= 2 * PI + 0.1; i += 0.1)
    glVertex2f(x+sin(i)*r, y+cos(i)*r);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

// Function to draw building
void draw_building(void) {
  glPushMatrix();
  glClearColor(0.0, 255/255.0, 255/255.0, 1.0);
  glRotatef(theta, 0.0, 1.0, 0.0);
  glScalef(1.0, 2.0, 1.0);
  draw_cube(building_color);
  draw_ramps();
  glPopMatrix();
}

void draw_ramps(void) {
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp1[0].x, face1_ramp1[0].y, face1_ramp1[0].z);
  glVertex3f(face1_ramp1[1].x, face1_ramp1[1].y, face1_ramp1[1].z);
  glVertex3f(face1_ramp1[2].x, face1_ramp1[2].y, face1_ramp1[2].z);
  glVertex3f(face1_ramp1[3].x, face1_ramp1[3].y, face1_ramp1[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp1[4].x, face1_ramp1[4].y, face1_ramp1[4].z);
  glVertex3f(face1_ramp1[5].x, face1_ramp1[5].y, face1_ramp1[5].z);
  glVertex3f(face1_ramp1[6].x, face1_ramp1[6].y, face1_ramp1[6].z);
  glVertex3f(face1_ramp1[7].x, face1_ramp1[7].y, face1_ramp1[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp1[8].x, face1_ramp1[8].y, face1_ramp1[8].z);
  glVertex3f(face1_ramp1[9].x, face1_ramp1[9].y, face1_ramp1[9].z);
  glVertex3f(face1_ramp1[10].x, face1_ramp1[10].y, face1_ramp1[10].z);
  glVertex3f(face1_ramp1[11].x, face1_ramp1[11].y, face1_ramp1[11].z);
  glEnd();

  // Face 1 Ramp 2
  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp2[0].x, face1_ramp2[0].y, face1_ramp2[0].z);
  glVertex3f(face1_ramp2[1].x, face1_ramp2[1].y, face1_ramp2[1].z);
  glVertex3f(face1_ramp2[2].x, face1_ramp2[2].y, face1_ramp2[2].z);
  glVertex3f(face1_ramp2[3].x, face1_ramp2[3].y, face1_ramp2[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp2[4].x, face1_ramp2[4].y, face1_ramp2[4].z);
  glVertex3f(face1_ramp2[5].x, face1_ramp2[5].y, face1_ramp2[5].z);
  glVertex3f(face1_ramp2[6].x, face1_ramp2[6].y, face1_ramp2[6].z);
  glVertex3f(face1_ramp2[7].x, face1_ramp2[7].y, face1_ramp2[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp2[8].x, face1_ramp2[8].y, face1_ramp2[8].z);
  glVertex3f(face1_ramp2[9].x, face1_ramp2[9].y, face1_ramp2[9].z);
  glVertex3f(face1_ramp2[10].x, face1_ramp2[10].y, face1_ramp2[10].z);
  glVertex3f(face1_ramp2[11].x, face1_ramp2[11].y, face1_ramp2[11].z);
  glEnd();

  // Face 1 Ramp 3
  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp3[0].x, face1_ramp3[0].y, face1_ramp3[0].z);
  glVertex3f(face1_ramp3[1].x, face1_ramp3[1].y, face1_ramp3[1].z);
  glVertex3f(face1_ramp3[2].x, face1_ramp3[2].y, face1_ramp3[2].z);
  glVertex3f(face1_ramp3[3].x, face1_ramp3[3].y, face1_ramp3[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp3[4].x, face1_ramp3[4].y, face1_ramp3[4].z);
  glVertex3f(face1_ramp3[5].x, face1_ramp3[5].y, face1_ramp3[5].z);
  glVertex3f(face1_ramp3[6].x, face1_ramp3[6].y, face1_ramp3[6].z);
  glVertex3f(face1_ramp3[7].x, face1_ramp3[7].y, face1_ramp3[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp3[8].x, face1_ramp3[8].y, face1_ramp3[8].z);
  glVertex3f(face1_ramp3[9].x, face1_ramp3[9].y, face1_ramp3[9].z);
  glVertex3f(face1_ramp3[10].x, face1_ramp3[10].y, face1_ramp3[10].z);
  glVertex3f(face1_ramp3[11].x, face1_ramp3[11].y, face1_ramp3[11].z);
  glEnd();

  // Face 2 Ramp 1
  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp1[0].x, face2_ramp1[0].y, face2_ramp1[0].z);
  glVertex3f(face2_ramp1[1].x, face2_ramp1[1].y, face2_ramp1[1].z);
  glVertex3f(face2_ramp1[2].x, face2_ramp1[2].y, face2_ramp1[2].z);
  glVertex3f(face2_ramp1[3].x, face2_ramp1[3].y, face2_ramp1[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp1[4].x, face2_ramp1[4].y, face2_ramp1[4].z);
  glVertex3f(face2_ramp1[5].x, face2_ramp1[5].y, face2_ramp1[5].z);
  glVertex3f(face2_ramp1[6].x, face2_ramp1[6].y, face2_ramp1[6].z);
  glVertex3f(face2_ramp1[7].x, face2_ramp1[7].y, face2_ramp1[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp1[8].x, face2_ramp1[8].y, face2_ramp1[8].z);
  glVertex3f(face2_ramp1[9].x, face2_ramp1[9].y, face2_ramp1[9].z);
  glVertex3f(face2_ramp1[10].x, face2_ramp1[10].y, face2_ramp1[10].z);
  glVertex3f(face2_ramp1[11].x, face2_ramp1[11].y, face2_ramp1[11].z);
  glEnd();

  // Face 2 Ramp 2
  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp2[0].x, face2_ramp2[0].y, face2_ramp2[0].z);
  glVertex3f(face2_ramp2[1].x, face2_ramp2[1].y, face2_ramp2[1].z);
  glVertex3f(face2_ramp2[2].x, face2_ramp2[2].y, face2_ramp2[2].z);
  glVertex3f(face2_ramp2[3].x, face2_ramp2[3].y, face2_ramp2[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp2[4].x, face2_ramp2[4].y, face2_ramp2[4].z);
  glVertex3f(face2_ramp2[5].x, face2_ramp2[5].y, face2_ramp2[5].z);
  glVertex3f(face2_ramp2[6].x, face2_ramp2[6].y, face2_ramp2[6].z);
  glVertex3f(face2_ramp2[7].x, face2_ramp2[7].y, face2_ramp2[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp2[8].x, face2_ramp2[8].y, face2_ramp2[8].z);
  glVertex3f(face2_ramp2[9].x, face2_ramp2[9].y, face2_ramp2[9].z);
  glVertex3f(face2_ramp2[10].x, face2_ramp2[10].y, face2_ramp2[10].z);
  glVertex3f(face2_ramp2[11].x, face2_ramp2[11].y, face2_ramp2[11].z);
  glEnd();

  // Face 2 Ramp 3
  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp3[0].x, face2_ramp3[0].y, face2_ramp3[0].z);
  glVertex3f(face2_ramp3[1].x, face2_ramp3[1].y, face2_ramp3[1].z);
  glVertex3f(face2_ramp3[2].x, face2_ramp3[2].y, face2_ramp3[2].z);
  glVertex3f(face2_ramp3[3].x, face2_ramp3[3].y, face2_ramp3[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp3[4].x, face2_ramp3[4].y, face2_ramp3[4].z);
  glVertex3f(face2_ramp3[5].x, face2_ramp3[5].y, face2_ramp3[5].z);
  glVertex3f(face2_ramp3[6].x, face2_ramp3[6].y, face2_ramp3[6].z);
  glVertex3f(face2_ramp3[7].x, face2_ramp3[7].y, face2_ramp3[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face2_ramp3[8].x, face2_ramp3[8].y, face2_ramp3[8].z);
  glVertex3f(face2_ramp3[9].x, face2_ramp3[9].y, face2_ramp3[9].z);
  glVertex3f(face2_ramp3[10].x, face2_ramp3[10].y, face2_ramp3[10].z);
  glVertex3f(face2_ramp3[11].x, face2_ramp3[11].y, face2_ramp3[11].z);
  glEnd();

  // Face 3 Ramp 1
  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp1[0].x, face1_ramp1[0].y, -1*face1_ramp1[0].z);
  glVertex3f(face1_ramp1[1].x, face1_ramp1[1].y, -1*face1_ramp1[1].z);
  glVertex3f(face1_ramp1[2].x, face1_ramp1[2].y, -1*face1_ramp1[2].z);
  glVertex3f(face1_ramp1[3].x, face1_ramp1[3].y, -1*face1_ramp1[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp1[4].x, face1_ramp1[4].y, -1*face1_ramp1[4].z);
  glVertex3f(face1_ramp1[5].x, face1_ramp1[5].y, -1*face1_ramp1[5].z);
  glVertex3f(face1_ramp1[6].x, face1_ramp1[6].y, -1*face1_ramp1[6].z);
  glVertex3f(face1_ramp1[7].x, face1_ramp1[7].y, -1*face1_ramp1[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp1[8].x, face1_ramp1[8].y, -1*face1_ramp1[8].z);
  glVertex3f(face1_ramp1[9].x, face1_ramp1[9].y, -1*face1_ramp1[9].z);
  glVertex3f(face1_ramp1[10].x, face1_ramp1[10].y, -1*face1_ramp1[10].z);
  glVertex3f(face1_ramp1[11].x, face1_ramp1[11].y, -1*face1_ramp1[11].z);
  glEnd();

  // Face 3 Ramp 2
  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp2[0].x, face1_ramp2[0].y, -1*face1_ramp2[0].z);
  glVertex3f(face1_ramp2[1].x, face1_ramp2[1].y, -1*face1_ramp2[1].z);
  glVertex3f(face1_ramp2[2].x, face1_ramp2[2].y, -1*face1_ramp2[2].z);
  glVertex3f(face1_ramp2[3].x, face1_ramp2[3].y, -1*face1_ramp2[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp2[4].x, face1_ramp2[4].y, -1*face1_ramp2[4].z);
  glVertex3f(face1_ramp2[5].x, face1_ramp2[5].y, -1*face1_ramp2[5].z);
  glVertex3f(face1_ramp2[6].x, face1_ramp2[6].y, -1*face1_ramp2[6].z);
  glVertex3f(face1_ramp2[7].x, face1_ramp2[7].y, -1*face1_ramp2[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp2[8].x, face1_ramp2[8].y, -1*face1_ramp2[8].z);
  glVertex3f(face1_ramp2[9].x, face1_ramp2[9].y, -1*face1_ramp2[9].z);
  glVertex3f(face1_ramp2[10].x, face1_ramp2[10].y, -1*face1_ramp2[10].z);
  glVertex3f(face1_ramp2[11].x, face1_ramp2[11].y, -1*face1_ramp2[11].z);
  glEnd();

  // Face 3 Ramp 3
  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp3[0].x, face1_ramp3[0].y, -1*face1_ramp3[0].z);
  glVertex3f(face1_ramp3[1].x, face1_ramp3[1].y, -1*face1_ramp3[1].z);
  glVertex3f(face1_ramp3[2].x, face1_ramp3[2].y, -1*face1_ramp3[2].z);
  glVertex3f(face1_ramp3[3].x, face1_ramp3[3].y, -1*face1_ramp3[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp3[4].x, face1_ramp3[4].y, -1*face1_ramp3[4].z);
  glVertex3f(face1_ramp3[5].x, face1_ramp3[5].y, -1*face1_ramp3[5].z);
  glVertex3f(face1_ramp3[6].x, face1_ramp3[6].y, -1*face1_ramp3[6].z);
  glVertex3f(face1_ramp3[7].x, face1_ramp3[7].y, -1*face1_ramp3[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(face1_ramp3[8].x, face1_ramp3[8].y, -1*face1_ramp3[8].z);
  glVertex3f(face1_ramp3[9].x, face1_ramp3[9].y, -1*face1_ramp3[9].z);
  glVertex3f(face1_ramp3[10].x, face1_ramp3[10].y, -1*face1_ramp3[10].z);
  glVertex3f(face1_ramp3[11].x, face1_ramp3[11].y, -1*face1_ramp3[11].z);
  glEnd();

  // Face 4 Ramp 1
  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp1[0].x, face2_ramp1[0].y, face2_ramp1[0].z);
  glVertex3f(-1*face2_ramp1[1].x, face2_ramp1[1].y, face2_ramp1[1].z);
  glVertex3f(-1*face2_ramp1[2].x, face2_ramp1[2].y, face2_ramp1[2].z);
  glVertex3f(-1*face2_ramp1[3].x, face2_ramp1[3].y, face2_ramp1[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp1[4].x, face2_ramp1[4].y, face2_ramp1[4].z);
  glVertex3f(-1*face2_ramp1[5].x, face2_ramp1[5].y, face2_ramp1[5].z);
  glVertex3f(-1*face2_ramp1[6].x, face2_ramp1[6].y, face2_ramp1[6].z);
  glVertex3f(-1*face2_ramp1[7].x, face2_ramp1[7].y, face2_ramp1[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp1[8].x, face2_ramp1[8].y, face2_ramp1[8].z);
  glVertex3f(-1*face2_ramp1[9].x, face2_ramp1[9].y, face2_ramp1[9].z);
  glVertex3f(-1*face2_ramp1[10].x, face2_ramp1[10].y, face2_ramp1[10].z);
  glVertex3f(-1*face2_ramp1[11].x, face2_ramp1[11].y, face2_ramp1[11].z);
  glEnd();

  // Face 4 Ramp 2
  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp2[0].x, face2_ramp2[0].y, face2_ramp2[0].z);
  glVertex3f(-1*face2_ramp2[1].x, face2_ramp2[1].y, face2_ramp2[1].z);
  glVertex3f(-1*face2_ramp2[2].x, face2_ramp2[2].y, face2_ramp2[2].z);
  glVertex3f(-1*face2_ramp2[3].x, face2_ramp2[3].y, face2_ramp2[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp2[4].x, face2_ramp2[4].y, face2_ramp2[4].z);
  glVertex3f(-1*face2_ramp2[5].x, face2_ramp2[5].y, face2_ramp2[5].z);
  glVertex3f(-1*face2_ramp2[6].x, face2_ramp2[6].y, face2_ramp2[6].z);
  glVertex3f(-1*face2_ramp2[7].x, face2_ramp2[7].y, face2_ramp2[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp2[8].x, face2_ramp2[8].y, face2_ramp2[8].z);
  glVertex3f(-1*face2_ramp2[9].x, face2_ramp2[9].y, face2_ramp2[9].z);
  glVertex3f(-1*face2_ramp2[10].x, face2_ramp2[10].y, face2_ramp2[10].z);
  glVertex3f(-1*face2_ramp2[11].x, face2_ramp2[11].y, face2_ramp2[11].z);
  glEnd();

  // Face 4 Ramp 3
  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp3[0].x, face2_ramp3[0].y, face2_ramp3[0].z);
  glVertex3f(-1*face2_ramp3[1].x, face2_ramp3[1].y, face2_ramp3[1].z);
  glVertex3f(-1*face2_ramp3[2].x, face2_ramp3[2].y, face2_ramp3[2].z);
  glVertex3f(-1*face2_ramp3[3].x, face2_ramp3[3].y, face2_ramp3[3].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp3[4].x, face2_ramp3[4].y, face2_ramp3[4].z);
  glVertex3f(-1*face2_ramp3[5].x, face2_ramp3[5].y, face2_ramp3[5].z);
  glVertex3f(-1*face2_ramp3[6].x, face2_ramp3[6].y, face2_ramp3[6].z);
  glVertex3f(-1*face2_ramp3[7].x, face2_ramp3[7].y, face2_ramp3[7].z);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-1*face2_ramp3[8].x, face2_ramp3[8].y, face2_ramp3[8].z);
  glVertex3f(-1*face2_ramp3[9].x, face2_ramp3[9].y, face2_ramp3[9].z);
  glVertex3f(-1*face2_ramp3[10].x, face2_ramp3[10].y, face2_ramp3[10].z);
  glVertex3f(-1*face2_ramp3[11].x, face2_ramp3[11].y, face2_ramp3[11].z);
  glEnd();

  glFlush();
  glutSwapBuffers();
}
