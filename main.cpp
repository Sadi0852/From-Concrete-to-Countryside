#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
// linkers for using sound
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

int transitionSequence = 1;

////city variables////

float tree1 = 3.0f;
float tree2 = 10.0f;
float tree3 = 17.0f;
float tree4 = 24.0f;
float tree5 = 31.0f;
float tree6 = 38.0f;
float tree7 = 45.0f;
float tree8 = 52.0f;
float tree9 = 59.0f;
float tree10 = 66.0f;
float tree11 = 73.0f;
float tree12 = 80.0f;
float tree13 = 87.0f;
float tree14 = 94.0f;

float cloud1 = 20.0f;
float cloud2 = 75.0f;

float plane = 220;

float sun = 100.0f;
float moon = 200.0f;
float skyRed = 0.5f, skyGreen = 0.8f, skyBlue = 0.9f;

float car1_x = 10.0f;   // Starting position of the first car
float car2_x = 40.0f;   // Starting position of the second car
float car3_x = 70.0f;   // Starting position of the third car

float speed = 0.5f;
const float SPEED_CHANGE_FACTOR = 0.4f;
// Initialize the projection and background color

////////////////////// rail variables
float _run = 0.0;
float _run1 = 0.0;
float _run2 = 0.0;
float _run3 = 0.0;
float _rain = 0.0;
float _nt = 0.0;
float _ang_tri = 0.0;

bool onOff;
bool frd = true;
bool bck = false;

bool night = false;
///////////////////// rail variables

////////////////////// village variables
float _moveA = 0.0f;
float _moveB = 0.0f;
float _moveC = 0.0f;
float _angle1 = 0.0f;
float updateMove = 0.13;
float updateAngle = 2.0;
// float speed = 0.02f;
////////////////////// village variables

void initGL() {
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    if (transitionSequence == 1 || transitionSequence == 2) {
        // gluOrtho2D(0.0, 100.0, 0.0, 100.0);
    } else if (transitionSequence == 3) {
        // gluOrtho2D(0.0, 100.0, 0.0, 100.0);
        // gluOrtho2D(-12, 38, -19, 14);
        // gluOrtho2D(0.0, 50.0, 0.0, 50.0);
        // glLoadIdentity(); //Reset the drawing perspective
        // gluOrtho2D(-12,38,-19,14);//range
        // glMatrixMode(GL_MODELVIEW);
    }
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
}

// Helper function to draw circles
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy) {
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawtreeC(float x, float y, float length, float r) {
    // Body of the car
    glColor3f(0.36f, 0.25f, 0.20f);
    glRectf(x, 24.0f, x + 1, 30.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    circle(1.8f, 2.5f, x - 1.50f, 30.0f);
    circle(1.8f, 2.5f, x + 1.50f, 30.0f);
    circle(1.8f, 2.5f, x + 0.50f, 34.0f);
}

float angle = 0.0f;  // Rotation angle for the wheels

// Function to draw wheels of the car
void drawWheel(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);            // Move to the wheel's position
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate the wheel
    glColor3f(0.0f, 0.0f, 0.0f);         // Color of the wheel

    // Draw the wheel as a circle
    glBegin(GL_POLYGON);
    const int num_segments =
        30;  // Number of segments to approximate the circle
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.14159f * float(i) / float(num_segments);
        float x_circle = 3.0f * cosf(theta);
        float y_circle = 3.0f * sinf(theta);
        glVertex2f(x_circle, y_circle);
    }
    glEnd();

    glPopMatrix();
}

void drawplane(float x, float y) {
    glColor3ub(212, 205, 187);  // Sets color to #D4CDBB
    drawRectangle(x - 5, 82.0f, x + 9, 87.0f);
    drawTriangle(x - 9, 82.0f, x - 5, 82.0f, x - 5, 87.0f);  // body

    drawTriangle(x - 8, 83.0f, x - 5, 83.0f, x - 5, 86.0f);   // body
    drawTriangle(x + 9, 82.0f, x + 11, 87.0f, x + 9, 87.0f);  // body
    drawTriangle(x - 5, 84.0f, x - 1, 84.0f, x + 3, 73.0f);   // wingy
    drawTriangle(x - 5, 84.0f, x - 1, 84.0f, x + 3, 95.0f);   // wingy2
    drawRectangle(x + 9, 87.0f, x + 10, 90.0f);

    glColor3ub(255, 215, 0);  // Sets color to Gold (#FFD700)
                              // Sets color to Silver (#C0C0C0)
    drawTriangle(x - 8.0f, 83.0f, x - 5, 83.0f, x - 5, 86.0f);  // body
}

// Draw the car for the city scene
void drawCar(float x, float y, float length, float height, float r, float g,
             float b) {
    // Body of the car
    glColor3f(r, g, b);  // Car color
    glRectf(x, y, x + length + 2, y + height - 5);

    // Windows of the car (now tilted)
    glColor3f(0.0f, 0.8f, 1.0f);  // Light blue windows
    glBegin(GL_POLYGON);          // Draw a trapezoid for tilted windows
    glVertex2f(x + 3.0f, y + height / 2);  // Bottom-left (near the car body)
    glVertex2f(x + length - 3.0f,
               y + height / 2);  // Bottom-right (near the car body)
    glVertex2f(x + length - 7.0f, y + height);  // Top-right (shorter width)
    glVertex2f(x + 7.0f, y + height);           // Top-left (shorter width)
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);  // Dark gray road
    glRectf(x + 10, y + 5, x + length - 9, y + height);


    //car light
    if (moon > -10.0f && moon < 100.0f)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
    }
    else
    {
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    glRectf(x + 19, y + 3, x + length + 2, y + height - 5);

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);      // Black wheels
    drawWheel(x + 5.0f, y);           // Front wheel
    drawWheel(x + length - 5.0f, y);  // Back wheel
}

void drawsun(float x, float y, float length, float r) {
    glColor3f(1.0f, 1.0f, 0.0f);
    circle(5.0f, 5.0f, 85.0f, sun);
}

void drawmoon(float x, float y, float length, float r) {
    glColor3f(0.9f, 0.9f, 1.0f);
    circle(5.0f, 5.0f, 85.0f, moon);
}

void drawclouds(float x, float y, float length, float r) {
    if (moon > -10.0f && moon < 100.0f) {
        glColor3f(0.0f, 0.0f, 0.5f);
        circle(5.0f, 5.0f, length, 85);      // mid
        circle(5.0f, 4.0f, length - 5, 85);  // left
        circle(5.0f, 4.0f, length + 5, 85);  // right

    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        circle(5.0f, 5.0f, length, 85);      // mid
        circle(5.0f, 4.0f, length - 5, 85);  // left
        circle(5.0f, 4.0f, length + 5, 85);  // right
    }
}

