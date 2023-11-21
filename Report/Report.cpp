#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
#define g 9.8
int count;
// �F�ƒl��\���\����
struct ColorValue {
	int color;
	int radius;
};
int main(int Number) {
	int m, n, mm = 0, nn = 0, start_x = sGW.w / 2 * (0 / 100 + 1) , start_y = sGW.h / 10;
	double x = 0, y = 90, w = 100, h = 100, real_r;
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // ��ʂ����Z�b�g����t���O
	int found = 0;

	// �F�ƒl�̃y�A��z��Ɋi�[
	struct ColorValue colorValues[] = {
		//{0, 70}, //��
		//{1, 60}, //��
		//{2, 50}, //��
		//{3, 40}, //��ctrlk>ctrlc/u�ŃR�����g�A�E�g
		{4, 30}, //���F
		{5, 20}, //���F
		{6, 10}  //�s���N
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
	Printf("count = %d\n", count);

	while (y > -real_r) { //While()����()����0�ɂȂ�܂ŌJ��Ԃ��̂ŁA1�ł͖������[�v,���̂����C���ɓ��B����܂�


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
				Circle(mm - r, nn - r, mm + r, nn + r, 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������

				Plot_pen(0, 2, 1);
				Line(0, sGW.w - 650, sGW.w, sGW.w - 650); //�f�b�h���C��
				if (pl < 0) {
					x = x - 0.1;     //���L�[�������ꂽ�Ƃ��̏���
					if (x < -w) {
						x = w;
					}
				}
				if (pr < 0) {
					x = x + 0.1;     //�E�L�[�������ꂽ�Ƃ��̏���
					if (x > w) {
						x = -w;
					}
				}

				m = sGW.w / 2 * (x / w + 1);//�����W���s�N�Z�����W�ɕϊ�sgw960/2*(0/101)=480sGw620
				n = sGW.h / 2 * (1 - y / h);//�����W���s�N�Z�����W�ɕϊ�620/2*(1-95/100)=291.4sGW710

				Plot_pen(0, 2, color);  //�ΐF�Ɏw��   
				Circle(m - r, n - r, m + r, n + r, 1);        //�V�����ʒu�ɉ~��`��m,n�͉~�̒��S���W




				mm = m; nn = n;       //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���

				if (pd < 0) {
					found = 1;
					//Plot_pen(0, 2, color);  //�ΐF�Ɏw��   
					//Circle(start_x - r, start_y - r, start_x + r, start_y + r, 1);        //�V�����ʒu�ɉ~��`��m,n�͉~�̒��S���W
				}

				if (found == 1) {
					real_r = h*(sGW.h - 2 * n) / sGW.h; //�����W�ɕϊ�
					while (y > -real_r) {
						Plot_pen(0, 2, 7); //���F�ɐݒ�i�o�b�N�Ɠ����j
						Circle(mm - r, nn - r, mm + r, nn + r, 1); //�ߋ��̋ʂ�����
						y = y + vy * dt - g * dt * dt / 2;  //  z���W�X�V
						vy = vy - g * dt;         //  z�������x�X�V

						vy = vy - g * dt; // z�������x�X�V
						if (y < -real_r) { // ���̂������ɓ��������Ƃ��A
							y = -real_r;
						} //z�͏��ɂ߂荞��ł���̂�-h�ɏC��

						if (x > w) { // ���̂��E�ɓ��������Ƃ��A
							vx = -e * vx; // ���x�ɔ��ˌW������Z
							x = w;
						} //z�͉E�ɂ߂荞��ł���̂�w�ɏC��


						if (x < -w) { // ���̂����ɓ��������Ƃ��A
							vx = -e * vx; // ���x�ɔ��ˌW������Z
							x = -w;
						} //z�͍��ɂ߂荞��ł���̂�-w�ɏC��



						m = sGW.w * (1 + x / w) / 2;  //�����W���s�N�Z�����W�ɕϊ�
						n = sGW.h * (1 - y / h) / 2;     //�����W���s�N�Z�����W�ɕϊ�
						//(z���W�͏�����𐳁j)

						Plot_pen(0, 2, color); //�ΐF�Ɏw��
						Circle(m - r, n - r, m + r, n + r, 1);   //�V�����ʒu�ɋʂ�`��

						Refresh();  //��ʍX�V

						mm = m; //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W��
						nn = n; //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W��
					}
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


