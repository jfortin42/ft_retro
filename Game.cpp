/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/15 19:18:25 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _main_win(newwin(//completer)), _bottom_win(newwin(//completer)),
_timer(120), _score(0), _enemyList(NULL)
{
    //int height, width;
    //getmaxyx(height, width);
    //init windows;
    _initDisplay();
    _gameLoop();
    _endGame();
}

Game::Game(Game const &src)
{
    //fonction pour remplir this->_enemyList (DEEP COPY!)
    this->_main_window = new WINDOW(src._main_window);//a verifier
    this->_bottom_win = new WINDOW(src._bottom_win);//a verifier
    this->_timer = src._timer;
    this->score = src._score;
}

Game::~Game()
{
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
        this->_main_window = new WINDOW(src._main_window);//a verifier
        this->_bottom_win = new WINDOW(src._bottom_win);//a verifier
        this->_timer = src._timer;
        this->score = src._score;
    }
    return (*this);
}