/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2018/02/11 22:30:38 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _mainWin(NULL), _bottomWin(NULL), _timer(120), _score(0), _playerList(NULL), _enemyList(NULL), _bossList(NULL), _missilePlayerList(NULL), _missileEnemyList(NULL), _missileBossList(NULL), _bonusList(NULL), _lastTimer(clock()) {}

Game::Game(Game const &src) : _mainWin(NULL), _bottomWin(NULL), _timer(src._timer), _score(src._score), _playerList(NULL), _enemyList(NULL)
{
	_copyEntityList(_playerList, src._playerList);
	_copyEntityList(_enemyList, src._enemyList);
	_copyEntityList(_bossList, src._bossList);
	_copyEntityList(_missilePlayerList, src._missilePlayerList);
	_copyEntityList(_missileEnemyList, src._missileEnemyList);
	_copyEntityList(_missileBossList, src._missileBossList);
	_copyEntityList(_bonusList, src._bonusList);
}

Game::~Game()
{
	_freeEntityList(_playerList);
	_freeEntityList(_enemyList);
	_freeEntityList(_bossList);
	_freeEntityList(_missilePlayerList);
	_freeEntityList(_missileEnemyList);
	_freeEntityList(_missileBossList);
	_freeEntityList(_bonusList);
}

Game            &Game::operator=(Game const &rhs)
{
	if (this != &rhs)
	{
		_timer = rhs._timer;
		_score = rhs._score;
		wclear(_mainWin);
		wclear(_bottomWin);
		delwin(_mainWin);
		delwin(_bottomWin);
		_freeEntityList(_playerList);
		_freeEntityList(_enemyList);
		_freeEntityList(_bossList);
		_freeEntityList(_missilePlayerList);
		_freeEntityList(_missileEnemyList);
		_freeEntityList(_missileBossList);
		_freeEntityList(_bonusList);
		_copyEntityList(_playerList, rhs._playerList);
		_copyEntityList(_enemyList, rhs._enemyList);
		_copyEntityList(_bossList, rhs._bossList);
		_copyEntityList(_missilePlayerList, rhs._missilePlayerList);
		_copyEntityList(_missileEnemyList, rhs._missileEnemyList);
		_copyEntityList(_missileBossList, rhs._missileBossList);
		_copyEntityList(_bonusList, rhs._bonusList);
	}
	return (*this);
}

void            Game::launch()
{
	_initGame();
	_gameLoop();
	_endGame();
}

void			Game::relaunch()
{
	Game::~Game();
	_initGame();
	_gameLoop();
}

void            Game::_initGame()
{
	t_coord playerCoord1;
	t_coord playerCoord2;

	initscr();
	if (LINES < MAIN_WIN_HMIN || COLS < MAIN_WIN_WMIN)
	{
		endwin();
		throw (Game::WindowDimensionsInvalidException());
	}
	_mainWin = newwin(LINES - BOT_WIN_H, COLS, 0, 0);
	_bottomWin = newwin(BOT_WIN_H, COLS, LINES - BOT_WIN_H, 0);
	noecho();
	cbreak();
	curs_set(0);
	keypad(_mainWin, TRUE);
	nodelay(_mainWin, TRUE);
	set_escdelay(0);
	start_color();
	init_color(COLOR_BLUE, 600, 800, 1000);
	init_color(COLOR_WHITE, 1000, 500, 200);
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_YELLOW, 220, 180, 120);
	init_color(COLOR_RED, 800, 0, 0);
	init_color(COLOR_MAGENTA, 800, 0, 800);
	init_color(COLOR_GREEN, 0, 800, 0);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	wbkgdset(_mainWin, COLOR_PAIR(COL_DEFAULT));
	wbkgdset(_bottomWin, COLOR_PAIR(COL_DEFAULT));
	playerCoord1.y = (unsigned int)(LINES - (6 + BOT_WIN_H));
	playerCoord1.x = (unsigned int)((COLS / 3) - 1);
	playerCoord2.y = (unsigned int)(LINES - (6 + BOT_WIN_H));
	playerCoord2.x = (unsigned int)(2 * (COLS / 3) - 1);
	Weapon      pioupiou = Weapon(1, 1, 50, "|" , 1000);
	pushInList(_playerList, new Player(3, 3, 2, _readSkin("env/playership.env"), new Weapon(pioupiou), playerCoord1, 119, 115, 97, 100, KEY_SPC));
	pushInList(_playerList, new Player(3, 3, 2, _readSkin("env/playership.env"), new Weapon(pioupiou), playerCoord2, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, 48));//92
}

