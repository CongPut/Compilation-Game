#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include <cstdio>
#include <windows.h>

#define sizeR 20
#define sizeC 40

#define CLR_YEL "\e[0;36m"
#define CLR_WHT "\e[0;37m"
void mainPage();
void ascii_mainMenu();
void ascii_mainMenuAnimated();
void catchs();
void setup();
void draw();
void input();
void logic();
void level1();
void endGameLevel1();
void level2();
void endGameLevel2();
void level3();
void endGameLevel3();
void delay();
void ascii_logIn();
void ascii_newPlayer();
void ascii_catchAsterisk();
void ascii_miniArcade();
void inputUsername();
void inputPassword();
void newPlayer();
void logInPlayer();
void logIn();
void rulesAsterisk();
void menuAsterisk();
void ascii_riddleGame();
void rulesRiddle();
void menuRiddle();
void menuSnake();
void rulesSnake();
void reset_screen_position();
void board();
void remove_tail();
void snake_movement();
void game_over();
void random_food();
void make_snake();
int input_key();
void ascii_snakeGame();
void readScoreBoard();
void writeScoreBoard();
void updateScoreBoard(int scoreZ);
void showScoreBoard();
void frequencyPlay();
int countSnake = 0, countRiddle = 0, countAsterisk = 0;
struct data
{
    char name[41];
    long int num;
};
int icatch,
    jcatch, heightcatch = 20, widthcatch = 20, gameovercatch, scorecatch;
int xcatch, ycatch, buahxcatch, buahycatch, flagcatch, difficultycatch;
struct riddle_data
{
    char riddle_soal[200];
    char riddle_answer[100];
    char riddle_PG;
} soal1[10], soal2[10], soal3[10];
int riddle_score = 0;
int score_temp = 0;
bool flag[10] = {};
char username[21];
char passwords[21];
int scoreFinal = 0;
int map_value[sizeR][sizeC];
int snake_head, snake_tail;
int snake_x, snake_y, snake_gy;
int snake_food, snake_foodX, snake_foodY;
int snake_game;
int snake_key, snake_direction;
int snake_score = 0, snake_highscore = 0, snake_speed;
FILE *snake_nilai;

int main(void)
{
    ascii_mainMenuAnimated();
    logIn();
    return 0;
}

void frequencyPlay()
{

    struct data allData[3];

    allData[0].num = countRiddle;
    allData[1].num = countSnake;
    allData[2].num = countAsterisk;

    strcpy(allData[0].name, "Riddle Game");
    strcpy(allData[1].name, "Snake Game");
    strcpy(allData[2].name, "Catch Asterisk Game");

    int temp_num = 0;
    int j, k;
    char temp[41];
    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3 - 1 - j; k++)
        {
            if (allData[k].num < allData[k + 1].num)
            {
                struct data temp = allData[k];
                allData[k] = allData[k + 1];
                allData[k + 1] = temp;
            }
        }
    }

    int l;
    for (l = 0; l < 3; l++)
    {
        printf("%d %s\n", allData[l].num, allData[l].name);
    }

    puts("\n\nPress enter to continue");

    char input;
    input = _getche();

    if (input == '\x0D')
    {
        system("CLS");
        mainPage();
    }
}

void showScoreBoard()
{
    system("CLS");
    char usernameNow[101][21];
    int scoreSB[101];
    int count = 0;

    FILE *fp = fopen("scoreboard.txt", "r");

    for (char c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n')
        {
            count++;
        }
    }
    fclose(fp);

    FILE *fp2 = fopen("scoreboard.txt", "r");
    for (int i = 0; i < count; i++)
    {
        fscanf(fp2, "%[^#]#%d\n", usernameNow[i], &scoreSB[i]);
        printf("%s %d\n", usernameNow[i], scoreSB[i]);
    }
    fclose(fp2);

    puts("\n\nPress enter to continue");
    char input;
    input = _getche();
    if (input == '\x0D')
    {
        system("CLS");
        mainPage();
    }
}

void writeScoreBoard()
{
    FILE *fp = fopen("scoreboard.txt", "a");
    fprintf(fp, "%s#%d\n", username, scoreFinal);
    fclose(fp);
}

void updateScoreBoard(int scoreZ)
{
    FILE *fp = fopen("scoreboard.txt", "a");
    fprintf(fp, "%s#%d\n", username, scoreZ);
    fclose(fp);
}

void readScoreBoard()
{
    char usernameNow[101][21];
    int scoreSB[101];
    int count = 0;
    FILE *fp = fopen("scoreboard.txt", "r");

    for (char i; i != EOF; i = getc(fp))
    {
        fscanf(fp, "%[^#]#%[^\n]", usernameNow[count], scoreSB[count]);
        count++;
    }

    int comparation = 0;

    for (int i = 0; i < count; i++)
    {
        if ((strcmp(username, usernameNow[i])) == 0)
        {
            updateScoreBoard(scoreFinal);
        }
    }

    fclose(fp);
}

void menuSnake()
{
    system("CLS");
    ascii_snakeGame();
    printf("%s> Guide for new players <%s\n", CLR_YEL, CLR_WHT);
    printf("Play Game\nBack\n");

    char input;
    char texts[4][30] = {"Guide for new players", "Play Game", "Back"};
    int inputChoice = 0;

    for (int i = 0;; i++)
    {

        input = _getche();
        system("CLS");
        ascii_snakeGame();
        // printf("Do you want to play again?\n");
        if (input == 's')
        {
            inputChoice++;
        }
        else if (input == 'w')
        {
            inputChoice--;
        }

        if (inputChoice < 0)
        {
            inputChoice = 0;
        }
        else if (inputChoice > 2)
        {
            inputChoice = 2;
        }

        if (input == '\x0D' && inputChoice == 0)
        {
            system("CLS");
            rulesSnake();
        }
        else if (input == '\x0D' && inputChoice == 1)
        {
            system("CLS");
            countSnake++;
            make_snake();

            while (snake_game == 0)
            {
                board();
                reset_screen_position();
                random_food();
                snake_movement();
                remove_tail();
                Sleep(snake_speed);
            }
        }
        else if (input == '\x0D' && inputChoice == 2)
        {
            mainPage();
        }

        for (int i = 0; i < 3; i++)
        {

            if (i != inputChoice)
            {
                printf("%s\n", texts[i]);
            }
            else
            {
                printf("%s> %s <%s\n", CLR_YEL, texts[inputChoice], CLR_WHT);
            }
        }
    }
}

