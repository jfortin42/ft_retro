/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 14:35:38 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/15 16:45:26 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <time.h>

#include "AEntity.hpp"
#include "AWeapon.hpp"
#include "Player.hpp"

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

std::string     read_skin(std:: string nameOfFile)
{
    std::ifstream       file(nameOfFile);
    std::stringstream   read;

    read << file.rdbuf();
    file.close();
    return (read.str());
}

void    print_env(std::string bkgd)
{
    wattron(stdscr, COLOR_PAIR(2));
    //mvwaddstr(stdscr, 1, 10, bkgd.c_str());
    mvwprintw(stdscr, 1, 10, bkgd.c_str());
    wattroff(stdscr, COLOR_PAIR(2));
    box(stdscr, 0, 0);
    mvwprintw(stdscr, 1, 1, "time:");
	mvwprintw(stdscr, 1, 10, "|");
	mvwprintw(stdscr, 2, 1, "---------");
	wmove(stdscr, 2, 10);
	waddch(stdscr, ACS_LRCORNER);
    wrefresh(stdscr);
}

/*void    spawn_bonus(int height, int width)
{
    t_coord coord;
    int     i;
    int     j;

    j = rand() % (height - (height / 2) + 1) + (height / 2);//height et width - 1 pour eviter la box
    i = rand() % (width) + 1;
    coord.y = j;
    coord.x = i;
    i = rand() % 100; 
    if (i < 6)
        Bonus   *bonus = new Bonus(coord, "B", 15, NULL);
    while (timer)
}*/

void    init_display(int timer, int height, int width)
{
    t_coord coord;
    int     ch;

    srand(time(NULL));
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
    start_color();
    init_color(COLOR_BLUE, 600, 800, 1000);
    init_color(COLOR_WHITE, 1000, 700, 300);
    init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_YELLOW, 220, 160, 110);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    bkgdset(COLOR_PAIR(1));
    getmaxyx(stdscr, height, width);
    fill_background(height, width);
    print_env(read_skin("env/background.env"));//vvvv
    coord.y = height - 6;
    coord.x = (width / 2) - 1;
    AEntity *player = new Player(3, 4, read_skin("env/playership.env"), NULL, coord);
    player->displaySkin();//vv
    while ((ch = wgetch(stdscr)) != 27 && timer > 0)
	{
        print_env(read_skin("env/background.env"));
        player->move(ch);
        player->displaySkin();
        //spawn_bonus(height, width);
        mvwprintw(stdscr, 1, 7, "%i", timer);
        wrefresh(stdscr);
        //werase(stdscr);
        //timer--;
        //sleep(1);
	}
}

int main()
{
    init_display(120, 0, 0);
    wclear(stdscr);
	//wrefresh(stdscr);
	endwin();
	return 0;
}