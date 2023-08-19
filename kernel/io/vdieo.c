#include "common.h"

extern char systemFont[16];
extern Frame shell_frame;

Video *video_main;
extern Cursor cursor;

static RGB get_color(Pointer *at)
{
	return video_main->Frame[at->x + at->y * video_main->wight];
}

void init_vdieo(Video *video)
{
	video_main = video;
	RGB background = {.red = 0, .green = 0, .bule = 0, .reserved = 0xff};
	//draw_rectangle(&(Rectangle){.color = &background, .start.x = 0, .start.y = 0, .end.x = video_main->wight, .end.y = video_main->hight});
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
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 0, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b01000000)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 1, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b00100000)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 2, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b00010000)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 3, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b00001000)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 4, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b00000100)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 5, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b00000010)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 6, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
		if (data & 0b00000001)
		{
			RGB color = get_color(at);
			invert_color(&color);
			Pointer draw_p = {.x = at->x + 7, .y = at->y + i};
			draw_at(&draw_p, &color);
		}
	}
}

void draw_char(char c)
{
	Pointer cursor_at = get_cursor_at();
	inc_cursor();
	draw_font(&cursor_at, systemFont + c * 16);
}

void put_char(char c)
{
	switch (c)
	{
	case '\n':
		cursor_next_line();
	case '\r':
		cursor_restart_line();
	}
	draw_char(c);
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