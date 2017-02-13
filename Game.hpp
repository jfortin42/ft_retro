/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:14:47 by fsidler           #+#    #+#             */
/*   Updated: 2017/02/13 13:38:01 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "AEntity.hpp"
# include "AWeapon.hpp"
# include "Missile.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Pioupiou.hpp"
# include "Laser.hpp"

# define MAIN_WIN_WMIN 130
# define MAIN_WIN_HMIN 30

# define KEY_SPC 32
# define KEY_ESC 27

class                   Player;

typedef struct          s_entityList
{
    AEntity             *entity;
    struct s_entityList *next;
}                       t_entityList;

class                   Game {

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
                virtual ~WindowDimensionsInvalidException() throw();

                WindowDimensionsInvalidException    &operator=(WindowDimensionsInvalidException const &rhs);
                
                char const                          *what(void) const throw();
                
        };

        void            _initGame();
        void            _gameLoop();
        void            _endGame();
        
        void            _gameCore(int key);
        void            _displayEntities(t_entityList *list) const;
    	void			_moveInList(t_entityList *&begin, int key);
        void            _shootInList(t_entityList *list, t_entityList *&listOfMissile);
        bool            _hitbox(t_entityList *entity1, t_entityList *entity2) const;
        void            _collision(t_entityList *&list1, t_entityList *&list2);

        bool            _checkTime(unsigned int msecond, clock_t &last);
        void            _refreshMainWin(std::string bkgd) const;
        void            _refreshBottomWin(std::string bkgd);
        
        void            _pushInList(t_entityList *&list, AEntity *entity);
        void            _lstdelone(t_entityList *&begin, t_entityList *&current, char command);
        void            _freeEntityList(t_entityList *&list);

        std::string     _fillBackground() const;
        std::string     _readSkin(std::string nameOfFile) const;

        WINDOW          *_main_win;
        WINDOW          *_bottom_win;
        
        unsigned int    _timer;
        unsigned int    _score;

        t_entityList    *_playerList;
        t_entityList    *_enemyList;
        t_entityList    *_bossList;
        t_entityList    *_missilePlayerList;
        t_entityList    *_missileEnemyList;

        clock_t         _last_loop;
        clock_t         _last_timer;

};

#endif