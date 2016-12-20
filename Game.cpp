/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/20 18:23:10 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _timer(120), _score(0), _player(NULL), _enemyList(NULL){ return ; }

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

void        Game::_printEnv()
{
    wattron(_main_win, COLOR_PAIR(2));
    mvwprintw(_main_win, 1, 10, _readSkin("env/background.env").c_str());
    wattroff(_main_win, COLOR_PAIR(2));
    box(_main_win, 0, 0);
}

void        Game::_fillBackground() const
{
    int             i;
    unsigned int    size = (LINES - BOT_WIN_H) * COLS;
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

    initscr();
    if (LINES < MAIN_WIN_HMIN || COLS < MAIN_WIN_WMIN)
    {
        endwin();
        throw (Game::WindowDimensionsInvalidException());
    }
    _main_win = newwin(LINES - BOT_WIN_H, COLS, 0, 0);
    _bottom_win = newwin(BOT_WIN_H, COLS, LINES - BOT_WIN_H, 0);
	noecho();
	cbreak();
    curs_set(0);
	keypad(_main_win, TRUE);
	nodelay(_main_win, TRUE);
    start_color();
    init_color(COLOR_BLUE, 600, 800, 1000);
    init_color(COLOR_WHITE, 1000, 700, 300);
    init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_YELLOW, 220, 180, 120);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wbkgdset(_main_win, COLOR_PAIR(1));
    wbkgdset(_bottom_win, COLOR_PAIR(1));
    _fillBackground();
    playerCoord.y = LINES - (6 + BOT_WIN_H);
    playerCoord.x = (COLS / 2) - 1;
    _player = new Player(3, 4, _readSkin("env/playership.env"), NULL, playerCoord);
    //init enemy list
}

void        Game::_gameLoop()
{
    int ch;

    while ((ch = wgetch(_main_win)) != KEY_ESC)
    {
        _printEnv();
        if (ch == KEY_SPC)
            _player->shoot()->displaySkin(_main_win);
        _player->move(LINES - BOT_WIN_H, COLS, ch);
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
    mvwprintw(_bottom_win, 2, 2, "time:");
    mvwprintw(_bottom_win, 2, 8, "%i", _timer);
    mvwvline(_bottom_win, 1, 16, ACS_VLINE, 3);
    wrefresh(_bottom_win);
    werase(_bottom_win);
    //_timer--;
}

void        Game::_freeEnemyList()
{
    ;
}

Game::WindowDimensionsInvalidException::WindowDimensionsInvalidException() { return ; }

Game::WindowDimensionsInvalidException::WindowDimensionsInvalidException(WindowDimensionsInvalidException const &src) { *this = src; }

Game::WindowDimensionsInvalidException::~WindowDimensionsInvalidException() throw() { return ; }

Game::WindowDimensionsInvalidException  &Game::WindowDimensionsInvalidException::operator=(Game::WindowDimensionsInvalidException const &rhs)
{
    (void)rhs;
    return (*this);
}

char const                              *Game::WindowDimensionsInvalidException::what(void) const throw()
{
    return ("Window dimensions are invalid");
}