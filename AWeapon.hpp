/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:27 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/10 18:01:21 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_WEAPON_HPP
# define A_WEAPON_HPP

# include "Missile.hpp"
# include "AEntity.hpp"

# define BOT_WIN_H 5

class	Game;

class	AWeapon {

public:
	AWeapon(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, std::string skin_missile, unsigned int rateOfFire);
	AWeapon(AWeapon const &src);
	virtual ~AWeapon();

	AWeapon							&operator=(AWeapon const &rhs);

	virtual AWeapon					*clone() const = 0;
	virtual AEntity::t_entityList	*createMissile(AEntity &shooter, char direction);
	
	t_coord	const					_skin_size;

protected:
	unsigned int					_hp_missile;
	unsigned int					_damageDeal;
	unsigned int					_speed_missile;
	std::string						_skin_missile;
	unsigned int					_rateOfFire;
	clock_t							_last_shoot;

private:
	AWeapon();

};

#endif