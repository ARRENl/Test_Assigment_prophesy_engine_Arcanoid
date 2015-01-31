/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.


    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.


	source:
		OpenGL example ( windowed )

	revision history:
		Dec/27/2000 - Edmond Cote - initial revision
*/
#define PRCORE_IMPLEMENT_MAIN
#include <prcore/prcore.hpp>
#include <GL/gl.h>

using namespace prcore;


// =============================================================
// window class
// =============================================================

class TestWindow : public WindowGL
{
	public:

	TestWindow(int width, int height)
	{
		// open window
		OpenWindow(width,height,"TestWindow",WINDOW_NORMAL|WINDOW_USES3D);

		// create render context
		context = CreateContext();
		SetContext(context);
	}

	~TestWindow()
	{
		// delete render context
		DeleteContext(context);
	}

	bool EventMain()
	{
		EventDraw();
		return true;
	}

	void EventDraw()
	{
		// clear
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
		// projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);

		// modelview matrix	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
  
		// draw polygon
		glBegin(GL_POLYGON);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.25f,0.25f,0.0f);
		glVertex3f(0.75f,0.25f,0.0f);
		glVertex3f(0.75f,0.75f,0.0f);
		glVertex3f(0.25f,0.75f,0.0f);
		glEnd();
	
		// pageflip
		PageFlip();
	}

	void EventSize(int width, int height)
	{
		glViewport(0,0,width,height);
		glScissor(0,0,width,height);
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
	}

	private:

	ContextGL* context;
};


// =============================================================
// prmain()
// =============================================================

int prmain(int argc, char** argv)
{
	TestWindow window(512,384);
	window.MainLoop();

	return 0;
}
