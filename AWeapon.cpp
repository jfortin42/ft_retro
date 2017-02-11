/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/11 22:25:24 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

AWeapon::AWeapon(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, std::string skin_missile, unsigned int rateOfFire) : _hp_missile(hp_missile), _damageDeal(damageDeal), _speed_missile(speed_missile), _skin_missile(skin_missile), _rateOfFire(rateOfFire), _cnt_shoot(0) {}

AWeapon::AWeapon(AWeapon const &src) : _hp_missile(src._hp_missile), _damageDeal(src._damageDeal), _speed_missile(src._speed_missile), _skin_missile(src._skin_missile), _rateOfFire(src._rateOfFire), _cnt_shoot(0) {}

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
		_cnt_shoot = rhs._cnt_shoot;
	}
	return (*this);
}

t_coord			AWeapon::getSkinSize() const
{
    std::size_t index;
	std::size_t	height;
    std::size_t length_tmp;
    std::size_t length_max;

    index = 0;
	height = 0;
    length_tmp = 0;
    length_max = 0;
	while (index < _skin_missile.length() - 1)
    {
		height++;
        index += length_tmp + 1;
		if ((length_tmp = _skin_missile.find("\n", index + 1) - index) > _skin_missile.length())
        {
            length_tmp = _skin_missile.length() - index;
            length_max = (length_max < length_tmp) ? length_tmp : length_max;        
            break ;
        }
        length_max = (length_max < length_tmp) ? length_tmp : length_max;
    }
	return ((t_coord){length_max, height});
}

AEntity		*AWeapon::createMissile(AEntity &shooter, char direction)
{
	t_coord	skinShooter = shooter.getSkinSize();
	t_coord coordShooter = shooter.getCoord();
	t_coord	coordMissile;

	if (direction == 'N')
	{
		coordMissile.x = coordShooter.x + skinShooter.x / 2 - getSkinSize().x / 2;
		coordMissile.y = coordShooter.y - getSkinSize().y - 1;
	}
	else if (direction == 'S')
	{
		coordMissile.x = coordShooter.x + skinShooter.x / 2 - getSkinSize().x / 2;
		coordMissile.y = coordShooter.y + skinShooter.y;
	}
	else if (direction == 'E')
	{
		coordMissile.x = coordShooter.x + skinShooter.x;
		coordMissile.y = coordShooter.y + skinShooter.y / 2 - getSkinSize().y / 2;
	}
	else if (direction == 'W')
	{
		coordMissile.x = coordShooter.x - getSkinSize().x - 1;
		coordMissile.y = coordShooter.y + skinShooter.y / 2 - getSkinSize().y / 2;
	}
	if (_cnt_shoot++ < _rateOfFire || coordMissile.y + getSkinSize().y >= (unsigned int)(LINES - BOT_WIN_H))
		return (NULL);
	_cnt_shoot = 0;
	return (new Missile(_hp_missile, _damageDeal, _speed_missile, _skin_missile, NULL, coordMissile, direction));
}