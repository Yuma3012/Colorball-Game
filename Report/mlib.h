//------------------------
//  Mlib ver 3.8
//  
//-------------------------
// �֐��̃v���g�^�C�v�錾

void	Print(TCHAR*, ...);
int		Printf(const char*, ...);

void	bufprint(void);
void	inputbuf(TCHAR*,int);
int		retcheck(TCHAR*);
void	Font_info(TCHAR* ,long ,LONG ,BYTE );
void	Line(int, int, int, int);
void	Rect(int, int, int, int, int);
void	Circle(int, int, int, int, int);
void	Plot_pen(int, int, int);

void	Clf(int);
int		Set_figure(int, int, int);

void	Text_draw(double , double , const char* );
void	Plot1d_int(int* ,int) ;
void	Plot1d(double* ,int );
void	Plotxy(double* ,double* ,int );
void	Plot2d(double*,int ,int, double , double , int , int , int );

void	Axis_xcap(double ,double , const char*);
void	Axis_ycap(double ,double , const char* );
void	Aspect_ratio(double , double );
void	Legend(const char* , int );
void	Fig2clipboard(void);
void	Grid_on(int);
void	drawline(double, double ,double ,double ,double ,double , HPEN ,HPEN);
void	auto_label(double ,double ,double* ,double* ,double*);
void	colormap(int, COLORREF* );

int		Input_int(void);
double	Input_double(void);
TCHAR  *Input_text(void);
char   *Input_char(void);

int		Get_int(int);
double	Get_double(int);
void	Get_text(int, TCHAR* );
void	Get_char(int, char* );

void	Set_text(int, TCHAR* );
void	Set_char(int, const char* );
void	Set_double(int , double);

void	Pause(void);
void	Delay(int);
void    Refresh(void);

DWORD	dialog(LPCTSTR );
LRESULT CALLBACK DialogProc(HWND  , UINT  , WPARAM  , LPARAM );
LRESULT CALLBACK WndProc(HWND  , UINT  , WPARAM  , LPARAM );

int main(int);  // in Ver 3.7   "void main(int);" is corrected for warning
// �֐��̃v���g�^�C�v�錾�I��


	//�v���O�����̃��C���֐�
	//WIN32API�v���O�����ł͂�������n�܂�B
    //���C���E�C���h�E�ƃ_�C�A���O�E�C���h�E�̒�`
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow) {

    MSG msg;
	WNDCLASSEX winc,diaclass;
	hInst=hInstance;	/* �v���Z�X�̃n���h����ۑ� */

	//�E�C���h�E�N���X�̒�`�i���C���E�C���h�E�̃N���X���`���Ă���j
	winc.cbSize        = sizeof(winc);
	winc.style		= CS_HREDRAW | CS_VREDRAW ;   //�E�C���h�E�T�C�Y�̕ύX��
	winc.lpfnWndProc	= WndProc;   //�E�C���h�E�v���V�[�W���֐��̒�`
	winc.cbClsExtra	= 0;
	winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	=(HBRUSH)(COLOR_BTNFACE+1);// (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("GUIconsole");   //�E�C���h�E�N���X�̖��O�B�E�C���h�E�쐬���Ɏw�肷��
	winc.hIconSm       = LoadIcon(NULL,IDI_APPLICATION);

	RegisterClassEx(&winc);	/* �E�C���h�E�N���X�o�^ */

	diaclass.cbSize        = sizeof(winc);
	diaclass.style         = CS_HREDRAW | CS_VREDRAW;
	diaclass.lpfnWndProc   = DialogProc;
	diaclass.cbClsExtra    = 0;
	diaclass.cbWndExtra    = 0;
	diaclass.hInstance     = hInstance;
	diaclass.hIcon         = NULL;
	diaclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	diaclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	diaclass.lpszMenuName  = NULL;
	diaclass.lpszClassName = TEXT("CDialog");
	diaclass.hIconSm       = NULL;

	RegisterClassEx(&diaclass);		/* �E�C���h�E�N���X�o�^ */

	//���C���E�C���h�E�̍쐬
	//�e�E�C���h�E�ł��邽�߁A�E�C���h�E�n���h����hWnd�ɕԂ��悤�ݒ�
	//�������F�E�C���h�E�N���X�̎w��i��Œ�`�����N���X���g�p�j
	//�������F�^�C�g���o�[�̖��O
	//��O�����F�I�[�o�[���b�v�A�����w��i���ɂ����낢�날��B�_���a�L���Ō����j
	//��S�|�V�����F���W�ƕ��A����
	hWnd = CreateWindow(
			TEXT("GUIconsole") , TEXT(PROGRAM_TITLE) ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			MAINWIN_W , MAINWIN_H ,
			NULL , NULL , hInstance , NULL
	);
	
	//�f�B�X�p�b�`���[�̏���
	while(GetMessage(&msg , NULL , 0 , 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

	//���C���E�C���h�E�̃E�C���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {

	HDC hdc;
	HGDIOBJ hpen;
	PAINTSTRUCT ps;
	long lo;
	long long i=0; 
	int j,k=0;

	switch (msg) {
	case WM_DESTROY:
		// �E�C���h�Eclose�̏���

		DeleteDC(hBuffer);
		DeleteObject(hBitmap);

		PostQuitMessage(0);
		return 0;
	       
	case WM_CREATE:

		component();	//�{�^�����̓o�^
		
		//�v�b�V���{�^���쐬

		for(i=0;i<PB_NUM;i++){
			sPB[i].hdl=CreateWindowEx(WS_EX_CONTROLPARENT |WS_EX_WINDOWEDGE ,
				TEXT("BUTTON") , sPB[i].name ,
				WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE |BS_MULTILINE ,
				sPB[i].x , sPB[i].y , sPB[i].w , sPB[i].h ,
				hWnd , (HMENU)(BUTTON_ID1+i) , hInstance , NULL
			);
		}
		
		//�`�F�b�N�{�b�N�X�쐬
		for(i=0;i<CK_NUM;i++){
			sCK[i].hdl=CreateWindow(
				TEXT("BUTTON") , sCK[i].name ,
				WS_CHILD| WS_VISIBLE | BS_AUTOCHECKBOX     ,
				sCK[i].x , sCK[i].y , sCK[i].w , sCK[i].h ,
				hWnd , (HMENU)(BUTTON_ID1+PB_NUM+i) , hInstance , NULL
			);
			sCK[i].chk=FALSE;
		}

		//���W�I�{�^���쐬
		for(i=0;i<RD_NUM;i++){
			sRD[i].hdl=CreateWindow(
				TEXT("BUTTON") , sRD[i].name ,
				WS_CHILD| WS_VISIBLE | BS_AUTORADIOBUTTON  | WS_GROUP*sRD[i].chk ,
				sRD[i].x , sRD[i].y , sRD[i].w , sRD[i].h ,
				hWnd , (HMENU)(BUTTON_ID1+PB_NUM+CK_NUM+i) , hInstance , NULL
			);
			sRD[i].chk=FALSE;
		}

		//�G�f�B�b�g�E�C���h�E�쐬
		for (i=0;i<ED_NUM;i++){
			sED[i].hdl=CreateWindowEx(WS_EX_CLIENTEDGE |WS_EX_CONTROLPARENT ,
				TEXT("EDIT") , sED[i].name , 
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT  |ES_AUTOHSCROLL ,
				sED[i].x , sED[i].y , sED[i].w , sED[i].h ,
				hWnd , (HMENU)(EDIT_ID1+i) ,
				hInstance , NULL
			);
		}

		//�X�^�e�B�b�N�쐬
		for (i=0;i<ST_NUM;i++){
			sST[i].hdl=CreateWindow(
				TEXT("STATIC") , sST[i].name , 
				WS_CHILD  | WS_VISIBLE  |sST[i].chk ,
				sST[i].x , sST[i].y , sST[i].w , sST[i].h ,
				hWnd , (HMENU)(STATIC_ID1+i) ,
				hInstance , NULL
			);
		}

		//�@�����E�C���h�E�쐬
		hMemo1 = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("EDIT") , NULL , 
			WS_CHILD  | WS_HSCROLL  |
			ES_AUTOHSCROLL  |ES_READONLY |
			ES_LEFT | ES_MULTILINE | WS_VISIBLE | WS_BORDER ,
			sME.x ,sME.y,sME.w,sME.h,
			hWnd , (HMENU)MEMO_ID1 ,
			hInstance , NULL
		);

		//  �����E�C���h�E�̃X�N���[���o�[�쐬
		hScroll = CreateWindow(
			TEXT("SCROLLBAR") , NULL ,
			WS_CHILD | WS_VISIBLE | SBS_VERT ,
			sME.x+sME.w, sME.y, 18, sME.h-17,
			hWnd , (HMENU)SCRBAR_ID1 ,
			hInstance , NULL
		);

		scr.cbSize = sizeof(SCROLLINFO);
		scr.fMask = SIF_PAGE | SIF_RANGE  ;

		scr.nMin = DISPSIZE_H-1;	
		scr.nMax = DISPSIZE_H-1;
		scr.nPos = DISPSIZE_H-1;
		scr.nPage = 1;

		SetScrollInfo(hScroll , SB_CTL , &scr , TRUE);
		scr.fMask = SIF_POS;

	//  �t�@���g�\���̂̏�����
		ZeroMemory( &DefFont, sizeof(DefFont) );	// �t�H���g���\���̂��O�ŏ�����			
		DefFont.lfCharSet=DEFAULT_CHARSET;		//�f�t�H���g_CHARSET
		DefFont.lfHeight=Used_Font_Size;			
		lstrcpy(DefFont.lfFaceName,Used_Font);
			//	DefFont.lfOutPrecision=1;//8;
		DefFont.lfQuality=5;


	//  �O���t�B�b�N�E�C���h�E�̃r�b�g�}�b�v�����������Ɋm��
		hdc = GetDC(hWnd);

		hBitmap = CreateCompatibleBitmap(hdc , sGW.w , sGW.h); //��ʕ\���p�r�b�g�}�b�v�쐬
		hBuffer = CreateCompatibleDC(hdc);		//�o�b�t�@�[�E�C���h�E�쐬

		SelectObject(hBuffer , hBitmap);
		SelectObject(hBuffer , GetStockObject(NULL_PEN));

		PatBlt(hBuffer , 0 , 0 , sGW.w , sGW.h , WHITENESS); //�o�b�t�@�N���A
		
		ReleaseDC(hWnd , hdc);

		hpen = CreatePen(PS_SOLID , 0 ,RGB(0,0,0));
		hpen = GetStockObject(WHITE_PEN);
		SelectObject(hBuffer , hpen);

		Rectangle( hBuffer , 0,0,sGW.w, sGW.h);
		DeleteObject(SelectObject(hBuffer , GetStockObject(WHITE_BRUSH)));

		Clf(2);

		return 0;

/*-------�}�E�X�L���v�`���[
	case WM_LBUTTONDOWN:
		blMouse = TRUE;
		rct.left = LOWORD(lp);
		rct.top = HIWORD(lp);
		SetCapture(hWnd);
		return 0;
	case WM_LBUTTONUP:
		blMouse = FALSE;
		ReleaseCapture();
		return 0;
	case WM_MOUSEMOVE:
		if(blMouse) {
			rct.right = LOWORD(lp);
			rct.bottom = HIWORD(lp);
			InvalidateRect(hWnd , NULL , TRUE);
		}
		return 0;
-------�}�E�X�L���v�`���[*/

	case WM_COMMAND:
		
		// �e��{�^���������ꂽ�Ƃ��̏���

		j=LOWORD(wp)-BUTTON_ID1;

		if((j>=0)&(j<PB_NUM)) {				// �v�b�V���{�^���̏���
			main(j);

		}else if (j<PB_NUM+CK_NUM) {		// �`�F�b�N�{�^���̏���
			int jj = j - PB_NUM;
			lo=(long)SendMessage(sCK[jj].hdl, BM_GETCHECK, 0, 0);
			sCK[jj].chk=lo;

		}else if (j<PB_NUM+CK_NUM+RD_NUM) {	// ���W�I�{�^���̏���

			for(k=0;k<RD_NUM;k++){
				sRD[k].chk=(long)SendMessage(sRD[k].hdl , BM_GETCHECK , 0 , 0);
			}
		}
		return 0;


	case WM_VSCROLL:
		//�����E�C���h�E�̃X�N���[������
		switch(LOWORD(wp)) {
	
		case SB_TOP:
			scr.nPos = scr.nMin;
			iVLine0=(iVLine-BUFSIZE_H-DISPSIZE_H+BUFSIZE_H*2)%BUFSIZE_H;
			break;
		case SB_BOTTOM:
			scr.nPos = scr.nMax;
			iVLine0=(iVLine-DISPSIZE_H+BUFSIZE_H)%BUFSIZE_H;
			break;
		case SB_LINEUP:
			if (scr.nPos>scr.nMin) {
				scr.nPos--;
				iVLine0--;		
			}
			break;
		case SB_LINEDOWN:
			if (scr.nPos < scr.nMax){ 
				scr.nPos++;
				iVLine0++;
			}
			break;
		case SB_PAGEUP:
			if (scr.nPos>scr.nMin) {
				if (scr.nPos>scr.nMin+DISPSIZE_H+1){
					scr.nPos-=DISPSIZE_H;
					iVLine0-=DISPSIZE_H;
				}
				else{
					scr.nPos=DISPSIZE_H-1;
					iVLine0=0;
				}
			}
			break;
		case SB_PAGEDOWN:
			if (scr.nPos < scr.nMax){ 
				if (scr.nPos < scr.nMax-DISPSIZE_H-1){ 
					scr.nPos+=DISPSIZE_H;
					iVLine0+=DISPSIZE_H;
				}
				else{
					scr.nPos=iVLine;
					iVLine0=iVLine-DISPSIZE_H+1;
					}
			}
			break;
		case SB_THUMBPOSITION:
			scr.nPos = HIWORD(wp);
			iVLine0=(int)scr.nPos-DISPSIZE_H+1;
			break;
		}
		SetScrollInfo(hScroll , SB_CTL , &scr , TRUE);
		scr.fMask = SIF_POS;
		bufprint();

		return 0;

    case WM_PAINT:
		//windows�̃V�X�e���ł̕`�施�߂����s���ꂽ�Ƃ��̏���
		//�`��̓��������̃r�b�g�}�b�v�̈�ɍs��
		//�`��̂��тɃ����������ʂɕ`��f�[�^���R�s�[����

		hdc = BeginPaint(hWnd , &ps);
		BitBlt(hdc , sGW.x , sGW.y , sGW.w , sGW.h , hBuffer , 0 , 0 , SRCCOPY);
		EndPaint(hWnd , &ps);
		return 0;
	}
	return DefWindowProc(hWnd , msg , wp , lp);
}

//  The specified string is displayed in MEMO window�@ehich is standard output for MLIB.
//  Instructions of string is compatible to pritnf() function;
int Printf(const char *fmt, ...){
	va_list args;
	char  buf[1024]="";
	TCHAR  bufW[1024]=L"";
	int i,LN,cn=0;
	char bl[1024];

	va_start(args ,fmt);

	vsprintf_s(buf,1023,fmt,args);
	va_end(args);

	LN=(int)strlen(buf);	
	for(i=0;i<LN;i++){
			if(buf[i]=='\n'){
				bl[cn]='\0';
				wsprintf(bufW,L"%S",bl);
				inputbuf(bufW,1);
				cn=0;
			} else {
				bl[cn]=buf[i];
				cn++;
			}
	}
	if(buf[i]!='\n'){
		bl[cn]='\0';
		wsprintf(bufW,L"%S",bl);
		inputbuf(bufW,0);
	}
	UpdateWindow(hWnd);
return 0;
}

	//Printf()�֐������邽�ߓ��Ɏg�F�K�v�Ȃ�
	//�����E�C���h�E�ɏ����t�����\�����s���B�g�p���printf���Ɠ����B
	//�g�p�ϐ��͐����^�Ǝ����^���\�L�ł���B
	//�ϐ���\������ꍇ�͂��ꂼ��%d��%g�ŕ\���ʒu���w�肵�A
	//������̌��ɃR���}�ŕϐ������L�q����B���s���䕶���́e\\n�f
void Print(TCHAR *fmt, ...){

	va_list args;
	TCHAR buf[1024];
	char bufs[BUFNMAX+1];
	double valuef;
	int i,LN,pf0,pf1,pf2,value;
	TCHAR *lp;
	TCHAR lp0[2],lp1[2];
	size_t ret;
	LPTSTR dum;
	lp=fmt;
	va_start(args ,fmt);

	LN=lstrlen(lp);				//�����̕�����
	for(i=0;i<LN;i++){			//�����������[�v
		dum=lstrcpyn(lp0,lp,2);
		pf0=lstrcmp(lp0,TEXT("%"));		//"%"�̃`�F�b�N
		 if(pf0==0){					//"%"���������ꍇ
			 dum=lstrcpyn(lp1,lp+1,2);
			pf1=lstrcmp(lp1,TEXT("d"));		//���̕�����"d"���ǂ����`�F�b�N
			pf2=lstrcmp(lp1,TEXT("g"));		//���̕�����"f"���ǂ����`�F�b�N

			if(pf1==0){
									//"%d"�̐��C���N�������g
				value=va_arg(args, int);

				wsprintf(buf,TEXT("%d"),value);
				inputbuf(buf,0);
				
				lp=lp+1;
				i=i+1;
				if (retcheck(lp)==1) {
					wsprintf(buf, TEXT(""));
					inputbuf(buf,1);
					i=i+2;
					lp=lp+2;
				}
			} else if (pf2==0){
									//"%d"�̐��C���N�������g
				valuef=va_arg(args, double);

				sprintf_s(bufs,BUFNMAX,"%g",valuef);

				mbstowcs_s(&ret, buf,BUFNMAX, bufs, BUFNMAX );
				inputbuf(buf,0);
				
				lp=lp+1;
				i=i+1;
				if (retcheck(lp)==1) {
					wsprintf(buf, TEXT(""));
					inputbuf(buf, 1);
					
					i=i+2;
					lp=lp+2;
				}
			}

		}else{
				
			if (retcheck(lp)==1) {
				wsprintf(buf, TEXT(""));
				inputbuf(buf, 1);
				
				i=i+2;
				lp=lp+2;
			} else {
				inputbuf(lp0,0);
			}
		}
		lp++;
	}
	va_end(args);
	UpdateWindow(hWnd);
}

int retcheck(TCHAR *pp){
	TCHAR *lp;
	TCHAR lp0[3];
	int ef0,retflug=0;
	LPTSTR dum;
	lp=pp;
	dum=lstrcpyn(lp0,lp,2);
	ef0=lstrcmp(lp0,TEXT("\n"));		//"\n"�̃`�F�b�N

	if(ef0==0){							//"\"���������ꍇ
		retflug=1;	
	}
	return retflug;
}


	//�����E�C���h�E��TCHAR�^�̕����z��mess�̓��e��\������B
	//crflug=0 �ȊO�̂Ƃ����s����B
void inputbuf(TCHAR *mess,int crflug){	

	int ml;		//���͕��̕�����
	int ml0;	//���ݍs�̕�����
	TCHAR mes0[BUFSIZE_W];	//���ݍs�̕���
	TCHAR dummy[BUFSIZE_W];  //�_�~�[�o�b�t�@
	LPTSTR dum;

	lstrcpy(mes0,MemoBuf[ivVLine]);
	ml0=lstrlen(mes0);
	ml=lstrlen(mess);

	if (ml0+ml>BUFSIZE_W-1){		//���������������̏���.�����ȏ�͏������߂Ȃ�
		dum=lstrcpyn(dummy,mess,BUFSIZE_W-ml0);	
		lstrcat(MemoBuf[ivVLine],dummy);	// �o�b�t�@�ɓ���
	}
	else{
	   lstrcat(MemoBuf[ivVLine],mess);	// �o�b�t�@�ɓ���
	}

	if (crflug!=0) {				// ���s�t���O�̏����@0:���s�Ȃ� �@0�ȊO:���s

		iVLine++;					//���ݍs�ʒu���C���N�������g
		ivVLine=iVLine%BUFSIZE_H;			//�]��l��

		if (iVLine>DISPSIZE_H-1) {		//���ݍs���E�C���h�E���𒴂����Ƃ�
			iVLine0=iVLine-DISPSIZE_H+1;				//�\���ʒu���C���N�������g
			lstrcpy(MemoBuf[ivVLine],TEXT(""));
		
			scr.cbSize = sizeof(SCROLLINFO);
			scr.fMask = SIF_PAGE | SIF_RANGE  ;

			if(iVLine==ivVLine){		//���ݍs���\�������s���̂Ƃ�
				scr.nMin = DISPSIZE_H-1;
			    scr.nMax = iVLine;
			}
			else{					//���ݍs���\�������𒴂����Ƃ�
				scr.nMin =iVLine-BUFSIZE_H+1+DISPSIZE_H;
				scr.nMax =iVLine;
			}

			SetScrollInfo(hScroll , SB_CTL , &scr , TRUE);
			scr.fMask = SIF_POS;

			//scr.nPos = iVLine-DISPSIZE_H+1;
			scr.nPos = scr.nMax;

			SetScrollInfo(hScroll , SB_CTL , &scr , TRUE);
			scr.fMask = SIF_POS;
		}
	}
	bufprint();						// �o�b�t�@�̌��݃E�C���h�E�ւ̕\��
}

void bufprint(){
	int i,ii;
	TCHAR dummy[BUFSIZE_W*DISPSIZE_H]=TEXT("");		//�_�~�[������
	

	for(i=iVLine0;i<iVLine0+DISPSIZE_H;i++){		//�\���s�̐擪���烋�[�v
		ii=i%BUFSIZE_H;

		lstrcat(dummy , MemoBuf[ii]);
		lstrcat(dummy , TEXT("\r\n"));
	}
		SetWindowText(hMemo1 , dummy);
}


void Font_info(TCHAR *font_face,long font_size,LONG rotation ,BYTE font_italic){
		
		DefFont.lfHeight=font_size;
		lstrcpy(DefFont.lfFaceName,font_face);
		DefFont.lfEscapement=rotation*10;
		DefFont.lfItalic=font_italic;
}


	//Draw a line in graphic window
	//	[X1,y1] start position of the line
	//	[x2,y2] End positon of the line
	//	Line color or Line style is specified Plot_pen() function.
void Line(int x1,int y1,int x2,int y2){


	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//�y���̎w��
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);		//�V���ȃy���̑I���ƌÂ��y���̕ۑ�

	MoveToEx(hBuffer , x1 , y1 , NULL);	
	LineTo(hBuffer ,x2,y2);				//�����̕`��
	SelectObject(hBuffer , hpen_old);	//���Ƃ̃y���ɖ߂�
	DeleteObject(hpen);					//�y���̎w�����

	InvalidateRect(hWnd , &d , FALSE);	//�V�X�e���`�施�߂̃f�B�X�p�b�`
}


	//�O���t�B�b�N�E�C���h�E�Ɏl�p�`��`���A�F�A���̎�ނ�Plot_pen()�Ŏw��
	//	X1,y1�͍���̍��W�Ax2,y2�͉E���̍��W
	//	bfflug=0  		�g�̂݁B�g���͕`�悵�Ȃ��B
	//	bfflug=1  		�g�Ƙg����Plot_pen()�Ŏw�肵���F�œh��Ԃ�
	//	bfflug=����ȊO  	�g�Ƙg���𔒂œh��Ԃ�
void Rect(int x1,int y1,int x2,int y2,int bfflug){

	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;
	HGDIOBJ hbrush,hbrush_old;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//�y���̎w��
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);		//�V���ȃy���̑I���ƌÂ��y���̕ۑ�

	if (bfflug== FILL_OFF) hbrush=GetStockObject(NULL_BRUSH);		//�u���V�̎w��
	else if(bfflug== FILL_ON) hbrush=CreateSolidBrush(PenColor);
	else hbrush=GetStockObject(WHITE_BRUSH);

	hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);

	Rectangle(hBuffer,x1,y1,x2, y2);		//�l�p�̕`��

	SelectObject(hBuffer , hpen_old);		//���Ƃ̃y���ɖ߂�
	DeleteObject(hpen);						//�y���̎w�����

	SelectObject(hBuffer , hbrush_old);		//���Ƃ̃u���V�ɖ߂�
	DeleteObject(hbrush);					//�u���V�̎w�����

	InvalidateRect(hWnd , &d , FALSE);		//�V�X�e���`�施�߂̃f�B�X�p�b�`
}


	//�O���t�B�b�N�E�C���h�E�ɑȉ~��`���A�F�A���̎�ނ�Plot_pen()�Ŏw��
	//	X1,y1�͍���̍��W�Ax2,y2�͉E���̍��W���w�肵�A���̎l�p�`�ɐڂ���ȉ~��`���B
	//	bfflug=0  �g�̂ݘg���͕`�悵�Ȃ��B
	//	bfflug=1  �g����Plot_pen()�Ŏw�肵���F�œh��Ԃ�
	//	bfflug=����ȊO  �g�݂̂𔒂œh��Ԃ�
void Circle(int x1,int y1,int x2,int y2,int bfflug)/* Draw circle */{

	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;
	HGDIOBJ hbrush,hbrush_old;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//�y���̎w��
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);		//�V���ȃy���̑I���ƌÂ��y���̕ۑ�

	if (bfflug== FILL_OFF) hbrush=GetStockObject(NULL_BRUSH);    //�u���V�̎w��
	else if(bfflug== FILL_ON) hbrush=CreateSolidBrush(PenColor);
	else hbrush=GetStockObject(WHITE_BRUSH);

	hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//�V���ȃu���V�̑I���ƌÂ��u���V�̕ۑ�

	Ellipse(hBuffer,x1,y1,x2, y2);			//�ȉ~�̕`��

	SelectObject(hBuffer , hpen_old);		//���Ƃ̃y���ɖ߂�
	DeleteObject(hpen);						//�y���̎w�����

	SelectObject(hBuffer , hbrush_old);		//���Ƃ̃u���V�ɖ߂�
	DeleteObject(hbrush);					//�u���V�̎w�����

	InvalidateRect(hWnd , &d , FALSE);		//�V�X�e���`�施�߂̃f�B�X�p�b�`
}


	//�O���t�B�b�N�E�C���h�E�ɕ`�悷��F���w�肷��B
	//pf: 0-�����@1-�j��  2-�_���@3-�P�_�����@4-�Q�_����  5-�`�悵�Ȃ�
	//pw: �y���̑������s�N�Z���P�ʂŎw��B 0�͂P�s�N�Z��
	//pc: 0-���@1-��   2-��   3-��   4-���F    5-�}�[���_    6-�V�A��   7-��   
	//8�ȏ���w�肷���Plot_Pen���Ăяo�����Ɏ����I�ɐF��0�`6�܂ŏ��񂳂���B
