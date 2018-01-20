//
//  Tile.hpp
//  sfml
//
//  Created by Preston Meade on 10/25/17.
//  Copyright © 2017 com.preston.xc. All rights reserved.
//

#ifndef Tile_h
#define Tile_h

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

using namespace sf;

class Tile{

    int WIDTH = 100;
    int HEIGHT = 100;
public:
    bool empty = false;
    
    RectangleShape twoTile;
    Text textValue;
    Tile(int, int, int, Color, int , int);
    Tile();
    
    void render(RenderWindow & window);
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();
    void update();
    int x;
    int y;
    int value;
};

#endif /* Tile_hpp */
