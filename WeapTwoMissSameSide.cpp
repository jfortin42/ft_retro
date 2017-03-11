/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WeapTwoMissSameSide.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:43:21 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/11 12:32:09 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WeapTwoMissSameSide.hpp"

WeapTwoMissSameSide::WeapTwoMissSameSide(unsigned int hpMissile, unsigned int damageDeal, unsigned int speedMissile, std::string skinMissile, unsigned int rateOfFire, unsigned int marging) : Weapon(hpMissile, damageDeal, speedMissile, skinMissile, rateOfFire), _marging(marging) {}

WeapTwoMissSameSide::WeapTwoMissSameSide() : Weapon(1, 2, 50, "|", 200), _marging(1) {}

WeapTwoMissSameSide::WeapTwoMissSameSide(WeapTwoMissSameSide const &src) : Weapon(src._hpMissile, src._damageDeal, src._speedMissile, src._skinMissile, src._rateOfFire), _marging(src._marging) {}

WeapTwoMissSameSide::~WeapTwoMissSameSide() {}

WeapTwoMissSameSide				&WeapTwoMissSameSide::operator=(WeapTwoMissSameSide const &rhs)
{
	Weapon::operator=(rhs);
	_marging = rhs._marging;
	return (*this);
}

Weapon					*WeapTwoMissSameSide::clone() const
{
	Weapon	*clone = new WeapTwoMissSameSide(*this);
	return (clone);
}

AEntity::t_entityList	*WeapTwoMissSameSide::createMissile(AEntity &shooter, char direction)
{
	t_coord					skinShooter = shooter._skinSize;
	t_coord					coordShooter = shooter.getCoord();
	
	t_coord					coordMissile1;
	t_coord					coordMissile2;

	char					direction2;
	char					direction3;	

	AEntity::t_entityList	*listMissile = NULL;

	//if (!Game::_checkTime(_rateOfFire, _lastShoot))
	//	return (NULL);
	if (direction == 'N')
	{
		direction2 = 'W';
		direction3 = 'E';
		coordMissile1.x = coordShooter.x + _marging - _skinSize.x / 2;
		coordMissile1.y = coordShooter.y - _skinSize.y;
		coordMissile2.x = coordShooter.x + skinShooter.x - _marging - _skinSize.x / 2 - 1;
		coordMissile2.y = coordShooter.y - _skinSize.y;
	}
	else if (direction == 'S')
	{
		direction2 = 'W';
		direction3 = 'E';
		coordMissile1.x = coordShooter.x + _marging - _skinSize.x / 2;
		coordMissile1.y = coordShooter.y + skinShooter.y;
		coordMissile2.x = coordShooter.x + skinShooter.x - _marging - _skinSize.x / 2 - 1;
		coordMissile2.y = coordMissile1.y;
	}
	else if (direction == 'E')
	{
		direction2 = 'N';
		direction3 = 'S';
		coordMissile1.x = coordShooter.x + skinShooter.x;
		coordMissile1.y = coordShooter.y + _marging + _skinSize.y / 2;
		coordMissile2.x = coordShooter.x + skinShooter.x;
		coordMissile2.y = coordShooter.y + skinShooter.y - _marging - _skinSize.y / 2 - 1;
	}
	else if (direction == 'W')
	{
		direction2 = 'N';
		direction3 = 'S';
		coordMissile1.x = coordShooter.x - _skinSize.x - 1;
		coordMissile1.y = coordShooter.y + _marging + _skinSize.y / 2;
		coordMissile2.x = coordShooter.x - _skinSize.x - 1;
		coordMissile2.y = coordShooter.y + skinShooter.y - _marging - _skinSize.y / 2 - 1;
	}
	if (!Game::_checkTime(_rateOfFire, _lastShoot))
		return (NULL);
	int rof = rand() % 255 + 245;
	Weapon *pioupiou = new Weapon(1, 1, 50, "-", rof);
	if (insideMap(coordMissile1, _skinSize))
		Game::_pushInList(listMissile, new Missile(_hpMissile, _damageDeal, _speedMissile, 50, _skinMissile, pioupiou->clone(), coordMissile1, direction, direction2));
	if (insideMap(coordMissile2, _skinSize))
		Game::_pushInList(listMissile, new Missile(_hpMissile, _damageDeal, _speedMissile, 50, _skinMissile, pioupiou->clone(), coordMissile2, direction, direction3));
	delete pioupiou;
	return (listMissile);
}

bool					WeapTwoMissSameSide::insideMap(t_coord coordEntity, t_coord sizeSkin)
{
	if (coordEntity.x < 1 || coordEntity.x + sizeSkin.x > (unsigned int)COLS || coordEntity.y < 1 || coordEntity.y + sizeSkin.y > (unsigned int)(LINES - BOT_WIN_H))
		return false;
	return true;
}