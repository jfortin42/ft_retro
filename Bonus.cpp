/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:52:16 by fsidler           #+#    #+#             */
/*   Updated: 2017/03/10 19:48:10 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"

Bonus::Bonus(t_coord coord, unsigned int timer) : _coord(coord), _timer(timer), _refresh(0) {}

Bonus::Bonus(Bonus const &src) : _coord(src._coord), _timer(src._timer), _refresh(src._refresh) {}

Bonus::~Bonus() {}

Bonus           &Bonus::operator=(Bonus const &rhs)
{
    if (this != &rhs)
    {
        _coord = rhs._coord;
        _timer = rhs._timer;
        _refresh = rhs._refresh;
    }
    return (*this);
}



unsigned int    Bonus::getTimer() const { return (_timer); }

//bool         Bonus::cmpCoord(AEntity *entity) const
//{
    //comparer les coordonnees du bonus avec la hitbox de l'entite
    //return TRUE or FALSE
    //if TRUE => delete bonus
//}

void            Bonus::displaySkin(WINDOW *win) const
{
    wattron(win, A_BLINK | COLOR_PAIR(3));
    mvwaddch(win, _coord.y, _coord.x, ACS_DIAMOND);
    wattroff(win, A_BLINK | COLOR_PAIR(3));
}