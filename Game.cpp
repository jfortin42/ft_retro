/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/16 19:02:22 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _main_win(NULL), _bottom_win(NULL), _timer(120), _score(0), _playerList(NULL), _enemyList(NULL), _missilePlayerList(NULL), _missileEnemyList(NULL) {}

Game::Game(Game const &src) : _main_win(NULL), _bottom_win(NULL), _timer(src._timer), _score(src._score), _playerList(NULL), _enemyList(NULL), _missilePlayerList(NULL), _missileEnemyList(NULL)
{
    //fonction pour remplir toutes les listes (DEEP COPY!)
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
        _timer = rhs._timer;
        _score = rhs._score;
        wclear(_main_win);
        wclear(_bottom_win);
        delwin(_main_win);
        delwin(_bottom_win);
        _freeEntityList(_playerList);
        _freeEntityList(_enemyList);
        _freeEntityList(_missilePlayerList);
        _freeEntityList(_missileEnemyList);
        //fonction pour remplir toutes les listes (DEEP COPY!)
    }
    return (*this);
}

void            Game::launch()
{
    _initGame();
    _gameLoop();
    _endGame();
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
    AWeapon *laser = new Laser(1, 1, 30, 0);
    _pushInList(_playerList, new Player(3, 3, 2, _readSkin("env/playership.env"), laser->clone(), playerCoord));
}

