// SDLtest.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>






struct Worldstate
{



    
};

int checkOutOfBounds(int window_dim, int object_pos, int object_dim)
{
    int flag = 0;
    if (object_pos < 0) return 1;

    if ((object_pos + object_dim) > window_dim) return 2;

    return 0;

    //return 0 = False, 1 = under, 2 = over,
}

void initWorldState(Worldstate & ws)
{







}


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    bool map[1280][640];
    SDL_Window* window = SDL_CreateWindow("Game",100,100,1280,640,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_PRESENTVSYNC);



    int window_width = 1280;  //640,480 old
    int window_height = 640;

    SDL_FRect rect = {640,560,80,80};
    SDL_Rect ball = { 100,100,50,50 };
    

    //cm/s
    float deltav_player = 150;
    //cm/s
    const float deltav_max = 150;
    float ball_vel_x,ball_vel_y;
    int i = 10;
    Uint8 currentkeypressed = 0;
    int lastpressedkey = 0;
    int keypressedfor = 0;
    float jumpingstrength = 1;

    ball_vel_x = (float) (rand() % 100 * 0.02);
    ball_vel_y = (float) (rand() % 100 * 0.02);
    float rect_vel_x = 0;
    float rect_vel_y = 0;
    float accelerationFactor = 1;

    SDL_Surface * lander_image = IMG_Load("img/apollo_lander.png");
    SDL_Surface * lander_engine_on = IMG_Load("img/apollo_lander_engine_on.png");
    SDL_Surface * lander_left = IMG_Load("img/apollo_lander_left.png");
    SDL_Surface * lander_right = IMG_Load("img/apollo_lander_right.png");
    SDL_Surface * lander_down = IMG_Load("img/apollo_lander_down.png");
    SDL_Surface * explosion = IMG_Load("img/explosion_sprite.png");
    SDL_Surface * missile_surf = IMG_Load("img/missile_sprites.png");
    SDL_Texture * lander = SDL_CreateTextureFromSurface(renderer,lander_image);
    SDL_Texture * missile = SDL_CreateTextureFromSurface(renderer, missile_surf);

    while (true)
    {

        SDL_PumpEvents();

        SDL_RenderClear(renderer);

        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        //
        // Zufallsfaktor für Flummi-Beschleunigung
        // 
        // int rng = rand() % 100;
        //if (rng < 7) ball_vel_x += 0.1;
        //else if (rng > 93) ball_vel_y += 0.1;

        ball.x += ball_vel_x;
        ball.y += ball_vel_y;
        rect.x += rect_vel_x;
        rect.y += rect_vel_y;

        if (currentkeypressed == *keystate)
        {
            keypressedfor += 1;
        }
        else
        {
            keypressedfor = 1;
        }

        if (keystate[SDL_SCANCODE_ESCAPE] || (keystate[SDL_SCANCODE_LCTRL] && keystate[SDL_SCANCODE_Q]) || keystate[SDL_SCANCODE_RETURN])
            break;



        i += 2;
        //acceleratorFactor, der längeres Drücken durch stärkere Beschleunigung "belohnt"
        //
        // accelerationFactor = keypressedfor * (0.002);
        if (accelerationFactor >= 10) accelerationFactor = 10;
        //
        //MOmentan nicht eingebaut, daher = 1 
        //
        

        lander = SDL_CreateTextureFromSurface(renderer, lander_image);

        //check if fuel is not empty
        if(deltav_player > 0)
        {
        if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
        {
            rect_vel_x += 0.05 * accelerationFactor;
            lander = SDL_CreateTextureFromSurface(renderer, lander_right);
            deltav_player -= 0.05;
        }

        if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
        {
            rect_vel_x -= 0.05 * accelerationFactor;
            lander = SDL_CreateTextureFromSurface(renderer, lander_left);
            deltav_player -= 0.05;
        }

        if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
        {
            rect_vel_y -= 0.15 * accelerationFactor;
            lander = SDL_CreateTextureFromSurface(renderer, lander_engine_on);
            deltav_player -= 0.05;
        }
        if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
        {
            rect_vel_y += 0.05 * accelerationFactor;
            lander = SDL_CreateTextureFromSurface(renderer, lander_down);
            deltav_player -= 0.05;
        }
    }

        //rect_vel_y += 0.05 * accelerationFactor * (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]);
        if (keystate[SDL_SCANCODE_ESCAPE]) break;










        //check ball
        switch (checkOutOfBounds(window_width, ball.x, ball.w))
        {

        case 1:
        
            ball.x = 0;
            ball_vel_x *= -1;

        case 2:
        
            ball.x = (window_width - ball.w);
            ball_vel_x *= -1;
        
        }


        switch (checkOutOfBounds(window_height, ball.y, ball.h))
        {

        case 1:
            ball.y = 0;
            ball_vel_y *= -1;

        case 2:
            ball.y = (window_height - (ball.h + 1) );
            ball_vel_y *= -1;

        }


        //check rect

        switch (checkOutOfBounds(window_width, rect.x, rect.w))
        {

        case 1:

            rect.x = 0;
            rect_vel_x *= -1;

        case 2:

            rect.x = (window_width - (rect.w + 1));
            rect_vel_x *= -1;

        }



        switch (checkOutOfBounds(window_height, rect.y, rect.h))
        {

        case 1:
            rect.y = 0;
            rect_vel_y *= -1;

        case 2:
            rect.y = (window_height - (rect.h + 1));
            rect_vel_y *= -1;

        }







        if (    ( (ball.y > rect.y) && (ball.y < rect.y + rect.h)  ) && (  (ball.x > rect.x) && (ball.x < (rect.x + rect.w) ) )     )
        {
            accelerationFactor = 0;
            ball_vel_x = 0;
            ball_vel_y = 0;
            lander = SDL_CreateTextureFromSurface(renderer, explosion);
            missile = SDL_CreateTextureFromSurface(renderer, explosion);
            accelerationFactor = 0;

            //Kill condition


        }






        //Check Missile Difference to Lander

        int missle_texture_offset_x = 0;
        int missle_texture_offset_y = 0;

        //ball == missle
        //offsets x/y have to be inverted! 


        char ballxoverrect = 0;
        char ballyoverrect = 0;
        bool ballonx = 0;
        bool ballony = 0;

        //0 = neutral, 1 = yes 2 = no
        if ( (ball.x - rect.x) < (-50) )
        {
            //ball is left of lander
            ballonx = 0;
            ballxoverrect = 2;
        }
        else if ((ball.x - rect.x) || (rect.x - ball.x < 50)  )
        {
            //ball is about vertically over/under lander
            ballonx = 1;
            ballxoverrect = 0;
        }
        else
        {
            ballxoverrect = 1;
            ballonx = 0 ;
            //ball is somewhere right of lander
        }

        if ( (ball.y - rect.y) < (-50) )
        {
            //ball is over lander
            ballyoverrect = 2;
            ballony = 0;
        }
        else if ( ( (ball.y - rect.y) < 50) || ((rect.y - ball.y) < 50) )
        {
            //ball is about as high as lander
            ballyoverrect = 0;
            ballony = 1;

        }
        else
        {
            //ball is under lander
            ballony = 0;
            ballyoverrect = 1;
        }





        if (ballony == 1)
        {
            missle_texture_offset_x = 0;

            if (ballxoverrect == 1)
            {
                missle_texture_offset_y = 0;
                ball_vel_x -= 0.05;
            }

            if (ballxoverrect == 2)
            {
                missle_texture_offset_y = 50;
                ball_vel_x += 0.05;
            }

        }
        else if (ballonx == 1)
        {
            missle_texture_offset_x = 150;
            if (ballyoverrect == 1)
            {
                missle_texture_offset_y = 0;
                ball_vel_y -= 0.05;
            }

            if (ballyoverrect == 2)
            {
                missle_texture_offset_y = 50;
                ball_vel_y += 0.05;
            }
        }
        else
        {
            //ball is over y
            if (ballyoverrect == 1)
            {
                ball_vel_y -= 0.025;
                if (ballxoverrect == 1)
                {
                    ball_vel_x -= 0.025;
                    missle_texture_offset_x = 50;
                    missle_texture_offset_y = 0;

                }
                else
                {
                    ball_vel_x += 0.025;
                    missle_texture_offset_x = 100;
                    missle_texture_offset_x = 50;

                }
            }
            else if (ballyoverrect == 2)
            {

                ball_vel_y += 0.025;

                if (ballxoverrect == 1)
                {
                    ball_vel_x -= 0.025;
                    missle_texture_offset_x = 100;
                    missle_texture_offset_y = 0;

                }
                else
                {
                    ball_vel_x += 0.025;
                    missle_texture_offset_x = 50;
                    missle_texture_offset_x = 50;

                }





            }


            




        }




        ballxoverrect = 0;
        ballyoverrect = 0;
        ballonx = 0;
        ballony = 0;




        if (rect.y < (window_height - rect.h) ) rect_vel_y += 0.05;


       


        //ballrendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        

        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        //SDL_RenderFillRectF(renderer, &rect);

        SDL_RenderFillRect(renderer, &ball);

        
        //Gelaendegenerierung

        for (int i = 0; i < 1280; i++)
        {
            for (int j = 0; j < 640; j++)
            {
                if ((map[i][j] == 1))
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }

        }


        //landerrendering
        SDL_Rect lander_rect = { (int)rect.x , (int)rect.y, (int)rect.w, (int)rect.h };
        SDL_RenderCopy(renderer, lander, NULL, &lander_rect);

        //missilerendering
       
        std::cout << "Vel_Y :" << ball_vel_y << " , Vel_X :" << ball_vel_x << std::endl;

        SDL_Rect Missle_texture = { missle_texture_offset_x, missle_texture_offset_y, 50, 50 };
       


        SDL_RenderCopy(renderer, missile, &Missle_texture , &ball);

        //fuelrendering
        //float tmp = modulo(deltav_max, deltav_player );
        int fuel_indicator = 1 + 50 * (deltav_player / deltav_max);


        SDL_Rect fuel_rect = { 50, 600, (5 * fuel_indicator)  , 20 };
        
        std::cout << "fi: " << fuel_indicator << " | dv: " << deltav_player << std::endl;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        if (fuel_indicator < 10) { SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); }

        SDL_RenderFillRect(renderer, &fuel_rect);


        SDL_SetRenderDrawColor(renderer, 0 , 0 , 0, 255);


        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}





// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