void rulesSnake()
{
    printf("1. Move the snake with WASD key on keyboard\n");
    printf("2. Move the snake to eat the food\n");
    printf("3. Every time you eat the food, you got point and the snake is getting longer\n");
    printf("4. Snake die if the snake hit his own body\n");
    printf("5. When the snake is die, game is over\n");

    puts("\n\nPress enter to continue");

    char input;
    input = _getche();

    if (input == '\x0D')
    {
        system("CLS");
        menuSnake();
    }
}

void reset_screen_position()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void board()
{
    // upper board
    for (int i = 0; i <= sizeC + 1; i++)
    {
        // sudut kiri
        if (i == 0)
        {
            printf("%c", 201);
        }
        // sudut kanan
        else if (i == sizeC + 1)
        {
            printf("%c", 187);
        }
        // sisi atas
        else
        {
            printf("%c", 205);
        }
    }
    printf("     Current score: %d Highscore: %d", snake_score, snake_highscore);
    printf("\n");
    // middle board
    for (int i = 0; i < sizeR; i++)
    {
        // sisi kiri(tembok)
        printf("%c", 186);
        for (int j = 0; j < sizeC; j++)
        {
            // lapangan kosong
            if (map_value[i][j] == 0)
            {
                printf(" ");
            }

            // display tail
            if (map_value[i][j] > 0 && map_value[i][j] != snake_head)
            {
                printf("*");
            }
            // display head
            if (map_value[i][j] == snake_head)
            {
                printf("%c", 178);
            }
            // display snake_food
            if (map_value[i][j] == -1)
            {
                printf("%c", 15);
            }
            // sisi kanan (tembok)
            if (j == sizeC - 1)
            {
                printf("%c\n", 186);
            }
        }
    }

    // bottom
    for (int i = 0; i <= sizeC + 1; i++)
    {
        // sudut kiri
        if (i == 0)
        {
            printf("%c", 200);
        }
        // sudut kanan
        else if (i == sizeC + 1)
        {
            printf("%c", 188);
        }
        // sisi bawah
        else
        {
            printf("%c", 205);
        }
    }
}

void remove_tail()
{
    for (int i = 0; i < sizeR; i++)
    {
        for (int j = 0; j < sizeC; j++)
        {
            if (map_value[i][j] == snake_tail)
            {
                map_value[i][j] = 0;
            }
        }
    }
    snake_tail++;
}

void snake_movement()
{
    snake_key = input_key();
    snake_key = tolower(snake_key);
    // wasd key
    if (((snake_key == 'd' || snake_key == 'a') || (snake_key == 'w' || snake_key == 's')) && (abs(snake_direction - snake_key) > 5))
    {
        snake_direction = snake_key;
    }

    // right
    if (snake_direction == 'd')
    {
        snake_y++;

        // condition when snake touch his own body
        if (map_value[snake_x][snake_y] != 0 && map_value[snake_x][snake_y] != -1)
        {
            game_over();
        }
        // condition when snake eat the food
        if (map_value[snake_x][snake_y] == -1)
        {
            snake_food = 0;
            snake_score += 5;
            snake_tail -= 2;
        }

        if (snake_y == sizeC - 1)
        {
            snake_y = 0;
        }
        snake_head++;
        map_value[snake_x][snake_y] = snake_head;
    }
    // left
    if (snake_direction == 'a')
    {
        snake_y--;
        if (snake_y == 0)
        {
            snake_y = sizeC - 1;
        }
        // condition when snake touch his own body
        if (map_value[snake_x][snake_y] != 0 && map_value[snake_x][snake_y] != -1)
        {
            game_over();
        }
        // condition when snake eat the food
        if (map_value[snake_x][snake_y] == -1)
        {
            snake_food = 0;
            snake_score += 5;
            snake_tail -= 2;
        }
        snake_head++;
        map_value[snake_x][snake_y] = snake_head;
    }
    // down
    if (snake_direction == 's')
    {
        snake_x++;
        if (snake_x == sizeR - 1)
        {
            snake_x = 0;
        }
        // condition when snake touch his own body
        if (map_value[snake_x][snake_y] != 0 && map_value[snake_x][snake_y] != -1)
        {
            game_over();
        }
        // condition when snake eat the food
        if (map_value[snake_x][snake_y] == -1)
        {
            snake_food = 0;
            snake_score += 5;
            snake_tail -= 2;
        }
        snake_head++;
        map_value[snake_x][snake_y] = snake_head;
    }
    // up
    if (snake_direction == 'w')
    {
        snake_x--;
        if (snake_x == 0)
        {
            snake_x = sizeR - 1;
        }
        // condition when snake touch his own body
        if (map_value[snake_x][snake_y] != 0 && map_value[snake_x][snake_y] != -1)
        {
            game_over();
        }
        // condition when snake eat the food
        if (map_value[snake_x][snake_y] == -1)
        {
            snake_food = 0;
            snake_score += 5;
            snake_tail -= 2;
        }

        snake_head++;
        map_value[snake_x][snake_y] = snake_head;
    }
}

void game_over()
{
    // make the game end
    Sleep(1500);
    system("Cls");

    // check if it is highscore
    if (snake_score > snake_highscore)
    {
        printf(" New HighScore %d!!!!\n", snake_score);
        system("pause");
        // write the highscore in a file
        snake_nilai = fopen("Highscore.txt", "w");
        fprintf(snake_nilai, "%d", snake_score);
        fclose(snake_nilai);
    }
    system("Cls");
    printf("\n\n     GAME OVER !!!!\n");
    printf("---------------------------------------\n");
    printf("     Score : %d\n\n", snake_score);
    printf("     Press Enter to continue...\n");
    scoreFinal += snake_score;
    snake_score = 0;

    char input;
    input = _getche();

    if (input == '\x0D')
    {
        system("CLS");
        menuSnake();
    }

    snake_game = 1;
}

