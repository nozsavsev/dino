#define _CRT_SECURE_NO_WARNINGS 
#include <SFML/Graphics.hpp> 
#include <SFML/Network.hpp> 
#include <Windows.h> 
#include <random> 
#include <sstream>
#include "palyer.h"
#include "visual.h"

using namespace std;
int main()
{
    printf("Dino SFML by nozsavsev\n");
    Sleep(1000);
    printf("starting dino\n");
    Sleep(500);
    printf("turning off the Internet\n");
    Sleep(1000);

    int rec;
    
    int resumerzz = 0;

    bool ret = false;
    bool rel = false;
    bool sdf = false;
    bool pause = false;
    bool startgame = true;
    bool resumeonse = true;
    int plsp = 0;

    int frame = 0;
    int nw = 0;
  rec = 0;

    float u = 0;

    std::ostringstream record, now;

    sf::RenderWindow window;


    sf::Font font;
    sf::Text text("", font, 20);
    sf::Text stop("to resume press Down",font,75);
   
    stop.setFillColor(rcolor(true));
    stop.setPosition(sf::VideoMode::getDesktopMode().width/3 , sf::VideoMode::getDesktopMode().height / 3);

    sf::Texture tex,shtex;
    sf::Image img,shimg;
    sf::Color bcg = rcolor(true);

    sf::Event event;

    sf::RectangleShape line;

    font.loadFromFile("res//arial.ttf");
    
    rec = readrecord();

    now << nw;
    record << rec;

    text.setString("record:" + record.str() + "now:" + now.str());
    text.setPosition(1500, 10);
    text.setFillColor(sf::Color::White);

    img.loadFromFile("res//dino.png");
    img.createMaskFromColor(sf::Color::White);
    tex.loadFromImage(img);

    shimg.loadFromFile("res//kaktus.png");
    shimg.createMaskFromColor(sf::Color::White);
    shtex.loadFromImage(shimg);
    
    window.create(sf::VideoMode::getDesktopMode(), "", sf::Style::None);
    

    while (1) {

        ShowWindow(GetConsoleWindow(), SW_HIDE);//hide console window

        ret = false; //reset
        rel = false;
        sdf = false;
        pause = false;
        startgame = true;
        frame = 0;
        nw = 0;
        u = 0;

        line.setPosition(0, 255);
        line.setSize(sf::Vector2f(1000, 2));
        line.setFillColor(sf::Color::White);

        for (int i = 0; i < CNT; i++)
        {
            mp[i].x = 700 * (i + 1);
            mp[i].y = 200;
            mp[i].sh.setSize(sf::Vector2f(10, 50));
            mp[i].sh.setFillColor(sf::Color::White);
            mp[i].anim();
            mp[i].hide = false;
            mp[i].speed = 3;
            mp[i].sh.setTexture(&shtex,false);
        }

        

        pl.spr.setTexture(tex);
        pl.spr.setScale(sf::Vector2f(0.1, 0.1));
        pl.dwnborder = 202;
        pl.spr.setColor(sf::Color(2, 201, 201));
        pl.x = 200;

        pl.y = 0;

        pl.def = 2;
        pl.jmp = 5;
        pl.jumptime = 700;

        pl.anim();

        window.setMouseCursorVisible(false);
        window.setFramerateLimit(60);

        while (window.isOpen())//start gui
        {
     



            window.pollEvent(event);

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//exit
            {
                writerecord(rec);
                window.close();
                return 0;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A && rel == false)//random backhround color
            {
                rel = true;
                bcg = rcolor(true);
            }

            if (event.type == sf::Event::KeyReleased)//once change background (without blinking)
                rel = false;


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) //restart 
            {
                pl.def = 3;
                break;
            }
           
            
            
            
            
            if (sdf == true && startgame == false && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && resumeonse == true) //pause 
            { 
                    sdf = false;
                    pause = true;
                    pl.freeze = true;
                    resumeonse = false;
                 
            }

            if(sdf == false && pause == true && startgame == false && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)//resume
            {
                sdf = true;
                pause = false;
                pl.freeze = false;
             

            }

            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                resumeonse = true;
            }


           
            
            
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) //zero the records
            {
                rec = nw = 0;
            }

            if (sdf == false)
            {
                u += 50;
                line.setSize(sf::Vector2f(u, 2));

                pl.move(event);
                pl.grav(line);
                pl.anim();
            }

            if (u > 1930 && startgame == true)
            {
                sdf = true;
                startgame = false;
            }
            if (ret == true)
            {


                frame++;
                if (u > 0) {
                    u -= 100;
                    line.setSize(sf::Vector2f(u, 2));


                    pl.dwnborder = 1000;
                    pl.def = 30;

                    for (int i = 0; i < CNT; i++)
                    {
                        mp[i].grav();
                        mp[i].an();
                    }

                    now.str("");
                    record.str("");
                    now << nw;
                    record << rec;

                    text.setString("record:" + record.str() + "    " + "now:" + now.str());
                }
            }
            if (sdf == true) {
                plsp = nw;

                if (nw > rec)
                    rec = nw;

                nw++;
                now.str("");
                record.str("");
                now << nw;
                record << rec;
                text.setString("record:" + record.str() + "    " + "now:" + now.str());


                pl.move(event);
                pl.grav(line);


                for (int i = 0; i < CNT; i++)
                {


                    mp[i].move();
                    mp[i].anim();

                    if (mp[i].sh.getPosition().x < pl.spr.getPosition().x + 800 && rsd(230, 537) == 256)
                        mp[i].hide = true;

                    if (pl.mapinter(mp[i].sh) == true)
                    {
                        ret = true;
                        sdf = false;
                        bcg = rcolor(false);
                    }

                }

                pl.anim();
                for (int i = 0; i < CNT; i++)
                {
                    if (mp[i].x < (400 * (i + 1))*-1)
                    {
                        mp[i].x = 2000;
                        
                        mp[i].sh.setSize(sf::Vector2f(rsd(60,90), rsd(50, 65)));
                    }
             
                }

                  if (nw % 654 == 0 && pl.jumptime >= 250)
                  {
                        
                        mp[0].speed += 1.5;
                        mp[1].speed += 1.5;
                        mp[2].speed += 1.5;

                        pl.def += 2;
                        pl.jumptime -= 50;
                        pl.jmp += 1;

                  }
               
                
                
            }

                window.clear(bcg);
                window.draw(pl.spr);

                for (int i = 0; i < CNT; i++)
                   
                      window.draw(mp[i].sh);

                window.draw(line);
                window.draw(text);

                if (pause == true)
                    window.draw(stop);

                    window.display();

            

        }
    }
     
    return 0;}