void            Game::_gameLoop()
{
    int         i;
    int         key;
    std::string bkgd;
    std::string game_over;
    AWeapon     *pioupiou = new Pioupiou(1, 1, 50, 1000);

    bkgd = _fillBackground();
    game_over = _readSkin("env/gameover.env");
    while ((key = wgetch(_main_win)) != KEY_ESC && _playerList && _timer > 0)
    {
        _refreshMainWin(bkgd);
        i = rand();
        if (i % 5000 < 1)
            _pushInList(_enemyList, new Enemy(2, 3, 500, 250, _readSkin("env/enemy.env"), pioupiou->clone(), (t_coord){i % (COLS - 10) + 1, 1}));
        if (key == KEY_SPC && _playerList)
        try { _pushInList(_missilePlayerList, _playerList->entity->shoot()); }
        catch (std::exception &e) {}
        _gameCore(key);
        wrefresh(_main_win);
        _refreshBottomWin(bkgd);
    }
    if (!_playerList || _timer == 0)
    {
        werase(_main_win);
        delete pioupiou;
        mvwprintw(_main_win, 3, (COLS - 10) / 2, "FINAL SCORE:");
        mvwprintw(_main_win, 3, ((COLS - 3) / 2) + 14, "%i", _score);        
        mvwprintw(_main_win, (LINES - BOT_WIN_H - 6) / 2, 1, game_over.c_str());
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

void            Game::_displayEntities(t_entityList *list) const
{
    t_entityList    *list_tmp = list;

    while (list_tmp)
    {
        list_tmp->entity->displaySkin(_main_win);
        list_tmp = list_tmp->next;
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

void            Game::_shootInList(t_entityList *list, t_entityList *&listOfMissile)
{
    while (list)
    {
        try { _pushInList(listOfMissile, list->entity->shoot()); }
        catch (std::exception &e) {}
        list = list->next;
    }
}

bool            Game::_hitbox(t_entityList *entity1, t_entityList *entity2) const
{
    if (entity1->entity->getCoord().x + entity1->entity->getSkinSize().x >= entity2->entity->getCoord().x
        && entity1->entity->getCoord().x <= entity2->entity->getCoord().x + entity2->entity->getSkinSize().x
        && entity1->entity->getCoord().y + entity1->entity->getSkinSize().y - 1 >= entity2->entity->getCoord().y
        && entity1->entity->getCoord().y <= entity2->entity->getCoord().y + entity2->entity->getSkinSize().y - 1)
        return (true);
    return (false);
}

void            Game::_collision(t_entityList *&list1, t_entityList *&list2)
{
    t_entityList    *tmp1 = list1;
    unsigned int    tmp1HP;
    unsigned int    tmp2HP;

    while (tmp1)
    {
        t_entityList    *tmp2 = list2;
        while (tmp1 && tmp2)
        {
            if (tmp1->next && tmp2->next && _hitbox(tmp1->next, tmp2->next))
            {
                tmp1HP = tmp1->next->entity->takeDamage(*tmp2->next->entity, _main_win);
                tmp2HP = tmp2->next->entity->takeDamage(*tmp1->next->entity, _main_win);
                if (!tmp1HP)
                {
                    _score += tmp1->entity->getScore();
                    _lstdelone(list1, tmp1, 'N');
                }
                if (!tmp2HP)
                {
                    _score += tmp2->entity->getScore();
                    _lstdelone(list2, tmp2, 'N');
                }
            }
            else if (tmp1->next && _hitbox(tmp1->next, tmp2))
            {
                tmp1HP = tmp1->next->entity->takeDamage(*tmp2->entity, _main_win);
                tmp2HP = tmp2->entity->takeDamage(*tmp1->next->entity, _main_win);
                if (!tmp1HP)
                {
                    _score += tmp1->entity->getScore();
                    _lstdelone(list1, tmp1, 'N');
                }
                if (!tmp2HP)
                {
                    _score += tmp2->entity->getScore();
                    _lstdelone(list2, tmp2, 'F');
                }
            }
            else if (tmp2->next && _hitbox(tmp1, tmp2->next))
            {
                tmp1HP = tmp1->entity->takeDamage(*tmp2->next->entity, _main_win);
                tmp2HP = tmp2->next->entity->takeDamage(*tmp1->entity, _main_win);
                if (!tmp1HP)
                {
                    _score += tmp1->entity->getScore();
                    _lstdelone(list1, tmp1, 'F');
                }
                if (!tmp2HP)
                {
                    _score += tmp2->entity->getScore();
                    _lstdelone(list2, tmp2, 'N');
                }
            }
            else if (_hitbox(tmp1, tmp2))
            {
                tmp1HP = tmp1->entity->takeDamage(*tmp2->entity, _main_win);
                tmp2HP = tmp2->entity->takeDamage(*tmp1->entity, _main_win);
                if (!tmp1HP)
                {
                    _score += tmp1->entity->getScore();
                    _lstdelone(list1, tmp1, 'F');
                }
                if (!tmp2HP)
                {
                    _score += tmp2->entity->getScore();
                    _lstdelone(list2, tmp2, 'F');
                }
            }
            tmp2 = tmp2 ? tmp2->next : list2;
        }
        tmp1 = tmp1 ? tmp1->next : list1;
    }
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

void            Game::_refreshMainWin(std::string bkgd) const
{
    wattron(_main_win, COLOR_PAIR(2));
    mvwprintw(_main_win, 1, 1, bkgd.c_str());
    wattroff(_main_win, COLOR_PAIR(2));
    box(_main_win, 0, 0);
}

void            Game::_refreshBottomWin(std::string bkgd)
{
    unsigned int i;
    int x;

    x = 26;
    if (_playerList)
        i = _playerList->entity->getHp();
    wattron(_bottom_win, COLOR_PAIR(2));
    mvwprintw(_bottom_win, 1, 1, bkgd.c_str());
    wattroff(_bottom_win, COLOR_PAIR(2));
    box(_bottom_win, 0, 0);
    mvwprintw(_bottom_win, 2, 3, "time:");
    mvwprintw(_bottom_win, 2, 19, "lives:");
    mvwprintw(_bottom_win, 2, 42, "score:");
    if (_playerList)
    {
        for (i = 0 ; i < _playerList->entity->getHp() ; i++)
        {
            mvwprintw(_bottom_win, 2, x, "<3");//single player only for now
            x += 4;
        }
    }
    mvwprintw(_bottom_win, 2, 9, "%i", _timer);
    mvwprintw(_bottom_win, 2, 50, "%i", _score);    
    mvwvline(_bottom_win, 1, 16, ACS_VLINE, 3);
    mvwvline(_bottom_win, 1, 39, ACS_VLINE, 3);
    mvwvline(_bottom_win, 1, 60, ACS_VLINE, 3); 
    if (_checkTime(1000, _last_timer))
        _timer--;
    wrefresh(_bottom_win);
    werase(_bottom_win);
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

Game::WindowDimensionsInvalidException::WindowDimensionsInvalidException() {}

Game::WindowDimensionsInvalidException::WindowDimensionsInvalidException(WindowDimensionsInvalidException const &src) { *this = src; }

Game::WindowDimensionsInvalidException::~WindowDimensionsInvalidException() throw() {}

Game::WindowDimensionsInvalidException  &Game::WindowDimensionsInvalidException::operator=(Game::WindowDimensionsInvalidException const &rhs)
{
    (void)rhs;
    return (*this);
}

char const                              *Game::WindowDimensionsInvalidException::what(void) const throw() { return ("Window dimensions are invalid"); }