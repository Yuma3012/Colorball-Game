#include "def.h"
#include "mlib.h"

#define g 9.8

int main(int Number) {
	int m, n, mm = 0, nn = 0, r = 10;
	double x = 0, y = 95, w = 100, h = 100;
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // 画面をリセットするフラグ
	int found = 0;

	while (1) { //While()文は()内が0になるまで繰り返すので、例では無限ループ,物体がラインに到達するまで
		short pl, pr, pd;
		pl = GetAsyncKeyState(VK_LEFT);//左キーの状態入力
		pr = GetAsyncKeyState(VK_RIGHT);//右キーの状態入力
		pd = GetAsyncKeyState(VK_DOWN);//下キーの状態入力
		switch (Number) {
		case 0:

			if (!resetScreen) {
				Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
				Rect(-w, h, w, -h, 1);
			}
			Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
			Circle(mm - r, nn - r, mm + r, nn + r, 1);        //過去の位置に描かれた円を消去

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
			Plot_pen(0, 2, 3);  //緑色に指定   
			Circle(m - r, n - r, m + r, n + r, 1);        //新しい位置に円を描画
			Plot_pen(0, 2, 1);
			Line(-sGW.w, n+10, sGW.w, n+10); //デッドライン



			mm = m; nn = n;       //新しいピクセル座標を過去のピクセル座標にする

			if (pd < 0) {
				found = 1;

			}
                
			if (found == 1) {
				while (y >= -h+0.5*r) {
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
			
		break;
		case 1:
			Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
			Rect(-w, h, w, -h, 1);
			break;
		}
	}
}


