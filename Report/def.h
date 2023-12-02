#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include<tchar.h>
#include<stdarg.h> 
#include<math.h> 
#include<stdio.h>

/**********************************/
/*   Window Parameter Setting     */
/**********************************/
	#define PROGRAM_TITLE "�J���[�{�[���Q�[��"   // Caption of Title bar
	#define MAINWIN_W	800	//Width of main window (in pixel)
	#define MAINWIN_H	800		//Height of main window (in pixel)

	#define PB_NUM		2		//Number of used push button
	#define CK_NUM		0		//Number of used check box
	#define RD_NUM		0		//Number of used radio box
	#define ED_NUM		0		//Number of used edit box
	#define ST_NUM		0		//Number of static text box

/************/
/*   end    */
/************/

/******************************/
/*   Constant (Never change)  */
/******************************/

	#define FIGMAX		20		//�t�B�M���A�E�C���h�E�ɕ`����}�̍ő吔
	#define PALLET_NUM	(8*32)	//2D�摜�̃J���[�}�b�v���~���i8�`256�܂ł�8�̔{�����w��j

	#define BUFSIZE_W	81		//�����E�B���h�E�̐���������
	#define BUFSIZE_H	1024	//�����E�C���h�E�̋L���s��
	#define DISPSIZE_H	2		//�����E�C���h�E�̕\���s��
	#define MEMOWIN_H	(19*(DISPSIZE_H+1))		//�����E�C���h�E�̍���
	#define PNMAX		20		//�t�B�M���A�E�C���h�E�ɋL���ł������̍ő吔
	#define BUFNMAX		25		//���L���v�V�����C���l���x�����̍ő啶���T�C�Y

	#define MEMO_ID1	0
	#define SCRBAR_ID1	1
	#define DIALOG1		2
	#define BUTTON_ID1	3
	#define EDIT_ID1	(BUTTON_ID1+PB_NUM+CK_NUM+RD_NUM)
	#define STATIC_ID1	(EDIT_ID1+ED_NUM)
	
	//plflug
	#define GRAY		0		//�O���C�X�P�[��
	#define RAINBOW		1		//�t���J���[���F�@�i��ʁj
	#define CYCLIC		2		//��-��-��-��-���@�i�ʑ����̏���I�Ȑ��l�p�j

	//cbflug
	#define LEGEND_ON	1		//�Q�c�v���b�g�̖}��\��
	#define LEGEND_OFF	0		//�Q�c�v���b�g�̖}���\��

	//szflug
	#define SIZE_NORMAL 0		//�t�B�M���A�E�C���h�E�̘g�ɂQ�c�摜�\��
	#define SIZE_SQUARE 1		//�t�B�M���A�E�C���h�E�̏c���T�C�Y�����킹��	
	#define SIZE_DATA	2		//�t�B�M���A�E�C���h�E���f�[�^�̃T�C�Y�ɍ��킹��

	//bfflug�@�@�@�@�@�@�@�@
	#define	FILL_OFF	0		// ������h��Ȃ�(�ۑ�)
	#define	FILL_ON		1		//�w��͈͂�g�Ɠ��F�œh��Ԃ��C  
	#define	FILL_WHITE	2		// �g���𔒐F�œh��Ԃ�

	//clflug
	#define	DRAW_OUTLINE -1		//�g�̂ݕ\��
	#define	CLEAR_INSIDE 0		//�J�����g�t�B�M���A�E�C���h�E�̓��������C�g�C���͏����Ȃ�	
	#define	CLEAR_FIG	 1		//�J�����g�t�B�M���A�E�C���h�E�̑S����
	#define	CLEAR_ALL	 2		//�O���t�B�b�N�E�C���h�E�̑S����

	//grflug
	#define	ZERO_LINE	0		//�[�����C���݂̂̕`��
	#define	YGRID_LINE	1		//�O���b�h���C���̕`��	
	#define	XGRID_LINE	2		//�O���b�h���C���̕`��	
	#define	XYGRID_LINE	3		//�O���b�h���C���̕`��


/***********************/
/*     End�@�@�@�@*/
/***********************/


