/*
	Twilight Prophecy 3D/Multimedia SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2000 by Twilight 3D Finland Oy Ltd.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	Please read the file LICENSE.TXT for additional details.


	source:
		Quake .mdl model viewer

	revision history:
		Jul/30/2001 - Jukka Liimatta - initial revision
		Sep/23/2001 - Jukka Liimatta - cleanup
		Feb/06/2002 - Francesco Montecuccoli - boundbox drawing
*/
#define PRCORE_IMPLEMENT_MAIN
#define PRMATH_TYPENAME

#include <prcore/prcore.hpp>
#include <primport/primport.hpp>
#include <GL/gl.h>

using namespace prcore;
using namespace prmath;
using namespace primport;


// ===========================================================================
// CreateTextureGL()
// ===========================================================================

static void BlitTexture(const Surface& surface, int nlog)
{
	for ( int j=0; j<(nlog+1); ++j )
	{
		Bitmap mip = CreateMipLevel(surface,j);
		glTexImage2D(GL_TEXTURE_2D,
			j,GL_RGBA8,
			mip.GetWidth(),
			mip.GetHeight(),
			0,GL_RGBA,GL_UNSIGNED_BYTE,
			mip.GetImage());
	}
}


static GLuint CreateTextureGL(Bitmap map)
{
	// size
	int nlog = prcore::log2i(map.GetWidth());
	int size = 1 << nlog;

	// 32bit and square power-of-two textures
	map.ReformatImage(PixelFormat(32,0x0000ff,0x00ff00,0xff0000,0xff000000));
	map.ResizeImage(size,size);

	// create texture
	GLuint itx = 0;
	glGenTextures(1,&itx);
	glBindTexture(GL_TEXTURE_2D,itx);

	// create mipmap
	BlitTexture(map,nlog);

	return itx;
}


static GLuint CreateTextureGL(const char* filename)
{
	// load image
	Bitmap map(filename);
	return CreateTextureGL(map);
}


// ===========================================================================
// Model
// ===========================================================================

class Model : public RefCount
{
	public:

	ImportQ1MDL*	import;
	GLuint			texture;

	Model(const char* filename)
	: import(NULL),texture(0)
	{
		import = new ImportQ1MDL(filename);
		texture = CreateTextureGL(import->skin);
	}

	~Model()
	{
		import->Release();
	}

	void DrawModel(float time, bool bbox)
	{
		// interpolation
		int numframe = import->frames.GetSize();
		int frame0 = static_cast<int>(time) % numframe;
		int frame1 = static_cast<int>(time+1.f) % numframe;
		float t = time - static_cast<int>(time);

		// frames
		Array<VertexMDL>& va0 = import->frames[frame0].vertexarray;
		Array<VertexMDL>& va1 = import->frames[frame1].vertexarray;

		// texture
		glBindTexture(GL_TEXTURE_2D,texture);

		// draw bounding box
		if ( bbox )
		{
			point3f box0[8];
			point3f box1[8];
			import->frames[frame0].box.GetVertexArray8(box0);
			import->frames[frame1].box.GetVertexArray8(box1);

			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINE_LOOP);
				glVertex3fv(Lerp(box0[0],box1[0],t));
				glVertex3fv(Lerp(box0[1],box1[1],t));
				glVertex3fv(Lerp(box0[3],box1[3],t));
				glVertex3fv(Lerp(box0[2],box1[2],t));
			glEnd();
			glBegin(GL_LINE_LOOP);
				glVertex3fv(Lerp(box0[4],box1[4],t));
				glVertex3fv(Lerp(box0[5],box1[5],t));
				glVertex3fv(Lerp(box0[7],box1[7],t));
				glVertex3fv(Lerp(box0[6],box1[6],t));
			glEnd();
			glBegin(GL_LINES);
				for ( int j=0; j<4; ++j )
				{
					glVertex3fv(Lerp(box0[j],box1[j],t));
					glVertex3fv(Lerp(box0[j+4],box1[j+4],t));
				}
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}

		// innerloop
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,1.0f);
		for ( int i=0; i<import->faces.GetSize(); ++i )
		{
			FaceMDL& face = import->faces[i];

			for ( int j=0; j<3; ++j )
			{
				int index = face.index[j];

				glTexCoord2fv(face.texcoord[j]);
				glNormal3fv(Lerp(va0[index].normal,va1[index].normal,t));
				glVertex3fv(Lerp(va0[index].point,va1[index].point,t));
			}
		}
		glEnd();
	}

}; // class Model


// ===========================================================================
// WindowQuake
// ===========================================================================

class WindowQuake : public WindowGL
{
	public:
	
	WindowQuake(int width, int height)
	: context(NULL),model(NULL),speed(10),bbox(true)
	{
		// open window
		OpenWindow(width,height,"Quake MDL",WINDOW_NORMAL);

		// create render context
		context = CreateContext(NULL);

		// set current render context
		SetContext(context);

		// load Quake model
		model = new Model("../shambler.mdl");

		// render states
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CW);
	}

	~WindowQuake()
	{
		model->Release();

		DeleteContext(context);
		CloseWindow();
	}

	bool EventMain()
	{
		EventDraw();
		return true;
	}

	void EventDraw()
	{
		// time
		float time = timer.GetTime();

		// clear buffer
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-4,4,-3,3,6,500);

		// modelview
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0,-20,-150);
		glRotatef(time*20,0,1,0);

		// draw model
		model->DrawModel(time*speed,bbox);

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
		if ( !press )
			return;

		switch ( keycode )
		{
			case KEYCODE_ESC:
				MainBreak();
				break;

			case KEYCODE_UP:
				if (speed < 100) ++speed;
				break;

			case KEYCODE_DOWN:
				if (speed > 0) --speed;
				break;

			case KEYCODE_B:
				bbox = !bbox;
				break;
		}
	}

	ContextGL*	context;
	Timer		timer;
	Model*		model;
	int			speed;
	bool		bbox;
};


// ===========================================================================
// prmain()
// ===========================================================================

int prmain(int argc, char** argv)
{
	WindowQuake window(512,384);
	window.MainLoop();
  
	return 0;
}
