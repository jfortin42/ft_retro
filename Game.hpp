/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:14:47 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/19 20:02:09 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <unistd.h>
# include <iostream>
# include <fstream>
# include <sstream>
# include <time.h>//

# include "Player.hpp"

# define MAIN_WIN_WMIN 130
# define MAIN_WIN_HMIN 30
# define BOT_WIN_H 5

# define KEY_ESC 27

class                   Player;

typedef struct          s_enemyList
{
    AEntity             *enemy;
    struct s_enemyList  *next;
}                       t_enemyList;

class Game {

    public:
        Game();
        Game(Game const &src);
        ~Game();

        Game            &operator=(Game const &rhs);
        void            launch();
        //void            incScore(unsigned int amount);
        //unsigned int    getScore() const;
        
    private:
        void            _initGame();
        void            _gameLoop();
        void            _refreshBottomWin();
        void            _endGame();
        
        void            _freeEnemyList();

        void            _fillBackground(unsigned int height, unsigned int width) const;
        std::string     _readSkin(std::string nameOfFile) const;

        WINDOW          *_main_win;
        WINDOW          *_bottom_win;
        
        unsigned int    _timer;
        unsigned int    _score;
        unsigned int    _stdscrHeight;
        unsigned int    _stdscrWidth;

        AEntity         *_player;
        t_enemyList     *_enemyList;

};

#endif