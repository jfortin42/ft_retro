/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:52:16 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/13 12:46:49 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"

Bonus::Bonus(t_coord coord, std::string skin, unsigned int timer, AWeapon *weapon) : _coord(coord), _skin(skin), _timer(timer), _weapon(weapon) {}

Bonus::Bonus(Bonus const &src) : _coord(src._coord), _skin(src._skin), _timer(src._timer)
{
    //DEEPCOPY
    //_weapon = src._weapon->clone();
    //DEEPCOPY
}

Bonus::~Bonus() {}

Bonus           &Bonus::operator=(Bonus const &rhs)
{
    if (this != &rhs)
    {
        _coord = rhs._coord;
        _skin = rhs._skin;
        _timer = rhs._timer;
        //_weapon = rhs._weapon;//DEEPCOPY!
    }
    return (*this);
}

unsigned int    Bonus::getTimer() const { return (_timer); }

// bool         Bonus::cmpCoord(AEntity *entity) const
// {
    //comparer les coordonnees du bonus avec la hitbox de l'entite
    //return TRUE or FALSE
    //if TRUE => delete bonus
// }

void            Bonus::displaySkin(WINDOW *win) const
{
    wattron(win, A_BLINK);// | COLOR_PAIR(3));
    mvwprintw(win, _coord.y, _coord.x, _skin.c_str());
    wattroff(win, A_BLINK);// | COLOR_PAIR(3));
}

void            Bonus::giveWeapon(AEntity *entity) const { entity->equipWeapon(_weapon); }