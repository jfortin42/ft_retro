/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:14:47 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/15 17:05:24 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <ncurses.h>
# include <string>

# define KEY_ESC 27

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
        void            _initDisplay();
        void            _gameLoop();
        void            _refreshBottomWin();
        void            _endGame();
        
        void            _freeEnemyList();

        WINDOW          *_main_win;
        WINDOW          *_bottom_win;
        
        unsigned int    _timer;
        unsigned int    _score;

        t_enemyList      *_enemyList;

};

#endif