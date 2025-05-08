#include <iostream>
#include <raylib.h>


using namespace std;

Color Dark_Green = Color{20, 160, 133, 255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int cpu_score = 0;


class Ball{
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;

        void Draw() {
            DrawCircle(x, y, radius, Yellow);
        }

        void Update() {
            x += speed_x;
            y += speed_y;
            
            if (y + radius >= GetScreenHeight() || y - radius <= 0) {
                speed_y *= -1;
            }
            if (x + radius >= GetScreenWidth()) //Cpu wins 
            {
                cpu_score++;
                ResetBall();
            }
            if (x - radius <= 0) {
                player_score++;
                ResetBall();
                //speed_x *= -1;
            }
        }

        void ResetBall()
        {
            x = GetScreenWidth()/2;
            y = GetScreenHeight()/2;

            int speed_choices[2] = {-1, 1};
            speed_x *= speed_choices[GetRandomValue(0, 1)];
            speed_y *= speed_choices[GetRandomValue(0, 1)];
        }
};

class Paddle {
    protected:

    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

    public:
        float x, y;
        float width, height;
        int speed;

        void Draw() {
            DrawRectangle(x, y, width, height, WHITE);
        }

        void Update() {
            if(IsKeyDown(KEY_UP)) {
                y = y - speed;
            }
            if(IsKeyDown(KEY_DOWN)) {
                y = y + speed;
            }
            LimitMovement();
        }
};

class CpuPaddle: public Paddle{
    public:

    void Update(int ball_y) {
        if (y + height/2 > ball_y) {
            y = y - speed;
        } 
        if (y + height/2 <= ball_y) {
            y = y + speed;
        }
        LimitMovement();
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main () {
    cout << "Starting the game" << endl;
    const int xdim = 1200;
    const int ydim = 800;
    
    InitWindow(xdim, ydim, "Pong Game Test");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = xdim/2;
    ball.y = ydim/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = xdim - player.width - 10;
    player.y = ydim/2 - player.height/2;
    player.speed = 10;

    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = ydim/2 - cpu.height/2;
    cpu.speed = 5;

    bool exit = false;
    while(!WindowShouldClose()&& exit == false){
        Vector2 mousePos = GetMousePosition();
        bool mouse = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        //bool press = false;
        // dimensions off for button need to fix
        Rectangle start = {500,382,200,50};
        Rectangle quit = {500,482,200,50};
        if(CheckCollisionPointRec(mousePos, start)){
            if(mouse == true){
                break;
            }
        }
        else if (CheckCollisionPointRec(mousePos, quit)){
            if(mouse == true){
            exit = true;
        }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("PONG", 475, 80, 100, WHITE);
        DrawRectangle(500,400,200,50,WHITE);
        DrawRectangle(500, 500, 200, 50, WHITE);
        DrawText("Start", 525, 400, 60,BLACK);
        DrawText("Quit", 525, 495, 60, BLACK);


        EndDrawing();


    }
    if(exit == true){
        CloseWindow();
        return 0;}

    while (WindowShouldClose() == false) {
        BeginDrawing();

        //Updating
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //Checking for collisions
        //need to fix collision to keep ball from not clipping into the paddle
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, 
        Rectangle{player.x, player. y, player.width, player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, 
        Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        //Drawing
        ClearBackground(Dark_Green);
        DrawLine(xdim/2, 0, xdim/2, ydim, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i",cpu_score), xdim/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i",player_score), 3*xdim/4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// int main () {
//     const int SCREEN_WIDTH = 800;
//     const int SCREEN_HEIGHT = 600;
//     int ball_x = 100;
//     int ball_y = 100;
//     int ball_speed_x = 5;
//     int ball_speed_y = 5;
//     int ball_radius = 15;

//     cout << "Hello World" << endl;

//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first RAYLIB program!");
//     SetTargetFPS(60);

//     while (WindowShouldClose() == false){
   
//         ball_x += ball_speed_x;
//         ball_y += ball_speed_y;

//         if(ball_x + ball_radius >= SCREEN_WIDTH || ball_x - ball_radius <= 0)
//         {
//             ball_speed_x *= -1;
//         }

//         if(ball_y + ball_radius >= SCREEN_HEIGHT || ball_y - ball_radius <= 0)
//         {
//             ball_speed_y *= -1;
//         }
        
//         BeginDrawing();
//             ClearBackground(BLACK);
//             DrawCircle(ball_x,ball_y,ball_radius, WHITE);
//         EndDrawing();
//     }

//     CloseWindow();
//}