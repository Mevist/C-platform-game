#ifndef PLAYER_H
#define PLAYER_H

#include<tile.h>
#include<physics.h>
#include<animation.h>

class Player : public Physics
{
private:
    void movement_side_ways(const sf::Time &elapsed_time);
    void movement_jump(const sf::Time &elapsed_time);
    void move();
    void animation_handle(const sf::Time &elapsed_time);
    Animation walking;
    Animation stand;
public:
    Player(float x_,float y_); // moze byc bezuzyteczne ale zostawiam jeszcze
 //   Player() : walking(body_texture,70,278,66,93,3) {}
    void uptade(const sf::Time &elapsed_time,std::vector<std::unique_ptr<Tile>>& tiles);

    //temp functions//
};


#endif // PLAYER_H
