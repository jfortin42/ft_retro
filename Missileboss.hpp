/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missileboss.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:38:39 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/10 18:07:38 by fsidler          ###   ########.fr       */
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
	~Missileboss();

	Missileboss				&operator=(Missileboss const &rhs);
	
	AWeapon					*clone() const;
	AEntity::t_entityList	*createMissile(AEntity &shooter, char direction);
	
	bool					insideMap(t_coord coordEntity, t_coord sizeSkin);


private:
	unsigned int			_marging;

};

#endif