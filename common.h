#ifndef COMMON_H
#define COMMON_H

typedef struct
{
	int x;
	int y;
} Pointer;

typedef struct
{
	Pointer start;
	Pointer end;
} Frame;

typedef struct
{
	char bule;
	char green;
	char red;
	char reserved;
} RGB;

typedef struct
{
	Pointer start;
	Pointer end;
	RGB *color;
} Rectangle;

typedef struct
{
	RGB *Frame;
	unsigned long long FrameBufferSize;
	unsigned int hight;
	unsigned int wight;
} Video;

typedef struct
{
	int line;
	int col;
} Cursor;

typedef struct
{
	Video vdieo;

} Table;

void undraw_cursor();
void inc_cursor();
Pointer get_cursor_at();
Pointer get_cursor_end_at();
void draw_cursor();
void init_vdieo(Video *video);
void draw_at(Pointer *in, RGB *color);
void draw_rectangle(Rectangle *out);
void invert_color(RGB *color);
void draw_rectangle_invert_color(Pointer *start, Pointer *end);
void draw_font(Pointer *at, char *font);
void draw_char(char c);
void put_char(char c);
int put_string(const char *str);

void init_shell();

char *number_to_string(int num);

void cursor_next_line();
void cursor_restart_line();

int print(const char *str, ...);
#endif