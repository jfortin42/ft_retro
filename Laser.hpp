/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:00:56 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/11 22:22:01 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LASER_HPP
# define LASER_HPP

# include "Game.hpp"

class Laser : public AWeapon {

public:
	Laser(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin_missile, unsigned int rateOfFire);
	Laser();
	Laser(Laser const &src);
	~Laser();

	Laser	&operator=(Laser const &rhs);

	AWeapon	*clone() const;

};

#endif