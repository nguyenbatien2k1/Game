
#include "ThreatsObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT * 0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject()
{

}


void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT - 100)
		{
			rand_y = SCREEN_HEIGHT * 0.3;
		}

		rect_.y = rand_y;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
	// Todo
}
