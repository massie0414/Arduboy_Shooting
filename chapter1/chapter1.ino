#include <Arduboy2.h>

Arduboy2 arduboy;

class Character {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    Character(int x, int y, int w, int h);
};

Character::Character(
    int xx,
    int yy,
    int ww,
    int hh)
{
    x = xx;
    y = yy;
    w = ww;
    h = hh;
}

// プレイヤーのグラフィックデータ
const uint8_t bmp_player[8] PROGMEM = {
    0,16,150,121,121,150,16,0
};

// プレイヤーの初期位置と大きさ
Character player(10,28,8,8);

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
}

void loop() {
    if (!(arduboy.nextFrame())){
        return;
    }

    arduboy.clear();

    // プレイヤーの描画
    arduboy.drawBitmap(
        player.x,
        player.y,
        bmp_player,
        player.w,
        player.h,
        WHITE
    );

    arduboy.display();
}

