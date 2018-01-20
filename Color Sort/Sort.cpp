//
//  Sort.cpp
//  Color Sort
//
//  Created by Preston Meade on 10/25/17.
//  Copyright © 2017 com.preston.xc. All rights reserved.
//

#include "Sort.hpp"
#include <iostream>


using namespace sf;

using namespace std;

void sortUpTo(int upTo, vector<vector<Color>> & allColors, vector<vector<int>> & allNums){
    for(int r = 0; r < allColors.size() ; r++){
        
        if(upTo < allColors.at(r).size()){
            
            
            for(int i = 0; i < upTo; i++){ // loop through array
                
                int lowest = allNums.at(r).at(i); // lowest is at index i
                
                int indexLowest = i; // the index is saved
                
                for(int j = i; j < allNums.at(0).size(); j++){ // loop from i to length
                    if(allNums.at(r).at(j) < lowest){ // mark that we found a new lowest
                        lowest = allNums.at(r).at(j);
                        indexLowest = j;
                    }
                }
                // if we found lower value than array[i] swap the values at the indexs
                if(lowest < allNums.at(r).at(i)){
                    
                    //swap
                    int temp = allNums.at(r).at(i);
                    Color tempColor = allColors.at(r).at(i);
                    
                    allNums.at(r)[i] = allNums.at(r)[indexLowest];
                    allColors.at(r).at(i) = allColors.at(r).at(indexLowest);
                    
                    
                    allNums.at(r)[indexLowest] = temp;
                    allColors.at(r).at(indexLowest) = tempColor;
                }
            }
        }
    }
}
