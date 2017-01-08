/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:27 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/07 22:35:29 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

#include "Missile.hpp"
// #include "AEntity.hpp"
// class   AEntity;
// class   AWeapon;
// class   Missile;
// # include "Game.hpp"
#include "AEntity.hpp"
// class	Missile;
// class	AEntity;

class	AWeapon{

public:
	AWeapon(unsigned int hp_missile, unsigned int speed, unsigned int rateOfFire);
	AWeapon(AWeapon const &src);
	~AWeapon();

	virtual AEntity	*createMissile(t_coord coord, char direction);

	AWeapon	&operator=(AWeapon const &rhs);

protected:
	class	RateOfFireException : public std::exception {
		public:
			RateOfFireException();
			RateOfFireException(RateOfFireException const &src);
			~RateOfFireException() throw();

			RateOfFireException	&operator=(RateOfFireException const &rhs);

			char const					*what(void) const throw();
	};
	
	unsigned int		hp_missile;
	unsigned int		speed_missile;
	unsigned int		rateOfFire;
	unsigned int		cnt_shoot;

private:
	AWeapon();

};

#endif