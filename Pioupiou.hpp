/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:41:51 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/16 18:37:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIOUPIOU_HPP
# define PIOUPIOU_HPP

# include "Game.hpp"

class Pioupiou : public AWeapon {

public:
	Pioupiou(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int rateOfFire);
	Pioupiou(Pioupiou const &src);
	~Pioupiou();

	Pioupiou	&operator=(Pioupiou const &rhs);
	
	AWeapon		*clone() const;
	AEntity		*createMissile(t_coord coord, char direction);

private:
	Pioupiou();

};

#endif