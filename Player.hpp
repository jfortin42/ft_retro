/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:56:48 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/20 19:57:08 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "AEntity.hpp"
# include "Missile.hpp"

class Missile;
class AEntity;

class Player : public AEntity {

    public:
        Player(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord);
        Player(Player const &src);
        ~Player();

        Player      &operator=(Player const &rhs);

        bool        move(unsigned int height, unsigned int width, int key);
        AEntity     *shoot();
        
    private:
        Player();
};

#endif