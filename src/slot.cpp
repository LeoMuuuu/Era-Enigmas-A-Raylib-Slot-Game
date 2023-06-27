#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <raylib.h>
#include "slot.hpp"
#include <fstream>
#include <functional>
#include <string>

class Button
{
public:
    Rectangle rec;
    Texture2D texture;
    bool clicked;

    Button();
    bool IsClicked();

};

class BoardOperations {
public:
    int randNum();

};

class CreateBoard : public BoardOperations {
public:
    CreateBoard(int r, int c) : ROWS(r), COLS(c), board(ROWS, std::vector<int>(COLS)), replenishboard(ROWS, std::vector<int>(COLS)){};
    int ROWS;
    int COLS;
    bool RemoveisOver;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> replenishboard;
    void initBoard4(std::vector<std::vector<int>>& board);
    void initReplenishBoard4(std::vector<std::vector<int>>& board);
    void printBoard4(std::vector<std::vector<int>>& board);
    //void DetectMagicEye(std::vector<std::vector<int>>& board);
    bool IsIncluded(std::vector<std::vector<std::vector<int>>>& vec, int x, int y);
    bool IsIncludedPoint(std::vector<std::vector<int>>& vec, int x, int y);
    std::vector<std::vector<std::vector<int>>> ConnectionDetect(std::vector<std::vector<int>>& board);
    bool is_within_bounds(int x, int y);
    void RegionGrowing(std::vector<std::vector<int>>& board,std::vector <std::vector<int>>& region, int x, int y);
    int RemoveConnection(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec);
    bool CreateBoard::IsFinished(std::vector<std::vector<std::vector<int>>>& vec);
    void DropDown(std::vector<std::vector<int>>& board);
    std::vector<std::vector<int>> ReplenishMap(std::vector<std::vector<std::vector<int>>>& vec);
    void Replenish(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& replenishboard, std::vector<std::vector<int>>& vec);
    bool IsFinish(std::vector<std::vector<std::vector<int>>>& vec);

    void initBoard5(std::vector<std::vector<int>>& board);
    void initReplenishBoard5(std::vector<std::vector<int>>& board);
    void printBoard5(std::vector<std::vector<int>>& board);

    void initBoard6(std::vector<std::vector<int>>& board);
    void initReplenishBoard6(std::vector<std::vector<int>>& board);
    void printBoard6(std::vector<std::vector<int>>& board);

    int BonusLookup4(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec);
    int BonusLookup5(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec);
    int BonusLookup6(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec);

    int table[11][5] = {
    {2,4,5,10,20},
    {4,5,10,30,50},
    {5,10,20,50,100},
    {8,20,40,60,500},
    {10,30,80,100,1000},
    {20,50,160,750,2000},
    {30,100,500,1000,5000},
    {50,250,1000,10000,20000},
    {100,500,2000,20000,50000},
    {200,750,5000,50000,60000},
    {450,1000,7000,70000,100000}
    };

};

CreateBoard Mission1(4, 4);
CreateBoard Mission2(5, 5);
CreateBoard Mission3(6, 6);
int frames = 0;
int animationFrame = 0;
bool StopAnimation = false;
bool leverPressed = false;
int AnimationRow=1;
static const int u = 128;
int blocks_4 = 36;
int blocks_5 = 44;
int blocks_6 = 100;
int playerMoney;
int bonus;
Texture2D Sprites1[5];
Texture2D Sprites2[5];
Texture2D Sprites3[5];
Texture2D animation1[15];
Texture2D animation2[15];
Texture2D animation3[15];
Texture2D back;
Texture2D block;
bool RemoveisOver;
int c11, c12, c13, c14;
int c21, c22, c23, c24, c25;
int c31, c32, c33, c34, c35, c36;

