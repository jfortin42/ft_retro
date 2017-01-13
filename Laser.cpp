/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:06:23 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/13 19:18:14 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Laser.hpp"

Laser::Laser(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, unsigned int rateOfFire) : AWeapon(hp_missile, damageDeal, speed_missile, rateOfFire) {}

Laser::Laser() : AWeapon(1, 2, 50, 200) {}

Laser::Laser(Laser const &src) : AWeapon(src._hp_missile, src._damageDeal, src._speed_missile, src._rateOfFire) {}

Laser::~Laser() {}

Laser		&Laser::operator=(Laser const &rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
	//(appel de l'operateur d'AEntity? possible//
    //*this AWeapon::= rhs;
    //??)
    //OU ALORS
	/*if (this != &rhs)
	{
		_hp_missile = rhs._hp_missile;
		_damageDeal = rhs._damageDeal;
		_speed_missile = rhs._speed_missile;
		_rateOfFire = rhs._rateOfFire;
		_cnt_shoot = rhs._cnt_shoot;
	}
	return (*this);*/
}

AEntity		*Laser::createMissile(t_coord coord, char direction)
{
	if (_cnt_shoot++ < _rateOfFire)
        throw(AWeapon::RateOfFireException::RateOfFireException());
	_cnt_shoot = 0;
	return (new Missile(_hp_missile, _damageDeal, _speed_missile, "|", NULL, coord, direction));
}