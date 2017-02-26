/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/26 18:07:11 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"
# include "Game.hpp"

AWeapon::AWeapon(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, std::string skin_missile, unsigned int rateOfFire) : _skin_size(AEntity::getSkinSize(skin_missile)), _hp_missile(hp_missile), _damageDeal(damageDeal), _speed_missile(speed_missile), _skin_missile(skin_missile), _rateOfFire(rateOfFire), _last_shoot(0) {}

AWeapon::AWeapon(AWeapon const &src) : _skin_size(src._skin_size), _hp_missile(src._hp_missile), _damageDeal(src._damageDeal), _speed_missile(src._speed_missile), _skin_missile(src._skin_missile), _rateOfFire(src._rateOfFire), _last_shoot(0) {}

AWeapon::~AWeapon() {}

AWeapon		&AWeapon::operator=(AWeapon const &rhs)
{
	if (this != &rhs)
	{
		_hp_missile = rhs._hp_missile;
		_damageDeal = rhs._damageDeal;
		_speed_missile = rhs._speed_missile;
		_rateOfFire = rhs._rateOfFire;
		_skin_missile = rhs._skin_missile;
		_last_shoot = rhs._last_shoot;
	}
	return (*this);
}

AEntity::t_entityList		*AWeapon::createMissile(AEntity &shooter, char direction)
{
	t_coord	skinShooter = shooter._skin_size;
	t_coord coordShooter = shooter.getCoord();
	t_coord	coordMissile;
	AEntity::t_entityList *listOfMissile = NULL;

	if (direction == 'N')
	{
		coordMissile.x = coordShooter.x + skinShooter.x / 2 - _skin_size.x / 2;
		coordMissile.y = coordShooter.y - _skin_size.y - 1;
	}
	else if (direction == 'S')
	{
		coordMissile.x = coordShooter.x + skinShooter.x / 2 - _skin_size.x / 2;
		coordMissile.y = coordShooter.y + skinShooter.y;
	}
	else if (direction == 'E')
	{
		coordMissile.x = coordShooter.x + skinShooter.x;
		coordMissile.y = coordShooter.y + skinShooter.y / 2 - _skin_size.y / 2;
	}
	else if (direction == 'W')
	{
		coordMissile.x = coordShooter.x - _skin_size.x - 1;
		coordMissile.y = coordShooter.y + skinShooter.y / 2 - _skin_size.y / 2;
	}
	if (!Game::_checkTime(_rateOfFire, _last_shoot) || coordMissile.y + _skin_size.y >= (unsigned int)(LINES - BOT_WIN_H))
		return (NULL);
	Game::_pushInList(listOfMissile, new Missile(_hp_missile, _damageDeal, _speed_missile, _skin_missile, NULL, coordMissile, direction));
	return (listOfMissile);
}