void random_food()
{
    srand(time(0));
    snake_foodX = rand() % 18 + 1;
    snake_foodY = rand() % 38 + 1;

    if (snake_food == 0 && map_value[snake_foodX][snake_foodY] == 0)
    {
        map_value[snake_foodX][snake_foodY] = -1;
        snake_food = 1;
        if (snake_speed > 10 && snake_score != 0)
        {
            snake_speed = snake_speed - 5;
        }
    }
}

void make_snake()
{
    // membaca file highscore
    snake_nilai = fopen("Highscore.txt", "r");
    fscanf(snake_nilai, "%d", &snake_highscore);
    fclose(snake_nilai);
    // set each coordinate map value into 0
    for (int i = 0; i < sizeR; i++)
    {
        for (int j = 0; j < sizeC; j++)
        {
            map_value[i][j] = 0;
        }
    }

    // snake game start position
    snake_x = sizeR / 2;
    snake_y = sizeC / 2;
    snake_gy = snake_y;
    snake_game = 0;
    snake_head = 5;
    snake_tail = 1;
    snake_food = 0;
    snake_direction = 'd';
    snake_speed = 75;
    // declare the tail
    for (int i = 0; i < snake_head; i++)
    {
        snake_gy++;
        map_value[snake_x][snake_gy - snake_head] = i + 1;
    }
}

int input_key()
{
    if (kbhit())
    {
        return _getch();
    }
    else
    {
        return -1;
    }
}

void logInPlayer()
{
    system("CLS");
    ascii_logIn();
    FILE *fp = fopen("password.txt", "r");

    char usernameNow[101][21];
    char passwordNow[101][21];
    char passwordCheck[21];
    int count = 0;

    for (char i; i != EOF; i = getc(fp))
    {
        fscanf(fp, "%[^#]#%[^\n]", usernameNow[count], passwordNow[count]);
        count++;
    }

    inputUsername();
    int comparation = 0;

    for (int i = 0; i < count; i++)
    {
        if ((strcmp(username, usernameNow[i])) == 0)
        {
            strcpy(passwordCheck, passwordNow[i]);
            comparation = 1;
        }
    }

    if (comparation == 1)
    {
        inputPassword();

        if ((strcmp(passwordCheck, passwords)) != 0)
        {
            logInPlayer();
        }
        else
        {
            mainPage();
        }
    }
    else
    {
        system("CLS");
        printf("Your username can not be found, make new account.\n");
        newPlayer();
    }

    fclose(fp);
}

void logIn()
{
    system("CLS");
    ascii_mainMenu();
    printf("%s> New Player <%s\n", CLR_YEL, CLR_WHT);
    printf("Log In");

    char input;
    char logins[3][30] = {"New Player", "Log In"};
    int inputChoice = 0;

    for (int i = 0;; i++)
    {

        input = _getche();
        system("CLS");
        ascii_mainMenu();

        if (input == 's')
        {
            inputChoice++;
        }
        else if (input == 'w')
        {
            inputChoice--;
        }

        if (inputChoice < 0)
        {
            inputChoice = 0;
        }
        else if (inputChoice > 1)
        {
            inputChoice = 1;
        }

        if (input == '\x0D' && inputChoice == 0)
        {
            system("CLS");
            newPlayer();
        }
        else if (input == '\x0D' && inputChoice == 1)
        {
            system("CLS");
            logInPlayer();
        }

        for (int i = 0; i < 2; i++)
        {

            if (i != inputChoice)
            {
                printf("%s\n", logins[i]);
            }
            else
            {
                printf("%s> %s <%s\n", CLR_YEL, logins[inputChoice], CLR_WHT);
            }
        }
    }
}

void newPlayer()
{
    ascii_newPlayer();
    FILE *fp = fopen("password.txt", "r");
    char usernameCheck[101][21];
    char passwordCheck[101][21];
    int count = 0;
    inputUsername();

    for (char i; i != EOF; i = getc(fp))
    {
        fscanf(fp, "%[^#]#%[^\n]", usernameCheck[count], passwordCheck[count]);
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        if (strcmp(usernameCheck[i], username) == 0)
        {
            system("CLS");
            printf("This username has been taken, please make a new one.\n");
            newPlayer();
        }
    }

    fclose(fp);

    FILE *fp2 = fopen("password.txt", "a");
    // inputUsername();
    inputPassword();
    fprintf(fp2, "%s#%s\n", username, passwords);
    fclose(fp2);
    mainPage();
}

void inputUsername()
{
    printf("Enter your username (min. 3 letters): ");
    scanf("%s", username);

    int len = strlen(username);

    if (len < 3)
    {
        system("CLS");
        printf("Your username is not longer than 3 letters!\n");
        inputUsername();
    }
}

void inputPassword()
{

    printf("Enter your password (min. 6 letters): ");
    int p = 0;
    do
    {
        passwords[p] = getch();
        if (passwords[p] != '\r')
        {
            printf("*");
        }
        p++;
    } while (passwords[p - 1] != '\r');
    passwords[p - 1] = '\0';
    getchar();
    int len = strlen(passwords);
    if (len < 6)
    {
        system("CLS");
        printf("Username: %s\n", username);
        printf("\nYour password is not longer than 6 letters or it does not match!\n");
        inputPassword();
    }
}