// Function to draw the city scene
void drawCity() {
    drawsun(sun, 0.0, 0.0, 0.0);
    drawmoon(moon, 0.0, 0.0, 0.0);

    glColor3f(0.3f, 0.3f, 0.3f);         // Dark gray road
    glRectf(0.0f, 0.0f, 100.0f, 20.0f);  // Main road

    // Catwalk
    glColor3f(0.75f, 0.75f, 0.75f);       // Silver catwalk
    glRectf(0.0f, 20.0f, 100.0f, 25.0f);  // catwalk

    glColor3f(0.0f, 0.5f, 0.0f);  // Green base of catwalk
    glRectf(0.0f, 23.0f, 100.0f, 25.0f);
    // Draw cars
    glColor3f(1.0f, 1.0f, 1.0f);  // divider?
    for (float i = 0.0f; i < 100.0f; i += 10.0f) {
        glRectf(i, 9.0f, i + 5.0f, 11.0f);
    }

    // Buildings
    glColor3f(0.0f, 0.0f, 0.0f);  // Black buildings
    glRectf(0.0f, 25.0f, 16.0f, 70.0f);
    glColor3ub(169, 169, 169);  // Sets color to Dark Grey (#A9A9A9)
    glRectf(0.0f, 25.0f, 0.5f, 70.0f);
    glRectf(16.0f, 25.0f, 16.5f, 80.0f);

    glColor3f(0.6f, 0.0f, 0.0f);  // More buildings
    glRectf(16.0f, 25.0f, 31.0f, 90.0f);
    glColor3f(1.0f, 0.84f, 0.0f);
    glRectf(31.0f, 25.0f, 51.0f, 80.0f);
    glColor3f(0.5f, 0.0f, 0.5f);
    glRectf(31.0f, 80.0f, 51.0f, 82.0f);
    glColor3f(0.8f, 0.5f, 0.2f);
    glRectf(65.0f, 25.0f, 85.0f, 60.0f);
    glColor3f(0.2f, 0.2f, 0.2f);  // Dark gray tower
    glRectf(56.0f, 80.0f, 59.0f, 95.0f);
    glColor3f(0.75f, 0.75f, 0.75f);
    glRectf(55.0f, 25.0f, 60.0f, 80.0f);
    glColor3f(0.8f, 0.0f, 0.0f);  // Red tip of the tower
    glRectf(57.0f, 95.0f, 58.0f, 100.0f);

    glColor3ub(169, 169,
               169);  // Sets color to Dark Grey//concrete stonk (#A9A9A9)
    glRectf(0.0f, 70.0f, 16.0f, 72.0f);
    glColor3ub(169, 169,
               169);  // Sets color to Dark Grey//concrete stonk (#A9A9A9)
    glRectf(16.0f, 25.0f, 16.5f, 90.0f);
    glRectf(16.0f, 90.0f, 31.0f, 91.0f);
    glRectf(31.0f, 80.0f, 51.0f, 82.0f);
    glRectf(31.0f, 25.0f, 31.5f, 82.0f);
    glRectf(65.0f, 25.0f, 65.5f, 60.0f);
    glRectf(85.0f, 25.0f, 85.5f, 60.0f);
    glRectf(65.0f, 60.0f, 85.5f, 62.0f);

    // Windows
    if (moon > -10.0f && moon < 100.0f) {

        //red tip
        glColor3f(1.0f, 0.27f, 0.0f);
        glRectf(57.0f, 95.0f, 58.0f, 100.0f);


        // Windows on Black
        glColor3f(1.0f, 1.0f, 0.0f);  // Yellow windows
        for (float x = 1.0f; x < 14.0f; x += 3.0f) {
            for (float y = 30.0f; y < 65.0f; y += 10.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

        // Windows on Red Building
        for (float x = 17.0f; x < 30.0f; x += 5.0f) {
            for (float y = 26.0f; y < 89.0f; y += 8.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

        // Windows on Gold Building
        for (float x = 32.0f; x < 49.0f; x += 5.0f) {
            for (float y = 26.0f; y < 79.0f; y += 8.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

        // Windows on Brown Building
        for (float x = 66.0f; x < 84.0f; x += 5.0f) {
            for (float y = 26.0f; y < 55.0f; y += 8.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

    } else {
        glColor3f(0.0f, 0.5f, 0.5f);  // Yellow windows
        for (float x = 1.0f; x < 14.0f; x += 3.0f) {
            for (float y = 30.0f; y < 65.0f; y += 10.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

        // Windows on Red Building
        for (float x = 17.0f; x < 30.0f; x += 5.0f) {
            for (float y = 26.0f; y < 89.0f; y += 8.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

        // Windows on Gold Building
        for (float x = 32.0f; x < 49.0f; x += 5.0f) {
            for (float y = 26.0f; y < 79.0f; y += 8.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }

        // Windows on Brown Building
        for (float x = 66.0f; x < 84.0f; x += 5.0f) {
            for (float y = 26.0f; y < 55.0f; y += 8.0f) {
                glRectf(x, y, x + 2.0f, y + 5.0f);
            }
        }
    }

    drawclouds(0.0, 0.0, cloud1, 0.0);
    drawclouds(0.0, 0.0, cloud2, 0.0);

    drawplane(plane, 0.0f);

    drawCar(car1_x, 5.0f, 20.0f, 10.0f, 1.0f, 0.0f, 0.0f);  // Red car
    drawCar(car2_x, 5.0f, 20.0f, 10.0f, 0.0f, 0.0f, 1.0f);  // Blue car
    drawCar(car3_x, 5.0f, 20.0f, 10.0f, 0.0f, 1.0f, 0.0f);

    drawtreeC(tree1, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree2, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree3, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree4, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree5, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree6, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree7, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree8, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree9, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree10, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree11, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree12, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree13, 0.0f, 0.0f, 0.0f);
    drawtreeC(tree14, 0.0f, 0.0f, 0.0f);
}

///////////////////////////////////// train scene stars here
///////////////////////////////////

void Sprint(float x, float y, char* st) {
    int l, i;

    l = strlen(st);  // see how many characters are in text string.
    glColor3f(1.0, 0.0, 0.0);
    // glDisable(GL_LIGHTING);
    glRasterPos2f(x, y);     // location to start printing text
    for (i = 0; i < l; i++)  // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, st[i]);
    }
}


float birdX = 150.0f;
float birdY = 150.0f;
float wingSize = 10.0f;
float birdmove = 0.0f;

void drawBird(float x, float y, float wingLength) {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(4);
    glBegin(GL_LINES);


    // Left wing
     glVertex2f(x, y);                // Center point
    glVertex2f(x - wingLength, y + wingLength); // End of the left wing

    // Right wing
    glVertex2f(x, y);                // Center point
    glVertex2f(x + wingLength, y + wingLength); // End of the right wing

    glEnd();
}

void railScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // hills
    glColor3ub(34, 177, 76);
    circle(150, 170, 150, 500);
    glColor3ub(34, 177, 76);
    circle(180, 190, 600, 500);
    glColor3ub(34, 200, 76);
    circle(200, 170, 350, 500);
    glColor3ub(34, 200, 76);
    circle(220, 200, 850, 500);

    glBegin(GL_QUADS);
    glColor3ub(0.0, 128, 0.0);
    glVertex2i(0, 550);
    glVertex2i(1000, 550);
    glVertex2i(1000, 0);
    glVertex2i(0, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(0, 50, 0);

    glColor3ub(173, 151, 9);  // BODY
    glBegin(GL_QUADS);
    glVertex2i(575, 350);
    glVertex2i(575, 425);
    glVertex2i(825, 425);
    glVertex2i(825, 350);
    glEnd();

    glColor3ub(77, 77, 219);  // ROOF
    glBegin(GL_QUADS);
    glVertex2i(550, 425);
    glVertex2i(600, 460);
    glVertex2i(800, 460);
    glVertex2i(850, 425);
    glEnd();

    glColor3ub(139, 137, 143);  // STAIR
    glBegin(GL_QUADS);
    glVertex2i(565, 340);
    glVertex2i(565, 350);
    glVertex2i(835, 350);
    glVertex2i(835, 340);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);  // DOOR
    glBegin(GL_QUADS);
    glVertex2i(690, 350);
    glVertex2i(690, 400);
    glVertex2i(710, 400);
    glVertex2i(710, 350);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);  // Left Windows
    glBegin(GL_QUADS);
    glVertex2i(595, 375);
    glVertex2i(595, 400);
    glVertex2i(615, 400);
    glVertex2i(615, 375);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(635, 375);
    glVertex2i(635, 400);
    glVertex2i(655, 400);
    glVertex2i(655, 375);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);  // Right Windows
    glBegin(GL_QUADS);
    glVertex2i(805, 375);
    glVertex2i(805, 400);
    glVertex2i(785, 400);
    glVertex2i(785, 375);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(765, 400);
    glVertex2i(745, 400);
    glVertex2i(745, 375);
    glVertex2i(765, 375);
    glEnd();

    glPopMatrix();

    /////circle tree 1

    glPushMatrix();
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    /////circle tree 2

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(250, 50, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    glPopMatrix();

    /// circle tree 3

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(350, 50, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    // glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    glPopMatrix();

    /// near tree circle tree 4

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(250, 35, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // glColor3f(0.4, 0, 0.5);
    //   glBegin(GL_QUADS);
    // glVertex2i(198, 380);
    // glVertex2i(198, 425);
    // glVertex2i(203, 425);
    // glVertex2i(203, 380);
    // glEnd();

    glPopMatrix();

    /// circle tree 4

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(350, 47, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    glPopMatrix();

    /// circle tree 5

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(756, 80, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.8, 0.5);

    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 395);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 395);
    glEnd();

    glPopMatrix();

    /// circle tree 7

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(650, 40, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    glPopMatrix();

    /// circle tree 6 near tree

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(50, 34, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    glPopMatrix();

    /////////////new tree

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(50, 34, 0);

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 450, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(210, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    glTranslatef(190, 438, 0);

    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0, 0.8, 0.5);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 15;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(198, 380);
    glVertex2i(198, 425);
    glVertex2i(203, 425);
    glVertex2i(203, 380);
    glEnd();

    glPopMatrix();

    // road

    glColor3ub(66, 66, 49);
    glBegin(GL_QUADS);
    glVertex2i(0, 330);
    glVertex2i(1000, 330);
    glVertex2i(1000, 280);
    glVertex2i(0, 280);
    glEnd();

    glColor3ub(66, 66, 49);
    glBegin(GL_QUADS);
    glVertex2i(690, 390);
    glVertex2i(710, 390);
    glVertex2i(710, 320);
    glVertex2i(690, 320);
    glEnd();

    // rail line
    glColor3ub(150, 150, 144);
    glBegin(GL_QUADS);
    glVertex2i(0, 180);
    glVertex2i(0, 205);
    glVertex2i(1000, 205);
    glVertex2i(1000, 180);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, 202);
    glVertex2i(1000, 202);
    glVertex2i(1000, 205);
    glVertex2i(0, 205);

    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, 180);
    glVertex2i(1000, 180);
    glVertex2i(1000, 184);
    glVertex2i(0, 184);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    float j;
    for (j = 0; j <= 1000; j += 20)  // rail line
    {
        glVertex2i(10 + j, 180);
        glVertex2i(15 + j, 205);
    }
    glEnd();

    // TREE 1


    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(200, 440, 0);


    glColor3f(0, 0.8, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();


    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();


    // TREE 2

    glPushMatrix();
    glScalef(0.50, 0.50, 0.25);
    glTranslatef(1400, 500, 0);

    glColor3f(0, 0.8, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 3

    glPushMatrix();
    glScalef(0.50, 0.50, 0.25);
    glTranslatef(-400, 500, 0);

    glColor3f(0, 0.8, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 4

    glPushMatrix();
    glScalef(0.50, 0.50, 0.25);
    glTranslatef(250, 600, 0);

    glColor3f(0, 0.8, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 5

    glPushMatrix();

    glTranslatef(0, 400, 0);
    glScalef(0.25, 0.25, 0.25);
    glColor3f(0, 0.8, 0.2);

    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 6

    glPushMatrix();

    glTranslatef(150, 420, 0);
    glScalef(0.25, 0.25, 0.25);
    glColor3f(0, 0.8, 0.2);

    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 7

    glPushMatrix();

    glTranslatef(-50, 400, 0);
    glScalef(0.25, 0.25, 0.25);
    glColor3f(0, 0.8, 0.2);

    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 8

    glPushMatrix();

    glTranslatef(80, 420, 0);
    glScalef(0.25, 0.25, 0.25);
    glColor3f(0, 0.8, 0.2);

    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    // tree 9

    glPushMatrix();

    glTranslatef(780, 415, 0);
    glScalef(0.25, 0.25, 0.25);
    glColor3f(0, 0.8, 0.2);

    glBegin(GL_TRIANGLES);
    glVertex2i(445, 340);
    glVertex2i(492, 440);
    glVertex2i(540, 340);
    glEnd();

    glColor3f(0, 0.8, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2i(445, 360);
    glVertex2i(492, 460);
    glVertex2i(540, 360);
    glEnd();

    glColor3f(0.4, 0, 0.5);
    glBegin(GL_QUADS);
    glVertex2i(497, 340);
    glVertex2i(486, 340);
    glVertex2i(486, 250);
    glVertex2i(497, 250);
    glEnd();

    glPopMatrix();

    /// river

    glPushMatrix();

    glColor3ub(152, 222, 245);
    glBegin(GL_QUADS);
    glVertex2i(0, 120);
    glVertex2i(1000, 120);
    glVertex2i(1000, 0);
    glVertex2i(0, 0);
    glEnd();

    glPopMatrix();

    /// 1st CART

    glPushMatrix();
    glTranslatef(_run1, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(40, 80, 0.0);

    glPushMatrix();
    glTranslatef(30, 220, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(225, 245, 93);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    /// box of 1st CART
    glColor3ub(242, 242, 237);
    glBegin(GL_LINES);
    glVertex2i(20, 220);
    glVertex2i(40, 220);
    glVertex2i(30, 230);
    glVertex2i(30, 210);
    glVertex2i(37, 227);
    glVertex2i(23, 213);
    glVertex2i(37, 213);
    glVertex2i(23, 227);

    glVertex2i(5, 230);
    glVertex2i(100, 230);
    glVertex2i(100, 230);
    glVertex2i(100, 232);
    glVertex2i(100, 232);
    glVertex2i(5, 232);

    glVertex2i(7, 232);
    glVertex2i(7, 262);
    glVertex2i(17, 232);
    glVertex2i(17, 262);
    glVertex2i(27, 232);
    glVertex2i(27, 262);
    glVertex2i(37, 232);
    glVertex2i(37, 262);

    glVertex2i(47, 232);
    glVertex2i(47, 262);
    glVertex2i(57, 232);
    glVertex2i(57, 262);
    glVertex2i(7, 242);
    glVertex2i(59, 242);
    glVertex2i(7, 252);
    glVertex2i(59, 252);
    glVertex2i(99, 233);
    glVertex2i(97, 245);
    glVertex2i(101, 233);
    glVertex2i(103, 245);
    glEnd();

    /// COW of 1st CART
    glColor3ub(242, 242, 237);
    glBegin(GL_LINE_LOOP);
    glVertex2i(60, 210);
    glVertex2i(60, 230);
    glVertex2i(90, 230);
    glVertex2i(92, 233);
    glVertex2i(95, 230);
    glVertex2i(97, 230);
    glVertex2i(99, 233);
    glVertex2i(101, 233);

    glVertex2i(105, 226);
    glVertex2i(102, 226);
    glVertex2i(100, 228);
    glVertex2i(98, 228);
    glVertex2i(96, 220);
    glVertex2i(95, 210);
    glVertex2i(93, 210);
    glVertex2i(93, 220);

    glVertex2i(93, 216);
    glVertex2i(65, 216);
    glVertex2i(65, 220);
    glVertex2i(65, 210);
    glEnd();

    glPopMatrix();
    /// End of COW of 1st Cart

    // 2nd CART
    glPushMatrix();
    glTranslatef(200, 100, 0.0);

    glPushMatrix();
    glTranslatef(30, 220, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(225, 245, 93);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // box of 2nd CART
    glColor3ub(242, 242, 237);
    glBegin(GL_LINES);
    glVertex2i(20, 220);
    glVertex2i(40, 220);
    glVertex2i(30, 230);
    glVertex2i(30, 210);
    glVertex2i(37, 227);
    glVertex2i(23, 213);
    glVertex2i(37, 213);
    glVertex2i(23, 227);

    glVertex2i(5, 230);
    glVertex2i(100, 230);
    glVertex2i(100, 230);
    glVertex2i(100, 232);
    glVertex2i(100, 232);
    glVertex2i(5, 232);

    glVertex2i(7, 232);
    glVertex2i(7, 262);
    glVertex2i(17, 232);
    glVertex2i(17, 262);
    glVertex2i(27, 232);
    glVertex2i(27, 262);
    glVertex2i(37, 232);
    glVertex2i(37, 262);

    glVertex2i(47, 232);
    glVertex2i(47, 262);
    glVertex2i(57, 232);
    glVertex2i(57, 262);
    glVertex2i(7, 242);
    glVertex2i(59, 242);
    glVertex2i(7, 252);
    glVertex2i(59, 252);
    glVertex2i(99, 233);
    glVertex2i(97, 245);
    glVertex2i(101, 233);
    glVertex2i(103, 245);
    glEnd();

    // COW of 2nd CART
    glColor3ub(242, 242, 237);
    glBegin(GL_LINE_LOOP);
    glVertex2i(60, 210);
    glVertex2i(60, 230);
    glVertex2i(90, 230);
    glVertex2i(92, 233);
    glVertex2i(95, 230);
    glVertex2i(97, 230);
    glVertex2i(99, 233);
    glVertex2i(101, 233);

    glVertex2i(105, 226);
    glVertex2i(102, 226);
    glVertex2i(100, 228);
    glVertex2i(98, 228);
    glVertex2i(96, 220);
    glVertex2i(95, 210);
    glVertex2i(93, 210);
    glVertex2i(93, 220);

    glVertex2i(93, 216);
    glVertex2i(65, 216);
    glVertex2i(65, 220);
    glVertex2i(65, 210);
    glEnd();

    glPopMatrix();

    glPopMatrix();

    // End of COW of 2nd Cart

    // small home
    glPushMatrix();
    glTranslatef(-10, 70, 0.0);

    glColor3ub(182, 163, 240);
    glBegin(GL_POLYGON);
    glVertex2i(85, 310);
    glVertex2i(85, 350);
    glVertex2i(130, 350);
    glVertex2i(130, 310);
    glEnd();

    glColor3ub(240, 242, 242);
    glBegin(GL_POLYGON);
    glVertex2i(100, 310);
    glVertex2i(100, 338);
    glVertex2i(115, 338);
    glVertex2i(115, 310);
    glEnd();

    glColor3ub(55, 161, 163);
    glBegin(GL_TRIANGLES);
    glVertex2i(80, 350);
    glVertex2i(107, 380);
    glVertex2i(135, 350);
    glEnd();

    glColor3f(0.850, 0.490, 0.756);
    glBegin(GL_QUADS);
    glVertex2i(80, 310);
    glVertex2i(80, 300);
    glVertex2i(135, 300);
    glVertex2i(135, 310);
    glEnd();
    glPopMatrix();

    // small home2
    glPushMatrix();
    glTranslatef(60, 70, 0.0);

    glColor3ub(182, 163, 240);
    glBegin(GL_POLYGON);
    glVertex2i(85, 310);
    glVertex2i(85, 350);
    glVertex2i(130, 350);
    glVertex2i(130, 310);
    glEnd();

    glColor3ub(240, 242, 242);
    glBegin(GL_POLYGON);
    glVertex2i(100, 310);
    glVertex2i(100, 338);
    glVertex2i(115, 338);
    glVertex2i(115, 310);
    glEnd();

    glColor3ub(55, 161, 163);
    glBegin(GL_TRIANGLES);
    glVertex2i(80, 350);
    glVertex2i(107, 380);
    glVertex2i(135, 350);
    glEnd();

    glColor3f(0.850, 0.490, 0.756);
    glBegin(GL_QUADS);
    glVertex2i(80, 310);
    glVertex2i(80, 300);
    glVertex2i(135, 300);
    glVertex2i(135, 310);
    glEnd();
    glPopMatrix();

    /// Making of Rail Body

    glPushMatrix();
    glTranslatef(_ang_tri, 0.0, 0.0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 200);
    glVertex2i(170, 200);
    glVertex2i(170, 250);
    glVertex2i(100, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 225);
    glVertex2i(120, 225);
    glVertex2i(120, 240);
    glVertex2i(110, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 225);
    glVertex2i(140, 225);
    glVertex2i(140, 240);
    glVertex2i(130, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 225);
    glVertex2i(160, 225);
    glVertex2i(160, 240);
    glVertex2i(150, 240);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(100, 210);
    glVertex2i(170, 210);
    glVertex2i(170, 215);
    glVertex2i(100, 215);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 200);
    glVertex2i(176, 210);
    glVertex2i(176, 260);
    glVertex2i(170, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 250);
    glVertex2i(170, 250);
    glVertex2i(176, 260);
    glVertex2i(105, 260);
    glEnd();

    glPushMatrix();
    glTranslatef(115, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(155, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(75, 0, 0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 200);
    glVertex2i(170, 200);
    glVertex2i(170, 250);
    glVertex2i(100, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 225);
    glVertex2i(120, 225);
    glVertex2i(120, 240);
    glVertex2i(110, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 225);
    glVertex2i(140, 225);
    glVertex2i(140, 240);
    glVertex2i(130, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 225);
    glVertex2i(160, 225);
    glVertex2i(160, 240);
    glVertex2i(150, 240);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(100, 210);
    glVertex2i(170, 210);
    glVertex2i(170, 215);
    glVertex2i(100, 215);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 200);
    glVertex2i(176, 210);
    glVertex2i(176, 260);
    glVertex2i(170, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 250);
    glVertex2i(170, 250);
    glVertex2i(176, 260);
    glVertex2i(105, 260);
    glEnd();

    glPushMatrix();
    glTranslatef(115, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(155, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-75, 0, 0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 200);
    glVertex2i(170, 200);
    glVertex2i(170, 250);
    glVertex2i(100, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 225);
    glVertex2i(120, 225);
    glVertex2i(120, 240);
    glVertex2i(110, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 225);
    glVertex2i(140, 225);
    glVertex2i(140, 240);
    glVertex2i(130, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 225);
    glVertex2i(160, 225);
    glVertex2i(160, 240);
    glVertex2i(150, 240);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(100, 210);
    glVertex2i(170, 210);
    glVertex2i(170, 215);
    glVertex2i(100, 215);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 200);
    glVertex2i(176, 210);
    glVertex2i(176, 260);
    glVertex2i(170, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 250);
    glVertex2i(170, 250);
    glVertex2i(176, 260);
    glVertex2i(105, 260);
    glEnd();

    glPushMatrix();
    glTranslatef(115, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(155, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(150, 0, 0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 200);
    glVertex2i(170, 200);
    glVertex2i(170, 250);
    glVertex2i(100, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 225);
    glVertex2i(120, 225);
    glVertex2i(120, 240);
    glVertex2i(110, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 225);
    glVertex2i(140, 225);
    glVertex2i(140, 240);
    glVertex2i(130, 240);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 225);
    glVertex2i(160, 225);
    glVertex2i(160, 240);
    glVertex2i(150, 240);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(100, 210);
    glVertex2i(170, 210);
    glVertex2i(170, 215);
    glVertex2i(100, 215);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 200);
    glVertex2i(176, 210);
    glVertex2i(176, 260);
    glVertex2i(170, 250);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 250);
    glVertex2i(170, 250);
    glVertex2i(176, 260);
    glVertex2i(105, 260);
    glEnd();

    glPushMatrix();
    glTranslatef(115, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(155, 192, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 10;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(322, 245);
    glVertex2i(330, 245);
    glVertex2i(330, 232);
    glVertex2i(322, 232);
    glEnd();

    glColor3f(0.325, 0.101, 0.619);
    glBegin(GL_QUADS);
    glVertex2i(310, 253);
    glVertex2i(300, 253);
    glVertex2i(300, 258);
    glVertex2i(310, 258);
    glEnd();

    glPushMatrix();
    glTranslatef(303, 267, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.709, 0.701, 0.717);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 3;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(293, 270, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.709, 0.701, 0.717);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 4;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(283, 272, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.709, 0.701, 0.717);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 5;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    /// End of Making of Rail Body

    /// Cloud

    glPushMatrix();
    glTranslatef(_run3, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(200, 800, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 40;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(180, 750, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 50;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250, 800, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 40;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(230, 750, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 50;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // cloud 2
    glPushMatrix();
    glTranslatef(350, 100, 0);
    glPushMatrix();
    glTranslatef(200, 800, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 40;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(180, 750, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 50;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250, 800, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 50;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(230, 750, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 50;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 800, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 40;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(290, 760, 0);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = 40;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    // end of cloud

    glPushMatrix();
    glTranslatef(birdmove, birdmove, 0.0f);
    drawBird(50, 50, 50);
    drawBird(150, 150, 15);
    drawBird(0, 200, 35);
    drawBird(250, 50, 25);
    drawBird(100, 200, 25);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void railForward(int value) {
    if (frd) {
        _ang_tri += 2.5f;

        if (_ang_tri > 1000) {
            _ang_tri -= 1400;
        }

        glutPostRedisplay();
        glutTimerFunc(25, railForward, 0);
    }
}

void railBackward(int value) {
    if (bck) {
        _ang_tri -= 2.2f;

        if (_ang_tri < -350) {
            _ang_tri = 1100;
        }
        glutPostRedisplay();
        glutTimerFunc(25, railBackward, 0);
    }
}

void Night(int value) {
    if (night) {
        /* glBegin(GL_QUADS);
         glColor3f(0.10, 0.10, 0.10);
         glVertex2i(0,1000);
         glVertex2i(1000,1000);
         glVertex2i(1000,0);
         glVertex2i(0,0);
         glEnd();*/

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glutPostRedisplay();
        glutTimerFunc(5, Night, 0);
        glFlush();
    }
}

///////////////////////////////////// train scene ends here


///////////////////////////////////// village starts here

void drawScene2() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1, 0, 0);

    /// sky///
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(38.0f, 3.0f);
    glVertex2f(38.0f, 14.0f);
    glVertex2f(-12.0f, 14.0f);
    glVertex2f(-12.0f, 3.0f);

    glEnd();

    /// Stars///

    glPushMatrix();

    glPointSize(2.0);
    glColor3ub(255, 255, 255);

    glBegin(GL_POINTS);

    glVertex2f(1, 4);
    glVertex2f(2, 7.5);
    glVertex2f(4, 5);
    glVertex2f(-2, 8);
    glVertex2f(30, 5);
    glVertex2f(-1, 9);
    glVertex2f(35, 7);
    glVertex2f(-3, 7);
    glVertex2f(-7, 5);
    glVertex2f(10, 7.5);
    glVertex2f(12, 8.5);
    glVertex2f(-11, 6);
    glVertex2f(37, 7.5);
    glVertex2f(-10, 4.5);
    glVertex2f(13, 7);
    glVertex2f(14, 7.5);
    glVertex2f(18, 10);
    // glVertex2f(-10,4.5);

    glEnd();

    glPopMatrix();

    /// moon///
    // 1st circle for moon

    glPushMatrix();
    glColor3ub(217, 217, 217);
    glTranslatef(-8.0, 7.0, 0);
    glutSolidSphere(1, 250, 250);
    glPopMatrix();

    // 2nd circle for moon

    glPushMatrix();
    glColor3ub(0, 0, 0);
    glTranslatef(-8, 7.25, 0);
    glutSolidSphere(1, 250, 250);
    glPopMatrix();

    /// cloud 1///
    glPushMatrix();

    glTranslatef(_moveC, 0.0f, 0.0f);
    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(1.0, 6.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(1.0, 7.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(2.0, 7.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(2.0, 6.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(0.0, 6.5, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(3.0, 6.5, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPopMatrix();

    /// cloud 2///

    glPushMatrix();

    glTranslatef(_moveC, 0.0f, 0.0f);
    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(15.0, 9.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(15.0, 8.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(16.0, 8.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(16.0, 9.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(14.0, 8.5, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(17.0, 8.5, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPopMatrix();

    /// cloud 3///

    glPushMatrix();

    glTranslatef(_moveC, 0.0f, 0.0f);

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(22.0, 8.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(22.0, 7.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(23.0, 8.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(23.0, 7.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(24.0, 7.5, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(105, 105, 105);
    glTranslatef(21.0, 7.5, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPopMatrix();

    /// sea portion///
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(65, 105, 225);
    glVertex2f(38.0f, -19.0f);
    glVertex2f(38.0f, 3.0f);
    glVertex2f(-12.0f, 3.0f);
    glVertex2f(-12.0f, -19.0f);

    glEnd();

    /// left soil portion///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(6.0f, 1.0f);
    glVertex2f(3.0f, 3.0f);
    glVertex2f(-12.0f, 3.0f);
    glVertex2f(-12.0f, 0.0f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(7.0f, -1.5f);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(-12.0f, 0.0f);
    glVertex2f(-12.0f, -3.0f);

    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(6.0f, -4.5f);
    glVertex2f(8.0f, -4.0f);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(-12.0f, -3.0f);
    glVertex2f(-12.0f, -4.5f);

    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(2.0f, -9.0f);
    glVertex2f(9.5f, -7.0f);
    glVertex2f(6.0f, -4.5f);
    glVertex2f(-12.0f, -4.5f);
    glVertex2f(-12.0f, -9.5f);

    glEnd();

    // polygon 5
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(2.0f, -11.5f);
    glVertex2f(5.0f, -10.0f);
    glVertex2f(2.0f, -9.0f);
    glVertex2f(-12.0f, -9.0f);
    glVertex2f(-12.0f, -11.5f);

    glEnd();

    /// left sidewise border partition///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(6.0f, 0.5f);
    glVertex2f(6.0f, 1.0f);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(4.5f, -0.25f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(7.0f, -2.0f);
    glVertex2f(7.0f, -1.5f);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(5.5f, -3.15f);

    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(8.0f, -4.4f);
    glVertex2f(8.0f, -4.0f);
    glVertex2f(6.0f, -4.5f);
    glVertex2f(6.3f, -4.8f);

    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(9.5f, -7.5f);
    glVertex2f(9.5f, -7.0f);
    glVertex2f(2.0f, -9.0f);
    glVertex2f(3.0f, -9.3f);

    glEnd();

    // polygon 5
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(5.0f, -10.5f);
    glVertex2f(5.0f, -10.0f);
    glVertex2f(2.0f, -11.5f);
    glVertex2f(2.0f, -12.0f);

    glEnd();

    // polygon 6
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -12.0f);
    glVertex2f(2.0f, -11.5f);
    glVertex2f(-12.0f, -11.5f);
    glVertex2f(-12.0f, -12.0f);

    glEnd();

    /// straw///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(2.5f, -3.0f);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(-3.0f, -1.0f);
    glVertex2f(-3.5f, -3.0f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(-2.0f, 0.5f);
    glVertex2f(-3.0f, -1.0f);

    glEnd();
    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-2.0f, 0.5f);

    glEnd();

    /// triangle///

    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-0.5f, 1.2f);
    glVertex2f(-1.0f, 1.0f);

    glEnd();

    // polygon

    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(-0.4f, 1.1f);
    glVertex2f(-0.4f, 1.5f);
    glVertex2f(-0.6f, 1.5f);
    glVertex2f(-0.6f, 1.1f);

    glEnd();

    /// house on left side///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-2.7f, 1.2f);
    glVertex2f(-6.7f, 1.2f);
    glVertex2f(-5.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-6.5f, 1.0f);
    glVertex2f(-6.7f, 1.2f);
    glVertex2f(-8.5f, -1.0f);
    glVertex2f(-8.0f, -1.0f);

    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(205, 133, 63);
    glVertex2f(-6.5f, 1.0f);
    glVertex2f(-8.0f, -1.0f);
    glVertex2f(-8.0f, -2.5f);
    glVertex2f(-5.0f, -3.0f);
    glVertex2f(-5.0f, -1.0f);

    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(-6.0f, -2.0f);
    glVertex2f(-6.0f, -1.0f);
    glVertex2f(-7.0f, -1.0f);
    glVertex2f(-7.0f, -2.0f);

    glEnd();

    // polygon 5
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-5.0f, -3.0f);
    glVertex2f(-8.0f, -2.5f);
    glVertex2f(-8.3f, -2.9f);
    glVertex2f(-5.0f, -3.5f);

    glEnd();

    // polygon 6
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(-1.5f, -3.0f);
    glVertex2f(-1.5f, -1.0f);
    glVertex2f(-5.0f, -1.0f);
    glVertex2f(-5.0f, -3.0f);

    glEnd();

    // polygon 7
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-5.0f, -3.0f);
    glVertex2f(-5.0f, -3.5f);
    glVertex2f(-1.0f, -3.5f);
    glVertex2f(-1.5f, -3.0f);

    glEnd();

    /// door:left
    // polygon a
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(-2.5f, -3.0f);
    glVertex2f(-2.5f, -1.2f);
    glVertex2f(-4.0f, -1.2f);
    glVertex2f(-4.0f, -3.0f);

    glEnd();

    // polygon b
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(-3.3f, -3.0f);
    glVertex2f(-3.3f, -1.4f);
    glVertex2f(-4.0f, -1.2f);
    glVertex2f(-4.0f, -3.0f);

    glEnd();

    // polygon c
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(-2.5f, -3.0f);
    glVertex2f(-2.5f, -1.2f);
    glVertex2f(-3.2f, -1.4f);
    glVertex2f(-3.2f, -3.0f);

    glEnd();

    /// tree left side
    // polygon 1
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-9.5, 1);
    glVertex2f(-9, 1.5);
    glVertex2f(-9.5, 2.5);
    glVertex2f(-10, 2);
    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-9, 1.5);
    glVertex2f(-8.5, 1);
    glVertex2f(-8, 2);
    glVertex2f(-8, 2.5);
    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-9.5, 1);
    glVertex2f(-9.5, -3.5);
    glVertex2f(-9, -4);
    glVertex2f(-8.5, -3.5);
    glVertex2f(-8.5, 1);
    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-8.5, -3);
    glVertex2f(-9.5, -3);
    glVertex2f(-10.5, -3.5);
    glVertex2f(-7.5, -3.5);
    glEnd();

    // triangle 1
    glBegin(GL_TRIANGLES);
    glColor3ub(139, 69, 19);
    glVertex2f(-10, -0.5);
    glVertex2f(-9.5, -1);
    glVertex2f(-9.5, -0.6);
    glEnd();

    // triangle 2
    glBegin(GL_TRIANGLES);
    glColor3ub(139, 69, 19);
    glVertex2f(-9.5, 1);
    glVertex2f(-9, 1.5);
    glVertex2f(-8.5, 1);
    glEnd();

    /// right soil portion///
    // polygon1//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(13.0f, 3.0f);
    glVertex2f(16.0f, 1.0f);
    glVertex2f(38.0f, 1.0f);
    glVertex2f(38.0f, 3.0f);

    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(16, 1);
    glVertex2f(14, 0);
    glVertex2f(17, -1.5);
    glVertex2f(38, -1.5);
    glVertex2f(38, 1);

    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(17, -1.5);
    glVertex2f(15, -3);
    glVertex2f(18, -4);
    glVertex2f(38, -4);
    glVertex2f(38, -1.5);

    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(18, -4);
    glVertex2f(16, -4.5);
    glVertex2f(21, -7);
    glVertex2f(38, -7);
    glVertex2f(38, -4);

    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(21, -7);
    glVertex2f(19, -8);
    glVertex2f(22, -9);
    glVertex2f(38, -9);
    glVertex2f(38, -7);

    glEnd();

    /// right sidewise border partition///

    // polygon1//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(12.5, 3);
    glVertex2f(15.6, 0.8);
    glVertex2f(16, 1);
    glVertex2f(13, 3);

    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(14, -0.5);
    glVertex2f(16.4, -1.9);
    glVertex2f(17, -1.5);
    glVertex2f(14, 0);

    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(15, -3.5);
    glVertex2f(17, -4.2);
    glVertex2f(18, -4);
    glVertex2f(15, -3);

    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(16, -5);
    glVertex2f(20.5, -7.2);
    glVertex2f(21, -7);
    glVertex2f(16, -4.5);

    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(19, -8.5);
    glVertex2f(22, -9.5);
    glVertex2f(22, -9);
    glVertex2f(19, -8);

    glEnd();

    // polygon6//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(38, -9);
    glVertex2f(22, -9);
    glVertex2f(22, -9.5);
    glVertex2f(38, -9.5);

    glEnd();

    /// house on right side///

    // polygon1//
    glBegin(GL_POLYGON);

    // glColor3ub(25,25,112);
    glColor3ub(47, 79, 79);
    glVertex2f(25.3, 1.2);
    glVertex2f(21.3, 1.2);
    glVertex2f(23, -1);
    glVertex2f(27, -1);

    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(47, 79, 79);
    // glColor3ub(139,69,19);
    glVertex2f(21.5, 1);
    glVertex2f(21.3, 1.2);
    glVertex2f(19.5, -1);
    glVertex2f(20, -1);

    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);

    glColor3ub(184, 134, 11);
    glVertex2f(21.5, 1);
    glVertex2f(20, -1);
    glVertex2f(20, -2.5);
    glVertex2f(23, -3);
    glVertex2f(23, -1);

    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);

    glColor3ub(160, 82, 45);
    glVertex2f(22, -2);
    glVertex2f(22, -1);
    glVertex2f(21, -1);
    glVertex2f(21, -2);

    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);
    glColor3ub(47, 79, 79);
    // glColor3ub(139,69,19);
    glVertex2f(23, -3);
    glVertex2f(20, -2.5);
    glVertex2f(19.7, -2.9);
    glVertex2f(23, -3.5);

    glEnd();

    // polygon6//
    glBegin(GL_POLYGON);

    glColor3ub(205, 133, 63);
    glVertex2f(26.5, -3);
    glVertex2f(26.5, -1);
    glVertex2f(23, -1);
    glVertex2f(23, -3);

    glEnd();

    // polygon7//
    glBegin(GL_POLYGON);
    glColor3ub(47, 79, 79);
    // glColor3ub(139,69,19);
    glVertex2f(23, -3);
    glVertex2f(23, -3.5);
    glVertex2f(27, -3.5);
    glVertex2f(26.5, -3);

    glEnd();

    /// door:right///
    // polygon a//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(25.5, -3);
    glVertex2f(25.5, -1.2);
    glVertex2f(24, -1.2);
    glVertex2f(24, -3);

    glEnd();

    // polygon b//
    glBegin(GL_POLYGON);

    glColor3ub(160, 82, 45);
    glVertex2f(24.7, -3);
    glVertex2f(24.7, -1.4);
    glVertex2f(24, -1.2);
    glVertex2f(24, -3);

    glEnd();

    // polygon c//
    glBegin(GL_POLYGON);

    glColor3ub(160, 82, 45);
    glVertex2f(25.5, -3);
    glVertex2f(25.5, -1.2);
    glVertex2f(24.8, -1.4);
    glVertex2f(24.8, -3);

    glEnd();

    /// hillview///
    /// hill-1///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-12, 3);
    glVertex2f(-11.5, 4.5);
    glVertex2f(-7.5, 4.5);
    glVertex2f(-7, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-11.5, 4.5);
    glVertex2f(-11, 5.5);
    glVertex2f(-8, 5.5);
    glVertex2f(-7.5, 4.5);
    // glVertex2f();
    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-11, 5.5);
    glVertex2f(-10.5, 6);
    glVertex2f(-8.5, 6);
    glVertex2f(-8, 5.5);
    // glVertex2f();
    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-10.5, 6);
    glVertex2f(-10.3, 6.2);
    glVertex2f(-8.7, 6.2);
    glVertex2f(-8.5, 6);
    // glVertex2f();
    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-10.3, 6.2);
    glVertex2f(-10.2, 6.3);
    glVertex2f(-8.8, 6.3);
    glVertex2f(-8.7, 6);
    // glVertex2f();
    glEnd();

    /// Hill 2///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-7, 3);
    glVertex2f(-6.5, 4);
    glVertex2f(-4.5, 4);
    glVertex2f(-4, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-6.5, 4);
    glVertex2f(-6, 4.5);
    glVertex2f(-5, 4.5);
    glVertex2f(-4.5, 4);
    // glVertex2f();
    glEnd();

    /// Hill 3///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-4, 3);
    glVertex2f(-3.5, 4.5);
    glVertex2f(-1.5, 4.5);
    glVertex2f(-1, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-3.5, 4.5);
    glVertex2f(-3, 5);
    glVertex2f(-2, 5);
    glVertex2f(-1.5, 4.5);
    // glVertex2f();
    glEnd();

    /// Hill 4///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-1, 3);
    glVertex2f(-0.5, 6);
    glVertex2f(4.5, 6);
    glVertex2f(5, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-0.5, 6);
    glVertex2f(0, 7);
    glVertex2f(4, 7);
    glVertex2f(4.5, 6);
    // glVertex2f();
    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(0, 7);
    glVertex2f(1, 8);
    glVertex2f(3, 8);
    glVertex2f(4, 7);
    // glVertex2f();
    glEnd();
    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(1, 8);
    glVertex2f(3, 8);
    glVertex2f(2, 8.3);
    glEnd();

    /// hill 5///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(5, 3);
    glVertex2f(5.5, 4);
    glVertex2f(6.5, 4);
    glVertex2f(7, 3);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(5.5, 4);
    glVertex2f(6.5, 4);
    glVertex2f(6, 4.5);
    glEnd();

    /// hill 6///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(7, 3);
    glVertex2f(8, 5);
    glVertex2f(13, 5);
    glVertex2f(14, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(8, 5);
    glVertex2f(9, 6);
    glVertex2f(12, 6);
    glVertex2f(13, 5);
    // glVertex2f();
    glEnd();
    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(9, 6);
    glVertex2f(12, 6);
    glVertex2f(10.5, 6.5);
    glEnd();

    /// hill 7///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(14, 3);
    glVertex2f(15, 5);
    glVertex2f(20, 5);
    glVertex2f(21, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(15, 5);
    glVertex2f(16, 6);
    glVertex2f(19, 6);
    glVertex2f(20, 5);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(16, 6);
    glVertex2f(19, 6);
    glVertex2f(17.5, 6.5);
    glEnd();

    /// hill 8///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(21, 3);
    glVertex2f(22, 5);
    glVertex2f(24, 5);
    glVertex2f(25, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(22, 5);
    glVertex2f(22.5, 5.5);
    glVertex2f(23.5, 5.5);
    glVertex2f(24, 5);
    // glVertex2f();
    glEnd();

    /// hill 9///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(25, 3);
    glVertex2f(25.5, 4.5);
    glVertex2f(28.5, 4.5);
    glVertex2f(29, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(25.5, 4.5);
    glVertex2f(26, 5);
    glVertex2f(28, 5);
    glVertex2f(28.5, 4.5);
    // glVertex2f();
    glEnd();

    /// hill 10///
    // polygon4//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(29, 3);
    glVertex2f(29.5, 4);
    glVertex2f(30.5, 4);
    glVertex2f(31, 3);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(29.5, 4);
    glVertex2f(30, 4.5);
    glVertex2f(30.5, 4);
    glEnd();

    /// hill 11///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(31, 3);
    glVertex2f(31.5, 4.5);
    glVertex2f(32.5, 4.5);
    glVertex2f(33, 3);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(31.5, 4.5);
    glVertex2f(32.5, 4.5);
    glVertex2f(32, 5);
    glEnd();

    /// hill 12///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(33, 3);
    glVertex2f(33.5, 4.5);
    glVertex2f(37.5, 4.5);
    glVertex2f(38, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(33.5, 4.5);
    glVertex2f(34, 5);
    glVertex2f(37, 5);
    glVertex2f(37.5, 4.5);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(34, 5);
    glVertex2f(37, 5);
    glVertex2f(35.5, 5.5);
    glEnd();

    /// tree upper side///

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-10.5, 2.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-9.5, 3.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-7.5, 1.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-7.5, 2.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-8.5, 3.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-10.0, 4.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-8.0, 4.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-9.0, 5.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    /// boat-1 motion left to right
    glPushMatrix();
    // glColor3d(1,0,0);
    glTranslatef(_moveA, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(1.0f, -14.0f);
    glVertex2f(1.50f, -13.0f);
    glVertex2f(-2.0f, -13.0f);
    glVertex2f(-3.0f, -14.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -14.5f);
    glVertex2f(2.0f, -14.0f);
    glVertex2f(-3.0f, -14.0f);
    glVertex2f(-3.0f, -14.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.0f, -14.5f);
    glVertex2f(-3.0f, -14.0f);
    glVertex2f(-4.5f, -13.7f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -14.5f);
    glVertex2f(3.5f, -13.7f);
    glVertex2f(2.0f, -14.0f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -14.0f);
    glVertex2f(1.5f, -13.0f);
    glVertex2f(1.0f, -14.0f);

    glEnd();

    glPopMatrix();

    ///////////////
    /// boat-2 motion right to left
    glPushMatrix();
    // glColor3d(1,0,0);
    glTranslatef(_moveB, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(21.0f, -16.5f);
    glVertex2f(17.50f, -16.5f);
    glVertex2f(18.0f, -17.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(22.0f, -18.0f);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(17.0f, -18.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255, 99, 71);
    glVertex2f(20.5f, -16.5f);
    glVertex2f(21.0f, -14.5f);
    glVertex2f(18.5f, -14.5f);
    glVertex2f(18.0f, -16.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(19.8f, -14.5f);
    glVertex2f(19.8f, -14.0f);
    glVertex2f(19.7f, -14.0f);
    glVertex2f(19.7f, -14.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(17.0f, -18.0f);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(15.5f, -17.2f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(22.0f, -18.0f);
    glVertex2f(23.5f, -17.2f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(18.0f, -17.5f);
    glVertex2f(17.5f, -16.5f);

    glEnd();

    glPopMatrix();

    /// boat-3 without motion
    // polygon-1//
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(8, -2.5);
    glVertex2f(10.5, -2.5);
    glVertex2f(10.5, -2.2);
    glVertex2f(8, -2.2);
    glEnd();

    // triangle-1//
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2f(8, -2.2);
    glVertex2f(7, -2);
    glVertex2f(8, -2.5);
    glEnd();

    // triangle-2//
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2f(11.5, -2);
    glVertex2f(10.5, -2.2);
    glVertex2f(10.5, -2.5);
    glEnd();

    /// windmill structure///
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(192, 192, 192);
    // glColor3ub(0,206,209);

    glVertex2f(31.0f, 2.0f);
    glVertex2f(30.0f, -6.0f);
    glVertex2f(34.0f, -6.0f);
    glVertex2f(33.0f, 2.0f);
    glVertex2f(32.5f, 3.0f);
    glVertex2f(31.5f, 3.0f);

    glEnd();

    // circle//
    glPushMatrix();
    glColor3ub(0, 0, 0);
    glTranslatef(32.0f, 3.0f, 0.0f);
    glutSolidSphere(0.5, 150, 150);
    glRotatef(_angle1, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);  // first stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(5.0f, 0.0f);
    glVertex2f(5.0f, 0.25f);
    glVertex2f(0.0f, 0.25f);
    glEnd();

    glBegin(GL_QUADS);  // second stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 5.0f);
    glVertex2f(-0.25f, 5.0f);
    glVertex2f(-0.25f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);  // third stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.0f, -0.25f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-5.0f, 0.0f);
    glVertex2f(-5.0f, -0.25f);
    glEnd();

    glBegin(GL_QUADS);  // fourth stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -5.0f);
    glVertex2f(0.25f, -5.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // first triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(5.0f, -2.5f);
    glVertex2f(5.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // second triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(0.0f, 0.025f);
    glVertex2f(2.5f, 5.0f);
    glVertex2f(0.0f, 5.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // third triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-5.0f, 2.5f);
    glVertex2f(-5.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // fourth triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(0.0f, -0.025f);
    glVertex2f(-2.5f, -5.0f);
    glVertex2f(0.0f, -5.0f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void drawScene() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1, 0, 0);
    glLoadIdentity();              // Reset the drawing perspective
    gluOrtho2D(-12, 38, -19, 14);  // range
    glMatrixMode(GL_MODELVIEW);

    /// sky///
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(135, 206, 250);
    glVertex2f(38.0f, 3.0f);
    glVertex2f(38.0f, 14.0f);
    glVertex2f(-12.0f, 14.0f);
    glVertex2f(-12.0f, 3.0f);

    glEnd();

    /// sun///
    glPushMatrix();
    glColor3d(255, 255, 0);
    glTranslatef(30.0, 7.0, 0);
    glutSolidSphere(1.0, 250, 250);
    glPopMatrix();

    /// cloud 1///
    glPushMatrix();

    glTranslatef(_moveC, 0.0f, 0.0f);
    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(1.0, 6.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(1.0, 7.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(2.0, 7.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(2.0, 6.0, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(0.0, 6.5, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(3.0, 6.5, 0);
    glutSolidSphere(0.7, 250, 250);
    glPopMatrix();

    glPopMatrix();

    /// cloud 2///

    glPushMatrix();

    glTranslatef(_moveC, 0.0f, 0.0f);
    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(15.0, 9.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(15.0, 8.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(16.0, 8.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(16.0, 9.0, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(14.0, 8.5, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(17.0, 8.5, 0);
    glutSolidSphere(0.8, 250, 250);
    glPopMatrix();

    glPopMatrix();

    /// cloud 3///

    glPushMatrix();

    glTranslatef(_moveC, 0.0f, 0.0f);

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(22.0, 8.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(22.0, 7.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(23.0, 8.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(23.0, 7.0, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(24.0, 7.5, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPushMatrix();
    glColor3d(255, 255, 255);
    glTranslatef(21.0, 7.5, 0);
    glutSolidSphere(0.75, 250, 250);
    glPopMatrix();

    glPopMatrix();

    /// sea portion///
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(65, 105, 225);
    glVertex2f(38.0f, -19.0f);
    glVertex2f(38.0f, 3.0f);
    glVertex2f(-12.0f, 3.0f);
    glVertex2f(-12.0f, -19.0f);

    glEnd();

    /// left soil portion///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(6.0f, 1.0f);
    glVertex2f(3.0f, 3.0f);
    glVertex2f(-12.0f, 3.0f);
    glVertex2f(-12.0f, 0.0f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(7.0f, -1.5f);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(-12.0f, 0.0f);
    glVertex2f(-12.0f, -3.0f);

    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(6.0f, -4.5f);
    glVertex2f(8.0f, -4.0f);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(-12.0f, -3.0f);
    glVertex2f(-12.0f, -4.5f);

    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(2.0f, -9.0f);
    glVertex2f(9.5f, -7.0f);
    glVertex2f(6.0f, -4.5f);
    glVertex2f(-12.0f, -4.5f);
    glVertex2f(-12.0f, -9.5f);

    glEnd();

    // polygon 5
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 128, 0);
    glVertex2f(2.0f, -11.5f);
    glVertex2f(5.0f, -10.0f);
    glVertex2f(2.0f, -9.0f);
    glVertex2f(-12.0f, -9.0f);
    glVertex2f(-12.0f, -11.5f);

    glEnd();

    /// left sidewise border partition///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(6.0f, 0.5f);
    glVertex2f(6.0f, 1.0f);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(4.5f, -0.25f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(7.0f, -2.0f);
    glVertex2f(7.0f, -1.5f);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(5.5f, -3.15f);

    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(8.0f, -4.4f);
    glVertex2f(8.0f, -4.0f);
    glVertex2f(6.0f, -4.5f);
    glVertex2f(6.3f, -4.8f);

    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(9.5f, -7.5f);
    glVertex2f(9.5f, -7.0f);
    glVertex2f(2.0f, -9.0f);
    glVertex2f(3.0f, -9.3f);

    glEnd();

    // polygon 5
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(5.0f, -10.5f);
    glVertex2f(5.0f, -10.0f);
    glVertex2f(2.0f, -11.5f);
    glVertex2f(2.0f, -12.0f);

    glEnd();

    // polygon 6
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -12.0f);
    glVertex2f(2.0f, -11.5f);
    glVertex2f(-12.0f, -11.5f);
    glVertex2f(-12.0f, -12.0f);

    glEnd();

    /// straw///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(2.5f, -3.0f);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(-3.0f, -1.0f);
    glVertex2f(-3.5f, -3.0f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(-2.0f, 0.5f);
    glVertex2f(-3.0f, -1.0f);

    glEnd();
    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-2.0f, 0.5f);

    glEnd();

    /// triangle///

    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-0.5f, 1.2f);
    glVertex2f(-1.0f, 1.0f);

    glEnd();

    // polygon

    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(189, 183, 107);
    glVertex2f(-0.4f, 1.1f);
    glVertex2f(-0.4f, 1.5f);
    glVertex2f(-0.6f, 1.5f);
    glVertex2f(-0.6f, 1.1f);

    glEnd();

    /// house on left side///
    // polygon 1
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-2.7f, 1.2f);
    glVertex2f(-6.7f, 1.2f);
    glVertex2f(-5.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);

    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-6.5f, 1.0f);
    glVertex2f(-6.7f, 1.2f);
    glVertex2f(-8.5f, -1.0f);
    glVertex2f(-8.0f, -1.0f);

    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(205, 133, 63);
    glVertex2f(-6.5f, 1.0f);
    glVertex2f(-8.0f, -1.0f);
    glVertex2f(-8.0f, -2.5f);
    glVertex2f(-5.0f, -3.0f);
    glVertex2f(-5.0f, -1.0f);

    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(-6.0f, -2.0f);
    glVertex2f(-6.0f, -1.0f);
    glVertex2f(-7.0f, -1.0f);
    glVertex2f(-7.0f, -2.0f);

    glEnd();

    // polygon 5
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-5.0f, -3.0f);
    glVertex2f(-8.0f, -2.5f);
    glVertex2f(-8.3f, -2.9f);
    glVertex2f(-5.0f, -3.5f);

    glEnd();

    // polygon 6
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(-1.5f, -3.0f);
    glVertex2f(-1.5f, -1.0f);
    glVertex2f(-5.0f, -1.0f);
    glVertex2f(-5.0f, -3.0f);

    glEnd();

    // polygon 7
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(-5.0f, -3.0f);
    glVertex2f(-5.0f, -3.5f);
    glVertex2f(-1.0f, -3.5f);
    glVertex2f(-1.5f, -3.0f);

    glEnd();

    /// door:left
    // polygon a
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(-2.5f, -3.0f);
    glVertex2f(-2.5f, -1.2f);
    glVertex2f(-4.0f, -1.2f);
    glVertex2f(-4.0f, -3.0f);

    glEnd();

    // polygon b
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(-3.3f, -3.0f);
    glVertex2f(-3.3f, -1.4f);
    glVertex2f(-4.0f, -1.2f);
    glVertex2f(-4.0f, -3.0f);

    glEnd();

    // polygon c
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(-2.5f, -3.0f);
    glVertex2f(-2.5f, -1.2f);
    glVertex2f(-3.2f, -1.4f);
    glVertex2f(-3.2f, -3.0f);

    glEnd();

    /// tree left side
    // polygon 1
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-9.5, 1);
    glVertex2f(-9, 1.5);
    glVertex2f(-9.5, 2.5);
    glVertex2f(-10, 2);
    glEnd();

    // polygon 2
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-9, 1.5);
    glVertex2f(-8.5, 1);
    glVertex2f(-8, 2);
    glVertex2f(-8, 2.5);
    glEnd();

    // polygon 3
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-9.5, 1);
    glVertex2f(-9.5, -3.5);
    glVertex2f(-9, -4);
    glVertex2f(-8.5, -3.5);
    glVertex2f(-8.5, 1);
    glEnd();

    // polygon 4
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(-8.5, -3);
    glVertex2f(-9.5, -3);
    glVertex2f(-10.5, -3.5);
    glVertex2f(-7.5, -3.5);
    glEnd();

    // triangle 1
    glBegin(GL_TRIANGLES);
    glColor3ub(139, 69, 19);
    glVertex2f(-10, -0.5);
    glVertex2f(-9.5, -1);
    glVertex2f(-9.5, -0.6);
    glEnd();

    // triangle 2
    glBegin(GL_TRIANGLES);
    glColor3ub(139, 69, 19);
    glVertex2f(-9.5, 1);
    glVertex2f(-9, 1.5);
    glVertex2f(-8.5, 1);
    glEnd();

    /// right soil portion///
    // polygon1//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(13.0f, 3.0f);
    glVertex2f(16.0f, 1.0f);
    glVertex2f(38.0f, 1.0f);
    glVertex2f(38.0f, 3.0f);

    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(16, 1);
    glVertex2f(14, 0);
    glVertex2f(17, -1.5);
    glVertex2f(38, -1.5);
    glVertex2f(38, 1);

    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(17, -1.5);
    glVertex2f(15, -3);
    glVertex2f(18, -4);
    glVertex2f(38, -4);
    glVertex2f(38, -1.5);

    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(18, -4);
    glVertex2f(16, -4.5);
    glVertex2f(21, -7);
    glVertex2f(38, -7);
    glVertex2f(38, -4);

    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);

    glColor3ub(0, 128, 0);
    glVertex2f(21, -7);
    glVertex2f(19, -8);
    glVertex2f(22, -9);
    glVertex2f(38, -9);
    glVertex2f(38, -7);

    glEnd();

    /// right sidewise border partition///

    // polygon1//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(12.5, 3);
    glVertex2f(15.6, 0.8);
    glVertex2f(16, 1);
    glVertex2f(13, 3);

    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(14, -0.5);
    glVertex2f(16.4, -1.9);
    glVertex2f(17, -1.5);
    glVertex2f(14, 0);

    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(15, -3.5);
    glVertex2f(17, -4.2);
    glVertex2f(18, -4);
    glVertex2f(15, -3);

    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(16, -5);
    glVertex2f(20.5, -7.2);
    glVertex2f(21, -7);
    glVertex2f(16, -4.5);

    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(19, -8.5);
    glVertex2f(22, -9.5);
    glVertex2f(22, -9);
    glVertex2f(19, -8);

    glEnd();

    // polygon6//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(38, -9);
    glVertex2f(22, -9);
    glVertex2f(22, -9.5);
    glVertex2f(38, -9.5);

    glEnd();

    /// house on right side///

    // polygon1//
    glBegin(GL_POLYGON);

    // glColor3ub(25,25,112);
    glColor3ub(47, 79, 79);
    glVertex2f(25.3, 1.2);
    glVertex2f(21.3, 1.2);
    glVertex2f(23, -1);
    glVertex2f(27, -1);

    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(47, 79, 79);
    // glColor3ub(139,69,19);
    glVertex2f(21.5, 1);
    glVertex2f(21.3, 1.2);
    glVertex2f(19.5, -1);
    glVertex2f(20, -1);

    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);

    glColor3ub(184, 134, 11);
    glVertex2f(21.5, 1);
    glVertex2f(20, -1);
    glVertex2f(20, -2.5);
    glVertex2f(23, -3);
    glVertex2f(23, -1);

    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);

    glColor3ub(160, 82, 45);
    glVertex2f(22, -2);
    glVertex2f(22, -1);
    glVertex2f(21, -1);
    glVertex2f(21, -2);

    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);
    glColor3ub(47, 79, 79);
    // glColor3ub(139,69,19);
    glVertex2f(23, -3);
    glVertex2f(20, -2.5);
    glVertex2f(19.7, -2.9);
    glVertex2f(23, -3.5);

    glEnd();

    // polygon6//
    glBegin(GL_POLYGON);

    glColor3ub(205, 133, 63);
    glVertex2f(26.5, -3);
    glVertex2f(26.5, -1);
    glVertex2f(23, -1);
    glVertex2f(23, -3);

    glEnd();

    // polygon7//
    glBegin(GL_POLYGON);
    glColor3ub(47, 79, 79);
    // glColor3ub(139,69,19);
    glVertex2f(23, -3);
    glVertex2f(23, -3.5);
    glVertex2f(27, -3.5);
    glVertex2f(26.5, -3);

    glEnd();

    /// door:right///
    // polygon a//
    glBegin(GL_POLYGON);

    glColor3ub(0, 0, 0);
    glVertex2f(25.5, -3);
    glVertex2f(25.5, -1.2);
    glVertex2f(24, -1.2);
    glVertex2f(24, -3);

    glEnd();

    // polygon b//
    glBegin(GL_POLYGON);

    glColor3ub(160, 82, 45);
    glVertex2f(24.7, -3);
    glVertex2f(24.7, -1.4);
    glVertex2f(24, -1.2);
    glVertex2f(24, -3);

    glEnd();

    // polygon c//
    glBegin(GL_POLYGON);

    glColor3ub(160, 82, 45);
    glVertex2f(25.5, -3);
    glVertex2f(25.5, -1.2);
    glVertex2f(24.8, -1.4);
    glVertex2f(24.8, -3);

    glEnd();

    /// hillview///
    /// hill-1///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-12, 3);
    glVertex2f(-11.5, 4.5);
    glVertex2f(-7.5, 4.5);
    glVertex2f(-7, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-11.5, 4.5);
    glVertex2f(-11, 5.5);
    glVertex2f(-8, 5.5);
    glVertex2f(-7.5, 4.5);
    // glVertex2f();
    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-11, 5.5);
    glVertex2f(-10.5, 6);
    glVertex2f(-8.5, 6);
    glVertex2f(-8, 5.5);
    // glVertex2f();
    glEnd();

    // polygon4//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-10.5, 6);
    glVertex2f(-10.3, 6.2);
    glVertex2f(-8.7, 6.2);
    glVertex2f(-8.5, 6);
    // glVertex2f();
    glEnd();

    // polygon5//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-10.3, 6.2);
    glVertex2f(-10.2, 6.3);
    glVertex2f(-8.8, 6.3);
    glVertex2f(-8.7, 6);
    // glVertex2f();
    glEnd();

    /// Hill 2///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-7, 3);
    glVertex2f(-6.5, 4);
    glVertex2f(-4.5, 4);
    glVertex2f(-4, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-6.5, 4);
    glVertex2f(-6, 4.5);
    glVertex2f(-5, 4.5);
    glVertex2f(-4.5, 4);
    // glVertex2f();
    glEnd();

    /// Hill 3///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-4, 3);
    glVertex2f(-3.5, 4.5);
    glVertex2f(-1.5, 4.5);
    glVertex2f(-1, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-3.5, 4.5);
    glVertex2f(-3, 5);
    glVertex2f(-2, 5);
    glVertex2f(-1.5, 4.5);
    // glVertex2f();
    glEnd();

    /// Hill 4///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-1, 3);
    glVertex2f(-0.5, 6);
    glVertex2f(4.5, 6);
    glVertex2f(5, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(-0.5, 6);
    glVertex2f(0, 7);
    glVertex2f(4, 7);
    glVertex2f(4.5, 6);
    // glVertex2f();
    glEnd();

    // polygon3//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(0, 7);
    glVertex2f(1, 8);
    glVertex2f(3, 8);
    glVertex2f(4, 7);
    // glVertex2f();
    glEnd();
    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(1, 8);
    glVertex2f(3, 8);
    glVertex2f(2, 8.3);
    glEnd();

    /// hill 5///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(5, 3);
    glVertex2f(5.5, 4);
    glVertex2f(6.5, 4);
    glVertex2f(7, 3);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(5.5, 4);
    glVertex2f(6.5, 4);
    glVertex2f(6, 4.5);
    glEnd();

    /// hill 6///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(7, 3);
    glVertex2f(8, 5);
    glVertex2f(13, 5);
    glVertex2f(14, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(8, 5);
    glVertex2f(9, 6);
    glVertex2f(12, 6);
    glVertex2f(13, 5);
    // glVertex2f();
    glEnd();
    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(9, 6);
    glVertex2f(12, 6);
    glVertex2f(10.5, 6.5);
    glEnd();

    /// hill 7///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(14, 3);
    glVertex2f(15, 5);
    glVertex2f(20, 5);
    glVertex2f(21, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(15, 5);
    glVertex2f(16, 6);
    glVertex2f(19, 6);
    glVertex2f(20, 5);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(16, 6);
    glVertex2f(19, 6);
    glVertex2f(17.5, 6.5);
    glEnd();

    /// hill 8///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(21, 3);
    glVertex2f(22, 5);
    glVertex2f(24, 5);
    glVertex2f(25, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(22, 5);
    glVertex2f(22.5, 5.5);
    glVertex2f(23.5, 5.5);
    glVertex2f(24, 5);
    // glVertex2f();
    glEnd();

    /// hill 9///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(25, 3);
    glVertex2f(25.5, 4.5);
    glVertex2f(28.5, 4.5);
    glVertex2f(29, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(25.5, 4.5);
    glVertex2f(26, 5);
    glVertex2f(28, 5);
    glVertex2f(28.5, 4.5);
    // glVertex2f();
    glEnd();

    /// hill 10///
    // polygon4//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(29, 3);
    glVertex2f(29.5, 4);
    glVertex2f(30.5, 4);
    glVertex2f(31, 3);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(29.5, 4);
    glVertex2f(30, 4.5);
    glVertex2f(30.5, 4);
    glEnd();

    /// hill 11///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(31, 3);
    glVertex2f(31.5, 4.5);
    glVertex2f(32.5, 4.5);
    glVertex2f(33, 3);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(31.5, 4.5);
    glVertex2f(32.5, 4.5);
    glVertex2f(32, 5);
    glEnd();

    /// hill 12///
    // polygon1//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(33, 3);
    glVertex2f(33.5, 4.5);
    glVertex2f(37.5, 4.5);
    glVertex2f(38, 3);
    // glVertex2f();
    glEnd();

    // polygon2//
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0);
    glVertex2f(33.5, 4.5);
    glVertex2f(34, 5);
    glVertex2f(37, 5);
    glVertex2f(37.5, 4.5);
    // glVertex2f();
    glEnd();

    // triangle//
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 100, 0);
    glVertex2f(34, 5);
    glVertex2f(37, 5);
    glVertex2f(35.5, 5.5);
    glEnd();

    /// tree upper side///

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-10.5, 2.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-9.5, 3.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-7.5, 1.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-7.5, 2.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-8.5, 3.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-10.0, 4.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-8.0, 4.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50, 205, 50);
    glTranslatef(-9.0, 5.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    /// boat-1 motion left to right
    glPushMatrix();
    // glColor3d(1,0,0);
    glTranslatef(_moveA, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(1.0f, -14.0f);
    glVertex2f(1.50f, -13.0f);
    glVertex2f(-2.0f, -13.0f);
    glVertex2f(-3.0f, -14.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -14.5f);
    glVertex2f(2.0f, -14.0f);
    glVertex2f(-3.0f, -14.0f);
    glVertex2f(-3.0f, -14.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(-3.0f, -14.5f);
    glVertex2f(-3.0f, -14.0f);
    glVertex2f(-4.5f, -13.7f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -14.5f);
    glVertex2f(3.5f, -13.7f);
    glVertex2f(2.0f, -14.0f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(2.0f, -14.0f);
    glVertex2f(1.5f, -13.0f);
    glVertex2f(1.0f, -14.0f);

    glEnd();

    glPopMatrix();

    ///////////////
    /// boat-2 motion right to left
    glPushMatrix();
    // glColor3d(1,0,0);
    glTranslatef(_moveB, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(21.0f, -16.5f);
    glVertex2f(17.50f, -16.5f);
    glVertex2f(18.0f, -17.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(22.0f, -18.0f);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(17.0f, -18.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(255, 99, 71);
    glVertex2f(20.5f, -16.5f);
    glVertex2f(21.0f, -14.5f);
    glVertex2f(18.5f, -14.5f);
    glVertex2f(18.0f, -16.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(19.8f, -14.5f);
    glVertex2f(19.8f, -14.0f);
    glVertex2f(19.7f, -14.0f);
    glVertex2f(19.7f, -14.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(17.0f, -18.0f);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(15.5f, -17.2f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(22.0f, -18.0f);
    glVertex2f(23.5f, -17.2f);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(18.0f, -17.5f);
    glVertex2f(17.5f, -16.5f);

    glEnd();

    glPopMatrix();

    /// boat-3 without motion
    // polygon-1//
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(8, -2.5);
    glVertex2f(10.5, -2.5);
    glVertex2f(10.5, -2.2);
    glVertex2f(8, -2.2);
    glEnd();

    // triangle-1//
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2f(8, -2.2);
    glVertex2f(7, -2);
    glVertex2f(8, -2.5);
    glEnd();

    // triangle-2//
    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    glVertex2f(11.5, -2);
    glVertex2f(10.5, -2.2);
    glVertex2f(10.5, -2.5);
    glEnd();

    /// windmill structure///
    glBegin(GL_POLYGON);  // Draw a Red 1x1 Square centered at origin
    glColor3ub(192, 192, 192);
    // glColor3ub(0,206,209);

    glVertex2f(31.0f, 2.0f);
    glVertex2f(30.0f, -6.0f);
    glVertex2f(34.0f, -6.0f);
    glVertex2f(33.0f, 2.0f);
    glVertex2f(32.5f, 3.0f);
    glVertex2f(31.5f, 3.0f);

    glEnd();

    // circle//
    glPushMatrix();
    glColor3ub(0, 0, 0);
    glTranslatef(32.0f, 3.0f, 0.0f);
    glutSolidSphere(0.5, 150, 150);
    glRotatef(_angle1, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);  // first stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(5.0f, 0.0f);
    glVertex2f(5.0f, 0.25f);
    glVertex2f(0.0f, 0.25f);
    glEnd();

    glBegin(GL_QUADS);  // second stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 5.0f);
    glVertex2f(-0.25f, 5.0f);
    glVertex2f(-0.25f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);  // third stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.0f, -0.25f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-5.0f, 0.0f);
    glVertex2f(-5.0f, -0.25f);
    glEnd();

    glBegin(GL_QUADS);  // fourth stand to hold the blade
    glColor3ub(255, 255, 0);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -5.0f);
    glVertex2f(0.25f, -5.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // first triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(5.0f, -2.5f);
    glVertex2f(5.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // second triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(0.0f, 0.025f);
    glVertex2f(2.5f, 5.0f);
    glVertex2f(0.0f, 5.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // third triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-5.0f, 2.5f);
    glVertex2f(-5.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);  // fourth triangular blade to hold the blade
    glColor3ub(128, 0, 0);
    glVertex2f(0.0f, -0.025f);
    glVertex2f(-2.5f, -5.0f);
    glVertex2f(0.0f, -5.0f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

//////////////////////////////////// village ends here


// play sound
void playSound(const std::string& soundFile) {
    PlaySound(soundFile.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}
// stop sound
void stopSound() { PlaySound(NULL, NULL, 0); }


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (transitionSequence == 1) {
        glLoadIdentity();
        gluOrtho2D(0.0, 100.0, 0.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
        drawCity();
    } else if (transitionSequence == 2) {
        glLoadIdentity();
        gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        railScene();
    } else if (transitionSequence == 3) {
        glLoadIdentity();
        gluOrtho2D(-12, 38, -19, 14);
        glMatrixMode(GL_MODELVIEW);
        drawScene2();
    } else if (transitionSequence == 4) {
        glLoadIdentity();
        gluOrtho2D(-12, 38, -19, 14);
        glMatrixMode(GL_MODELVIEW);
        drawScene();
    }

    glFlush();
}


// Timer function to update the transition effect
void update(int value) {

    sun -= speed;   // Move the sun
    moon -= speed;  // Move the moon

    // Reset the sun and moon positions
    if (sun < -10.0f) {
        sun = 200.0f;
    }
    if (moon < -10.0f) {
        moon = 200.0f;
    }

    // Sky color transitions from day to night
    if (sun > -10.0f) {
        // Daytime: sky is bright
        skyRed = 0.5f;
        skyGreen = 0.8f;
        skyBlue = 0.9f;
    }

    if (moon > -10.0f && moon < 100.0f) {
        // Nighttime: sky is dark
        skyRed = 0.0f;
        skyGreen = 0.0f;
        skyBlue = 0.2f;
    }

    // Update sky color
    glClearColor(skyRed, skyGreen, skyBlue, 1.0f);

    cloud1 += speed;  // Move the first car
    cloud2 += speed;  // Move the second car

    if (cloud1 > 110) cloud1 = -20;  // Reset first car
    if (cloud2 > 110) cloud2 = -20;
    car1_x += speed;  // Move the first car
    car2_x += speed;  // Move the second car
    car3_x += speed;  // Move the third car

    if (car1_x > 100) car1_x = -20;  // Reset first car
    if (car2_x > 100) car2_x = -20;  // Reset second car
    if (car3_x > 100) car3_x = -20;  // Reset third car


    plane -= 2 * speed;
    if (plane < -100) plane = 100;

    ////////////////////////////////// rail scene updates starts
    _run += 0.01f;
    if (_run > 1000) {
        _run -= 1700;
    }

    _run1 += 3.0f;
    if (_run1 > 1000) {
        _run1 -= 1300;
    }

    _run2 += 2.5f;
    if (_run2 > 1000) {
        _run2 -= 1300;
    }

    _run3 += 3.0f;
    if (_run3 > 1000) {
        _run3 -= 1700;
    }

    if (onOff) {
        _ang_tri += 2.5f;
        if (_ang_tri > 1000) {
            _ang_tri = 1300;
        }
    }

    birdmove += 4.0f;
    if (birdmove > 1000.0f) {
        birdmove = -200.0f;
    }

    ////////////////////////////////// rail scene update ends

    glutPostRedisplay();  // Redraw the scene with the updated transition
    glutTimerFunc(30, update, 0);  // Update every 30ms
}

////////////////////////////////////// village scene


void update1(int value) {
    _moveA += updateMove;
    if (_moveA > 38) {
        _moveA = -34;
    }
    // Notify GLUT that the display has changed

    //_moveA += 0.11;

    glutTimerFunc(20, update1,
                  0);  // Notify GLUT to call update again in 25 milliseconds
    glutPostRedisplay();
}

void update2(int value) {
    if (_moveB < -36) {
        _moveB = +38;
    }
    // Notify GLUT that the display has changed

    _moveB -= updateMove;

    glutTimerFunc(20, update2,
                  0);  // Notify GLUT to call update again in 25 milliseconds
    glutPostRedisplay();
}
// function for windlmill
void update3(int value) {
    _angle1 -= updateAngle;
    if (_angle1 > 360.0) {
        _angle1 -= 360;
    }
    glutPostRedisplay();  // Notify GLUT that the display has changed

    glutTimerFunc(10, update3,
                  0);  // Notify GLUT to call update again in 25 milliseconds
}
void update4(int value) {
    if (_moveC > +36) {
        _moveC = -38;
    }
    // Notify GLUT that the display has changed

    _moveC += updateMove;

    glutTimerFunc(20, update4,
                  0);  // Notify GLUT to call update again in 25 milliseconds
    glutPostRedisplay();
}

// Keyboard function to change scene with arrow keys
void handleKeypress(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT && transitionSequence == 1) {
        transitionSequence = 2;
        birdmove = 0.0f;
        stopSound();
        playSound("train.wav");
    }

    else if (key == GLUT_KEY_LEFT && transitionSequence == 2) {
        transitionSequence = 1;
        stopSound();
        playSound("city.wav");
    }

    else if (key == GLUT_KEY_RIGHT && transitionSequence == 2) {
        transitionSequence = 3;
        stopSound();
        playSound("river.wav");
    }

    else if (key == GLUT_KEY_LEFT && transitionSequence == 3) {
        transitionSequence = 2;
        birdmove = 0.0f;
        stopSound();
        playSound("train.wav");
    }

    else if (key == GLUT_KEY_RIGHT && transitionSequence == 3) {
        transitionSequence = 4;
    }

    else if (key == GLUT_KEY_LEFT && transitionSequence == 4) {
        transitionSequence = 3;
    }
}

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        speed += SPEED_CHANGE_FACTOR;  // Increase speed on left click
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        speed = std::max(
            0.0f,
            speed - SPEED_CHANGE_FACTOR);  // Decrease speed on right click
    }

    if (speed > 4.0f) {
        speed = 4.0f;  // Maximum speed
    } else if (speed < 0.0f) {
        speed = 0.0f;  // Minimum speed
    }

    glutPostRedisplay();  // Update display after speed change
}

void Keyboardpress(unsigned char key, int x, int y) {

    // keys for city scene
    switch (key) {
        case ' ':
            speed = 0.0f;  // Stop all movement
            break;
        case 's':
            speed = 0.5f;  // Restart movement at a set speed
            break;
        default:
            break;
    }

    // keys for train scene
    switch (key) {
        case 'b':
            frd = false;
            bck = true;
            railBackward(_ang_tri);
            break;

        case 'f':
            frd = true;
            bck = false;
            railForward(_ang_tri);
            break;

        case 's':
            frd = false;
            bck = false;
            break;

        /*case 'd':
            night = false;
            glClearColor(0.0, 0.5, 0.8, 1.0);
            break;*/

        case 27:  // ESC key
            exit(0);
            break;

        default:
            break;
    }

    // keys for village scene
    switch (key) {
        case ' ':
            updateMove = 0.0f;  // Stop all movement
            updateAngle = 0.0f;
            break;
        case 's':
            updateMove = 0.13f;  // Restart movement
            updateAngle = 0.2f;
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    cout << "A journey by train from city to village" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Press 'esc' key -> exit" << endl;
    cout << "Press keyboard 'Right' key -> Next Scene" << endl;
    cout << "Press keyboard 'Left' key -> Previous Scene" << endl;
    cout << "-------------------------------------------" << endl << endl;
    cout << "First Scene: City " << endl;
    cout << "-------------------------------" << endl;
    cout << "Keyboard and Mouse operations: " << endl;
    cout << "-------------------------------" << endl;
    cout << "Press 'space' key -> stop cars" << endl;
    cout << "Press 's' key -> restart cars" << endl;
    cout << "Right Click -> Decrease speed" << endl;
    cout << "Left Click -> Increase speed" << endl;
    cout << endl;
    cout << "-------------------------------" << endl;
    cout << "-------------------------------" << endl << endl;
    cout << "Second Scene: Train " << endl;
    cout << "-------------------------------" << endl;
    cout << "Keyboard operations: " << endl;
    cout << "-------------------------------" << endl;
    cout << "Press 'f' key -> move train forward" << endl;
    cout << "Press 'b' key -> move train backward" << endl;
    cout << "Press 's' key -> stop train" << endl;
    cout << endl;
    cout << "-------------------------------" << endl;
    cout << "-------------------------------" << endl << endl;
    cout << "Third Scene: Village " << endl;
    cout << "-------------------------------" << endl;
    cout << "Keyboard and Mouse operations: " << endl;
    cout << "-------------------------------" << endl;
    cout << "Press 'space' key -> stop movement" << endl;
    cout << "Press 's' key -> restart movement" << endl;
    cout << "Press keyboard 'Right' key -> day" << endl;
    cout << "Press keyboard 'Left' key -> night" << endl << endl << endl;

    cout << ".---------------------------------------------------------------." << endl;
    cout << "|                             GROUP: 08                         |" << endl;
    cout << "|                                                               |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|                     TITLE      : From Concrete to Countryside |" << endl;
    cout << "|                    Submitted To: Mahfujur Rahman              |" << endl;
    cout << "|                    Submission Date: 21/01/2025                |" << endl;
    cout << "|                                                               |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|                           Submitted By                        |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|               Name            |      ID      |  Contribution  |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|        Nafisa Sharmin Sadia   |  21-45162-2  |       20%      |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|        Ajmayeen Chisty        |  21-45331-2  |       20%      |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|        Anik Ben Alamgir       |  22-48258-2  |       20%      |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|        Siddatun Bin MD Sadi   |  22-47943-2  |       20%      |" << endl;
    cout << ".---------------------------------------------------------------." << endl;
    cout << "|        Farzana Zaman          |  22-48258-2  |       20%      |" << endl;
    cout << "`---------------------------------------------------------------`" << endl << endl;


    playSound("city.wav");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(960, 540);
    glutCreateWindow("From Concrete to Countryside");

    initGL();
    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);
    glutTimerFunc(20, update1, 0);  // Add a timer 3rd scene
    glutTimerFunc(20, update2, 0);  // Add a timer 3rd scene
    glutTimerFunc(10, update3, 0);  // Add a timer 3rd scene
    glutTimerFunc(20, update4, 0);  // Add a timer 3rd scene
    glutSpecialFunc(handleKeypress);
    glutMouseFunc(handleMouse);
    glutKeyboardFunc(Keyboardpress);  // Use glutSpecialFunc for arrow keys
    railForward(_ang_tri);            // rail moving forward initially

    glutMainLoop();
    return 0;
}
