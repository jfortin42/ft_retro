/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/11 17:54:08 by jfortin          ###   ########.fr       */
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