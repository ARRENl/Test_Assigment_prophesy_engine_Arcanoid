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
		alpha blending example

	revision history:
		Dec/07/2001 - Jukka Liimatta - initial revision
*/
#define PRCORE_IMPLEMENT_MAIN
#include <prcore/prcore.hpp>

using namespace prcore;


// =============================================================
// window class
// =============================================================

class TestWindow : public FrameBuffer
{
	public:

	TestWindow(int width, int height)
	{
		// open framebuffer
		OpenBuffer(width,height,"TestWindow");

		// initialize bitmaps
		buffer = Bitmap(width,height,   PIXELFORMAT_ARGB8888);
		screen = Bitmap("../screen.jpg",PIXELFORMAT_ARGB8888);
		sprite = Bitmap("../leaf.tga"  ,PIXELFORMAT_ARGB8888);
	}

	~TestWindow()
	{
	}

	bool EventMain()
	{
		EventDraw();
		return true;
	}

	void EventDraw()
	{
		float time = timer.GetTime();
		int x = static_cast<int>(sin(time) * 60 + 80);

		// "clear" buffer with screen/background bitmap
		buffer.BlitImage(screen);

		// setup alphablending
		SetAlphaFunc(SRCALPHA,SRCINVALPHA);
		SetConstantAlpha(0xff,0xff);

		// blend the sprite into the buffer
		AlphaBlend(x,10,buffer,sprite);

		BlitWrite(0,0,buffer);
		PageFlip();
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
	}
	
	private:

	Timer	timer;
	Bitmap	buffer;
	Bitmap	screen;
	Bitmap	sprite;
};


// =============================================================
// prmain()
// =============================================================

int prmain(int argc, char** argv)
{
	TestWindow window(400,300);
	window.MainLoop();
  
	return 0;
}