int BoardOperations::randNum() {
    int probabilities[] = { 30, 25, 20, 15, 10}; // probabilities of each number in percent
    int randValue = rand() % 100 + 1; // generate a random value between 1 and 100 inclusive
    int cumulativeProb = 0;
    for (int i = 0; i < 5; i++) {
        cumulativeProb += probabilities[i];
        if (randValue <= cumulativeProb) {
            return i + 1; // return the number (i+1)
        }
    }
    return 1; // default return value (just in case)
}
bool Button::IsClicked()
{
    if (GetMouseX() >= rec.x && GetMouseX() <= rec.x + rec.width && GetMouseY() >= rec.y && GetMouseY() <= rec.y + rec.height
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return true;
    return false;
}
bool LeverClicked()
{
    if (GetMouseX() >= u * 10.5 && GetMouseX() <= u * 13.5 && GetMouseY() >= u * 5.5 && GetMouseY() <= u * 7.0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return true;
    return false;
}

//Mission 1
void CreateBoard::initBoard4(std::vector<std::vector<int>>& board) {
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = randNum();
        }
    }
}
void CreateBoard::initReplenishBoard4(std::vector<std::vector<int>>& board) {
    srand(time(NULL)+1);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = randNum();
        }
    }
}
void CreateBoard::printBoard4(std::vector<std::vector<int>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
bool CreateBoard::IsIncluded(std::vector<std::vector<std::vector<int>>>& vec, int x , int y) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            if (x == vec[i][j][0] && y == vec[i][j][1]) {
                return true;
            }
        }
    }
    return false;
}
bool CreateBoard::is_within_bounds(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}
bool CreateBoard::IsIncludedPoint(std::vector<std::vector<int>>& vec, int x, int y) {
    for (int i = 0; i < vec.size(); i++) {
        if (x == vec[i][0] && y == vec[i][1]) {
            return true;
        }
    }
    return false;
}
void CreateBoard::RegionGrowing(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& region, int x, int y) {
    if (!is_within_bounds(x, y) || IsIncludedPoint(region, x, y)) {
        return;
    }

    std::vector<int> point;
    point.push_back(x);
    point.push_back(y);
    region.push_back(point);

    if (is_within_bounds(x - 1, y) && board[x - 1][y] == board[x][y]) {
        RegionGrowing(board, region, x - 1, y);
    }
    if (is_within_bounds(x, y - 1) && board[x][y - 1] == board[x][y]) {
        RegionGrowing(board, region, x, y - 1);
    }
    if (is_within_bounds(x + 1, y) && board[x + 1][y] == board[x][y]) {
        RegionGrowing(board, region, x + 1, y);
    }
    if (is_within_bounds(x, y + 1) && board[x][y + 1] == board[x][y]) {
        RegionGrowing(board, region, x, y + 1);
    }
}
std::vector<std::vector<std::vector<int>>> CreateBoard::ConnectionDetect(std::vector<std::vector<int>>& board) {
    std::vector<std::vector<std::vector<int>>> MainStorage;
    std::vector<std::vector<int>> PointsStorage;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (!IsIncluded(MainStorage, i, j)) {
                RegionGrowing(board, PointsStorage, i, j);
                MainStorage.push_back(PointsStorage);
                PointsStorage.clear();
            }
        }
    }
    return MainStorage;
}
int CreateBoard::RemoveConnection(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec) {
    int count = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() >= ROWS) {
            count += 1;
            
        }
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i].size() >= ROWS) {
                board[vec[i][j][0]][vec[i][j][1]] = 0;
            }
        }
    }
    return count;
}
bool CreateBoard::IsFinished(std::vector<std::vector<std::vector<int>>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i].size() >= ROWS) {
                return false;
            }
        }
    }
    return true;
}
void CreateBoard::DropDown(std::vector<std::vector<int>>& board) {
    int t;
    for (int k = 0; k < ROWS; k++) {
        for (int i = ROWS - 1; i > 0; i--) {
            for (int j = COLS - 1; j >= 0; j--) {
                if (board[i][j] == 0) {
                    t = board[i - 1][j];
                    board[i][j] = t;
                    board[i - 1][j] = 0;
                }
            }
        }
    }
}
std::vector<std::vector<int>> CreateBoard::ReplenishMap(std::vector<std::vector<std::vector<int>>>& vec) {
    std::vector<int> ColCounts;
    for (int k = 0; k < ROWS; k++) {
        ColCounts.push_back(ROWS-1);
    }
    std::vector<std::vector<int>> PointsStorage;
    std::vector<int> SinglePointStorage;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() >= ROWS) {
            for (int j = 0; j < vec[i].size(); j++) {
                SinglePointStorage.push_back(ColCounts[vec[i][j][1]]);
                ColCounts[vec[i][j][1]] -= 1;
                SinglePointStorage.push_back(vec[i][j][1]);
                PointsStorage.push_back(SinglePointStorage);
                SinglePointStorage.clear();
            }
        }
    }
    return PointsStorage;
}
void CreateBoard::Replenish(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& replenishboard, std::vector<std::vector<int>>& vec) {
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    for (int i = 0; i < vec.size(); i++) {
            if (vec[i][1] == 0) {
                a += 1;
            }
            else if (vec[i][1] == 1) {
                b += 1;
            }
            else if (vec[i][1] == 2) {
                c += 1;
            }
            else if (vec[i][1] == 3) {
                d += 1;
            }
            else if (vec[i][1] == 4) {
                e += 1;
            }
            else if (vec[i][1] == 5) {
                f += 1;
            }
    }
    int ColCounts[6] = { a,b,c,d,e,f };
    if (vec.size()!=0) {
        for (int i = 0; i < vec.size(); i++) {
            board[vec[i][0]+ ColCounts[vec[i][1]]-ROWS][vec[i][1]] = replenishboard[vec[i][0]][vec[i][1]];
        }
    }
}
bool CreateBoard::IsFinish(std::vector<std::vector<std::vector<int>>>& vec){
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i].size() >= ROWS) {
                return false;
            }
        }
    }
    return true;
}
int CreateBoard::BonusLookup4(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec) {
    int bonus = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() >= ROWS) {
            bonus += table[vec[i].size()-4][board[vec[i][0][0]][vec[i][0][1]]];
            std::cout << bonus;
        }
    }
    return bonus;
}
//Mission 2
void CreateBoard::initBoard5(std::vector<std::vector<int>>& board) {
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = randNum();
        }
    }
}
void CreateBoard::initReplenishBoard5(std::vector<std::vector<int>>& board) {
    srand(time(NULL) + 1);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = randNum();
        }
    }
}
void CreateBoard::printBoard5(std::vector<std::vector<int>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int CreateBoard::BonusLookup5(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec) {
    int bonus = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() >= ROWS) {
            bonus += table[vec[i].size() - 5][board[vec[i][0][0]][vec[i][0][1]]]*1.5;
            std::cout << bonus;
        }
    }
    return bonus;
}
//Mission 3
void CreateBoard::initBoard6(std::vector<std::vector<int>>& board) {
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = randNum();
        }
    }
}
void CreateBoard::initReplenishBoard6(std::vector<std::vector<int>>& board) {
    srand(time(NULL) + 1);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = randNum();
        }
    }
}
void CreateBoard::printBoard6(std::vector<std::vector<int>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int CreateBoard::BonusLookup6(std::vector<std::vector<int>>& board, std::vector<std::vector<std::vector<int>>>& vec) {
    int bonus = 0;
    int params = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() >= ROWS) {
            bonus += table[vec[i].size() - 6][board[vec[i][0][0]][vec[i][0][1]]]*2 + 200* params;
            std::cout << bonus;
            params += 1;
        }
    }
    return bonus;
}

