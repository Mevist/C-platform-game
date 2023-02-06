#ifndef PHYSICS_H
#define PHYSICS_H

//forward declaration

//included dependencies
#define PI 3.14159265

#include <iostream>
#include <tile.h>
#include <cmath>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <entity.h>

class Physics : public Entity
{
    protected:
    //===vectors, unit vectors tests, not used yet===//
    sf::Vector2f sum_vector;
    float velocity_length;
    sf::Vector2f velocity_dir;
    float angle;

    //===variables for horizontal movement===//
    float acceleration;
    sf::Vector2f max_velocity;
    bool hit_right = false;
    bool hit_left = false;

    //===variables for vertical movement===//
     bool hit_top = false;
     bool hit_bottom = false;
     bool gravity;
     float gravity_acceleration;

     //===collsion stuff===//
     sf::Vector2f collision_point_top_bottom;           //2 charakterystyczne punkty dla danego obiektu, ktory pozwoli dokladnie sprawdzic kolizje, trzeba bedzie przedytowac,
                                                        // aktualnie zostalo to obliczone troche na sztywno warto bylboy zmienic

public:
   enum direction{
      Right,
      Left,
      None
    }Direction;
    sf::Vector2f current_velocity;

   // virtual ~Physics() = default;

  //====Calculate & do stuff====//
   void Calculate_sum_vector(sf::RectangleShape &body);
   void Calculate_vel_dir();
   float Calculate_current_velocity_x(const sf::Time &elapsed_time, float acceleration_);
   float Calculate_current_velocity_y(const sf::Time &elapsed_time, float acceleration_);
   void Gravity_pull(const sf::Time &elapsed_time);
   void Calculate_area_of_search();
   void collision_with_arena(std::vector<std::unique_ptr<Tile>>& tiles);
   void calculate_collision_point();
   void calculate_angle();
   sf::Vector2f calculate_vector_velocity(const sf::Time &elapsed_time,float acceleration_);
  //====Getters====//
    sf::Vector2f getcurrent_velocity();
    float getacceleration();
    sf::Vector2f getmax_velocity();
    float getgravity_acceleration();
    bool getgravity();
    bool gethit_top();
    bool gethit_left();
    bool gethit_right();
    bool gethit_bottom();

  //====Setters====//
    void setcurrent_velocity_x(float current_velocity_);
    void setcurrent_velocity_y(float current_velocity_);
    void setacceleration(float acceleration_);
    void setmax_velocity(sf::Vector2f max_velocity_);
    void setgravity_acceleration(float gravity_acceleration_);
    void setgravity(bool gravity_);
    void sethit_top(bool hit_top_);
    void sethit_left(bool hit_left_);
    void sethit_right(bool hit_right_);
    void sethit_bottom(bool hit_bottom_);

};
#endif // PHYSICS_H
