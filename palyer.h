#pragma once
#define CNT 3

struct player {

    sf::Sprite spr;
    sf::Clock clock;

    int time;
    int jumptime = 600; //time for gravity *= -1
    
    float jmp = 5;
    float grv = 3;
    float def = 3; //gravity old
    
    float x = 0;
    float y = 0;
    float dwnborder = 100;
   
    bool up = false;
    bool ongr = false;

    bool jumpdisable = false;

    bool freeze = false;

    void move(sf::Event event) {
       
        bool once = false;
if(freeze != true){
        time = clock.getElapsedTime().asMilliseconds();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && ongr == true && up == false) {

            once = false;
            
            
            up = true;
            clock.restart();

        }

        if (clock.getElapsedTime().asMilliseconds() <= jumptime && up == true)
        {
            if (y > 50)
            {
                y -= jmp;

            }

            else
                y -= jmp / 3;

            grv = 0;  
        }

        if (clock.getElapsedTime().asMilliseconds() > jumptime)
        {
           
            up = false;

            grv = def;
        }


        if (event.type == sf::Event::KeyReleased)
            once = false;
}
    }

    bool mapinter(sf::RectangleShape sh) {

        if (x + 72 > sh.getPosition().x&& x < sh.getPosition().x + sh.getSize().x - 30 && y + 40 > sh.getPosition().y)
        {
            return true;
        }
    
      
        return false;
    }
       
    void anim() {
        if (freeze != true) {
            spr.setPosition(x, y);
            x = spr.getPosition().x;
            y = spr.getPosition().y;
        }
    }

    int grav(sf::RectangleShape line) {
        int tmp = 0;
        if (freeze == true)
            return 0;
        while (tmp++ <= grv)
        {
            if (y >= dwnborder)
            {
                
                ongr = true;
                return 0;
            }

            else
            {
                y += 1;
                ongr = false;
            }
        }
    return 0; 
        
    }
   
    int create(int gravity,int xtoset,int ytoset,int jtime,int jump,sf::Texture playertexture) {

        def = gravity;
        x = xtoset;
        y = ytoset;
        jumptime = jtime;
        jmp = jump;
        spr.setTexture(playertexture);
        clock.restart();
        up = false;
        ongr = false;
        jumpdisable = false;
        anim();
        return 0;
    }

}pl;


struct entt {

    sf::RectangleShape sh;
    float speed = 2;
    float x = 0;
    float y = 0;
    bool hide = false;

    sf::Clock clock;

    void move() {
        x -= speed;
        clock.restart();
    }

    void anim() {

        sh.setPosition(x, 255 - sh.getSize().y);
        x = sh.getPosition().x;
        y = sh.getPosition().y;
    }
    void an() {

        sh.setPosition(x, y);

    }

    void grav() {

        if (y < 1000)
            y += 10;
    }
}mp[CNT];