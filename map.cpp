#include "map.h"

Map::Map(std::string mapfile_path_,std::string maptiles_path_): mapfile_path(mapfile_path_),maptiles_path(maptiles_path_)
{
    size.operator=({40,40});
    loaded_map.open(mapfile_path,std::fstream::in | std::fstream::out | std::fstream::app);
    if(!loaded_map.is_open()){
       printf("error, map not loaded\n");
    }
    else
       printf("Map loaded\n");
    if(maptiles.loadFromFile(maptiles_path + "arena.png")){
        printf("textures loaded\n");
    }
    else{
        printf("erorr\n");
    }

}

void Map::Initialize_map(sf::RenderTarget &window){
    read_data_from_file();
    setbackgroundsettings(window);
    //Setup_tiles();
}

void Map::read_data_from_file(){
    while(!getline(loaded_map,find_line,'|').eof()){

        if(find_line.compare("\nBACKGROUND_TEXTURE") == 0){
          getline(loaded_map,find_line,'|');
            if(background_texture.loadFromFile(maptiles_path+find_line)){
              printf("background loaded\n");
          }

        }
        if(find_line.compare("\nTILE") == 0){
           //-----------------------------------------// //wczytanie danych z pliku map
              read_data_line();
           //-----------------------------------------// //przeformatowanie danych
              convert_data();
           //------------------------------------------// tworzenie obiektu klasy tile
              create_tile(false);
        }
        if(find_line.compare("\nTILE_AIR") == 0){
           //-----------------------------------------// //wczytanie danych z pliku map
              read_data_line();
           //-----------------------------------------// //przeformatowanie danych
              convert_data();
           //------------------------------------------// tworzenie obiektu klasy tile
              create_tile(true);
       }
        if(find_line.compare("\tTILE") == 0){
           //-----------------------------------------// //wczytanie danych z pliku map
              read_data_line();
           //-----------------------------------------// //przeformatowanie danych
              convert_data();
           //------------------------------------------// tworzenie obiektu klasy tile
              create_tile(false);
        }
        if(find_line.compare("\tTILE_AIR") == 0){
           //-----------------------------------------// //wczytanie danych z pliku map
              read_data_line();
           //-----------------------------------------// //przeformatowanie danych
              convert_data();
           //------------------------------------------// tworzenie obiektu klasy tile
              create_tile(true);
        }
    }
}

sf::Vector2f Map::Calculate_tile_position_(sf::Vector2i &tile_position_number){
    sf::Vector2f temp_position;
    temp_position.x = size.x/2 + tile_position_number.x*size.x;
    temp_position.y = size.y/2 + tile_position_number.y*size.y;
    return temp_position;
}

void Map::read_data_line(){
    //-----------------------------------------// //wczytanie danych z pliku map
    getline(loaded_map,tile_x_,'|');
    getline(loaded_map,tile_y_,'|');
    getline(loaded_map,texture_number_,'|');
}

void Map::convert_data(){
    //-----------------------------------------// //przeformatowanie danych
    tile_position_number.x = std::stoi(tile_x_);
    tile_position_number.y = std::stoi(tile_y_);
    texture_number = std::stoi(texture_number_);
}

void Map::create_tile(bool Air_){
    //------------------------------------------// tworzenie obiektu klasy tile
    if(Air_){
    auto new_tile = std::make_unique<Tile>(Calculate_tile_position_(tile_position_number),texture_number,size,Air_);
    Tiles.push_back(std::move(new_tile));
    }
    else
    {
    auto new_tile = std::make_unique<Tile>(Calculate_tile_position_(tile_position_number),texture_number,size,maptiles);
    Tiles.push_back(std::move(new_tile));
    }

}

void Map::setbackgroundsettings(sf::RenderTarget &window){
    background.setPosition(0,0);
    background_texture.setRepeated(true);
    background.setTexture(background_texture);
    background.setTextureRect(sf::IntRect(0,0,window.getSize().x,window.getSize().y));

}
//====Getters====//
std::vector<std::unique_ptr<Tile>>& Map::getTiles() {
    return Tiles;
}
sf::Sprite Map::getbackground_texture(){
    return background;
}
