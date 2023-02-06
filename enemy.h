#ifndef ENEMY_H
#define ENEMY_H

#include <projectile.h>

class Enemy : public Physics
{
private:
    //===Projectiles===//
    float fire_speed;
    float time_passed;
    std::vector<std::unique_ptr<Projectile>> projectiles;

    //===Connection line===//
    sf::Vector2f point_cordinates;
    std::vector<sf::Vector2f> points_vector;

    bool contains;
    std::vector<bool> contains_bool_vector;
    int point_number = 1;
    bool in_sight = true;

    //===luuuufa===//
    sf::RectangleShape lufa;

    //===methods===//
    void fire(const sf::Time &elapsed_time);
    void clear_projectiles_out_of_window();
    void projectiles_collision_arena(std::vector<std::unique_ptr<Tile>> &tiles);
    void uptade_line(sf::RectangleShape &body);
    void create_points_vector(sf::RectangleShape &body);
    void calculate_points(int x,int y);

    void check_if_tile_contain_point(std::vector<std::unique_ptr<Tile> > &tiles);
    void check_in_sight();
    void uptade_lufa(sf::RectangleShape &body);
public:
    Enemy(sf::Vector2f staring_position_,float fire_speed_);
    sf::Vertex line2 [];        //do wizualizacji tylko
    //===methods===//
   void uptade(const sf::Time &elapsed_time,sf::RectangleShape &body,std::vector<std::unique_ptr<Tile> > &tiles);


   //===setters===//

   //===getters===//
   std::vector<std::unique_ptr<Projectile>>& getprojectiles();

   sf::RectangleShape getline();
   std::unique_ptr<sf::Vertex>& getline2() ;
};

#endif // ENEMY_H