void            Game::_gameLoop()
{
	int                 i;
	int                 key;
	t_coord             coord;
	bool                bossPop = false;
	std::string         bkgd;
	std::string         gameOver = _readSkin("env/gameover.env");
	std::string         gameWin = _readSkin("env/gamewin.env");
	std::string         enemySkin = _readSkin("env/enemy.env");
	std::string         bossSkin = _readSkin("env/shadow.env");
	Weapon              laser = Weapon(1, 1, 50, "|" , 1000);
	Weapon              pioupiou = Weapon(1, 1, 50, "." , 1000);
	WeapTwoMissSameSide bonusWeap = WeapTwoMissSameSide(2, 2, 70, "*", 400, 0);
	WeapTwoMissSameSide weaponBoss = WeapTwoMissSameSide(2, 2, 50, _readSkin("env/stinger.env"), 2000, 0);

	_timer = 125;
	bkgd = _fillBackground();
	while ((key = wgetch(_mainWin)) != KEY_ESC && _playerList && _timer > 0 && (!bossPop || _bossList))
	{
		if (key == KEY_RESIZE)
		{
			relaunch();
			return ;
		}
		_refreshMainWin(bkgd);
		if ((i = rand()) % 5000 < 1 && _timer > 100)
		{
			coord.x = i % (COLS - AEntity::getSkinSize(enemySkin).x - 1) + 1;
			coord.y = 1;
			pushInList(_enemyList, new Enemy(2, 3, 500, 250, enemySkin, new Weapon(laser), coord));
		}
		else if (!bossPop && _timer <= 100)
		{
			pushInList(_bossList, new Boss(50, 3, 100, 1000, bossSkin, new WeapTwoMissSameSide(weaponBoss), (t_coord){30, 1}));
			bossPop = true;
		}
		if ((i = rand()) % 17321 < 1)
		{
			coord.x = (unsigned int)((i % (COLS - 2)) + 1);
			coord.y = (unsigned int)((i % (LINES - BOT_WIN_H - 2)) + 1);
			if (i % 2)
				pushInList(_bonusList, new Bonus("$", new WeapTwoMissSameSide(bonusWeap), coord));
			else
				pushInList(_bonusList, new Bonus("$", new Weapon(pioupiou), coord));
		}
		_gameCore(key);
		wrefresh(_mainWin);
		_refreshBottomWin(bkgd);
	}
	if (key != KEY_ESC)
	{
		werase(_mainWin);
		mvwprintw(_mainWin, (LINES - BOT_WIN_H + 10) / 2, (COLS - 12) / 2, "FINAL SCORE:");
		mvwprintw(_mainWin, (LINES - BOT_WIN_H + 10) / 2, ((COLS - 3) / 2) + 14, "%i", _score);
		if (!_playerList || _timer == 0)
			_displayInMiddle(_mainWin, gameOver.c_str(), (LINES - BOT_WIN_H - 6) / 2);
		else
			_displayInMiddle(_mainWin, gameWin.c_str(), (LINES - BOT_WIN_H - 6) / 2);
		wrefresh(_mainWin);
		usleep(2000000);
	}
}

void	Game::_displayInMiddle(WINDOW *win, const char *str, int y)
{
	int	i;
	int x;
	int xStart;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	xStart = COLS / 2 - i / 2;
	i = 0;
	while (str[i])
	{
		x = xStart;
		while (str[i] && str[i] != '\n')
			mvwaddch(win, y, x++, str[i++]);
		i += str[i] ? 1 : 0;
		y++;
	}
}

void            Game::_endGame()
{
	wclear(_mainWin);
	wclear(_bottomWin);
	delwin(_mainWin);
	delwin(_bottomWin);
	endwin();
}

