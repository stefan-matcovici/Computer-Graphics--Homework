
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1.0);
   double ratia = 0.05;
   double t;

   // calculul valorilor maxime/minime ptr. x si y
   // aceste valori vor fi folosite ulterior la scalare
   xmax = a - b - 1;
   xmin = a + b + 1;
   ymax = ymin = 0;
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
   double pi = 4 * atan(1.0);
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}

void Display3() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.05;
	double t, y, x;

	xmax = 100;
	xmin = 0;
	ymax = ymin = 1;
	for (t = ratia; t <= 100; t += ratia) {
		y = fabs(t - roundf(t)) / t;
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 1 - 0.1);
	for (t = ratia; t <= 100; t += ratia) {
		x = t / xmax;
		y = (fabs(t - roundf(t)) / t) / ymax - 0.1;
		
		glVertex2f(x, y);
	}
	glEnd();
}

void Display4() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.05;
	double t, y, x;
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1.0);

	xmax = xmin = 2*(a+b);
	ymax = ymin = 0;
	for (t = -pi+ratia; t < pi; t += ratia) {
		x = 2 * (a*cosf(t) + b) * cosf(t);
		y = 2 * (a*cosf(t) + b) * sinf(t);

		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);

	ymax *= 1.5;
	xmax *= 1.2;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	for (t = -pi + ratia; t < pi; t += ratia) {
		x = 2 * (a*cosf(t) + b) * cosf(t) / xmax;
		y = 2 * (a*cosf(t) + b) * sinf(t) / ymax;

		glVertex2f(x, y);
	}
	glEnd();
}

void Display5() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.005;
	double t, y, x;
	double a = 0.2;
	double pi = 4 * atan(1.0);

	xmax = xmin = 0.2;
	ymax = ymin = 0;
	int no_points = 0;
	for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
		x = a / (4 * pow(cosf(t), 2.0) - 3);
		y = a * tanf(t) / (4 * pow(cosf(t), 2.0) - 3);

		no_points++;

		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	xmax *= 1.3;
	ymax *= 2;

	float* graph_x = new float[no_points];
	float* graph_y = new float[no_points];

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(0, 0, 1); // albastru
	glBegin(GL_LINE_STRIP);
	int i = 0;
	for (t = -pi / 2; t < -pi / 6; t += ratia) {
		x = a / (4 * pow(cos(t), 2) - 3);
		y = a * tan(t) / (4 * pow(cos(t), 2) - 3);
		
		graph_x[i] = x;
		graph_y[i] = y;
		i++;

		glVertex2f(x, y);
	}
	glEnd();

	printf("%d %d\n", no_points, i);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_TRIANGLES);
	for (int j = 1; j < i-1; j=j+2) {
		printf("%f %f\n", graph_y[j], graph_y[j + 1]);
		glVertex2f(graph_x[j], graph_y[j]);
		glVertex2f(graph_x[j+1], graph_y[j+1]);
		glVertex2f(-0.95, 0.95);
	}
	glEnd();

}

void Display6() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.05;
	double t, y, x;
	double a = 0.1, b = 0.2;
	double pi = 4 * atan(1.0);

	xmax = xmin = 0;
	ymax = ymin = a-b;
	for (t = -10; t < 10; t += ratia) {
		x = a * t - b * sinf(t);
		y = a - b * cosf(t);

		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	ymax *= 2.5;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -10; t < 10; t += ratia) {
		x = a * t - b * sinf(t);
		y = a - b * cosf(t);

		glVertex2f(x / xmax, y / ymax);
	}
	glEnd();
}

void Display7() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.05;
	double t, y, x;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);

	xmax = xmin = R+r;
	ymax = ymin = R;
	for (t = 0; t <= 2*pi; t += ratia) {
		x = (R + r)*cosf(r*t / R) - r * cosf(t + r * t / R);
		y = (R + r)*sinf(r*t / R) - r * sinf(t + r * t / R);

		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;

		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);

	xmax *= 1.5;
	ymax *= 1.4;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = 0; t <= 2 * pi; t += ratia) {
		x = (R + r)*cosf(r*t / R) - r * cosf(t + r * t / R);
		y = (R + r)*sinf(r*t / R) - r * sinf(t + r * t / R);

		glVertex2f(x / xmax, y / ymax);
	}
	glEnd();
}

void Display8() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.05;
	double t, y, x;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);

	xmax = xmin = R-2*r;
	ymax = ymin = 0;
	for (t = 0; t <= 2 * pi; t += ratia) {
		x = (R - r)*cosf(r*t / R) - r * cosf(t - r * t / R);
		y = (R - r)*sinf(r*t / R) - r * sinf(t - r * t / R);

		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;

		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);

	ymax *= 1.6;
	xmax *= 1.6;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = 0; t <= 2 * pi; t += ratia) {
		x = (R - r)*cosf(r*t / R) - r * cosf(t - r * t / R);
		y = (R - r)*sinf(r*t / R) - r * sinf(t - r * t / R);

		glVertex2f(x / xmax, y / ymax);
	}
	glEnd();
}

void Display9() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.01;
	double t, y1, x1, x2, y2;
	double r1, r2;
	double pi = 4 * atan(1.0);
	double a = 0.4;

	xmax = xmin = a*sqrt(2);
	ymax = ymin = 0;

	for (t =- pi/4 + ratia; t < pi /4; t += ratia) {
		r1 = a * sqrt(2 * cosf(2 * t));
		r2 = - a * sqrt(2 * cosf(2 * t));

		x1 = r1 * cosf(t);
		y1 = r1 * sinf(t);

		x2 = r2 * cosf(t);
		y2 = r2 * sinf(t);

		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;

		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);

	ymax *= 3;
	xmax *= 1.5;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		r2 = -a * sqrt(2 * cosf(2 * t));

		x2 = r2 * cosf(t);
		y2 = r2 * sinf(t);

		glVertex2f(x2 / xmax, y2 / ymax);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		r1 = a * sqrt(2 * cosf(2 * t));

		x1 = r1 * cosf(t);
		y1 = r1 * sinf(t);

		glVertex2f(x1 / xmax, y1/ ymax);
	}
	glVertex2f(x2 / xmax, y2 / ymax);
	glEnd();
}

void Display10() {
	double xmax, ymax, xmin, ymin;
	double ratia = 0.05;
	double t, y, x, r;
	double a = 0.02;
	double pi = 4 * atan(1.0);

	xmax = xmin = a * exp(1);
	ymax = ymin = 0;
	for (t = ratia; t <= 17.2; t += ratia) {
		r = a * exp(1 + t);
		
		x = r * cosf(t);
		y = r * sinf(t);
		
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;

		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);

	xmax *= 0.2;
	ymax *= 0.2;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = ratia; t <= 100; t += ratia) {
		r = a * exp(1 + t);

		x = r * cosf(t);
		y = r * sinf(t);

		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) {
   case '1':
      Display1();
      break;
   case '2':
      Display2();
      break;
   case '3':
	   Display3();
	   break;
   case '4':
	   Display4();
	   break;
   case '5':
	   Display5();
	   break;
   case '6':
	   Display6();
	   break;
   case '7':
	   Display7();
	   break;
   case '8':
	   Display8();
	   break;
   case '9':
	   Display9();
	   break;
   case 'a':
	   Display10();
	   break;
   default:
      break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);
   
   glutInitWindowSize(dim, dim);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);
   
   glutKeyboardFunc(KeyboardFunc);
   
   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);
   
   glutMainLoop();

   return 0;
}