void Plot_pen(int pf, int pw, int pc){
	int ppc[8]={3,2,1,6,5,4,0};
	int pnc;

		switch (pf){
			case 0:
				PenStyle=PS_SOLID;
				break;
			case 1:
				PenStyle=PS_DASH;
				break;
			case 2:
				PenStyle=PS_DOT;
				break;
			case 3:
				PenStyle=PS_DASHDOT;
				break;
			case 4:
				PenStyle=PS_DASHDOTDOT;
				break;
			case 5:
				PenStyle=PS_NULL;
				break;
			default:
				MessageBox(hWnd, TEXT("Plot_Pen�֐��̑�P�����̎w�肪�͈͂𒴂��Ă��܂��D"), TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
				PenStyle=PS_SOLID;
				break;
		}
	
		PenWidth=pw;
	
		if (pc<8){
			pnc=pc;
		    iPpc0=0;
		}
		else{
			pnc=ppc[sFW[iID_Cfw].pn%7];
		}

		switch (pnc){
			case 0:
				PenColor=RGB(0,0,0);		//��
				break;
			case 1:
				PenColor=RGB(0xff,0,0);		//��
				break;
			case 2:
				PenColor=RGB(0,0xff,0);		//��
				break;
			case 3:
				PenColor=RGB(0,0,0xff);		//��
				break;
			case 4:
				PenColor=RGB(0xff,0xff,0);	//���F
				break;
			case 5:
				PenColor=RGB(0,0xff,0xff);	//�}�[���_
				break;
			case 6:
				PenColor=RGB(0xff,0,0xff);	//�V�A��
				break;
			case 7:
				PenColor=RGB(0xff,0xff,0xff);//��
				break;
		}
	}

	//�t�B�M���A�E�C���h�E�̏����B
	//	clflug=-1		�w�肵���t�B�M���A�E�C���h�E�̘g�����`��
	//	clflug=0		�w�肵���t�B�M���A�E�C���h�E�̘g��`�悵�A�g��������
	//	clflug=1		�w�肵���t�B�M���A�E�C���h�E�����x�����܂߂ď���
	//	clflug=2		�O���t�B�b�N�E�C���h�E��S�ď���
void Clf(int clflug){
	int i;
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;
	HBRUSH hbrush,hbrush_old;

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;

	if((clflug<-1)|(clflug>2)){
		MessageBox(hWnd, TEXT("Clf�֐��̈����̎w�肪�͈͂𒴂��Ă��܂��D"), TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
		return;
	}

	if(clflug<1){			//	clflug=-1		�w�肵���t�B�M���A�E�C���h�E�̘g�����`��
							//	clflug=0		�w�肵���t�B�M���A�E�C���h�E�̘g��`�悵�A�g��������
		hpen = CreatePen(0 , 0 , RGB(0,0,0));			//���������̃y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�V���ȃy���̑I���ƌÂ��y���̕ۑ�

		if(clflug== CLEAR_INSIDE){		//�g���ɔ����u���V���w��

			hbrush=(HBRUSH)GetStockObject(WHITE_BRUSH);				
			sFW[iID_Cfw].pn=0;	

		} else {			//�g���ɓ����̃u���V���w��

			hbrush=(HBRUSH)GetStockObject(NULL_BRUSH);
		}			
		hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//�V���ȃu���V�̑I���ƌÂ��u���V�̕ۑ�
		Rectangle(hBuffer,figwin_X,figwin_Y,figwin_X+figwin_W, figwin_Y+figwin_H);	//�g�̕`��

		SelectObject(hBuffer, hpen_old);		//���Ƃ̃y���ɖ߂�
		DeleteObject(hpen);						//�y���̎w�����

		SelectObject(hBuffer, hbrush_old);		//���Ƃ̃u���V�ɖ߂�
		DeleteObject(hbrush);					//�u���V�̎w�����

	} else if(clflug== CLEAR_FIG){	//	clflug=1		�w�肵���t�B�M���A�E�C���h�E�����x�����܂߂ď���

		hpen = CreatePen(0 , 0 , RGB(0xff,0xff,0xff));	//���������̃y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�V���ȃy���̑I���ƌÂ��y���̕ۑ�

		hbrush=CreateSolidBrush(RGB(0xff,0xff,0xff));		//�g���ɔ����u���V���w��
		hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//�V���ȃu���V�̑I���ƌÂ��u���V�̕ۑ�
	
		Rectangle(hBuffer,figwin_X-MERGIN_L,figwin_Y-MERGIN_T,figwin_X+figwin_W+MERGIN_R,figwin_Y+figwin_H+MERGIN_B);

		//�w�肵���t�B�M���A�E�C���h�E���̏�����
		sFW[iID_Cfw].xmin=0.;
		sFW[iID_Cfw].xmax=0.;
		sFW[iID_Cfw].ymin=0.;
		sFW[iID_Cfw].ymax=0.;
		sFW[iID_Cfw].ys=0.;
		sFW[iID_Cfw].xs=0.;
		sFW[iID_Cfw].ye=0.;
		sFW[iID_Cfw].xe=0.;	
		sFW[iID_Cfw].yd=1.;
		sFW[iID_Cfw].xd=1.;
		sFW[iID_Cfw].N=0;				
		sFW[iID_Cfw].pn=0;		
	    strcpy_s(sFW[iID_Cfw].xlabel,1,"\0");
		strcpy_s(sFW[iID_Cfw].ylabel,1,"\0");

		SelectObject(hBuffer, hpen_old);		//���Ƃ̃y���ɖ߂�
		DeleteObject(hpen);						//�y���̎w�����

		SelectObject(hBuffer, hbrush_old);		//���Ƃ̃u���V�ɖ߂�
		DeleteObject(hbrush);					//�u���V�̎w�����

	} else if(clflug== CLEAR_ALL){	//	clflug=2		�O���t�B�b�N�E�C���h�E��S�ď���

		hpen = CreatePen(0 , 0 , RGB(0xff,0xff,0xff));	//�����y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�V���ȃy���̑I���ƌÂ��y���̕ۑ�

		hbrush=CreateSolidBrush(RGB(0xff,0xff,0xff));		//�����u���V�̎w�� 
		hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//�V���ȃu���V�̑I���ƌÂ��u���V�̕ۑ�
	
		Rectangle(hBuffer,0,0,sGW.w, sGW.h);		//�t�B�M���A�E�C���h�E�ɔ��h��̎l�p��`��

		//�O���t�B�b�N�E�C���h�E���̑S����
		iID_Cfw=-1;		
		iNum_fw=-1;

		for(i=0;i<FIGMAX;i++){	

			sFW[i].xwin=0;
			sFW[i].ywin=0;
			sFW[i].wwin=0;
			sFW[i].hwin=0; 

			sFW[i].wn=0;
			sFW[i].hn=0;
			sFW[i].nn=0;
			sFW[i].nobm=0;

			sFW[i].xmin=0.;
			sFW[i].xmax=0.;
			sFW[i].ymin=0.;
			sFW[i].ymax=0.;
			sFW[i].ys=0.;
			sFW[i].xs=0.;
			sFW[i].ye=0.;
			sFW[i].xe=0.;
			sFW[i].yd=1.;
			sFW[i].xd=1.;
			sFW[i].N=0;
			sFW[i].pn=0;
		   	strcpy_s(sFW[i].xlabel,1,"\0");
			strcpy_s(sFW[i].ylabel,1,"\0");
		}
		SelectObject(hBuffer, hpen_old);		//���Ƃ̃y���ɖ߂�
		DeleteObject(hpen);						//�y���̎w�����

		SelectObject(hBuffer, hbrush_old);		//���Ƃ̃u���V�ɖ߂�
		DeleteObject(hbrush);					//�u���V�̎w�����
	}
	InvalidateRect(hWnd , &d , FALSE);		//�V�X�e���`�施�߂̃f�B�X�p�b�`
}


	//�}�ɃO���b�h���C����`�悷��B���l���x���̒l�̂�����W�ɒ���������
	//���̍ő�ŏ������߂��iPlot�֐��AAxis_ycap, Axis_xcap�j��Ɏw�肷��B
	//	grflug: 0�̂Ƃ�������0���x���݂̂������B
	//			1�̂Ƃ����l���x���̍��W�ɂ����ɃO���b�h���C���������B
	//			2�̂Ƃ����l���x���̍��W�ɂ����ɃO���b�h���C���������B
	//			3�̂Ƃ����l���x���̍��W�ɂ����A�����ɃO���b�h���C���������B
void Grid_on(int grflug){
	int j,x,y,nx=0,ny=0;
	double lx[20],ly[20];
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;	
	double xmax,ymax,xmin,ymin,am;

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;

	if (sFW[iID_Cfw].N>0){	//�t�B�M���A�E�C���h�E�ɐ}���`�悳��Ă��邩�ǂ����`�F�b�N
			
		//�O���[�o���ϐ�����w��t�B�M���A�E�C���h�E�̂��������̍ő�ŏ����擾
		ymax=sFW[iID_Cfw].ymax;	
		xmax=sFW[iID_Cfw].xmax;
		ymin=sFW[iID_Cfw].ymin;	
		xmin=sFW[iID_Cfw].xmin;

		if (grflug== ZERO_LINE){	//�[�����C���`��I��
			nx=0;
			ny=1;
			lx[0]=0;
			ly[0]=0;
		} 
		
		if ((grflug== YGRID_LINE)|(grflug== XYGRID_LINE)){	//�O���b�h���C���`��I��

			am=sFW[iID_Cfw].ys;

			while(am<=ymax){
				ly[ny]=am;
				am=am+sFW[iID_Cfw].yd;
				ny++;	
			}
		} 
		
		if ((grflug== XGRID_LINE)|(grflug== XYGRID_LINE)){

			am=sFW[iID_Cfw].xs;

			while(am<=xmax){
				lx[nx]=am;
				am=am+sFW[iID_Cfw].xd;
				nx++;	
			}
		}

		hpen = CreatePen(PS_DOT , 0 , RGB(0,0,0));		//�����_���̃y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�V���ȃy���̑I���ƌÂ��y���̕ۑ�
		SetBkMode(hBuffer , TRANSPARENT);

		for(j=0;j<ny;j++){		//���̃O���b�h�\��
			x=figwin_X;
			y=figwin_Y+(int)((ymax-ly[j])*((double)figwin_H-1)/(ymax-ymin)+.5);
			MoveToEx(hBuffer ,x , y , NULL);
			x=figwin_X+figwin_W-1;
			y=figwin_Y+(int)((ymax-ly[j])*((double)figwin_H-1)/(ymax-ymin)+.5);
			LineTo(hBuffer ,x,y);
		}

		for(j=0;j<nx;j++){		//�c�̃O���b�h�\��

			x=figwin_X+(int)((lx[j]-xmin)*((double)figwin_W-1)/(xmax-xmin)+.5);
			y=figwin_Y;

			MoveToEx(hBuffer , x ,y , NULL);

			x=figwin_X+(int)((lx[j]-xmin)*((double)figwin_W-1)/(xmax-xmin)+.5);
			y=figwin_Y+figwin_H-1;

			LineTo(hBuffer ,x,y);
		}
		SetBkMode(hBuffer , OPAQUE);

		SelectObject(hBuffer , hpen_old);	//���Ƃ̃y���ɖ߂�
		DeleteObject(hpen);					//�y���̎w�����
		InvalidateRect(hWnd , &d , FALSE);	//�V�X�e���`�施�߂̃f�B�X�p�b�`
	}
}


	//�O���t�B�b�N�E�C���h�E�Ƀt�B�M���A�E�C���h�E���쐬���A
	//�Ȍ��Plot1d(�c)���̕`��͎w�肵���E�C���h�E�ɕ`�����B
	//��U�A�w�肵���E�C���h�E�͍��g�݂̂��`�����B
	//	i1: �E�C���h�E�̉������̐�
	//	i2:�E�C���h�E�̏c�����̐�
	//	n:�w�肷��E�C���h�E�̔ԍ��A������P�ԂƂ��E�ɐ����čs��
	//Set_figure(�c)���s�������ԂɃt�B�M���AID�����蓖�Ă���B
	//���݂̃t�B�M���AID��global�ϐ���iID_Cfw�ɓ����Ă���B
	//���߂Ďw�肵���Ƃ��̓t�B�M���A�E�C���h�E�̍ő�ŏ��l���N���A�����B
	//���ڈȍ~�Ɏw�肵���Ƃ��͑O�Ɏw�肵���l�Ɠ����t�B�M���A�E�C���h�E��
	//�ݒ�l���p�����邽�߁A�ő�l�ŏ��l�̒l�͋L������Ă���B
	//1��w�肷��΍ێw�肷��K�v�͂Ȃ��B
	//����A��x�w�肵���t�B�M���A�E�C���h�E�ɈႤ�������}��`�悷��ꍇ��
	//Clf(1)�ň�U�}���������āA�Ďw�肷��K�v������B
int Set_figure(int i1,int i2,int n){
	int figwin_X;
	int figwin_Y;
	int figwin_W;
	int figwin_H;	
	int i;

	if ((i1>0)&(i2>0)){

		if ((n>0)&(n<i1*i2+1)) {			//i1 i2 n�̐ݒ�l�̑Ó����`�F�b�N
			
			for (i=0;i<=iNum_fw;i++){	
				//�w��t�B�M���A�E�C���h�E�����łɐݒ�ς݂��ǂ����m�F
				if ((sFW[i].wn==i2)&(sFW[i].hn==i1)&(sFW[i].nn==n)){
					iID_Cfw=i;			//�w��t�B�M���A�E�C���h�E���J�����g�E�C���h�E�ɐݒ�
					Clf(-1);				//�t�B�M���A�E�C���h�E�̘g�̂ݕ`��
					return i;				//�߂�
				}
			}

			//�w��t�B�M���A�E�C���h�E���V�K�t�B�M���A�E�C���h�E�̏ꍇ
			iNum_fw=iNum_fw+1;	//�����̃E�C���h�E�h�c�ő�l���C���N�������g
 			iID_Cfw=iNum_fw;		//�V�K�t�B�M���A�E�C���h�E���J�����g�E�C���h�E��

			//�E�C���h�E�̍�����W�C�����C���̐ݒ�
			figwin_W=(sGW.w/i2)-(MERGIN_L+MERGIN_R)+1;
			figwin_H=(sGW.h/i1)-(MERGIN_T+MERGIN_B)+1;

			figwin_X=(sGW.w/i2)*((n-1)%i2)+MERGIN_L;
			figwin_Y=(sGW.h/i1)*((n-1)/i2)+MERGIN_T;

			sFW[iID_Cfw].xwin=figwin_X;
			sFW[iID_Cfw].ywin=figwin_Y;
			sFW[iID_Cfw].wwin=figwin_W;
			sFW[iID_Cfw].hwin=figwin_H; 

			Clf(0);		//�t�B�M���A�E�C���h�E�̘g������

			//�t�B�M���A�E�C���h�E�̃E�C���h�E�ʒu���
			sFW[iID_Cfw].wn=i2;
			sFW[iID_Cfw].hn=i1;
			sFW[iID_Cfw].nn=n;

			//�t�B�M���A�E�C���h�E�̏�񏉊���
			sFW[iID_Cfw].nobm=0;
			sFW[iID_Cfw].xmin=0;
			sFW[iID_Cfw].xmax=0;
			sFW[iID_Cfw].ymin=0;
			sFW[iID_Cfw].ymax=0;
			sFW[iID_Cfw].ys=0.;
			sFW[iID_Cfw].xs=0.;
			sFW[iID_Cfw].ye=0.;
			sFW[iID_Cfw].xe=0.;
			sFW[iID_Cfw].yd=1.;
			sFW[iID_Cfw].xd=1.;
			sFW[iID_Cfw].N=0;

			sFW[iID_Cfw].pn=0;

		    strcpy_s(sFW[iID_Cfw].xlabel,1,"\0");
		    strcpy_s(sFW[iID_Cfw].ylabel,1,"\0");

			
		} else {MessageBox(hWnd, TEXT("�t�B�M���A�E�C���h�E�̎w�肪�͈͂𒴂��Ă��܂��D"), TEXT("Mlib�ɂ��x��"),MB_ICONHAND);}
	} else {MessageBox(hWnd, TEXT("�t�B�M���A�E�C���h�E�̐������̒l�ł��D"), TEXT("Mlib�ɂ��x��"),MB_ICONHAND);}
return iID_Cfw;
}

	//�����̍ŏ��A�ő�ݒ�A���l���x���A�L���v�V������\������B
	//min: �����̍ŏ��l
	//max: �����̍ő�l
	//label: �����L���v�V�����̕�����i100�����ȓ��j�̐擪�A�h���X
	//���l���x����min����max�̊Ԃ̓K���Ȑ��l�������I�Ɍv�Z���ĕ`�悷��B
	//min=max=0�͐ݒ�ł��Ȃ��BPlot�֐����̑O��Ŏw��\
	//Plot1d()�֐��ł�x���̃��x���̂ݏ�����A���̕\���͈͕͂ς��Ȃ�
void Axis_xcap(double min,double max, const char *label){
	double am,st,en,in;
	int cap_X=sFW[iID_Cfw].xwin;   
	int cap_Y=sFW[iID_Cfw].ywin+sFW[iID_Cfw].hwin-1;
	int cap_W=sFW[iID_Cfw].wwin;
	int x,y,ms;
	size_t nob,nobm;
	HPEN hpen,hpen_old;
	HFONT hFont,hFont_old;
	TEXTMETRIC tm;
	char a[BUFNMAX+1];
	TCHAR b[BUFNMAX+1]=TEXT(""),Label[100];

	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};

	if ((max*max+min*min)>1e-20){  //�ő�ŏ���0�łȂ��̂Ƃ�
		
		auto_label(min,max,&st,&en,&in);	//���l���x���̎擾

		sFW[iID_Cfw].xmin=min;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�����ŏ��l�̏�������
		sFW[iID_Cfw].xmax=max;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�����ő�l�̏�������
	
		nobm=0;
		hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//���������̃y�����w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�y���̐ݒ���s���C�Â��y������hpen_old��

		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// �t�H���g�̉�]�ݒ�
		hFont = CreateFontIndirect( &DefFont );				// �_���t�H���g���쐬����
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//�_���t�H���g��V���ɐݒ肵�Â��t�H���g��ۑ�

		GetTextMetrics(hBuffer , &tm);	//�t�H���g�T�C�Y��񓙎擾�̂��߂̐ݒ�

		for(am=st;am<=max;am=am+in){
			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);				//���l���x���Ɏg�������l�����C�h�����ɕϊ�
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );	//���l���x���̕�������nob�Ɏ擾
			nob--;
			if(nob>nobm){nobm=nob;}			//���l���x���̕������̍ő�l��nobm�Ɏ擾
		}

		// ���l���x���̊Ԋu�����l���x���̕��������傫���Ƃ��̏���
		if (((double)cap_W*in/(max-min))<(((double)nobm+1)*tm.tmAveCharWidth)) {

			in=in*2;		//���l���x���̊Ԋu���{�ɐݒ�	

			if (fabs(st)>1e-10){  //���l���x����0�������0��ʂ�悤�ɒ���
				char n1[BUFNMAX+1],n2[BUFNMAX+1];
				sprintf_s(n1,BUFNMAX,"%g",st);
				sprintf_s(n2,BUFNMAX,"%g",st+in/2);

				if ((strlen(n1)>strlen(n2))&(fmod(fabs(st+in/2),in)<1e-10)){	
					st=st+in/2;
				}
			}
		}

		for(am=st;am<=max;am=am+in){	//���l���x���̐��������[�v

			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );
			nob--;

			x=cap_X+(int)(((double)cap_W-1)*(am-min)/(max-min)+.5);
			y=cap_Y;

			TextOut(hBuffer, x-(int)((double)nob*tm.tmAveCharWidth/2.), y+(int)(tm.tmHeight/6.), b, (int)nob);//���l���x���̕`��
	
    		MoveToEx(hBuffer , x , cap_Y-1 , NULL);	//�ڐ���ʒu�̐ݒ�
			LineTo(hBuffer ,x , cap_Y-5);			//�ڐ���̕`��
		}

		SelectObject(hBuffer , hFont_old);		//���̃t�H���g�ɖ߂�
		DeleteObject( hFont );					//�쐬�����_���t�H���g���폜����

		SelectObject(hBuffer , hpen_old);		//���Ƃ̃y���ɖ߂�
		DeleteObject(hpen);						//�y���̎w�����

		sFW[iID_Cfw].xs=st;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ŏ��l�̏�������
		sFW[iID_Cfw].xe=en;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ő�l�̏�������
		sFW[iID_Cfw].xd=in;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���Ԋu�̏�������
	}

	Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// �t�H���g�̉�]�ݒ�
	hFont = CreateFontIndirect( &DefFont );				// �_���t�H���g���쐬����
	hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//�_���t�H���g��V���ɐݒ肵�Â��t�H���g��ۑ�

	GetTextMetrics(hBuffer , &tm);	//�t�H���g�T�C�Y��񓙎擾�̂��߂̐ݒ�

	wsprintf(Label,L"%S",label);
	ms=lstrlen(Label);	//�L���v�V�����̕�����
	x=cap_X;
	y=cap_Y;
	TextOut(hBuffer, x-(int)(ms/2.*tm.tmAveCharWidth-cap_W/2.), y+(int)(7*(double)tm.tmHeight/6.), Label, ms);//�L���v�V�����̕`��
	strcpy_s(sFW[iID_Cfw].xlabel,ms+1,label);		//�w���L���v�V������ݒ�

	SelectObject(hBuffer , hFont_old);		//���̃t�H���g�ɖ߂�
	DeleteObject( hFont );					//�쐬�����_���t�H���g���폜����

	InvalidateRect(hWnd , &d , FALSE);	//�V�X�e���`�施�߂̃f�B�X�p�b�`
}

	//�����̍ŏ��A�ő�ݒ�A���l���x���A�L���v�V������\������B
	//min, max : �����̍ŏ��l�A�ő�l
	//label: y���L���v�V�����̕�����i100�����ȓ��j�̐擪�A�h���X
	//���l���x����min����max�̊Ԃ̓K���Ȑ��l�������I�Ɍv�Z���ĕ`�悷��B
	//���X�P�[�������炩���ߌ��܂��Ă���Ƃ���Plot1d()���̊֐�����ɌĂяo���B
	//����̂Ƃ���min=max=0���w�肷��΁A�L���v�V�����݂̂�`�悷��B
	//���̂Ƃ��͂ǂ��ŌĂяo���Ă��ǂ��Bmin=max=0�̂Ƃ��APlot1d���ɂ��
	//�����͎����I�ɍ쐬�����B
	//���l���x�����������Ƃ��A�L���v�V�������E�C���h�E�g���яo�����Ƃ�����B
	//���̂Ƃ���def.h����MERGIN_L��傫������Ƃ悢�B
