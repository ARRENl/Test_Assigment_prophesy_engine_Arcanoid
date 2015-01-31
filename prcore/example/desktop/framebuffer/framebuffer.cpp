#define PRCORE_IMPLEMENT_MAIN
#include <prcore/prcore.hpp>
using namespace prcore;


class TestWindow : public FrameBuffer
{
public:

	TestWindow() : bitmap("../haxor.jpg")
	{
	}

	void CreateCanvasWindow(HWND h)
	{

		int width  = 300;
		int height = 300;

		WindowHandle wh;
		wh.hwnd = h;
		//OpenBuffer(wh, width, height);
		OpenBuffer(300,300, "jojo");
	}


	void DestroyCanvasWindow()
	{
		CloseBuffer();
	}

	~TestWindow()
	{
		// close framebuffer
	}

	bool EventMain()
	{
		// yes, we want to keep rolling..
		return true;
	}

	void EventDraw()
	{
		ClearBuffer(0x0);
		Beep(1000,1);
		//BlitWrite(0,0,bitmap);
		PageFlip();
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
	}
private:
	Bitmap bitmap;
};

TestWindow *window;


// =============================================================
// prmain()
// =============================================================

int prmain(int argc, char** argv)
{
	window = new TestWindow();
	window->CreateCanvasWindow(0);

	///Sleep(5000);
	window->MainLoop();

	window->DestroyCanvasWindow();
	delete window;

	return 0;
}
