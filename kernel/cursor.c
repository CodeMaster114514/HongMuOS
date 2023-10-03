#include "common.h"

extern Frame shell_frame;
Cursor cursor;

void undraw_cursor()
{
	draw_cursor();
}

void set_cursor()
{
	if (cursor.col <= 0)
	{
		cursor.col = 1;
		cursor.line -= 1;
	}
    if (cursor.col > shell_frame.end.x / 8)
	{
		cursor.col = 1;
		cursor.line += 1;
	}
	if (cursor.line > shell_frame.end.y / 16)
	{
		cursor.col = 1;
		cursor.line = 1;
	}
	draw_cursor();
}

void inc_cursor()
{
	undraw_cursor();
	cursor.col += 1;
    set_cursor();
}

Pointer get_cursor_at()
{
	return (Pointer){.x = shell_frame.start.x + (cursor.col - 1) * 8, .y = shell_frame.start.y + (cursor.line - 1) * 16};
}

Pointer get_cursor_end_at()
{
	Pointer start = get_cursor_at();
	return (Pointer){.x = start.x + 8, .y = start.y + 16};
}

void draw_cursor()
{
	Pointer start = get_cursor_at();
	Pointer end = get_cursor_end_at();
	draw_rectangle_invert_color(&start, &end);
}

void cursor_back()
{
	undraw_cursor();
	cursor.col -= 1;
	set_cursor();
}

void cursor_next_line()
{
    undraw_cursor();
    cursor.col = 1;
    cursor.line += 1;
    set_cursor();
}

void cursor_restart_line()
{
    undraw_cursor();
    cursor.col = 1;
    set_cursor();
}