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

// Translate coordinates
point T(-150.0, 270.0, -150.0);
point C(0.0, 0.0, 0.0);

// Vertices for the ramps
point face1_ramp1[] = { 
  // Front
  point(-200.0, -100.0, 240.0),
  point(150.0, -100.0, 240.0),
  point(150.0, -90.0, 240.0),
  point(-200.0, -90.0, 240.0),
  // Side 1
  point(-200.0, -100.0, 200.0),
  point(-200.0, -100.0, 240.0),
  point(-200.0, -90.0, 240.0),
  point(-200.0, -90.0, 200.0),
  // Side 2
  point(150.0, -100.0, 200.0),
  point(150.0, -90.0, 200.0),
  point(150.0, -90.0, 240.0),
  point(150.0, -100.0, 240.0)};

point face1_ramp2[] = {
  // Front
  point(-150.0, 0.0, 240.0),
  point(200.0, 0.0, 240.0),
  point(200.0, 10.0, 240.0),
  point(-150.0, 10.0, 240.0),
  // Side 
  point(-150.0, 0.0, 200.0),
  point(-150.0, 0.0, 240.0),
  point(-150.0, 10.0, 240.0),
  point(-150.0, 10.0, 200.0),
  // Side 2
  point(200.0, 0.0, 200.0),
  point(200.0, 10.0, 200.0),
  point(200.0, 10.0, 240.0),
  point(200.0, 0.0, 240.0)};

point face1_ramp3[] = {
  // Front
  point(-200.0, 100.0, 240.0),
  point(150.0, 100.0, 240.0),
  point(150.0, 110.0, 240.0),
  point(-200.0, 110.0, 240.0),
  // Side 1
  point(-200.0, 100.0, 200.0),
  point(-200.0, 100.0, 240.0),
  point(-200.0, 110.0, 240.0),
  point(-200.0, 110.0, 200.0),
  // Side 2
  point(150.0, 100.0, 200.0),
  point(150.0, 110.0, 200.0),
  point(150.0, 110.0, 240.0),
  point(150.0, 100.0, 240.0)};

point face2_ramp1[] = {
  // Front
  point(240.0, -100.0, 200.0),
  point(240.0, -100.0, -150.0),
  point(240.0, -90.0, -150.0),
  point(240.0, -90.0, 200.0),
  // Side 1
  point(200.0, -100.0, 200.0),
  point(240.0, -100.0, 200.0),
  point(240.0, -90.0, 200.0),
  point(200.0, -90.0, 200.0),
  // Side 2
  point(200.0, -100.0, -150.0),
  point(200.0, -90.0, -150.0),
  point(240.0, -90.0, -150.0),
  point(240.0, -100.0, -150.0)};

point face2_ramp2[] = {
  // Front
  point(240.0, 0.0, 150.0),
  point(240.0, 0.0, -200.0),
  point(240.0, 10.0, -200.0),
  point(240.0, 10.0, 150.0),
  // Side 1
  point(200.0, 0.0, 150.0),
  point(240.0, 0.0, 150.0),
  point(240.0, 10.0, 150.0),
  point(200.0, 10.0, 150.0),
  // Side 2
  point(200.0, 0.0, -200.0),
  point(200.0, 10.0, -200.0),
  point(240.0, 10.0, -200.0),
  point(240.0, 0.0, -200.0)};

point face2_ramp3[] = {
  // Front
  point(240.0, 100.0, 200.0),
  point(240.0, 100.0, -150.0),
  point(240.0, 110.0, -150.0),
  point(240.0, 110.0, 200.0),
  // Side 1
  point(200.0, 100.0, 200.0),
  point(240.0, 100.0, 200.0),
  point(240.0, 110.0, 200.0),
  point(200.0, 110.0, 200.0),
  // Side 2
  point(200.0, 100.0, -150.0),
  point(200.0, 110.0, -150.0),
  point(240.0, 110.0, -150.0),
  point(240.0, 100.0, -150.0)};

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
static int mouse_input;
static int theta;
static int count=0;
static int flag = 0;

/***** FUNCTION DECLARATION *****/
void mouse(int,int,int,int);
void incpot(int);
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
void make_ramp(point[], int);
void draw_grass(void);

/***** MAIN FUNCTION *****/

int main(int argc, char **argv) {
  key_input = 0;
  theta = 0;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Nature Amongst Humans");
  glutMouseFunc(mouse);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
}

/***** FUNCTION DEFINITION *****/

//MOUSE function for left and right button's
void mouse(int btn,int state,int x,int y)
{
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && mouse_input == 1) {
    count++;
    incpot(count);
  }

  if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    createMenu();
}

