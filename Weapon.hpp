/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                        :+:      :+:    :+:   */
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

class	Weapon {

public:

	Weapon(unsigned int hpMissile, unsigned int damageDeal, unsigned int speedMissile, std::string skinMissile, unsigned int rateOfFire);
	Weapon(Weapon const &src);
	virtual ~Weapon();

	Weapon							&operator=(Weapon const &rhs);

	virtual AEntity::t_entityList	*createMissile(AEntity &shooter, char direction);

	virtual bool					isSimpleWeapon() const;
	
	t_coord	const					_skinSize;

protected:

	bool							insideMap(t_coord coordEntity, t_coord sizeSkin) const;

	unsigned int					_hpMissile;
	unsigned int					_damageDeal;
	unsigned int					_speedMissile;
	std::string						_skinMissile;
	unsigned int					_rateOfFire;
	clock_t							_lastShoot;

private:
	Weapon();

};

#endif