void Axis_ycap(double min,double max, const  char *label){
	double am,st,en,in;
	int cap_X=sFW[iID_Cfw].xwin;   
	int cap_Y=sFW[iID_Cfw].ywin;
	int cap_H=sFW[iID_Cfw].hwin;
	int x,y;
	size_t ms,nob,nobmax=0;
	HPEN hpen,hpen_old;
	char a[BUFNMAX+1];
	TCHAR b[BUFNMAX+1],Label[100];
	TEXTMETRIC tm;
	HFONT hFont,hFont_old;

	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};

	if ((max*max+min*min)>1e-20){	//�ő�ŏ���0�ȊO�̂Ƃ�

		auto_label(min,max,&st,&en,&in);	//���l���x���̎擾

		sFW[iID_Cfw].ymin=min;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�����ŏ��l�̏�������
		sFW[iID_Cfw].ymax=max;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�����ő�l�̏�������
	
		hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//���������̃y�����w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�y���̐ݒ���s���C�Â��y������hpen_old��

		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// �t�H���g�̉�]�ݒ�
		hFont = CreateFontIndirect( &DefFont );				// �_���t�H���g���쐬����
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//�_���t�H���g��V���ɐݒ肵�Â��t�H���g��ۑ�

		GetTextMetrics(hBuffer , &tm);	//�t�H���g�T�C�Y��񓙎擾�̂��߂̐ݒ�
	
		// ���l���x���̍��������l���x���̕��������傫���Ƃ��̏���
		if (((double)cap_H*in/(max-min))<5*(double)tm.tmHeight/4.) {
			
			in=in*2;		//���l���x���̊Ԋu���{�ɐݒ�

			if (fabs(st)>1e-10){  //���l���x����0�������0��ʂ�悤�ɒ���
				char n1[BUFNMAX+1],n2[BUFNMAX+1];
				sprintf_s(n1,BUFNMAX,"%g",st);
				sprintf_s(n2,BUFNMAX,"%g",st+in/2);
				if ((strlen(n1)>strlen(n2))&(fmod(fabs(st+in/2),in)<1e-10)){	
					st=st+in/2;
				}
			}
		}

		for(am=st;am<=max;am=am+in){	//���l���x���̐��������[�v
			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );
			nob--;
			x=cap_X;
			y=cap_Y+(int)(((double)cap_H-1)*(max-am)/(max-min)+.5);

			TextOut(hBuffer, x-(int)((nob+0.5)*tm.tmAveCharWidth)-4, y-(int)(tm.tmHeight/2.), b, (int)nob);	//���l���x���̕`��
    		MoveToEx(hBuffer , cap_X, y  , NULL);	//�ڐ���ʒu�̐ݒ�
			LineTo(hBuffer , cap_X+5,y ); 			//�ڐ���̕`��			

			if (nob>nobmax){nobmax=nob;}			//�������l���x���̕������̍ő�l��nobm�Ɏ擾
		}

		SelectObject(hBuffer , hFont_old);		//���̃t�H���g�ɖ߂�
		DeleteObject( hFont );					//�쐬�����_���t�H���g���폜����

		SelectObject(hBuffer , hpen_old);	//���Ƃ̃y���ɖ߂�
		DeleteObject(hpen);					//�y���̎w�����

		sFW[iID_Cfw].nobm=nobmax;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̂������l���x���������̍ő�l��������

		sFW[iID_Cfw].ys=st;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ŏ��l�̏�������
		sFW[iID_Cfw].ye=en;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ő�l�̏�������
		sFW[iID_Cfw].yd=in;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���Ԋu�̏�������
	} 

	if(sFW[iID_Cfw].nobm==0){				//�����̐��l���x�����ݒ肳��Ă��Ȃ��Ƃ�
		ms=strlen(label);
		strcpy_s(sFW[iID_Cfw].ylabel,ms+1,label);			//�����L���v�V�������O���[�o���ϐ��ɐݒ�

	} else {							//�����̐��l���x�����ݒ肳��Ă���Ƃ�
		wsprintf(Label,L"%S",label);

		Font_info(Used_Font,Used_Font_Size,90,Italic_Font_Flug);			// �t�H���g�̉�]�ݒ�
		hFont = CreateFontIndirect( &DefFont );				// �_���t�H���g���쐬����
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//�_���t�H���g��V���ɐݒ肵�Â��t�H���g��ۑ�

		GetTextMetrics(hBuffer , &tm);	//�t�H���g�T�C�Y��񓙎擾�̂��߂̐ݒ�

		ms=lstrlen(Label);	//�L���v�V�����̕�����
		x=cap_X;
		y=cap_Y;
		//�L���v�V�����̕`��
		TextOut(hBuffer, x-(int)((sFW[iID_Cfw].nobm+0.5)*tm.tmAveCharWidth+5.*(double)tm.tmHeight/4.)-4,
			y+(int)(cap_H/2.+(ms/2.*tm.tmAveCharWidth)), Label, (int)ms);

		SelectObject(hBuffer , hFont_old);			//���̃t�H���g�ɖ߂�
		DeleteObject( hFont );						//�쐬�����_���t�H���g���폜����
		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);	// �t�H���g�̉�]�ݒ����
		
	}
	InvalidateRect(hWnd , &d , FALSE);		//�V�X�e���`�施�߂̃f�B�X�p�b�`
}

	//Paste the string specified by argument �etext�f in the figure window.
	//	The position(x, y) is based on the coordinates of each axis in the specified figure window.
	//	Can be used to express information such as graph titles and legends