void mainPage()
{
    system("CLS");
    ascii_miniArcade();
    printf("%s> Riddle Game <%s\n", CLR_YEL, CLR_WHT);
    printf("Snake Game\nCatch the Asterisk Game\nScoreboard\nGame Frequency\nExit\n");

    char input;
    char mainMenu[6][30] = {"Riddle Game", "Snake Game", "Catch the Asterisk Game", "Scoreboard", "Game Frequency", "Exit"};
    int now = 0;

    for (int i = 0;; i++)
    {

        input = _getche();
        system("CLS");

        if (input == 's')
        {
            now++;
        }
        else if (input == 'w')
        {
            now--;
        }

        if (now < 0)
        {
            now = 0;
        }
        else if (now > 5)
        {
            now = 5;
        }

        if (input == '\x0D' && now == 0)
        {

            menuRiddle();
        }
        else if (input == '\x0D' && now == 1)
        {

            menuSnake();
        }
        else if (input == '\x0D' && now == 2)
        {

            menuAsterisk();
        }
        else if (input == '\x0D' && now == 3)
        {
            writeScoreBoard();
            showScoreBoard();
        }
        else if (input == '\x0D' && now == 4)
        {
            frequencyPlay();
        }
        else if (input == '\x0D' && now == 5)
        {
            exit(1);
        }

        ascii_miniArcade();

        for (int i = 0; i < 6; i++)
        {

            if (i != now)
            {
                printf("%s\n", mainMenu[i]);
            }
            else
            {
                printf("%s> %s <%s\n", CLR_YEL, mainMenu[now], CLR_WHT);
            }
        }
    }
}

void rulesRiddle()
{
    printf("1. Choose the correct answer from the given options\n2. For each correct answer is worth +10 and each wrong answer is worth -5\n3. You have to collect as many points as specified to continue to the next level\n4. The game is over if you managed to conquer level 3\n5. Enjoy!");
    puts("\n\nPress enter to continue");

    char input;
    input = _getche();

    if (input == '\x0D')
    {
        system("CLS");
        menuRiddle();
    }
}

void menuRiddle()
{
    system("CLS");
    ascii_riddleGame();
    printf("%s> Guide for new players <%s\n", CLR_YEL, CLR_WHT);
    printf("Play Game\nBack\n");

    char input;
    char texts[4][30] = {"Guide for new players", "Play Game", "Back"};
    int inputChoice = 0;

    for (int i = 0;; i++)
    {

        input = _getche();
        system("CLS");
        ascii_riddleGame();
        // printf("Do you want to play again?\n");
        if (input == 's')
        {
            inputChoice++;
        }
        else if (input == 'w')
        {
            inputChoice--;
        }

        if (inputChoice < 0)
        {
            inputChoice = 0;
        }
        else if (inputChoice > 2)
        {
            inputChoice = 2;
        }

        if (input == '\x0D' && inputChoice == 0)
        {
            system("CLS");
            rulesRiddle();
        }
        else if (input == '\x0D' && inputChoice == 1)
        {
            system("CLS");
            countRiddle++;
            level1();
        }
        else if (input == '\x0D' && inputChoice == 2)
        {
            mainPage();
        }

        for (int i = 0; i < 3; i++)
        {

            if (i != inputChoice)
            {
                printf("%s\n", texts[i]);
            }
            else
            {
                printf("%s> %s <%s\n", CLR_YEL, texts[inputChoice], CLR_WHT);
            }
        }
    }
}

void rulesAsterisk()
{
    printf("1. Use W, A, S, D to move up, left, down, and right\n2. Do not hit the border\n3. Catch as many asterisks as possible\n4. The more asterisks you catch, the more points you will get\n5. Have Fun!");
    puts("\n\nPress enter to continue");

    char input;
    input = _getche();

    if (input == '\x0D')
    {
        system("CLS");
        menuAsterisk();
    }
}

void menuAsterisk()
{
    system("CLS");
    ascii_catchAsterisk();
    printf("%s> Guide for new players <%s\n", CLR_YEL, CLR_WHT);
    printf("Play Game\nBack\n");

    char input;
    char texts[4][30] = {"Guide for new players", "Play Game", "Back"};
    int inputChoice = 0;

    for (int i = 0;; i++)
    {

        input = _getche();
        system("CLS");
        ascii_catchAsterisk();
        // printf("Do you want to play again?\n");
        if (input == 's')
        {
            inputChoice++;
        }
        else if (input == 'w')
        {
            inputChoice--;
        }

        if (inputChoice < 0)
        {
            inputChoice = 0;
        }
        else if (inputChoice > 2)
        {
            inputChoice = 2;
        }

        if (input == '\x0D' && inputChoice == 0)
        {
            system("CLS");
            rulesAsterisk();
        }
        else if (input == '\x0D' && inputChoice == 1)
        {
            countAsterisk++;
            catchs();
        }
        else if (input == '\x0D' && inputChoice == 2)
        {
            mainPage();
        }

        for (int i = 0; i < 3; i++)
        {

            if (i != inputChoice)
            {
                printf("%s\n", texts[i]);
            }
            else
            {
                printf("%s> %s <%s\n", CLR_YEL, texts[inputChoice], CLR_WHT);
            }
        }
    }
}

void endGameLevel3()
{
    printf("--------------------------------------------------------------------\n");
    printf("Your score is %d\n", riddle_score);
    char riddle_gameOver_level3;
    if (riddle_score > 165)
    {
        printf("Congratulations you successfully finished the game! Press 'X' to exit the game!\n");
        scanf("%c", &riddle_gameOver_level3);
        getchar();
    }
    else
    {
        printf("Game Over! press 'R' to try again or 'X' to exit the game! \n");
        scanf("%c", &riddle_gameOver_level3);
        getchar();
    }

    for (int i = 0; i < 10; i++)
    {
        flag[i] = 0;
    }
    if (riddle_gameOver_level3 >= 'A' && riddle_gameOver_level3 <= 'Z')
    {
        riddle_gameOver_level3 += 32;
    }

    switch (riddle_gameOver_level3)
    {
    case 'r':
        riddle_score = score_temp;
        system("CLS");
        level3();
        break;
    case 'x':
        printf("Thank you for playing!\n");
        system("CLS");
        menuRiddle();
        break;
    }

    scoreFinal += riddle_score;
}

