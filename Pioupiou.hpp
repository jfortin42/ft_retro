/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:41:51 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/11 22:23:18 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIOUPIOU_HPP
# define PIOUPIOU_HPP

# include "Game.hpp"

class Pioupiou : public AWeapon {

public:
	Pioupiou(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin_missile, unsigned int rateOfFire);
	Pioupiou(Pioupiou const &src);
	~Pioupiou();

	Pioupiou	&operator=(Pioupiou const &rhs);
	
	AWeapon		*clone() const;

private:
	Pioupiou();

};

#endif