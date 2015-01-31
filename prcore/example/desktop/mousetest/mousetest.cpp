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
		mouse test/example

	revision history:
		Apr/24/2003 - Jukka Liimatta - initial revision
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
	: buffer(width,height,PIXELFORMAT_ARGB8888),
	  sprite("../leaf.tga"),x(20),y(20),color(0)
	{
		// open framebuffer
		OpenBuffer(width,height,"TestWindow");

		// change pixelformat
		sprite.ReformatImage(PIXELFORMAT_ARGB8888);
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
		buffer.ClearImage(color);

		// setup alphablending
		SetAlphaFunc(SRCALPHA,SRCINVALPHA);
		SetConstantAlpha(0xff,0xff);

		// blend the sprite into the buffer
		AlphaBlend(x,y,buffer,sprite);

		BlitWrite(0,0,buffer);
		PageFlip();
	}

	void EventSize(int width, int height)
	{
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
	}

	void EventMouseButton(int mx, int my, MouseButton button, int count)
	{
		switch ( button )
		{
			case MOUSE_LEFT:
				switch ( count )
				{
					case 1: color = 0x00ff0000; break;
					case 2: color = 0x0000ff00; break;
				}
				break;

			case MOUSE_MIDDLE:
				switch ( count )
				{
					case 1: color = 0x000000ff; break;
					case 2: color = 0x00ffff00; break;
				}
				break;

			case MOUSE_RIGHT:
				switch ( count )
				{
					case 1: color = 0x00000000; break;
					case 2: color = 0x00ffffff; break;
				}
				break;

			case MOUSE_XBUTTON1:
				switch ( count )
				{
					case 1: color = 0x0000ffff; break;
					case 2: color = 0x00ff00ff; break;
				}
				break;

			case MOUSE_XBUTTON2:
				switch ( count )
				{
					case 1: color = 0x000f707f; break;
					case 2: color = 0x00448811; break;
				}
				break;

			case MOUSE_WHEEL:
				y -= count / 12;
				break;
		}
	}

	private:

	Timer timer;
	Bitmap buffer;
	Bitmap sprite;
	uint32 color;
	int x;
	int y;
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
