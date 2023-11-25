#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
//MAINWIN_W=1200,MAINWIN_H=800�̂Ƃ�
#define W 133
#define H 100
#define g 9.8
#define MAX_BALLS 100
int count;
int x2m(double x) {//�s�N�Z�����W�ւ̕ϊ�
	return sGW.w / 2 * (1 + x / W);
}

int y2n(double y) {//�s�N�Z�����W�ւ̕ϊ�
	return sGW.h / 2 * (1 - y / H);
}

// �F�ƒl��\���\����
struct ColorValue {
	int color;
	int radius;
};
//Ball���Ƃ̏����i�[����\����
struct Ball {
	double x;
	double y;
	double vx;
	double vy;
	int r;
	int color;
};	
struct Ball balls[MAX_BALLS]; // �ʂ̔z��(�O���[�o���ϐ�)
int main(int Number) {
	int m = 10, n, mm = 0, nn = 0, start_x = sGW.w / 2 * (0 / 100 + 1), start_y = sGW.h / 10;
	double x = 0, y = 90, w = 100, h = 100, real_r, xx = x, yy = y;//�ߋ��̍��W
	double vy=0, dt = 5e-3, vx = 0;
	double e = 0, pp = 0; //�����W����0
	int resetScreen = 0; // ��ʂ����Z�b�g����t���O
	int found = 0;

	// �F�ƒl�̃y�A��z��Ɋi�[
	struct ColorValue colorValues[] = {
		//{0, 35}, //��
		//{1, 30}, //��
		//{2, 25}, //��
		//{3, 20}, //��ctrlk>ctrlc/u�ŃR�����g�A�E�g
		{4, 15}, //���F
		{5, 10}, //���F
		{6, 5}  //�s���N
	};
	// ���������̂��߂̃V�[�h��ݒ�
	srand(time(NULL));

	// �����_���ɃC���f�b�N�X��I��
	int randomIndex = rand() % (sizeof(colorValues) / sizeof(colorValues[0]));

	// �I�����ꂽ�F�Ɣ��a�̃y�A���擾
	int color = colorValues[randomIndex].color;
	int r = colorValues[randomIndex].radius;
	real_r = h * (sGW.h - 2 * r) / sGW.h; //�{�[���̎��ۂ̔��a



	//�������ɓ��������珈�����I������
// ���x�����g�p����switch���Ń��[�v�𐧌䂷��
	count++; // Increment count on each iteration
	//Printf("count = %d\n", count);
	//���̂̑��xvy��1��菬�����Ȃ�܂Ń��[�v
	while(fabs(vy) > 0.01 or vy == 0) {


		//case1�̏��������������case0�̏����������Ȃ�

		switch (Number) {
		case 0:

			//if (!resetScreen) {
			//	Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			//	Rect(-w, h, w, -h, 1);
			//}
			//y�����ɂ��܂Ń��[�v
			//Printf("sGW.h = %d", sGW.h);
			//Printf("sGW.w = %d", sGW.w);

			real_r = h * (sGW.h - 2 * r) / sGW.h; //�{�[���̎��ۂ̔��a
			/*		Printf("real_r%f", real_r);*/
					//while (1) { //y > -real_r
			short pl, pr, pd;
			pl = GetAsyncKeyState(VK_LEFT);//���L�[�̏�ԓ���
			pr = GetAsyncKeyState(VK_RIGHT);//�E�L�[�̏�ԓ���
			pd = GetAsyncKeyState(VK_DOWN);//���L�[�̏�ԓ���

			Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������

			Plot_pen(0, 2, 1);
			Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //�f�b�h���C��
			if (pl < 0) {
				x = x - 0.1;     //���L�[�������ꂽ�Ƃ��̏���
				if (x < -W + r) { // ���̂����ǂɓ��������Ƃ�
					x = W - r;
				}
			}
			if (pr < 0) {
				x = x + 0.1;     //�E�L�[�������ꂽ�Ƃ��̏���
				if (x > W - r) { // ���̂��E�ǂɓ��������Ƃ�
					x = -W + r;
				}
			}


			Plot_pen(0, 2, color);  //�ΐF�Ɏw��   
			Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
			xx = x;   //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���
			yy = y;   //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���




			if (pd < 0) {
				found = 1;
				vy = 1;
				//Plot_pen(0, 2, color);  //�ΐF�Ɏw��   
				//Circle(start_x - r, start_y - r, start_x + r, start_y + r, 1);        //�V�����ʒu�ɉ~��`��m,n�͉~�̒��S���W
			}

			if (found == 1) {
				real_r = h * (sGW.h - 2 * r) / sGW.h; //�����W�ɕϊ�
				while (fabs(vy) > 0.01) { //���x��1��菬�����Ȃ�܂Ń��[�v
					Plot_pen(0, 2, 7); //���F�ɐݒ�i�o�b�N�Ɠ����j
					Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������
					y = y + vy * dt - g * dt * dt / 2;  //  z���W�X�V
					vy = vy - g * dt;         //  z�������x�X�V
					
					if (y < -H + r) { // ���̂������ɓ��������Ƃ��A
						y = -H + r;
						vy = 0.0001;
					} //z�͏��ɂ߂荞��ł���̂�-h�ɏC��

					if (x < -W + r) { // ���̂����ǂɓ��������Ƃ��A
						vx = -e * vx; // ���x�ɔ��ˌW������Z
						x = -W + r;
					} //z�͉E�ɂ߂荞��ł���̂�w�ɏC��


					if (x > W - r) { // ���̂����ɓ��������Ƃ��A
						vx = -e * vx; // ���x�ɔ��ˌW������Z
						x = W - r;
					} //z�͍��ɂ߂荞��ł���̂�-w�ɏC��

					if (count > 1) {
						// �Փ˔���ƏՓˌ�̋���
						for (int i = 1; i < count; i++) {
							double dx = x - balls[i].x;
							double dy = y - balls[i].y;
							double distanceSquared = dx * dx + dy * dy; // ������2��

							double sumRadiiSquared = (r + balls[i].r) * (r + balls[i].r); // ���a�̘a��2��

							if (distanceSquared < sumRadiiSquared) { // �Փ˔���
								// �Փˎ��̏���
								//Printf("color = %d\n", balls[i].color);
								//Printf("distanceSquared=%f,sumRadiiSquared=%f\n", distanceSquared, sumRadiiSquared);
								//pp = (1 + e) * (balls[i].vx - vx);
								//vx = vx + m / (m + m) * pp;    //���O�̏Փˌ㑬�x�X�V
								//vy = vy - m / (m + m) * pp;    //���O�̏Փˌ㑬�x�X�V
								vy = vy * e;
								balls[i].vx = balls[i].vx - m / (m + m) * pp;    //���P�̏Փˌ㑬�x�X�V
								balls[i].vy = balls[i].vy - m / (m + m) * pp;    //���P�̏Փˌ㑬�x�X�V
								//Plot_pen(0, 2, color); //�ΐF�Ɏw��
								//Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
								//Plot_pen(0, 2, balls[i].color); //�ԐF�Ɏw��
								//Circle(x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), 1);
								//// ���x�x�N�g���̐��^�ϊ��ƌ���
								//double tempVx = vx;
								//double tempVy = vy;

								//vx = balls[i].vx;
								//vy = balls[i].vy;

								//balls[i].vx = tempVx;
								//balls[i].vy = tempVy;

								if (fabs(vy) < 1) vy = 0.0001; // ���x���������Ȃ�����0�ɂ���
								
							}
						}
					}
					
					Plot_pen(0, 2, color); //�ΐF�Ɏw��
					Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
					Refresh();  //��ʍX�V
					xx = x;   //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���
					yy = y;   //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���


					//for (int i = 0; i < count; i++) {
					//	if (fabs(x - balls[i].x) < r + balls[i].r ) {       //���S����d�ʓ��m���Ԃ������Ƃ�
					//		pp = (1 + e) * (balls[i].vx - vx);
					//		vx = vx + m / (m + m) * pp;    //���O�̏Փˌ㑬�x�X�V
					//		vy = vy + m / (m + m) * pp;    //���O�̏Փˌ㑬�x�X�V
					//		balls[i].vx  = balls[i].vx - m / (m + m) * pp;    //���P�̏Փˌ㑬�x�X�V
					//		balls[i].vy = balls[i].vy - m / (m + m) * pp;    //���P�̏Փˌ㑬�x�X�V
					//		Plot_pen(0, 2, color); //�ΐF�Ɏw��
					//		Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
					//		Plot_pen(0, 2, balls[i].color); //�ԐF�Ɏw��
					//		Circle(x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), 1);
					//	}
					//}



				}



				//Printf("color = %d\n", balls[color].color);
				
				Plot_pen(0, 2, 1);
				Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //�f�b�h���C��

				balls[count].x = x;
				balls[count].y = y;
				balls[count].vx = vx;
				balls[count].vy = vy;
				balls[count].r = r;
				balls[count].color = color;
				found = 0;
				
				


			}
			Refresh();        //��ʍX�V
			//}
			//
			break;
		case 1:
			Plot_pen(0, 2, 1);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			//Rect(-w, h, w, -h, 1);
			Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //�f�b�h���C��
			break;
		}

	}
}


