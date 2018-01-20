//
//  Sort.hpp
//  Color Sort
//
//  Created by Preston Meade on 10/25/17.
//  Copyright © 2017 com.preston.xc. All rights reserved.
//

#ifndef Sort_hpp
#define Sort_hpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sort.hpp"
#include "Tile.hpp"
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include <stdio.h>
#include <vector>

//void bubble(int & arr[]);

using namespace std;

void sortUpTo(int upTo, vector<vector<Color>> & allColors, vector<vector<int>> & allNums);
#endif /* Sort_hpp */
