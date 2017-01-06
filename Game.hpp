/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:14:47 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/06 14:30:59 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <unistd.h>
# include <iostream>
# include <fstream>
# include <sstream>

// typedef struct	s_coord
// {
// 	unsigned int	x;
// 	unsigned int	y;
// }				t_coord;

// class   AEntity;
// class   AWeapon;
// class   Missile;
// # include
# include "AEntity.hpp"
# include "AWeapon.hpp"
# include "Missile.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Pioupiou.hpp"

# define MAIN_WIN_WMIN 130
# define MAIN_WIN_HMIN 30
# define BOT_WIN_H 5

# define KEY_SPC 32
# define KEY_ESC 27

class                   Player;

typedef struct          s_entityList
{
    AEntity             *entity;
    struct s_entityList  *next;
}                       t_entityList;

class Game {

    public:
        Game();
        Game(Game const &src);
        ~Game();

        Game            &operator=(Game const &rhs);
        void            launch();
        
    private:
        class WindowDimensionsInvalidException : public std::exception {

            public:
                WindowDimensionsInvalidException();
                WindowDimensionsInvalidException(WindowDimensionsInvalidException const &src);
                ~WindowDimensionsInvalidException() throw();

                WindowDimensionsInvalidException    &operator=(WindowDimensionsInvalidException const &rhs);
                
                char const                          *what(void) const throw();
                
        };

        void            _initGame();
        bool            _checkTime(unsigned int msecond, clock_t &last);
        void            _gameLoop();
        void            _endGame();
        
        void            _displayEntities(t_entityList *list) const;
    	void			_moveInList(t_entityList *&begin, int key);
        void            _collision(t_entityList *&list1, t_entityList *&list2);
        bool            _hitbox(t_entityList *entity1, t_entityList *entity2);
        void            _moveEntities(int key);

        void            _pushInList(t_entityList *&list, AEntity *entity);
        void            _lstdelone(t_entityList *&begin, t_entityList *&current, char command);
        void            _freeEntityList(t_entityList *&list);

        void            _refreshMainWin(std::string bkgd);
        void            _refreshBottomWin(std::string bkgd);
        
        std::string     _fillBackground() const;
        std::string     _readSkin(std::string nameOfFile) const;

        WINDOW          *_main_win;
        WINDOW          *_bottom_win;
        
        unsigned int    _timer;
        unsigned int    _score;

        t_entityList    *_playerList;
        t_entityList    *_enemyList;
        t_entityList    *_missileList;

        clock_t         _last_loop;
        clock_t         _last_timer;

};

#endif