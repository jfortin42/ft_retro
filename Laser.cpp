/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:06:23 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/11 22:21:48 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Laser.hpp"

Laser::Laser(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, std::string skin_missile, unsigned int rateOfFire) : AWeapon(hp_missile, damageDeal, speed_missile, skin_missile, rateOfFire) {}

Laser::Laser() : AWeapon(1, 2, 50, "|", 200) {}

Laser::Laser(Laser const &src) : AWeapon(src._hp_missile, src._damageDeal, src._speed_missile, src._skin_missile, src._rateOfFire) {}

Laser::~Laser() {}

Laser		&Laser::operator=(Laser const &rhs)
{
	AWeapon::operator=(rhs);
	return (*this);
}

AWeapon		*Laser::clone() const
{
	AWeapon	*clone = new Laser(*this);

	return (clone);
}