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
		Drag'n'drop example

	revision history:
		Oct/17/2001 - Jukka Liimatta - initial revision
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
	: bitmap(width,height,PIXELFORMAT_ARGB8888)
	{
		// open framebuffer
		OpenBuffer(width,height,"Drag/drop image file into this window.");

		// clear bitmap
		bitmap.ClearImage(0x00ff0000);
	}

	~TestWindow()
	{
	}

	bool EventMain()
	{
		return true;
	}

	void EventDraw()
	{
		BlitWrite(0,0,bitmap);
		PageFlip();
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
	}

	void EventDropFile(const String& filename)
	{
		// load image
		bitmap.LoadImage(filename);
		bitmap.ReformatImage(PIXELFORMAT_ARGB8888);

		int width  = bitmap.GetWidth();
		int height = bitmap.GetHeight();

		// resize framebuffer
		ResizeBuffer(width,height);

		// draw the dropped image
		EventDraw();
	}

	private:

	Bitmap bitmap;
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