/**************************************************/
/* Definition of gloval variables (never change)  */
/**************************************************/

	int iID_Cfw;				//���݂̃t�B�M���A�E�C���h�E��ID
	int iNum_fw;				//���ꂽ�t�B�M���A�E�C���h�E�̍ő吔

	struct figure				//�e�t�B�M���A�E�C���h�E�̈ʒu�A�ő�l�A�ŏ��l���̍\����
	{
		int xwin;				//�t�B�M���A�E�C���h�E����̂����W
		int ywin;				//�t�B�M���A�E�C���h�E����̂����W
		int wwin;				//�t�B�M���A�E�C���h�E�̕�
		int	hwin;				//�t�B�M���A�E�C���h�E�̍���

		int hn;					//�O���t�B�b�N�E�C���h�E�ł̏c�����̃t�B�M���A�E�C���h�E�̐�
		int wn;					//�O���t�B�b�N�E�C���h�E�ł̉������̃t�B�M���A�E�C���h�E�̐�
		int nn;					//���̕\���ʒu

		double ymin;			//�����X�P�[���ŏ��l
		double ymax;			//�����X�P�[���ő�l
		double xmin;			//�����X�P�[���ŏ��l
		double xmax;			//�����X�P�[���ő�l

		size_t nobm;				//�������l���x���̍ő啶����

		double xs;				//�����̐��l���x���ŏ��l
		double ys;				//�����̐��l���x���ŏ��l
		double xe;				//�����̐��l���x���ő�l
		double ye;				//�����̐��l���x���ő�l
		double xd;				//�����̐��l���x���Ԋu
		double yd;				//�����̐��l���x���Ԋu
		int N;					//�E�C���h�E�ɕ`�悳���_�̌�
		char  xlabel[BUFNMAX+1];		//�����L���v�V�����i25�����܂Łj
		char  ylabel[BUFNMAX+1];		//�����L���v�V�����i25�����܂Łj

		int pf[PNMAX];				//�t�B�M���A�E�C���h�E�ɏd�ˏ������ꂽ�}�̃y���X�^�C�����L��
		int pw[PNMAX];				//�t�B�M���A�E�C���h�E�ɏd�ˏ������ꂽ�}�̃y�������L��
		COLORREF pc[PNMAX];				//�t�B�M���A�E�C���h�E�ɏd�ˏ������ꂽ�}�̃y���J���[���L��
		int pn;					//�t�B�M���A�E�C���h�E�ɏd�ˏ������ꂽ��
	}sFW[FIGMAX];

	struct controle				//�R���g���[���̈ʒu�A�T�C�Y�A�L���v�V�������̍\����
	{
		HWND hdl;
		int x;					//�E�C���h�E����̂����W
		int y;					//�E�C���h�E����̂����W
		int w;					//�E�C���h�E�̕�
		int	h;					//�E�C���h�E�̍���
		long chk;				//�`�F�b�N�{�^�����̃`�F�b�N��Ԃ�����t���O
		TCHAR name[BUFNMAX+1];
	}sPB[PB_NUM+1],sED[ED_NUM+1],sCK[CK_NUM+1],sRD[RD_NUM+1],sST[ST_NUM+1],sME,sGW;

	HINSTANCE hInstance,hInst;
	TCHAR MemoBuf[BUFSIZE_H][BUFSIZE_W];
	TCHAR MemoBuf1[BUFSIZE_H*BUFSIZE_W];  
	TCHAR Input1[100];

	HWND hWnd,hMemo1,hScroll,hEditDialog,hDiaBt1,hDiaBt2;
	HDC hBuffer;

	SCROLLINFO scr;
	HBITMAP hBitmap;
	LOGFONT DefFont;

	COLORREF PenColor=RGB(0,0,0);
	int PenStyle=PS_SOLID;
	int PenWidth=0;

	int iPpc0=0;
	int iVLine;					
	int iVLine0;				
	int ivVLine;				
/*************/
/*    End    */
/*************/

	

/************************************************/
/*		Global variables concern with FONT		*/
/************************************************/

	//Chage of the following variables is valid in main progeam //
	//Available font    	//MS GOTHIC, MS PGOTHIC, MS MINCHO, MS PMINCHO 
							//TIMES, TAHOMA, SYLFAEN, CENTURY
							//RAGE ITALIC, SCRIPT MT BOLD

	TCHAR Used_Font[32]=TEXT("TIMES");	// Default font in graphic window
	long Used_Font_Size=15;				// Font size
	BYTE Italic_Font_Flug=0;			//0 -- normal�A1 -- Italic