void Test() {
    Mission1.initBoard4(Mission1.board);
    srand(time(NULL));
    Mission1.initReplenishBoard4(Mission1.replenishboard);

    std::cout << "Initial£º" << std::endl;
    Mission1.printBoard4(Mission1.board);
    std::vector<std::vector<std::vector<int>>> connectionmap;
    connectionmap = Mission1.ConnectionDetect(Mission1.board);
    Mission1.RemoveConnection(Mission1.board, connectionmap);

    std::cout << "Canceled£º" << std::endl;
    Mission1.printBoard4(Mission1.board);

    std::cout << "Fallen£º" << std::endl;
    Mission1.DropDown(Mission1.board);
    Mission1.printBoard4(Mission1.board);

    std::cout << "Replenish£º" << std::endl;
    Mission1.printBoard4(Mission1.replenishboard);

    std::cout << "After£º" << std::endl;
    std::vector<std::vector<int>> replenishmap;
    replenishmap = Mission1.ReplenishMap(connectionmap);
    Mission1.Replenish(Mission1.board, Mission1.replenishboard, replenishmap);
    Mission1.printBoard4(Mission1.board);
}
void LoadElements() {
    for (int i = 0; i < 15; i++)
    {
        animation1[i] = LoadTexture(TextFormat("ani_a/layer%d.png", i + 1));
    }
    for (int i = 0; i < 15; i++)
    {
        animation2[i] = LoadTexture(TextFormat("ani_b/layer%d.png", i + 1));
    }
    for (int i = 0; i < 15; i++)
    {
        animation3[i] = LoadTexture(TextFormat("ani_c/layer%d.png", i + 1));
    }
    for (int i = 0; i < 5; i++)
    {
        Sprites1[i] = LoadTexture(TextFormat("a/a%d.png", i + 1));
    }
    for (int i = 0; i < 5; i++)
    {
        Sprites2[i] = LoadTexture(TextFormat("b/b%d.png", i + 1));
    }
    for (int i = 0; i < 5; i++)
    {
        Sprites3[i] = LoadTexture(TextFormat("c/c%d.png", i + 1));
    }
    block = LoadTexture("f0/block.png");
}
int AddAnimationFrame(int x)
{
    int ans;
    ans = animationFrame + x;
    if (ans > 14)ans -= 14;
    return ans;
}
void PlayAnimation4()
{
    float scale = 2.0f/3.0f;
    if (frames == 60)frames = 0;
    if (animationFrame == 14)animationFrame = 0;
    else animationFrame++;
        if (AnimationRow < 2)c11 = AddAnimationFrame(2);
        if (AnimationRow < 3)c12 = AddAnimationFrame(8);
        if (AnimationRow < 4)c13 = AddAnimationFrame(4);
        if (AnimationRow < 5)c14 = AddAnimationFrame(10);
        if (AnimationRow < 2)DrawTextureEx(animation1[c11], { u * 5, u * 2.7 },0, scale, WHITE);
        if (AnimationRow < 3)DrawTextureEx(animation1[c12], { u * 6, u * 2.7 }, 0, scale, WHITE);
        if (AnimationRow < 4)DrawTextureEx(animation1[c13], { u*7, u * 2.7 }, 0, scale, WHITE);
        if (AnimationRow < 5)DrawTextureEx(animation1[c14], { u*8, u * 2.7 }, 0, scale, WHITE);
}
void PlayAnimation5()
{
    float scale = 2.0f / 3.0f;
    if (frames == 60)frames = 0;
    if (animationFrame == 14)animationFrame = 0;
    else animationFrame++;
    if (AnimationRow < 2)c21 = AddAnimationFrame(2);
    if (AnimationRow < 3)c22 = AddAnimationFrame(8);
    if (AnimationRow < 4)c23 = AddAnimationFrame(4);
    if (AnimationRow < 5)c24 = AddAnimationFrame(10);
    if (AnimationRow < 5)c25 = AddAnimationFrame(5);
    if (AnimationRow < 2)DrawTextureEx(animation2[c21], { u * 4.5, u * 2.2 }, 0, scale, WHITE);
    if (AnimationRow < 3)DrawTextureEx(animation2[c22], { u * 5.5, u * 2.2 }, 0, scale, WHITE);
    if (AnimationRow < 4)DrawTextureEx(animation2[c23], { u * 6.5, u * 2.2 }, 0, scale, WHITE);
    if (AnimationRow < 5)DrawTextureEx(animation2[c24], { u * 7.5, u * 2.2 }, 0, scale, WHITE);
    if (AnimationRow < 5)DrawTextureEx(animation2[c25], { u * 8.5, u * 2.2 }, 0, scale, WHITE);
}
void PlayAnimation6()
{
    float scale = 2.0f / 3.0f;
    if (frames == 60)frames = 0;
    if (animationFrame == 14)animationFrame = 0;
    else animationFrame++;
    if (AnimationRow < 2)c31 = AddAnimationFrame(2);
    if (AnimationRow < 3)c32 = AddAnimationFrame(8);
    if (AnimationRow < 4)c33 = AddAnimationFrame(4);
    if (AnimationRow < 5)c34 = AddAnimationFrame(10);
    if (AnimationRow < 5)c35 = AddAnimationFrame(5);
    if (AnimationRow < 5)c36 = AddAnimationFrame(12);
    if (AnimationRow < 2)DrawTextureEx(animation3[c31], { u * 4, u * 1.7 }, 0, scale, WHITE);
    if (AnimationRow < 3)DrawTextureEx(animation3[c32], { u * 5, u * 1.7 }, 0, scale, WHITE);
    if (AnimationRow < 4)DrawTextureEx(animation3[c33], { u * 6, u * 1.7 }, 0, scale, WHITE);
    if (AnimationRow < 5)DrawTextureEx(animation3[c34], { u * 7, u * 1.7 }, 0, scale, WHITE);
    if (AnimationRow < 5)DrawTextureEx(animation3[c35], { u * 8, u * 1.7 }, 0, scale, WHITE);
    if (AnimationRow < 5)DrawTextureEx(animation3[c36], { u * 9, u * 1.7 }, 0, scale, WHITE);
}
void Input() {
    frames++;
    if ((IsKeyPressed(KEY_SPACE) || LeverClicked()) && !leverPressed)//&& money != 0 && money >= credit
    {
        AnimationRow = 1;
    }
}
std::size_t hashFunction(int money) {
    std::hash<int> hasher;
    return hasher(money);
}
void saveMoney(const char* filename) {
    std::ofstream file;
    file.open(filename);

    if (file.is_open()) {
        std::string encryptedMoney = std::to_string(playerMoney);
        file << encryptedMoney << "\n";
        file << hashFunction(playerMoney);
        file.close();
    }
    else {
        std::cout << "Missing money.txt\n";
    }
}
void loadMoney(const char* filename) {
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        std::string encryptedMoney;
        file >> encryptedMoney;
        std::size_t savedHash;
        file >> savedHash;

        playerMoney = std::stoi(encryptedMoney);
        if (hashFunction(playerMoney) != savedHash) {
            std::cout << "Money data has been tampered!\n";
            playerMoney = 3000; // Reset
        }

        file.close();
    }
    else {
        std::cout << "Unable to open file for reading.\n";
    }
}
void DispWall4(int i) {
    float scale = 64.0f/512.0f;
    for (int j = 0; j < 12; j++) {
        DrawTextureEx(block, { u * 4.0f + j * u * 0.5f, u * 1.7f }, 0, scale, WHITE);
        DrawTextureEx(block, { u * 4.0f , u * 1.7f + j * u * 0.5f }, 0, scale, WHITE);
        DrawTextureEx(block, { u * 9.5f , u * 1.7f + j * u * 0.5f }, 0, scale, WHITE);
        DrawTextureEx(block, { u * 4.0f + j * u * 0.5f , u * 7.2f }, 0, scale, WHITE);
    }
    //top
    if (i <= Mission1.COLS * 2 + 2) {
        for (int j = 0; j < i; j++) {
        DrawTextureEx(block, { u * 4.5f + j * u * 0.5f, u * 2.2 }, 0, scale, WHITE);
        }
    }
    else {
        for (int j = 0; j < Mission1.COLS * 2 + 2; j++) {
            DrawTextureEx(block, { u * 4.5f + j * u * 0.5f, u * 2.2 }, 0, scale, WHITE);
        }
    }
    //right
    if (i > Mission1.COLS * 2 + 2 && i <= Mission1.COLS * 2 + 2 + Mission1.COLS * 2 + 1) {
        for (int j = 0; j < i-Mission1.COLS * 2 -2; j++) {
            DrawTextureEx(block, { u * 4.5f + (Mission1.COLS * 2 + 1)*u * 0.5f, u * 2.2f + (j+1) * u * 0.5f }, 0, scale, WHITE);
        }
    }
    else if (i > Mission1.COLS * 2 + 2 + Mission1.COLS * 2 + 1) {
        for (int j = 0; j < Mission1.COLS * 2 + 1; j++) {
            DrawTextureEx(block, { u * 4.5f + (Mission1.COLS * 2 + 1) * u * 0.5f, u * 2.2f + (j + 1) * u * 0.5f }, 0, scale, WHITE);
        }
    }
    //bottom
    if (i > Mission1.COLS * 4 + 3 && i <= Mission1.COLS * 4 + 3 + Mission1.COLS * 2 + 1) {
        for (int j = 0; j < i-Mission1.COLS * 4 - 3; j++) {
            DrawTextureEx(block, { u * 8.5f - j * u * 0.5f, u * 6.7 }, 0, scale, WHITE);
   
        }
    }
    else if (i > Mission1.COLS * 6 + 4 ) {
        for (int j = 0; j < Mission1.COLS * 2 + 1; j++) {
            DrawTextureEx(block, { u * 8.5f - j * u * 0.5f, u * 6.7 }, 0, scale, WHITE);
        }
    }
    //left
    if (i > Mission1.COLS * 6 + 4 && i <= Mission1.COLS * 6 + 4 + Mission1.COLS * 2 ) {
        for (int j = 0; j < i - Mission1.COLS * 6 - 4; j++) {
            DrawTextureEx(block, { u * 4.5f , u * 6.2f - j * u * 0.5f }, 0, scale, WHITE);

        }
    }
    else if (i > Mission1.COLS * 6 + 4) {
        for (int j = 0; j < Mission1.COLS * 2 ; j++) {
            DrawTextureEx(block, { u * 4.5f , u * 6.2f - j * u * 0.5f }, 0, scale, WHITE);
        }
    }
}
void DispWall5(int i) {
    float scale = 64.0f / 512.0f;
    //top
    if (i <= Mission2.COLS * 2 + 2) {
        for (int j = 0; j < i; j++) {
            DrawTextureEx(block, { u * 4.0f + j * u * 0.5f, u * 1.7 }, 0, scale, WHITE);
        }
    }
    else {
        for (int j = 0; j < Mission2.COLS * 2 + 2; j++) {
            DrawTextureEx(block, { u * 4.0f + j * u * 0.5f, u * 1.7 }, 0, scale, WHITE);
        }
    }
    //right
    if (i > Mission2.COLS * 2 + 2 && i <= Mission2.COLS * 2 + 2 + Mission2.COLS * 2 + 1) {
        for (int j = 0; j < i - Mission2.COLS * 2 - 2; j++) {
            DrawTextureEx(block, { u * 4.0f + (Mission2.COLS * 2 + 1) * u * 0.5f, u * 1.7f + (j + 1) * u * 0.5f }, 0, scale, WHITE);
        }
    }
    else if (i > Mission2.COLS * 2 + 2 + Mission2.COLS * 2 + 1) {
        for (int j = 0; j < Mission2.COLS * 2 + 1; j++) {
            DrawTextureEx(block, { u * 4.0f + (Mission2.COLS * 2 + 1) * u * 0.5f, u * 1.7f + (j + 1) * u * 0.5f }, 0, scale, WHITE);
        }
    }
    //bottom
    if (i > Mission2.COLS * 4 + 3 && i <= Mission2.COLS * 4 + 3 + Mission2.COLS * 2 + 1) {
        for (int j = 0; j < i - Mission2.COLS * 4 - 3; j++) {
            DrawTextureEx(block, { u * 9.0f - j * u * 0.5f, u * 7.2 }, 0, scale, WHITE);

        }
    }
    else if (i > Mission2.COLS * 6 + 4) {
        for (int j = 0; j < Mission2.COLS * 2 + 1; j++) {
            DrawTextureEx(block, { u * 9.0f - j * u * 0.5f, u * 7.2 }, 0, scale, WHITE);
        }
    }
    //left
    if (i > Mission2.COLS * 6 + 4 && i <= Mission2.COLS * 6 + 4 + Mission2.COLS * 2) {
        for (int j = 0; j < i - Mission2.COLS * 6 - 4; j++) {
            DrawTextureEx(block, { u * 4.0f , u * 6.7f - j * u * 0.5f }, 0, scale, WHITE);

        }
    }
    else if (i > Mission2.COLS * 6 + 4) {
        for (int j = 0; j < Mission2.COLS * 2; j++) {
            DrawTextureEx(block, { u * 4.5f , u * 6.7f - j * u * 0.5f }, 0, scale, WHITE);
        }
    }
}
void BG4(int i) 
{
    //DrawRectangle(u * 4, u * 1.7, u * 6, u * 6, BLACK);
    //DrawRectangle(u * 4, u * 0.4, u * 6, u, BLACK);
    //DrawRectangle(u * 0.5, u * 0.8, u * 3, u * 1.5, BLACK);
    //DrawRectangle(u * 10.5, u * 0.8, u * 3, u * 3, BLACK);
    //DrawRectangle(u * 10.5, u * 5.5, u * 3, u * 1.7, WHITE);
    //DrawRectangle(u * 5, u * 2.7, u , u , WHITE);
    DispWall4(blocks_4);
}
void BG5(int i)
{
    //DrawRectangle(u * 4, u * 1.7, u * 6, u * 6, BLACK);
    //DrawRectangle(u * 4, u * 0.4, u * 6, u, BLACK);
    //DrawRectangle(u * 0.5, u * 0.8, u * 3, u * 1.5, BLACK);
    //DrawRectangle(u * 10.5, u * 0.8, u * 3, u * 3, BLACK);
    //DrawRectangle(u * 10.5, u * 5.5, u * 3, u * 1.7, WHITE);
    //DrawRectangle(u * 5, u * 2.7, u , u , WHITE);
    DispWall5(blocks_5);
}
void Init4()
{
    BeginDrawing();
    BG4(0);
    PlayAnimation4();
    EndDrawing();
}
void Init5()
{
    BeginDrawing();
    BG5(0);
    PlayAnimation5();
    EndDrawing();
}
void Init6()
{
    BeginDrawing();
    PlayAnimation6();
    EndDrawing();
}
void Disp4(std::vector<std::vector<int>>& board)
{
    float scale_u = 1.0f / 4.0f;
    BeginDrawing();
    BG4(0);
    int i = 0;
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            DrawTextureEx(Sprites1[board[y][x]-1], {u * (5.0f + x), u * (2.7f + y)}, 0, scale_u, WHITE);
        }
    }
    EndDrawing();
}
void Disp5(std::vector<std::vector<int>>& board)
{
    float scale_u = 1.0f / 4.0f;
    BeginDrawing();
    BG5(0);
    int i = 0;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            DrawTextureEx(Sprites2[board[y][x] - 1], { u * (4.5f + x), u * (2.2f + y) }, 0, scale_u, WHITE);
        }
    }
    EndDrawing();
}
void Disp6(std::vector<std::vector<int>>& board)
{
    float scale_u = 1.0f / 4.0f;
    BeginDrawing();
    int i = 0;
    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 6; y++) {
            DrawTextureEx(Sprites3[board[y][x] - 1], { u * (4.0f + x), u * (1.7f + y) }, 0, scale_u, WHITE);
        }
    }
    EndDrawing();
}

