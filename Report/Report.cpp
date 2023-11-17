#include "def.h"
#include "mlib.h"
#include <time.h>
#include <cstdlib>
#define g 9.8
// �F�ƒl��\���\����
struct ColorValue {
	int color;
	int radius;
};
int main(int Number) {
	int m, n, mm = 0, nn = 0;
	double x = 0, y = 95, w = 100, h = 100;
	double vy = 0, dt = 5e-3, vx;
	double e = 1;
	int resetScreen = 0; // ��ʂ����Z�b�g����t���O
	int found = 0;

	// �F�ƒl�̃y�A��z��Ɋi�[
	struct ColorValue colorValues[] = {
		{0, 70}, //��
		{1, 60}, //��
		{2, 50}, //��
		{3, 40}, //��
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

		//�������ɓ��������珈�����I������
	// ���x�����g�p����switch���Ń��[�v�𐧌䂷��
main_loop:

	while (1) { //While()����()����0�ɂȂ�܂ŌJ��Ԃ��̂ŁA1�ł͖������[�v,���̂����C���ɓ��B����܂�
		short pl, pr, pd;
		pl = GetAsyncKeyState(VK_LEFT);//���L�[�̏�ԓ���
		pr = GetAsyncKeyState(VK_RIGHT);//�E�L�[�̏�ԓ���
		pd = GetAsyncKeyState(VK_DOWN);//���L�[�̏�ԓ���

		//case1�̏��������������case0�̏����������Ȃ�
		
		switch (Number) {
		case 0:

			if (!resetScreen) {
				Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
				Rect(-w, h, w, -h, 1);
			}

			Plot_pen(0, 2, 7);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			Circle(mm - r, nn - r, mm + r, nn + r, 1);        //�ߋ��̈ʒu�ɕ`���ꂽ�~������
			
			Plot_pen(0, 2, 1);
			Line(-sGW.w, h-60, sGW.w, h-60); //�f�b�h���C��
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
			Plot_pen(0, 2, color);  //�ΐF�Ɏw��   
			Circle(m - r, n - r, m + r, n + r, 1);        //�V�����ʒu�ɉ~��`��




			mm = m; nn = n;       //�V�����s�N�Z�����W���ߋ��̃s�N�Z�����W�ɂ���

			if (pd < 0) {
				found = 1;

			}
                
			if (found == 1) {
				while (y >= -h) {
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
			//Printf("��������");
		    break;
		case 1:
			// ��ʂ����Z�b�g����
			resetScreen = 1;
			Plot_pen(0, 2, 1);  //���F�ɐݒ�i�o�b�N�Ɠ����j
			//Rect(-w, h, w, -h, 1);
			Line(-sGW.w, h - 60, sGW.w, h - 60); //�f�b�h���C��
			break;
		}
		// switch �̐擪�ɖ߂�
		goto main_loop;
	}
}


