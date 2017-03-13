/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:52:16 by fsidler           #+#    #+#             */
/*   Updated: 2017/03/18 16:04:55 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"

Bonus::Bonus(std::string skin, Weapon *weapon, t_coord coord) : AEntity(1, 0, 20000, 1, skin, weapon, coord) {}

Bonus::Bonus(Bonus const &src) : AEntity(src) {}

Bonus::~Bonus() {}

Bonus                   &Bonus::operator=(Bonus const &rhs)
{
    AEntity::operator=(rhs);
    return (*this);
}

bool			        Bonus::move(unsigned int height, unsigned int width, int key)
{
    (void)width;
    (void)height;
    (void)key;
    if (Game::checkTime(_speed, _lastMove))
      return (false);
    return (true);
}

AEntity::t_entityList   *Bonus::shoot(int key)
{
    (void)key;
    if (!_weaponList)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    t_weaponList            *tmp = _weaponList;
    AEntity::t_entityList   *listOfMissile = NULL;
    while (tmp)
    {
        Game::pushInList(listOfMissile, tmp->weapon->createMissile(*this,'S'));
        tmp = tmp->next;
    }
    return (listOfMissile);
}

unsigned int	        Bonus::takeDamage(AEntity &attacker, WINDOW *win)
{
    //wattron(win, A_BLINK);
	//displaySkin(win, COL_GREEN);
	//wattroff(win, A_BLINK);
    (void)win;
    (void)attacker;
    //t_weaponList    *src = _weaponList;
    //(void)attacker;
    //return (_hp);
    //attacker.copyWeaponList(_weaponList);
    //while (src)
	//{
	//	attacker.equipWeapon(new Weapon(*(src->weapon)));
	//	src = src->next;
	///}
    this->_hp -= this->_hp < attacker.getDamageDeal() ? this->_hp : attacker.getDamageDeal();
    //_hp = 0;
	return (_hp);
}