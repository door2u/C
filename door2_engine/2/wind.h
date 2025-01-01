#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xfixes.h>
#include <X11/Xatom.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

static Display *disp;
static int scre;
static Window root;
Window wind;
XEvent even;
XVisualInfo *xvis;
XSetWindowAttributes windAttrSet_;
XWindowAttributes windAttr;
Colormap colo;
GLint attr[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
GLXContext glxc;

void Init(unsigned int *widt, unsigned int *heig, float skyr, float skyg, float skyb, float skya, bool fullScre, bool warpPoin, bool hideCurs) {
	disp = XOpenDisplay((char*)0);
	if (disp == NULL) {
		std::cout << "could not open display" << std::endl;
		exit(-1);
	}
	scre = DefaultScreen(disp);
	root = XDefaultRootWindow(disp);
	xvis = glXChooseVisual(disp, 0, attr);
	if (xvis == NULL) {
		std::cout << "could not choose visual" << std::endl;
		exit(-1);
	}
	colo = XCreateColormap(disp, root, xvis->visual, AllocNone);
	windAttrSet_.colormap = colo;
	//windAttrSet_.event_mask = ExposureMask | ButtonPressMask | KeyPressMask | KeyReleaseMask | PointerMotionMask;
	windAttrSet_.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask;
	if (fullScre == true) {
		*widt = XWidthOfScreen(ScreenOfDisplay(disp, scre));
		*heig = XHeightOfScreen(ScreenOfDisplay(disp, scre));
	}
	wind = XCreateWindow(disp, root, 0, 0, *widt, *heig, 0, xvis->depth, InputOutput, xvis->visual, CWColormap | CWEventMask, &windAttrSet_);
	XSync(disp, true);
	if (fullScre == true) {
		Atom wm_state = XInternAtom(disp, "_NET_WM_STATE", true);
		Atom wm_fullscreen = XInternAtom (disp, "_NET_WM_STATE_FULLSCREEN", true);
		XChangeProperty(disp, wind, wm_state, XA_ATOM, 32, PropModeReplace, (unsigned char *)&wm_fullscreen, 1);
	}
	if (warpPoin == true) {
		XWarpPointer(disp, None, wind, even.xmotion.x, even.xmotion.y, *widt, *heig, (int)(*widt / 2.0), (int)(*heig / 2.0));
	}
	if (hideCurs == true) {
		XFixesHideCursor(disp, DefaultRootWindow(disp));
	}
	XSetStandardProperties(disp, wind, "3D Engine", NULL, None, NULL, 0, NULL);
	glxc = glXCreateContext(disp, xvis, NULL, GL_TRUE);
	glXMakeCurrent(disp, wind, glxc);
	XClearWindow(disp, wind);
	XMapRaised(disp, wind);
	XMapWindow(disp, wind);
	glClearColor(skyr, skyg, skyb, skya);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5, 0.5, -0.5, 0.5, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	XGetWindowAttributes(disp, wind, &windAttr);
	glViewport(0, 0, windAttr.width, windAttr.height);
	glEnable(GL_DEPTH_TEST);
}

void Clos(Display *disp, GLXContext glxc, Window wind) {
	glXMakeCurrent(disp, None, NULL);
	glXDestroyContext(disp, glxc);
	XUnmapWindow(disp, wind);
	XDestroyWindow(disp, wind);
	XCloseDisplay(disp);
}
