/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missileboss.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:38:39 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/19 18:42:28 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILEBOSS_HPP
# define MISSILEBOSS_HPP

# include "Game.hpp"

class Missileboss : public AWeapon {

public:
	Missileboss(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin_missile, unsigned int rateOfFire, unsigned int marging);
	Missileboss();
	Missileboss(Missileboss const &src);
	AEntity::t_entityList	*createMissile(AEntity &shooter, char direction);
	bool					insideMap(t_coord coordEntity, t_coord sizeSkin);
	~Missileboss();

	Missileboss	&operator=(Missileboss const &rhs);

	AWeapon	*clone() const;

private:
	unsigned int	_marging;

};

#endif