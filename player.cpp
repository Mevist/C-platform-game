#include "player.h"


//domyslne wymiary player 25/40 albo zmniejsze chyba do <40

Player:: Player(float x_,float y_):
    walking(body_texture,0,187,71,92,3),stand(body_texture,0,0,66,93,1)
{
    starting_position.operator=({x_,y_});         // wpisanie pozycji i wspolrzednych
    size=sf::Vector2f (30,50);
    body.setSize({size});           //srodek obiektu, ustawienie pozycji
    setOrigin();
    body.setPosition(starting_position);

    //====speemed!!====//
    setacceleration(5.0f);
    setmax_velocity({5.0f,7.0f});
    //===gramvity!!====//
    setgravity_acceleration(10.0f); //na sztywno
    sethit_bottom(false);
    sethit_top(false);
    sethit_left(false);
    sethit_right(false);
    setgravity(true);
    //===animation===//
    body_texture.loadFromFile("Textures/Player/p1_walk/p1_walk.png");
    body.setTexture(&body_texture);
    body.setTextureRect(sf::IntRect(0,0,66,93));
    Direction=None;

    object_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body.push_back(std::move(object_ptr));
}

void Player::uptade(const sf::Time &elapsed_time,std::vector<std::unique_ptr<Tile>>& tiles){
     //ustawia krawedzie player
    setEdges();
    calculate_collision_point();    //charakterystyczne dwa punkty graza, wynikajace z roznicy wielkosci tile z wielkoscia player
    Gravity_pull(elapsed_time);
    movement_side_ways(elapsed_time);
    if(gethit_bottom()){  //jump
    movement_jump(elapsed_time);
    }
    animation_handle(elapsed_time);
    move();
    collision_with_arena(tiles);


    object_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body[0].swap(object_ptr);
}

void Player::movement_side_ways(const sf::Time &elapsed_time){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        Direction = Right;
        sethit_left(false);
       if(current_velocity.x <= getmax_velocity().x){
            current_velocity.x += Calculate_current_velocity_x(elapsed_time,getacceleration());
        }
       else if(!gethit_right()){
       setcurrent_velocity_x(getmax_velocity().x);
       }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        Direction = Left;
        sethit_right(false);
       if(current_velocity.x >= -getmax_velocity().x){
            current_velocity.x -= Calculate_current_velocity_x(elapsed_time,getacceleration());
        }
       else if(!gethit_left()){
         setcurrent_velocity_x(-getmax_velocity().x);
       }
    }

  if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
           //warunki hamowania, zalezne od kierunku
        if(current_velocity.x > 0 || Direction == Right ){
         current_velocity.x -= Calculate_current_velocity_x(elapsed_time,getacceleration()); //poki co hamuje po prostu predkosc potem dodac sile tarcia czy cos
            if(current_velocity.x <= 0){
            current_velocity.x = 0;
            Direction=None;
            }
        }
  }

  if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
      if(current_velocity.x < 0 || Direction == Left){
       current_velocity.x += Calculate_current_velocity_x(elapsed_time,getacceleration()); //poki co hamuje po prostu predkosc potem dodac sile tarcia czy cos
          if(current_velocity.x >= 0) {
              current_velocity.x = 0;
              Direction = None;
          }
      }
  }
}

void Player::movement_jump(const sf::Time &elapsed_time){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //gracz jest na ziemi wciska skok,
    if(gethit_bottom()){                            //predkosc zmienia sie na maksymalna pionowa
    current_velocity.y = -getmax_velocity().y;      // zmienia bool na false jako ze jest w powietrzu
    sethit_bottom(false);
    setgravity(true);
    }

    if( (current_velocity.y >= -getmax_velocity().y &&  current_velocity.y < 0 )
        && !gethit_bottom()){  //skok w gore
        current_velocity.y += Calculate_current_velocity_y(elapsed_time,getacceleration());
        }
   }
}

void Player::move(){
    body.move(getcurrent_velocity());
}

void Player::animation_handle(const sf::Time &elapsed_time){
    if(Direction==Right){
        body.setScale({1,1});
        walking.uptade_animation(elapsed_time,body,0.2);
    }
    if(Direction==None){
        stand.uptade_animation(elapsed_time,body,0.3);
    }
    if(Direction==Left){
        body.setScale({-1,1});
        walking.uptade_animation(elapsed_time,body,0.2);
    }

}

//===temp functions===//
