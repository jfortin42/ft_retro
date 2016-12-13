/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 14:35:38 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/13 15:16:46 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <time.h>

#define HEIGHT height
#define WIDTH width

void    fill_background(int height, int width)
{
    int             i;
    int             size = height * width;
    std::ofstream   file("env/background.env");
    
    while (size--)
    {
        i = rand() % 100;
        if (i < 2)
            file << '+';
        else if (i > 98)
            file << '.';
        else
            file << ' ';
    }
    file.close();
}

std::string     read_background()
{
    std::ifstream       file("env/background.env");
    std::stringstream   read;

    read << file.rdbuf();
    file.close();
    return (read.str());
}

void    print_env(std::string bkgd)
{
    wattron(stdscr, COLOR_PAIR(2));
    mvwaddstr(stdscr, 1, 10, bkgd.c_str());
    wattroff(stdscr, COLOR_PAIR(2));
    box(stdscr, 0, 0);
    mvwprintw(stdscr, 1, 1, "time:");
	mvwprintw(stdscr, 1, 10, "|");
	mvwprintw(stdscr, 2, 1, "---------");
	wmove(stdscr, 2, 10);
	waddch(stdscr, ACS_LRCORNER);
    wrefresh(stdscr);
}

void    init_display(int timer, int height, int width)
{
    srand(time(NULL));
	initscr();
	noecho();
	cbreak(); /* Line buffering disabled. pass on everything */
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
    start_color();
    init_color(COLOR_WHITE, 1000, 700, 300);
    init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_YELLOW, 220, 160, 110);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    bkgdset(COLOR_PAIR(1));
    getmaxyx(stdscr, height, width);
    fill_background(height, width);
    print_env(read_background());
	while (wgetch(stdscr) != 27 && timer > 0)
	{
        print_env(read_background());
        mvwprintw(stdscr, 1, 7, "%i", timer);
        wrefresh(stdscr);
        werase(stdscr);
        timer--;
        sleep(1);
	}
}

int main()
{
    init_display(120, 0, 0);
    wclear(stdscr);
	wrefresh(stdscr);
	endwin();
	return 0;
}