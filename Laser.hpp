/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:00:56 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/06 15:32:20 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LASER_HPP
# define LASER_HPP

# include "Game.hpp"

class	Laser : public AWeapon{

public:
	Laser();
	Laser(Laser const &src);
	~Laser();

	AEntity	*createMissile(AEntity const &shooter);

	Laser	&operator=(Laser const &rhs);

private:

};

#endif