/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:14:47 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/20 18:37:42 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <unistd.h>
# include <iostream>
# include <fstream>
# include <sstream>

# include "Player.hpp"

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
        void            _gameLoop();
        void            _refreshBottomWin();
        void            _endGame();
        
        void            _pushInList(AEntity *tmp, t_entityList *list);
        void            _freeEnemyList();

        void            _printEnv();
        void            _fillBackground() const;
        std::string     _readSkin(std::string nameOfFile) const;

        WINDOW          *_main_win;
        WINDOW          *_bottom_win;
        
        unsigned int    _timer;
        unsigned int    _score;

        AEntity         *_player;
        t_entityList    *_enemyList;
        t_entityList    *_missileList;

};

#endif