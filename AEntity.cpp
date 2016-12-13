/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:01:52 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/13 18:46:06 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntity.hpp"

AEntity::AEntity(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord)
	: hp(hp), speed(speed), skin(skin), weapon(NULL), coord(coord)
{}

AEntity::~AEntity()
{}

void	AEntity::move(char direction)
{
	if (direction == 'N')
		this->coord.y -= this->speed;
	else if (direction == 'S')
		this->coord.y += this->speed;
	else if (direction == 'E')
		this->coord.x -= this->speed;
	else if (direction == 'W')
		this->coord.x += this->speed;
}

Missile	*AEntity::shoot()
{
	if (this->weapon)
		return (this->weapon->createMissile());
	return (NULL);
}

void	AEntity::takeDamage(AEntity const &attcker)
{
	
}

