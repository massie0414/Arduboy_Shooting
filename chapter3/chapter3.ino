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

// 弾のグラフィックデータ
const uint8_t bmp_bullet[4] PROGMEM = {
    6,9,9,6
};

// ブロックのグラフィックデータ
const uint8_t bmp_block[8] PROGMEM = {
    238,14,238,224,238,14,238,224
};

// 弾の生存フラグ
bool is_bullet = false;

// 壁の生存フラグ
bool is_block = true;

// プレイヤーの初期位置と大きさ
Character player(10,28,8,8);

// 弾の初期位置と大きさ
Character bullet(0,0,4,4);

// ブロックの初期位置と大きさ
Character block(100,28,8,8);

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
}

void loop() {
    if (!(arduboy.nextFrame())){
        return;
    }

    // 弾を発射させるためのキー入力
    if ( is_bullet == false && arduboy.pressed(A_BUTTON) ) {
      is_bullet = true;
      bullet.x = player.x + 4;
      bullet.y = player.y + 2;
    }

    // プレイヤーを移動させるためのキー入力
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

    // 弾の処理
    if(is_bullet){
        bullet.x ++;

        // 画面外の判定
        if(bullet.x > 128){
            // 画面外に行ったので弾を消滅
            is_bullet = false;
        }

        // ブロックとの衝突判定
        if ( is_block == true
          && block.x  <= bullet.x + bullet.w 
          && bullet.x <= block.x + block.w  // ここは使わない
          && block.y  <= bullet.y + bullet.h
          && bullet.y <= block.y + block.h
        ) {
            // ブロックに当たった
            
            // 弾を消す
            is_bullet = false;

            // ブロックを消す
            is_block = false;
        }
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

    // 弾の描画
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

    // ブロックの描画
    if(is_block){
        arduboy.drawBitmap(
            block.x,
            block.y,
            bmp_block,
            block.w,
            block.h,
            WHITE
        );
    }

    arduboy.display();
}

