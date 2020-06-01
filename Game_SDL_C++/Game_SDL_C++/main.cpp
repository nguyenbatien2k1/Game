
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "TextObject.h"


#undef main

TTF_Font* g_font_text = NULL;


bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf", 20);
	if (g_font_text == NULL)
	{
		return false;
	}

	return true;
}


int main(int arc, char* argv[])
{
	int bkgn_x = 0;
	bool is_quit = false;
	if (Init() == false)
		return 0;

	g_bkground = SDLCommonFunc::LoadImage("bg600.png");
	if (g_bkground == NULL)
	{
		return 0;
	}

	TextObject time_game;
	time_game.SetColor(TextObject::RED_TEXT);

	// Make MainObject
	MainObject bird_object;
	bird_object.SetRect(100, 410);
	bool ret = bird_object.LoadImg("chim4.png");

	if (!ret)
	{
		return 0;
	}
	// Make ThreatObject
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];

	for (int t = 0; t < NUM_THREATS; t++)
	{
		ThreatObject* p_threat = (p_threats + t);
		if (p_threat)
		{
			ret = p_threat->LoadImg("chim3.png");
			if (ret == false)
			{
				return 0;
			}

			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEIGHT - 100)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}


			p_threat->SetRect(SCREEN_WIDTH + t * 400, rand_y);
			p_threat->set_x_val(6);
		}
	}

	unsigned int time_value = 0;

	while (!is_quit)
	{
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			bird_object.HandleInputAction(g_even);
		}
		// APPLY BACKGROUND
		bkgn_x -= 2;
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
		if (bkgn_x <= -SCREEN_WIDTH)
		{
			bkgn_x = 0;
		}

		bird_object.HandleMove();
		bird_object.Show(g_screen);

		// Run Threat
		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if (p_threat)
			{

				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);

				// Check collision main and threats
				bool is_col = SDLCommonFunc::CheckCollision(bird_object.GetRect(), p_threat->GetRect());
				if (is_col)
				{
					if (MessageBox(NULL, "GAME OVER!", "...", MB_OK) == IDOK)
					{
						delete[] p_threats;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;
					}
				}

			}

		}

		//Show mark for game
		std::string str_time = "MARK: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.SetRect(SCREEN_WIDTH / 2, 10);
		time_game.CreateGameText(g_font_text, g_screen);

		// Update screen
		if (SDL_Flip(g_screen) == -1)
			return 0;
	}
	delete[] p_threats;
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 1;

}