void level3()
{
    strcpy(soal3[0].riddle_soal, "What travels all around the world and stays in a corner?");
    strcpy(soal3[0].riddle_answer, "\nA. A car\nB. A stamp\nC. Rollercoaster\nD. A plane\n");
    soal3[0].riddle_PG = 'b';

    strcpy(soal3[1].riddle_soal, "What has four wheels and flies?");
    strcpy(soal3[1].riddle_answer, "\nA. A flying car\nB. A unicorn\nC. A garbage truck\nD. A pegasus\n");
    soal3[1].riddle_PG = 'c';

    strcpy(soal3[2].riddle_soal, "The more you take, the more you leave behind. What am I?");
    strcpy(soal3[2].riddle_answer, "\nA. time\nB. A hand watch\nC. footsteps\nD. Age\n");
    soal3[2].riddle_PG = 'c';

    strcpy(soal3[3].riddle_soal, "I go in hard. I come out soft. You blow me hard. What am I?");
    strcpy(soal3[3].riddle_answer, "\nA. candy\nB. Gum\nC. Lollipop\nD. Cotton Candy\n");
    soal3[3].riddle_PG = 'b';

    strcpy(soal3[4].riddle_soal, "I can bring tears to your eyes; resurrect the dead, make you smile, and reverse time.\nI form in an instant but I last a lifetime. What am I?");
    strcpy(soal3[4].riddle_answer, "\nA. Tears\nB. Smile\nC. Fault\nD. Memory\n");
    soal3[4].riddle_PG = 'd';

    strcpy(soal3[5].riddle_soal, "What body part is pronounced as one letter but written with three, only two different letters are used?");
    strcpy(soal3[5].riddle_answer, "\nA. Leg\nB. Rib\nC. Arm\nD. Eye\n");
    soal3[5].riddle_PG = 'd';

    strcpy(soal3[6].riddle_soal, "I am not alive but i grow. I don't have lungs but I need air. What am I?");
    strcpy(soal3[6].riddle_answer, "\nA. Fire\nB. Plants\nC. Balloon\nD. Bubble gum\n");
    soal3[6].riddle_PG = 'a';

    strcpy(soal3[7].riddle_soal, "What has a ring, but no finger?");
    strcpy(soal3[7].riddle_answer, "\nA. Collar\nB. Heart\nC. Phone\nD. Dinamo\n");
    soal3[7].riddle_PG = 'c';

    strcpy(soal3[8].riddle_soal, "What doesn't get any wetter, no matter how much rain falls on it?");
    strcpy(soal3[8].riddle_answer, "\nA. Parachute\nB. Umbrella\nC. A Raincoat\nD. Water\n");
    soal3[8].riddle_PG = 'd';

    strcpy(soal3[9].riddle_soal, "What never asks questions but is always answered. What am I?");
    strcpy(soal3[9].riddle_answer, "\nA. A call\nB. Adzan\nC. Women\nD. Doorbell\n");
    soal3[9].riddle_PG = 'd';

    printf("--------------------------------------------------------------------\n");
    printf("\n\t\t\t   RIDDLE GAME LEVEL 3\n\n");
    printf("--------------------------------------------------------------------\n");
    printf("\tChoose the correct answer for the following questions!\n");
    printf("     You must collect at least 165 points to finish the game!\n\n");
    int num;
    for (int i = 0; i < 10; i++)
    {
        char riddle_userAnswer;
        int check;
        while (true)
        {
            srand(time(0));
            num = rand() % 10;
            if (flag[num] == 1)
                continue;
            else
            {
                flag[num] = 1;
                break;
            }
        }
        printf("--------------------------------------------------------------------\n");
        printf("\n%s", soal3[num].riddle_soal);
        printf("%s", soal3[num].riddle_answer);
        while (true)
        {
            printf("Answer: ");
            scanf("%c", &riddle_userAnswer);
            getchar();
            if (riddle_userAnswer >= 'A' && riddle_userAnswer <= 'D')
            {
                riddle_userAnswer += 32;
                break;
            }
            else if (riddle_userAnswer >= 'a' && riddle_userAnswer <= 'd')
            {
                break;
            }
        }
        switch (riddle_userAnswer)
        {
        case 'a':
            system("CLS");
            (riddle_userAnswer == soal3[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal3[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        case 'b':
            system("CLS");
            (riddle_userAnswer == soal3[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal3[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            };
            break;
        case 'c':
            system("CLS");
            (riddle_userAnswer == soal3[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal3[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        case 'd':
            system("CLS");
            (riddle_userAnswer == soal3[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal3[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        default:
            break;
        }
    }
    endGameLevel3();
}

void endGameLevel2()
{
    printf("--------------------------------------------------------------------\n");
    printf("Your score is %d\n", riddle_score);
    char riddle_gameOver_level2;
    if (riddle_score > 110)
    {
        printf("Congrats, press 'Y' to play the next level or 'X' to exit the game!\n");
        scanf("%c", &riddle_gameOver_level2);
        getchar();
    }
    else
    {
        printf("Game Over! press 'R' to try again or 'X' to exit the game! \n");
        riddle_score = score_temp;
        scanf("%c", &riddle_gameOver_level2);
        getchar();
    }
    for (int i = 0; i < 10; i++)
    {
        flag[i] = 0;
    }
    if (riddle_gameOver_level2 >= 'A' && riddle_gameOver_level2 <= 'Z')
    {
        riddle_gameOver_level2 += 32;
    }

    switch (riddle_gameOver_level2)
    {
    case 'y':
        score_temp = riddle_score;
        system("CLS");
        level3();
        break;
    case 'r':
        riddle_score = score_temp;
        system("CLS");
        level2();
        break;
    case 'x':
        printf("Thank you for playing!\n");
        system("CLS");
        menuRiddle();
        break;
    }

    scoreFinal += riddle_score;
}

void level2()
{
    strcpy(soal2[0].riddle_soal, "How many letters are in the alphabet?");
    strcpy(soal2[0].riddle_answer, "\nA. 26\nB. 11\nC. 25\nD. 12\n");
    soal2[0].riddle_PG = 'b';

    strcpy(soal2[1].riddle_soal, "What has a face and two hands but no arms or legs?");
    strcpy(soal2[1].riddle_answer, "\nA. A chair\nB. A chinchilla\nC. A clock\nD. A car\n");
    soal2[1].riddle_PG = 'c';

    strcpy(soal2[2].riddle_soal, "There's a house. One enters it blind and comes out seeing. What is it?");
    strcpy(soal2[2].riddle_answer, "\nA. A church\nB. A hut\nC. A school\nD. A castle\n");
    soal2[2].riddle_PG = 'c';

    strcpy(soal2[3].riddle_soal, "As I was going to St. Ives, I met a man with seven wives.\nHow many were there going to St. Ives?");
    strcpy(soal2[3].riddle_answer, "\nA. 9\nB. 1\nC. 7\nD. 2\n");
    soal2[3].riddle_PG = 'b';

    strcpy(soal2[4].riddle_soal, "What instrument can you hear but never see?");
    strcpy(soal2[4].riddle_answer, "\nA. your thought\nB. someone's thought\nC. A piano\nD. Your voice\n");
    soal2[4].riddle_PG = 'd';

    strcpy(soal2[5].riddle_soal, "Which letter of the alphabet has the most water? ");
    strcpy(soal2[5].riddle_answer, "\nA. r\nB. a\nC. w\nD. c\n");
    soal2[5].riddle_PG = 'd';

    strcpy(soal2[6].riddle_soal, "What five-letter word becomes shorter when you add two letters to it?");
    strcpy(soal2[6].riddle_answer, "\nA. Short\nB. Aging\nC. Connect\nD. shorten\n");
    soal2[6].riddle_PG = 'a';

    strcpy(soal2[7].riddle_soal, "What word begins and ends with an E but only has one letter?");
    strcpy(soal2[7].riddle_answer, "\nA. E\nB. Earth\nC. Envelope\nD. Egg\n");
    soal2[7].riddle_PG = 'c';

    strcpy(soal2[8].riddle_soal, "I am a word. If you pronounce me rightly, it will be wrong.\nIf you pronounce me wrong it is right. What word am I?");
    strcpy(soal2[8].riddle_answer, "\nA. Rightly\nB. Me\nC. A Right\nD. A Wrong\n");
    soal2[8].riddle_PG = 'd';

    strcpy(soal2[9].riddle_soal, "The more there is, the less you see.");
    strcpy(soal2[9].riddle_answer, "\nA. Lamp\nB. Diamond\nC. Gold\nD. Darkness\n");
    soal2[9].riddle_PG = 'd';

    printf("--------------------------------------------------------------------\n");
    printf("\n\t\t\t   RIDDLE GAME LEVEL 2\n\n");
    printf("--------------------------------------------------------------------\n");
    printf("\tChoose the correct answer for the following questions!\n");
    printf("     You must collect at least 110 points to unlock the next level!\n\n");
    int num;
    for (int i = 0; i < 10; i++)
    {
        char riddle_userAnswer;
        int check;
        while (true)
        {
            srand(time(0));
            num = rand() % 10;
            if (flag[num] == 1)
                continue;
            else
            {
                flag[num] = 1;
                break;
            }
        }
        printf("--------------------------------------------------------------------\n");
        printf("\n%s", soal2[num].riddle_soal);
        printf("%s", soal2[num].riddle_answer);
        while (true)
        {
            printf("Answer: ");
            scanf("%c", &riddle_userAnswer);
            getchar();
            if (riddle_userAnswer >= 'A' && riddle_userAnswer <= 'D')
            {
                riddle_userAnswer += 32;
                break;
            }
            else if (riddle_userAnswer >= 'a' && riddle_userAnswer <= 'd')
            {
                break;
            }
        }
        switch (riddle_userAnswer)
        {
        case 'a':
            system("CLS");
            (riddle_userAnswer == soal2[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal2[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        case 'b':
            system("CLS");
            (riddle_userAnswer == soal2[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal2[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            };
            break;
        case 'c':
            system("CLS");
            (riddle_userAnswer == soal2[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal2[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        case 'd':
            system("CLS");
            (riddle_userAnswer == soal2[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal2[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        default:
            break;
        }
    }
    endGameLevel2();
}

void endGameLevel1()
{
    printf("--------------------------------------------------------------------\n");
    printf("Your score is %d\n", riddle_score);
    char riddle_gameOver_level1;
    if (riddle_score > 55)
    {
        printf("Congrats, press 'Y' to play the next level or 'X' to exit the game!\n");
        scanf("%c", &riddle_gameOver_level1);
        getchar();
    }
    else
    {
        printf("Game Over! press 'R' to try again or 'X' to exit the game! \n");
        scanf("%c", &riddle_gameOver_level1);
        getchar();
    }
    for (int i = 0; i < 10; i++)
    {
        flag[i] = 0;
    }
    if (riddle_gameOver_level1 >= 'A' && riddle_gameOver_level1 <= 'Z')
    {
        riddle_gameOver_level1 += 32;
    }

    switch (riddle_gameOver_level1)
    {
    case 'y':
        score_temp = riddle_score;
        system("CLS");
        level2();
        break;
    case 'r':
        riddle_score = 0;
        system("CLS");
        level1();
        break;
    case 'x':
        printf("Thank you for playing!\n");
        system("CLS");
        menuRiddle();
        break;
    }
    system("CLS");
    scoreFinal += riddle_score;
}

void level1()
{
    strcpy(soal1[0].riddle_soal, "I'm a mother's child and a father's child but nobody's son. what am I?");
    strcpy(soal1[0].riddle_answer, "\nA. Grandson\nB. Daughter\nC. Father\nD. Uncle\n");
    soal1[0].riddle_PG = 'b';

    strcpy(soal1[1].riddle_soal, "What ten letter word starts with gas?");
    strcpy(soal1[1].riddle_answer, "\nA. Television\nB. Aberration\nC. Automobile\nD. Retirement\n");
    soal1[1].riddle_PG = 'c';

    strcpy(soal1[2].riddle_soal, "What Comes once in a minute, twice in a moment, but never in a thousand years?");
    strcpy(soal1[2].riddle_answer, "\nA. 30 seconds\nB. 1/1000 of a decade\nC. The letter 'M'\nD. One-tenth of a century\n");
    soal1[2].riddle_PG = 'c';

    strcpy(soal1[3].riddle_soal, "What is 3/7 chicken, 2/3 cat and 2/4 goat?");
    strcpy(soal1[3].riddle_answer, "\nA. Childbirth\nB. Chicago\nC. Chipmunk\nD. Ciao\n");
    soal1[3].riddle_PG = 'b';

    strcpy(soal1[4].riddle_soal, "I'm a 7 letter word. I become longer when my third letter is removed. Who am I?");
    strcpy(soal1[4].riddle_answer, "\nA. Longing\nB. Lenghty\nC. Longing\nD. Lounger\n");
    soal1[4].riddle_PG = 'd';

    strcpy(soal1[5].riddle_soal, "Which month has 28 days?");
    strcpy(soal1[5].riddle_answer, "\nA. February\nB. April\nC. July\nD. All\n");
    soal1[5].riddle_PG = 'd';

    strcpy(soal1[6].riddle_soal, "A cow has 3 A girl Has 4. What is it?");
    strcpy(soal1[6].riddle_answer, "\nA. Letters\nB. Hand\nC. Horn\nD. Leg\n");
    soal1[6].riddle_PG = 'a';

    strcpy(soal1[7].riddle_soal, "I belong to you but others use me more often than you do. what am I?");
    strcpy(soal1[7].riddle_answer, "\nA. Brain\nB. Toy\nC. Name\nD. Hand\n");
    soal1[7].riddle_PG = 'c';

    strcpy(soal1[8].riddle_soal, "I have 13 hearts, yet never alive. what am I?");
    strcpy(soal1[8].riddle_answer, "\nA. A cat\nB. A tiger\nC. A Penguin\nD. A pack of card\n");
    soal1[8].riddle_PG = 'd';

    strcpy(soal1[9].riddle_soal, "What can you catch but not throw ?");
    strcpy(soal1[9].riddle_answer, "\nA. Wind\nB. Water\nC. A candle\nD. A cold\n");
    soal1[9].riddle_PG = 'd';
    printf("--------------------------------------------------------------------\n");
    printf("\n\t\t\t   RIDDLE GAME LEVEL 1\n\n");
    printf("--------------------------------------------------------------------\n");
    printf("\tChoose the correct answer for the following questions!\n");
    printf("You must collect at least 55 points to unlock the next level!\n\n");
    int num;
    for (int i = 0; i < 10; i++)
    {
        char riddle_userAnswer;
        int check;
        while (true)
        {
            srand(time(0));
            num = rand() % 10;
            if (flag[num] == 1)
                continue;
            else
            {
                flag[num] = 1;
                break;
            }
        }
        printf("--------------------------------------------------------------------\n");
        printf("\n%s", soal1[num].riddle_soal);
        printf("%s", soal1[num].riddle_answer);
        while (true)
        {
            printf("Answer: ");
            scanf("%c", &riddle_userAnswer);
            getchar();
            if (riddle_userAnswer >= 'A' && riddle_userAnswer <= 'D')
            {
                riddle_userAnswer += 32;
                break;
            }
            else if (riddle_userAnswer >= 'a' && riddle_userAnswer <= 'd')
            {
                break;
            }
        }
        switch (riddle_userAnswer)
        {
        case 'a':
            system("CLS");
            (riddle_userAnswer == soal1[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal1[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        case 'b':
            system("CLS");
            (riddle_userAnswer == soal1[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal1[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            };
            break;
        case 'c':
            system("CLS");
            (riddle_userAnswer == soal1[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal1[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        case 'd':
            system("CLS");
            (riddle_userAnswer == soal1[num].riddle_PG) ? check = 1 : check = 0;
            if (check == 1)
            {
                printf("--------------------------------------------------------------------\n");
                printf("Correct! You get +10 points\n");
                riddle_score += 10;
                printf("Current score: %d\n", riddle_score);
            }
            else if (check == 0)
            {
                printf("Wrong! The correct answer is %c \nYou lose -5 points\n", soal1[num].riddle_PG);
                riddle_score -= 5;
                printf("Current score: %d\n", riddle_score);
            }
            break;
        default:
            break;
        }
    }
    endGameLevel1();
}

void catchs()
{
    int a = 1;
    if (a = 1)
    {
        setup();

        while (!gameovercatch)
        {
            draw();
            input();
            logic();
        }
        scoreFinal += scorecatch;
        system("CLS");
        ascii_catchAsterisk();
        printf("Do you want to play again?\n");
        printf("%s> Yes <%s\n", CLR_YEL, CLR_WHT);
        printf("No\n");

        char input;
        char texts[3][30] = {"Yes", "No"};
        int inputChoice = 0;

        for (int i = 0;; i++)
        {

            input = _getche();
            system("CLS");
            ascii_catchAsterisk();
            printf("Do you want to play again?\n");
            if (input == 's')
            {
                inputChoice++;
            }
            else if (input == 'w')
            {
                inputChoice--;
            }

            if (inputChoice < 0)
            {
                inputChoice = 0;
            }
            else if (inputChoice > 1)
            {
                inputChoice = 1;
            }

            if (input == '\x0D' && inputChoice == 0)
            {
                system("CLS");
                catchs();
            }
            else if (input == '\x0D' && inputChoice == 1)
            {
                system("CLS");
                mainPage();
            }

            for (int i = 0; i < 2; i++)
            {

                if (i != inputChoice)
                {
                    printf("%s\n", texts[i]);
                }
                else
                {
                    printf("%s> %s <%s\n", CLR_YEL, texts[inputChoice], CLR_WHT);
                }
            }
        }
    }
}

void setup()
{
    gameovercatch = 0;
    xcatch = heightcatch / 2;
    ycatch = widthcatch / 2;

label1:
    buahxcatch = rand() % 20;
    if (buahxcatch == 0)
        goto label1;
label2:
    buahycatch = rand() % 20;
    if (buahycatch == 0)
        goto label2;
    scorecatch = 0;
}

void draw()
{
    system("cls"); // untuk membersihkan output
    for (icatch = 0; icatch < heightcatch; icatch++)
    {
        for (jcatch = 0; jcatch < widthcatch; jcatch++)
        {
            if (icatch == 0 || icatch == widthcatch - 1 || jcatch == 0 || jcatch == heightcatch - 1)
            {
                printf("#");
            }
            else
            {
                if (icatch == xcatch && jcatch == ycatch)
                    printf("0");
                else if (icatch == buahxcatch && jcatch == buahycatch)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("score = %d", scorecatch);
    printf("\n");
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'a':
            flagcatch = 1;
            break;
        case 's':
            flagcatch = 2;
            break;
        case 'd':
            flagcatch = 3;
            break;
        case 'w':
            flagcatch = 4;
            break;
        case 'x':
            gameovercatch = 1;
            break;
        }
    }
}

void logic()
{
    usleep(90000); // for delaying the program
    switch (flagcatch)
    {
    case 1:
        ycatch--;
        break;
    case 2:
        xcatch++;
        break;
    case 3:
        ycatch++;
        break;
    case 4:
        xcatch--;
        break;
    default:
        break;
    }
    if (xcatch < 0 || xcatch > heightcatch || ycatch < 0 || ycatch > widthcatch)
        gameovercatch = 1;
    if (xcatch == buahxcatch && ycatch == buahycatch)
    {
    label3:
        buahxcatch = rand() % 20;
        if (buahxcatch == 0)
            goto label3;
    label4:
        buahycatch = rand() % 20;
        if (buahycatch == 0)
            goto label4;
        scorecatch += 10;
    }
}

void ascii_snakeGame()
{
    printf("   _____             _           _____                      \n");
    printf("  / ____|           | |         / ____|                     \n");
    printf(" | (___  _ __   __ _| | _____  | |  __  __ _ _ __ ___   ___ \n");
    printf("  \\___ \\| '_ \\ / _` | |/ / _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\\n");
    printf("  ____) | | | | (_| |   <  __/ | |__| | (_| | | | | | |  __/\n");
    printf(" |_____/|_| |_|\\__,_|_|\\_\\___|  \\_____|\\__,_|_| |_| |_|\\___|\n");
    printf("\n\n");
}

void ascii_riddleGame()
{
    printf("  _____  _     _     _ _         _____                      \n");
    printf(" |  __ \\(_)   | |   | | |       / ____|                     \n");
    printf(" | |__) |_  __| | __| | | ___  | |  __  __ _ _ __ ___   ___ \n");
    printf(" |  _  /| |/ _` |/ _` | |/ _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\\n");
    printf(" | | \\ \\| | (_| | (_| | |  __/ | |__| | (_| | | | | | |  __/\n");
    printf(" |_|  \\_\\_|\\__,_|\\__,_|_|\\___|  \\_____|\\__,_|_| |_| |_|\\___|\n");
    printf("\n\n");
}

void ascii_miniArcade()
{
    printf("  __  __ _       _                              _      \n");
    printf(" |  \\/  (_)     (_)     /\\                     | |     \n");
    printf(" | \\  / |_ _ __  _     /  \\   _ __ ___ __ _  __| | ___ \n");
    printf(" | |\\/| | | '_ \\| |   / /\\ \\ | '__/ __/ _` |/ _` |/ _ \n");
    printf(" | |  | | | | | | |  / ____ \\| | | (_| (_| | (_| |  __/\n");
    printf(" |_|  |_|_|_| |_|_| /_/    \\_\\_|  \\___\\__,_|\\__,_|\\___|\n");
    printf("\n\n");
}

void ascii_catchAsterisk()
{
    printf("   _____      _       _                    _            _     _    \n");
    printf("  / ____|    | |     | |         /\\       | |          (_)   | |   \n");
    printf(" | |     __ _| |_ ___| |__      /  \\   ___| |_ ___ _ __ _ ___| | __\n");
    printf(" | |    / _` | __/ __| '_ \\    / /\\ \\ / __| __/ _ \\ '__| / __| |/ /\n");
    printf(" | |___| (_| | || (__| | | |  / ____ \\__ \\  ||  __/ |  | \\__ \\   < \n");
    printf("  \\_____\\__,_|\\__\\___|_| |_| /_/    \\_\\___/\\__\\___|_|  |_|___/_|\\_\\\n");
    printf("\n\n");
}

void ascii_newPlayer()
{
    printf("  _   _                 _____  _                       \n");
    printf(" | \\ | |               |  __ \\| |                      \n");
    printf(" |  \\| | _____      __ | |__) | | __ _ _   _  ___ _ __ \n");
    printf(" | . ` |/ _ \\ \\ /\\ / / |  ___/| |/ _` | | | |/ _ \\ '__|\n");
    printf(" | |\\  |  __/\\ V  V /  | |    | | (_| | |_| |  __/ |   \n");
    printf(" |_| \\_|\\___| \\_/\\_/   |_|    |_|\\__,_|\\__, |\\___|_|   \n");
    printf("                                        __/ |          \n");
    printf("                                       |___/           \n");
    printf("\n\n");
}

void ascii_logIn()
{
    printf("  _                   _____       \n");
    printf(" | |                 |_   _|      \n");
    printf(" | |     ___   __ _    | |  _ __  \n");
    printf(" | |    / _ \\ / _` |   | | | '_ \\ \n");
    printf(" | |___| (_) | (_| |  _| |_| | | |\n");
    printf(" |______\\___/ \\__, | |_____|_| |_|\n");
    printf("               __/ |              \n");
    printf("              |___/               \n");
    printf("\n\n");
}

void ascii_mainMenuAnimated()
{
    printf(" __          __  _                            _ \n");
    delay();
    printf(" \\ \\        / / | |                          | |\n");
    delay();
    printf("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |\n");
    delay();
    printf("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\n");
    delay();
    printf("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ |_|\n");
    delay();
    printf("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| (_)\n");
    delay();
}

void ascii_mainMenu()
{
    printf(" __          __  _                            _ \n");
    printf(" \\ \\        / / | |                          | |\n");
    printf("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |\n");
    printf("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\n");
    printf("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ |_|\n");
    printf("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| (_)\n");
    printf("\n\n");
}

void delay()
{
    for (int i = 0; i < 2e8; i++)
    {
    }
}