void Text_draw(double xn, double yn, const char* buf){
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	int x,y,ret;
	TCHAR *buf0;
	size_t n;
	HFONT hFont,hFont_old;

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;
	double ymin=sFW[iID_Cfw].ymin;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�����ŏ��l�̏�������
	double ymax=sFW[iID_Cfw].ymax;
	double xmin=sFW[iID_Cfw].xmin;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�����ŏ��l�̏�������
	double xmax=sFW[iID_Cfw].xmax;

	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)
		+(sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)>1e-20){

		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// �t�H���g�̉�]�ݒ�
		hFont = CreateFontIndirect( &DefFont );				// �_���t�H���g���쐬����
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//�_���t�H���g��V���ɐݒ肵�Â��t�H���g��ۑ�

		x=figwin_X+(int)((xn-xmin)*(figwin_W-1.)/(xmax-xmin)+.5);
		y=figwin_Y+(int)((ymax-yn)*(figwin_H-1.)/(ymax-ymin)+.5);

		n=strlen(buf)+1;
		buf0=(TCHAR*)malloc(n*sizeof(TCHAR));

		ret=MultiByteToWideChar(0,0,buf,-1, buf0,(int)n);

		n=lstrlen(buf0);
		TextOut(hBuffer,x,y,buf0,(int)n);

		SelectObject(hBuffer , hFont_old);			//���̃t�H���g�ɖ߂�
		DeleteObject( hFont );						//�쐬�����_���t�H���g���폜����

		InvalidateRect(hWnd , &d , FALSE);
		free(buf0);
	}
}

	//�w�肳��Ă���t�B�M���A�E�C���h�E��int�^�z��yn�̐��ln�_���O���t���B
	//	�F�A���̎�ނ�Plot_pen()�Ŏw��BAxis_ycap(�c)�Ŏ��̍ő�ŏ����w��
	//	Set_Figure()�֐��ł��炩���߃t�B�M���A�E�C���h�E���w�肳��Ă��Ȃ��Ƃ����Ȃ�
	//	����Ă��Ȃ��Ƃ��́A�����I�ɔz����̍ő�l�ŏ��l��T��y����ݒ�A�`�悷��B
	//		yn:�\������z��̐擪�A�h���X(int �^)
	//		n: �\������z��̍ő�v�f
void Plot1d_int(int *yn,int n){

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;
	int i,ixx,iyy,it,ib; 
	double x,y,xx,yy,top,btm;
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpenull,hpen_old;	
	double ymin,ymax;

	//�t�B�M���A�E�C���h�E�̍ő�ŏ����O�ɐݒ肳��Ă���Ƃ�
	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<n;i++){		//�ő�l�C�ŏ��l�������I�ɒT��
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}
		//�O���[�o���ϐ��Ƀt�B�M���A�E�C���h�E�̍ő�ŏ�����������
		sFW[iID_Cfw].ymin=mi;
		sFW[iID_Cfw].ymax=ma;
		
		Axis_ycap(mi,ma,sFW[iID_Cfw].ylabel);		//y���̐��l���x���A�L���v�V�����`��
	}
	if ((sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)<1e-20){
		double st,en,in;

		sFW[iID_Cfw].xmin=(double)0;
		sFW[iID_Cfw].xmax=((double)n-1);

		auto_label(sFW[iID_Cfw].xmin,sFW[iID_Cfw].xmax,&st,&en,&in);
		sFW[iID_Cfw].xs=st;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ŏ��l�̏�������
		sFW[iID_Cfw].xe=en;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ő�l�̏�������
		sFW[iID_Cfw].xd=in;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���Ԋu�̏�������
	} 

	//�O���[�o���ϐ�����ȑO�Ɏw�肵���ő�ŏ���ǂݍ���
	ymax=sFW[iID_Cfw].ymax;
	ymin=sFW[iID_Cfw].ymin;

	top=figwin_Y+.5-1;
	btm=((double)figwin_Y+ (double)figwin_H)+.5;

	it=(int)top;
	ib=(int)btm;
	xx=(double)figwin_X+.5;
	yy=(double)figwin_Y+(ymax-(yn[0]))*(figwin_H-1.)/(ymax-ymin)+.5;
	ixx=(int)xx;
	iyy=(int)yy;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//�y���̍쐬
	hpenull=(HPEN)GetStockObject(NULL_PEN);				//�k���y���̍쐬

	if((iyy>=it)&(iyy<=ib)){		//�����y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);
	} else {
		hpen_old=(HPEN)SelectObject(hBuffer , hpenull);
	}

	MoveToEx(hBuffer , ixx , iyy , NULL);

	SetBkMode(hBuffer , TRANSPARENT);
	for(i=1;i<n;i++){
		
		x=(double)figwin_X+i*((double)figwin_W-1.)/((double)n-1.)+.5;
		y=(double)figwin_Y+(ymax-(yn[i]))*((double)figwin_H-1.)/(ymax-ymin)+.5;

		drawline(x,y,xx,yy,top,btm,hpen,hpenull);
		xx=x;
		yy=y;
	}

	sFW[iID_Cfw].N=n;		//�}�ɕ\�������|�C���g��
	sFW[iID_Cfw].pf[sFW[iID_Cfw].pn]=PenStyle;
	sFW[iID_Cfw].pw[sFW[iID_Cfw].pn]=PenWidth;
	sFW[iID_Cfw].pc[sFW[iID_Cfw].pn]=PenColor;
	sFW[iID_Cfw].pn++;

	if (sFW[iID_Cfw].pn>PNMAX) sFW[iID_Cfw].pn=PNMAX;

	SetBkMode(hBuffer , OPAQUE);
	SelectObject(hBuffer , hpen_old);
	DeleteObject(hpen);

	InvalidateRect(hWnd , &d , FALSE);
}

//�w�肳��Ă���t�B�M���A�E�C���h�E��double�^�z��yn�̐��ln�_���O���t���B
//	�F�A���̎�ނ�Plot_pen()�Ŏw��BAxis_ycap(�c)�Ŏ��̍ő�ŏ����w��
//	Set_Figure()�֐��ł��炩���߃t�B�M���A�E�C���h�E���w�肳��Ă��Ȃ��Ƃ����Ȃ�
//	����Ă��Ȃ��Ƃ��́A�����I�ɔz����̍ő�l�ŏ��l��T��y����ݒ�A�`�悷��B
//		yn:�\������z��̐擪�A�h���X(double �^)
//		n: �\������z��̍ő�v�f
void Plot1d(double *yn,int n){

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;
	int i;
	int ixx,iyy,it,ib; 
	double x,y,xx,yy,top,btm;
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpenull,hpen_old;	
	double ymin,ymax;

	//�t�B�M���A�E�C���h�E�̍ő�ŏ����O�ɐݒ肳��Ă���Ƃ�
	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<n;i++){		//�ő�l�C�ŏ��l�������I�ɒT��
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}
		//�O���[�o���ϐ��Ƀt�B�M���A�E�C���h�E�̍ő�ŏ�����������
		sFW[iID_Cfw].ymin=mi;
		sFW[iID_Cfw].ymax=ma;
		
		Axis_ycap(mi,ma,sFW[iID_Cfw].ylabel);		//y���̐��l���x���A�L���v�V�����`��
	}
	if ((sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)<1e-20){
		double st,en,in;

		sFW[iID_Cfw].xmin=(double)0;
		sFW[iID_Cfw].xmax=(double)n-1;

		auto_label(sFW[iID_Cfw].xmin,sFW[iID_Cfw].xmax,&st,&en,&in);
		sFW[iID_Cfw].xs=st;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ŏ��l�̏�������
		sFW[iID_Cfw].xe=en;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���ő�l�̏�������
		sFW[iID_Cfw].xd=in;	//�O���[�o���ϐ��ւ̃t�B�M���A�E�C���h�E�̖ڐ���Ԋu�̏�������
	} 

	//�O���[�o���ϐ�����ȑO�Ɏw�肵���ő�ŏ���ǂݍ���
	ymax=sFW[iID_Cfw].ymax;
	ymin=sFW[iID_Cfw].ymin;

	top=figwin_Y+.5;
	btm=((double)figwin_Y+ (double)figwin_H)-.5;

	it=(int)top;
	ib=(int)btm;
	xx=(double)figwin_X+.5;
	yy=(double)figwin_Y+(ymax-yn[0])*((double)figwin_H-1.)/(ymax-ymin)+.5;
	ixx=(int)xx;
	iyy=(int)yy;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//�y���̍쐬
	hpenull=(HPEN)GetStockObject(NULL_PEN);				//�k���y���̍쐬

	if((iyy>=it)&(iyy<=ib)){		//�����y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);
	} else {
		hpen_old=(HPEN)SelectObject(hBuffer , hpenull);
	}

	MoveToEx(hBuffer , ixx , iyy , NULL);

	SetBkMode(hBuffer , TRANSPARENT);
	for(i=1;i<n;i++){
		
		x=(double)figwin_X+i*((double)figwin_W-1.)/((double)n-1.)+.5;
		y=(double)figwin_Y+(ymax-(yn[i]))*((double)figwin_H-1.)/(ymax-ymin)+.5;

		drawline(x,y,xx,yy,top,btm,hpen,hpenull);
		xx=x;
		yy=y;
	}
	sFW[iID_Cfw].N=n;		//�}�ɕ\�������|�C���g��

	sFW[iID_Cfw].pf[sFW[iID_Cfw].pn]=PenStyle;
	sFW[iID_Cfw].pw[sFW[iID_Cfw].pn]=PenWidth;
	sFW[iID_Cfw].pc[sFW[iID_Cfw].pn]=PenColor;
	sFW[iID_Cfw].pn++;
	if (sFW[iID_Cfw].pn>PNMAX) sFW[iID_Cfw].pn=PNMAX;

	SetBkMode(hBuffer , OPAQUE);
	SelectObject(hBuffer , hpen_old);
	DeleteObject(hpen);

	InvalidateRect(hWnd , &d , FALSE);
}

	//�w�肳��Ă���t�B�M���A�E�C���h�E��double�^�z��xn������,yn�������ɑΉ��������O���t��`��B
	//	�F�A���̎�ނ�Plot_pen()�Ŏw��B
	//	���炩����Axis_ycap(�c)�AAxis_xcap(�c)��y���Ax���̕\���͈́A�����x�����w��\
	//	����Ă��Ȃ��Ƃ��́A�����I�ɔz����̍ő�l�ŏ��l��T��y����ݒ�A�`�悷��B
	//		xn,yn:double�^�̔z��
	//		n: �\������z��̍ő�v�f
