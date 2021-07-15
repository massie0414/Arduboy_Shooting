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

const uint8_t bmp_player[8] PROGMEM = {
    0,16,150,121,121,150,16,0
};

const uint8_t bmp_bullet[4] PROGMEM = {
    6,9,9,6
};

bool is_bullet = false;

Character player(10,28,8,8);
Character bullet(0,0,4,4);

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
}

void loop() {
    if (!(arduboy.nextFrame())){
        return;
    }

    // 入力
    if ( is_bullet == false && arduboy.pressed(A_BUTTON) ) {
      is_bullet = true;
      bullet.x = player.x + 4;
      bullet.y = player.y + 2;
    }

    if ( arduboy.pressed(LEFT_BUTTON) ) {
      player.x --;
    }
    if ( arduboy.pressed(RIGHT_BUTTON) ) {
      player.x ++;
    }
    if ( arduboy.pressed(UP_BUTTON) ) {
      player.y --;
    }
    if ( arduboy.pressed(DOWN_BUTTON) ) {
      player.y ++;
    }

    // 処理
    if(is_bullet){
        bullet.x ++;
        if(bullet.x > 128){
            // 画面外に行ったので消滅
            is_bullet = false;
            bullet.x = 0;
            bullet.y = 0;
        }
    }

    arduboy.clear();

    arduboy.drawBitmap(
        player.x,
        player.y,
        bmp_player,
        player.w,
        player.h,
        WHITE
    );

    if(is_bullet){
        arduboy.drawBitmap(
            bullet.x,
            bullet.y,
            bmp_bullet,
            bullet.w,
            bullet.h,
            WHITE
        );
    }

    arduboy.display();
}
