/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:25:43 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/15 17:19:30 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _main_win(newwin()), _bottom_win(newwin()),
_timer(120), _score(0), _enemyList(NULL)
{

}

Game::Game(Game const &src)
{
    //delwin(_main_win);
    //delwin(_score_win);
    //endwin();
    //_freeEnemyList();
    *this = src;
}

Game::~Game()
{

    //_freeEnemyList();
}