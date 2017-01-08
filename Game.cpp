/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/08 17:20:05 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _main_win(NULL), _bottom_win(NULL), _timer(120), _score(0),
_playerList(NULL), _enemyList(NULL), _missilePlayerList(NULL), _missileEnemyList(NULL)
{}

Game::Game(Game const &src) : _main_win(NULL), _bottom_win(NULL),
_timer(src._timer), _score(src._score), _enemyList(NULL), _missilePlayerList(NULL), _missileEnemyList(NULL)
{
    //fonction pour remplir this->_enemyList (DEEP COPY!)    
    //fonction pour remplir this->_missileList (DEEP COPY!)
    //this->_player = new Player(*(src._player));
    //this->_main_win = new WINDOW(src._main_win);//a verifier
    //this->_bottom_win = new WINDOW(src._bottom_win);//a verifier
}

Game::~Game()
{
    
    _freeEntityList(_playerList);
    _freeEntityList(_enemyList);
    _freeEntityList(_missilePlayerList);
    _freeEntityList(_missileEnemyList);
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
        _freeEntityList(_missilePlayerList);
        _freeEntityList(_missileEnemyList);
        //fonction pour remplir this->_enemyList (DEEP COPY!)
        //fonction pour remplir this->_entityList (DEEP COPY!)
        _freeEntityList(_playerList);
        //this->_player = new Player(*(rhs._player));
        //this->_main_win = new WINDOW(rhs._main_win);//a verifier
        //this->_bottom_win = new WINDOW(rhs._bottom_win);//a verifier
        this->_timer = rhs._timer;
        this->_score = rhs._score;
    }
    return (*this);
}

void            Game::_displayEntities(t_entityList *list) const
{
    t_entityList    *list_tmp = list;

    while (list_tmp)
    {
        list_tmp->entity->displaySkin(_main_win);
        list_tmp = list_tmp->next;
    }
}

void            Game::_lstdelone(t_entityList *&begin, t_entityList *&current, char command)
{
    t_entityList    *tmp_next = NULL;

    if (current == begin && command == 'F')
    {
        begin = current->next;
        delete current->entity;
        delete current;
        current = NULL;
    }
    else if (current->next)
    {
        tmp_next = current->next->next;
        delete current->next->entity;
        delete current->next;
        current->next = tmp_next;
    }
}

void            Game::_moveInList(t_entityList *&begin, int key)
{
    t_entityList    *entity_tmp = begin;

    while (entity_tmp)
    {
        if (entity_tmp == begin && entity_tmp->entity->move(LINES - BOT_WIN_H, COLS, key) == false)
            _lstdelone(begin, entity_tmp, 'F');
        else if (entity_tmp->next && entity_tmp->next->entity->move(LINES - BOT_WIN_H, COLS, key) == false)
            _lstdelone(begin, entity_tmp, 'N');
        entity_tmp = entity_tmp ? entity_tmp->next : begin;
    }
}

bool            Game::_hitbox(t_entityList *entity1, t_entityList *entity2)
{
    if (entity1->entity->getCoord().x + entity1->entity->getSizeSkin().x >= entity2->entity->getCoord().x
        && entity1->entity->getCoord().x <= entity2->entity->getCoord().x + entity2->entity->getSizeSkin().x
        && entity1->entity->getCoord().y + entity1->entity->getSizeSkin().y - 1 >= entity2->entity->getCoord().y
        && entity1->entity->getCoord().y <= entity2->entity->getCoord().y + entity2->entity->getSizeSkin().y - 1)
        return (true);
    return (false);
}

void            Game::_collision(t_entityList *&list1, t_entityList *&list2)
{
    t_entityList    *tmp1 = list1;

    while (tmp1)
    {
        t_entityList    *tmp2 = list2;
        while (tmp1 && tmp2)
        {
                if (tmp1->next && tmp2->next && _hitbox(tmp1->next, tmp2->next))
            {
                _lstdelone(list1, tmp1, 'N');
                _lstdelone(list2, tmp2, 'N');
            }
                else if (tmp1->next && _hitbox(tmp1->next, tmp2))
            {
                _lstdelone(list1, tmp1, 'N');
                _lstdelone(list2, tmp2, 'F');
            }
                else if (tmp2->next && _hitbox(tmp1, tmp2->next))
            {
                _lstdelone(list1, tmp1, 'F');
                _lstdelone(list2, tmp2, 'N');
            }
                else if (_hitbox(tmp1, tmp2))
            {
                _lstdelone(list1, tmp1, 'F');
                _lstdelone(list2, tmp2, 'F');
            }
            tmp2 = tmp2 ? tmp2->next : list2;
        }
        tmp1 = tmp1 ? tmp1->next : list1;
    }
}

