/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:35:21 by fsidler           #+#    #+#             */
/*   Updated: 2017/03/11 12:23:25 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_HPP
# define BONUS_HPP

# include "AEntity.hpp"
# include "Weapon.hpp"

class Weapon;

class Bonus {

public:

    typedef struct          s_bonusList
    {
	    Bonus               *bonus;
	    struct s_bonusList  *next;
    }                       t_bonusList;

    Bonus(t_coord coord, unsigned int timer);
    Bonus(Bonus const &src);
    ~Bonus();

    Bonus           &operator=(Bonus const &rhs);

    unsigned int    getTimer() const;
    bool            cmpCoord(AEntity *entity) const;
    void            displaySkin(WINDOW *win) const;
    
private:
    Bonus();

    t_coord         _coord;
    unsigned int    _timer;
    unsigned int    _refresh;

};

#endif