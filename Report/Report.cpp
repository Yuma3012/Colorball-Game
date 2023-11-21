#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
//MAINWIN_W=1200,MAINWIN_H=800のとき
#define W 133
#define H 100
#define g 9.8
int count;
int x2m(double x) {//ピクセル座標への変換
	return sGW.w / 2 * (1 + x / W);
}

int y2n(double y) {//ピクセル座標への変換
	return sGW.h / 2 * (1 - y / H);
}

// 色と値を表す構造体
struct ColorValue {
	int color;
	int radius;
};
int main(int Number) {
	int m, n, mm = 0, nn = 0, start_x = sGW.w / 2 * (0 / 100 + 1) , start_y = sGW.h / 10;
	double x = 0, y = 90, w = 100, h = 100, real_r, xx = x, yy = y;//過去の座標
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // 画面をリセットするフラグ
	int found = 0;

	// 色と値のペアを配列に格納
	struct ColorValue colorValues[] = {
		//{0, 35}, //黒
		//{1, 30}, //赤
		//{2, 25}, //緑
		//{3, 20}, //青ctrlk>ctrlc/uでコメントアウト
		{4, 15}, //黄色
		{5, 10}, //水色
		{6, 5}  //ピンク
	};
	// 乱数生成のためのシードを設定
	srand(time(NULL));

	// ランダムにインデックスを選択
	int randomIndex = rand() % (sizeof(colorValues) / sizeof(colorValues[0]));

	// 選択された色と半径のペアを取得
	int color = colorValues[randomIndex].color;
	int r = colorValues[randomIndex].radius;
	real_r = h * (sGW.h - 2 * r) / sGW.h; //ボールの実際の半径
		//球が下に当たったら処理を終了する
	// ラベルを使用してswitch内でループを制御する
	count++; // Increment count on each iteration
	Printf("count = %d\n", count);

	while (y > -real_r) { //While()文は()内が0になるまで繰り返すので、1では無限ループ,物体がラインに到達するまで


		//case1の処理がおわったらcase0の処理をおこなう
		
		switch (Number) {
		case 0:

			//if (!resetScreen) {
			//	Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
			//	Rect(-w, h, w, -h, 1);
			//}
			//yが床につくまでループ
			//Printf("sGW.h = %d", sGW.h);
			//Printf("sGW.w = %d", sGW.w);

			real_r = h * (sGW.h - 2 * r) / sGW.h; //ボールの実際の半径
	/*		Printf("real_r%f", real_r);*/
			//while (1) { //y > -real_r
				short pl, pr, pd;
				pl = GetAsyncKeyState(VK_LEFT);//左キーの状態入力
				pr = GetAsyncKeyState(VK_RIGHT);//右キーの状態入力
				pd = GetAsyncKeyState(VK_DOWN);//下キーの状態入力

				Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
				Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //過去の位置に描かれた円を消去

				Plot_pen(0, 2, 1);
				Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //デッドライン
				if (pl < 0) {
					x = x - 0.1;     //左キーが押されたときの処理
					if (x < -(W - r)) {
						x = W - r;
					}
				}
				if (pr < 0) {
					x = x + 0.1;     //右キーが押されたときの処理
					if (x > W - r) {
						x = -(W - r);
					}
				}


				Plot_pen(0, 2, color);  //緑色に指定   
				Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
				xx = x;   //新しいピクセル座標を過去のピクセル座標にする
				yy = y;   //新しいピクセル座標を過去のピクセル座標にする




				if (pd < 0) {
					found = 1;
					//Plot_pen(0, 2, color);  //緑色に指定   
					//Circle(start_x - r, start_y - r, start_x + r, start_y + r, 1);        //新しい位置に円を描画m,nは円の中心座標
				}

				if (found == 1) {
					real_r = h*(sGW.h - 2 * r) / sGW.h; //実座標に変換
					while (y > -real_r) {
						Plot_pen(0, 2, 7); //白色に設定（バックと同じ）
						Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //過去の位置に描かれた円を消去
						y = y + vy * dt - g * dt * dt / 2;  //  z座標更新
						vy = vy - g * dt;         //  z方向速度更新

						vy = vy - g * dt; // z方向速度更新
						if (y < -real_r) { // 物体が下床に当たったとき、
							y = -real_r;
						} //zは床にめり込んでいるので-hに修正

						//if (x > w) { // 物体が右に当たったとき、
						//	vx = -e * vx; // 速度に反射係数を乗算
						//	x = w;
						//} //zは右にめり込んでいるのでwに修正


						//if (x < -w) { // 物体が左に当たったとき、
						//	vx = -e * vx; // 速度に反射係数を乗算
						//	x = -w;
						//} //zは左にめり込んでいるので-wに修正




						Plot_pen(0, 2, color); //緑色に指定
						Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
						Refresh();  //画面更新
						xx = x;   //新しいピクセル座標を過去のピクセル座標にする
						yy = y;   //新しいピクセル座標を過去のピクセル座標にする





					}
					found = 0;
				
				}
				Refresh();        //画面更新
			//}
			//
		    break;
		case 1:
			Plot_pen(0, 2, 1);  //白色に設定（バックと同じ）
			//Rect(-w, h, w, -h, 1);
			Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //デッドライン
			break;
		}

	}
}


