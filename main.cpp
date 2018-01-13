/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 14:35:38 by fsidler           #+#    #+#             */
/*   Updated: 2018/02/11 22:27:17 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

int main()
{
    srand((unsigned int)time(NULL));
    Game    *play = new Game();
    try
    {
        play->launch();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    delete play;
    return (0);
}