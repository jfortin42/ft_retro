/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/19 20:18:10 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _timer(120), _score(0), _player(NULL), _enemyList(NULL)
{
    initscr();
    getmaxyx(stdscr, _stdscrHeight, _stdscrWidth);
    if (_stdscrHeight < MAIN_WIN_HMIN || _stdscrWidth < MAIN_WIN_WMIN)
        ;//throw (Game::WindowDimensionsInvalidException());
    _main_win = newwin(_stdscrHeight - BOT_WIN_H, _stdscrWidth, 0, 0);
    _bottom_win = newwin(BOT_WIN_H, _stdscrWidth, _stdscrHeight - BOT_WIN_H, 0);
}

Game::Game(Game const &src)
{
    this->_enemyList = NULL;
    //fonction pour remplir this->_enemyList (DEEP COPY!)
    //this->_player = new Player(*(src._player));
    //this->_main_win = new WINDOW(src._main_win);//a verifier
    //this->_bottom_win = new WINDOW(src._bottom_win);//a verifier
    this->_timer = src._timer;
    this->_score = src._score;
}

Game::~Game()
{
    delete _player;
    _freeEnemyList();
}

Game        &Game::operator=(Game const &rhs)
{
    if (this != &rhs)
    {
        wclear(this->_main_win);
        wclear(this->_bottom_win);
        delwin(this->_main_win);
        delwin(this->_bottom_win);
        _freeEnemyList();
        //fonction pour remplir this->_enemyList (DEEP COPY!)
        delete this->_player;
        //this->_player = new Player(*(rhs._player));
        //this->_main_win = new WINDOW(rhs._main_win);//a verifier
        //this->_bottom_win = new WINDOW(rhs._bottom_win);//a verifier
        this->_timer = rhs._timer;
        this->_score = rhs._score;
    }
    return (*this);
}

void        Game::launch()
{
    _initGame();
    _gameLoop();
    _endGame();
}

void        Game::_fillBackground(unsigned int height, unsigned int width) const
{
    int             i;
    unsigned int    size = height * width;
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

std::string Game::_readSkin(std::string nameOfFile) const
{
    std::ifstream       file(nameOfFile);
    std::stringstream   read;

    read << file.rdbuf();
    file.close();
    return (read.str());
}

void        Game::_initGame()
{
    t_coord playerCoord;

	noecho();
	cbreak();
	keypad(_main_win, TRUE);
	nodelay(_main_win, TRUE);
    start_color();
    init_color(COLOR_BLUE, 600, 800, 1000);
    init_color(COLOR_WHITE, 1000, 700, 300);
    init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_YELLOW, 220, 180, 120);
	//init_color(COLOR_YELLOW, 150, 200, 250);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	//init_pair(1, COLOR_BLUE, COLOR_BLACK);    
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wbkgdset(_main_win, COLOR_PAIR(1));
    wbkgdset(_bottom_win, COLOR_PAIR(1));
    _fillBackground(_stdscrHeight - BOT_WIN_H, _stdscrWidth);
    playerCoord.y = _stdscrHeight - (6 + BOT_WIN_H);
    playerCoord.x = (_stdscrWidth / 2) - 1;
    _player = new Player(3, 4, _readSkin("env/playership.env"), NULL, playerCoord);
    //init enemy list
}

void        Game::_gameLoop()
{
    int ch;

    while ((ch = wgetch(_main_win)) != KEY_ESC)// && _timer > 0)
    {
        //print_env (start)
        wattron(_main_win, COLOR_PAIR(2));
        mvwprintw(_main_win, 1, 10, _readSkin("env/background.env").c_str());
        wattroff(_main_win, COLOR_PAIR(2));
        box(_main_win, 0, 0);
        mvwprintw(_main_win, 1, 1, "time:");
        mvwprintw(_main_win, 1, 10, "|");
        mvwprintw(_main_win, 2, 1, "---------");
        wmove(_main_win, 2, 10);
        waddch(_main_win, ACS_LRCORNER);
        //print_env (end)
        _player->move(_stdscrHeight - BOT_WIN_H, _stdscrWidth, ch);
        _player->displaySkin(_main_win);
        wrefresh(_main_win);
        _refreshBottomWin();
        usleep(10000);
    }
}

void        Game::_endGame()
{
    wclear(_main_win);
    wclear(_bottom_win);
    delwin(_main_win);
    delwin(_bottom_win);
    endwin();
}

void        Game::_refreshBottomWin()
{
    wattron(_bottom_win, COLOR_PAIR(2));
    mvwprintw(_bottom_win, 1, 1, _readSkin("env/background.env").c_str());
    wattroff(_bottom_win, COLOR_PAIR(2));
    box(_bottom_win, 0, 0);
    wrefresh(_bottom_win);
}

void        Game::_freeEnemyList()
{
    ;
}