void            Game::_gameCore(int key)
{
	_shootInList(_playerList, _missilePlayerList, key);
	_shootInList(_enemyList, _missileEnemyList, key);
	_shootInList(_bossList, _missileBossList, key);
	_shootInList(_missileBossList, _missileBossList, key);

	_displayEntities(_playerList, COL_BLUE);
	_displayEntities(_enemyList, COL_DEFAULT);
	_displayEntities(_bossList, COL_RED);
	_displayEntities(_missilePlayerList, COL_BLUE);
	_displayEntities(_missileEnemyList, COL_DEFAULT);
	_displayEntities(_missileBossList, COL_PURPLE);
	_displayEntities(_bonusList, COL_GREEN);

	_moveInList(_playerList, key);
	_moveInList(_enemyList, key);
	_moveInList(_bossList, key);
	_moveInList(_missilePlayerList, key);
	_moveInList(_missileEnemyList, key);
	_moveInList(_missileBossList, key);
	_moveInList(_bonusList, key);

	_collision(_playerList, _enemyList);
	_collision(_playerList, _bossList);
	_collision(_playerList, _missileEnemyList);
	_collision(_playerList, _missileBossList);
	_collision(_playerList, _bonusList);
	_collision(_missilePlayerList, _enemyList);
	_collision(_missilePlayerList, _bossList);
	_collision(_missilePlayerList, _missileBossList);
}

void            Game::_displayEntities(AEntity::t_entityList *list, unsigned int colorNb) const
{
	while (list)
	{
		list->entity->displaySkin(_mainWin, colorNb);
		list = list->next;
	}
}

void            Game::_moveInList(AEntity::t_entityList *&begin, int key) const
{
	AEntity::t_entityList    *entityTmp = begin;

	while (entityTmp)
	{
		if (entityTmp == begin && !entityTmp->entity->move((unsigned int) (LINES - BOT_WIN_H), COLS, key))
			_lstdelone(begin, entityTmp, 'F');
		else if (entityTmp->next && !entityTmp->next->entity->move((unsigned int) (LINES - BOT_WIN_H), COLS, key))
			_lstdelone(begin, entityTmp, 'N');
		entityTmp = entityTmp ? entityTmp->next : begin;
	}
}

void            Game::_shootInList(AEntity::t_entityList *list, AEntity::t_entityList *&listOfMissile, int key) const
{
	while (list)
	{
		try { pushInList(listOfMissile, list->entity->shoot(key)); }
		catch (std::exception &e) {}
		list = list->next;
	}
}

bool            Game::_hitbox(AEntity::t_entityList *entity1, AEntity::t_entityList *entity2) const
{
	if (entity1->entity->getCoord().x + entity1->entity->_skinSize.x >= entity2->entity->getCoord().x
			&& entity1->entity->getCoord().x <= entity2->entity->getCoord().x + entity2->entity->_skinSize.x
			&& entity1->entity->getCoord().y + entity1->entity->_skinSize.y - 1 >= entity2->entity->getCoord().y
			&& entity1->entity->getCoord().y <= entity2->entity->getCoord().y + entity2->entity->_skinSize.y)
		return (true);
	return (false);
}

