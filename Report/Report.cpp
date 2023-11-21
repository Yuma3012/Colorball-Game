#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
#define g 9.8
int count;
// 色と値を表す構造体
struct ColorValue {
	int color;
	int radius;
};
int main(int Number) {
	int m, n, mm = 0, nn = 0, start_x = sGW.w / 2 * (0 / 100 + 1) , start_y = sGW.h / 10;
	double x = 0, y = 90, w = 100, h = 100, real_r;
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // 画面をリセットするフラグ
	int found = 0;

	// 色と値のペアを配列に格納
	struct ColorValue colorValues[] = {
		//{0, 70}, //黒
		//{1, 60}, //赤
		//{2, 50}, //緑
		//{3, 40}, //青ctrlk>ctrlc/uでコメントアウト
		{4, 30}, //黄色
		{5, 20}, //水色
		{6, 10}  //ピンク
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
				Circle(mm - r, nn - r, mm + r, nn + r, 1);        //過去の位置に描かれた円を消去

				Plot_pen(0, 2, 1);
				Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //デッドライン
				if (pl < 0) {
					x = x - 0.1;     //左キーが押されたときの処理
					if (x < -w) {
						x = w;
					}
				}
				if (pr < 0) {
					x = x + 0.1;     //右キーが押されたときの処理
					if (x > w) {
						x = -w;
					}
				}

				m = sGW.w / 2 * (x / w + 1);//実座標をピクセル座標に変換sgw960/2*(0/101)=480sGw620
				n = sGW.h / 2 * (1 - y / h);//実座標をピクセル座標に変換620/2*(1-95/100)=291.4sGW710

				Plot_pen(0, 2, color);  //緑色に指定   
				Circle(m - r, n - r, m + r, n + r, 1);        //新しい位置に円を描画m,nは円の中心座標




				mm = m; nn = n;       //新しいピクセル座標を過去のピクセル座標にする

				if (pd < 0) {
					found = 1;
					//Plot_pen(0, 2, color);  //緑色に指定   
					//Circle(start_x - r, start_y - r, start_x + r, start_y + r, 1);        //新しい位置に円を描画m,nは円の中心座標
				}

				if (found == 1) {
					real_r = h*(sGW.h - 2 * n) / sGW.h; //実座標に変換
					while (y > -real_r) {
						Plot_pen(0, 2, 7); //白色に設定（バックと同じ）
						Circle(mm - r, nn - r, mm + r, nn + r, 1); //過去の玉を消去
						y = y + vy * dt - g * dt * dt / 2;  //  z座標更新
						vy = vy - g * dt;         //  z方向速度更新

						vy = vy - g * dt; // z方向速度更新
						if (y < -real_r) { // 物体が下床に当たったとき、
							y = -real_r;
						} //zは床にめり込んでいるので-hに修正

						if (x > w) { // 物体が右に当たったとき、
							vx = -e * vx; // 速度に反射係数を乗算
							x = w;
						} //zは右にめり込んでいるのでwに修正


						if (x < -w) { // 物体が左に当たったとき、
							vx = -e * vx; // 速度に反射係数を乗算
							x = -w;
						} //zは左にめり込んでいるので-wに修正



						m = sGW.w * (1 + x / w) / 2;  //実座標をピクセル座標に変換
						n = sGW.h * (1 - y / h) / 2;     //実座標をピクセル座標に変換
						//(z座標は上向きを正）)

						Plot_pen(0, 2, color); //緑色に指定
						Circle(m - r, n - r, m + r, n + r, 1);   //新しい位置に玉を描画

						Refresh();  //画面更新

						mm = m; //新しいピクセル座標を過去のピクセル座標に
						nn = n; //新しいピクセル座標を過去のピクセル座標に
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