/**************/
/*    End     */
/**************/



/**********************************************************/
/*   �O���t�B�b�N�E�C���h�E���̊e�t�B�M���A�E�C���h�E��	  */
/*   ���E�㉺�̃}�[�W�����߂�O���[�o���ϐ��̕ύX�ӏ�   */
/**********************************************************/

	int MERGIN_L=80;		// Left mergin in figure window�Awhen caption in y-axis is wide, increase the value here
	int MERGIN_R=30;		//Right mergin in figure window
	int MERGIN_T=12;		//Upper mergin in figure window
	int MERGIN_B=60;		//Lower mergin in figure window

/******************/
/*    �����܂Ł@  */
/******************/



void component(){

	/**************************************************/
	/*   �E�C���h�E���̊e�R���g���[�����̕ύX�ӏ�   */
	/**************************************************/

	//�W���̃G�f�B�b�g�E�C���h�E�A�{�^�����̃O���[�o���ϐ��ւ̓o�^
	//�E�C���h�E�z�u��W������ς������ꍇ�͂����ō\���̕ϐ��𒼐ڕύX����
	int i;
	int MERGIN_W=20;		//���C���E�B���h�E�̒[�}�[�W��
	int MERGIN_C=10	;		//�e�R���g���[���Ԋu�̃}�[�W��
	int BTWIN_W=120;		//�v�b�V���{�^���̕�
	int BTWIN_H=50;			//�v�b�V���{�^���̍���
	int EDBOX_W=80;			//EditBox �̍���
	int EDBOX_H=27;			//EditBox �̍���
	TCHAR buf[BUFNMAX+1];

	//�e�v�b�V���{�^���̏��o�^�ii�̓{�^���ԍ��ɑΉ��j
	//for(i=0;i<PB_NUM;i++){
	sPB[0].x=MERGIN_W+(BTWIN_W+MERGIN_C)*0;	//�e�{�^������̂����W
	sPB[0].y=MERGIN_W;						//�e�{�^������̂����W
	sPB[0].w=BTWIN_W*2;						//�e�{�^���̕�
	sPB[0].h=BTWIN_H;						//�e�{�^���̍���
	wsprintf(buf,TEXT("�l�N�X�g"));
	lstrcpy(sPB[0].name,buf);				//�e�{�^���̃L���v�V����
	//}
	//sPB[1].x = MERGIN_W + (BTWIN_W + MERGIN_C) * 1;	//�e�{�^������̂����W
	//sPB[1].y = MERGIN_W;						//�e�{�^������̂����W
	//sPB[1].w = BTWIN_W;						//�e�{�^���̕�
	//sPB[1].h = BTWIN_H;						//�e�{�^���̍���
	//wsprintf(buf, TEXT("RESET"));
	//lstrcpy(sPB[1].name, buf);				//�e�{�^���̃L���v�V����

	//�`�F�b�N�{�b�N�X�̏��o�^�ii�̓`�F�b�N�{�b�N�X�ԍ��ɑΉ��j
	for(i=0;i<CK_NUM;i++){
		sCK[i].x=MERGIN_W+MERGIN_C				//�e�`�F�b�N�{�b�N�X����̂����W
			+((BTWIN_W+MERGIN_C)*PB_NUM-MERGIN_C)/3;	
		sCK[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//�e�`�F�b�N�{�b�N�X����̂����W
			+(EDBOX_H+MERGIN_C)*i;	
		sCK[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//�e�`�F�b�N�{�b�N�X�̕�
			-MERGIN_C)/3-MERGIN_C;	
		sCK[i].h=EDBOX_H;						//�e�`�F�b�N�{�b�N�X�̍���
		wsprintf(buf,TEXT("Check Box%d"),i);
		lstrcpy(sCK[i].name,buf);				//�`�F�b�N�{�b�N�X�̃L���v�V����
	}

	//���W�I�{�^���̏��o�^�ii�͊e���W�I�{�^���ԍ��ɑΉ��j
	for(i=0;i<RD_NUM;i++){
		sRD[i].x=MERGIN_W+MERGIN_C				//�e���W�I�{�^������̂����W
			+2*((BTWIN_W+MERGIN_C)*PB_NUM-MERGIN_C)/3;	
		sRD[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//�e���W�I�{�^������̂����W
			+(EDBOX_H+MERGIN_C)*i;	
		sRD[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//�e���W�I�{�^���̕�
			-MERGIN_C)/3-MERGIN_C;	
		sRD[i].h=EDBOX_H;						//�e���W�I�{�^���̍���
		sRD[i].chk=FALSE;
		wsprintf(buf,TEXT("Radio Button%d"),i);
		lstrcpy(sRD[i].name,buf);				//�e���W�I�{�^���̃L���v�V����
	}

		//���W�I�{�^���̃O���[�v���̎w��@�ȉ��̎w��ł̓��W�I�{�^���̐���4�̂Ƃ�
		//ID=0,1 ��2,3�����ꂼ��O���[�v�ɂȂ�
		//sRD[0].chk=TRUE;sRD[2].chk=TRUE;
		sRD[0].chk=TRUE;
		sRD[3].chk=TRUE;

	//�e�G�f�B�b�g�E�C���h�E�̏��o�^
	for(i=0;i<ED_NUM;i++){
		sED[i].x=MERGIN_W;						//�e�G�f�B�b�g�E�C���h�E��̂����W
		sED[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//�e�G�f�B�b�g�E�C���h�E����̂����W
			+(EDBOX_H+MERGIN_C)*i;	
		sED[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//�e�G�f�B�b�g�E�C���h�E�̕�
			-MERGIN_C)/3-MERGIN_C;	
		sED[i].h=EDBOX_H;						//�e�G�f�B�b�g�E�C���h�E�̍���
		//wsprintf(buf,TEXT("Edit%d"),i);
		wsprintf(buf, TEXT(""));
		lstrcpy(sED[i].name,buf);				//�e�G�f�B�b�g�E�C���h�E�̃L���v�V����
	}

	for(i=0;i<ST_NUM;i++){
		sST[i].x=MERGIN_W;						//�e�X�^�e�B�b�N�̂����W
		sST[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//�e�X�^�e�B�b�N�̂����W
			+(EDBOX_H+MERGIN_C)*i;	
		sST[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//�e�X�^�e�B�b�N�̕�
			-MERGIN_C)/3-MERGIN_C;	
		sST[i].h=EDBOX_H;						//�e�X�^�e�B�b�N�̍���
		wsprintf(buf,TEXT("STATIC%d"),i);
		lstrcpy(sST[i].name,buf);				//�e�X�^�e�B�b�N�̃L���v�V����	
	}
	lstrcpy(sST[0].name, L"�X�^�e�B�b�N");
	lstrcpy(sST[1].name, TEXT("������"));
	wsprintf(sST[2].name, _T("%d�Ԗ�"), 3);

	//�����E�C���h�E�̏��o�^
	sME.x=MERGIN_W+(BTWIN_W+MERGIN_C)*PB_NUM;	//�����E�B���h�E�̍���X���W
	sME.y=MERGIN_W;								//�����E�B���h�E�̍���Y���W	
	sME.w=MAINWIN_W-MERGIN_W-(MERGIN_W			//�����E�C���h�E�̕�
		+(BTWIN_W+MERGIN_C)*PB_NUM)-18; 
	sME.h=MEMOWIN_H ;							//�����E�C���h�E�̍���
	lstrcpy(sME.name,TEXT(""));


	//�O���t�B�b�N�E�C���h�E�̏��o�^
	sGW.x=MERGIN_W;								//�O���t�B�b�N�E�B���h�E�̍���X���W
	sGW.y=MERGIN_W*2+BTWIN_H					//�O���t�B�b�N�E�B���h�E�̍���Y���W	20*2+50+37*0
		+(MERGIN_C+EDBOX_H)*ED_NUM;		
	sGW.w=MAINWIN_W-MERGIN_W*3;					//�O���t�B�b�N�E�C���h�E�̕�1000-40 960
	sGW.h=MAINWIN_H-sGW.y-MERGIN_W*3;			//�O���t�B�b�N�E�C���h�E�̍���750-90-20*2=620
	lstrcpy(sGW.name,TEXT(""));
}

/*****************/
/*   �����܂Ł@�@*/
/*****************/