// Function to create the menu option.
void createMenu(void) {
  menu_id = glutCreateMenu(menu);
  glutAddMenuEntry("House", 1);
  glutAddMenuEntry("Building", 2);
  glutAddMenuEntry("Quit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutPostRedisplay();
}

void incpot(int count) {
  if(count <= 7) {
    C.x += 60.0;
    C.y -= 10.0;
    C.z += 60.0;
    glPushMatrix();
    glTranslatef(C.x, C.y, C.z);
    glScalef(1.5, 1.5, 1.5);
    draw_pot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(C.x, C.y-15.0, C.z);
    glScalef(1.5, 1.5, 1.5);
    draw_circle(0.0, 50.0, 20.0);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    if (count == 7)
      flag = 1;
  }
  else if(count <= 15 && count > 7) {
    if(flag == 1) {
      C.x = -150.0;
      C.z = 150.0;
      C.y = 200.0;
      flag = 0;
      cout << "flag : " << flag << endl;
    }
    else {
      C.x += 60.0;
      C.y -= 10.0;
      C.z += 60.0;
    }

    glPushMatrix();
    glTranslatef(C.x, C.y, C.z);
    glScalef(1.5, 1.5, 1.5);
    draw_pot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(C.x, C.y-15.0, C.z);
    glScalef(1.5, 1.5, 1.5);
    draw_circle(0.0, 50.0, 20.0);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
  }
  else {
    cout << "Limit exceeded" << endl;
  }
}

// Function that assigns the appropriate value for the option chosen by the user
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
    mouse_input = 1;
    C = T;
    count = 0;
    draw_house();
    break;

  case 2: key_input = 1;
    mouse_input = 0;
    draw_building();
    break;
  }
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
  draw_door();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(T.x, T.y, T.z);
  glScalef(1.5, 1.5, 1.5);
  draw_pot();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(T.x, T.y-15.0, T.z);
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

  draw_grass();

  glPopMatrix();
}


void make_ramp(point ramp[], float a, float b, float c, float p=0, float q=0, float r=0, int flag = 0) {
  float val = 0;
  if(flag == 1)
    val = 10.0;

  glBegin(GL_POLYGON);
  glVertex3f(a*ramp[0].x+p, b*ramp[0].y+q, c*ramp[0].z+r);
  glVertex3f(a*ramp[1].x+p, b*ramp[1].y+q, c*ramp[1].z+r);
  glVertex3f(a*ramp[2].x+p, b*ramp[2].y+q+val, c*ramp[2].z+r);
  glVertex3f(a*ramp[3].x+p, b*ramp[3].y+q+val, c*ramp[3].z+r);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(a*ramp[4].x+p, b*ramp[4].y+q, c*ramp[4].z+r);
  glVertex3f(a*ramp[5].x+p, b*ramp[5].y+q, c*ramp[5].z+r);
  glVertex3f(a*ramp[6].x+p, b*ramp[6].y+q+val, c*ramp[6].z+r);
  glVertex3f(a*ramp[7].x+p, b*ramp[7].y+q+val, c*ramp[7].z+r);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(a*ramp[8].x+p, b*ramp[8].y+q, c*ramp[8].z+r);
  glVertex3f(a*ramp[9].x+p, b*ramp[9].y+q+val, c*ramp[9].z+r);
  glVertex3f(a*ramp[10].x+p, b*ramp[10].y+q+val, c*ramp[10].z+r);
  glVertex3f(a*ramp[11].x+p, b*ramp[11].y+q, c*ramp[11].z+r);
  glEnd();

  glFlush();
  glutSwapBuffers();
}

void draw_ramps() {
  glColor3f(0.0, 0.0, 0.0);

  make_ramp(face1_ramp1, 1, 1, 1);
  make_ramp(face1_ramp2, 1, 1, 1);
  make_ramp(face1_ramp3, 1, 1, 1);

  make_ramp(face2_ramp1, 1, 1, 1);
  make_ramp(face2_ramp2, 1, 1, 1);
  make_ramp(face2_ramp3, 1, 1, 1);

  make_ramp(face1_ramp1, 1, 1, -1);
  make_ramp(face1_ramp2, 1, 1, -1);
  make_ramp(face1_ramp3, 1, 1, -1);

  make_ramp(face2_ramp1, -1, 1, 1);
  make_ramp(face2_ramp2, -1, 1, 1);
  make_ramp(face2_ramp3, -1, 1, 1);
}

void draw_grass() {
  glColor3f(51/255.0, 102/255.0, 0.0);

  make_ramp(face1_ramp1, 1, 1, 1, 0.0, 10.0, 0.0, 1);
  make_ramp(face1_ramp2, 1, 1, 1, 0.0, 10.0, 0.0, 1);
  make_ramp(face1_ramp3, 1, 1, 1, 0.0, 10.0, 0.0, 1);

  make_ramp(face2_ramp1, 1, 1, 1, 0.0, 10.0, 0.0, 1);
  make_ramp(face2_ramp2, 1, 1, 1, 0.0, 10.0, 0.0, 1);
  make_ramp(face2_ramp3, 1, 1, 1, 0.0, 10.0, 0.0, 1);

  make_ramp(face1_ramp1, 1, 1, -1, 0.0, 10.0, 0.0, 1);
  make_ramp(face1_ramp2, 1, 1, -1, 0.0, 10.0, 0.0, 1);
  make_ramp(face1_ramp3, 1, 1, -1, 0.0, 10.0, 0.0, 1);

  make_ramp(face2_ramp1, -1, 1, 1, 0.0, 10.0, 0.0, 1);
  make_ramp(face2_ramp2, -1, 1, 1, 0.0, 10.0, 0.0, 1);
  make_ramp(face2_ramp3, -1, 1, 1, 0.0, 10.0, 0.0, 1);
}
