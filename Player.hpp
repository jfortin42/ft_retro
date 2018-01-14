/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:08:35 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:47:20 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Game.hpp"

class Player : public AEntity {

    public:
        Player(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, Weapon *weapon, t_coord coord, int keyUp, int keyDown, int keyLeft, int keyRight, int keyShoot);
        Player(Player const &src);
        ~Player();

        Player                  &operator=(Player const &rhs);

        bool                    move(unsigned int height, unsigned int width, int key);
        AEntity::t_entityList    *shoot(int key);

        unsigned int            takeDamage(AEntity &attacker);

    private:
        Player();

        int _keyUp;
        int _keyDown;
        int _keyLeft;
        int _keyRight;
        int _keyShoot;
};

#endif