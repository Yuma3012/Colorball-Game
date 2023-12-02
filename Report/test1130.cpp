#include "def.h"
#include "mlib.h"
#include <iostream>
#include <vector>
//MAINWIN_W=200,MAINWIN_H=100のとき
#define W 133
#define H 100

int x2m(double x) {//座標変換
	return sGW.w / 2 * (x / W + 1);
}
int y2m(double y) {//座標変換
	return sGW.h / 2 * (1 - y / H);
}
int main(int Number) {

	double e = 0.95;
	short pl, pr, pu;
	double x2 = 0, y2 = -93, x3 = 0, y3 = -86, x2_past = 0, y2_past = 0, x3_past = 0, y3_past = 0, v0 = 15, theta = 35, vx = 0, vy = 0, dt = 5e-3, g = 9.8;
	int rise = 0;

	while (1) { //While()文は()内が0になるまで繰り返すので、例では無限ループ

		pl = GetAsyncKeyState(VK_LEFT);
		pr = GetAsyncKeyState(VK_RIGHT);
		pu = GetAsyncKeyState(VK_RETURN); //押されたキーに従って座標を更新


		//背景を黒
		int x1 = 0, y1 = 0;

		Plot_pen(0, 2, 0);

		Rect(x2m(x1 - 200), y2m(y1 + 100), x2m(x1 + 200), y2m(y1 - 100), 1);

		//パドルを表示

		Plot_pen(0, 2, 4);

		if (pl < 0) {
			x2 = x2 - 0.3;
			x3 = x3 - 0.3;
		}
		if (pr < 0) {
			x2 = x2 + 0.3;
			x3 = x3 + 0.3;
		}



		Rect(x2m(x2 - 24), y2m(y2 + 3), x2m(x2 + 24), y2m(y2 - 3), 1);


		//ブロックを表示1列目
		int x4 = -112, y4 = 88;

		Plot_pen(0, 2, 2);

		Rect(x2m(x4 - 8), y2m(y4 + 8), x2m(x4 + 8), y2m(y4 - 8), 1);

		int x5 = -84, y5 = 88;

		Plot_pen(0, 2, 2);

		Rect(x2m(x5 - 8), y2m(y5 + 8), x2m(x5 + 8), y2m(y5 - 8), 1);

		int x6 = -56, y6 = 88;

		Plot_pen(0, 2, 2);

		Rect(x2m(x6 - 8), y2m(y6 + 8), x2m(x6 + 8), y2m(y6 - 8), 1);

		int x7 = -28, y7 = 88;

		Plot_pen(0, 2, 3);

		Rect(x2m(x7 - 8), y2m(y7 + 8), x2m(x7 + 8), y2m(y7 - 8), 1);

		int x8 = 0, y8 = 88;

		Plot_pen(0, 2, 1);

		Rect(x2m(x8 - 8), y2m(y8 + 8), x2m(x8 + 8), y2m(y8 - 8), 1);

		int x9 = 28, y9 = 88;

		Plot_pen(0, 2, 3);

		Rect(x2m(x9 - 8), y2m(y9 + 8), x2m(x9 + 8), y2m(y9 - 8), 1);

		int x10 = 56, y10 = 88;

		Plot_pen(0, 2, 2);

		Rect(x2m(x10 - 8), y2m(y10 + 8), x2m(x10 + 8), y2m(y10 - 8), 1);

		int x11 = 84, y11 = 88;

		Plot_pen(0, 2, 2);

		Rect(x2m(x11 - 8), y2m(y11 + 8), x2m(x11 + 8), y2m(y11 - 8), 1);

		int x12 = 112, y12 = 88;

		Plot_pen(0, 2, 2);

		Rect(x2m(x12 - 8), y2m(y12 + 8), x2m(x12 + 8), y2m(y12 - 8), 1);


		//ブロックを表示2列目
		int x13 = -112, y13 = 68;

		Plot_pen(0, 2, 2);

		Rect(x2m(x13 - 8), y2m(y13 + 8), x2m(x13 + 8), y2m(y13 - 8), 1);

		int x14 = -84, y14 = 68;

		Plot_pen(0, 2, 2);

		Rect(x2m(x14 - 8), y2m(y14 + 8), x2m(x14 + 8), y2m(y14 - 8), 1);

		int x15 = -56, y15 = 68;

		Plot_pen(0, 2, 2);

		Rect(x2m(x15 - 8), y2m(y15 + 8), x2m(x15 + 8), y2m(y15 - 8), 1);

		int x16 = -28, y16 = 68;

		Plot_pen(0, 2, 3);

		Rect(x2m(x16 - 8), y2m(y16 + 8), x2m(x16 + 8), y2m(y16 - 8), 1);

		int x17 = 0, y17 = 68;

		Plot_pen(0, 2, 3);

		Rect(x2m(x17 - 8), y2m(y17 + 8), x2m(x17 + 8), y2m(y17 - 8), 1);

		int x18 = 28, y18 = 68;

		Plot_pen(0, 2, 3);

		Rect(x2m(x18 - 8), y2m(y18 + 8), x2m(x18 + 8), y2m(y18 - 8), 1);

		int x19 = 56, y19 = 68;

		Plot_pen(0, 2, 2);

		Rect(x2m(x19 - 8), y2m(y19 + 8), x2m(x19 + 8), y2m(y19 - 8), 1);

		int x20 = 84, y20 = 68;

		Plot_pen(0, 2, 2);

		Rect(x2m(x20 - 8), y2m(y20 + 8), x2m(x20 + 8), y2m(y20 - 8), 1);

		int x21 = 112, y21 = 68;

		Plot_pen(0, 2, 2);

		Rect(x2m(x21 - 8), y2m(y21 + 8), x2m(x21 + 8), y2m(y21 - 8), 1);

		//ブロックを表示3列目
		int x22 = -112, y22 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x22 - 8), y2m(y22 + 8), x2m(x22 + 8), y2m(y22 - 8), 1);

		int x23 = -84, y23 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x23 - 8), y2m(y23 + 8), x2m(x23 + 8), y2m(y23 - 8), 1);

		int x24 = -56, y24 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x24 - 8), y2m(y24 + 8), x2m(x24 + 8), y2m(y24 - 8), 1);

		int x25 = -28, y25 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x25 - 8), y2m(y25 + 8), x2m(x25 + 8), y2m(y25 - 8), 1);

		int x26 = 0, y26 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x26 - 8), y2m(y26 + 8), x2m(x26 + 8), y2m(y26 - 8), 1);

		int x27 = 28, y27 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x27 - 8), y2m(y27 + 8), x2m(x27 + 8), y2m(y27 - 8), 1);

		int x28 = 56, y28 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x28 - 8), y2m(y28 + 8), x2m(x28 + 8), y2m(y28 - 8), 1);

		int x29 = 84, y29 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x29 - 8), y2m(y29 + 8), x2m(x29 + 8), y2m(y29 - 8), 1);

		int x30 = 112, y30 = 48;

		Plot_pen(0, 2, 2);

		Rect(x2m(x30 - 8), y2m(y30 + 8), x2m(x30 + 8), y2m(y30 - 8), 1);


		//球を表示

		Plot_pen(0, 2, 7);

		if (pu < 0) rise = 1;
		if (rise == 1) {
			double radian = theta / 180 * 3.14;
			vx = v0 * cos(radian);
			vy = v0 * sin(radian);
			int flug4 = 0, flug5 = 0, flug6 = 0, flug7 = 0, flug8 = 0, flug9 = 0, flug10 = 0;
			int flug11 = 0, flug12 = 0, flug13 = 0, flug14 = 0, flug15 = 0, flug16 = 0, flug17 = 0, flug18 = 0, flug19 = 0, flug20 = 0;
			int flug21 = 0, flug22 = 0, flug23 = 0, flug24 = 0, flug25 = 0, flug26 = 0, flug27 = 0, flug28 = 0, flug29 = 0, flug30 = 0;
			while (y3 > -H - 10) {

				Plot_pen(0, 2, 0);
				Circle(x2m(x3_past - 4), y2m(y3_past + 4), x2m(x3_past + 4), y2m(y3_past - 4), 1);
				Rect(x2m(x2_past - 24), y2m(y2_past + 3), x2m(x2_past + 24), y2m(y2_past - 3), 1);

				Plot_pen(0, 2, 4);
				pl = GetAsyncKeyState(VK_LEFT);
				pr = GetAsyncKeyState(VK_RIGHT);
				pu = GetAsyncKeyState(VK_RETURN); //押されたキーに従って座標を更新
				if (pl < 0) x2 = x2 - 0.1;
				if (pr < 0) x2 = x2 + 0.1;


				Rect(x2m(x2 - 24), y2m(y2 + 3), x2m(x2 + 24), y2m(y2 - 3), 1);
				//Printf("x2%f", x2);
				x2_past = x2;
				y2_past = y2;
				x3 = x3 + vx * dt + g * dt * dt / 2;   //　x座標更新

				y3 = y3 + vy * dt + g * dt * dt / 2;//  z方向速度更新
				// 速度に反射係数を乗算


				if (x3 > W) {
					vx = -e * vx;
					x3 = W;
				}  // 物体が床に当たったとき、

				if (x3 < -W) {
					vx = -e * vx;
					x3 = -W;
				}
				if (y3 > H) {
					vy = -e * vy;
					y3 = H;
				}

				/*if (y3 < H) {
					vy = -e * vy;
					y3 = H;
				}*/

				int Eight_balls[8];
				//Printf("x2", x2);
				Eight_balls[0] = x2 - 21;
				Eight_balls[1] = x2 - 15;
				Eight_balls[2] = x2 - 9;
				Eight_balls[3] = x2 - 3;
				Eight_balls[4] = x2 + 3;
				Eight_balls[5] = x2 + 9;
				Eight_balls[6] = x2 + 15;
				Eight_balls[7] = x2 + 21;
				for (int i = 0; i < 8; ++i) {
					double dx = x3 - Eight_balls[i];
					double dy = y3 - y2;
					double d = dx * dx + dy * dy;
					double sumr = (3 + 4) * (3 + 4);

					if (d < sumr) {
						vy = -e * vy;
						y3 = y2 + 10; // 衝突後、ボールをパドル上に配置する
						theta = theta + 5;
						Printf("ひゃっほー!!!\n");
					}
				}




				//ここから
				double dx_4 = x3 - x4;
				double dy_4 = y3 - y4;
				double dx4 = x3 - x4;
				double dy4 = y3 - y4;
				double d4 = dx4 * dx4 + dy4 * dy4;
				double sumr4 = (4 + 8) * (4 + 8);
				if (d4 < sumr4 && flug4 == 0) {

					if (fabs(dx_4) < fabs(dy_4) && y3 > y4) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y4 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_4) < fabs(dy_4) && y3 < y4) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y4 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_4) > fabs(dy_4) && x3 > x4) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x4 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_4) > fabs(dy_4) && x3 < x4) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x4 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x4 - 8), y2m(y4 + 8), x2m(x4 + 8), y2m(y4 - 8), 1);
					Refresh();
					Printf("ナイスwww\n");
					flug4 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_5 = x3 - x5;
				double dy_5 = y3 - y5;
				double dx5 = x3 - x5;
				double dy5 = y3 - y5;
				double d5 = dx5 * dx5 + dy5 * dy5;
				double sumr5 = (4 + 8) * (4 + 8);
				if (d5 < sumr5 && flug5 == 0) {

					if (fabs(dx_5) < fabs(dy_5) && y3 > y5) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y5 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_5) < fabs(dy_5) && y3 < y5) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y5 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_5) > fabs(dy_5) && x3 > x5) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x5 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_5) > fabs(dy_5) && x3 < x5) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x5 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x5 - 8), y2m(y5 + 8), x2m(x5 + 8), y2m(y5 - 8), 1);
					Refresh();
					Printf("うますぎwww\n");
					flug5 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_6 = x3 - x6;
				double dy_6 = y3 - y6;
				double dx6 = x3 - x6;
				double dy6 = y3 - y6;
				double d6 = dx6 * dx6 + dy6 * dy6;
				double sumr6 = (4 + 8) * (4 + 8);
				if (d6 < sumr6 && flug6 == 0) {

					if (fabs(dx_6) < fabs(dy_6) && y3 > y6) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y6 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_6) < fabs(dy_6) && y3 < y6) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y6 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_6) > fabs(dy_6) && x3 > x6) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x6 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_6) > fabs(dy_6) && x3 < x6) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x6 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x6 - 8), y2m(y6 + 8), x2m(x6 + 8), y2m(y6 - 8), 1);
					Refresh();
					Printf("天才!!!\n");
					flug6 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_7 = x3 - x7;
				double dy_7 = y3 - y7;
				double dx7 = x3 - x7;
				double dy7 = y3 - y7;
				double d7 = dx7 * dx7 + dy7 * dy7;
				double sumr7 = (4 + 8) * (4 + 8);
				if (d7 < sumr7 && flug7 == 0) {

					if (fabs(dx_7) < fabs(dy_7) && y3 > y7) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y7 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_7) < fabs(dy_7) && y3 < y7) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y7 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_7) > fabs(dy_7) && x3 > x7) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x7 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_7) > fabs(dy_7) && x3 < x7) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x7 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x7 - 8), y2m(y7 + 8), x2m(x7 + 8), y2m(y7 - 8), 1);
					Refresh();
					Printf("ボスはすぐ横だ!!!\n");
					flug7 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_8 = x3 - x8;
				double dy_8 = y3 - y8;
				double dx8 = x3 - x8;
				double dy8 = y3 - y8;
				double d8 = dx8 * dx8 + dy8 * dy8;
				double sumr8 = (4 + 8) * (4 + 8);
				if (d8 < sumr8 && flug8 == 0) {

					if (fabs(dx_8) < fabs(dy_8) && y3 > y8) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y8 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_8) < fabs(dy_8) && y3 < y8) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y8 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_8) > fabs(dy_8) && x3 > x8) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x8 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_8) > fabs(dy_8) && x3 < x8) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x8 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x8 - 8), y2m(y8 + 8), x2m(x8 + 8), y2m(y8 - 8), 1);
					Plot_pen(0, 2, 0);
					Printf("おめでとう!!!ボスを倒したwww\n");
					flug8 = 1;  // 衝突処理が終わったことを示すフラグをセット
					break;
				}
				//ここまで

				//ここから
				double dx_9 = x3 - x9;
				double dy_9 = y3 - y9;
				double dx9 = x3 - x9;
				double dy9 = y3 - y9;
				double d9 = dx9 * dx9 + dy9 * dy9;
				double sumr9 = (4 + 8) * (4 + 8);
				if (d9 < sumr9 && flug9 == 0) {

					if (fabs(dx_9) < fabs(dy_9) && y3 > y9) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y9 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_9) < fabs(dy_9) && y3 < y9) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y9 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_9) > fabs(dy_9) && x3 > x9) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x9 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_9) > fabs(dy_9) && x3 < x9) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x9 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x9 - 8), y2m(y9 + 8), x2m(x9 + 8), y2m(y9 - 8), 1);
					Refresh();
					Printf("ボスはすぐ横だ!!!\n");
					flug9 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_10 = x3 - x10;
				double dy_10 = y3 - y10;
				double dx10 = x3 - x10;
				double dy10 = y3 - y10;
				double d10 = dx10 * dx10 + dy10 * dy10;
				double sumr10 = (4 + 8) * (4 + 8);
				if (d10 < sumr10 && flug10 == 0) {

					if (fabs(dx_10) < fabs(dy_10) && y3 > y10) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y10 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_10) < fabs(dy_10) && y3 < y10) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y10 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_10) > fabs(dy_10) && x3 > x10) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x10 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_10) > fabs(dy_10) && x3 < x10) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x10 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x10 - 8), y2m(y10 + 8), x2m(x10 + 8), y2m(y10 - 8), 1);
					Refresh();
					Printf("天才www\n");
					flug10 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_11 = x3 - x11;
				double dy_11 = y3 - y11;
				double dx11 = x3 - x11;
				double dy11 = y3 - y11;
				double d11 = dx11 * dx11 + dy11 * dy11;
				double sumr11 = (4 + 8) * (4 + 8);
				if (d11 < sumr11 && flug11 == 0) {

					if (fabs(dx_11) < fabs(dy_11) && y3 > y11) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y11 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_11) < fabs(dy_11) && y3 < y11) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y11 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_11) > fabs(dy_11) && x3 > x11) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x11 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_11) > fabs(dy_11) && x3 < x11) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x11 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x11 - 8), y2m(y11 + 8), x2m(x11 + 8), y2m(y11 - 8), 1);
					Refresh();
					Printf("がんばれい!\n");
					flug11 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_12 = x3 - x12;
				double dy_12 = y3 - y12;
				double dx12 = x3 - x12;
				double dy12 = y3 - y12;
				double d12 = dx12 * dx12 + dy12 * dy12;
				double sumr12 = (4 + 8) * (4 + 8);
				if (d12 < sumr12 && flug12 == 0) {

					if (fabs(dx_12) < fabs(dy_12) && y3 > y12) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y12 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_12) < fabs(dy_12) && y3 < y12) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y12 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_12) > fabs(dy_12) && x3 > x12) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x12 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_12) > fabs(dy_12) && x3 < x12) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x12 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x12 - 8), y2m(y12 + 8), x2m(x12 + 8), y2m(y12 - 8), 1);
					Refresh();
					Printf("まだまだ!!!\n");
					flug12 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_13 = x3 - x13;
				double dy_13 = y3 - y13;
				double dx13 = x3 - x13;
				double dy13 = y3 - y13;
				double d13 = dx13 * dx13 + dy13 * dy13;
				double sumr13 = (4 + 8) * (4 + 8);
				if (d13 < sumr13 && flug13 == 0) {

					if (fabs(dx_13) < fabs(dy_13) && y3 > y13) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y13 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_13) < fabs(dy_13) && y3 < y13) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y13 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_13) > fabs(dy_13) && x3 > x13) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x13 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_13) > fabs(dy_13) && x3 < x13) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x13 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x13 - 8), y2m(y13 + 8), x2m(x13 + 8), y2m(y13 - 8), 1);
					Refresh();
					Printf("ナイスゥwww\n");
					flug13 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_14 = x3 - x14;
				double dy_14 = y3 - y14;
				double dx14 = x3 - x14;
				double dy14 = y3 - y14;
				double d14 = dx14 * dx14 + dy14 * dy14;
				double sumr14 = (4 + 8) * (4 + 8);
				if (d14 < sumr14 && flug14 == 0) {

					if (fabs(dx_14) < fabs(dy_14) && y3 > y14) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y14 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_14) < fabs(dy_14) && y3 < y14) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y14 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_14) > fabs(dy_14) && x3 > x14) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x14 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_14) > fabs(dy_14) && x3 < x14) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x14 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x14 - 8), y2m(y14 + 8), x2m(x14 + 8), y2m(y14 - 8), 1);
					Refresh();
					Printf("やっほーwww\n");
					flug14 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_15 = x3 - x15;
				double dy_15 = y3 - y15;
				double dx15 = x3 - x15;
				double dy15 = y3 - y15;
				double d15 = dx15 * dx15 + dy15 * dy15;
				double sumr15 = (4 + 8) * (4 + 8);
				if (d15 < sumr15 && flug15 == 0) {

					if (fabs(dx_15) < fabs(dy_15) && y3 > y15) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y15 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_15) < fabs(dy_15) && y3 < y15) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y15 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_15) > fabs(dy_15) && x3 > x15) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x15 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_15) > fabs(dy_15) && x3 < x15) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x15 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x15 - 8), y2m(y15 + 8), x2m(x15 + 8), y2m(y15 - 8), 1);
					Refresh();
					Printf("ナイスゥwww\n");
					flug15 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_16 = x3 - x16;
				double dy_16 = y3 - y16;
				double dx16 = x3 - x16;
				double dy16 = y3 - y16;
				double d16 = dx16 * dx16 + dy16 * dy16;
				double sumr16 = (4 + 8) * (4 + 8);
				if (d16 < sumr16 && flug16 == 0) {

					if (fabs(dx_16) < fabs(dy_16) && y3 > y16) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y16 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_16) < fabs(dy_16) && y3 < y16) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y16 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_16) > fabs(dy_16) && x3 > x16) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x16 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_16) > fabs(dy_16) && x3 < x16) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x16 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x16 - 8), y2m(y16 + 8), x2m(x16 + 8), y2m(y16 - 8), 1);
					Refresh();
					Printf("やられたー\n");
					flug16 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_17 = x3 - x17;
				double dy_17 = y3 - y17;
				double dx17 = x3 - x17;
				double dy17 = y3 - y17;
				double d17 = dx17 * dx17 + dy17 * dy17;
				double sumr17 = (4 + 8) * (4 + 8);
				if (d17 < sumr17 && flug17 == 0) {

					if (fabs(dx_17) < fabs(dy_17) && y3 > y17) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y17 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_17) < fabs(dy_17) && y3 < y17) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y17 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_17) > fabs(dy_17) && x3 > x17) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x17 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_17) > fabs(dy_17) && x3 < x17) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x17 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x17 - 8), y2m(y17 + 8), x2m(x17 + 8), y2m(y17 - 8), 1);
					Refresh();
					Printf("ボスはすぐ上だ!!!\n");
					flug17 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_18 = x3 - x18;
				double dy_18 = y3 - y18;
				double dx18 = x3 - x18;
				double dy18 = y3 - y18;
				double d18 = dx18 * dx18 + dy18 * dy18;
				double sumr18 = (4 + 8) * (4 + 8);
				if (d18 < sumr18 && flug18 == 0) {

					if (fabs(dx_18) < fabs(dy_18) && y3 > y18) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y18 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_18) < fabs(dy_18) && y3 < y18) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y18 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_18) > fabs(dy_18) && x3 > x18) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x18 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_18) > fabs(dy_18) && x3 < x18) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x18 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x18 - 8), y2m(y18 + 8), x2m(x18 + 8), y2m(y18 - 8), 1);
					Refresh();
					Printf("やられたwww\n");
					flug18 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_19 = x3 - x19;
				double dy_19 = y3 - y19;
				double dx19 = x3 - x19;
				double dy19 = y3 - y19;
				double d19 = dx19 * dx19 + dy19 * dy19;
				double sumr19 = (4 + 8) * (4 + 8);
				if (d19 < sumr19 && flug19 == 0) {

					if (fabs(dx_19) < fabs(dy_19) && y3 > y19) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y19 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_19) < fabs(dy_19) && y3 < y19) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y19 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_19) > fabs(dy_19) && x3 > x19) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x19 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_19) > fabs(dy_19) && x3 < x19) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x19 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x19 - 8), y2m(y19 + 8), x2m(x19 + 8), y2m(y19 - 8), 1);
					Refresh();
					Printf("ナイスゥwww\n");
					flug19 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_20 = x3 - x20;
				double dy_20 = y3 - y20;
				double dx20 = x3 - x20;
				double dy20 = y3 - y20;
				double d20 = dx20 * dx20 + dy20 * dy20;
				double sumr20 = (4 + 8) * (4 + 8);
				if (d20 < sumr20 && flug20 == 0) {

					if (fabs(dx_20) < fabs(dy_20) && y3 > y20) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y20 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_20) < fabs(dy_20) && y3 < y20) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y20 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_20) > fabs(dy_20) && x3 > x20) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x20 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_20) > fabs(dy_20) && x3 < x20) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x20 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x20 - 8), y2m(y20 + 8), x2m(x20 + 8), y2m(y20 - 8), 1);
					Refresh();
					Printf("わっしょーーーいwww\n");
					flug20 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_21 = x3 - x21;
				double dy_21 = y3 - y21;
				double dx21 = x3 - x21;
				double dy21 = y3 - y21;
				double d21 = dx21 * dx21 + dy21 * dy21;
				double sumr21 = (4 + 8) * (4 + 8);
				if (d21 < sumr21 && flug21 == 0) {

					if (fabs(dx_21) < fabs(dy_21) && y3 > y21) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y21 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_21) < fabs(dy_21) && y3 < y21) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y21 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_21) > fabs(dy_21) && x3 > x21) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x21 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_21) > fabs(dy_21) && x3 < x21) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x21 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x21 - 8), y2m(y21 + 8), x2m(x21 + 8), y2m(y21 - 8), 1);
					Refresh();
					Printf("ナイスゥwww\n");
					flug21 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_22 = x3 - x22;
				double dy_22 = y3 - y22;
				double dx22 = x3 - x22;
				double dy22 = y3 - y22;
				double d22 = dx22 * dx22 + dy22 * dy22;
				double sumr22 = (4 + 8) * (4 + 8);
				if (d22 < sumr22 && flug22 == 0) {

					if (fabs(dx_22) < fabs(dy_22) && y3 > y22) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y22 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_22) < fabs(dy_22) && y3 < y22) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y22 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_22) > fabs(dy_22) && x3 > x22) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x22 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_22) > fabs(dy_22) && x3 < x22) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x22 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x22 - 8), y2m(y22 + 8), x2m(x22 + 8), y2m(y22 - 8), 1);
					Refresh();
					Printf("天才!!!\n");
					flug22 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_23 = x3 - x23;
				double dy_23 = y3 - y23;
				double dx23 = x3 - x23;
				double dy23 = y3 - y23;
				double d23 = dx23 * dx23 + dy23 * dy23;
				double sumr23 = (4 + 8) * (4 + 8);
				if (d23 < sumr23 && flug23 == 0) {

					if (fabs(dx_23) < fabs(dy_23) && y3 > y23) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y23 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_23) < fabs(dy_23) && y3 < y23) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y23 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_23) > fabs(dy_23) && x3 > x23) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x23 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_23) > fabs(dy_23) && x3 < x23) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x23 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x23 - 8), y2m(y23 + 8), x2m(x23 + 8), y2m(y23 - 8), 1);
					Refresh();
					Printf("WWWWWWWWW\n");
					flug23 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_24 = x3 - x24;
				double dy_24 = y3 - y24;
				double dx24 = x3 - x24;
				double dy24 = y3 - y24;
				double d24 = dx24 * dx24 + dy24 * dy24;
				double sumr24 = (4 + 8) * (4 + 8);
				if (d24 < sumr24 && flug24 == 0) {

					if (fabs(dx_24) < fabs(dy_24) && y3 > y24) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y24 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_24) < fabs(dy_24) && y3 < y24) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y24 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_24) > fabs(dy_24) && x3 > x24) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x24 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_24) > fabs(dy_24) && x3 < x24) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x24 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x24 - 8), y2m(y24 + 8), x2m(x24 + 8), y2m(y24 - 8), 1);
					Refresh();
					Printf("やるやん\n");
					flug24 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_25 = x3 - x25;
				double dy_25 = y3 - y25;
				double dx25 = x3 - x25;
				double dy25 = y3 - y25;
				double d25 = dx25 * dx25 + dy25 * dy25;
				double sumr25 = (4 + 8) * (4 + 8);
				if (d25 < sumr25 && flug25 == 0) {

					if (fabs(dx_25) < fabs(dy_25) && y3 > y25) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y25 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_25) < fabs(dy_25) && y3 < y25) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y25 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_25) > fabs(dy_25) && x3 > x25) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x25 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_25) > fabs(dy_25) && x3 < x25) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x25 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x25 - 8), y2m(y25 + 8), x2m(x25 + 8), y2m(y25 - 8), 1);
					Refresh();
					Printf("わーーーーお\n");
					flug25 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_26 = x3 - x26;
				double dy_26 = y3 - y26;
				double dx26 = x3 - x26;
				double dy26 = y3 - y26;
				double d26 = dx26 * dx26 + dy26 * dy26;
				double sumr26 = (4 + 8) * (4 + 8);
				if (d26 < sumr26 && flug26 == 0) {

					if (fabs(dx_26) < fabs(dy_26) && y3 > y26) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y26 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_26) < fabs(dy_26) && y3 < y26) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y26 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_26) > fabs(dy_26) && x3 > x26) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x26 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_26) > fabs(dy_26) && x3 < x26) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x26 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x26 - 8), y2m(y26 + 8), x2m(x26 + 8), y2m(y26 - 8), 1);
					Refresh();
					Printf("いい感じ!!!\n");
					flug26 = flug26 + 1;  // 衝突処理が終わったことを示すフラグをセット

				}

				//ここまで

				//ここから
				double dx_27 = x3 - x27;
				double dy_27 = y3 - y27;
				double dx27 = x3 - x27;
				double dy27 = y3 - y27;
				double d27 = dx27 * dx27 + dy27 * dy27;
				double sumr27 = (4 + 8) * (4 + 8);
				if (d27 < sumr27 && flug27 == 0) {

					if (fabs(dx_27) < fabs(dy_27) && y3 > y27) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y27 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_27) < fabs(dy_27) && y3 < y27) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y27 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_27) > fabs(dy_27) && x3 > x27) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x27 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_27) > fabs(dy_27) && x3 < x27) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x27 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x27 - 8), y2m(y27 + 8), x2m(x27 + 8), y2m(y27 - 8), 1);
					Refresh();
					Printf("ナイスゥwww\n");
					flug27 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_28 = x3 - x28;
				double dy_28 = y3 - y28;
				double dx28 = x3 - x28;
				double dy28 = y3 - y28;
				double d28 = dx28 * dx28 + dy28 * dy28;
				double sumr28 = (4 + 8) * (4 + 8);
				if (d28 < sumr28 && flug28 == 0) {

					if (fabs(dx_28) < fabs(dy_28) && y3 > y28) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y28 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_28) < fabs(dy_28) && y3 < y28) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y28 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_28) > fabs(dy_28) && x3 > x28) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x28 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_28) > fabs(dy_28) && x3 < x28) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x28 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x28 - 8), y2m(y28 + 8), x2m(x28 + 8), y2m(y28 - 8), 1);
					Refresh();
					Printf("うぇーーい\n");
					flug28 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_29 = x3 - x29;
				double dy_29 = y3 - y29;
				double dx29 = x3 - x29;
				double dy29 = y3 - y29;
				double d29 = dx29 * dx29 + dy29 * dy29;
				double sumr29 = (4 + 8) * (4 + 8);
				if (d29 < sumr29 && flug29 == 0) {

					if (fabs(dx_29) < fabs(dy_29) && y3 > y29) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y29 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_29) < fabs(dy_29) && y3 < y29) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y29 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_29) > fabs(dy_29) && x3 > x29) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x29 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_29) > fabs(dy_29) && x3 < x29) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x29 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x29 - 8), y2m(y29 + 8), x2m(x29 + 8), y2m(y29 - 8), 1);
					Refresh();
					Printf("ナイスゥwww\n");
					flug29 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで

				//ここから
				double dx_30 = x3 - x30;
				double dy_30 = y3 - y30;
				double dx30 = x3 - x30;
				double dy30 = y3 - y30;
				double d30 = dx30 * dx30 + dy30 * dy30;
				double sumr30 = (4 + 8) * (4 + 8);
				if (d30 < sumr30 && flug30 == 0) {

					if (fabs(dx_30) < fabs(dy_30) && y3 > y30) { //上だったら
						// 上側面の衝突
						vy = -e * vy;
						y3 = y30 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_30) < fabs(dy_30) && y3 < y30) {
						// 下側面の衝突
						vy = -e * vy;
						y3 = y30 - 8; // ボールの位置を調整
					}
					else if (fabs(dx_30) > fabs(dy_30) && x3 > x30) {
						// 右側面の衝突
						vx = -e * vx;
						x3 = x30 + 8; // ボールの位置を調整
					}
					else if (fabs(dx_30) > fabs(dy_30) && x3 < x30) {
						// 左側面の衝突
						vx = -e * vx;
						x3 = x30 - 8; // ボールの位置を調整
					}
					Plot_pen(0, 2, 0);
					Rect(x2m(x30 - 8), y2m(y30 + 8), x2m(x30 + 8), y2m(y30 - 8), 1);
					Refresh();
					Printf("すご!!!!!!\n");
					flug30 = 1;  // 衝突処理が終わったことを示すフラグをセット
				}
				//ここまで


				Plot_pen(0, 2, 7);
				Circle(x2m(x3 - 4), y2m(y3 + 4), x2m(x3 + 4), y2m(y3 - 4), 1);

				Refresh();//画面更新

				x3_past = x3;
				y3_past = y3;
			}
			rise = 0;

		}

		Circle(x2m(x3 - 4), y2m(y3 + 4), x2m(x3 + 4), y2m(y3 - 4), 1);
		Printf("敵をやっつけて、村を取り戻してくれ～\n");
		Refresh();//画面更新
	}


}