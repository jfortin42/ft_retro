/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missileboss.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:43:21 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/26 17:55:41 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missileboss.hpp"

Missileboss::Missileboss(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, std::string skin_missile, unsigned int rateOfFire, unsigned int marging) : AWeapon(hp_missile, damageDeal, speed_missile, skin_missile, rateOfFire), _marging(marging) {}

Missileboss::Missileboss() : AWeapon(1, 2, 50, "|", 200), _marging(1) {}

Missileboss::Missileboss(Missileboss const &src) : AWeapon(src._hp_missile, src._damageDeal, src._speed_missile, src._skin_missile, src._rateOfFire), _marging(src._marging) {}

Missileboss::~Missileboss() {}

Missileboss		&Missileboss::operator=(Missileboss const &rhs)
{
	AWeapon::operator=(rhs);
	return (*this);
}

AWeapon		*Missileboss::clone() const
{
	AWeapon	*clone = new Missileboss(*this);

	return (clone);
}

AEntity::t_entityList	*Missileboss::createMissile(AEntity &shooter, char direction)
{
	t_coord			skinShooter = shooter._skin_size;
	t_coord			coordShooter = shooter.getCoord();
	t_coord			coordMissile1;
	t_coord			coordMissile2;
	AEntity::t_entityList	*listMissile = NULL;

	if (direction == 'N')
	{
		coordMissile1.x = coordShooter.x + _marging - _skin_size.x / 2;
		coordMissile1.y = coordShooter.y - _skin_size.y;
		coordMissile2.x = coordShooter.x + skinShooter.x - _marging - _skin_size.x / 2 - 1;
		coordMissile2.y = coordShooter.y - _skin_size.y;
	}
	else if (direction == 'S')
	{
		coordMissile1.x = coordShooter.x + _marging - _skin_size.x / 2;
		coordMissile1.y = coordShooter.y + skinShooter.y;
		coordMissile2.x = coordShooter.x + skinShooter.x - _marging - _skin_size.x / 2 - 1;
		coordMissile2.y = coordMissile1.y;
	}
	else if (direction == 'E')
	{
		coordMissile1.x = coordShooter.x + skinShooter.x;
		coordMissile1.y = coordShooter.y + _marging + _skin_size.y / 2;
		coordMissile2.x = coordShooter.x + skinShooter.x;
		coordMissile2.y = coordShooter.y + skinShooter.y - _marging - _skin_size.y / 2 - 1;
	}
	else if (direction == 'W')
	{
		coordMissile1.x = coordShooter.x - _skin_size.x - 1;
		coordMissile1.y = coordShooter.y + _marging + _skin_size.y / 2;
		coordMissile2.x = coordShooter.x - _skin_size.x - 1;
		coordMissile2.y = coordShooter.y + skinShooter.y - _marging - _skin_size.y / 2 - 1;
	}
	if (!Game::_checkTime(_rateOfFire, _last_shoot))
		return (NULL);
	if (insideMap(coordMissile1, _skin_size))
		Game::_pushInList(listMissile, new Missile(_hp_missile, _damageDeal, _speed_missile, _skin_missile, NULL, coordMissile1, direction));
	if (insideMap(coordMissile2, _skin_size))
		Game::_pushInList(listMissile, new Missile(_hp_missile, _damageDeal, _speed_missile, _skin_missile, NULL, coordMissile2, direction));
	return (listMissile);
}

bool					Missileboss::insideMap(t_coord coordEntity, t_coord sizeSkin)
{
	if (coordEntity.x < 1 || coordEntity.x + sizeSkin.x > (unsigned int)COLS || coordEntity.y < 1 || coordEntity.y + sizeSkin.y > (unsigned int)(LINES - BOT_WIN_H))
		return false;
	return true;
}