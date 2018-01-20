
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Sort.hpp"
#include "Tile.hpp"
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <sstream>
#include <vector>
#include <bitset>


using namespace std;
using namespace sf;

int WIDTH = 1200;
int HEIGHT = 1000;

int colorAreaYoffset = 200;
int colorWidth = WIDTH;
int colorHeight = HEIGHT - colorAreaYoffset;

String status = "loaded";

bool sortNumbers = false;
bool loaded = false;
bool order = false;

bool shuffle = false;

vector<vector<Color>> allColors;
vector<vector<int>> allNums;

int boxSize = 20;
int boxHeight = boxSize;

int maxRows;
int maxCols;
int sameColor = 0;

int sortTo = 0;

double sleepTime = 0.01; // in seconds!


int displayMethod = 0;

Color getRandomColor(){
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    
    return Color(r,g,b);
}

Color getRandomColor(int v){
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    
    if(v == 0){
        g = 0;
        b = 0;
    }else if(v == 1){
        r = 0;
        b = 0;
    }else {
        r = 0;
        g = 0;
    }
    
    return Color(r,g,b);
}

int numValueOfColor(Color c){
    int colorValue = c.toInteger();
    
    int red = (colorValue & 0xFF000000) >> 24;
    int green  = (colorValue & 0x00FF0000) >> 16;
    int blue  = (colorValue & 0x0000FF00) >> 8;
    


    return red + green + blue;
}

int section = 0;
int yCur = 0;

void fillColors(){
    double threshold = maxRows / 3.0;
    cout << "Rows: " << maxRows << endl;
    for(int i = 0; i < maxRows; i++){
        allColors.push_back(vector<Color>());
        allNums.push_back(vector<int>());
        
        if(yCur  > threshold){
            section++;
            yCur = 0;
        }
      
        cout << "t: " << threshold  << " " << section<< endl;

        for(int j = 0; j < maxCols; j++){
            Color c;
            if(order){
                c = getRandomColor(section - 1);

            }else{
                if(::shuffle){
                    c = getRandomColor();
                }else{
                     c = getRandomColor(sameColor);
                }
            }
            allColors.at(i).push_back(c);
            allNums.at(i).push_back(numValueOfColor(c));
            
        }
        yCur++;
    }
    loaded = true;
    yCur = 0;
    section = 0;
   // cout << "Filed colors with: " << allColors.size() << endl;
    //cout << "Filed colors.0 with: " << allColors.at(0).size() << endl;
}

void drawColors(RenderWindow & window){

    for(int i = 0; i < allColors.size(); i++){
        for(int j = 0; j < allColors.at(0).size(); j++){
            Tile t(j * boxSize , i * boxSize + colorAreaYoffset, 1, allColors.at(i).at(j), boxSize, boxHeight);

            t.render(window);

            }
        }
}



void showStatus( RenderWindow & window){
    Text statusLabel;
    
    // Program font
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    String s = status + "\tSpace: Sort\nRight arrow: different board pattern\nUp Arrow: Different rgb\nC: Reset\nR: Random Colors\n0: Flag patter";
    statusLabel.setString(s);
    statusLabel.setColor(Color::White);
    statusLabel.setFont(font);
    statusLabel.setPosition(200, 5);
    window.draw(statusLabel);
    
}

void reset(){
    sortTo = 0;
    allColors.clear();
    allNums.clear();
    fillColors();
    sortNumbers = false;
    loaded = true;
}

void setSortSpeed(int x){
        cout << "on left half\n";
    
    sleepTime = double(x) * (.001);
    
    cout << sleepTime << endl;
    
}

int main(int, char const**){
    srand (time(NULL));
    
    sleepTime = 0.02;

    
    maxRows = colorHeight / boxHeight + 1;
    maxCols = colorWidth / boxSize + 1;
    
    fillColors();
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Color Sort");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    
    window.setKeyRepeatEnabled(false);

    
    // Start the game loop
    while (window.isOpen()){
        
       
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::MouseMoved){
               int x = sf::Mouse::getPosition(window).x;
                cout << "sending x: " << x << endl;
                setSortSpeed(x);
                stringstream ss;
                ss << "Sorting speed ";
                ss << (double(x) * (.001) );
                
               status = ss.str();

            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
          

     
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num0) {
                
                order = !order;
                if(order){
                    status = "Order in rows, rgb";
                }else{
                    status = "Not in order of rgb";
                }

                 reset();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                ::shuffle = !::shuffle;
                 reset();
                if(::shuffle){
                status = "Shuffle colors" ;
                }else{
                    status = "Unshuffled colors";
                }

            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                reset();
                status = "Resetting board";
            }
        
         
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                if(displayMethod == 0){
                    boxHeight = HEIGHT;
                    boxSize = 1;
                    maxRows = HEIGHT / boxHeight + 1;
                    maxCols = WIDTH / boxSize + 1;
                    status = "Use stripped lines";

                }else if (displayMethod == 1){
                    boxSize = 15;
                    boxHeight = 15;
                    maxRows = HEIGHT / boxHeight + 1;
                    maxCols = WIDTH / boxSize + 1;
                    status = "User normal board";

                   
                }else if(displayMethod == 2){
                    boxSize = 30;
                    boxHeight = 30;
                    maxRows = HEIGHT / boxHeight + 1;
                    maxCols = WIDTH / boxSize + 1;
                    status = "Use zoomed board" ;

               
                }else if (displayMethod == 3){
                    boxSize = 3;
                    boxHeight = 3;
                    maxRows = HEIGHT / boxHeight + 1;
                    maxCols = WIDTH / boxSize + 1;
                    status = "Use big board";

                }
                
                reset();
                drawColors(window);
                sortNumbers = false;
                displayMethod++;
                if(displayMethod == 4){
                    displayMethod = 0;
                }
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                sameColor++;
                status = "Changed display type";

                if(sameColor == 3){
                    sameColor = 0;
                }
                reset();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                sortNumbers = !sortNumbers;
                if(sortNumbers){
                    status = "Sorting resumed";
                }else{
                status = "Paused sorting";
                }
            }
        }
        
     
        window.clear();
        
        if(sortNumbers){
            sortUpTo(sortTo, allColors, allNums);
            sortTo++;
            cout << "sleep time: " << sleepTime << endl;
            sf:sleep(sf::seconds(sleepTime)); // Slows cpu from 100% to 1% :)
        }else{
            sf::sleep(sf::seconds(0.05));
        }
        
        
        if(loaded){
            drawColors(window);
        }
        
        showStatus(window);

        window.display();
    
    }

    return EXIT_SUCCESS;
}
