/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:41:51 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/06 13:31:02 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIOUPIOU_HPP
# define PIOUPIOU_HPP

# include "Game.hpp"
// # include "AWeapon.hpp"

class Pioupiou : public AWeapon{

public:
	Pioupiou();
	Pioupiou(Pioupiou const &src);
	~Pioupiou();

	AEntity		*createMissile(AEntity const &shooter);

	Pioupiou	&operator=(Pioupiou const &rhs);

private:

};

#endif