#define PRCORE_IMPLEMENT_MAIN
#include <prcore/prcore.hpp>
#include <vector>

using namespace prcore;
using std::vector;

#define window_w 640
#define window_h 480
#define club_medium 5
#define club_small 10

struct Vec2
{
	int x;
	int y;
	Vec2() {}
	Vec2(int x_, int y_) : x(x_), y(y_) {}

	Vec2& operator=(const Vec2& right) {
		
		if (this == &right) {
			return *this;
		}
		x = right.x;
		y = right.y;
		return *this;
	}

	Vec2& operator+=(Vec2& right)
	{
		this->x += right.x;
		this->y += right.y;
		return *this;
	}
};

struct object_brick
{
	Vec2 position; //position
	Vec2 size;
	bool isDead;
	prcore::Rect rect_bounds;
	object_brick() : isDead(false) {}
	object_brick(Vec2 pos, Vec2 s) : isDead(false), position(pos), size(s), rect_bounds(pos.x, pos.y, s.x, s.y ) { }
};

// =============================================================
// window class
// =============================================================

class Arcanoid : public FrameBuffer
{
	public:
		Arcanoid()
	{
		// open framebuffer
		OpenBuffer(window_w, window_h, "Arcanoid");
		
		m_level = 1;

		//field collision shape
		m_field_shape = Rect(0, 0, window_w, window_h);

		//brick init
		m_bricts_number = 60;
		initialize_brick_field();

		//club info
		int club_w = window_w / club_medium; //128 //64
		int clib_h = 20;
		m_club_pos = Vec2(window_w - 2 * club_w, 450);
		m_club_size = Vec2(club_w, clib_h);
		
		//ball info
		int ball_w = 10;
		int ball_h = 10;
		m_ball_pos.x = (window_w - (2 * club_w)) + (club_w / 2) - ball_w;
		m_ball_pos.y = 450 - ball_h*2;
		m_ball_size = Vec2(ball_w, ball_h);
		m_ball_shape = Rect(m_ball_pos.x, m_ball_pos.y, ball_w, ball_h);

		int speed = 10;
		m_ball_speed = Vec2(speed, -speed);
		m_ball_isDead = false;
	}

		~Arcanoid()
	{
	}

	void initialize_object(int posx, int posy, int wide, int height, String texname);
	void initialize_brick_field();
	void update_ball();
	void Collide(Rect& ball, Rect rect2);
	void SlowSpeed();
	void Gamelosed();
	void GameWon();

	// Разворачивание движения по горизонтальной оси
	void ReflectHorizontal()
	{
		m_ball_speed.y = -m_ball_speed.y;
	}

	// Разворачивание движения по вертикальной оси
	void ReflectVertical()
	{
		m_ball_speed.x = -m_ball_speed.x;
	}
	
	void MoveClubLeft() 
	{ 
		if (m_club_pos.x == 0)
			return;

		int step_size = m_club_size.x;
		m_club_pos.x -= step_size;
	}
	void MoveClubRight()
	{
		int step_size = m_club_size.x;
		if (m_club_pos.x == window_w - step_size)
			return;

		m_club_pos.x += step_size;
	}
	
	void ChangeClub()
	{
		m_club_size.x = m_club_size.x == window_w / club_medium ? window_w / club_small : window_w / club_medium;
	}
	bool EventMain()
	{
		EventDraw();
		return true;
	}

	void EventDraw()
	{
		if (m_level < 3)
		{
			//background
			initialize_object(0, 0, 640, 480, "Space.png");

			//club
			initialize_object(m_club_pos.x, m_club_pos.y, m_club_size.x, m_club_size.y, "Club.jpg");

			//Draw bricks
			for (int i = 0; i < bricks.size(); i++)
			{
				if (bricks[i]->isDead) continue;
				initialize_object(bricks[i]->position.x, bricks[i]->position.y, bricks[i]->size.x, bricks[i]->size.y, "Brick.png");
			}

			//draw ball
			if (!m_ball_isDead)
			{
				initialize_object(m_ball_pos.x, m_ball_pos.y, m_ball_size.x, m_ball_size.y, "Ball.png");
			}

			//move ball
			update_ball();
		}
		else
			initialize_object(0, 0, 640, 480, "Winner.png");
		
		//refresh screen(только одна)
		PageFlip();
	}

	void EventKeyboard(int keycode, char charcode, bool press)
	{
		if ( keycode == KEYCODE_ESC && press )
			MainBreak();
		if (keycode == KEYCODE_A && press)
			MoveClubLeft();
		if (keycode == KEYCODE_D && press)
			MoveClubRight();
		if (keycode == KEYCODE_SPACE && press)
			ChangeClub();
		//if (keycode == KEYCODE_1 && press)
			//SlowSpeed();

	}

	private:

	Timer		timer;
	Rect		m_field_shape;

	//object_club
	Vec2		m_club_pos;
	Vec2		m_club_size;
	
	//object_ball
	Vec2		m_ball_pos;
	Vec2		m_ball_size;
	Vec2		m_ball_speed;
	Rect		m_ball_shape;
	bool		m_ball_isDead;
	vector<object_brick*> bricks;
	int			m_bricts_number;  //кол-во кирпичиков
	int			m_level;
};


// =============================================================
// prmain()
// =============================================================

int prmain(int argc, char** argv)
{
	Arcanoid window;
	window.MoveWindow(512, 234);
	window.MainLoop();
	return 0;
}


