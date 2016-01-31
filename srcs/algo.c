#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "game_2048.h"

int			init_colors()
{
	start_color();
	init_color(COLOR_YELLOW, 200, 200, 1000);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	return (0);
}



WINDOW		*init_ncurses()
{
	WINDOW		*game_win;
	
	initscr();
	init_colors();
	cbreak();
	refresh();
	curs_set(FALSE);
	mouseinterval(FALSE);
	game_win = newwin(0, 0, 0, 0);
	wbkgd(game_win, COLOR_PAIR(1));
	keypad(game_win, TRUE);
	noecho();
	return (game_win);
}

int			display_values(WINDOW *game_win, int *tbl, int len)
{
	int			i;
	int			max_y;
	int			max_x;
	int			write_y;
	int			write_x;

	i = 0;
	getmaxyx(game_win, max_y, max_x);
	write_y = ((max_y / len) / 2);	
	while (i < (len * len))
	{
		if (i && i % len == 0)
			write_y += (max_y / len);
		write_x = (max_x / len) / 2 + ((max_x / len) * (i % len));	
		wmove(game_win, write_y, write_x);
		if (tbl[i] != 0)
			wprintw(game_win, "%d", tbl[i]);
		i++;
	}
	return (0);
}

int			main()
{
	WINDOW		*game_win;
	int		*tbl;
	int		win;
	int		len;

	srand(time(NULL));
	game_win = init_ncurses();
	len = 4;
	win = 0;
	tbl = (int *)malloc(sizeof(int) * (len * len));
	init_tbl(&tbl, len);
	while (TRUE)
	{
		resize(game_win, len);
		display_values(game_win, tbl, len);
		if (winorlose(game_win, tbl, len, &win))
			break ;
		if (get_keys(game_win, &tbl, len))
			break ;
		wrefresh(game_win);
	}
	delwin (game_win);
	endwin();
	free(tbl);
	return (0);
}
