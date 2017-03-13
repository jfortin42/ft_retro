/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WeapTwoMissSameSide.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 11:38:39 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/11 12:23:25 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILEBOSS_HPP
# define MISSILEBOSS_HPP

# include "Game.hpp"

class WeapTwoMissSameSide : public Weapon {

public:
	WeapTwoMissSameSide(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skinMissile, unsigned int rateOfFire, unsigned int marging);
	WeapTwoMissSameSide();
	WeapTwoMissSameSide(WeapTwoMissSameSide const &src);
	~WeapTwoMissSameSide();

	WeapTwoMissSameSide				&operator=(WeapTwoMissSameSide const &rhs);
	
	AEntity::t_entityList			*createMissile(AEntity &shooter, char direction);

	bool							isSimpleWeapon() const;

private:
	unsigned int			_marging;

};

#endif