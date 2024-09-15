#include <stdio.h>
#include <SDL.h>
#include "Constants.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int game_is_running = NULL;

int last_frame_time = 0;
void draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius);

int velx = VELOCIDADX;
int vely = VELOCIDADY;
r = 0;
g = 100;
b = 200;




struct rect
{
	float x;
	float y;
	float width;
	float height;
	int velx;
	int vely;


} rect;
struct rect2
{
	float x;
	float y;
	float width;
	float height;
	int velx;
	int vely;


} rect2;

struct ball
{
	float center_x;
	float center_y;
	int radius;
	int velx;
	int vely;
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
	rect.velx = VELOCIDADX;
	rect.vely = VELOCIDADY;

	rect2.x = 400;
	rect2.y = 20;
	rect2.height = 15;
	rect2.width = 15;
	rect2.velx = VELOCIDADX;
	rect2.vely = VELOCIDADY;

	ball.center_x = 20;
	ball.center_y = 20;
	ball.radius = 25;
	ball.velx = VELOCIDADX;
	ball.vely = VELOCIDADY;

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
	rect.x += rect.velx * delta_time;
	rect.y += rect.vely * delta_time;
	//rect.width += 1;
	//rect.height += 1;
	rect2.x += rect2.velx * delta_time;
	rect2.y += rect2.vely * delta_time;
	
	ball.center_x += ball.velx + delta_time;
	ball.center_y += ball.vely + delta_time;


	//colision con las paredes
	if (rect.x >= WINDOW_WIDTH)
	{
		rect.velx = -rect.velx;
	}
	if (rect.y >= WINDOW_HEIGHT)
	{
		rect.vely = -rect.vely;
	}
	if (rect.x < 0)
	{
		rect.velx = VELOCIDADX;
	}
	if (rect.y < 0)
	{
		rect.vely = VELOCIDADY;
		
	}
	if (rect2.x >= WINDOW_WIDTH)
	{
		rect2.velx = -rect2.velx;
	}
	if (rect2.y >= WINDOW_HEIGHT)
	{
		rect2.vely = -rect2.vely;
	}
	if (rect2.x < 0)
	{
		rect2.velx = VELOCIDADX;
	}
	if (rect2.y < 0)
	{
		rect2.vely = VELOCIDADY;

	}
	if (ball.center_x >= WINDOW_WIDTH)
	{
		ball.velx = -ball.velx;
	}
	if (ball.center_y >= WINDOW_HEIGHT)
	{
		ball.vely = -ball.vely;
	}
	if (ball.center_x < 0)
	{
		ball.velx = VELOCIDADX;
	}
	if (ball.center_y < 0)
	{
		ball.vely = VELOCIDADY;

	}
	//ciclo de colores
	r++;
	g++;
	b++;
	//colisiones entre figurar
	if (rect.x == ball.center_x || rect.x == rect2.x)
	{
		rect.velx = -rect.velx;
		rect2.velx = -rect2.velx;
		ball.velx = -ball.velx;

	}
	if (rect.y == ball.center_y || rect.y == rect2.y)
	{
		rect.vely = -rect.vely;
		rect2.vely = -rect2.vely;
		ball.vely = -ball.vely;
	}
	
	//cambiar orientacion
	
	
	
	
	
	
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
	SDL_Rect ball_rect2 = {
		(int)rect2.x,
		(int)rect2.y,
		(int)rect2.width,
		(int)rect2.height
	};

	// Dibuja el rectángulo
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderFillRect(renderer, &ball_rect2);

	// Dibuja el círculo
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
