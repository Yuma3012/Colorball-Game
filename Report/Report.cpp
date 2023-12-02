#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
//MAINWIN_W=1200,MAINWIN_H=800のとき
#define W 133
#define H 100
#define g 9.8
#define MAX_BALLS 100
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
//Ballごとの情報を格納する構造体
struct Ball {
	double x;
	double y;
	double vx;
	double vy;
	int r;
	int color;
};	
struct Ball balls[MAX_BALLS]; // 玉の配列(グローバル変数)
int main(int Number) {
	int m = 10, n, mm = 0, nn = 0, start_x = sGW.w / 2 * (0 / 100 + 1), start_y = sGW.h / 10;
	double x = 0, y = 80, w = 100, h = 100, real_r, xx = x, yy = y;//過去の座標
	double vy=0, dt = 5e-3, vx = 0;
	double e = 0, pp = 0; //反発係数は0
	int resetScreen = 0; // 画面をリセットするフラグ
	int found = 0, found2;

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
	//Printf("count = %d\n", count);
	//物体の速度vyが1より小さくなるまでループ
	while(fabs(vy) > 0.01 or vy == 0 ) {


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
			//Line(x2m(xx), y2n(yy), x2m(xx), y2n(-H)); // 落下ライン
			Plot_pen(0, 4, 1);
			Line(x2m(-W), y2n(H - 10), x2m(W), y2n(H-10)); //デッドライン
			//Plot_pen(2, 1, 1);
			//Line(x2m(x), y2n(y), x2m(x), y2n(-H));
			if (pl < 0) {
				x = x - 0.1;     //左キーが押されたときの処理
				if (x < -W + r) { // 物体が左壁に当たったとき
					x = W - r;
				}
			}
			if (pr < 0) {
				x = x + 0.1;     //右キーが押されたときの処理
				if (x > W - r) { // 物体が右壁に当たったとき
					x = -W + r;
				}
			}


			Plot_pen(0, 2, color);  //緑色に指定   
			Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
			xx = x;   //新しいピクセル座標を過去のピクセル座標にする
			yy = y;   //新しいピクセル座標を過去のピクセル座標にする




			if (pd < 0) {
				found = 1;
				vy = 1;
				//Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
				//Line(x2m(x), y2n(y), x2m(x), y2n(-H));
				//Plot_pen(0, 2, color);  //緑色に指定   
				//Circle(start_x - r, start_y - r, start_x + r, start_y + r, 1);        //新しい位置に円を描画m,nは円の中心座標
			}

			if (found == 1) {
				real_r = h * (sGW.h - 2 * r) / sGW.h; //実座標に変換
				while (fabs(vy) > 0.01) { //速度が1より小さくなるまでループ
					Plot_pen(0, 2, 7); //白色に設定（バックと同じ）
					Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //過去の位置に描かれた円を消去
					y = y + vy * dt - g * dt * dt / 2;  //  z座標更新
					vy = vy - g * dt;         //  z方向速度更新
					
					if (y < -H + r) { // 物体が下床に当たったとき、
						y = -H + r;
						vy = 0.0001;
					} //zは床にめり込んでいるので-hに修正

					if (x < -W + r) { // 物体が左壁に当たったとき、
						vx = -e * vx; // 速度に反射係数を乗算
						x = -W + r;
					} //zは右にめり込んでいるのでwに修正


					if (x > W - r) { // 物体が左に当たったとき、
						vx = -e * vx; // 速度に反射係数を乗算
						x = W - r;
					} //zは左にめり込んでいるので-wに修正

					if (count > 1) {
						// 衝突判定と衝突後の挙動
						for (int i = 1; i < count; i++) {
							double dx = x - balls[i].x;
							double dy = y - balls[i].y;
							double distanceSquared = dx * dx + dy * dy; // 距離の2乗

							double sumRadiiSquared = (r + balls[i].r) * (r + balls[i].r); // 半径の和の2乗

							if (distanceSquared < sumRadiiSquared) {

								if (fabs(dx) < fabs(dy) && x == balls[i].x) { //真上だったら
									// 上側面の衝突
									vy = -e * vy;
									y = balls[i].y + balls[i].r + r + 0.1; // ボールの位置を調整
								}
								else if (fabs(dx) < fabs(dy) && y < balls[i].y) {
									// 下側面の衝突
									vy = -e * vy;
									y = balls[i].y - balls[i].r - r - 0.1; // ボールの位置を調整
								}
								else if ( x > balls[i].x) {
									// 右側面の衝突
									vx = -e * vx;
									x = balls[i].x + balls[i].r + r + 0.1; // ボールの位置を調整
								}
								else if ( x < balls[i].x) {
									// 左側面の衝突
									vx = -e * vx;
									x = balls[i].x - balls[i].r - r  - 0.1; // ボールの位置を調整
								}
								Refresh();
								Printf("衝突\n");
							}
						}
					}
					
					Plot_pen(0, 2, color); //緑色に指定
					Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
					Refresh();  //画面更新
					xx = x;   //新しいピクセル座標を過去のピクセル座標にする
					yy = y;   //新しいピクセル座標を過去のピクセル座標にする


					//for (int i = 0; i < count; i++) {
					//	if (fabs(x - balls[i].x) < r + balls[i].r ) {       //中心距離d玉同士がぶつかったとき
					//		pp = (1 + e) * (balls[i].vx - vx);
					//		vx = vx + m / (m + m) * pp;    //球０の衝突後速度更新
					//		vy = vy + m / (m + m) * pp;    //球０の衝突後速度更新
					//		balls[i].vx  = balls[i].vx - m / (m + m) * pp;    //球１の衝突後速度更新
					//		balls[i].vy = balls[i].vy - m / (m + m) * pp;    //球１の衝突後速度更新
					//		Plot_pen(0, 2, color); //緑色に指定
					//		Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
					//		Plot_pen(0, 2, balls[i].color); //赤色に指定
					//		Circle(x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), 1);
					//	}
					//}



				}



				//Printf("color = %d\n", balls[color].color);
				
				Plot_pen(0, 4, 1);
				Line(x2m(-W), y2n(H - 10), x2m(W), y2n(H - 10));

				balls[count].x = x;
				balls[count].y = y;
				balls[count].vx = vx;
				balls[count].vy = vy;
				balls[count].r = r;
				balls[count].color = color;
				found = 0;

				for (int i = 0; i < count; i++) {
					Plot_pen(0, 2, balls[i].color);
					Circle(x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), x2m(balls[i].x + balls[i].r), y2n(balls[i].y + balls[i].r), 1);

					
				}
				
				


			}
			Refresh();        //画面更新
			//}
			//
			break;
		case 1:
			Plot_pen(0, 2, 7);  //白色に設定（バックと同じ）
			Rect(x2m(-W), y2n(H), x2m(W), y2n(-H),1); //デッドライン
			found2 = 0;
			break;
		}

	}
}


