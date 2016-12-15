/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:35:21 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/15 15:18:51 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_HPP
# define BONUS_HPP

# include "AEntity.hpp"
# include "AWeapon.hpp"

class AWeapon;

class Bonus {

    public:
        Bonus(t_coord coord, std::string skin, unsigned int timer, AWeapon *weapon);
        Bonus(Bonus const &src);
        ~Bonus();

        Bonus           &operator=(Bonus const &rhs);

        bool            cmpCoord(AEntity *) const;
        void            giveWeapon(AEntity *) const;
        void            displaySkin() const;
        unsigned int    getTimer() const;
    private:
        Bonus();

        t_coord         coord;
        std::string     skin;//retirer?
        unsigned int    timer;
        AWeapon         *weapon;

};

#endif