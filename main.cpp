#include <SFML/Graphics.hpp>
#include <iostream>
#include "block.h"
#include <vector>
#include <time.h>
#include <stdio.h>
#include <signal.h>

using namespace std;

int main()
{
    // Create the main window
     sf::RenderWindow App(sf::VideoMode(960, 640), "Columns");
     sf::View main_view(sf::FloatRect(0, 0, 480, 320));
     App.setView(main_view);

     //draw level
     sf::Texture lvl;
     sf::Sprite sprite_lvl;
     lvl.loadFromFile("sprites/level1.png");
     //lvl.setSmooth(false);

     sprite_lvl.setTexture(lvl);
     sprite_lvl.setPosition(176,0);
     sf::Rect<float> lvl_bottom = sf::Rect<float>(192,288,288,298);
     sf::Texture block_img;
     block_img.loadFromFile("sprites/mons.png");
     block_img.setSmooth(false);
     sf::Texture back;
     sf::Sprite sprite_back;
     back.loadFromFile("sprites/back1.png");
     back.setSmooth(false);
     sprite_back.setTexture(back);
     sf::Texture grass;
     sf::Sprite sprite_grass;
     grass.loadFromFile("sprites/grass.png");
     grass.setSmooth(false);
     sprite_grass.setTexture(grass);
     sf::Texture grid;
     sf::Sprite sprite_grid;
     grid.loadFromFile("sprites/grid.png");
     grid.setSmooth(false);
     sprite_grid.setTexture(grid);
     sprite_grid.setPosition(192,32);


     //Common room properties
     int lvl_rows = 16;
     int lvl_columns = 6;

     //if you press down, you don't want the block to move back and forth
     bool move_block = true;

     //create first block
     bool create = true;
     block current = block();
     block current_2 = block();
     block current_3 = block();
     int c_num = 0;
     //int r_num = 0;
     vector<int> rows_c(6);
     vector< vector<int> > play_matrix;
     vector< vector<block> > block_matrix;

     //Setting up play matrix and block matrix
     play_matrix.resize(lvl_rows);
     for(int i=0; i<lvl_rows; i++)
     {
       play_matrix[i].resize(lvl_columns);
     }

     block_matrix.resize(lvl_rows);
     for(int i=0; i<lvl_rows; i++)
     {
       block_matrix[i].resize(lvl_columns, block());
     }

     for(int i=0; i<lvl_rows; i++)
     {
       for(int j=0; j<lvl_columns; j++)
       {
         play_matrix[i][j]=-1;
       }
     }

     //creating the checking of vertical/horizontal blocks
     vector<vector<int> > hvect(20);
     vector<vector<int> > vvect(20);
     hvect.resize(20);
     for(int i=0; i<20; i++)
     {
        hvect[i].resize(2,-1);
     }
     vvect.resize(20);
     for(int i=0; i<20; i++)
     {
        vvect[i].resize(2,-1);
     }

     //creating the checking of diagnol
     vector<vector<int> > dlrvect(20);
     for(int i=0; i<20; i++)
     {
        dlrvect[i].resize(2,-1);
     }
     vector<vector<int> > drlvect(20);
     for(int i=0; i<20; i++)
     {
        drlvect[i].resize(2,-1);
     }


     while (App.isOpen())
     {

         //Block creation
        if(create)
        {
          current = block(rand() % 6 + 1 );
          current_2 = block( rand() % 6 + 1 );
          current_2.set_y(48);
          current_3 = block(rand() % 6 + 1);
          current_3.set_y(32);
          create = false;
          c_num = 2;
          move_block = true;


          for(int i=0; i<lvl_rows; i++)
          {
            for(int j=0; j<lvl_columns; j++)
            {
              cout << play_matrix[i][j];
            }
            cout << endl;
          }

          //Time to break them blocks that are in the play_matrix and block matrix
        //horizontal, vertical, and diagnol (right to left and left to right)
          for(int i=0; i<5; i++)
          {
            for(int j=0; j<2; j++)
            {
              if(hvect[i][j]!=-1)
              {
                cout << hvect[i][j];
              }
            cout << endl;
            }
          }
        }

        //constantly sets the image loaded earlier to the sprite of the blocks
        //seeing as the image should only be loaded once and the image gets
        //destroyed once it goes out of scope
        current.get_sprite().setTexture(block_img);
        //current.get_sprite().setTextureRect(sf::IntRect(0,0+(16*(current.get_number()-1)),16,16+(16*(current.get_number()-1))));
        current.get_sprite().setTextureRect(sf::IntRect(0,0+(16*(current.get_number()-1)),16,16));
        current_2.get_sprite().setTexture(block_img);
        //current_2.get_sprite().setTextureRect(sf::IntRect(0,0+(16*(current_2.get_number()-1)),16,16+(16*(current_2.get_number()-1))));
        current_2.get_sprite().setTextureRect(sf::IntRect(0,0+(16*(current_2.get_number()-1)),16,16));
        current_3.get_sprite().setTexture(block_img);
        //current_3.get_sprite().setTextureRect(sf::IntRect(0,0+(16*(current_3.get_number()-1)),16,16+(16*(current_3.get_number()-1))));
        current_3.get_sprite().setTextureRect(sf::IntRect(0,0+(16*(current_3.get_number()-1)),16,16));

        //constantly makes my block fall
        current.set_y(current.get_y()+current.get_speed());
        current_2.set_y(current_2.get_y()+current_2.get_speed());
        current_3.set_y(current_3.get_y()+current_3.get_speed());


        //If it intersects with the floor, then save that block to the play matrix
        if(current.get_rect().intersects(lvl_bottom))
        {
          rows_c[c_num] +=3;
          play_matrix[15][c_num]=current.get_number();
          play_matrix[14][c_num]=current_2.get_number();
          play_matrix[13][c_num]=current_3.get_number();
          create = true;
        }
        else{
        //If it collides with another block, update the row at which the current block must be at
        for(int i=0; i<lvl_rows; i++)
        {
          for(int j=0; j<lvl_columns; j++)
          {
            if(play_matrix[i][j]!=-1)
            {
              if(current.get_rect().intersects(block_matrix[i][j].get_rect()))
              {
                rows_c[c_num] +=3;
                play_matrix[16-rows_c[c_num]+2][c_num]=current.get_number();
                play_matrix[16-rows_c[c_num]+1][c_num]=current_2.get_number();
                play_matrix[16-rows_c[c_num]][c_num]=current_3.get_number();
                create = true;
              }
            }
          }
        }
        }

        //Allocate the blocks to the block matrix using the play matrix
        for(int i=0; i<lvl_rows; i++)
        {
          for(int j=0; j<lvl_columns; j++)
          {
            if(play_matrix[i][j]!=-1)
            {
              block_matrix[i][j] = block(play_matrix[i][j]);
              block_matrix[i][j].set_x(192+(16*j));
              block_matrix[i][j].set_y(32+(16*i));
            }
          }
        }

        //The cheking variables
        int hsize = 0;
        int vsize = 0;
        int dlrsize = 0;
        int drlsize=0;
        //The horizontal for loop
        for(int i=0; i<lvl_rows; i++)
        {
          for(int j=0; j< lvl_columns-2; j++)
          {
            if(play_matrix[i][j]!=-1 && play_matrix[i][j+1]!=-1 && play_matrix[i][j+2]!=-1)
            {
              if(block_matrix[i][j].get_number() == block_matrix[i][j+1].get_number() && block_matrix[i][j].get_number()==block_matrix[i][j+2].get_number())
              {
                hvect[hsize][0]=i;
                hvect[hsize][1]=j;
                hsize++;
              }
            }
          }
        }

        //The vertical for loop
        for(int i=0; i<lvl_rows-2; i++)
        {
          for(int j=0; j< lvl_columns; j++)
          {
            if(play_matrix[i][j]!=-1 && play_matrix[i+1][j]!=-1 && play_matrix[i+2][j]!=-1)
            {
              if(block_matrix[i][j].get_number() == block_matrix[i+1][j].get_number() && block_matrix[i][j].get_number()==block_matrix[i+2][j].get_number())
              {
                vvect[vsize][0]=i;
                vvect[vsize][1]=j;
                vsize++;
              }
            }
          }
        }

        //Diagnol checking from the top left to bottom right
        for(int i=0; i<lvl_rows-2; i++)
        {
          for(int j=0; j< lvl_columns-2; j++)
          {
            if(play_matrix[i][j]!=-1 && play_matrix[i+1][j+1]!=-1 && play_matrix[i+2][j+2]!=-1)
            {
              if(block_matrix[i][j].get_number() == block_matrix[i+1][j+1].get_number() && block_matrix[i][j].get_number()==block_matrix[i+2][j+2].get_number())
              {
                dlrvect[dlrsize][0]=i;
                dlrvect[dlrsize][1]=j;
                dlrsize++;
              }
            }
          }
        }

        for(int i=0; i<lvl_rows-2; i++)
        {
          for(int j=lvl_columns-1; j>1; j--)
          {
            if(play_matrix[i][j]!=-1 && play_matrix[i+1][j-1]!=-1 && play_matrix[i+2][j-2]!=-1)
            {
              if(block_matrix[i][j].get_number() == block_matrix[i+1][j-1].get_number() && block_matrix[i][j].get_number()==block_matrix[i+2][j-2].get_number())
              {
                drlvect[drlsize][0]=i;
                drlvect[drlsize][1]=j;
                drlsize++;
              }
            }
          }
        }

         // Process events
         sf::Event Event;
         while (App.pollEvent(Event))
         {
             // Close window : exit
             if (Event.type == sf::Event::Closed)
                 App.close();

             //pressing escape
             if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                 App.close();

             //Moving the block to the left or right.
             if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left) && move_block)
             {
                if(current.get_x()!= 192 && c_num!=0)
                {
                  if(current.get_y()<288-(rows_c[c_num-1]*16))
                  {
                    current.set_x(current.get_x()-16);
                    current_2.set_x(current_2.get_x()-16);
                    current_3.set_x(current_3.get_x()-16);
                    if(c_num!=0)
                    {
                      c_num -= 1;
                    }
                  }
                }
             }

             if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right) && move_block)
             {
                if(current.get_x()!= 272 && c_num != 5)
                {
                  if(current.get_y()<288-(rows_c[c_num+1]*16))
                  {
                    current.set_x(current.get_x()+16);
                    current_2.set_x(current_2.get_x()+16);
                    current_3.set_x(current_3.get_x()+16);
                    if(c_num!=5)
                    {
                      c_num+=1;
                    }
                  }
                }
             }

             //Speeding up the falling block
             if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
             {
                current.set_speed(1.5);
                current_2.set_speed(1.5);
                current_3.set_speed(1.5);
                move_block = false;
             }

             if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
             {
                int temp = current.get_number();
                current.set_number(current_3.get_number());
                current_3.set_number(current_2.get_number());
                current_2.set_number(temp);
             }


         }
         // Clear screen
         App.clear();

         //draw sprite
         App.draw(sprite_back);
         App.draw(sprite_grass);
         App.draw(sprite_lvl);
         App.draw(sprite_grid);
         App.draw(current.get_sprite());
         App.draw(current_2.get_sprite());
         App.draw(current_3.get_sprite());

         //drawing block in the block matrix
         for(int i=0; i< lvl_rows; i++)
         {
           for(int j=0; j<lvl_columns; j++)
           {
             if(play_matrix[i][j]!=-1)
             {
               block_matrix[i][j].get_sprite().setTexture(block_img);
               block_matrix[i][j].get_sprite().setTextureRect(sf::IntRect(0,0+(16*(block_matrix[i][j].get_number()-1)),16,16));
               App.draw(block_matrix[i][j].get_sprite());
             }
           }
         }

         // Update the window
         App.display();
     }

     return EXIT_SUCCESS;
}


