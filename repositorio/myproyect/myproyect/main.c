#include <stdio.h>
#include <SDL.h>
#include "Constants.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int game_is_running = NULL;

int last_frame_time = 0;
void draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius);


struct rect
{
	float x;
	float y;
	float width;
	float height;


} rect;

struct ball
{
	int center_x;
	int center_y;
	int radius;
} ball;


int initialize_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL \n");
		return FALSE;

	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window \n");
		return FALSE;

	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		0
	);

	if (!renderer)
	{
		fprintf(stderr, "Error creating renderer \n");
		return FALSE;

	}

	return TRUE;
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		game_is_running = FALSE;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			game_is_running = FALSE;
		}
		break;

	default:
		break;
	}
}
void setup()
{
	rect.x = 20;
	rect.y = 20;
	rect.height = 15;
	rect.width = 15;

	ball.center_x = 20;
	ball.center_y = 20;
	ball.radius = 25;

}
void update()
{
	
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}

	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

	last_frame_time = SDL_GetTicks();
	rect.x += 70 * delta_time;
	rect.y += 50 * delta_time;
	
	ball.center_x += 5 + delta_time;
	ball.center_y += 2 + delta_time;
	
	
}
void render()
{
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect ball_rect = {
		(int)rect.x,
		(int)rect.y,
		(int)rect.width,
		(int)rect.height
	};

	// Dibuja el rect�ngulo
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	// Dibuja el c�rculo
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	draw_circle(renderer, ball.center_x, ball.center_y, ball.radius);

	SDL_RenderPresent(renderer);
}
void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius) {
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);  // "radius << 1" is the same as "radius * 2"

	while (x >= y) {
		SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
		SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
		SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);
		SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
		SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
		SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
		SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
		SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);

		if (err <= 0) {
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0) {
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}


int main(int argc, char* args[])
{
	
	game_is_running = initialize_window();

	setup();

	while (game_is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}
