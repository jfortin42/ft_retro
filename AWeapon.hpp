/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:27 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/21 20:01:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_WEAPON_HPP
# define A_WEAPON_HPP

# include "Missile.hpp"
# include "AEntity.hpp"

class	AWeapon {

public:
	AWeapon(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed, unsigned int rateOfFire);
	AWeapon(AWeapon const &src);
	virtual ~AWeapon();

	AWeapon				&operator=(AWeapon const &rhs);

	virtual AWeapon		*clone() const = 0;
	virtual AEntity		*createMissile(t_coord coord, char direction) = 0;

protected:
	class	RateOfFireException : public std::exception {
		public:
			RateOfFireException();
			RateOfFireException(RateOfFireException const &src);
			virtual ~RateOfFireException() throw();

			RateOfFireException	&operator=(RateOfFireException const &rhs);

			char const			*what(void) const throw();
	};
	
	unsigned int		_hp_missile;
	unsigned int		_damageDeal;
	unsigned int		_speed_missile;
	unsigned int		_rateOfFire;
	unsigned int		_cnt_shoot;

private:
	AWeapon();

};

#endif