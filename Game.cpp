/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/20 20:25:44 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _main_win(NULL), _bottom_win(NULL), _timer(120), _score(0),
_player(NULL), _enemyList(NULL), _missileList(NULL) { return ; }

Game::Game(Game const &src) : _main_win(NULL), _bottom_win(NULL),
_timer(src._timer), _score(src._score), _enemyList(NULL), _missileList(NULL)
{
    //fonction pour remplir this->_enemyList (DEEP COPY!)    
    //fonction pour remplir this->_missileList (DEEP COPY!)
    //this->_player = new Player(*(src._player));
    //this->_main_win = new WINDOW(src._main_win);//a verifier
    //this->_bottom_win = new WINDOW(src._bottom_win);//a verifier
}

Game::~Game()
{
    delete _player;
    _freeEntityList(_enemyList);
    _freeEntityList(_missileList);
}

Game            &Game::operator=(Game const &rhs)
{
    if (this != &rhs)
    {
        wclear(this->_main_win);
        wclear(this->_bottom_win);
        delwin(this->_main_win);
        delwin(this->_bottom_win);
        _freeEntityList(_enemyList);
        _freeEntityList(_missileList);
        //fonction pour remplir this->_enemyList (DEEP COPY!)
        //fonction pour remplir this->_entityList (DEEP COPY!)
        delete this->_player;
        //this->_player = new Player(*(rhs._player));
        //this->_main_win = new WINDOW(rhs._main_win);//a verifier
        //this->_bottom_win = new WINDOW(rhs._bottom_win);//a verifier
        this->_timer = rhs._timer;
        this->_score = rhs._score;
    }
    return (*this);
}

void            Game::_displayEntities() const
{
    t_entityList    *enemy_tmp = _enemyList;
    t_entityList    *missile_tmp = _missileList;

    _player->displaySkin(_main_win);
    while (missile_tmp)
    {
        missile_tmp->entity->displaySkin(_main_win);
        missile_tmp = missile_tmp->next;
    }
    while (enemy_tmp)
    {
        enemy_tmp->entity->displaySkin(_main_win);
        enemy_tmp = enemy_tmp->next;
    }
}

void            Game::_moveEntities(int key) const
{
    //t_entityList    *missile_tmp_next;// = new t_entityList();
    t_entityList    *enemy_tmp = _enemyList;
    t_entityList    *missile_tmp = _missileList;

    _player->move(LINES - BOT_WIN_H, COLS, key);
    while (missile_tmp)
    {
        if (missile_tmp->entity->move(LINES - BOT_WIN_H, COLS, key) == false)
        {
            //fix this part
            ;/*missile_tmp_next = missile_tmp->next;
            delete missile_tmp->entity;
            delete missile_tmp;
            missile_tmp = NULL;
            missile_tmp = missile_tmp_next;*/
            //fix this part
        }
        missile_tmp = missile_tmp->next;
    }
    while (enemy_tmp)
    {
        if (enemy_tmp->entity->move(LINES - BOT_WIN_H, COLS, key) == false)
            ;
        enemy_tmp = enemy_tmp->next;
    }
}

void            Game::launch()
{
    _initGame();
    _gameLoop();
    _endGame();
}

void            Game::_refreshMainWin(std::string bkgd)
{
    wattron(_main_win, COLOR_PAIR(2));
    mvwprintw(_main_win, 1, 10, bkgd.c_str());
    wattroff(_main_win, COLOR_PAIR(2));
    box(_main_win, 0, 0);
}

void            Game::_refreshBottomWin(std::string bkgd)
{
    wattron(_bottom_win, COLOR_PAIR(2));
    mvwprintw(_bottom_win, 1, 1, bkgd.c_str());
    wattroff(_bottom_win, COLOR_PAIR(2));
    box(_bottom_win, 0, 0);
    mvwprintw(_bottom_win, 2, 2, "time:");
    mvwprintw(_bottom_win, 2, 8, "%i", _timer);
    mvwvline(_bottom_win, 1, 16, ACS_VLINE, 3);
    wrefresh(_bottom_win);
    werase(_bottom_win);
    //_timer--;
}

std::string     Game::_fillBackground() const
{
    int                 i;
    unsigned int        size = (LINES - BOT_WIN_H) * COLS;
    std::stringstream   bkgd;
    
    while (size--)
    {
        i = rand() % 100;
        if (i < 2)
            bkgd << '+';
        else if (i > 98)
            bkgd << '.';
        else
            bkgd << ' ';
    }
    return (bkgd.str());
}

std::string     Game::_readSkin(std::string nameOfFile) const
{
    std::ifstream       file(nameOfFile);
    std::stringstream   read;

    read << file.rdbuf();
    file.close();
    return (read.str());
}

void            Game::_initGame()
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
    playerCoord.y = LINES - (6 + BOT_WIN_H);
    playerCoord.x = (COLS / 2) - 1;
    _player = new Player(3, 4, _readSkin("env/playership.env"), NULL, playerCoord);
    //init enemy list
}

void            Game::_gameLoop()
{
    int key;
    std::string bkgd;

    bkgd = _fillBackground();
    while ((key = wgetch(_main_win)) != KEY_ESC)
    {
        _refreshMainWin(bkgd);
        if (key == KEY_SPC)
            _missileList = _pushInList(_missileList, _player->shoot());
        _displayEntities();
        _moveEntities(key);
        //fonction pour tout DISPLAY (player, enemy, missile);
        //fonction pour tout les moves(envoyer ch) qui detecte aussi les collisions;
        //fonction pour tous les tirs;
        wrefresh(_main_win);
        _refreshBottomWin(bkgd);
        usleep(10000);
    }
}

void            Game::_endGame()
{
    wclear(_main_win);
    wclear(_bottom_win);
    delwin(_main_win);
    delwin(_bottom_win);
    endwin();
}

//copy creation and operator= must send a clone of entity to Game::_pushInList (cf. d04/ex02/Squad.cpp)

t_entityList    *Game::_pushInList(t_entityList *list, AEntity *entity)
{
    t_entityList    *tmp = list;
    t_entityList    *newEntity = new t_entityList();

    newEntity->entity = entity;
    newEntity->next = NULL;
    if (!list)
    {
        list = newEntity;
        return (list);
    }
    while (list->next)
        list = list->next;
    list->next = newEntity;
    return (tmp);
}

void            Game::_freeEntityList(t_entityList *list)
{
    t_entityList    *first;
    t_entityList    *tmp;

    first = list;
    while (first != NULL)
    {
        tmp = first->next;
        delete first->entity;
        delete first;
        first = tmp;
    }
    list = NULL;
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