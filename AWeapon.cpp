/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/18 15:46:59 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

AWeapon::AWeapon(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, unsigned int rateOfFire) : _hp_missile(hp_missile), _damageDeal(damageDeal), _speed_missile(speed_missile), _rateOfFire(rateOfFire), _cnt_shoot(0) {}

AWeapon::AWeapon(AWeapon const &src) : _hp_missile(src._hp_missile), _damageDeal(src._damageDeal), _speed_missile(src._speed_missile), _rateOfFire(src._rateOfFire), _cnt_shoot(0) {}

AWeapon::~AWeapon() {}

AWeapon		&AWeapon::operator=(AWeapon const &rhs)
{
	if (this != &rhs)
	{
		_hp_missile = rhs._hp_missile;
		_damageDeal = rhs._damageDeal;
		_speed_missile = rhs._speed_missile;
		_rateOfFire = rhs._rateOfFire;
		_cnt_shoot = rhs._cnt_shoot;
	}
	return (*this);
}

AWeapon::RateOfFireException::RateOfFireException() {}

AWeapon::RateOfFireException::RateOfFireException(RateOfFireException const &src) { *this = src; }

AWeapon::RateOfFireException::~RateOfFireException() throw() {}

AWeapon::RateOfFireException	&AWeapon::RateOfFireException::operator=(AWeapon::RateOfFireException const &rhs)
{
    (void)rhs;
    return (*this);
}

char const						*AWeapon::RateOfFireException::what(void) const throw() { return ("Rate of fire"); }