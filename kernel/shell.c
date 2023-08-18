#include "common.h"

extern Video *video_main;
extern Cursor cursor;

Frame shell_frame;

void init_shell()
{
	RGB color = {.red = 0xff, .green = 0xff, .bule = 0xff, .reserved = 0xff};
    shell_frame.start.x = 0;
    shell_frame.start.y = 0;
    shell_frame.end.x = video_main->wight;
    shell_frame.end.y = video_main->hight;
	cursor.line = 1;
	cursor.col = 1;
    draw_cursor();
}