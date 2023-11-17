#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
#define g 9.8
// 色と値を表す構造体
struct ColorValue {
	int color;
	int radius;
};
int main(int Number) {
	int m, n, mm = 0, nn = 0;
	double x = 0, y = 95, w = 100, h = 100;
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // 画面をリセットするフラグ
	int found = 0;

	// 色と値のペアを配列に格納
	struct ColorValue colorValues[] = {
		{0, 70}, //黒
		{1, 60}, //赤
		{2, 50}, //緑
		{3, 40}, //青
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

		//球が下に当たったら処理を終了する
	// ラベルを使用してswitch内でループを制御する
main_loop:

	while (1) { //While()文は()内が0になるまで繰り返すので、1では無限ループ,物体がラインに到達するまで
		short pl, pr, pd;
		pl = GetAsyncKeyState(VK_LEFT);//左キーの状態入力
		pr = GetAsyncKeyState(VK_RIGHT);//右キーの状態入力
		pd = GetAsyncKeyState(VK_DOWN);//下キーの状態入力

		//case1の処理がおわったらcase0の処理をおこなう
		
		switch (Number) {
		case 0:

			if (!resetScreen) {
				Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
				Rect(-w, h, w, -h, 1);
			}

			Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
			Circle(mm - r, nn - r, mm + r, nn + r, 1);        //過去の位置に描かれた円を消去
			
			Plot_pen(0, 2, 1);
			Line(-sGW.w, h-60, sGW.w, h-60); //デッドライン
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

			m = sGW.w / 2 * (x / w + 1);//実座標をピクセル座標に変換sgw960/2*(0/101)=480
			n = sGW.h / 2 * (1 - y / h);//実座標をピクセル座標に変換620/2*(1-95/100)=291.4
			Plot_pen(0, 2, color);  //緑色に指定   
			Circle(m - r, n - r, m + r, n + r, 1);        //新しい位置に円を描画




			mm = m; nn = n;       //新しいピクセル座標を過去のピクセル座標にする

			if (pd < 0) {
				found = 1;

			}
                
			if (found == 1) {
				while (y >= -h) {
					Plot_pen(0, 2, 7); //白色に設定（バックと同じ）
					Circle(mm - r, nn - r, mm + r, nn + r, 1); //過去の玉を消去
					y = y + vy * dt - g * dt * dt / 2;  //  z座標更新
					vy = vy - g * dt;         //  z方向速度更新

					vy = vy - g * dt; // z方向速度更新
					if (y < -h) { // 物体が下床に当たったとき、
						y = -h;
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

					Plot_pen(0, 2, 3); //緑色に指定
					Circle(m - r, n - r, m + r, n + r, 1);   //新しい位置に玉を描画

					Refresh();  //画面更新

					mm = m; //新しいピクセル座標を過去のピクセル座標に
					nn = n; //新しいピクセル座標を過去のピクセル座標に
				}
				found = 0;
				
			}
			Refresh();        //画面更新
			//Printf("処理完了");
		    break;
		case 1:
			// 画面をリセットする
			resetScreen = 1;
			Plot_pen(0, 2, 1);  //白色に設定（バックと同じ）
			//Rect(-w, h, w, -h, 1);
			Line(-sGW.w, h - 60, sGW.w, h - 60); //デッドライン
			break;
		}
		// switch の先頭に戻る
		goto main_loop;
	}
}