void Plotxy(double *xn,double *yn,int n){

	int i,ixx,iyy,it,ib,il,ir; 
	double x,y,xx,yy,top,btm,lft,rit;
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpenull,hpen_old;	
	double ymin,ymax,xmax,xmin;

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;

	//�t�B�M���A�E�C���h�E�̍ő�ŏ����O�ɐݒ肳��Ă���Ƃ�
	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<n;i++){		//y���̍ő�l�C�ŏ��l�������I�ɒT��
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}

		//�O���[�o���ϐ��Ƀt�B�M���A�E�C���h�E�̍ő�ŏ�����������
		sFW[iID_Cfw].ymin=mi;
		sFW[iID_Cfw].ymax=ma;
		
		Axis_ycap(mi,ma,sFW[iID_Cfw].ylabel);		//y���̐��l���x���A�L���v�V�����`��
	}

	if ((sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)<1e-20){
		double ma=xn[0];
		double mi=xn[0];

		for(i=1;i<n;i++){		//�����̍ő�l�C�ŏ��l�������I�ɒT��
			if (xn[i]>ma) {ma=xn[i];}
			if (xn[i]<mi) {mi=xn[i];}
		}
		sFW[iID_Cfw].xmin=mi;
		sFW[iID_Cfw].xmax=ma;
		Axis_xcap(mi,ma,sFW[iID_Cfw].xlabel);		//x���̐��l���x���A�L���v�V�����`��
	} 

	//�O���[�o���ϐ�����ȑO�Ɏw�肵���ő�ŏ���ǂݍ���
	ymax=sFW[iID_Cfw].ymax;
	ymin=sFW[iID_Cfw].ymin;
	xmax=sFW[iID_Cfw].xmax;
	xmin=sFW[iID_Cfw].xmin;

	top=figwin_Y+.5;
	btm=((double)figwin_Y+ (double)figwin_H)-.5;
	lft=figwin_X+.5;
	rit=((double)figwin_X+ (double)figwin_W)-.5;

	it=(int)top;
	ib=(int)btm;
	il=(int)lft;
	ir=(int)rit;

	xx=(double)figwin_X+(xn[0]-xmin)*(figwin_W-1.)/(xmax-xmin)+.5;
	yy=(double)figwin_Y+(ymax-yn[0])*(figwin_H-1.)/(ymax-ymin)+.5;
	ixx=(int)xx;
	iyy=(int)yy;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//�y���̍쐬
	hpenull=(HPEN)GetStockObject(NULL_PEN);				//�k���y���̍쐬

	if(((iyy>=it)&(iyy<=ib))){		//�����y���̎w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);
	} else {
		hpen_old=(HPEN)SelectObject(hBuffer , hpenull);
	}

	MoveToEx(hBuffer , ixx , iyy , NULL);

	SetBkMode(hBuffer , TRANSPARENT);
	for(i=1;i<n;i++){
	
		x=(double)figwin_X+(xn[i]-xmin)*((double)figwin_W-1.)/(xmax-xmin)+.5;
		y=(double)figwin_Y+(ymax-yn[i])*((double)figwin_H-1.)/(ymax-ymin)+.5;

		drawline(x,y,xx,yy,top,btm,hpen,hpenull);

		xx=x;
		yy=y;
	}

	sFW[iID_Cfw].N=n;		//�}�ɕ\�������|�C���g��

	sFW[iID_Cfw].pf[sFW[iID_Cfw].pn]=PenStyle;
	sFW[iID_Cfw].pw[sFW[iID_Cfw].pn]=PenWidth;
	sFW[iID_Cfw].pc[sFW[iID_Cfw].pn]=PenColor;
	sFW[iID_Cfw].pn++;

	if (sFW[iID_Cfw].pn>PNMAX) sFW[iID_Cfw].pn=PNMAX;

	SetBkMode(hBuffer , OPAQUE);
	SelectObject(hBuffer , hpen_old);
	DeleteObject(hpen);

	InvalidateRect(hWnd , &d , FALSE);
}


/*	�w�肳��Ă���t�B�M���A�E�C���h�E��double�^�z��yn��2D�摜��`��B
	�z��yn�͓񎟌��f�[�^��1�����z��ɕ��ёւ����f�[�^�Ƃ��ė^����Bx�����A�������̃|�C���g����nx,ny�ŗ^������B
	cmin,cmax: �J���[�X�P�[���̍ŏ��A�ő�l�̎w��,�����Ƃ�0�̂Ƃ��ő�ŏ��l�������I�ɒT���B
	plflug : �J���[�}�b�v�̎w��B0�F�O���[�X�P�[���A1�F���F�A2�F�A�Ԃ̏z�F
	cbflug : 0�F�J���[�o�[�\��off�A1�F�J���[�o�[�\��
	szflug : 0�F�摜�T�C�Y�Ɋ֌W�Ȃ��t�B�M���A�E�C���h�E�̋K��T�C�Y�Ɋg�債�ĕ`��
�@�@�@�@1�F�t�B�M���A�E�C���h�E�̃T�C�Y�𐳕��`�ɂ��ĕ`��
�@�@�@�@2�F�f�[�^�̃T�C�Y�ɑΉ������s�N�Z�����ŕ`��i�ł����ꂢ�j
	�f�[�^�̏c���T�C�Y���E�C���h�E�T�C�Y���傫���Ɖ摜�������̂Œ���

	0�Ԗ�:x=0;y=0, 1�Ԗ�:x=1;y=0, �c	,nx�Ԗ�:x=nx-1;y=0, nx+1�Ԗ�:x=0;y=1, nx+2�Ԗ�:x=1;y=1, �c , Nx*ny-2�Ԗ�:x=nx-2;y=nx-1, Nx*ny-1�Ԗ�:x=nx-1;y=ny-1
	�̏��Ԃœ񎟌��f�[�^��z��yn�Ɋi�[����B
*/
void Plot2d(double *yn,int nx,int ny, double cmin, double cmax, int plflug, int cbflug, int szflug){

	int i,j,px,py;
	double c;
	int cn;
	HDC hdc;
	PAINTSTRUCT ps;
	COLORREF pc[PALLET_NUM];
	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin-1;
	int figwin_H=sFW[iID_Cfw].hwin-1;

	//�J���[�o�[�t���O�C�T�C�Y�t���O�̃`�F�b�N

	if(cbflug== LEGEND_ON){			//�J���[�o�[��\��
		Clf(CLEAR_FIG);										//�t�B�M���A�E�C���h�E���������A
		figwin_W=sGW.w/sFW[iID_Cfw].wn-(MERGIN_L+MERGIN_R);	//�V���ȃE�C���h�E�T�C�Y������
		figwin_W=(int)(figwin_W*0.85);
	} else{
		if ((szflug== SIZE_SQUARE)|(szflug == SIZE_DATA)){		//�J���[�o�[���\��
			Clf(CLEAR_FIG);	//�t�B�M���A�E�C���h�E����������
		}
	}

	if (szflug== SIZE_SQUARE){			//�`��T�C�Y�������`�̂Ƃ�
		if(figwin_W>figwin_H){
			figwin_W=figwin_H;		//�����L���Ƃ��������߂�
		} else {
			figwin_H=figwin_W;		//�c�������Ƃ����������k�߂�
		}
	} else if (szflug== SIZE_DATA){	//�`��T�C�Y���f�[�^�T�C�Y�̂Ƃ�
		figwin_W=nx+1;
		figwin_H=ny+1;
	} 
	
	sFW[iID_Cfw].wwin=figwin_W+1;	//�O���[�o���ϐ��ɃT�C�Y��o�^���A
	sFW[iID_Cfw].hwin=figwin_H+1;
	Clf(-1);					//��ʏ���

	//�J���[�X�P�[���̍ŏ��C�ő�l�Ƃ��ɂO�̂Ƃ������I�ɍő�ŏ��l��T���D

	if((cmin*cmin+cmax*cmax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<nx*ny;i++){
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}
		cmin=mi;
		cmax=ma;
	}

	if((nx>figwin_W)|(ny>figwin_H)){
	MessageBox(hWnd, TEXT("�f�[�^�̃T�C�Y���t�B�M���A�E�C���h�E�̃T�C�Y���傫�����߉摜������܂�"),TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	}

	colormap(plflug,pc);	//�J���[�}�b�v�̎擾

	//�Q�c�摜�̕\��
	for(i=0;i<nx;i++){
		px=figwin_X+i+1;

		for(j=0;j<ny;j++){
			py=figwin_Y+figwin_H-j-1;

			c=(yn[j*nx+i]-cmin)/(cmax-cmin);	//�񎟌��f�[�^���J���[�}�b�v�f�[�^�ɑΉ�������
			if (c<0) {c=0;}
			if (c>1) {c=1;}
			cn=(int)(c*((double)PALLET_NUM-1)+.5);
			SetPixel(hBuffer,px,py,pc[cn]);  //�J�����g�E�C���h�E�Ƀf�[�^�T�C�Y�Ɠ����s�N�Z���͈͂ŕ\��
		}
	}

	//�J�����g�E�C���h�E�̐}���w��̃T�C�Y�Ɉ����L�΂�

	hdc = BeginPaint(hWnd , &ps);
	SetStretchBltMode(hdc , HALFTONE);
	StretchBlt(hBuffer , figwin_X+1 , figwin_Y+1 , figwin_W-1 , figwin_H-1 ,
		       hBuffer , figwin_X+1 , figwin_Y+1+figwin_H-ny-1,nx,ny , SRCCOPY);
	EndPaint(hWnd , &ps);

	////////////////////
	//�J���[�o�[�̕\��//
	////////////////////

	if(cbflug== LEGEND_ON){

		double am,st,en,in;
		int i,j,l,gg,pn;
		double c[PALLET_NUM*5];
		int x,y;
		size_t nob;

		char a[BUFNMAX+1];
		TCHAR b[BUFNMAX+1];
		TEXTMETRIC tm;
		HPEN hpen,hpen_old;
		HFONT hFont,hFont_old;

		auto_label(cmin,cmax,&st,&en,&in);		//�J���[���x���̎擾

		//Plot2D���g���ăJ���[�o�[��\�����邽�߈ꎞ�I�Ƀt�B�M���A�E�C���h�E���쐬
		gg=iID_Cfw;
		iID_Cfw=FIGMAX-1;

		//�J���[�o�[�̃T�C�Y������
		sFW[iID_Cfw].wwin=(int)(sFW[gg].wwin/10.);		
		sFW[iID_Cfw].hwin=(int)(sFW[gg].hwin*0.8);
		sFW[iID_Cfw].xwin=(int)(sFW[gg].xwin+sFW[gg].wwin*1.03);
		sFW[iID_Cfw].ywin=(int)(sFW[gg].ywin+sFW[gg].hwin)-sFW[iID_Cfw].hwin;
	
		//l=(int)(sFW[gg].hwin/8.);	//	�J���[�o�[�̃E�C���h�E��
		l=2;

		if (sFW[iID_Cfw].hwin>PALLET_NUM){
			pn=PALLET_NUM-1;			
		} else {
			pn=(int)(8*(floor(sFW[iID_Cfw].hwin/8.)))-1;//	�J���[�o�[�͈̔͂��Ďw��
		}

		for (i=0;i<pn;i++){
			for(j=0;j<l;j++){
				c[i*l+j]=i*(((double)PALLET_NUM-1)/(pn-1.));    //�J���[�o�[�Ɏg���񎟌��f�[�^�̍쐬
			}
		}

		Plot2d(c,l,pn,0, (double)PALLET_NUM-1,plflug,LEGEND_OFF,0);		//Plot2D�֐����g�����J���[�o�[�̕\���i�ċA�Ăяo���j

		//�J���[���x���̕\��
		hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//���������̃y���w��
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);

		Font_info(Used_Font,(long)(Used_Font_Size*0.85),0,Italic_Font_Flug);	// �t�H���g�T�C�Y�̏k��
		hFont = CreateFontIndirect( &DefFont );   // �_���t�H���g���쐬����
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );

		GetTextMetrics(hBuffer , &tm);

		if (((double)sFW[iID_Cfw].hwin*in/(cmax-cmin))<5*(double)tm.tmHeight/4.) {
			in=in*2;

			if (fabs(st)>1e-10){  //���l���x����0�������0��ʂ�悤�ɒ���
				char n1[BUFNMAX+1],n2[BUFNMAX+1];
				sprintf_s(n1,BUFNMAX,"%g",st);
				sprintf_s(n2,BUFNMAX,"%g",st+in/2);
				if ((strlen(n1)>strlen(n2))&(fmod(fabs(st+in/2),in)<1e-10)){	
					st=st+in/2;
				}
			}
		}

		for(am=st;am<=cmax;am=am+in){

			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );

			x=sFW[iID_Cfw].xwin+sFW[iID_Cfw].wwin-1;
			y=sFW[iID_Cfw].ywin+(int)((sFW[iID_Cfw].hwin-1.)*(cmax-am)/(cmax-cmin));

			TextOut(hBuffer, x+(int)(sFW[iID_Cfw].wwin/3.), y-(int)(tm.tmHeight/2.), b, (int)nob-1);

			MoveToEx(hBuffer , x-(int)(sFW[iID_Cfw].wwin/10.), y  , NULL);
			LineTo(hBuffer , x,y );

		}

		SelectObject(hBuffer , hFont_old);
		DeleteObject( hFont );   // �쐬�����_���t�H���g���폜����
		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);	// �t�H���g�T�C�Y�̏k������

		SelectObject(hBuffer , hpen_old);
		DeleteObject(hpen);

		iID_Cfw=gg;  //�J�����g�t�B�M���A�ԍ������ɖ߂�
	}

	sFW[iID_Cfw].N=nx*ny;
	InvalidateRect(hWnd , &d , FALSE);
}

