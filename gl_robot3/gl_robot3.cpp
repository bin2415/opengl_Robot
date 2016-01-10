// gl_robot2.cpp : 定义控制台应用程序的入口点。
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
static const GLfloat leg_x = 2.0, leg_y = 0.6, leg_z = 0.5; //腿的坐标系缩放比例
static const GLfloat body_x = 1.2, body_y = 2.4, body_z = 1.8; //身体的坐标系缩放比例
static const GLfloat head_x = 1.0, head_z = 1.2, head_y = 1; //头的半径
static const GLfloat arm_x = 1.6, arm_y = 0.6, arm_z = 0.4; //手臂的坐标系缩放比例
static const GLfloat head_radis = 0.25;
static const GLfloat foot_x = 1.0, foot_y = 0.3, foot_z = 0.4; //脚的坐标系缩放比例
static const GLfloat neck_x = head_x / 2, neck_y = head_y, neck_z = head_z / 4;
static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
static GLint angle = 0;
//初始的角度为竖直的
static int leftHigherLegAngle = -90, rightHigherLegAngle = -90;
static int LeftLowerLegAngle = 90, rightLowerLegAngle = 0;
static int leftHigherHandAngle = -90, rightHigherHandAngle = -90;
static int leftLowerHandAngle = 0, rightLowerHandAngle = 0;
static int leftFootAngle = 0, rightFootAngle = 0;
int speed = 1;
GLUquadricObj *quadratic; //画三维物体时用到
GLuint g_texture = 0, g_texture_head = 0, g_texture_ground = 0, g_texture_sky = 0;
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	//glCullFace(GL_BACK);                        //背面裁剪(背面不可见)
	//glEnable(GL_CULL_FACE);                        //启用裁剪
	glEnable(GL_TEXTURE_2D);

	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);


}
//画立方体的函数

