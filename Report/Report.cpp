#include "def.h"
#include "mlib.h"

#define g 9.8

int main(int Number) {
	int m, n, mm = 0, nn = 0, r = 10;
	double x = 0, y = 95, w = 100, h = 100;
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // ��ʂ����Z�b�g����t���O
	int found = 0;

	while (1) { //While()����()����0�ɂȂ�܂ŌJ��Ԃ��̂ŁA��ł͖������[�v,���̂����C���ɓ��B����܂�
		short pl, pr, pd;
		pl = GetAsyncKeyState(VK_LEFT);//���L�[�̏�ԓ���
		pr = GetAsyncKeyState(VK_RIGHT);//�E�L�[�̏�ԓ���
		pd = GetAsyncKeyState(VK_DOWN);//���L�[�̏�ԓ���
		switch (Number) {
		case 0:

			if (!resetScreen) {
				Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
				Rect(-w, h, w, -h, 1);
			}
			Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			Circle(mm - r, nn - r, mm + r, nn + r, 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������

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

			m = sGW.w / 2 * (x / w + 1);//�����W���s�N�Z�����W�ɕϊ�sgw960/2*(0/101)=480
			n = sGW.h / 2 * (1 - y / h);//�����W���s�N�Z�����W�ɕϊ�620/2*(1-95/100)=291.4
			Plot_pen(0, 2, 3);  //�ΐF�Ɏw��   
			Circle(m - r, n - r, m + r, n + r, 1);        //�V�����ʒu�ɉ~��`��
			Plot_pen(0, 2, 1);
			Line(-sGW.w, n+10, sGW.w, n+10); //�f�b�h���C��



			mm = m; nn = n;       //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���

			if (pd < 0) {
				found = 1;

			}
                
			if (found == 1) {
				while (y >= -h+0.5*r) {
					Plot_pen(0, 2, 7); //���F�ɐݒ�i�o�b�N�Ɠ����j
					Circle(mm - r, nn - r, mm + r, nn + r, 1); //�ߋ��̋ʂ�����
					y = y + vy * dt - g * dt * dt / 2;  //  z���W�X�V
					vy = vy - g * dt;         //  z�������x�X�V

					vy = vy - g * dt; // z�������x�X�V
					if (y < -h) { // ���̂������ɓ��������Ƃ��A
						y = -h;
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

					Plot_pen(0, 2, 3); //�ΐF�Ɏw��
					Circle(m - r, n - r, m + r, n + r, 1);   //�V�����ʒu�ɋʂ�`��

					Refresh();  //��ʍX�V

					mm = m; //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W��
					nn = n; //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W��
				}
				found = 0;
			}
			Refresh();        //��ʍX�V
			
		break;
		case 1:
			Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			Rect(-w, h, w, -h, 1);
			break;
		}
	}
}


