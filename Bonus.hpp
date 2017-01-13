/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:35:21 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/13 12:40:45 by fsidler          ###   ########.fr       */
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

    unsigned int    getTimer() const;
    bool            cmpCoord(AEntity *entity) const;
    void            displaySkin(WINDOW *win) const;
    void            giveWeapon(AEntity *entity) const;
    
private:
    Bonus();

    t_coord         _coord;
    std::string     _skin;
    unsigned int    _timer;
    AWeapon         _*weapon;

};

#endif