#include <raylib.h>
#include <iostream>
#define FPS 60
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

using namespace std;

class Screen {
    private:
        int width = 0;
        int height = 0;
    public:
        Screen(int width, int height){
            this->width = width;
            this->height = height;
        }
        int getWidth(){
            return width;
        }
        int getHeight(){
            return height;
        }
};


Vector2 getSquareClicked(Screen screen){
    Vector2 mousePos = GetMousePosition();
    int width = screen.getWidth();
    int height = screen.getHeight();
    int x = mousePos.x;
    int y = mousePos.y;
    Vector2 clickedSquare = {0, 0};
    if(x > 0 && x <= width/3){
        clickedSquare.x = 1;
    } else if(x > width/3 && x <= width/3*2){
        clickedSquare.x = 2;
    } else if(x > width/3*2 && x <= width){
        clickedSquare.x = 3;
    }

    if(y > 0 && y <= height/3){
        clickedSquare.y = 1;
    } else if(y > height/3 && y <= height/3*2){
        clickedSquare.y = 2;
    } else if(y > height/3*2 && y <= height){
        clickedSquare.y = 3;
    }
    return clickedSquare;    
}

void drawBoard(Screen screen, string boardSquares[3][3]){
    int width = screen.getHeight();
    int height = screen.getHeight();
    Color color = CLITERAL(Color){255, 0, 0, 255};
    // Draw squares
    DrawLine(0, height/3, width, height/3, color);
    DrawLine(0, height/3*2, width, height/3*2, color);
    DrawLine(width/3, 0, width/3, height, color);
    DrawLine(width/3*2, 0, width/3*2, height, color);
    // Draw values
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
        {
            DrawText(boardSquares[j][i].c_str(), 50+i*200, 200*j, 200, BLACK);
        }
    }
}

int testGameState(string boardSquares[3][3]){

    string curChar[2] = {"x", "o"};
    int winner = 0;

    for (int i = 0; i < 2; i++)
    {
        if(
            (boardSquares[0][0] == curChar[i] &&
            boardSquares[1][0] == curChar[i] &&
            boardSquares[2][0] == curChar[i]) ||
            (boardSquares[0][1] == curChar[i] &&
            boardSquares[1][1] == curChar[i] &&
            boardSquares[2][1] == curChar[i]) ||
            (boardSquares[0][2] == curChar[i] &&
            boardSquares[1][2] == curChar[i] &&
            boardSquares[2][2] == curChar[i]) ||
            (boardSquares[0][0] == curChar[i] &&
            boardSquares[0][1] == curChar[i] &&
            boardSquares[0][2] == curChar[i]) ||
            (boardSquares[1][0] == curChar[i] &&
            boardSquares[1][1] == curChar[i] &&
            boardSquares[1][2] == curChar[i]) ||
            (boardSquares[2][0] == curChar[i] &&
            boardSquares[2][1] == curChar[i] &&
            boardSquares[2][2] == curChar[i]) ||
            (boardSquares[0][0] == curChar[i] &&
            boardSquares[1][1] == curChar[i] &&
            boardSquares[2][2] == curChar[i]) ||
            (boardSquares[0][2] == curChar[i] &&
            boardSquares[1][1] == curChar[i] &&
            boardSquares[2][0] == curChar[i])
        ) {
            winner = i+1;
        }
    }
    return winner;
}

int main(){

    Screen screen(SCREEN_HEIGHT, SCREEN_HEIGHT);

    int canClick = 1;
    int clickDelay = 0;
    int playerOfTheTime = 1;

    Color player1Color;
    Color player2Color;

    InitWindow(screen.getWidth(), screen.getHeight(), "Tic Tac Toe");

    SetTargetFPS(FPS);

    string boardSquares[3][3] = {
        " "," "," ",
        " "," "," ",
        " "," "," "
    };

    while (!WindowShouldClose())
    {
        if(clickDelay > 0){
            canClick = 0;
            clickDelay--;
        } else {
            canClick = 1;
        }

        // cout << clickDelay << " - " << canClick << "\n";
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && canClick){
            Vector2 clickedSquare = getSquareClicked(screen);
            string playerChar;
            // cout << "X: " << clickedSquare.x << "\nY: " << clickedSquare.y << "\n";
            if(boardSquares[(int)clickedSquare.y-1][(int)clickedSquare.x-1] == " "){
                if(playerOfTheTime == 1){
                    playerOfTheTime = 2;
                    playerChar = "x";
                } else {
                    playerOfTheTime = 1;
                    playerChar = "o";
                }
                boardSquares[(int)clickedSquare.y-1][(int)clickedSquare.x-1] = playerChar;
            }
            clickDelay = 20;
        }

        int winner = testGameState(boardSquares);
        if(winner != 0){
            cout << "Jogador " << winner << " ganhou!\n";
            break;
        }

        // ---------------------------------------------------------------------
        // DRAW ZONE
        // ---------------------------------------------------------------------

        BeginDrawing();

            if(playerOfTheTime == 1){
                player1Color = BLACK;
                player2Color = LIGHTGRAY;
            } else {
                player2Color = BLACK;
                player1Color = LIGHTGRAY;
            }

            DrawText("Player1 : x", 20, 20, 20, player1Color);
            DrawText("Player2 : o", 20, 40, 20, player2Color);

            ClearBackground(WHITE);
            drawBoard(screen, boardSquares);

        EndDrawing();
    }
    

    return 0;
}