void            Game::_shootInList(t_entityList *list, t_entityList *&listOfMissile)
{
    while (list)
    {
        try
        {
            _pushInList(listOfMissile, list->entity->shoot());
        }
        catch (std::exception &e) {}
        list = list->next;
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
    mvwprintw(_main_win, 1, 1, bkgd.c_str());
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
    if (_checkTime(1000, _last_timer))
        _timer--;
    wrefresh(_bottom_win);
    werase(_bottom_win);
}

bool            Game::_checkTime(unsigned int msecond, clock_t  &last)
{
    clock_t        now;

    if (((now = clock()) * 1000 - last * 1000) / CLOCKS_PER_SEC >= msecond)
    {
        last = now;
        return (true);
    }
    return (false);
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

void            Game::_gameCore(int key)
{
    _displayEntities(_playerList);
    _displayEntities(_enemyList);
    _displayEntities(_missilePlayerList);
    _displayEntities(_missileEnemyList);
    _moveInList(_playerList, key);
    if (_checkTime(1, _last_loop))
    {
        _moveInList(_missilePlayerList, key);
        _moveInList(_missileEnemyList, key);
        _moveInList(_enemyList, key);
        _collision(_missilePlayerList, _enemyList);
        _collision(_playerList, _enemyList);
        _collision(_playerList, _missileEnemyList);
        _shootInList(_enemyList, _missileEnemyList);
    }
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
    set_escdelay(0);
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
    // AWeapon *pioupiou = new Pioupiou();
    AWeapon *laser = new Laser(1, 30, 0);
    _pushInList(_playerList, new Player(3, 2, _readSkin("env/playership.env"), laser, playerCoord));
    //init enemy list
}

void            Game::_gameLoop()
{
    int         i;
    int         key;
    std::string bkgd;
    std::string game_over;
    AWeapon *pioupiou = new Pioupiou(1, 50, 1000);

    bkgd = _fillBackground();
    game_over = _readSkin("env/gameover2.env");
    while ((key = wgetch(_main_win)) != KEY_ESC && _playerList && _timer > 0)
    {
        _refreshMainWin(bkgd);
        i = rand();
        if (i % 5000 < 1)
            _pushInList(_enemyList, new Enemy(1, 500, _readSkin("env/enemy.env"), pioupiou, (t_coord){i % (COLS - 10) + 1, 1}));
        if (key == KEY_SPC && _playerList)
        try
        {
            _pushInList(_missilePlayerList, _playerList->entity->shoot());
        }
        catch (std::exception &e) {}
        _gameCore(key);
        //fonction pour tout DISPLAY (player, enemy, missile);
        //fonction pour tout les moves(envoyer ch) qui detecte aussi les collisions;
        //fonction pour tous les tirs;
        wrefresh(_main_win);
        _refreshBottomWin(bkgd);
    }
    if (!_playerList)
    {
        werase(_main_win);
        mvwprintw(_main_win, (LINES - BOT_WIN_H - 8) / 2, 1, game_over.c_str());
        wrefresh(_main_win);
        usleep(2000000);
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

void            Game::_pushInList(t_entityList *&list, AEntity *entity)
{
    t_entityList    *tmp = list;
    t_entityList    *newEntity = new t_entityList();

    newEntity->entity = entity;
    newEntity->next = NULL;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp ? tmp->next = newEntity : list = newEntity;
}

void            Game::_freeEntityList(t_entityList *&list)
{
    t_entityList    *tmp;

    while (list)
    {
        tmp = list->next;
        delete list->entity;
        delete list;
        list = tmp;
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