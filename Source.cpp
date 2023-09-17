#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<iostream>
#include <stdlib.h>
#include <math.h>
#include <sstream> 
#include<string>
#include<GL/glut.h> 
#define PI 3.14
using namespace std;
typedef struct treenode {
	int data;
	int id;
	float x, y, r;
	int size;
	struct treenode* left;
	struct treenode* right;

}TREENODE;
TREENODE* root = NULL;
int w, sub1, n, w2, inst;
int id = 0, se, item, i = 0;
void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void add_node(TREENODE** l_root, TREENODE* current) {
	if (*l_root == NULL) {
		*l_root = current;
		return;
	}
	if (current->data < (*l_root)->data) {
		swap(*l_root, current);
	}
	if ((*l_root)->left == NULL) {
		(*l_root)->left = current;
	}
	else {
		add_node(&((*l_root)->right), current);
		if ((*l_root)->left->size < (*l_root)->right->size) {
			swap((*l_root)->left, (*l_root)->right);
		}

		(*l_root)->size = (*l_root)->right->size + 1;
	}
}
void accept_tree() {
	int ele;
	cout << "\n Enter the input nodes (enter 0 to start)\n";
	while (1) {
		fflush(stdin);
		cin >> ele;
		if (ele == 0) {
			break;
		}
		TREENODE* current = new TREENODE;
		current->data = ele;
		current->right = NULL;
		current->left = NULL;
		current->id = id;
		id += 1;
		n += 1;
		add_node(&root, current);
	}
}
void draw_text(const std::string& text, float x, float y) {
	glColor3f(0, 0, 0);
	glRasterPos2f(x, y);
	for (char c : text) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}
void drawCircle(float segments, float radius, float sx, float sy)
{
	const float step = 2 * PI / segments;
	const float tanFactor = tanf(step);
	const float radialFactor = cosf(step);
	float x = radius;
	float y = 0;
	glBegin(GL_LINES);
	for (int i = 0; i < segments; i++) {
		const float px = x + sx;
		const float py = y + sy;
		glVertex2f(px, py);
		const float tx = -y;
		const float ty = x;
		x += tx * tanFactor;
		y += ty * tanFactor;
		x *= radialFactor;
		y *= radialFactor;
	}
	glEnd();
	glFlush();
}
void draw_line(float x1, float y1, float x2, float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void drawNode(TREENODE* t_root, float x, float y, int level) {
	if (t_root == NULL) {
		return;
	}
	const float radius = 1.0;
	const float angle_change = 20;
	const float branch_length = 12 - level * 2.5;
	const float left_angle = 245 - level * angle_change;
	const float right_angle = 115 + level * angle_change;
	t_root->x = x;
	t_root->y = y;
	t_root->r = radius;
	drawCircle(40, radius, x, y);
	char buff[5];
	_itoa_s(t_root->data, buff, 10);
	draw_text(buff, x, y);
	if (t_root->left) {
		float angle = left_angle * 3.14 / 180;
		float x2 = x + branch_length * sin(angle);
		float y2 = y + branch_length * cos(angle);
		drawNode(t_root->left, x2, y2, level + 1);
		draw_line(x, y, x2, y2);
	}
	if (t_root->right) {
		float angle = right_angle * 3.14 / 180;
		float x2 = x + branch_length * sin(angle);
		float y2 = y + branch_length * cos(angle);
		drawNode(t_root->right, x2, y2, level + 1);
		draw_line(x, y, x2, y2);
	}
}
void display() {
	glClearColor(0.7, 0.95, 1, 0.8);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 10, -30);
	glColor3f(0, 0, 0);
	draw_text("Leftist Heap Sort", -5, 5);
	drawNode(root, 0, 3, 0);
	glutSwapBuffers();
}
void mouseInstr(int bt, int st, int x, int y) {
	if (bt == GLUT_RIGHT_BUTTON && st == GLUT_DOWN) {
		glutHideWindow();
		glutSetWindow(w);
		glutShowWindow();
	}
}
void dispInstr() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	draw_text("INSTRUCTIONS", 200, 480);
	draw_text("=> RIGHT CLICK to go to the leftist heap window.", 10, 390);
	glFlush();
}
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / (float)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
	accept_tree();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(0, 0);
	inst = glutCreateWindow("Instructions");
	init();
	glutDisplayFunc(dispInstr);
	glutMouseFunc(mouseInstr);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(0, 0);
	w = glutCreateWindow("Leftist Heap Sort");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutHideWindow();
	glutMainLoop();
	return 0;
}