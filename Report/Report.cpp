#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
//MAINWIN_W=1200,MAINWIN_H=800�̂Ƃ�
#define W 133
#define H 100
#define g 9.8
#define MAX_BALLS 100
int count, score;
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
	double x = 0, y = 80, xx = x, yy = y;//�ߋ��̍��W
	double vx = 0, vy=0, dt = 5e-3;
	double e = 0; //�����W����0
	int found = 0; // �t���O

	// �F�ƒl�̃y�A��z��Ɋi�[�@
	struct ColorValue colorValues[] = {
		//{2, 35}, //��
		//{0, 30}, //��
		//{1, 25}, //��
		//{3, 20}, //��
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

	count++; // ���T�ڂ����J�E���g
	//���̂̑��xvy��0.01��菬�����Ȃ�܂Ń��[�v
	while(fabs(vy) > 0.01 or vy == 0 ) {

			short pl, pr, pd;
			pl = GetAsyncKeyState('A');//���L�[�̏�ԓ���
			pr = GetAsyncKeyState('D');//�E�L�[�̏�ԓ���
			pd = GetAsyncKeyState('S');//���L�[�̏�ԓ���

			Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������
			Plot_pen(0, 4, 1);
			Line(x2m(-W), y2n(H - 10), x2m(W), y2n(H-10)); //�f�b�h���C��

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
				vy = -50;
			}

			if (found == 1) {

				while (fabs(vy) > 0.01 ) { //���x��1��菬�����Ȃ�܂Ń��[�v
					Plot_pen(0, 4, 1);
					Line(x2m(-W), y2n(H - 10), x2m(W), y2n(H - 10));//�f�b�h���C��
					Plot_pen(0, 2, 7); //���F�ɐݒ�i�o�b�N�Ɠ����j
					Circle(x2m(xx - r), y2n(yy - r), x2m(xx + r), y2n(yy + r), 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������
					
					vy = vy - g * dt;         //  y�������x�X�V
					y = y + vy * dt - g * dt * dt / 2;  //  y���W�X�V
					x = x + vx * dt;         //  x���W�X�V
					
					if (y < -H + r) { // ���̂������ɓ��������Ƃ��A
						y = -H + r;
						vy = 0.0001;
					} //z�͏��ɂ߂荞��ł���̂ŏC��

					if (x < -W + r) { // ���̂����ǂɓ��������Ƃ��A
						vx = -e * vx; // ���x�ɔ��ˌW������Z
						x = -W + r;
					} //z�͉E�ɂ߂荞��ł���̂ŏC��


					if (x > W - r) { // ���̂����ɓ��������Ƃ��A
						vx = -e * vx; // ���x�ɔ��ˌW������Z
						x = W - r;
					} //z�͍��ɂ߂荞��ł���̂ŏC��

					if (count > 1) {
						// �Փ˔���ƏՓˌ�̋���
						for (int i = 1; i < count; i++) {
							double dx = x - balls[i].x;
							double dy = y - balls[i].y;
							double distanceSquared = dx * dx + dy * dy; // ������2��

							double sumRadiiSquared = (r + balls[i].r) * (r + balls[i].r); // ���a�̘a��2��

							if (distanceSquared < sumRadiiSquared) {
								if (color == balls[i].color) {
									Plot_pen(0, 2, 7); //���F�ɐݒ�i�o�b�N�Ɠ����j
									Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������
									Circle(x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), x2m(balls[i].x + balls[i].r), y2n(balls[i].y + balls[i].r), 1);
									double half_x = (x + balls[i].x) / 2;
									double half_y = (y + balls[i].y) / 2;
									
									switch (color) {
									case 6:
										color = 5;
										r = 10;
										score = score + 3;
										break;
									case 5:
										color = 4;
										r = 15;
										score = score + 5;
										break;
									case 4:
										color = 3;
										r = 20;
										score = score + 10;
										break;
									case 3:
										color = 1;
										r = 25;
										score = score + 20;
										break;
									case 1:
										color = 0;
										r = 30;
										score = score + 30;
										break;
									case 0:
										color = 2;
										r = 35;
										score = score + 40;
										break;
									case 2:
										color = 6;
										r = 5;
										score = score + 55;
										break;

									}

									x = half_x;
									y = half_y;
									balls[i].x = -5000;
                                    balls[i].y = -5000; //�Փ˂����{�[������ʊO�Ɉړ�
									Plot_pen(0, 2, color); 
									Circle(x2m(half_x - r), y2n(half_y - r), x2m(half_x + r), y2n(half_y + r), 1);        //���Ԓn�_�ɉ~��`��
								}
								else 
								{
									if (fabs(dx) < fabs(dy) and x > -0.25* balls[i].r + balls[i].x and x < 0.25 * balls[i].r + balls[i].x) { //��ʂ�������
										// �㑤�ʂ̏Փ�
										vy = 0.0001;
										y = balls[i].y + balls[i].r + r + 0.001; // �{�[���̈ʒu�𒲐�
									}
									else if (fabs(dx) < fabs(dy) && y < balls[i].y) {
										// �����ʂ̏Փ�
										vy = -e * vy;
										y = balls[i].y - balls[i].r - r - 0.001; // �{�[���̈ʒu�𒲐�
									}
									else if (x > balls[i].x) {
										// �E���ʂ̏Փ�
										vx = 2;
										x = balls[i].x + balls[i].r + r + 0.001; // �{�[���̈ʒu�𒲐�
									}
									else if (x < balls[i].x) {
										// �����ʂ̏Փ�
										vx = -2;
										x = balls[i].x - balls[i].r - r - 0.001; // �{�[���̈ʒu�𒲐�
									}
								}
								Refresh();
							}
						}
					}
					Plot_pen(0, 2, color); //�ΐF�Ɏw��
					Circle(x2m(x - r), y2n(y - r), x2m(x + r), y2n(y + r), 1);
					Refresh();  //��ʍX�V
					xx = x;   //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���
					yy = y;   //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���
					
					for (int i = 0; i < count; i++) {	
						Plot_pen(0, 2, balls[i].color);
						Circle(x2m(balls[i].x - balls[i].r), y2n(balls[i].y - balls[i].r), x2m(balls[i].x + balls[i].r), y2n(balls[i].y + balls[i].r), 1);
					}
				}

				if (y - r > H - 20) { //�f�b�h���C���ɋ��̉��������G�ꂽ��
					Printf("�Q�[���I�[�o�[\n");
					Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
					Rect(x2m(-W), y2n(H), x2m(W), y2n(-H), 1); //�f�b�h���C��
					score = 0;
					for (int i = 0; i < MAX_BALLS; ++i) {
						balls[i].x = -5000;
						balls[i].y = -5000;
						balls[i].vx = 0.0;
						balls[i].vy = 0.0;
						balls[i].r = 0;
						balls[i].color = 7;
					}
					break;
				}

				Plot_pen(0, 4, 1);
				Line(x2m(-W), y2n(H - 10), x2m(W), y2n(H - 10));

				balls[count].x = x;
				balls[count].y = y;
				balls[count].vx = vx;
				balls[count].vy = vy;
				balls[count].r = r;
				balls[count].color = color;
				found = 0;
				Printf("�X�R�A:%d\n", score);
			
			}
			Refresh();        //��ʍX�V
			
	}
}



