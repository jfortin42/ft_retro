/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:00:56 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/16 18:37:47 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LASER_HPP
# define LASER_HPP

# include "Game.hpp"

class Laser : public AWeapon {

public:
	Laser(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int rateOfFire);
	Laser();
	Laser(Laser const &src);
	~Laser();

	Laser	&operator=(Laser const &rhs);

	AWeapon	*clone() const;
	AEntity	*createMissile(t_coord coord, char direction);

};

#endif