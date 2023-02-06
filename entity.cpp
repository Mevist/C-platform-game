#include "entity.h"

Entity::Entity() {}

void Entity::setOrigin(){
    body.setOrigin(body.getGlobalBounds().width/2,body.getGlobalBounds().height/2);
}


void Entity::setEdges(){
    x_left=body.getPosition().x-body.getLocalBounds().width/2;
    x_right=body.getPosition().x+body.getLocalBounds().width/2;
    y_bottom=body.getPosition().y+body.getLocalBounds().height/2;
    y_top=body.getPosition().y-body.getLocalBounds().height/2;
}

void Entity:: draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto &body : objects_body){
    target.draw(*body);
    }
}


void Entity:: outofwindow(sf::RenderTarget &target){
    setEdges();
    if(y_bottom>=target.getSize().y){ // bottom border
    body.setPosition(body.getPosition().x,target.getSize().y-body.getSize().y/2);
    }

    if(x_right>=target.getSize().x){ // right border
    body.setPosition(target.getSize().x-body.getSize().x/2,body.getPosition().y);
    }

    if(x_left<=0){                  // left border
    body.setPosition(body.getSize().x/2,body.getPosition().y);
    }

    if(y_top<=0){                  // top border
    body.setPosition(body.getPosition().x,body.getSize().y/2);
    }
}
