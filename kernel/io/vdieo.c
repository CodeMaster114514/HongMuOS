#include "common.h"

extern char systemFont[255][16];
extern Frame shell_frame;

Video *video_main;
extern Cursor cursor;

static RGB background;
static RGB text_color;

static RGB get_color(Pointer *at)
{
	return video_main->Frame[at->x + at->y * video_main->wight];
}

void init_vdieo(Video *video)
{
	video_main = video;
	background = (RGB){.red = 0, .green = 0, .bule = 0, .reserved = 0xff};
	text_color = (RGB){.red = 0xff, .green = 0xff, .bule = 0xff, .reserved = 0xff};
	clean_all();
}

void draw_at(Pointer *in, RGB *color)
{
	video_main->Frame[in->x + in->y * video_main->wight] = *color;
}

void draw_rectangle(Rectangle *out)
{
	for (int y = out->start.y; y < out->end.y; ++y)
	{
		for (int x = out->start.x; x < out->end.x; ++x)
		{
			draw_at(&(Pointer){.x = x, .y = y}, out->color);
		}
	}
}

void invert_color(RGB *color)
{
	RGB after = {.red = color->red ? -color->red : -1, .green = color->green ? -color->green : -1, .bule = color->bule ? -color->bule : -1, .reserved = color->reserved ? -color->reserved : -1};
	*color = after;
}

void draw_rectangle_invert_color(Pointer *start, Pointer *end)
{
	for (int x = start->x; x < end->x; ++x)
	{
		for (int y = start->y; y < end->y; ++y)
		{
			Pointer draw = {.x = x, .y = y};
			RGB color = get_color(&draw);
			invert_color(&color);
			draw_at(&draw, &color);
		}
	}
}

void draw_font(Pointer *at, char *font)
{
	char data;

	for (int i = 0; i < 16; ++i)
	{
		data = font[i];
		if (data & 0b10000000)
		{
			Pointer draw_p = {.x = at->x + 0, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 0, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b01000000)
		{
			Pointer draw_p = {.x = at->x + 1, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 1, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b00100000)
		{
			Pointer draw_p = {.x = at->x + 2, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 2, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b00010000)
		{
			Pointer draw_p = {.x = at->x + 3, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 3, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b00001000)
		{
			Pointer draw_p = {.x = at->x + 4, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 4, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b00000100)
		{
			Pointer draw_p = {.x = at->x + 5, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 5, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b00000010)
		{
			Pointer draw_p = {.x = at->x + 6, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 6, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
		if (data & 0b00000001)
		{
			Pointer draw_p = {.x = at->x + 7, .y = at->y + i};
			draw_at(&draw_p, &text_color);
		}
		else
		{
			Pointer draw_p = {.x = at->x + 7, .y = at->y + i};
			draw_at(&draw_p, &background);
		}
	}
}

void draw_char(char c)
{
	Pointer cursor_at = get_cursor_at();
	inc_cursor();
	draw_font(&cursor_at, systemFont[c]);
}

void put_char(char c)
{
	switch (c)
	{
	case '\n':
		cursor_next_line();
		break;
	case '\r':
		cursor_restart_line();
		break;
	default:
		draw_char(c);
	}
}

int put_string(const char *str)
{
	int i = 0;
	char c = str[i];
	while (c != '\0')
	{
		put_char(c);
		c = str[++i];
	}
	return i;
}

void clean_all()
{
	draw_rectangle(&(Rectangle){.color = &background, .start.x = 0, .start.y = 0, .end.x = video_main->wight, .end.y = video_main->hight});
}
