#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Entity : public sf::Drawable
{
protected:
    //body stuff, edges, origin

    float x_left,x_right;
    float y_bottom,y_top;

    sf::Vector2f size;
    //sprite stuff
    sf::Texture body_texture;
    //Postiton//
    sf::Vector2f starting_position;

 std::unique_ptr<sf::RectangleShape> object_ptr;
    std::vector<std::unique_ptr<sf::RectangleShape>> objects_body;
    //methods//
    void outofwindow(sf::RenderTarget &target);
    void setOrigin();
    void setEdges();
    void setSprite_Origin();
    Entity();

public:
    //friends//
    sf::RectangleShape body;
    //methods//
    virtual ~Entity() = default; // virtual desctructor
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;


};

#endif // ENTITY_H