void            Game::_collision(AEntity::t_entityList *&list1, AEntity::t_entityList *&list2)
{
	AEntity::t_entityList    *tmp1 = list1;
	unsigned int    tmp1HP;
	unsigned int    tmp2HP;

	while (tmp1)
	{
		AEntity::t_entityList    *tmp2 = list2;
		while (tmp1 && tmp2)
		{
			if (tmp1->next && tmp2->next && _hitbox(tmp1->next, tmp2->next))
			{
				tmp1HP = tmp1->next->entity->takeDamage(*tmp2->next->entity, _mainWin);
				tmp2HP = tmp2->next->entity->takeDamage(*tmp1->next->entity, _mainWin);
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
				tmp1HP = tmp1->next->entity->takeDamage(*tmp2->entity, _mainWin);
				tmp2HP = tmp2->entity->takeDamage(*tmp1->next->entity, _mainWin);
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
				tmp1HP = tmp1->entity->takeDamage(*tmp2->next->entity, _mainWin);
				tmp2HP = tmp2->next->entity->takeDamage(*tmp1->entity, _mainWin);
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
				tmp1HP = tmp1->entity->takeDamage(*tmp2->entity, _mainWin);
				tmp2HP = tmp2->entity->takeDamage(*tmp1->entity, _mainWin);
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

bool            Game::checkTime(unsigned int msecond, clock_t  &last)
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
	wattron(_mainWin, COLOR_PAIR(COL_YELLOW));
	mvwprintw(_mainWin, 1, 1, bkgd.c_str());
	wattroff(_mainWin, COLOR_PAIR(COL_YELLOW));
	box(_mainWin, 0, 0);
}

void            Game::_refreshBottomWin(std::string bkgd)
{
	wattron(_bottomWin, COLOR_PAIR(COL_YELLOW));
	mvwprintw(_bottomWin, 1, 1, bkgd.c_str());
	wattroff(_bottomWin, COLOR_PAIR(COL_YELLOW));
	box(_bottomWin, 0, 0);
	mvwprintw(_bottomWin, 2, 3, "time:");
	mvwprintw(_bottomWin, 2, 19, "lives:");
	mvwprintw(_bottomWin, 2, 42, "score:");
	mvwprintw(_bottomWin, 2, 64, "P1  |  move = W A S D  |  shoot = SPACE");
	mvwprintw(_bottomWin, 3, 64, "P2  |  move = ARROWS   |  shoot = 0");
	AEntity::t_entityList    *playerListTmp = _playerList;
	for (int y = 0; playerListTmp; y++)
	{
		int x = 26;
		for (unsigned int i = 0 ; i < playerListTmp->entity->getHp() ; i++)
		{
			mvwprintw(_bottomWin, 2 + y, x, "<3");
			x += 4;
		}
		playerListTmp = playerListTmp->next;
	}
	mvwprintw(_bottomWin, 2, 9, "%i", _timer);
	mvwprintw(_bottomWin, 2, 50, "%i", _score);
	mvwvline(_bottomWin, 1, 16, ACS_VLINE, 3);
	mvwvline(_bottomWin, 1, 39, ACS_VLINE, 3);
	mvwvline(_bottomWin, 1, 60, ACS_VLINE, 3); 
	if (checkTime(1000, _lastTimer))
		_timer--;
	wrefresh(_bottomWin);
	werase(_bottomWin);
}

std::string     Game::_fillBackground() const
{
	int                 i;
	unsigned int        size = (unsigned int)(LINES - BOT_WIN_H) * COLS;
	// unsigned int	size = 5000000;
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
	// std::string	str = bkgd.str();
	// str = "salut" + str;
	return (bkgd.str());
	
}

std::string     Game::_readSkin(std::string nameOfFile) const
{
	std::ifstream       file(nameOfFile.c_str());
	std::stringstream   read;

	read << file.rdbuf();
	file.close();
	return (read.str());
}

void            Game::pushInList(AEntity::t_entityList *&list, AEntity *entity)
{
	if (entity)
	{
		AEntity::t_entityList    *tmp = list;
		AEntity::t_entityList    *newEntity = new AEntity::t_entityList();

		newEntity->entity = entity;
		newEntity->next = NULL;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp ? tmp->next = newEntity : list = newEntity;
	}
}

void            Game::pushInList(AEntity::t_entityList *&dest, AEntity::t_entityList *src)
{
	if (src)
	{
		AEntity::t_entityList *tmp = dest;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp ? tmp->next = src : dest = src;
	}
}

void            Game::_lstdelone(AEntity::t_entityList *&begin, AEntity::t_entityList *&current, char command) const
{
	AEntity::t_entityList    *tmp_next = NULL;

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

void            Game::_freeEntityList(AEntity::t_entityList *&list) const
{
	AEntity::t_entityList    *tmp;

	while (list)
	{
		tmp = list->next;
		delete list->entity;
		delete list;
		list = tmp;
	}
	list = NULL;
}

void            Game::_copyEntityList(AEntity::t_entityList *&dest, AEntity::t_entityList *src) const
{
	while (src)
	{
		pushInList(dest, src->entity);
		src = src->next;
	}
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
