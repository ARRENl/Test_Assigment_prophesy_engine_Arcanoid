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
		Jul/01/2003 - Jukka Liimatta - initial revision
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

	TestWindow()
	{
		// open framebuffer
		OpenBuffer(640,480,"TestWindow");

		// init buffer bitmap
		buffer = Bitmap(640,480,PIXELFORMAT_ARGB8888);

		// init images
		image1 = Bitmap("image1.jpg",PIXELFORMAT_ARGB8888);
		image2 = Bitmap("image2.jpg",PIXELFORMAT_ARGB8888);
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
		uint8 alpha = static_cast<uint8>(sin(time) * 127 + 128);

		if ( IsDown(KEYCODE_X) )
		{
			// saturation effect
			prcore::SetConstantAlpha(alpha,255);
			prcore::SetAlphaFunc(SRCINVALPHA,ONE);
			prcore::AlphaBlendVolatile(buffer,image1,image1);
		}
		else
		{
			// crossfade effect
			prcore::SetConstantAlpha(alpha,255);
			prcore::SetAlphaFunc(SRCALPHA,SRCINVALPHA);
			prcore::AlphaBlendVolatile(buffer,image1,image2);
		}

		BlitWrite(0,0,buffer);
		PageFlip();
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
	}

	private:

	Timer		timer;
	Bitmap		buffer;
	Bitmap		image1;
	Bitmap		image2;
};


// =============================================================
// prmain()
// =============================================================

int prmain(int argc, char** argv)
{
	TestWindow window;
	window.MainLoop();

	return 0;
}
