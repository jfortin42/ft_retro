/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:06:23 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/06 15:33:14 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Laser.hpp"

Laser::Laser()
{}

Laser::Laser(Laser const &src)
{
	*this = src;
}

Laser::~Laser()
{}

AEntity		*Laser::createMissile(AEntity const &shooter)
{
	t_coord coordShoot;
    
    coordShoot.x = shooter.getCoord().x + shooter.getSizeSkin().x / 2;
    coordShoot.y = shooter.getCoord().y - 1;
	return (new Missile(1, 10, "|", NULL, coordShoot, 'N'));
}

Laser	&Laser::operator=(Laser const &rhs)
{
	if (this != &rhs)
	;
	return (*this);	
}