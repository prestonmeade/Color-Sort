//
//  Tile.cpp
//  sfml
//
//  Created by Preston Meade on 10/25/17.
//  Copyright © 2017 com.preston.xc. All rights reserved.
//

#include "Tile.hpp"
#include <iostream>
#include <sstream>



Tile::Tile(int xPos, int yPos, int value, Color c, int w, int h){
    x = xPos;
    y = yPos;
    twoTile.setSize(Vector2f(w,h));
    
    twoTile.setPosition(x, y);
    twoTile.setFillColor(c);
  
    std::stringstream ss;
    ss << value;
    
    textValue.setString(ss.str());
    textValue.setFillColor(Color(255, 0, 255));
    
 
    
   // std::cout << "New tile made!" << std::endl;
}



void Tile::update(){
    twoTile.setPosition(x + 100, y);
    textValue.setPosition(x + 30, y + 30);
    std::cout << "moved\b";
    
}

void Tile::render(RenderWindow & window){
     window.draw(twoTile);
   //window.draw(textValue);
}

