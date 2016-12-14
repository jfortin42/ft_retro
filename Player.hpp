/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:56:48 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/14 17:04:13 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "AEntity.hpp"
# include "AWeapon.hpp"

class AEntity;
class AWeapon;

class Player : public AEntity {

    public:
        Player(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord);
        Player(Player const &src);
        ~Player();

        Player      &operator=(Player const &rhs);
    private:
        Player();
};

#endif