void Arcanoid::initialize_object(int posx, int posy, int wide, int height, const String texname)
{
	//shape
	Bitmap buffer = Bitmap(wide, height, PIXELFORMAT_ARGB8888);
	//texture
	Bitmap texture = Bitmap(texname, PIXELFORMAT_ARGB8888);
	//bound texture to buffer
	prcore::AlphaBlendVolatile(buffer, texture, texture);
	//position
	BlitWrite(posx, posy, buffer);
}

void Arcanoid::initialize_brick_field()
{

	//bricks_info
	Vec2 bricks_size = Vec2(40, 20);
	int indent_x = 1;
	int indent_y = 2;
	Vec2 bricks_start_position = Vec2(indent_x * bricks_size.x, indent_y * bricks_size.y);
	int max_bricks_in_row = (window_w / bricks_size.x) - (indent_x * 2); //отступаем с 2х сторон
	int max_bricks_in_collum = (window_h / bricks_size.y) - (indent_y * 2); //максимум строк будет таким


	//create brick_field
	Vec2 Pos = bricks_start_position;
	int bricks_row_count = 0;
	int bricks_collum_count = 0;


	for (int i = 0; i < m_bricts_number; i++)
	{
		if (bricks_row_count >= max_bricks_in_row)
		{
			if (bricks_collum_count >= max_bricks_in_collum)
			{
				break;
			}
			else
			{
				bricks_row_count = 0;
				bricks_collum_count++;
			}
		}
		else
		{
			bricks.push_back(new object_brick(Vec2(Pos.x + bricks_row_count*bricks_size.x, Pos.y + bricks_collum_count*bricks_size.y), bricks_size));
			bricks_row_count++;
		}
	}
}

void Arcanoid::update_ball()
{
	m_ball_pos += m_ball_speed;
	m_ball_shape = Rect(m_ball_pos.x, m_ball_pos.y, m_ball_shape.width, m_ball_shape.height);
	
	if (m_ball_shape.x <= m_field_shape.x || (m_ball_shape.x + m_ball_shape.width * 2) >= (m_field_shape.x + m_field_shape.width))  ReflectVertical();
	if (m_ball_shape.y <= m_field_shape.y )   ReflectHorizontal();
	if ((m_ball_shape.y + m_ball_shape.height) >= (m_field_shape.y + m_field_shape.height))
	{
		m_ball_isDead = true;
		Gamelosed();
	}

	//club collision
	if ((m_ball_shape.y + m_ball_shape.height) >= (m_club_pos.y) && m_ball_shape.x >= m_club_pos.x &&  m_ball_shape.x + m_ball_shape.width <= m_club_pos.x + m_club_size.x)
	{
		ReflectHorizontal();
	}
	//врядли кто то умудрится ударить ребром биты по мячу

	//brick collision
	int count_dead = 0;
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks[i]->isDead) {
			count_dead++; 
			if (bricks.size() == count_dead) GameWon();
			continue;
		}
		//if () расстояние слишком большое то continue

		Rect box = bricks[i]->rect_bounds;
		if (m_ball_shape.y <= box.y + box.height && m_ball_shape.x >= box.x && m_ball_shape.x <= box.x + box.width)
		{
			ReflectHorizontal();
			bricks[i]->isDead = true;
		}
		//логику нужно доделать, но время уже вышло так что отправляю как есть
		//if ((m_ball_shape.x <= box.x + box.width && m_ball_shape.y <= box.y + box.height) || (m_ball_shape.x >= box.x && m_ball_shape.y <= box.y + box.height))
		//{
		//	ReflectVertical();
		//	bricks[i]->isDead = true;
		//}
	}
}

void Arcanoid::Gamelosed()
{
	//brick init
	initialize_brick_field();

	//club info
	int club_w = window_w / club_medium; //128 //64
	int clib_h = 20;
	m_club_pos = Vec2(window_w - 2 * club_w, 450);
	m_club_size = Vec2(club_w, clib_h);

	//ball info
	int ball_w = 10;
	int ball_h = 10;
	m_ball_pos.x = (window_w - (2 * club_w)) + (club_w / 2) - ball_w;
	m_ball_pos.y = 450 - ball_h * 2;
	m_ball_size = Vec2(ball_w, ball_h);
	m_ball_shape = Rect(m_ball_pos.x, m_ball_pos.y, ball_w, ball_h);

	int speed = m_ball_speed.x;
	m_ball_speed = Vec2(speed, -speed);
	m_ball_isDead = false;
}
void Arcanoid::GameWon()
{

	if (m_level < 3)
	{
		m_level++; //moar level!
		//brick init
		m_bricts_number += 30; //moar bricks!
		initialize_brick_field();

		//club info
		int club_w = window_w / club_medium; //128 //64
		int clib_h = 20;
		m_club_pos = Vec2(window_w - 2 * club_w, 450);
		m_club_size = Vec2(club_w, clib_h);

		//ball info
		int ball_w = 10;
		int ball_h = 10;
		m_ball_pos.x = (window_w - (2 * club_w)) + (club_w / 2) - ball_w;
		m_ball_pos.y = 450 - ball_h * 2;
		m_ball_size = Vec2(ball_w, ball_h);
		m_ball_shape = Rect(m_ball_pos.x, m_ball_pos.y, ball_w, ball_h);

		int speed = m_ball_speed.x + 10; //moar speed!
		m_ball_speed = Vec2(speed, -speed);
	}
	else
	{
		//LastZastavka();
	}
}
//void Arcanoid::SlowSpeed()
//{
//	if (m_ball_speed.x - 10)
//	{
//		m_ball_speed.x -= 10;
//		m_ball_speed.y -= 10;
//	}
//	else
//		return;
//}