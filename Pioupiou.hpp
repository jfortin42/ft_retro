/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:41:51 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/10 16:17:31 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIOUPIOU_HPP
# define PIOUPIOU_HPP

# include "Game.hpp"
// # include "AWeapon.hpp"

class Pioupiou : public AWeapon{

public:
	Pioupiou(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int rateOfFire);
	Pioupiou(Pioupiou const &src);
	~Pioupiou();

	AEntity		*createMissile(t_coord coord, char direction);

	Pioupiou	&operator=(Pioupiou const &rhs);

private:
	Pioupiou();

};

#endif