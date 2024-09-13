#include <stdio.h>
#include <SDL.h>
#include "Constants.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int game_is_running = NULL;

int last_frame_time = 0;

int velx = VELOCIDADX;
int vely = VELOCIDADY;
r = 0;
g = 100;
b = 200;
int is_jumping = 0;  // 0 si no está saltando, 1 si está saltando
int jump_speed = -15; // Velocidad inicial del salto (negativa para saltar hacia arriba)
int gravity = 30;     // Aceleración que simula la gravedad





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

	struct rect3
	{
		float x;
		float y;
		float width;
		float height;
		int velx;
		int vely;

	}rect3;


} rect2;




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
		else if (event.key.keysym.sym == SDLK_w)
		{
			if (!is_jumping) // Solo permite saltar si no está ya en el aire
			{
				is_jumping = 1;
				rect.vely = jump_speed; // Inicializa la velocidad vertical para el salto
			}
			printf("Personaje saltando\n");
		}
		break;
	

	default:
		break;
	}
}
void setup()
{
	rect.x = 20;
	rect.y = 250;
	rect.height = 30;
	rect.width = 30;
	rect.velx = 0;
	rect.vely = 30;

	rect2.x = 0;
	rect2.y = 300;
	rect2.height = 300;
	rect2.width = WINDOW_WIDTH*2;
	rect2.velx = -VELOCIDADX;

	rect2.rect3.x = 400;
	rect2.rect3.y = rect2.y;
	rect2.rect3.height = 300;
	rect2.rect3.width = 40;
	rect2.rect3.velx = -VELOCIDADX;
	


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

	if (is_jumping)
	{
		rect.vely += gravity * delta_time;
	}

	float second_half_x = rect2.x + rect2.width / 2;
	rect2.rect3.x = second_half_x + (rect2.width / 4) - rect2.rect3.width / 2;  // Centrado en la mitad de la segunda mitad
	rect2.rect3.y = rect2.y;


	//colision con las paredes
	/*if (rect.x >= WINDOW_WIDTH)
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
		
	}*/
	
	if (rect2.y >= WINDOW_HEIGHT)
	{
		rect2.vely = -rect2.vely;
	}
	if (rect2.x < -800)
	{
		rect2.x = 0;
	}
	if (rect2.y < 0)
	{
		rect2.vely = VELOCIDADY;

	}

	
	//ciclo de colores
	r++;
	g++;
	b++;
	//colisiones entre figurar
	if (rect.y == 300)
	{
		rect.vely = 0;
	}
	// Verificar colisión entre el cuadrado (rect) y el suelo (rect2)
	if (rect.y + rect.height >= rect2.y &&       // El borde inferior del cuadrado toca el borde superior del suelo
		rect.x + rect.width >= rect2.x &&        // El borde derecho del cuadrado está dentro del suelo
		rect.x <= rect2.x + rect2.width) {       // El borde izquierdo del cuadrado está dentro del suelo
		rect.y = rect2.y - rect.height;          // Ajusta la posición del cuadrado para que no atraviese el suelo
		rect.vely = 0;                           // Detiene el movimiento vertical (caída) del cuadrado
	}
		
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
	SDL_Rect ball_rect3 = {
		(int)rect2.rect3.x,
		(int)rect2.rect3.y,
		(int)rect2.rect3.width,
		(int)rect2.rect3.height
	};

	// Dibuja el rectángulo
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderFillRect(renderer, &ball_rect2);

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &ball_rect3);


	SDL_RenderPresent(renderer);
}
void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
