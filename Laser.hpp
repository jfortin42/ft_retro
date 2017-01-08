/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:00:56 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/07 20:07:20 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LASER_HPP
# define LASER_HPP

# include "Game.hpp"

class	Laser : public AWeapon{

public:
	Laser(unsigned int hp, unsigned int speed, unsigned int rateOfFire);
	Laser();
	Laser(Laser const &src);
	~Laser();

	AEntity	*createMissile(t_coord coord, char direction);

	Laser	&operator=(Laser const &rhs);

private:

};

#endif