#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <physics.h>
class Projectile : public Physics
{
private:
   void move();
public:
    Projectile(sf::Vector2f starting_position_,float rotate_factor_,sf::Vector2f vel_dir_);
    void uptade(const sf::Time &elapsed_time);
};

#endif // PROJECTILE_H
