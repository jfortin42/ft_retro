/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/10 18:18:04 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"
# include "Game.hpp"

Weapon::Weapon(unsigned int hpMissile, unsigned int damageDeal, unsigned int speedMissile, std::string skinMissile, unsigned int rateOfFire) : _skinSize(AEntity::getSkinSize(skinMissile)), _hpMissile(hpMissile), _damageDeal(damageDeal), _speedMissile(speedMissile), _skinMissile(skinMissile), _rateOfFire(rateOfFire), _lastShoot(0) {}

Weapon::Weapon(Weapon const &src) : _skinSize(src._skinSize), _hpMissile(src._hpMissile), _damageDeal(src._damageDeal), _speedMissile(src._speedMissile), _skinMissile(src._skinMissile), _rateOfFire(src._rateOfFire), _lastShoot(0) {}

Weapon::~Weapon() {}

Weapon						&Weapon::operator=(Weapon const &rhs)
{
	if (this != &rhs)
	{
		_hpMissile = rhs._hpMissile;
		_damageDeal = rhs._damageDeal;
		_speedMissile = rhs._speedMissile;
		_rateOfFire = rhs._rateOfFire;
		_skinMissile = rhs._skinMissile;
		_lastShoot = rhs._lastShoot;
	}
	return (*this);
}

AEntity::t_entityList		*Weapon::createMissile(AEntity &shooter, char direction)
{
	t_coord	skinShooter = shooter._skinSize;
	t_coord coordShooter = shooter.getCoord();
	t_coord	coordMissile;
	AEntity::t_entityList *listOfMissile = NULL;

	if (direction == 'N')
	{
		coordMissile.x = coordShooter.x + skinShooter.x / 2 - _skinSize.x / 2;
		coordMissile.y = coordShooter.y - _skinSize.y - 1;
	}
	else if (direction == 'S')
	{
		coordMissile.x = coordShooter.x + skinShooter.x / 2 - _skinSize.x / 2;
		coordMissile.y = coordShooter.y + skinShooter.y;
	}
	else if (direction == 'E')
	{
		coordMissile.x = coordShooter.x + skinShooter.x;
		coordMissile.y = coordShooter.y + skinShooter.y / 2 - _skinSize.y / 2;
	}
	else if (direction == 'W')
	{
		coordMissile.x = coordShooter.x - _skinSize.x - 1;
		coordMissile.y = coordShooter.y + skinShooter.y / 2 - _skinSize.y / 2;
	}
	if (!Game::checkTime(_rateOfFire, _lastShoot) || !insideMap(coordMissile, _skinSize))
		return (NULL);
	Game::pushInList(listOfMissile, new Missile(_hpMissile, _damageDeal, _speedMissile, 0, _skinMissile, NULL, coordMissile, direction, direction));
	return (listOfMissile);
}

bool						Weapon::insideMap(t_coord coordEntity, t_coord sizeSkin) const
{
	if (coordEntity.x < 2 || coordEntity.x + sizeSkin.x + 1 > (unsigned int)COLS || coordEntity.y < 1 || coordEntity.y + sizeSkin.y > (unsigned int)(LINES - BOT_WIN_H))
		return false;
	return true;
}

bool						Weapon::isSimpleWeapon() const { return (true); }