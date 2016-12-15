/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 14:51:56 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/15 15:14:24 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"

Bonus::Bonus(t_coord coord, std::string skin, unsigned int timer, AWeapon *weapon) : coord(coord), skin(skin), timer(timer), weapon(weapon)
{}

Bonus::Bonus(Bonus const &src)
{
    *this = src;
}

Bonus::~Bonus()
{}

Bonus           &Bonus::operator=(Bonus const &rhs)
{
    if (this != &rhs)
    {
        this->coord = rhs.coord;
        this->skin = rhs.skin;
        this->timer = rhs.timer;
        this->weapon = rhs.weapon;
    }
    return (*this);
}

bool            Bonus::cmpCoord(AEntity *entity) const
{
    //comparer les coordonnees du bonus avec la hitbox de l'entite
    //return TRUE or FALSE
    //if TRUE => delete bonus
}

void            Bonus::giveWeapon(AEntity *entity) const
{
    entity->equipWeapon(this->weapon);
}

void            Bonus::displaySkin() const
{
    wattron(stdscr, A_BLINK);// | COLOR_PAIR(3));
    mvwprintw(stdscr, this->coord.y, this->coord.x, skin.c_str());
    wattroff(stdscr, A_BLINK);
}

unsigned int    Bonus::getTimer() const
{
    return (this->timer);
}