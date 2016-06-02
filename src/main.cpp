/*
Autor : Diego A Perez A
CI : 19754458
*/

#pragma comment (lib, "lib/glut32.lib")

#include "curva.h"
vector<punto*> v;
vector<curva*> c;
punto * point;
curva * cur;
int puntomove=0;
int puntos=0;
int hay=0;
float rc=1.0,gc=1.0,bc=1.0,rr=1.0,gr=1.0,br=1.0;//color tanto curva como relleno
bool colocarpunto=true;
bool curva_nueva=true;
bool rellenar=false;
bool color =false;
bool aumentar=false;

float abs_abs(float x)
{
	if(x > 0)
		return(x);
	else
		return (-x);
}

float GlutToOpenglx(float x)
{
		int auxx=glutGet(GLUT_WINDOW_WIDTH)>>1;
		//printf("%d\n",auxx);
		x=(x/auxx) - 1;
		//x = (float)(2*x-(glutGet(GLUT_WINDOW_WIDTH)-1) )/(glutGet(GLUT_WINDOW_WIDTH)-1);
		return x;
}
float GlutToOpengly(float y)
{
		int auxy=glutGet(GLUT_WINDOW_HEIGHT)>>1;
		y=((y/auxy)-1)*-1;
		//y= (float)((glutGet(GLUT_WINDOW_HEIGHT)-1)-2*y)/(glutGet(GLUT_WINDOW_HEIGHT)-1);
		return y;
}
void AumentarGrado()
{
	unsigned int i;
	unsigned n = v.size();
	vector<punto*> aux;
	punto * nuevo = new punto();
	nuevo->vx =v[v.size() -1]->vx;
	nuevo->vy =v[v.size() -1]->vy;
	v.push_back(nuevo);
	for(i=0;i<v.size();i++)
	{
		 nuevo = new punto();
		 aux.push_back(nuevo);
		 aux[i]->vx=v[i]->vx;
		 aux[i]->vy=v[i]->vy;
	}
	for(i=1;i<n;i++)
	{
		v[i]->vx = ((float)i/n) * aux[i-1]->vx + (1 - (float)i/n)*aux[i]->vx;
		v[i]->vy = ((float)i/n) * aux[i-1]->vy + (1 - (float)i/n)*aux[i]->vy;
	}
	cur->crear_curva(v);
	aumentar=true;

}
void menuApp(int value)
{
	if(value == 1)colocarpunto=true;
	if(value == 2)
	{
		if(hay)
			colocarpunto=false;
	}
	if(value == 3)
	{
		if(hay)
			AumentarGrado();
	}
	if(value == 4)
	{
		colocarpunto=true;
		v.clear();
		puntomove=0;
		curva_nueva=true;
		rellenar=false;
		hay=0;
	}
	if(value == 9)exit(0);
}
void menuApp2(int value)
{
	if(value == 1)
	{
		rc=1.0;gc=1.0;bc=1.0;
	}
	if(value == 2)
	{
		rc=1.0;gc=1.0;bc=0.0;
	}
	if(value == 3)
	{
		rc=0.0;gc=1.0;bc=0.0;
	}
	if(value == 4)
	{
		rc=0.0;gc=1.0;bc=1.0;
	}
	if(value == 5)
	{
		rc=0.0;gc=0.0;bc=1.0;
	}
	if(value == 6)
	{
		rc=1.0;gc=0.0;bc=1.0;
	}
	if(value == 7)
	{
		rc=1.0;gc=0.0;bc=0.0;
	}
	if(hay)
	{
		cur->cambiar_color(rc,gc,bc);
		color =true;
	}
}
void menuApp3(int value)
{
	if(value == 1)
	{
		rr=1.0;gr=1.0;br=1.0;
	}
	if(value == 2)
	{
		rr=1.0;gr=1.0;br=0.0;
	}
	if(value == 3)
	{
		rr=0.0;gr=1.0;br=0.0;
	}
	if(value == 4)
	{
		rr=0.0;gc=1.0;br=1.0;
	}
	if(value == 5)
	{
		rr=0.0;gr=0.0;br=1.0;
	}
	if(value == 6)
	{
		rr=1.0;gr=0.0;br=1.0;
	}
	if(value == 7)
	{
		rr=1.0;gr=0.0;br=0.0;
	}
	if(hay)
	{
			cur->rellenar(rr,gr,br);
			rellenar = true;
	}
}
void renderScene (void)
{
	//submenus
	void init();
	{
		int submenu_color_curva, submenu_color_relleno;
		submenu_color_curva=glutCreateMenu(menuApp2);
		glutAddMenuEntry ("Blanco",1);
		glutAddMenuEntry ("Amarillo",2);
		glutAddMenuEntry ("Verde",3);
		glutAddMenuEntry ("Cyan",4);
		glutAddMenuEntry ("Azul",5);
		glutAddMenuEntry ("Magenta",6);
		glutAddMenuEntry ("Rojo",7);

		submenu_color_relleno=glutCreateMenu(menuApp3);
		glutAddMenuEntry ("Blanco",1);
		glutAddMenuEntry ("Amarillo",2);
		glutAddMenuEntry ("Verde",3);
		glutAddMenuEntry ("Cyan",4);
		glutAddMenuEntry ("Azul",5);
		glutAddMenuEntry ("Magenta",6);
		glutAddMenuEntry ("Rojo",7);

		glutCreateMenu (menuApp);

		glutAddMenuEntry ("Colocar puntos",1);
		glutAddMenuEntry ("Editar puntos",2);
		glutAddMenuEntry ("Aumentar Grado de la Curva",3);
		glutAddMenuEntry ("Terminar Curva",4);
		//glutAddSubMenu ("Formas",submenu_forma);
		//glutAddSubMenu ("Tipo linea",submenu_tipo_linea);
		//glutAddSubMenu ("Despliegue",submenu_despliegue);
		glutAddSubMenu ("Color Curva",submenu_color_curva);
		glutAddSubMenu ("Color Relleno",submenu_color_relleno);
		glutAddMenuEntry ("Salir",9);
		glutAttachMenu (GLUT_RIGHT_BUTTON);
	}
	//fin submenus
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(puntos>0)
	{
		for(unsigned int i=0;i < c.size();i++)
		{
			c.at(i)->Draw();
		}
	}
	for(unsigned int i=0;i < v.size();i++)
	{
		v.at(i)->Draw();
	}
	glutSwapBuffers();
}
void limpiarPantalla()
{
	v.clear();
	c.clear();
	puntomove=0;
	curva_nueva=true;
	rellenar=false;
	color =false;
	aumentar =false;
	hay=0;
	colocarpunto=true;
	renderScene();
}
void teclado (unsigned char key, int x, int y)
{
	if(key==27)
		limpiarPantalla();
}
void pasivo (int x, int y)
{
	if(curva_nueva || rellenar || color || aumentar)
	{
		color=false;
		aumentar =false;
		rellenar =false;
		renderScene();
	}
}
void click (int boton, int estado, int x, int y)
{
	if((estado==GLUT_DOWN) && colocarpunto)
	{
		point = new punto();
		if(curva_nueva)
		{
			cur=new curva();
			c.push_back(cur);
			curva_nueva =false;
			rellenar = false;
		}
		v.push_back(point);
		point->vx=GlutToOpenglx((float)x);
		point->vy=GlutToOpengly((float)y);
		cur->crear_curva(v);
		puntos++;hay++;
		renderScene();
	}
	if((estado==GLUT_DOWN) && !colocarpunto)
	{
		float X = GlutToOpenglx((float)x);
		float Y = GlutToOpengly((float)y);
		unsigned int i;
		for(i=0;i<v.size();i++)
		{
			//printf("%f\n",abs(v[i]->vx - X));
			if (abs_abs(v[i]->vx - X) < 0.02  &&  abs_abs(v[i]->vy - Y) < 0.02)
			{
				v[i]->vx=X;
				v[i]->vy=Y;
				v[i]->move=true;
				puntomove=i;
				
				break;
			}
			//printf("%d\n",i);
		}
	}
	if((estado==GLUT_UP))
	{
		if(hay)
			v[puntomove]->move=false;
	}
}
void movimiento (int x, int y)
{
	if(!colocarpunto)
	{
		float X = GlutToOpenglx((float)x);
		float Y = GlutToOpengly((float)y);
		if(v[puntomove]->move)
		{
			v[puntomove]->vx=X;
			v[puntomove]->vy=Y;
			cur->crear_curva(v);
		}
		renderScene();
	}
}
int main (int argc, char *argv [])
{
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (500, 500);
	glutCreateWindow ("Tarea#2");
	//glEnable(GL_LINE_STIPPLE);
	glutDisplayFunc (renderScene);
	//glutReshapeFunc(ReSizeGLScene);
	glutMotionFunc(movimiento);
	glutMouseFunc(click);
	glutKeyboardFunc(teclado);
	glutPassiveMotionFunc(pasivo);
	glutMainLoop ();

}