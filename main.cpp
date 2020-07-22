#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

    static float Xvalue = 0.0, Yvalue = 0.0, Angle = 0.0;

    int MoveX = 0;
    int MoveY = 0;

    void myInit(void) {
     glClearColor (0.0, 0.0, 0.0, 0.0);
    }


    static float x1[360][2];
    static float x2[360][2];
    static float x3[720][2];


    void generateCircle()
    {
     int i = 0;

      for(i=0; i <= 360; i++)
      {
       x1[i][0] = sin(i*3.1416/180)*2;
       x1[i][1] = cos(i*3.1416/180)*2;
      }

     for(i=0; i <= 360; i++)
     {
      x2[i][0] = sin(i*3.1416/180)*0.8;
      x2[i][1] = cos(i*3.1416/180)*0.8;
     }

     for(i=0; i <= 720; i++)
     {
      x3[i][0] = sin(i*3.1416/180)*5;
      x3[i][1] = cos(i*3.1416/180)*5;
     }

    }




    void myDisplay(void) {

     glClear (GL_COLOR_BUFFER_BIT);
     //Sun
     glColor3f (0.8, 0.2, 0.0);
     glPushMatrix();
     gluLookAt (0.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
     glTranslatef(Xvalue, 0.0, Yvalue);
     glRotatef(Angle, 0.0, 0.0, 1.0);
     glutWireSphere (0.8, 200, 200);
     glPopMatrix();
     //Earth & Moon
     glColor3f (0.2, 0.4, 0.8);
     glPushMatrix();
     gluLookAt (0.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
     if(MoveX==360)
      MoveX = 0;
     glTranslatef(x1[MoveX][1], x1[MoveX][0], 0.0);
     glRotatef(Angle, 0.0, 0.0, 1.0);
     glutWireSphere (0.3, 80, 80);
     glColor3f (1.0, 1.0, 1.0);
     glTranslatef(x2[MoveX][0], x2[MoveX][1], 0.0);
     glutWireSphere (0.1, 50, 50);
     glPopMatrix();
     //Saturn
     glColor3f (0.6, 0.5, 0.5);
     glPushMatrix();
     gluLookAt (0.0, 10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
     if(MoveY==720)
      MoveY = 0;
     glTranslatef(x3[MoveY/2][1], x3[MoveY/2][0], 0.0);
     glRotatef(Angle, 0.0, 0.0, 1.0);
     glutWireSphere (0.5, 200, 200);
     int i = 0;
     glBegin(GL_QUAD_STRIP);
     glColor3f (0.6, 0.6, 0.6);
     for(i=0; i <= 360; i++)
     {
      glVertex3f(sin(i*3.1416/180)*0.6, cos(i*3.1416/180)*0.6, 0 );
      glVertex3f(sin(i*3.1416/180)*0.7, cos(i*3.1416/180)*0.75, 0 );
     }
     glEnd();
     glRotatef(Angle, 0.0, 0.0, 1.0);
     glPopMatrix();

     glFlush ();
    }


    void resize(int w, int h)
    {
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity ();
     glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
     glMatrixMode (GL_MODELVIEW);
     glLoadIdentity ();
    }


    void animation(int value)
    {
     Angle += 25.0;
     glutPostRedisplay();
     MoveX +=1;
     MoveY +=1;
     glutPostRedisplay();
     glutTimerFunc(100, animation, 0);

    }


    int main(int argc, char ** argv){

     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(1200, 800);
     glutInitWindowPosition(100, 150);
     glutCreateWindow("OpenGL");
     myInit();
     glutDisplayFunc(myDisplay);
     glutReshapeFunc(resize);
     generateCircle();
     glutTimerFunc(100, animation, 0);
     glutMainLoop();
    }
