#include <SDL2/SDL.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_image.h>

#define FPS 120
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#include "config.h"
#include "debugwriter.h"
#include "pipe.h"
#include "sharedstate.h"

static void showInitError(const std::string &msg)
{
	Debug() << msg;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Screen Mode", msg.c_str(), 0);
}

static void readMessage(Pipe &ipc, std::vector<std::string> *vector)
{
	char buf[256];
	int index = 0;

	while (ipc.read(buf + index))
	{
		if (buf[index] == '\n')
		{
			vector->push_back(std::string(buf, index));
			index = 0;
			continue;
		}
		index++;
	}
}

int screenMain(Config &conf)
{
	const SDL_Color black = {0x00, 0x00, 0x00, 0xFF};

	Pipe ipc("oneshot-pipe", Pipe::Read);

	int imgFlags = IMG_INIT_PNG;
	if (IMG_Init(imgFlags) != imgFlags)
	{
		showInitError(std::string("Error initializing SDL_image: ") + SDL_GetError());
		SDL_Quit();

		return 0;
	}

	SDL_Window *win;
	win = SDL_CreateShapedWindow(conf.screen_mode.name.c_str(),
						   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						   DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP);
	if (conf.screen_mode.titlebar)
		SDL_SetWindowBordered(win, SDL_TRUE);

	if (!win)
	{
		showInitError(std::string("Error creating window: ") + SDL_GetError());
		return 0;
	}

	SDL_WindowShapeMode shapeMode;
	shapeMode.mode = ShapeModeBinarizeAlpha;
	shapeMode.parameters.binarizationCutoff = 255;

	SDL_Surface *shape = SDL_CreateRGBSurface(0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 8, 0, 0, 0, 0);
	SDL_SetPaletteColors(shape->format->palette, &black, 0, 1);

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1.0, 0);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, shape);
	SDL_Rect dimensions {
		x: 0,
		y: 0,
		w: shape->w,
		h: shape->h
	};

	std::vector<std::string> messages = std::vector<std::string>();

	uint64_t ticks = SDL_GetTicks64();
	for (;;)
	{
		// Handle events
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				return 0;
			}
		}
		readMessage(ipc, &messages);
		// Change shape
		for (const std::string &str : messages)
		{
			if (str.find("MOV") != std::string::npos)
			{
				size_t delimiter = str.find(";");
				int x = stoi(str.substr(3, delimiter - 3));
				int y = stoi(str.substr(delimiter + 1, str.length()));
				SDL_SetWindowPosition(win, x, y);
				Debug() << "x" << x << "y" << y;
				continue;
			}

			if (str == "END")
				break;

			std::string imgname = conf.screen_mode.imagePath + str + ".png";
			SDL_FreeSurface(shape);
			SDL_DestroyTexture(texture);
			if ((shape = IMG_Load(imgname.c_str())) == NULL)
			{
				std::string error = "Unable to find image ";
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Screen Mode", (error + imgname).c_str(), 0);
				Debug() << error + imgname;
				break;
			}
			SDL_SetWindowSize(win, shape->w, shape->h);
			SDL_SetWindowShape(win, shape, &shapeMode);
			dimensions.w = shape->w;
			dimensions.h = shape->h;
			texture = SDL_CreateTextureFromSurface(renderer, shape);
		}
		messages.clear();

		// Redraw
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texture, &dimensions, &dimensions);

		SDL_RenderPresent(renderer);

		// Regulate framerate
		int64_t ticksDelta = SDL_GetTicks64() - ticks;
		if (ticksDelta < 1000 / FPS)
			SDL_Delay(1000 / FPS - ticksDelta);
		ticks = SDL_GetTicks64();
	}

	SDL_FreeSurface(shape);
	return 0;
}
