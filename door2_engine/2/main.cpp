
#include <iostream>
#include <chrono>

#include "wind.h"
#include "obje/obje_data.h"

int main(int argc, char **argv) {
	
	// window resolution
	unsigned int widt = 640; unsigned int heig = 480;
	// background color
	float skyr = 0.6; float skyg = 0.8;	float skyb = 1.0; float skya = 1.0;
	// use fullscreen
	bool fullScre = true;
	//fullScre = false;
	// lock the mouse position to the screen center
	bool warpPoin = true;
	//warpPoin = false;
	// hide the mouse cursor
	bool hideCurs = true;
	//hideCurs = false;
	// time of one frame in billionths of a second
	int timeFram = 16666667;
	// print statements to console
	bool prin = true;
	prin = false;
	// camera movement speed
	float cameSpee = 0.1;
	
	///////////////////////////////////////////////////////////////
	
	void Load(std::vector<ObjeInit> &objeInitList, std::vector<ObjeDyna> &objeDynaList, std::vector<ObjeStat> &objeStatList, Came came, bool prin = false);
	void Init(unsigned int *widt, unsigned int *heig, float skyr, float skyg, float skyb, float skya, bool fullScre, bool warpPoin, bool hideCurs);
	void Inpu(unsigned int widt, unsigned int heig, Display *disp, XEvent *even, bool *keyw, bool *keya, bool *keys, bool *keyd, bool *keyq, bool *keye, int *difx, int *dify, bool *runn);
	void Move(unsigned int widt, unsigned int heig, Came *came, bool keyw, bool keya, bool keys, bool keyd, bool keyq, bool keye, int difx, int dify, float cameSpee, Display *disp, Window *wind, int soux, int souy, bool warpPoin);
	void Rend(std::vector<ObjeDyna> objeDynaList, std::vector<ObjeStat> objeStatList, Came came, unsigned int widt, unsigned int heig, Display *disp, Window *wind, float skyr, float skyg, float skyb, float skya, bool prin);
	void Clos(Display *disp, GLXContext grap, Window wind);

	// make a camera
	Came came;
	came.loca.z = 3.0;
	// read geometry
	std::vector<ObjeInit> objeInitList;
	std::vector<ObjeDyna> objeDynaList;
	std::vector<ObjeStat> objeStatList;
	Load(objeInitList, objeDynaList, objeStatList, came, prin);
	objeInitList.clear();
	
	// make a window
	Init(&widt, &heig, skyr, skyg, skyb, skya, fullScre, warpPoin, hideCurs);
	// break game loop if the window is closed
	Atom clos = XInternAtom(disp, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(disp, wind, &clos, 1);
	// are these keys being held
	bool keyw = false;
	bool keya = false;
	bool keys = false;
	bool keyd = false;
	bool keyq = false;
	bool keye = false;
	// mouse movement
	int difx = 0;
	int dify = 0;
	// timing
	long long unsigned int framCoun = 0;
	// TODO: try to get rid of auto
	auto timeNow_ = std::chrono::steady_clock::now();
	auto timeComp = std::chrono::steady_clock::now();
	auto timeElap = timeComp - timeNow_;
	
	bool runn = true;
	while (runn) {
		if (XPending(disp)) {
			Inpu(widt, heig, disp, &even, &keyw, &keya, &keys, &keyd, &keyq, &keye, &difx, &dify, &runn);
		}
		else {
			timeComp = std::chrono::steady_clock::now();
			timeElap = timeComp - timeNow_;
			if (timeElap.count() > timeFram) {
				timeNow_ = std::chrono::steady_clock::now();
				Move(widt, heig, &came, keyw, keya, keys, keyd, keyq, keye, difx, dify, cameSpee, disp, &wind, even.xmotion.x, even.xmotion.y, warpPoin);
				for (unsigned int a = 0; a < objeStatList.size(); a++) {
					objeStatList[a].BackCull(came);
				}
				Rend(objeDynaList, objeStatList, came, widt, heig, disp, &wind, skyr, skyg, skyb, skya, prin);
				if (prin == true) std::cout << "rendered" << std::endl;
				framCoun += 1;
			}
		}
		if (even.type == ClientMessage && (unsigned int)even.xclient.data.l[0] == clos) {
			runn = false;
		}
	}
	Clos(disp, glxc, wind);
	return 0;
}

void Rend(std::vector<ObjeDyna> objeDynaList, std::vector<ObjeStat> objeStatList, Came came, unsigned int widt, unsigned int heig, Display *disp, Window *wind, float skyr, float skyg, float skyb, float skya, bool prin) {
	void ObjeProc(std::vector<ObjeDyna> objeDynaList, std::vector<ObjeStat> objeStatList, Came came, unsigned int widt, unsigned int heig);
	void Refr(Display *disp, Window *wind, float skyr, float skyg, float skyb, float skya);
	// signal to gl that triangles are going to be added
	glBegin(GL_TRIANGLES);
	ObjeProc(objeDynaList, objeStatList, came, widt, heig);
	glEnd();
	if (prin == true) std::cout << "passed polygon data to GL" << std::endl;
	// refresh gl / x11
	Refr(disp, wind, skyr, skyg, skyb, skya);
}

void Inpu(unsigned int widt, unsigned int heig, Display *disp, XEvent *even, bool *keyw, bool *keya, bool *keys, bool *keyd, bool *keyq, bool *keye, int *difx, int *dify, bool *runn) {
	char keybInpu[1] = "";
	KeySym key;
	XNextEvent(disp, even);
	if (even->type == MotionNotify) {
		*difx = even->xmotion.x - widt / 2;
		*dify = even->xmotion.y - heig / 2;
	}
	if (even->type == KeyPress && XLookupString(&even->xkey, keybInpu, 255, &key, 0) == 1) {
		// ESC
		if (keybInpu[0] == 27) *runn = false;
		if (keybInpu[0] == 'w') *keyw = true;
		if (keybInpu[0] == 'a') *keya = true;
		if (keybInpu[0] == 's') *keys = true;
		if (keybInpu[0] == 'd') *keyd = true;
		if (keybInpu[0] == 'q') *keyq = true;
		if (keybInpu[0] == 'e') *keye = true;
	}
	if (even->type == KeyRelease && XLookupString(&even->xkey, keybInpu, 255, &key, 0) == 1) {
		if (keybInpu[0] == 'w') *keyw = false;
		if (keybInpu[0] == 'a') *keya = false;
		if (keybInpu[0] == 's') *keys = false;
		if (keybInpu[0] == 'd') *keyd = false;
		if (keybInpu[0] == 'q') *keyq = false;
		if (keybInpu[0] == 'e') *keye = false;
	}
}

void Move(unsigned int widt, unsigned int heig, Came *came, bool keyw, bool keya, bool keys, bool keyd, bool keyq, bool keye, int difx, int dify, float cameSpee, Display *disp, Window *wind, int soux, int souy, bool warpPoin) {
	// mouse look sensitivity
	float sens = 1.0 / 10.0;
	if (warpPoin && (difx != 0 || dify != 0)) {
		XWarpPointer(disp, None, *wind, soux, souy, widt, heig, (int)(widt / 2), (int)(heig / 2));
	}
	// handle horizotal mouse movement
	// axes around which mouse changes in x cause the camera to rotate
	Vec3 moux;
	moux.z = 1.0;
	if (difx != 0) {
		float mo_x = -difx * sens;
		came->u.Quat(mo_x, moux);
		came->w.Quat(mo_x, moux);
		came->v.Quat(mo_x, moux);
	}
	// handle vertical mouse movement
	// is the camera aimed above or below straight ahead. positive: above. negative: below.
	float cameVert = came->w * moux;
	if (dify != 0) {
		float mo_y = -dify * sens;
		Vec3 camwNext = came->w;
		Vec3 camvNext = came->v;
		camwNext.Quat(mo_y, came->u);
		camvNext.Quat(mo_y, came->u);
		// will the cameras v axis be pointed in the negative z direction if the above rotation is applied
		float camvVert = camvNext * moux;
		if (camvVert < 0.0) {
			// set the camera to point straight up
			if (cameVert > 0.0) {
				came->w = moux;
				came->v = moux.Cros(came->u) * -1.0;
			}
			// set the camera to point straight down
			else {
				came->w = moux * -1.0;
				came->v = moux.Cros(came->u);
			}
		}
		// if the camera did not exceed either vertical limit, apply the rotation
		else {
			came->w = camwNext;
			came->v = camvNext;
		}
	}
	// handle w a s d q e
	float angl = 0.0;
	if (fabs(cameVert) < 0.9) {
		angl = atan2f(came->w.y, came->w.x);
	}
	else {
		angl = atan2f(came->v.y, came->v.x);
		if (cameVert > 0.0) {
			angl += pi;
		}
	}
	if (keyw == true) {
		came->loca.y += cameSpee * sinf(angl);
		came->loca.x += cameSpee * cosf(angl);
	}
	if (keyd == true) {
		came->loca.y -= cameSpee * sinf(angl + pi / 2.0);
		came->loca.x -= cameSpee * cosf(angl + pi / 2.0);
	}
	if (keys == true) {
		came->loca.y -= cameSpee * sinf(angl);
		came->loca.x -= cameSpee * cosf(angl);
	}
	if (keya == true) {
		came->loca.y += cameSpee * sinf(angl + pi / 2.0);
		came->loca.x += cameSpee * cosf(angl + pi / 2.0);
	}
	if (keyq == true) {
		came->loca.z += cameSpee;
	}
	if (keye == true) {
		came->loca.z -= cameSpee;
	}
}

void ObjeProc(std::vector<ObjeDyna> objeDynaList, std::vector<ObjeStat> objeStatList, Came came, unsigned int widt, unsigned int heig) {
	for (unsigned int s = 0; s < objeStatList.size(); s++) {
		objeStatList[s].VertProc(came);
		for (unsigned int c = 0; c < objeStatList[s].polyList.size(); c++) {
			objeStatList[s].PolyAppe(c, came.clip, came.rang, widt, heig);
		}
	}
	for (unsigned int d = 0; d < objeDynaList.size(); d++) {
		for (unsigned int c = 0; c < objeDynaList[d].polyList.size(); c++) {
			objeDynaList[d].PolyAppe(c, came.clip, came.rang, widt, heig);
		}
	}
}

void Refr(Display *disp, Window *wind, float skyr, float skyg, float skyb, float skya) {
	glXSwapBuffers(disp, *wind);
	glClearColor(skyr, skyg, skyb, skya);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
