#ifndef TILE_H
#define TILE_H

#include <entity.h>

class Tile : public Entity
{
    friend class Physics;
private:
    int texture_number;
    sf::Vector2f tile_position;
    sf::IntRect roi;
    bool Air = false;
    bool collides = false;

    //===methods===//
    void select_texture(int texture_number_);
public:
    Tile(sf::Vector2f tile_position_,int texture_number_,sf::Vector2f size,sf::Texture &area_textures);
    Tile(sf::Vector2f tile_position_,int texture_number_,sf::Vector2f size,bool Air_);

    //===Setters===//
   void setcollides(bool collides_);
    //===Getters===//
   bool getcollides();
   bool getAir();
};

#endif // TILE_H
