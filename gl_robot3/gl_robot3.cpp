// gl_robot2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#define GLUT_DISABLE_ATEXIT_HACK
#pragma comment(lib, "legacy_stdio_definitions.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <GLAUX.H>
#include <cmath>
#define GLOBAL_SIZE 0.5
#define PI 3.1415926
bool isLeft = true;
static const GLfloat leg_x = 2.0, leg_y = 0.6, leg_z = 0.5; //�ȵ�����ϵ���ű���
static const GLfloat body_x = 1.2, body_y = 2.4, body_z = 1.8; //���������ϵ���ű���
static const GLfloat head_x = 1.0, head_z = 1.2, head_y = 1; //ͷ�İ뾶
static const GLfloat arm_x = 1.6, arm_y = 0.6, arm_z = 0.4; //�ֱ۵�����ϵ���ű���
static const GLfloat head_radis = 0.25;
static const GLfloat foot_x = 1.0, foot_y = 0.3, foot_z = 0.4; //�ŵ�����ϵ���ű���
static const GLfloat neck_x = head_x / 2, neck_y = head_y, neck_z = head_z / 4;
static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
static GLint angle = 0;
//��ʼ�ĽǶ�Ϊ��ֱ��
static int leftHigherLegAngle = -90, rightHigherLegAngle = -90;
static int LeftLowerLegAngle = 90, rightLowerLegAngle = 0;
static int leftHigherHandAngle = -90, rightHigherHandAngle = -90;
static int leftLowerHandAngle = 0, rightLowerHandAngle = 0;
static int leftFootAngle = 0, rightFootAngle = 0;
int speed = 1;
GLUquadricObj *quadratic; //����ά����ʱ�õ�
GLuint g_texture = 0, g_texture_head = 0, g_texture_ground = 0, g_texture_sky = 0;
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	//glCullFace(GL_BACK);                        //����ü�(���治�ɼ�)
	//glEnable(GL_CULL_FACE);                        //���òü�
	glEnable(GL_TEXTURE_2D);

	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);


}
//��������ĺ���

void drawCube_head(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat x1 = 0.5 * x / 2;
	GLfloat y1 = 0.5 * y / 2;
	GLfloat z1 = 0.5 * z / 2;
	glBindTexture(GL_TEXTURE_2D, g_texture_head);
	glBegin(GL_QUADS);
	//glPushMatrix();
	//��ǰ��								
	glVertex3f(-x1, y1, z1);
	glVertex3f(x1, y1, z1);

	glVertex3f(x1, -y1, z1);
	glVertex3f(-x1, -y1, z1);
	//������
	glVertex3f(-x1, y1, -z1);
	glVertex3f(x1, y1, -z1);
	glVertex3f(x1, -y1, -z1);
	glVertex3f(-x1, -y1, -z1);
	//������
	glVertex3f(-x1, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, -z1);
	glVertex3f(-x1, y1, -z1);
	//������
	glVertex3f(-x1, -y1, z1);
	glVertex3f(x1, -y1, z1);
	glVertex3f(x1, -y1, -z1);
	glVertex3f(-x1, -y1, -z1);
	//������
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-x1, y1, -z1);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-x1, -y1, -z1);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-x1, -y1, z1);
	//������
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, -z1);
	glVertex3f(x1, -y1, -z1);
	glVertex3f(x1, -y1, z1);
	glEnd();

	//glPopMatrix();
}
void drawCube(GLfloat x, GLfloat y, GLfloat z)
{

	GLfloat x1 = 0.5 * x / 2;
	GLfloat y1 = 0.5 * y / 2;
	GLfloat z1 = 0.5 * z / 2;
	glBindTexture(GL_TEXTURE_2D, g_texture);
	glBegin(GL_QUADS);
	//glPushMatrix();
	//��ǰ��								
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, z1);
	//������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, -z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, -z1);
	//������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, y1, -z1);
	//������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, -y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, -y1, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, -z1);
	//������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, z1);
	//������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, -z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, -y1, z1);
	glEnd();

	//glPopMatrix();
}
int LoadGLTexTures_head(GLuint& unTexture, const char* chFileName)
{
	AUX_RGBImageRec *TextureImage; //������ͼ���ݵ�ָ��
	TextureImage = auxDIBImageLoadA((LPCSTR)"face.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//�����������Ϣ��
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�����˲�Ϊ�����˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //�����˲�

	if (TextureImage)                //�ͷ���Դ
	{
		if (TextureImage->data)
		{
			free(TextureImage->data);
		}
		free(TextureImage);
	}
	return 1;
}

int LoadGLTexTures(GLuint& unTexture, const char* chFileName)
{
	AUX_RGBImageRec *TextureImage; //������ͼ���ݵ�ָ��
	TextureImage = auxDIBImageLoadA((LPCSTR)"body.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//�����������Ϣ��
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�����˲�Ϊ�����˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //�����˲�

	if (TextureImage)                //�ͷ���Դ
	{
		if (TextureImage->data)
		{
			free(TextureImage->data);
		}
		free(TextureImage);
	}
	return 1;
}
int LoadGLTexTures_ground(GLuint& unTexture, const char* chFileName)
{
	AUX_RGBImageRec *TextureImage; //������ͼ���ݵ�ָ��
	TextureImage = auxDIBImageLoadA((LPCSTR)"ground.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//�����������Ϣ��
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�����˲�Ϊ�����˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //�����˲�

	if (TextureImage)                //�ͷ���Դ
	{
		if (TextureImage->data)
		{
			free(TextureImage->data);
		}
		free(TextureImage);
	}
	return 1;
}
int LoadGLTexTures_sky(GLuint& unTexture, const char* chFileName)
{
	AUX_RGBImageRec *TextureImage; //������ͼ���ݵ�ָ��
	TextureImage = auxDIBImageLoadA((LPCSTR)"sky.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//�����������Ϣ��
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //�����˲�Ϊ�����˲�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //�����˲�

	if (TextureImage)                //�ͷ���Դ
	{
		if (TextureImage->data)
		{
			free(TextureImage->data);
		}
		free(TextureImage);
	}
	return 1;
}
void DrawGround()
{
	GLfloat y = -GLOBAL_SIZE * leg_x * 2 - GLOBAL_SIZE * foot_y;
	glBindTexture(GL_TEXTURE_2D, g_texture_ground);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ - 20.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ + 20.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(centerX + 20.0f, y, centerZ + 20.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(centerX + 20.0f, y, centerZ - 20.0f);
	glEnd();
}
void DrawSky()
{
	GLfloat y = 3.5;
	GLfloat y1 = -GLOBAL_SIZE * leg_x * 2 - GLOBAL_SIZE * foot_y;
	glBindTexture(GL_TEXTURE_2D, g_texture_sky);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ - 20.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ + 20.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(centerX + 20.0f, y, centerZ + 20.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(centerX + 20.0f, y, centerZ - 20.0f);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ - 20.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ + 20.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(centerX - 20.0f, y1, centerZ + 20.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(centerX - 20.0f, y1, centerZ - 20.0f);
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(centerX + 20.0f, y, centerZ - 20.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(centerX + 20.0f, y, centerZ + 20.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(centerX + 20.0f, y1, centerZ + 20.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(centerX + 20.0f, y1, centerZ - 20.0f);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(centerX - 20.0f, y, centerZ - 20.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(centerX + 20.0f, y, centerZ - 20.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(centerX + 20.0f, y1, centerZ - 20.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(centerX - 20.0f, y1, centerZ - 20.0f);
	glEnd();
}
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ɫ�������Ȼ���
	DrawGround();
	DrawSky();
	glColor3f(0.8, 0.8, 0.8);

	glPushMatrix(); //robot��λ�úͷ�������
	glTranslatef(centerX, centerY, centerZ);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.5, 0.5); //������ɫΪ��ɫ

	glPushMatrix();  //���������
	glColor3f(0.5, 0.5, 0.5);
	glRotatef((GLfloat)leftHigherLegAngle, 0, 0, 1.0);
	glTranslatef(0.5*leg_x / 2, 0.0, leg_z * 0.5);
	glPushMatrix();
	glScalef(leg_x, leg_y, leg_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(0.5 * leg_x / 2, 0.0, 0.0); //���ؽ�
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5*leg_z / 2);
	gluCylinder(quadratic, 0.5 * leg_y / 2, 0.5 * leg_y / 2, leg_z * 0.5, 32, 32);
	glPopMatrix();
	glRotatef(LeftLowerLegAngle, 0.0, 0.0, 1.0); //����С��
	glTranslatef(0.5*leg_x / 2, 0.0, 0.0);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glScalef(leg_x - 0.2, leg_y - 0.2, leg_z - 0.2);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(0.5*leg_x / 2, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-0.5*foot_x / 2 + 0.5*foot_y / 2, 0.0, 0.0);
	glRotatef(leftFootAngle, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(foot_x, foot_y, foot_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();  //�����Ҵ���
	glColor3f(0.25, 0.45, 0.25);
	glRotatef((GLfloat)rightHigherLegAngle, 0, 0, 1.0);
	glTranslatef(leg_x / 4, 0.0, -leg_z / 2);
	glPushMatrix();
	glScalef(leg_x, leg_y, leg_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(leg_x / 4, 0, 0); //���ؽ�
	glPushMatrix();
	glTranslatef(0.0, 0.0, -leg_z / 4);
	gluCylinder(quadratic, leg_y / 4, leg_y / 4, leg_z / 2, 32, 32);
	glPopMatrix();
	glRotatef(rightLowerLegAngle, 0.0, 0.0, 1.0); //����С��
	glTranslatef(leg_x / 4, 0.0, 0.0);
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glScalef(leg_x - 0.2, leg_y - 0.2, leg_z - 0.2);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(leg_x / 4, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-foot_x / 4 + leg_y / 4, 0.0, 0.0);
	glRotatef(rightFootAngle, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScalef(foot_x, foot_y, foot_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glPopMatrix();

	// ����
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glColor3f(0.65, 0.45, 0.45);
	glTranslatef(0, body_y / 4, 0.0);
	drawCube(body_x, body_y, body_z);
	glPopMatrix();

	glPushMatrix(); //����
	glColor3f(0.25, 0.75, 0.75);
	glTranslatef(0, 0.5*body_y, 0);
	glScalef(neck_x, neck_y, neck_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();

	// ͷ��
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0, 0.5*body_y + 0.5*head_y, 0);
	drawCube_head(head_x, head_y, head_z);
	glPopMatrix();

	glColor3f(0.5, 0.55, 0.55);
	glPushMatrix();	//������
	glColor3f(0.5, 0.6, 0.6);
	glTranslatef(0, 0.5*body_y, 0.0);
	glRotatef(leftHigherHandAngle, 0.0, 0.0, 1.0);
	glTranslatef(arm_x / 4, 0.0, (body_z + arm_z) / 4);
	glPushMatrix();
	glScalef(arm_x - 0.1, arm_y - 0.1, arm_z - 0.1);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(arm_x / 4, 0.0, 0.0);
	glPushMatrix();
	glColor3f(0.5, 0.55, 0.55);
	glTranslatef(0.0, 0.0, -arm_z / 4);
	gluCylinder(quadratic, arm_y / 4, arm_y / 4, arm_z*0.5, 32, 32);
	glPopMatrix();

	glRotatef(leftLowerHandAngle, 0.0, 0.0, 1.0);
	glTranslatef(arm_x / 4, 0.0, 0.0);
	glPushMatrix();
	glScalef(arm_x - 0.1, arm_y - 0.1, arm_z - 0.1);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();	//������
	glColor3f(0.5, 0.55, 0.55);
	glTranslatef(0, body_y / 2, 0.0);
	glRotatef(rightHigherHandAngle, 0.0, 0.0, 1.0);
	glTranslatef(arm_x / 4, 0.0, -(body_z + arm_z) / 4);
	glPushMatrix();
	glScalef(arm_x, arm_y, arm_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(arm_x / 4, 0.0, 0.0);
	glPushMatrix();
	glColor3f(0.5, 0.55, 0.55);
	glTranslatef(0.0, 0.0, -arm_z / 4);
	gluCylinder(quadratic, arm_y / 4, arm_y / 4, arm_z*0.5, 32, 32);
	glPopMatrix();

	glRotatef(rightLowerHandAngle, 0.0, 0.0, 1.0);
	glTranslatef(arm_x / 4, 0.0, 0.0);
	glPushMatrix();
	glScalef(arm_x - 0.1, arm_y - 0.1, arm_z - 0.1);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

static double lookatx = -3.5, lookatz = -3.5, lookaty = 0;
static int scrw, scrh;
//ʵʱˢ��
void reshape(int w, int h) {
	scrw = w;
	scrh = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
}

//��Ӧ����¼�
void passiveMotionFunc(int x, int y) {
	lookatx = -5.0 + (double)x / scrw * 10.0;
	lookatz = sqrt(25 - lookatx * lookatx) + centerZ;
	lookatx += centerX;
	double tmpy = -5.0 + (double)y / scrh * 10.0;
	if (tmpy >= -GLOBAL_SIZE * leg_x * 2)
		lookaty = tmpy;
	glLoadIdentity();
	glutPostRedisplay();
	gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
}

bool left = false;
//�涨���Ƕȴ���-75��ʱ��С�ȵĽǶȱ仯�����ȴ��ȱ仯�죬�涨�Ǵ��ȵ�4��
//��Ӧ�����¼��ģ�����'w'ʱ��ǰ�ߣ�����'s'ʱΪ���ת
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':

		for (int i = 0; i < speed; i++) {

			centerY = leg_x * sin(-leftHigherLegAngle / 180.0 * PI) - leg_x;
			// Ϊ�˼򻯼��㣬�Ҵ��Լٶ�����ÿ��1�ȣ��˻ᳯ���䷽��ǰ��0.035����λ����
			double mvx = cos(angle / 180.0 * PI) * 0.035; // ����x�᷽���ƶ��ľ���
			double mvz = sin(angle / 180.0 * PI) * 0.035; // ����z�᷽���ƶ��ľ���
			if (!left) { //�������
				leftHigherLegAngle--;
				rightHigherLegAngle++;
				if (leftHigherLegAngle >= -75) {
					LeftLowerLegAngle += 6;
					leftFootAngle = 0;
				}
				else if (leftHigherLegAngle < -105) LeftLowerLegAngle -= 6;

				if (leftHigherLegAngle == -120) {
					left = true;

				}

				leftHigherHandAngle++;
				leftLowerHandAngle++;
				rightHigherHandAngle--;
				rightLowerHandAngle--;
			}
			else {
				leftHigherLegAngle++;
				rightHigherLegAngle--;
				if (rightHigherLegAngle >= -75) {
					rightLowerLegAngle += 6;
					rightFootAngle = 0;
				}
				else if (rightHigherLegAngle < -105) rightLowerLegAngle -= 6;

				if (leftHigherLegAngle == -60) left = false;

				leftHigherHandAngle--;
				leftLowerHandAngle--;
				rightHigherHandAngle++;
				rightLowerHandAngle++;
			}
			centerX -= mvx;
			lookatx -= mvx;
			centerZ += mvz;
			lookatz += mvz;

			// �����ӽǣ�ʼ�հ���Ļ���Ķ�׼�˵�����
			glLoadIdentity();
			gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
			glutPostRedisplay();
		}
		break;
	case 's':
		angle = (angle + 180) % 360;

		glutPostRedisplay();
		break;
	case 'a': //��ת
		angle = (angle + 5) % 360;
		glutPostRedisplay();
		break;
	case 'd': //��ת
		angle = (angle - 5) % 360;
		glutPostRedisplay();
		break;
	case 'f':
		speed++;
		break;
	case 'h':
		if (speed > 0)
			speed--;
		break;
	}
}

//���ù���  
void SetupLights()
{
	GLfloat ambientLight[] = { 0.45f,  0.45f,  0.5f,  1.0f };//������  
	GLfloat diffuseLight[] = { 0.55f,  0.55f,  0.55f,  1.0f };//������  
	GLfloat specularLight[] = { 0.6f,  0.6f,  0.6f,  1.0f };//�����  
	GLfloat lightPos[] = { 50.0f, 80.0f, 60.0f, 1.0f };//��Դλ��  

	glEnable(GL_LIGHTING);          //���ù���  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);    //���û�����Դ  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);    //�����������Դ  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);   //���þ����Դ  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);        //���õƹ�λ��  
	glEnable(GL_LIGHT0);            //�򿪵�һ���ƹ�  

	glEnable(GL_COLOR_MATERIAL);    //���ò��ʵ���ɫ����  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  //ָ��������ɫ����  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //ָ�����϶Ծ����ķ�Ӧ  
	glMateriali(GL_FRONT, GL_SHININESS, 100);           //ָ������ϵ��  
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	LoadGLTexTures(g_texture, "body.bmp");
	LoadGLTexTures_head(g_texture_head, "face.bmp");
	LoadGLTexTures_ground(g_texture_ground, "ground.bmp");
	LoadGLTexTures_sky(g_texture_sky, "sky.bmp");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);  //��Ļˢ������
	glutKeyboardFunc(keyboard);//���°���
	glutPassiveMotionFunc(passiveMotionFunc);//���ת��
	SetupLights();
	glutMainLoop();
	return 0;
}