int main() {
    /*
    playerMoney = 3000;
    saveMoney("money.txt");
    return 0;
    */
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    loadMoney("money.txt");
	InitWindow(u * 14, u * 8.2, "Slot Beta 0.0");
	SetTargetFPS(60);
	LoadElements();
    Font myFont = LoadFontEx("nightside/WarPriestRegular-PanE.ttf", 100, 0, 0);
	//Test();
	int mission = 1;
	int frame_timer = 0;
	int freeze_frames = 80;
    char bonus_tx[32];
    int rounds=1;
    //blocks_4 = 36;
    blocks_4 = 5;
    blocks_5 = 5;
    //blocks_5 = 44;
	int process_flag = 0;//Should do 0: animation, 1: init and wait for click 2: remove 3: fallen 4: replenish 9: Mission Change
	bool need_freeze = false;
    bool prevent_click = false;
    bool is_initial = true;
    std::vector<std::vector<std::vector<int>>> connectionmap;
    while (!WindowShouldClose())
    {
        Input();
        ClearBackground(BLACK);
        DrawTextEx(myFont, "nyalathotep", { 4.33 * u, u* 0.6 }, myFont.baseSize , 2, RED);//nyalathotep
        DrawTextEx(myFont, "Click Here", { 10.5 * u, u * 5.56 }, myFont.baseSize*0.5, 2, DARKGRAY);
        DrawTextEx(myFont, "Or Press Space", { 10.5 * u, u * 6.5 }, myFont.baseSize * 0.5, 2, DARKGRAY);
        char moneyText[128];
        sprintf(moneyText, "GOLD: %d", playerMoney);
        DrawTextEx(myFont, moneyText, { 1.0 * u, u * 2.6 }, myFont.baseSize * 0.5, 1, GOLD);
        switch (mission) {
        case 1: {
            //Initial Board
            if ((IsKeyPressed(KEY_SPACE) || LeverClicked()) && !leverPressed && process_flag == 1 && !need_freeze) {
                Mission1.initBoard4(Mission1.board);
                playerMoney -= 20;
                saveMoney("money.txt");
                srand(time(NULL));
                Mission1.printBoard4(Mission1.board);
                Disp4(Mission1.board);
                leverPressed = true;
                frame_timer = 0;
                process_flag = 2;
            }
            if(leverPressed && frame_timer <= freeze_frames) {
                Disp4(Mission1.board);
                frame_timer += 1;
            }
            if(leverPressed && frame_timer > freeze_frames) {
                leverPressed = false;
                frame_timer = 0;
			}
			//Remove Connection
			if (!leverPressed && process_flag == 2) {
				connectionmap = Mission1.ConnectionDetect(Mission1.board);
                bonus = Mission1.BonusLookup4(Mission1.board, connectionmap);
                playerMoney += bonus;
                sprintf(bonus_tx, "+ %d", bonus);
                DrawTextEx(myFont, bonus_tx, { 1.0 * u, u * 3.6 }, myFont.baseSize * 0.5, 1, RED);
                saveMoney("money.txt");
                bonus = 0;
                is_initial = false;
                blocks_4 -= Mission1.RemoveConnection(Mission1.board, connectionmap);;
				Disp4(Mission1.board);
				process_flag = 3;
				need_freeze = true;
			}
			if (need_freeze && frame_timer <= freeze_frames) {
				Disp4(Mission1.board);
                DrawTextEx(myFont, bonus_tx, { 1.0 * u, u * 3.6 }, myFont.baseSize * 0.5, 1, RED);
				frame_timer += 1;
			}
			if (need_freeze && frame_timer > freeze_frames) {
				need_freeze = false;
				frame_timer = 0;
			}
			//Fallen
			if (!leverPressed && !need_freeze && process_flag == 3) {
				Mission1.DropDown(Mission1.board);
				Disp4(Mission1.board);
				process_flag = 4;
				need_freeze = false;
			}
			//Replenish
			if (!leverPressed && !need_freeze && process_flag == 4) {
				std::vector<std::vector<int>> replenishmap;
                Mission1.initReplenishBoard4(Mission1.replenishboard);
				replenishmap = Mission1.ReplenishMap(connectionmap);
				Mission1.Replenish(Mission1.board, Mission1.replenishboard, replenishmap);
				Disp4(Mission1.board);
                std::cout << "Test success" << std::endl;
				connectionmap = Mission1.ConnectionDetect(Mission1.board);
				need_freeze = true;
                process_flag = 1;
			}
			if (need_freeze && frame_timer <= freeze_frames) {
				Disp4(Mission1.board);
				frame_timer += 1;
			}
			if (need_freeze && frame_timer > freeze_frames) {
				need_freeze = false;
				frame_timer = 0;
			}
            //Check Again
			if (!Mission1.IsFinished(connectionmap) && !is_initial && !need_freeze && !leverPressed && process_flag == 1) {
                process_flag = 2;
			}
            else if (Mission1.IsFinished(connectionmap) && !is_initial && !need_freeze && !leverPressed && process_flag == 1) {
				process_flag = 0;  
			}
            //Run Animation
            if (!leverPressed && !need_freeze && (process_flag == 0 || process_flag == 1)) {
                Init4();
                process_flag = 1;
                prevent_click = true;
            }
            if (prevent_click && frame_timer <= freeze_frames/2) {
                frame_timer += 1;
            }
            if (prevent_click && frame_timer > freeze_frames/2) {
                prevent_click = false;
                frame_timer = 0;
            }
            if (blocks_4 <= 0) {
                process_flag = 0;
                prevent_click = false;
                mission += 1;
                frame_timer = 0;
                need_freeze = false;
            }
            break;
        }
        case 2: {
            //Initial Board
            if ((IsKeyPressed(KEY_SPACE) || LeverClicked()) && !leverPressed && process_flag == 1 && !need_freeze) {
                Mission2.initBoard5(Mission2.board);
                playerMoney -= 30;
                saveMoney("money.txt");
                srand(time(NULL));
                Mission2.printBoard5(Mission2.board);
                Disp5(Mission2.board);
                leverPressed = true;
                frame_timer = 0;
                process_flag = 2;
            }
            if (leverPressed && frame_timer <= freeze_frames) {
                Disp5(Mission2.board);
                frame_timer += 1;
            }
            if (leverPressed && frame_timer > freeze_frames) {
                leverPressed = false;
                frame_timer = 0;
            }
            //Remove Connection
            if (!leverPressed && process_flag == 2) {
                connectionmap = Mission2.ConnectionDetect(Mission2.board);
                bonus = Mission2.BonusLookup5(Mission2.board, connectionmap);
                playerMoney += bonus;
                sprintf(bonus_tx, "+ %d", bonus);
                DrawTextEx(myFont, bonus_tx, { 1.0 * u, u * 3.6 }, myFont.baseSize * 0.5, 1, RED);
                saveMoney("money.txt");
                bonus = 0;
                is_initial = false;
                blocks_5 -= Mission2.RemoveConnection(Mission2.board, connectionmap);;
                Disp5(Mission2.board);
                process_flag = 3;
                need_freeze = true;
            }
            if (need_freeze && frame_timer <= freeze_frames) {
                Disp5(Mission2.board);
                DrawTextEx(myFont, bonus_tx, { 1.0 * u, u * 3.6 }, myFont.baseSize * 0.5, 1, RED);
                frame_timer += 1;
            }
            if (need_freeze && frame_timer > freeze_frames) {
                need_freeze = false;
                frame_timer = 0;
            }
            //Fallen
            if (!leverPressed && !need_freeze && process_flag == 3) {
                Mission2.DropDown(Mission2.board);
                Disp5(Mission2.board);
                process_flag = 4;
                need_freeze = false;
            }
            //Replenish
            if (!leverPressed && !need_freeze && process_flag == 4) {
                std::vector<std::vector<int>> replenishmap;
                Mission2.initReplenishBoard5(Mission2.replenishboard);
                replenishmap = Mission2.ReplenishMap(connectionmap);
                Mission2.Replenish(Mission2.board, Mission2.replenishboard, replenishmap);
                Disp5(Mission2.board);
                std::cout << "Test success" << std::endl;
                connectionmap = Mission2.ConnectionDetect(Mission2.board);
                need_freeze = true;
                process_flag = 1;
            }
            if (need_freeze && frame_timer <= freeze_frames) {
                Disp5(Mission2.board);
                frame_timer += 1;
            }
            if (need_freeze && frame_timer > freeze_frames) {
                need_freeze = false;
                frame_timer = 0;
            }
            //Check Again
            if (!Mission2.IsFinished(connectionmap) && !is_initial && !need_freeze && !leverPressed && process_flag == 1) {
                process_flag = 2;
            }
            else if (Mission2.IsFinished(connectionmap) && !is_initial && !need_freeze && !leverPressed && process_flag == 1) {
                process_flag = 0;
            }
            //Run Animation
            if (!leverPressed && !need_freeze && (process_flag == 0 || process_flag == 1)) {
                Init5();
                process_flag = 1;
                prevent_click = true;
            }
            if (prevent_click && frame_timer <= freeze_frames / 2) {
                frame_timer += 1;
            }
            if (prevent_click && frame_timer > freeze_frames / 2) {
                prevent_click = false;
                frame_timer = 0;
            }
            if (blocks_5 <= 0) {
                process_flag = 0;
                prevent_click = false;
                mission += 1;
                frame_timer = 0;
                need_freeze = false;
            }
            break;
        }
        case 3: {
            //Initial Board
            if ((IsKeyPressed(KEY_SPACE) || LeverClicked()) && !leverPressed && process_flag == 1 && !need_freeze) {
                Mission3.initBoard6(Mission3.board);
                playerMoney -= 50;
                saveMoney("money.txt");
                srand(time(NULL));
                Mission3.printBoard6(Mission3.board);
                Disp6(Mission3.board);
                leverPressed = true;
                frame_timer = 0;
                process_flag = 2;
            }
            if (leverPressed && frame_timer <= freeze_frames) {
                Disp6(Mission3.board);
                frame_timer += 1;
            }
            if (leverPressed && frame_timer > freeze_frames) {
                leverPressed = false;
                frame_timer = 0;
            }
            //Remove Connection
            if (!leverPressed && process_flag == 2) {
                connectionmap = Mission3.ConnectionDetect(Mission3.board);
                bonus = Mission3.BonusLookup6(Mission3.board, connectionmap);
                playerMoney += bonus;
                sprintf(bonus_tx, "+ %d", bonus);
                DrawTextEx(myFont, bonus_tx, { 1.0 * u, u * 3.6 }, myFont.baseSize * 0.5, 1, RED);
                saveMoney("money.txt");
                bonus = 0;
                is_initial = false;
                blocks_6 -= Mission3.RemoveConnection(Mission3.board, connectionmap);;
                Disp6(Mission3.board);
                process_flag = 3;
                need_freeze = true;
            }
            if (need_freeze && frame_timer <= freeze_frames) {
                Disp6(Mission3.board);
                DrawTextEx(myFont, bonus_tx, { 1.0 * u, u * 3.6 }, myFont.baseSize * 0.5, 1, RED);
                frame_timer += 1;
            }
            if (need_freeze && frame_timer > freeze_frames) {
                need_freeze = false;
                frame_timer = 0;
            }
            //Fallen
            if (!leverPressed && !need_freeze && process_flag == 3) {
                Mission3.DropDown(Mission3.board);
                Disp6(Mission3.board);
                process_flag = 4;
                need_freeze = false;
            }
            //Replenish
            if (!leverPressed && !need_freeze && process_flag == 4) {
                std::vector<std::vector<int>> replenishmap;
                Mission3.initReplenishBoard6(Mission3.replenishboard);
                replenishmap = Mission3.ReplenishMap(connectionmap);
                Mission3.Replenish(Mission3.board, Mission3.replenishboard, replenishmap);
                Disp6(Mission3.board);
                std::cout << "Test success" << std::endl;
                connectionmap = Mission3.ConnectionDetect(Mission3.board);
                need_freeze = true;
                process_flag = 1;
            }
            if (need_freeze && frame_timer <= freeze_frames) {
                Disp6(Mission3.board);
                frame_timer += 1;
            }
            if (need_freeze && frame_timer > freeze_frames) {
                need_freeze = false;
                frame_timer = 0;
            }
            //Check Again
            if (!Mission3.IsFinished(connectionmap) && !is_initial && !need_freeze && !leverPressed && process_flag == 1) {
                process_flag = 2;
            }
            else if (Mission3.IsFinished(connectionmap) && !is_initial && !need_freeze && !leverPressed && process_flag == 1) {
                process_flag = 0;
            }
            //Run Animation
            if (!leverPressed && !need_freeze && (process_flag == 0 || process_flag == 1)) {
                Init6();
                process_flag = 1;
                prevent_click = true;
            }
            if (prevent_click && frame_timer <= freeze_frames / 2) {
                frame_timer += 1;
            }
            if (prevent_click && frame_timer > freeze_frames / 2) {
                prevent_click = false;
                frame_timer = 0;
            }
            break;
        }
    }
        /*
        if(mission_success&&mission<3){
            mission += 1;
        }
*/
    }
    CloseWindow();

}