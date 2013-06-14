//ok it's c++ but this doesn't mean there are c++ objects 
#include <windows.h> 
#include <windowsx.h>
#include <math.h>
#include <gl/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h> //read() write() !!

int mousex=0,mousey=0;

GLfloat counter=0,posx=0,posy=0;
typedef struct {GLfloat x;GLfloat y;}vektor;
vektor richtungsvektor,ortsvektor;


LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

GLvoid glPrint(const char *fmt, ...);
GLuint	base;	

GLvoid BuildFont(GLvoid){
	base = glGenLists(96);						
}

     
GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text	
}

GLvoid KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{            
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLpong";
    RegisterClass (&wc);
    hWnd = CreateWindow (
      "GLpong", "ponggl", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      70, 70, 800, 600,
      NULL, NULL, hInstance, NULL);
    EnableOpenGL (hWnd, &hDC, &hRC);
BuildFont();
	wglUseFontBitmaps(hDC, 32, 96, base);	
 
    while (!bQuit)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }           
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
glClear (GL_COLOR_BUFFER_BIT);

//glColor3f(1,1,1);           
//glPushMatrix();


glBegin(GL_TRIANGLE_FAN); //ball
//glColor3f(1,0,0);

glColor3f(0,1,0);
glVertex3f(posx+(GLfloat).01,posy+(GLfloat).01,0);
glVertex3f(posx-(GLfloat).01,posy+(GLfloat).01,0);
glVertex3f(posx-(GLfloat).01,posy-(GLfloat).01,0);
glVertex3f(posx+(GLfloat).01,posy-(GLfloat).01,0);
		
glEnd();

glBegin(GL_TRIANGLES); //paddle
//glColor3f(1,0,0);

glColor3f(0,1,0);
glVertex3f((GLfloat)(mousex-400)/400,(GLfloat)-1*(mousey-300)/300,0);
glVertex3f(0,0,0);
glVertex3f((GLfloat)(mousex-400)/400-(GLfloat).1,(GLfloat)-1*(mousey-300)/300,0);
		
glEnd();


                  
glRasterPos2f(0.05f,0.05f); 
glPrint("testx%f",(float)mousex); 

if (posx==0){richtungsvektor.x=(GLfloat).01;richtungsvektor.y=(GLfloat).03;}
if (posx>1){glPrint("gr%f",(float)posx);richtungsvektor.x=(GLfloat)-.01; }
if (posx<-1){glPrint("kl%f",(float)posx);richtungsvektor.x=(GLfloat)+.01; }
if (posy>1){glPrint("gr%f",(float)posy);richtungsvektor.y=(GLfloat)-.03; }
if (posy<-1){glPrint("kl%f",(float)posy);richtungsvektor.y=(GLfloat)+.03; }

//if (-0.5>posx){glPrint("kl%f",(float)posx);richtungsvektor.x=-.001; }

/*if (posx<-0.5f){richtungsvektor.x=-.001;}
if (posy>0.5f){richtungsvektor.y=.002;}
if (posy<-0.5f){richtungsvektor.y=-.002;}
*/
posx+=richtungsvektor.x;
posy+=richtungsvektor.y;





//glPopMatrix();
SwapBuffers (hDC);
        }
    }

    DisableOpenGL (hWnd, hDC, hRC);
    DestroyWindow (hWnd);

    return msg.wParam;

}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
         KillFont();
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;
  case WM_LBUTTONDOWN:

    return 0;
   case WM_MOUSEMOVE:

         mousex=GET_X_LPARAM(lParam);
         mousey=GET_Y_LPARAM(lParam);
       
         return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_F1:
             return 0;
        case VK_F2:
             return 0;
        case VK_UP:
        return 0;
        case VK_DOWN:
        return 0;
        case 0x51:
        return 0;
        case 0x4B:
        return 0;
        case 0x4C:
        return 0;
        case 0x41://A
        return 0;
        case 0x42://B
        return 0;
        case 0x43://c
        return 0;
        case 0x46://F
        return 0;
        case 0x52://T
        return 0;
        case 0x47:
        glRotatef(45,0,1,0);
        return 0;
        case 0x53:
        return 0;
        case VK_ESCAPE:

            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    *hDC = GetDC (hWnd);
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
