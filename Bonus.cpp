/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:07:22 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:46:55 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"
#include "Weapon.hpp"

Bonus::Bonus(std::string skin, Weapon *weapon, t_coord coord, unsigned int timePop) : AEntity(1, 0, timePop, 20, skin, weapon, coord, 'D') {}

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
    return !Game::checkTime(_speed, _lastMove);
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

unsigned int	        Bonus::takeDamage(AEntity &attacker)
{
    attacker.copyWeaponList(_weaponList);
    _weaponList = NULL;
    _hp -= (_hp < attacker.getDamageDeal()) ? _hp : attacker.getDamageDeal();
	return (_hp);
}