/*
	If you draw continuously by using Plot() function, it will be overwritten.
	Legend() function displays legends for the number of the overlaid graphs.
	The string of the legend should be written as �gline1 | line2 | line3�h.
	The name of each line is delimited the character �e | �f in the string .
	the legend position is specified by pos flag as
		1 : upper left corner
		2 : upper right corner
		3 : lower left corner
		4 : lower right corner
		0 : bottom right outside the frame
*/
void Legend(const char *label, int pos){

	int figwin_X=sFW[iID_Cfw].xwin;
	int figwin_Y=sFW[iID_Cfw].ywin;
	int figwin_W=sFW[iID_Cfw].wwin;
	int figwin_H=sFW[iID_Cfw].hwin;
	int lx,ly,lw,lh,lm,nobm=0;
	int i,ic,ll,l,pf,pw,pc,cn=0;
	HPEN hpen,hpen_old;
	HFONT hFont,hFont_old;
	TEXTMETRIC tm;
	int bufn[BUFNMAX+1];
	char bl[BUFNMAX+1];
	TCHAR bufW[PNMAX][BUFNMAX+1];

	for(i=0;i<PNMAX;i++){
		for(ic=0;ic<BUFNMAX;ic++){
			bufW[i][ic]=0;
			bufn[i] = 0;
		}
	}

	ic=0;
	cn=0;
	l=(int)strlen(label);

	for(i=0;i<l+1;i++){
		
		if((label[i]!='|') & (i<l)){
			bl[ic]=label[i];
			ic++;
		} else {

		bl[ic]='\0';
		if (ic>nobm){nobm=ic;}
		wsprintf(bufW[cn],L"%S",bl);
		bufn[cn]=ic;
		ic=0;
		cn++;
		}
	}

	pf=PenStyle;
	pw=PenWidth;
	pc=PenColor;

	hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//���������̃y�����w��
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//�y���̐ݒ���s���C�Â��y������hpen_old��

	Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// �t�H���g�̉�]�ݒ�
	hFont = CreateFontIndirect( &DefFont );				// �_���t�H���g���쐬����
	hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//�_���t�H���g��V���ɐݒ肵�Â��t�H���g��ۑ�

	GetTextMetrics(hBuffer , &tm);	//�t�H���g�T�C�Y��񓙎擾�̂��߂̐ݒ�

	ll=(nobm+1)*tm.tmAveCharWidth;				//	�}��̕����̕�
	lm=tm.tmAveCharWidth;					//�@�}��̍��E�㉺�}�[�W��

	lw=lm*2+(int)(ll*2);					//�@�}��̕�
	lh=(sFW[iID_Cfw].pn*tm.tmHeight+lm*2);  //  �}��̍���

	if ((pos<0)|(pos>4)){
		pos=0;
		MessageBox(hWnd, TEXT("�ʒu�w�肪�Ԉ���Ă��܂��D�E���ɕ\�����܂��D"),TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	}

	switch (pos){		//	�}��̕\���ʒu����
		case 0:
			lx=figwin_X+figwin_W+lm;
			ly=figwin_Y+figwin_H-lh;
			break;
		case 1:
			lx=figwin_X+lm;
			ly=figwin_Y+lm;
			break;
		case 2:	
			lx=figwin_X+figwin_W-lm-lw;
			ly=figwin_Y+lm;
			break;
		case 3:
			lx=figwin_X+lm;
			ly=figwin_Y+figwin_H-lm-lh;
			break;
		default:
			lx=figwin_X+figwin_W-lm-lw;
			ly=figwin_Y+figwin_H-lm-lh;
			break;
	}

	Plot_pen(0,0,7);
	Rect(lx,ly,lx+lw,ly+lh,1);

	for(i=0;i<sFW[iID_Cfw].pn;i++){

		PenStyle=sFW[iID_Cfw].pf[i];
		PenWidth=sFW[iID_Cfw].pw[i];
		PenColor=sFW[iID_Cfw].pc[i];
 
		Line(lx+lm               ,ly+lm+(int)((i+.5)*tm.tmHeight),
			 lx+lm+(int)(ll*0.75) ,ly+lm+(int)((i+.5)*tm.tmHeight));

		TextOut(hBuffer,lx+lm*2+(int)(ll*0.75),ly+lm+i*tm.tmHeight,bufW[i],bufn[i]);	
	}
	Plot_pen(0,0,0);
	Rect(lx,ly,lx+lw,ly+lh,0);

	PenStyle=pf;
	PenWidth=pw;
	PenColor=pc;
}

void drawline(double x,double y,double xx,double yy,double top,double btm, HPEN hpen,HPEN hpenull){

	int ix,iy,ixx,iyy,it,ib;

	ix=(int)x;
	iy=(int)y;

	it=(int)top;
	ib=(int)btm;

	ixx=(int)xx;
	iyy=(int)yy;

	if ((ix!=ixx)|(iy!=iyy)){

		if ((iy>=it)&(iy<=ib)) {				//y���͈͓�
			if ((iyy>=it)&(iyy<=ib)){			//yy���͈͓�
				LineTo(hBuffer ,ix,iy);
			} else if (iyy<it){					//yy���������
				SelectObject(hBuffer , hpen);
				MoveToEx(hBuffer ,(int)(xx+(top-yy)/(y-yy)*(x-xx)),it,NULL);
				LineTo(hBuffer ,ix,iy);
			} else if (iyy>ib){					//yy��������艺
				SelectObject(hBuffer , hpen);
				MoveToEx(hBuffer ,(int)(xx+(btm-yy)/(y-yy)*(x-xx)),ib,NULL);
				LineTo(hBuffer ,ix,iy);
			} 
		} else if (iy<it){						//y���������
			if (iyy<it){						//yy���������
				LineTo(hBuffer ,ix,iy);
			} else {
				LineTo(hBuffer ,(int)(xx+(top-yy)/(y-yy)*(x-xx)),it);
				SelectObject(hBuffer , hpenull);
			}
		} else {								//y��������艺
			if (iyy>ib){						//yy��������艺
				LineTo(hBuffer ,ix,iy);
			} else {
				LineTo(hBuffer ,(int)(xx+(btm-yy)/(y-yy)*(x-xx)),ib);
				SelectObject(hBuffer , hpenull);
			}
		}
	} 
	xx=x;
	yy=y;

}

	//mlib�����֐�
	//ymin,ymax���琔�l���x���̏����l�A�ŏI�l�A�Ԋu�������I�Ɍv�Z����
void auto_label(double ymin,double ymax,double *st,double *en,double *dis){

	double mm,x,y,z,a,aa=1e10;
	double mioff,maoff;
	double ydis;
	double s[]={1.0, 2.0, 2.5, 5.0, 10.0};
	int kk,k;

	if (ymin>ymax){
	   mm=ymin;
	   ymin=ymax;
	   ymax=mm;
	}
	if (ymin==ymax){
	   ymin=ymax-1e-10;
	}

	x=log10(ymax-ymin);
	y=floor(x);
	z=pow(10.,x-y);

	for(k=0;k<5;k++){
		a=z/s[k];
		if (floor(a-.1)==0){
			if (aa>fabs(a-1.)) {
				kk=k;
				aa=fabs(a-1.);
			}
		}
	}
	ydis=s[kk]*pow(10.,y-1);

	mioff=0;
	maoff=0;

	*st=ceil((ymin-mioff)/ydis)*ydis;
	*en=floor((ymax+maoff)/ydis)*ydis;
	*dis=ydis;

}
	/*
	The default figure window sizes are evenly allocated according to the number of windows determined by the Set_figure() function.
	The window size is changed by a specified ratio represented by (width: height) = (ax: ay) within a range that does not exceed the default size.
	Must be called before plot() function.
	*/
void Aspect_ratio(double ax, double ay){

	int figwin_X=(sGW.w/sFW[iID_Cfw].wn)*((sFW[iID_Cfw].nn-1)%sFW[iID_Cfw].wn)+MERGIN_L;
	int	figwin_Y=(sGW.h/sFW[iID_Cfw].hn)*((sFW[iID_Cfw].nn-1)/sFW[iID_Cfw].wn)+MERGIN_T;

	int figwin_W=(sGW.w/sFW[iID_Cfw].wn)-(MERGIN_L+MERGIN_R)+1;
	int figwin_H=(sGW.h/sFW[iID_Cfw].hn)-(MERGIN_T+MERGIN_B)+1;
	int fW,fH;

	if (sFW[iID_Cfw].N==0) Clf(1);

	fW=(int)(figwin_H*ax/ay+.5);
	fH=(int)(figwin_W*ay/ax+.5);

	if(figwin_W>fW){
		//figwin_X=figwin_X+(figwin_W-fW)/2;
		figwin_W=fW;		//�����L���Ƃ��������߂�
	} else if (figwin_H>fH){
		figwin_Y=figwin_Y+(figwin_H-fH)/2;
		figwin_H=fH;		//�c�������Ƃ����������k�߂�
	}

	sFW[iID_Cfw].wwin=figwin_W;
	sFW[iID_Cfw].hwin=figwin_H;
	sFW[iID_Cfw].xwin=figwin_X;
	sFW[iID_Cfw].ywin=figwin_Y;
					//�t�B�M���A�E�C���h�E�̘g������
	Clf(-1);
}


	//	�O���t�B�b�N�E�C���h�E�S�̂��N���b�v�{�[�h�ɃR�s�[����
void Fig2clipboard(){

	TCHAR buf[1024];
	HANDLE hdl;

	OpenClipboard(hWnd);
	EmptyClipboard();							//�N���b�v�{�[�h���N���A
	hdl=SetClipboardData(CF_BITMAP, hBitmap);		//�N���b�v�{�[�h�Ɏ�荞��
	CloseClipboard();

	if(hdl==NULL){
		MessageBox(hWnd, TEXT("�}�̃N���b�v�{�[�h�ւ̃R�s�[�Ɏ��s���܂����D"), TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	} else {
		wsprintf(buf, TEXT("�}���N���b�v�{�[�h�ɃR�s�[����܂����B"));
		MessageBox(hWnd, buf, TEXT("Mlib�ɂ��x��"), MB_ICONHAND);
	}
}

	//mlib�����֐�
	//	Plot2D�ŗp����J���[�}�b�v��z��pc�ɓ���Ė߂��BPlot2D����Ăяo���Ă���B
	//	plflug=0	�O���C�X�P�[��
	//	plflug=1	���C���{�[�J���[
	//	plflug=2	��-��-��-��-���̏z�F�i�ʑ��̕\���Ȃǂɕ֗��j
void colormap(int plflug, COLORREF *pc){

	int i,p1,p2,p3,p4,p5;
	BYTE r,g,b,f;
	BYTE pc0[3*PALLET_NUM/2];

	if ((plflug<0)|(plflug>2)){
		plflug=1;
		MessageBox(hWnd, TEXT("�J���[�p���b�g�̎w�肪�͈͂𒴂��Ă��܂�"),TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	}

	switch(plflug){
	case GRAY:		//�O���C�X�P�[��
		for(i=0;i<PALLET_NUM;i++){
			r=(BYTE)(i/((double)PALLET_NUM-1.0)*255+.5);
			g=r;
			b=r;
			pc[PALLET_NUM-1-i]=RGB(r,g,b);
		}
		return;

	case RAINBOW:		//���C���{�[�J���[
		p1=3*PALLET_NUM/8;
		p2=5*PALLET_NUM/8;
		p3=7*PALLET_NUM/8;
		p4=9*PALLET_NUM/8;
		p5=12*PALLET_NUM/8;

		for(i=0;i<p5;i++){
			if (i<p1) {
				pc0[i]=0;
			} else if (i<p2) {
				pc0[i]=(BYTE)(((double)i-p1)/((double)p2-p1+0.0)*255+.5);
			} else if (i<p3) {
				pc0[i]=255;
			} else if (i<p4) {
				pc0[i]=(BYTE)(((double)p4-i)/((double)p4-p3+0.0)*255+.5);
			} else if (i<p5) {
				pc0[i]=0;
			}
		}
		for(i=0;i<PALLET_NUM;i++){
			r=pc0[i+4*PALLET_NUM/8];
			g=pc0[i+2*PALLET_NUM/8];
			b=pc0[i+0*PALLET_NUM/8];

			pc[PALLET_NUM-1-i]=RGB(r,g,b);
		}
		return;

	case CYCLIC:		//���|�|���|�ԁ|��
		p1=0*PALLET_NUM/4;
		p2=1*PALLET_NUM/4;
		p3=2*PALLET_NUM/4;
		p4=3*PALLET_NUM/4;
		f=0;
		for(i=0;i<PALLET_NUM;i++){
			if (i<p2) {
				r=f+(BYTE)(((double)i-p1)/((double)p2-p1+0.0)*(255-f)+.5);
				g=f;
				b=f;
				pc[PALLET_NUM-1-i]=RGB(r,g,b);
			} else if (i<p3) {
				r=255;
				g=f+(BYTE)(((double)i-p2)/((double)p3-p2+0.0)*(255-f)+.5);
				b=f+(BYTE)(((double)i-p2)/((double)p3-p2+0.0)*(255-f)+.5);
				pc[PALLET_NUM-1-i]=RGB(r,g,b);
			} else if (i<p4) {
				r=f+(BYTE)(((double)p4-i)/((double)p4-p3+0.0)*(255-f)+.5);
				g=f+(BYTE)(((double)p4-i)/((double)p4-p3+0.0)*(255-f)+.5);
				b=255;
				pc[PALLET_NUM-1-i]=RGB(r,g,b);
			} else if (i<PALLET_NUM) {
				r=f;
				g=f;
				b=f+(BYTE)(((double)PALLET_NUM-i)/((double)PALLET_NUM-p4+0.0)*(255-f)+.5);
				pc[PALLET_NUM-1-i]=RGB(r,g,b);
			}
		}
		return;
	}
}


	//	�G�f�B�b�g�{�b�N�X�̕�����𐮐��l�ɕϊ����Ė߂�l�Ƃ��ĕԂ��B
	//	���l�ȊO�����͂���Ă����0�ɂȂ�
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�(0,1,2,...)
int Get_int(int i){

	TCHAR *buffer;
	int len,num;

	len=GetWindowTextLength(sED[i].hdl) + 1;
	buffer=(TCHAR*)malloc((size_t)len*sizeof(TCHAR));

	if ((i>=0)&(i<ED_NUM)){
		GetWindowText(sED[i].hdl, buffer,len);		
		num=_tstoi(buffer);	//	���C�h������ϊ��\
				
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
		num=0;
	}
	free(buffer);
	return num;
}


	//�G�f�B�b�g�{�b�N�X�̕������double�^�����l�ɕϊ����Ė߂�l�Ƃ��ĕԂ��B
	//	���l�ȊO�����͂���Ă����0�ɂȂ�
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�(0,1,2,..)
double Get_double(int i){

	static TCHAR *buffer;
	char *mb;
	double num;
	int len,ret;
	PCSTR  pD=NULL ;    // �f�t�H���g�L�����N�^
    PBOOL  pU=NULL ;

	len=(int)GetWindowTextLength(sED[i].hdl) + 1;
	buffer=(TCHAR*)malloc((size_t)len*sizeof(TCHAR));
	mb=(char*)malloc((size_t)len*2*sizeof(char));

	if ((i>=0)&(i<ED_NUM)){
		GetWindowText(sED[i].hdl, buffer, len);
		
		ret=WideCharToMultiByte(0,0, buffer,len,mb,len*2,pD,pU);
		num=atof(mb);
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
		num=0.;
	}
	free(buffer);
	free(mb);
	return num;
}


	//�@�G�f�B�b�g�{�b�N�X�̕������TCHAR�^�z�� buffer �ɃR�s�[
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�
	//  TCHAR�^�Ŏ��o���̂ł��܂�g��Ȃ�,Get_char()���g�p
void Get_text(int i, TCHAR *buffer){

	if ((i>=0)&(i<ED_NUM)){
		GetWindowText(sED[i].hdl, buffer, GetWindowTextLength(sED[i].hdl)+ 1);
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
		lstrcpy(buffer,TEXT(""));
	}
}

	//�G�f�B�b�g�{�b�N�X�̕������char�^�z�� buffer �ɃR�s�[
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�
void Get_char(int i, char *buf0){

	TCHAR *buffer;
	int len,ret;

	PCSTR  pD=NULL ;    // �f�t�H���g�L�����N�^
    PBOOL  pU=NULL ;

	len=GetWindowTextLength(sED[i].hdl)+ 1;
	buffer=(TCHAR*)malloc((size_t)len*sizeof(TCHAR));

	if ((i>=0)&(i<ED_NUM)){
		
		GetWindowText(sED[i].hdl, buffer, len);
		ret=WideCharToMultiByte(0,0, buffer,len,buf0,len*2,pD,pU);
		
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
		*buf0='\0';
	}
	free(buffer);
	return;
}

	//�w�肵���G�f�B�b�g�{�b�N�X�� buffer �Ŏw�肵�����C�h��������o��
	//	wsprintf(buffer,TEXT("���l��%d�ł�"),value);���Ő����l��}��������������w��\
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�
	// TCHAR�^�̕�������o�͂���̂ŁA���܂�g��Ȃ�
void Set_text(int i, TCHAR *buffer){

	if ((i>=0)&(i<ED_NUM)){	
		SetWindowText(sED[i].hdl, buffer);
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	}
}

	//�w�肵���G�f�B�b�g�{�b�N�X��*buffer�Ŏw�肵��char�^��������o��
	//	wsprintf(buffer,"���l��%d�ł�",value); ���Ő����l��}��������������w��\
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�
void Set_char(int i, const char *buffer){

	TCHAR buf0[100];
	size_t n,ret;

	if ((i>=0)&(i<ED_NUM)){	
		n=strlen(buffer);
		mbstowcs_s(&ret,buf0,n+1,buffer,n+1);
		SetWindowText(sED[i].hdl, buf0);

	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	}
}

	//�w�肵���G�f�B�b�g�{�b�N�X��double�^�ϐ�x�̒l���o�́B
	//	i: �̓G�f�B�b�g�{�b�N�X�̔ԍ�
void Set_double(int i, double x){

	char buffer[100];
	TCHAR buf0[100];
	size_t n,ret;

	if ((i>=0)&(i<ED_NUM)){	
		sprintf_s(buffer,99,"%g",x);
		n=strlen(buffer);
		mbstowcs_s(&ret,buf0,n+1,buffer,n+1);
		SetWindowText(sED[i].hdl, buf0);

	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("�G�f�B�b�g�{�b�N�X�̔ԍ���0�`%d�܂łł��D"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlib�ɂ��x��"),MB_ICONHAND);
	}
}

	//���l���̓_�C�A���O�{�b�N�X�p�̃E�C���h�E�v���V�[�W��
LRESULT CALLBACK DialogProc(HWND hDiag , UINT iMsg , WPARAM wParam , LPARAM lParam) {

	static LPDWORD lpRes;
	if (hDiag==NULL) {
		/* ���ʕϐ��̃A�h���X��ۑ� */
		lpRes=(LPDWORD)iMsg;
		*lpRes=0;
		return 0;
	}
	switch (iMsg) {
		case WM_CREATE: /* �E�C���h�E�쐬���̏��� */
			
			/* �{�^���쐬 */
			hDiaBt1=CreateWindow(TEXT("BUTTON"),TEXT("OK"),WS_CHILD|WS_VISIBLE,
			  190,8,60,32,hDiag,(HMENU)0,hInst,NULL);

			hDiaBt2=CreateWindow(TEXT("EDIT"),TEXT(""),WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_RIGHT,
			  8,8,170,32,hDiag,(HMENU)1,hInst,NULL);
			return 0;

		case WM_COMMAND: /* �R�}���h���b�Z�[�W */
			switch (LOWORD(wParam)) {
				case 0: /* �P�ԃ{�^�� */
					*lpRes=1;
					GetWindowText(hDiaBt2,Input1,GetWindowTextLength(hDiaBt2)+2);				
					DestroyWindow(hDiag);
					break;
			}
			return 0;
	
		case WM_DESTROY : /* �I������ */

			if (*lpRes==0) /* �ǂ�����I������Ă��Ȃ����-1 */
				*lpRes=-1;
			return 0;
	}
	return DefWindowProc (hDiag, iMsg, wParam, lParam) ;
}

	//���l���̓_�C�A���O�{�b�N�X�p�̃��[�_���_�C�A���O�֐�
DWORD dialog(LPCTSTR Mess) {

	DWORD dwRes;
	MSG msg;
	
	/* �_�C�A���O�̃E�C���h�E�v���V�[�W���|�Ɍ��ʕϐ��̃A�h���X��n�� */
	DialogProc(NULL,(UINT)LOWORD(&dwRes),0,0);

	/* �_�C�A���O�{�b�N�X�쐬 */
	hEditDialog = CreateWindow(TEXT("CDialog"),Mess,
	  WS_OVERLAPPEDWINDOW | WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,
	  270,80,NULL,NULL,hInst,NULL);

	/* ���C���E�C���h�E�𖳌������ă��[�_���� */
	EnableWindow(hWnd,FALSE);
	SetFocus(hDiaBt2);
	/* ���b�Z�[�W���[�v */
	while (dwRes==0) { /* �_�C�A���O�����ʂ�Ԃ��܂Ń��[�v */
		GetMessage(&msg,NULL,0,0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	/* ���C���E�C���h�E��L���ɂ��ă��[�_������ */
	EnableWindow(hWnd,TRUE);
	BringWindowToTop(hWnd);
	/* �_�C�A���O�̑I�����ʂ�Ԃ� */
	return dwRes;
}

	//	�����l����͂���_�C�A���O�{�b�N�X��\������B
	//	�����ȊO����͂����0���o�͂����B
	//	�P�Ȃ�L�[���͑҂��Ƃ��Ă��g�p�ł���B
int Input_int(){

	DWORD dwMRes;
	static char mb[200];
	int num;

	dwMRes=dialog(TEXT("�����l����͂��Ă�������"));
	num = _tstoi(Input1);

	Printf("%d�����͂���܂���\n", num);
	return num;
}


	//	��������͂���_�C�A���O�{�b�N�X��\������B
	//	double�^�ŏo�́B���l�ȊO����͂����0���o�͂����B
double Input_double(){

	DWORD dwMRes;
	static char mb[200];
	int len,ret;
	double num;
	PCSTR  pD=NULL ;    // �f�t�H���g�L�����N�^
    PBOOL  pU=NULL ;

	dwMRes=dialog(TEXT("��������͂��Ă�������"));
	
	len=(int)lstrlen(Input1);
	ret=WideCharToMultiByte(0,0, Input1,len,mb,len*2,pD,pU);

	num = atof(mb);
	Printf("%f�����͂���܂���\n", num);

	return num;
}


	//	���������͂���_�C�A���O�{�b�N�X��\������B
	//	���͂��ꂽ������̐擪�A�A�h���X��TCHAR�^�ŕԂ��B
TCHAR *Input_text(){
	
	DWORD dwMRes;
	dwMRes=dialog(TEXT("��������͂��Ă�������"));
	Print(Input1);
	Printf("�����͂���܂���\n");

	return Input1;
}

	//	���������͂���_�C�A���O�{�b�N�X��\������B
	//	���͂��ꂽ������̐擪�A�A�h���X��TCHAR�^�ŕԂ��B
char *Input_char(){

	DWORD dwMRes;
	static char mb[200];
	int len,ret;
	PCSTR  pD=NULL ;    // �f�t�H���g�L�����N�^
    PBOOL  pU=NULL ;

	dwMRes=dialog(TEXT("��������͂��Ă�������"));
		
	len=(int)lstrlen(Input1);
	ret=WideCharToMultiByte(0,0, Input1,len,mb,len*2,pD,pU);

	Printf(mb);
	Printf("�����͂���܂���\n");

	return mb;
}

	//�ꎞ��~�̃��b�Z�[�W�{�b�N�X���o��
void Pause(){

	MessageBox(NULL , TEXT("�ꎞ��~��") ,
			TEXT("") ,
			MB_OK | MB_ICONHAND);
}

	//�҂����Ԃ��~���b�Ŏw��(Sleep�֐��Ɠ���)
void Delay(int msec){

	Sleep(msec);
}

	//��ʕ`��������I�ɍX�V����
	//	�ʏ�A������`��֐��̓������ɏ������܂�邾���ŕ`�悹���A
	//	main�֐��I�����Ɏ����I�ɕ`�悷��ݒ�ɂȂ��Ă���B
	//	main�֐����Ń��A���^�C���`�悪�K�v�ȏꍇ�A���̊֐��Ăяo���ŋ����I�ɉ�ʕ`����s��
	//	�����I�ɂ́AUpdateWindow(hWnd)�@�Ɠ���
void Refresh(void) {

	UpdateWindow(hWnd);

}