void drawCube_head(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat x1 = 0.5 * x / 2;
	GLfloat y1 = 0.5 * y / 2;
	GLfloat z1 = 0.5 * z / 2;
	glBindTexture(GL_TEXTURE_2D, g_texture_head);
	glBegin(GL_QUADS);
	//glPushMatrix();
	//画前面								
	glVertex3f(-x1, y1, z1);
	glVertex3f(x1, y1, z1);

	glVertex3f(x1, -y1, z1);
	glVertex3f(-x1, -y1, z1);
	//画后面
	glVertex3f(-x1, y1, -z1);
	glVertex3f(x1, y1, -z1);
	glVertex3f(x1, -y1, -z1);
	glVertex3f(-x1, -y1, -z1);
	//画上面
	glVertex3f(-x1, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, -z1);
	glVertex3f(-x1, y1, -z1);
	//画底面
	glVertex3f(-x1, -y1, z1);
	glVertex3f(x1, -y1, z1);
	glVertex3f(x1, -y1, -z1);
	glVertex3f(-x1, -y1, -z1);
	//画左面
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-x1, y1, -z1);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-x1, -y1, -z1);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-x1, -y1, z1);
	//画右面
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
	//画前面								
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, z1);
	//画后面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, -z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, -z1);
	//画上面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, y1, -z1);
	//画底面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, -y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, -y1, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, -z1);
	//画左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-x1, -y1, z1);
	//画右面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y1, -z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, -y1, -z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, -y1, z1);
	glEnd();

	//glPopMatrix();
}
int LoadGLTexTures_head(GLuint& unTexture, const char* chFileName)
{
	AUX_RGBImageRec *TextureImage; //保存贴图数据的指针
	TextureImage = auxDIBImageLoadA((LPCSTR)"face.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//设置纹理的信息，
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //线性滤波

	if (TextureImage)                //释放资源
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
	AUX_RGBImageRec *TextureImage; //保存贴图数据的指针
	TextureImage = auxDIBImageLoadA((LPCSTR)"body.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//设置纹理的信息，
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //线性滤波

	if (TextureImage)                //释放资源
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
	AUX_RGBImageRec *TextureImage; //保存贴图数据的指针
	TextureImage = auxDIBImageLoadA((LPCSTR)"ground.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//设置纹理的信息，
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //线性滤波

	if (TextureImage)                //释放资源
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
	AUX_RGBImageRec *TextureImage; //保存贴图数据的指针
	TextureImage = auxDIBImageLoadA((LPCSTR)"sky.bmp");
	//TextureImage_head = auxDIBImageLoadA((LPCSTR)"face.bmp");
	glGenTextures(1, &unTexture);
	glBindTexture(GL_TEXTURE_2D, unTexture);
	//设置纹理的信息，
	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //设置滤波为线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    //线性滤波

	if (TextureImage)                //释放资源
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色缓冲和深度缓冲
	DrawGround();
	DrawSky();
	glColor3f(0.8, 0.8, 0.8);

	glPushMatrix(); //robot的位置和方向设置
	glTranslatef(centerX, centerY, centerZ);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.5, 0.5); //设置颜色为灰色

	glPushMatrix();  //画出左大腿
	glColor3f(0.5, 0.5, 0.5);
	glRotatef((GLfloat)leftHigherLegAngle, 0, 0, 1.0);
	glTranslatef(0.5*leg_x / 2, 0.0, leg_z * 0.5);
	glPushMatrix();
	glScalef(leg_x, leg_y, leg_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(0.5 * leg_x / 2, 0.0, 0.0); //画关节
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5*leg_z / 2);
	gluCylinder(quadratic, 0.5 * leg_y / 2, 0.5 * leg_y / 2, leg_z * 0.5, 32, 32);
	glPopMatrix();
	glRotatef(LeftLowerLegAngle, 0.0, 0.0, 1.0); //画左小腿
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

	glPushMatrix();  //画出右大腿
	glColor3f(0.25, 0.45, 0.25);
	glRotatef((GLfloat)rightHigherLegAngle, 0, 0, 1.0);
	glTranslatef(leg_x / 4, 0.0, -leg_z / 2);
	glPushMatrix();
	glScalef(leg_x, leg_y, leg_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();
	glTranslatef(leg_x / 4, 0, 0); //画关节
	glPushMatrix();
	glTranslatef(0.0, 0.0, -leg_z / 4);
	gluCylinder(quadratic, leg_y / 4, leg_y / 4, leg_z / 2, 32, 32);
	glPopMatrix();
	glRotatef(rightLowerLegAngle, 0.0, 0.0, 1.0); //画左小腿
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

	// 身体
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glColor3f(0.65, 0.45, 0.45);
	glTranslatef(0, body_y / 4, 0.0);
	drawCube(body_x, body_y, body_z);
	glPopMatrix();

	glPushMatrix(); //脖子
	glColor3f(0.25, 0.75, 0.75);
	glTranslatef(0, 0.5*body_y, 0);
	glScalef(neck_x, neck_y, neck_z);
	glutSolidCube(GLOBAL_SIZE);
	glPopMatrix();

	// 头部
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(0, 0.5*body_y + 0.5*head_y, 0);
	drawCube_head(head_x, head_y, head_z);
	glPopMatrix();

	glColor3f(0.5, 0.55, 0.55);
	glPushMatrix();	//画左手
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

	glPushMatrix();	//画右手
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
//实时刷新
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

//响应鼠标事件
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
//规定当角度大于-75度时，小腿的角度变化，并比大腿变化快，规定是大腿地4倍
//响应键盘事件的，当按'w'时先前走，当按's'时为向后转
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':

		for (int i = 0; i < speed; i++) {

			centerY = leg_x * sin(-leftHigherLegAngle / 180.0 * PI) - leg_x;
			// 为了简化计算，我粗略假定大腿每动1度，人会朝着其方向前进0.035个单位长度
			double mvx = cos(angle / 180.0 * PI) * 0.035; // 计算x轴方向移动的距离
			double mvz = sin(angle / 180.0 * PI) * 0.035; // 计算z轴方向移动的距离
			if (!left) { //左脚迈出
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

			// 调整视角，始终把屏幕中心对准人的中心
			glLoadIdentity();
			gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
			glutPostRedisplay();
		}
		break;
	case 's':
		angle = (angle + 180) % 360;

		glutPostRedisplay();
		break;
	case 'a': //左转
		angle = (angle + 5) % 360;
		glutPostRedisplay();
		break;
	case 'd': //右转
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

//设置光照  
void SetupLights()
{
	GLfloat ambientLight[] = { 0.45f,  0.45f,  0.5f,  1.0f };//环境光  
	GLfloat diffuseLight[] = { 0.55f,  0.55f,  0.55f,  1.0f };//漫反射  
	GLfloat specularLight[] = { 0.6f,  0.6f,  0.6f,  1.0f };//镜面光  
	GLfloat lightPos[] = { 50.0f, 80.0f, 60.0f, 1.0f };//光源位置  

	glEnable(GL_LIGHTING);          //启用光照  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);    //设置环境光源  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);    //设置漫反射光源  
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);   //设置镜面光源  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);        //设置灯光位置  
	glEnable(GL_LIGHT0);            //打开第一个灯光  

	glEnable(GL_COLOR_MATERIAL);    //启用材质的颜色跟踪  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  //指定材料着色的面  
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //指定材料对镜面光的反应  
	glMateriali(GL_FRONT, GL_SHININESS, 100);           //指定反射系数  
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
	glutReshapeFunc(reshape);  //屏幕刷新是用
	glutKeyboardFunc(keyboard);//按下按键
	glutPassiveMotionFunc(passiveMotionFunc);//鼠标转动
	SetupLights();
	glutMainLoop();
	return 0;
}
