//------------------------
//  Mlib ver 3.8
//  
//-------------------------
// 関数のプロトタイプ宣言

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
// 関数のプロトタイプ宣言終了


	//プログラムのメイン関数
	//WIN32APIプログラムではここから始まる。
    //メインウインドウとダイアログウインドウの定義
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR lpCmdLine,int nCmdShow) {

    MSG msg;
	WNDCLASSEX winc,diaclass;
	hInst=hInstance;	/* プロセスのハンドルを保存 */

	//ウインドウクラスの定義（メインウインドウのクラスを定義している）
	winc.cbSize        = sizeof(winc);
	winc.style		= CS_HREDRAW | CS_VREDRAW ;   //ウインドウサイズの変更可
	winc.lpfnWndProc	= WndProc;   //ウインドウプロシージャ関数の定義
	winc.cbClsExtra	= 0;
	winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	=(HBRUSH)(COLOR_BTNFACE+1);// (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("GUIconsole");   //ウインドウクラスの名前。ウインドウ作成時に指定する
	winc.hIconSm       = LoadIcon(NULL,IDI_APPLICATION);

	RegisterClassEx(&winc);	/* ウインドウクラス登録 */

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

	RegisterClassEx(&diaclass);		/* ウインドウクラス登録 */

	//メインウインドウの作成
	//親ウインドウであるため、ウインドウハンドルをhWndに返すよう設定
	//第一引数：ウインドウクラスの指定（上で定義したクラスを使用）
	//第二引数：タイトルバーの名前
	//第三引数：オーバーラップ可、可視を指定（他にもいろいろある。論理和記号で結合）
	//第４－７引数：座標と幅、高さ
	hWnd = CreateWindow(
			TEXT("GUIconsole") , TEXT(PROGRAM_TITLE) ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			MAINWIN_W , MAINWIN_H ,
			NULL , NULL , hInstance , NULL
	);
	
	//ディスパッチャーの処理
	while(GetMessage(&msg , NULL , 0 , 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

	//メインウインドウのウインドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {

	HDC hdc;
	HGDIOBJ hpen;
	PAINTSTRUCT ps;
	long lo;
	long long i=0; 
	int j,k=0;

	switch (msg) {
	case WM_DESTROY:
		// ウインドウcloseの処理

		DeleteDC(hBuffer);
		DeleteObject(hBitmap);

		PostQuitMessage(0);
		return 0;
	       
	case WM_CREATE:

		component();	//ボタン情報の登録
		
		//プッシュボタン作成

		for(i=0;i<PB_NUM;i++){
			sPB[i].hdl=CreateWindowEx(WS_EX_CONTROLPARENT |WS_EX_WINDOWEDGE ,
				TEXT("BUTTON") , sPB[i].name ,
				WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE |BS_MULTILINE ,
				sPB[i].x , sPB[i].y , sPB[i].w , sPB[i].h ,
				hWnd , (HMENU)(BUTTON_ID1+i) , hInstance , NULL
			);
		}
		
		//チェックボックス作成
		for(i=0;i<CK_NUM;i++){
			sCK[i].hdl=CreateWindow(
				TEXT("BUTTON") , sCK[i].name ,
				WS_CHILD| WS_VISIBLE | BS_AUTOCHECKBOX     ,
				sCK[i].x , sCK[i].y , sCK[i].w , sCK[i].h ,
				hWnd , (HMENU)(BUTTON_ID1+PB_NUM+i) , hInstance , NULL
			);
			sCK[i].chk=FALSE;
		}

		//ラジオボタン作成
		for(i=0;i<RD_NUM;i++){
			sRD[i].hdl=CreateWindow(
				TEXT("BUTTON") , sRD[i].name ,
				WS_CHILD| WS_VISIBLE | BS_AUTORADIOBUTTON  | WS_GROUP*sRD[i].chk ,
				sRD[i].x , sRD[i].y , sRD[i].w , sRD[i].h ,
				hWnd , (HMENU)(BUTTON_ID1+PB_NUM+CK_NUM+i) , hInstance , NULL
			);
			sRD[i].chk=FALSE;
		}

		//エディットウインドウ作成
		for (i=0;i<ED_NUM;i++){
			sED[i].hdl=CreateWindowEx(WS_EX_CLIENTEDGE |WS_EX_CONTROLPARENT ,
				TEXT("EDIT") , sED[i].name , 
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT  |ES_AUTOHSCROLL ,
				sED[i].x , sED[i].y , sED[i].w , sED[i].h ,
				hWnd , (HMENU)(EDIT_ID1+i) ,
				hInstance , NULL
			);
		}

		//スタティック作成
		for (i=0;i<ST_NUM;i++){
			sST[i].hdl=CreateWindow(
				TEXT("STATIC") , sST[i].name , 
				WS_CHILD  | WS_VISIBLE  |sST[i].chk ,
				sST[i].x , sST[i].y , sST[i].w , sST[i].h ,
				hWnd , (HMENU)(STATIC_ID1+i) ,
				hInstance , NULL
			);
		}

		//　メモウインドウ作成
		hMemo1 = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("EDIT") , NULL , 
			WS_CHILD  | WS_HSCROLL  |
			ES_AUTOHSCROLL  |ES_READONLY |
			ES_LEFT | ES_MULTILINE | WS_VISIBLE | WS_BORDER ,
			sME.x ,sME.y,sME.w,sME.h,
			hWnd , (HMENU)MEMO_ID1 ,
			hInstance , NULL
		);

		//  メモウインドウのスクロールバー作成
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

	//  ファント構造体の初期化
		ZeroMemory( &DefFont, sizeof(DefFont) );	// フォント情報構造体を０で初期化			
		DefFont.lfCharSet=DEFAULT_CHARSET;		//デフォルト_CHARSET
		DefFont.lfHeight=Used_Font_Size;			
		lstrcpy(DefFont.lfFaceName,Used_Font);
			//	DefFont.lfOutPrecision=1;//8;
		DefFont.lfQuality=5;


	//  グラフィックウインドウのビットマップをメモリ内に確保
		hdc = GetDC(hWnd);

		hBitmap = CreateCompatibleBitmap(hdc , sGW.w , sGW.h); //画面表示用ビットマップ作成
		hBuffer = CreateCompatibleDC(hdc);		//バッファーウインドウ作成

		SelectObject(hBuffer , hBitmap);
		SelectObject(hBuffer , GetStockObject(NULL_PEN));

		PatBlt(hBuffer , 0 , 0 , sGW.w , sGW.h , WHITENESS); //バッファクリア
		
		ReleaseDC(hWnd , hdc);

		hpen = CreatePen(PS_SOLID , 0 ,RGB(0,0,0));
		hpen = GetStockObject(WHITE_PEN);
		SelectObject(hBuffer , hpen);

		Rectangle( hBuffer , 0,0,sGW.w, sGW.h);
		DeleteObject(SelectObject(hBuffer , GetStockObject(WHITE_BRUSH)));

		Clf(2);

		return 0;

/*-------マウスキャプチャー
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
-------マウスキャプチャー*/

	case WM_COMMAND:
		
		// 各種ボタンが押されたときの処理

		j=LOWORD(wp)-BUTTON_ID1;

		if((j>=0)&(j<PB_NUM)) {				// プッシュボタンの処理
			main(j);

		}else if (j<PB_NUM+CK_NUM) {		// チェックボタンの処理
			int jj = j - PB_NUM;
			lo=(long)SendMessage(sCK[jj].hdl, BM_GETCHECK, 0, 0);
			sCK[jj].chk=lo;

		}else if (j<PB_NUM+CK_NUM+RD_NUM) {	// ラジオボタンの処理

			for(k=0;k<RD_NUM;k++){
				sRD[k].chk=(long)SendMessage(sRD[k].hdl , BM_GETCHECK , 0 , 0);
			}
		}
		return 0;


	case WM_VSCROLL:
		//メモウインドウのスクロール処理
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
		//windowsのシステムでの描画命令が実行されたときの処理
		//描画はメモリ内のビットマップ領域に行い
		//描画のたびにメモリから画面に描画データをコピーする

		hdc = BeginPaint(hWnd , &ps);
		BitBlt(hdc , sGW.x , sGW.y , sGW.w , sGW.h , hBuffer , 0 , 0 , SRCCOPY);
		EndPaint(hWnd , &ps);
		return 0;
	}
	return DefWindowProc(hWnd , msg , wp , lp);
}

//  The specified string is displayed in MEMO window　ehich is standard output for MLIB.
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

	//Printf()関数があるため特に使宇必要なし
	//メモウインドウに書式付文字表示を行う。使用例はprintf文と同じ。
	//使用変数は整数型と実数型が表記できる。
	//変数を表示する場合はそれぞれ%dと%gで表示位置を指定し、
	//文字列の後ろにコンマで変数名を記述する。改行制御文字は‘\\n’
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

	LN=lstrlen(lp);				//引数の文字数
	for(i=0;i<LN;i++){			//文字数分ループ
		dum=lstrcpyn(lp0,lp,2);
		pf0=lstrcmp(lp0,TEXT("%"));		//"%"のチェック
		 if(pf0==0){					//"%"発見した場合
			 dum=lstrcpyn(lp1,lp+1,2);
			pf1=lstrcmp(lp1,TEXT("d"));		//次の文字が"d"かどうかチェック
			pf2=lstrcmp(lp1,TEXT("g"));		//次の文字が"f"かどうかチェック

			if(pf1==0){
									//"%d"の数インクリメント
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
									//"%d"の数インクリメント
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
	ef0=lstrcmp(lp0,TEXT("\n"));		//"\n"のチェック

	if(ef0==0){							//"\"発見した場合
		retflug=1;	
	}
	return retflug;
}


	//メモウインドウにTCHAR型の文字配列messの内容を表示する。
	//crflug=0 以外のとき改行する。
void inputbuf(TCHAR *mess,int crflug){	

	int ml;		//入力文の文字数
	int ml0;	//現在行の文字数
	TCHAR mes0[BUFSIZE_W];	//現在行の文字
	TCHAR dummy[BUFSIZE_W];  //ダミーバッファ
	LPTSTR dum;

	lstrcpy(mes0,MemoBuf[ivVLine]);
	ml0=lstrlen(mes0);
	ml=lstrlen(mess);

	if (ml0+ml>BUFSIZE_W-1){		//水平文字数制限の処理.制限以上は書き込めない
		dum=lstrcpyn(dummy,mess,BUFSIZE_W-ml0);	
		lstrcat(MemoBuf[ivVLine],dummy);	// バッファに入力
	}
	else{
	   lstrcat(MemoBuf[ivVLine],mess);	// バッファに入力
	}

	if (crflug!=0) {				// 改行フラグの処理　0:改行なし 　0以外:改行

		iVLine++;					//現在行位置をインクリメント
		ivVLine=iVLine%BUFSIZE_H;			//余り考慮

		if (iVLine>DISPSIZE_H-1) {		//現在行がウインドウ幅を超えたとき
			iVLine0=iVLine-DISPSIZE_H+1;				//表示位置をインクリメント
			lstrcpy(MemoBuf[ivVLine],TEXT(""));
		
			scr.cbSize = sizeof(SCROLLINFO);
			scr.fMask = SIF_PAGE | SIF_RANGE  ;

			if(iVLine==ivVLine){		//現在行が表示制限行内のとき
				scr.nMin = DISPSIZE_H-1;
			    scr.nMax = iVLine;
			}
			else{					//現在行が表示制限を超えたとき
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
	bufprint();						// バッファの現在ウインドウへの表示
}

void bufprint(){
	int i,ii;
	TCHAR dummy[BUFSIZE_W*DISPSIZE_H]=TEXT("");		//ダミー文字列
	

	for(i=iVLine0;i<iVLine0+DISPSIZE_H;i++){		//表示行の先頭からループ
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

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//ペンの指定
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);		//新たなペンの選択と古いペンの保存

	MoveToEx(hBuffer , x1 , y1 , NULL);	
	LineTo(hBuffer ,x2,y2);				//直線の描画
	SelectObject(hBuffer , hpen_old);	//もとのペンに戻す
	DeleteObject(hpen);					//ペンの指定解除

	InvalidateRect(hWnd , &d , FALSE);	//システム描画命令のディスパッチ
}


	//グラフィックウインドウに四角形を描く、色、線の種類はPlot_pen()で指定
	//	X1,y1は左上の座標、x2,y2は右下の座標
	//	bfflug=0  		枠のみ。枠内は描画しない。
	//	bfflug=1  		枠と枠内をPlot_pen()で指定した色で塗りつぶす
	//	bfflug=それ以外  	枠と枠内を白で塗りつぶす
void Rect(int x1,int y1,int x2,int y2,int bfflug){

	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;
	HGDIOBJ hbrush,hbrush_old;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//ペンの指定
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);		//新たなペンの選択と古いペンの保存

	if (bfflug== FILL_OFF) hbrush=GetStockObject(NULL_BRUSH);		//ブラシの指定
	else if(bfflug== FILL_ON) hbrush=CreateSolidBrush(PenColor);
	else hbrush=GetStockObject(WHITE_BRUSH);

	hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);

	Rectangle(hBuffer,x1,y1,x2, y2);		//四角の描画

	SelectObject(hBuffer , hpen_old);		//もとのペンに戻す
	DeleteObject(hpen);						//ペンの指定解除

	SelectObject(hBuffer , hbrush_old);		//もとのブラシに戻す
	DeleteObject(hbrush);					//ブラシの指定解除

	InvalidateRect(hWnd , &d , FALSE);		//システム描画命令のディスパッチ
}


	//グラフィックウインドウに楕円を描く、色、線の種類はPlot_pen()で指定
	//	X1,y1は左上の座標、x2,y2は右下の座標を指定し、その四角形に接する楕円を描く。
	//	bfflug=0  枠のみ枠内は描画しない。
	//	bfflug=1  枠内をPlot_pen()で指定した色で塗りつぶす
	//	bfflug=それ以外  枠のみを白で塗りつぶす
void Circle(int x1,int y1,int x2,int y2,int bfflug)/* Draw circle */{

	RECT d={sGW.x , sGW.y , sGW.x+sGW.w , sGW.y+sGW.h};
	HPEN hpen,hpen_old;
	HGDIOBJ hbrush,hbrush_old;

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//ペンの指定
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);		//新たなペンの選択と古いペンの保存

	if (bfflug== FILL_OFF) hbrush=GetStockObject(NULL_BRUSH);    //ブラシの指定
	else if(bfflug== FILL_ON) hbrush=CreateSolidBrush(PenColor);
	else hbrush=GetStockObject(WHITE_BRUSH);

	hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//新たなブラシの選択と古いブラシの保存

	Ellipse(hBuffer,x1,y1,x2, y2);			//楕円の描画

	SelectObject(hBuffer , hpen_old);		//もとのペンに戻す
	DeleteObject(hpen);						//ペンの指定解除

	SelectObject(hBuffer , hbrush_old);		//もとのブラシに戻す
	DeleteObject(hbrush);					//ブラシの指定解除

	InvalidateRect(hWnd , &d , FALSE);		//システム描画命令のディスパッチ
}


	//グラフィックウインドウに描画する色を指定する。
	//pf: 0-実線　1-破線  2-点線　3-１点鎖線　4-２点鎖線  5-描画しない
	//pw: ペンの太さをピクセル単位で指定。 0は１ピクセル
	//pc: 0-黒　1-赤   2-緑   3-青   4-黄色    5-マゼンダ    6-シアン   7-白   
	//8以上を指定すればPlot_Penを呼び出す毎に自動的に色を0～6まで巡回させる。
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
				MessageBox(hWnd, TEXT("Plot_Pen関数の第１引数の指定が範囲を超えています．"), TEXT("Mlibによる警告"),MB_ICONHAND);
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
				PenColor=RGB(0,0,0);		//黒
				break;
			case 1:
				PenColor=RGB(0xff,0,0);		//赤
				break;
			case 2:
				PenColor=RGB(0,0xff,0);		//緑
				break;
			case 3:
				PenColor=RGB(0,0,0xff);		//青
				break;
			case 4:
				PenColor=RGB(0xff,0xff,0);	//黄色
				break;
			case 5:
				PenColor=RGB(0,0xff,0xff);	//マゼンダ
				break;
			case 6:
				PenColor=RGB(0xff,0,0xff);	//シアン
				break;
			case 7:
				PenColor=RGB(0xff,0xff,0xff);//白
				break;
		}
	}

	//フィギュアウインドウの消去。
	//	clflug=-1		指定したフィギュアウインドウの枠だけ描画
	//	clflug=0		指定したフィギュアウインドウの枠を描画し、枠内を消去
	//	clflug=1		指定したフィギュアウインドウをラベルも含めて消去
	//	clflug=2		グラフィックウインドウを全て消去
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
		MessageBox(hWnd, TEXT("Clf関数の引数の指定が範囲を超えています．"), TEXT("Mlibによる警告"),MB_ICONHAND);
		return;
	}

	if(clflug<1){			//	clflug=-1		指定したフィギュアウインドウの枠だけ描画
							//	clflug=0		指定したフィギュアウインドウの枠を描画し、枠内を消去
		hpen = CreatePen(0 , 0 , RGB(0,0,0));			//黒い実線のペンの指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//新たなペンの選択と古いペンの保存

		if(clflug== CLEAR_INSIDE){		//枠内に白いブラシを指定

			hbrush=(HBRUSH)GetStockObject(WHITE_BRUSH);				
			sFW[iID_Cfw].pn=0;	

		} else {			//枠内に透明のブラシを指定

			hbrush=(HBRUSH)GetStockObject(NULL_BRUSH);
		}			
		hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//新たなブラシの選択と古いブラシの保存
		Rectangle(hBuffer,figwin_X,figwin_Y,figwin_X+figwin_W, figwin_Y+figwin_H);	//枠の描画

		SelectObject(hBuffer, hpen_old);		//もとのペンに戻す
		DeleteObject(hpen);						//ペンの指定解除

		SelectObject(hBuffer, hbrush_old);		//もとのブラシに戻す
		DeleteObject(hbrush);					//ブラシの指定解除

	} else if(clflug== CLEAR_FIG){	//	clflug=1		指定したフィギュアウインドウをラベルも含めて消去

		hpen = CreatePen(0 , 0 , RGB(0xff,0xff,0xff));	//白い実線のペンの指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//新たなペンの選択と古いペンの保存

		hbrush=CreateSolidBrush(RGB(0xff,0xff,0xff));		//枠内に白いブラシを指定
		hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//新たなブラシの選択と古いブラシの保存
	
		Rectangle(hBuffer,figwin_X-MERGIN_L,figwin_Y-MERGIN_T,figwin_X+figwin_W+MERGIN_R,figwin_Y+figwin_H+MERGIN_B);

		//指定したフィギュアウインドウ情報の初期化
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

		SelectObject(hBuffer, hpen_old);		//もとのペンに戻す
		DeleteObject(hpen);						//ペンの指定解除

		SelectObject(hBuffer, hbrush_old);		//もとのブラシに戻す
		DeleteObject(hbrush);					//ブラシの指定解除

	} else if(clflug== CLEAR_ALL){	//	clflug=2		グラフィックウインドウを全て消去

		hpen = CreatePen(0 , 0 , RGB(0xff,0xff,0xff));	//白いペンの指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//新たなペンの選択と古いペンの保存

		hbrush=CreateSolidBrush(RGB(0xff,0xff,0xff));		//白いブラシの指定 
		hbrush_old=(HBRUSH)SelectObject(hBuffer , hbrush);	//新たなブラシの選択と古いブラシの保存
	
		Rectangle(hBuffer,0,0,sGW.w, sGW.h);		//フィギュアウインドウに白塗りの四角を描画

		//グラフィックウインドウ情報の全消去
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
		SelectObject(hBuffer, hpen_old);		//もとのペンに戻す
		DeleteObject(hpen);						//ペンの指定解除

		SelectObject(hBuffer, hbrush_old);		//もとのブラシに戻す
		DeleteObject(hbrush);					//ブラシの指定解除
	}
	InvalidateRect(hWnd , &d , FALSE);		//システム描画命令のディスパッチ
}


	//図にグリッドラインを描画する。数値ラベルの値のある座標に直線を引く
	//軸の最大最小を決めた（Plot関数、Axis_ycap, Axis_xcap）後に指定する。
	//	grflug: 0のときｙ軸の0レベルのみを引く。
	//			1のとき数値ラベルの座標にｙ軸にグリッドラインを引く。
	//			2のとき数値ラベルの座標にｘ軸にグリッドラインを引く。
	//			3のとき数値ラベルの座標にｘ軸、ｙ軸にグリッドラインを引く。
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

	if (sFW[iID_Cfw].N>0){	//フィギュアウインドウに図が描画されているかどうかチェック
			
		//グローバル変数から指定フィギュアウインドウのｘ軸ｙ軸の最大最小情報取得
		ymax=sFW[iID_Cfw].ymax;	
		xmax=sFW[iID_Cfw].xmax;
		ymin=sFW[iID_Cfw].ymin;	
		xmin=sFW[iID_Cfw].xmin;

		if (grflug== ZERO_LINE){	//ゼロライン描画オン
			nx=0;
			ny=1;
			lx[0]=0;
			ly[0]=0;
		} 
		
		if ((grflug== YGRID_LINE)|(grflug== XYGRID_LINE)){	//グリッドライン描画オン

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

		hpen = CreatePen(PS_DOT , 0 , RGB(0,0,0));		//黒い点線のペンの指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//新たなペンの選択と古いペンの保存
		SetBkMode(hBuffer , TRANSPARENT);

		for(j=0;j<ny;j++){		//横のグリッド表示
			x=figwin_X;
			y=figwin_Y+(int)((ymax-ly[j])*((double)figwin_H-1)/(ymax-ymin)+.5);
			MoveToEx(hBuffer ,x , y , NULL);
			x=figwin_X+figwin_W-1;
			y=figwin_Y+(int)((ymax-ly[j])*((double)figwin_H-1)/(ymax-ymin)+.5);
			LineTo(hBuffer ,x,y);
		}

		for(j=0;j<nx;j++){		//縦のグリッド表示

			x=figwin_X+(int)((lx[j]-xmin)*((double)figwin_W-1)/(xmax-xmin)+.5);
			y=figwin_Y;

			MoveToEx(hBuffer , x ,y , NULL);

			x=figwin_X+(int)((lx[j]-xmin)*((double)figwin_W-1)/(xmax-xmin)+.5);
			y=figwin_Y+figwin_H-1;

			LineTo(hBuffer ,x,y);
		}
		SetBkMode(hBuffer , OPAQUE);

		SelectObject(hBuffer , hpen_old);	//もとのペンに戻す
		DeleteObject(hpen);					//ペンの指定解除
		InvalidateRect(hWnd , &d , FALSE);	//システム描画命令のディスパッチ
	}
}


	//グラフィックウインドウにフィギュアウインドウを作成し、
	//以後のPlot1d(…)等の描画は指定したウインドウに描かれる。
	//一旦、指定したウインドウは黒枠のみが描かれる。
	//	i1: ウインドウの横方向の数
	//	i2:ウインドウの縦方向の数
	//	n:指定するウインドウの番号、左上を１番とし右に数えて行く
	//Set_figure(…)を行った順番にフィギュアIDが割り当てられる。
	//現在のフィギュアIDはglobal変数のiID_Cfwに入っている。
	//初めて指定したときはフィギュアウインドウの最大最小値がクリアされる。
	//二回目以降に指定したときは前に指定した値と同じフィギュアウインドウの
	//設定値が用いられるため、最大値最小値の値は記憶されている。
	//1回指定すれば際指定する必要はない。
	//一方、一度指定したフィギュアウインドウに違う軸を持つ図を描画する場合は
	//Clf(1)で一旦図を消去して、再指定する必要がある。
int Set_figure(int i1,int i2,int n){
	int figwin_X;
	int figwin_Y;
	int figwin_W;
	int figwin_H;	
	int i;

	if ((i1>0)&(i2>0)){

		if ((n>0)&(n<i1*i2+1)) {			//i1 i2 nの設定値の妥当性チェック
			
			for (i=0;i<=iNum_fw;i++){	
				//指定フィギュアウインドウがすでに設定済みかどうか確認
				if ((sFW[i].wn==i2)&(sFW[i].hn==i1)&(sFW[i].nn==n)){
					iID_Cfw=i;			//指定フィギュアウインドウをカレントウインドウに設定
					Clf(-1);				//フィギュアウインドウの枠のみ描画
					return i;				//戻る
				}
			}

			//指定フィギュアウインドウが新規フィギュアウインドウの場合
			iNum_fw=iNum_fw+1;	//既存のウインドウＩＤ最大値をインクリメント
 			iID_Cfw=iNum_fw;		//新規フィギュアウインドウをカレントウインドウに

			//ウインドウの左上座標，高さ，幅の設定
			figwin_W=(sGW.w/i2)-(MERGIN_L+MERGIN_R)+1;
			figwin_H=(sGW.h/i1)-(MERGIN_T+MERGIN_B)+1;

			figwin_X=(sGW.w/i2)*((n-1)%i2)+MERGIN_L;
			figwin_Y=(sGW.h/i1)*((n-1)/i2)+MERGIN_T;

			sFW[iID_Cfw].xwin=figwin_X;
			sFW[iID_Cfw].ywin=figwin_Y;
			sFW[iID_Cfw].wwin=figwin_W;
			sFW[iID_Cfw].hwin=figwin_H; 

			Clf(0);		//フィギュアウインドウの枠内消去

			//フィギュアウインドウのウインドウ位置情報
			sFW[iID_Cfw].wn=i2;
			sFW[iID_Cfw].hn=i1;
			sFW[iID_Cfw].nn=n;

			//フィギュアウインドウの情報初期化
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

			
		} else {MessageBox(hWnd, TEXT("フィギュアウインドウの指定が範囲を超えています．"), TEXT("Mlibによる警告"),MB_ICONHAND);}
	} else {MessageBox(hWnd, TEXT("フィギュアウインドウの数が負の値です．"), TEXT("Mlibによる警告"),MB_ICONHAND);}
return iID_Cfw;
}

	//ｘ軸の最小、最大設定、数値ラベル、キャプションを表示する。
	//min: ｘ軸の最小値
	//max: ｘ軸の最大値
	//label: ｘ軸キャプションの文字列（100文字以内）の先頭アドレス
	//数値ラベルはminからmaxの間の適当な数値を自動的に計算して描画する。
	//min=max=0は設定できない。Plot関数等の前後で指定可能
	//Plot1d()関数ではx軸のラベルのみ書かれ、軸の表示範囲は変わらない
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

	if ((max*max+min*min)>1e-20){  //最大最小が0でないのとき
		
		auto_label(min,max,&st,&en,&in);	//数値ラベルの取得

		sFW[iID_Cfw].xmin=min;	//グローバル変数へのフィギュアウインドウｘ軸最小値の書き込み
		sFW[iID_Cfw].xmax=max;	//グローバル変数へのフィギュアウインドウｘ軸最大値の書き込み
	
		nobm=0;
		hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//黒い実線のペンを指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//ペンの設定を行い，古いペン情報をhpen_oldに

		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// フォントの回転設定
		hFont = CreateFontIndirect( &DefFont );				// 論理フォントを作成する
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//論理フォントを新たに設定し古いフォントを保存

		GetTextMetrics(hBuffer , &tm);	//フォントサイズ情報等取得のための設定

		for(am=st;am<=max;am=am+in){
			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);				//数値ラベルに使う実数値をワイド文字に変換
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );	//数値ラベルの文字数をnobに取得
			nob--;
			if(nob>nobm){nobm=nob;}			//数値ラベルの文字数の最大値をnobmに取得
		}

		// 数値ラベルの間隔が数値ラベルの文字幅より大きいときの処理
		if (((double)cap_W*in/(max-min))<(((double)nobm+1)*tm.tmAveCharWidth)) {

			in=in*2;		//数値ラベルの間隔を二倍に設定	

			if (fabs(st)>1e-10){  //数値ラベルに0があれば0を通るように調整
				char n1[BUFNMAX+1],n2[BUFNMAX+1];
				sprintf_s(n1,BUFNMAX,"%g",st);
				sprintf_s(n2,BUFNMAX,"%g",st+in/2);

				if ((strlen(n1)>strlen(n2))&(fmod(fabs(st+in/2),in)<1e-10)){	
					st=st+in/2;
				}
			}
		}

		for(am=st;am<=max;am=am+in){	//数値ラベルの数だけループ

			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );
			nob--;

			x=cap_X+(int)(((double)cap_W-1)*(am-min)/(max-min)+.5);
			y=cap_Y;

			TextOut(hBuffer, x-(int)((double)nob*tm.tmAveCharWidth/2.), y+(int)(tm.tmHeight/6.), b, (int)nob);//数値ラベルの描画
	
    		MoveToEx(hBuffer , x , cap_Y-1 , NULL);	//目盛り位置の設定
			LineTo(hBuffer ,x , cap_Y-5);			//目盛りの描画
		}

		SelectObject(hBuffer , hFont_old);		//元のフォントに戻す
		DeleteObject( hFont );					//作成した論理フォントを削除する

		SelectObject(hBuffer , hpen_old);		//もとのペンに戻す
		DeleteObject(hpen);						//ペンの指定解除

		sFW[iID_Cfw].xs=st;	//グローバル変数へのフィギュアウインドウの目盛り最小値の書き込み
		sFW[iID_Cfw].xe=en;	//グローバル変数へのフィギュアウインドウの目盛り最大値の書き込み
		sFW[iID_Cfw].xd=in;	//グローバル変数へのフィギュアウインドウの目盛り間隔の書き込み
	}

	Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// フォントの回転設定
	hFont = CreateFontIndirect( &DefFont );				// 論理フォントを作成する
	hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//論理フォントを新たに設定し古いフォントを保存

	GetTextMetrics(hBuffer , &tm);	//フォントサイズ情報等取得のための設定

	wsprintf(Label,L"%S",label);
	ms=lstrlen(Label);	//キャプションの文字数
	x=cap_X;
	y=cap_Y;
	TextOut(hBuffer, x-(int)(ms/2.*tm.tmAveCharWidth-cap_W/2.), y+(int)(7*(double)tm.tmHeight/6.), Label, ms);//キャプションの描画
	strcpy_s(sFW[iID_Cfw].xlabel,ms+1,label);		//Ｘ軸キャプションを設定

	SelectObject(hBuffer , hFont_old);		//元のフォントに戻す
	DeleteObject( hFont );					//作成した論理フォントを削除する

	InvalidateRect(hWnd , &d , FALSE);	//システム描画命令のディスパッチ
}

	//ｙ軸の最小、最大設定、数値ラベル、キャプションを表示する。
	//min, max : ｙ軸の最小値、最大値
	//label: y軸キャプションの文字列（100文字以内）の先頭アドレス
	//数値ラベルはminからmaxの間の適当な数値を自動的に計算して描画する。
	//軸スケールがあらかじめ決まっているときはPlot1d()等の関数より先に呼び出す。
	//未定のときはmin=max=0を指定すれば、キャプションのみを描画する。
	//このときはどこで呼び出しても良い。min=max=0のとき、Plot1d等により
	//ｙ軸は自動的に作成される。
	//数値ラベル幅が長いとき、キャプションがウインドウ枠を飛び出すことがある。
	//このときはdef.h中のMERGIN_Lを大きくするとよい。
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

	if ((max*max+min*min)>1e-20){	//最大最小が0以外のとき

		auto_label(min,max,&st,&en,&in);	//数値ラベルの取得

		sFW[iID_Cfw].ymin=min;	//グローバル変数へのフィギュアウインドウｙ軸最小値の書き込み
		sFW[iID_Cfw].ymax=max;	//グローバル変数へのフィギュアウインドウｙ軸最大値の書き込み
	
		hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//黒い実線のペンを指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//ペンの設定を行い，古いペン情報をhpen_oldに

		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// フォントの回転設定
		hFont = CreateFontIndirect( &DefFont );				// 論理フォントを作成する
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//論理フォントを新たに設定し古いフォントを保存

		GetTextMetrics(hBuffer , &tm);	//フォントサイズ情報等取得のための設定
	
		// 数値ラベルの高さが数値ラベルの文字幅より大きいときの処理
		if (((double)cap_H*in/(max-min))<5*(double)tm.tmHeight/4.) {
			
			in=in*2;		//数値ラベルの間隔を二倍に設定

			if (fabs(st)>1e-10){  //数値ラベルに0があれば0を通るように調整
				char n1[BUFNMAX+1],n2[BUFNMAX+1];
				sprintf_s(n1,BUFNMAX,"%g",st);
				sprintf_s(n2,BUFNMAX,"%g",st+in/2);
				if ((strlen(n1)>strlen(n2))&(fmod(fabs(st+in/2),in)<1e-10)){	
					st=st+in/2;
				}
			}
		}

		for(am=st;am<=max;am=am+in){	//数値ラベルの数だけループ
			if (am*am<1e-20) am=0; 
			sprintf_s(a,BUFNMAX,"%g",am);
			mbstowcs_s(&nob, b, BUFNMAX, a, BUFNMAX );
			nob--;
			x=cap_X;
			y=cap_Y+(int)(((double)cap_H-1)*(max-am)/(max-min)+.5);

			TextOut(hBuffer, x-(int)((nob+0.5)*tm.tmAveCharWidth)-4, y-(int)(tm.tmHeight/2.), b, (int)nob);	//数値ラベルの描画
    		MoveToEx(hBuffer , cap_X, y  , NULL);	//目盛り位置の設定
			LineTo(hBuffer , cap_X+5,y ); 			//目盛りの描画			

			if (nob>nobmax){nobmax=nob;}			//ｙ軸数値ラベルの文字数の最大値をnobmに取得
		}

		SelectObject(hBuffer , hFont_old);		//元のフォントに戻す
		DeleteObject( hFont );					//作成した論理フォントを削除する

		SelectObject(hBuffer , hpen_old);	//もとのペンに戻す
		DeleteObject(hpen);					//ペンの指定解除

		sFW[iID_Cfw].nobm=nobmax;	//グローバル変数へのフィギュアウインドウのｙ軸数値ラベル文字数の最大値書き込み

		sFW[iID_Cfw].ys=st;	//グローバル変数へのフィギュアウインドウの目盛り最小値の書き込み
		sFW[iID_Cfw].ye=en;	//グローバル変数へのフィギュアウインドウの目盛り最大値の書き込み
		sFW[iID_Cfw].yd=in;	//グローバル変数へのフィギュアウインドウの目盛り間隔の書き込み
	} 

	if(sFW[iID_Cfw].nobm==0){				//ｙ軸の数値ラベルが設定されていないとき
		ms=strlen(label);
		strcpy_s(sFW[iID_Cfw].ylabel,ms+1,label);			//ｙ軸キャプションをグローバル変数に設定

	} else {							//ｙ軸の数値ラベルが設定されているとき
		wsprintf(Label,L"%S",label);

		Font_info(Used_Font,Used_Font_Size,90,Italic_Font_Flug);			// フォントの回転設定
		hFont = CreateFontIndirect( &DefFont );				// 論理フォントを作成する
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//論理フォントを新たに設定し古いフォントを保存

		GetTextMetrics(hBuffer , &tm);	//フォントサイズ情報等取得のための設定

		ms=lstrlen(Label);	//キャプションの文字数
		x=cap_X;
		y=cap_Y;
		//キャプションの描画
		TextOut(hBuffer, x-(int)((sFW[iID_Cfw].nobm+0.5)*tm.tmAveCharWidth+5.*(double)tm.tmHeight/4.)-4,
			y+(int)(cap_H/2.+(ms/2.*tm.tmAveCharWidth)), Label, (int)ms);

		SelectObject(hBuffer , hFont_old);			//元のフォントに戻す
		DeleteObject( hFont );						//作成した論理フォントを削除する
		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);	// フォントの回転設定解除
		
	}
	InvalidateRect(hWnd , &d , FALSE);		//システム描画命令のディスパッチ
}

	//Paste the string specified by argument ‘text’ in the figure window.
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
	double ymin=sFW[iID_Cfw].ymin;	//グローバル変数へのフィギュアウインドウｙ軸最小値の書き込み
	double ymax=sFW[iID_Cfw].ymax;
	double xmin=sFW[iID_Cfw].xmin;	//グローバル変数へのフィギュアウインドウｙ軸最小値の書き込み
	double xmax=sFW[iID_Cfw].xmax;

	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)
		+(sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)>1e-20){

		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// フォントの回転設定
		hFont = CreateFontIndirect( &DefFont );				// 論理フォントを作成する
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//論理フォントを新たに設定し古いフォントを保存

		x=figwin_X+(int)((xn-xmin)*(figwin_W-1.)/(xmax-xmin)+.5);
		y=figwin_Y+(int)((ymax-yn)*(figwin_H-1.)/(ymax-ymin)+.5);

		n=strlen(buf)+1;
		buf0=(TCHAR*)malloc(n*sizeof(TCHAR));

		ret=MultiByteToWideChar(0,0,buf,-1, buf0,(int)n);

		n=lstrlen(buf0);
		TextOut(hBuffer,x,y,buf0,(int)n);

		SelectObject(hBuffer , hFont_old);			//元のフォントに戻す
		DeleteObject( hFont );						//作成した論理フォントを削除する

		InvalidateRect(hWnd , &d , FALSE);
		free(buf0);
	}
}

	//指定されているフィギュアウインドウにint型配列ynの数値n点をグラフ化。
	//	色、線の種類はPlot_pen()で指定。Axis_ycap(…)で軸の最大最小が指定
	//	Set_Figure()関数であらかじめフィギュアウインドウが指定されていないといけない
	//	されていないときは、自動的に配列内の最大値最小値を探しy軸を設定、描画する。
	//		yn:表示すり配列の先頭アドレス(int 型)
	//		n: 表示する配列の最大要素
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

	//フィギュアウインドウの最大最小が０に設定されているとき
	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<n;i++){		//最大値，最小値を自動的に探す
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}
		//グローバル変数にフィギュアウインドウの最大最小を書き込む
		sFW[iID_Cfw].ymin=mi;
		sFW[iID_Cfw].ymax=ma;
		
		Axis_ycap(mi,ma,sFW[iID_Cfw].ylabel);		//y軸の数値ラベル、キャプション描画
	}
	if ((sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)<1e-20){
		double st,en,in;

		sFW[iID_Cfw].xmin=(double)0;
		sFW[iID_Cfw].xmax=((double)n-1);

		auto_label(sFW[iID_Cfw].xmin,sFW[iID_Cfw].xmax,&st,&en,&in);
		sFW[iID_Cfw].xs=st;	//グローバル変数へのフィギュアウインドウの目盛り最小値の書き込み
		sFW[iID_Cfw].xe=en;	//グローバル変数へのフィギュアウインドウの目盛り最大値の書き込み
		sFW[iID_Cfw].xd=in;	//グローバル変数へのフィギュアウインドウの目盛り間隔の書き込み
	} 

	//グローバル変数から以前に指定した最大最小を読み込む
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

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//ペンの作成
	hpenull=(HPEN)GetStockObject(NULL_PEN);				//ヌルペンの作成

	if((iyy>=it)&(iyy<=ib)){		//初期ペンの指定
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

	sFW[iID_Cfw].N=n;		//図に表示したポイント数
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

//指定されているフィギュアウインドウにdouble型配列ynの数値n点をグラフ化。
//	色、線の種類はPlot_pen()で指定。Axis_ycap(…)で軸の最大最小が指定
//	Set_Figure()関数であらかじめフィギュアウインドウが指定されていないといけない
//	されていないときは、自動的に配列内の最大値最小値を探しy軸を設定、描画する。
//		yn:表示すり配列の先頭アドレス(double 型)
//		n: 表示する配列の最大要素
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

	//フィギュアウインドウの最大最小が０に設定されているとき
	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<n;i++){		//最大値，最小値を自動的に探す
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}
		//グローバル変数にフィギュアウインドウの最大最小を書き込む
		sFW[iID_Cfw].ymin=mi;
		sFW[iID_Cfw].ymax=ma;
		
		Axis_ycap(mi,ma,sFW[iID_Cfw].ylabel);		//y軸の数値ラベル、キャプション描画
	}
	if ((sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)<1e-20){
		double st,en,in;

		sFW[iID_Cfw].xmin=(double)0;
		sFW[iID_Cfw].xmax=(double)n-1;

		auto_label(sFW[iID_Cfw].xmin,sFW[iID_Cfw].xmax,&st,&en,&in);
		sFW[iID_Cfw].xs=st;	//グローバル変数へのフィギュアウインドウの目盛り最小値の書き込み
		sFW[iID_Cfw].xe=en;	//グローバル変数へのフィギュアウインドウの目盛り最大値の書き込み
		sFW[iID_Cfw].xd=in;	//グローバル変数へのフィギュアウインドウの目盛り間隔の書き込み
	} 

	//グローバル変数から以前に指定した最大最小を読み込む
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

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//ペンの作成
	hpenull=(HPEN)GetStockObject(NULL_PEN);				//ヌルペンの作成

	if((iyy>=it)&(iyy<=ib)){		//初期ペンの指定
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
	sFW[iID_Cfw].N=n;		//図に表示したポイント数

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

	//指定されているフィギュアウインドウにdouble型配列xnをｘ軸,ynをｙ軸に対応させたグラフを描画。
	//	色、線の種類はPlot_pen()で指定。
	//	あらかじめAxis_ycap(…)、Axis_xcap(…)でy軸、x軸の表示範囲、軸ラベルが指定可能
	//	されていないときは、自動的に配列内の最大値最小値を探しy軸を設定、描画する。
	//		xn,yn:double型の配列
	//		n: 表示する配列の最大要素
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

	//フィギュアウインドウの最大最小が０に設定されているとき
	if ((sFW[iID_Cfw].ymin*sFW[iID_Cfw].ymin+sFW[iID_Cfw].ymax*sFW[iID_Cfw].ymax)<1e-20){
		double ma=yn[0];
		double mi=yn[0];

		for(i=1;i<n;i++){		//y軸の最大値，最小値を自動的に探す
			if (yn[i]>ma) {ma=yn[i];}
			if (yn[i]<mi) {mi=yn[i];}
		}

		//グローバル変数にフィギュアウインドウの最大最小を書き込む
		sFW[iID_Cfw].ymin=mi;
		sFW[iID_Cfw].ymax=ma;
		
		Axis_ycap(mi,ma,sFW[iID_Cfw].ylabel);		//y軸の数値ラベル、キャプション描画
	}

	if ((sFW[iID_Cfw].xmin*sFW[iID_Cfw].xmin+sFW[iID_Cfw].xmax*sFW[iID_Cfw].xmax)<1e-20){
		double ma=xn[0];
		double mi=xn[0];

		for(i=1;i<n;i++){		//ｘ軸の最大値，最小値を自動的に探す
			if (xn[i]>ma) {ma=xn[i];}
			if (xn[i]<mi) {mi=xn[i];}
		}
		sFW[iID_Cfw].xmin=mi;
		sFW[iID_Cfw].xmax=ma;
		Axis_xcap(mi,ma,sFW[iID_Cfw].xlabel);		//x軸の数値ラベル、キャプション描画
	} 

	//グローバル変数から以前に指定した最大最小を読み込む
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

	hpen = CreatePen(PenStyle , PenWidth , PenColor);	//ペンの作成
	hpenull=(HPEN)GetStockObject(NULL_PEN);				//ヌルペンの作成

	if(((iyy>=it)&(iyy<=ib))){		//初期ペンの指定
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

	sFW[iID_Cfw].N=n;		//図に表示したポイント数

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


/*	指定されているフィギュアウインドウにdouble型配列ynの2D画像を描画。
	配列ynは二次元データを1次元配列に並び替えたデータとして与える。x方向、ｙ方向のポイント数はnx,nyで与えられる。
	cmin,cmax: カラースケールの最小、最大値の指定,両方とも0のとき最大最小値を自動的に探す。
	plflug : カラーマップの指定。0：グレースケール、1：虹色、2：青、赤の循環色
	cbflug : 0：カラーバー表示off、1：カラーバー表示
	szflug : 0：画像サイズに関係なくフィギュアウインドウの規定サイズに拡大して描画
　　　　1：フィギュアウインドウのサイズを正方形にして描画
　　　　2：データのサイズに対応したピクセル数で描画（最もきれい）
	データの縦横サイズがウインドウサイズより大きいと画像が乱れるので注意

	0番目:x=0;y=0, 1番目:x=1;y=0, …	,nx番目:x=nx-1;y=0, nx+1番目:x=0;y=1, nx+2番目:x=1;y=1, … , Nx*ny-2番目:x=nx-2;y=nx-1, Nx*ny-1番目:x=nx-1;y=ny-1
	の順番で二次元データを配列ynに格納する。
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

	//カラーバーフラグ，サイズフラグのチェック

	if(cbflug== LEGEND_ON){			//カラーバーを表示
		Clf(CLEAR_FIG);										//フィギュアウインドウを消去し、
		figwin_W=sGW.w/sFW[iID_Cfw].wn-(MERGIN_L+MERGIN_R);	//新たなウインドウサイズを決定
		figwin_W=(int)(figwin_W*0.85);
	} else{
		if ((szflug== SIZE_SQUARE)|(szflug == SIZE_DATA)){		//カラーバー未表示
			Clf(CLEAR_FIG);	//フィギュアウインドウを消去する
		}
	}

	if (szflug== SIZE_SQUARE){			//描画サイズが正方形のとき
		if(figwin_W>figwin_H){
			figwin_W=figwin_H;		//横が広いとき幅を狭める
		} else {
			figwin_H=figwin_W;		//縦が長いときを高さを縮める
		}
	} else if (szflug== SIZE_DATA){	//描画サイズがデータサイズのとき
		figwin_W=nx+1;
		figwin_H=ny+1;
	} 
	
	sFW[iID_Cfw].wwin=figwin_W+1;	//グローバル変数にサイズを登録し、
	sFW[iID_Cfw].hwin=figwin_H+1;
	Clf(-1);					//画面消去

	//カラースケールの最小，最大値ともに０のとき自動的に最大最小値を探す．

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
	MessageBox(hWnd, TEXT("データのサイズがフィギュアウインドウのサイズより大きいため画像が乱れます"),TEXT("Mlibによる警告"),MB_ICONHAND);
	}

	colormap(plflug,pc);	//カラーマップの取得

	//２Ｄ画像の表示
	for(i=0;i<nx;i++){
		px=figwin_X+i+1;

		for(j=0;j<ny;j++){
			py=figwin_Y+figwin_H-j-1;

			c=(yn[j*nx+i]-cmin)/(cmax-cmin);	//二次元データをカラーマップデータに対応させる
			if (c<0) {c=0;}
			if (c>1) {c=1;}
			cn=(int)(c*((double)PALLET_NUM-1)+.5);
			SetPixel(hBuffer,px,py,pc[cn]);  //カレントウインドウにデータサイズと同じピクセル範囲で表示
		}
	}

	//カレントウインドウの図を指定のサイズに引き伸ばす

	hdc = BeginPaint(hWnd , &ps);
	SetStretchBltMode(hdc , HALFTONE);
	StretchBlt(hBuffer , figwin_X+1 , figwin_Y+1 , figwin_W-1 , figwin_H-1 ,
		       hBuffer , figwin_X+1 , figwin_Y+1+figwin_H-ny-1,nx,ny , SRCCOPY);
	EndPaint(hWnd , &ps);

	////////////////////
	//カラーバーの表示//
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

		auto_label(cmin,cmax,&st,&en,&in);		//カラーラベルの取得

		//Plot2Dを使ってカラーバーを表示するため一時的にフィギュアウインドウを作成
		gg=iID_Cfw;
		iID_Cfw=FIGMAX-1;

		//カラーバーのサイズを決定
		sFW[iID_Cfw].wwin=(int)(sFW[gg].wwin/10.);		
		sFW[iID_Cfw].hwin=(int)(sFW[gg].hwin*0.8);
		sFW[iID_Cfw].xwin=(int)(sFW[gg].xwin+sFW[gg].wwin*1.03);
		sFW[iID_Cfw].ywin=(int)(sFW[gg].ywin+sFW[gg].hwin)-sFW[iID_Cfw].hwin;
	
		//l=(int)(sFW[gg].hwin/8.);	//	カラーバーのウインドウ幅
		l=2;

		if (sFW[iID_Cfw].hwin>PALLET_NUM){
			pn=PALLET_NUM-1;			
		} else {
			pn=(int)(8*(floor(sFW[iID_Cfw].hwin/8.)))-1;//	カラーバーの範囲を再指定
		}

		for (i=0;i<pn;i++){
			for(j=0;j<l;j++){
				c[i*l+j]=i*(((double)PALLET_NUM-1)/(pn-1.));    //カラーバーに使う二次元データの作成
			}
		}

		Plot2d(c,l,pn,0, (double)PALLET_NUM-1,plflug,LEGEND_OFF,0);		//Plot2D関数を使ったカラーバーの表示（再帰呼び出し）

		//カラーラベルの表示
		hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//黒い実線のペン指定
		hpen_old=(HPEN)SelectObject(hBuffer , hpen);

		Font_info(Used_Font,(long)(Used_Font_Size*0.85),0,Italic_Font_Flug);	// フォントサイズの縮小
		hFont = CreateFontIndirect( &DefFont );   // 論理フォントを作成する
		hFont_old=(HFONT)SelectObject( hBuffer, hFont );

		GetTextMetrics(hBuffer , &tm);

		if (((double)sFW[iID_Cfw].hwin*in/(cmax-cmin))<5*(double)tm.tmHeight/4.) {
			in=in*2;

			if (fabs(st)>1e-10){  //数値ラベルに0があれば0を通るように調整
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
		DeleteObject( hFont );   // 作成した論理フォントを削除する
		Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);	// フォントサイズの縮小解除

		SelectObject(hBuffer , hpen_old);
		DeleteObject(hpen);

		iID_Cfw=gg;  //カレントフィギュア番号を元に戻す
	}

	sFW[iID_Cfw].N=nx*ny;
	InvalidateRect(hWnd , &d , FALSE);
}

/*
	If you draw continuously by using Plot() function, it will be overwritten.
	Legend() function displays legends for the number of the overlaid graphs.
	The string of the legend should be written as “line1 | line2 | line3”.
	The name of each line is delimited the character ‘ | ’ in the string .
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

	hpen = CreatePen(PS_SOLID , 0 , RGB(0,0,0));	//黒い実線のペンを指定
	hpen_old=(HPEN)SelectObject(hBuffer , hpen);	//ペンの設定を行い，古いペン情報をhpen_oldに

	Font_info(Used_Font,Used_Font_Size,0,Italic_Font_Flug);			// フォントの回転設定
	hFont = CreateFontIndirect( &DefFont );				// 論理フォントを作成する
	hFont_old=(HFONT)SelectObject( hBuffer, hFont );	//論理フォントを新たに設定し古いフォントを保存

	GetTextMetrics(hBuffer , &tm);	//フォントサイズ情報等取得のための設定

	ll=(nobm+1)*tm.tmAveCharWidth;				//	凡例の文字の幅
	lm=tm.tmAveCharWidth;					//　凡例の左右上下マージン

	lw=lm*2+(int)(ll*2);					//　凡例の幅
	lh=(sFW[iID_Cfw].pn*tm.tmHeight+lm*2);  //  凡例の高さ

	if ((pos<0)|(pos>4)){
		pos=0;
		MessageBox(hWnd, TEXT("位置指定が間違っています．右下に表示します．"),TEXT("Mlibによる警告"),MB_ICONHAND);
	}

	switch (pos){		//	凡例の表示位置決定
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

		if ((iy>=it)&(iy<=ib)) {				//yが範囲内
			if ((iyy>=it)&(iyy<=ib)){			//yyが範囲内
				LineTo(hBuffer ,ix,iy);
			} else if (iyy<it){					//yyが上限より上
				SelectObject(hBuffer , hpen);
				MoveToEx(hBuffer ,(int)(xx+(top-yy)/(y-yy)*(x-xx)),it,NULL);
				LineTo(hBuffer ,ix,iy);
			} else if (iyy>ib){					//yyが下限より下
				SelectObject(hBuffer , hpen);
				MoveToEx(hBuffer ,(int)(xx+(btm-yy)/(y-yy)*(x-xx)),ib,NULL);
				LineTo(hBuffer ,ix,iy);
			} 
		} else if (iy<it){						//yが上限より上
			if (iyy<it){						//yyが上限より上
				LineTo(hBuffer ,ix,iy);
			} else {
				LineTo(hBuffer ,(int)(xx+(top-yy)/(y-yy)*(x-xx)),it);
				SelectObject(hBuffer , hpenull);
			}
		} else {								//yが下限より下
			if (iyy>ib){						//yyが下限より下
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

	//mlib内部関数
	//ymin,ymaxから数値ラベルの初期値、最終値、間隔を自動的に計算する
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
		figwin_W=fW;		//横が広いとき幅を狭める
	} else if (figwin_H>fH){
		figwin_Y=figwin_Y+(figwin_H-fH)/2;
		figwin_H=fH;		//縦が長いときを高さを縮める
	}

	sFW[iID_Cfw].wwin=figwin_W;
	sFW[iID_Cfw].hwin=figwin_H;
	sFW[iID_Cfw].xwin=figwin_X;
	sFW[iID_Cfw].ywin=figwin_Y;
					//フィギュアウインドウの枠内消去
	Clf(-1);
}


	//	グラフィックウインドウ全体をクリップボードにコピーする
void Fig2clipboard(){

	TCHAR buf[1024];
	HANDLE hdl;

	OpenClipboard(hWnd);
	EmptyClipboard();							//クリップボードをクリア
	hdl=SetClipboardData(CF_BITMAP, hBitmap);		//クリップボードに取り込む
	CloseClipboard();

	if(hdl==NULL){
		MessageBox(hWnd, TEXT("図のクリップボードへのコピーに失敗しました．"), TEXT("Mlibによる警告"),MB_ICONHAND);
	} else {
		wsprintf(buf, TEXT("図がクリップボードにコピーされました。"));
		MessageBox(hWnd, buf, TEXT("Mlibによる警告"), MB_ICONHAND);
	}
}

	//mlib内部関数
	//	Plot2Dで用いるカラーマップを配列pcに入れて戻す。Plot2Dから呼び出している。
	//	plflug=0	グレイスケール
	//	plflug=1	レインボーカラー
	//	plflug=2	黒-青-白-赤-黒の循環色（位相の表示などに便利）
void colormap(int plflug, COLORREF *pc){

	int i,p1,p2,p3,p4,p5;
	BYTE r,g,b,f;
	BYTE pc0[3*PALLET_NUM/2];

	if ((plflug<0)|(plflug>2)){
		plflug=1;
		MessageBox(hWnd, TEXT("カラーパレットの指定が範囲を超えています"),TEXT("Mlibによる警告"),MB_ICONHAND);
	}

	switch(plflug){
	case GRAY:		//グレイスケール
		for(i=0;i<PALLET_NUM;i++){
			r=(BYTE)(i/((double)PALLET_NUM-1.0)*255+.5);
			g=r;
			b=r;
			pc[PALLET_NUM-1-i]=RGB(r,g,b);
		}
		return;

	case RAINBOW:		//レインボーカラー
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

	case CYCLIC:		//黒－青－白－赤－黒
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


	//	エディットボックスの文字列を整数値に変換して戻り値として返す。
	//	数値以外が入力されていれば0になる
	//	i: はエディットボックスの番号(0,1,2,...)
int Get_int(int i){

	TCHAR *buffer;
	int len,num;

	len=GetWindowTextLength(sED[i].hdl) + 1;
	buffer=(TCHAR*)malloc((size_t)len*sizeof(TCHAR));

	if ((i>=0)&(i<ED_NUM)){
		GetWindowText(sED[i].hdl, buffer,len);		
		num=_tstoi(buffer);	//	ワイド文字を変換可能
				
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
		num=0;
	}
	free(buffer);
	return num;
}


	//エディットボックスの文字列をdouble型実数値に変換して戻り値として返す。
	//	数値以外が入力されていれば0になる
	//	i: はエディットボックスの番号(0,1,2,..)
double Get_double(int i){

	static TCHAR *buffer;
	char *mb;
	double num;
	int len,ret;
	PCSTR  pD=NULL ;    // デフォルトキャラクタ
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
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
		num=0.;
	}
	free(buffer);
	free(mb);
	return num;
}


	//　エディットボックスの文字列をTCHAR型配列 buffer にコピー
	//	i: はエディットボックスの番号
	//  TCHAR型で取り出すのであまり使わない,Get_char()を使用
void Get_text(int i, TCHAR *buffer){

	if ((i>=0)&(i<ED_NUM)){
		GetWindowText(sED[i].hdl, buffer, GetWindowTextLength(sED[i].hdl)+ 1);
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
		lstrcpy(buffer,TEXT(""));
	}
}

	//エディットボックスの文字列をchar型配列 buffer にコピー
	//	i: はエディットボックスの番号
void Get_char(int i, char *buf0){

	TCHAR *buffer;
	int len,ret;

	PCSTR  pD=NULL ;    // デフォルトキャラクタ
    PBOOL  pU=NULL ;

	len=GetWindowTextLength(sED[i].hdl)+ 1;
	buffer=(TCHAR*)malloc((size_t)len*sizeof(TCHAR));

	if ((i>=0)&(i<ED_NUM)){
		
		GetWindowText(sED[i].hdl, buffer, len);
		ret=WideCharToMultiByte(0,0, buffer,len,buf0,len*2,pD,pU);
		
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
		*buf0='\0';
	}
	free(buffer);
	return;
}

	//指定したエディットボックスに buffer で指定したワイド文字列を出力
	//	wsprintf(buffer,TEXT("数値は%dです"),value);等で整数値を挿入した文字列を指定可能
	//	i: はエディットボックスの番号
	// TCHAR型の文字列を出力するので、あまり使わない
void Set_text(int i, TCHAR *buffer){

	if ((i>=0)&(i<ED_NUM)){	
		SetWindowText(sED[i].hdl, buffer);
	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
	}
}

	//指定したエディットボックスに*bufferで指定したchar型文字列を出力
	//	wsprintf(buffer,"数値は%dです",value); 等で整数値を挿入した文字列を指定可能
	//	i: はエディットボックスの番号
void Set_char(int i, const char *buffer){

	TCHAR buf0[100];
	size_t n,ret;

	if ((i>=0)&(i<ED_NUM)){	
		n=strlen(buffer);
		mbstowcs_s(&ret,buf0,n+1,buffer,n+1);
		SetWindowText(sED[i].hdl, buf0);

	} else {
		TCHAR s[100];
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
	}
}

	//指定したエディットボックスにdouble型変数xの値を出力。
	//	i: はエディットボックスの番号
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
		wsprintf(s,TEXT("エディットボックスの番号は0～%dまでです．"),ED_NUM-1);
		MessageBox(hWnd, s, TEXT("Mlibによる警告"),MB_ICONHAND);
	}
}

	//数値入力ダイアログボックス用のウインドウプロシージャ
LRESULT CALLBACK DialogProc(HWND hDiag , UINT iMsg , WPARAM wParam , LPARAM lParam) {

	static LPDWORD lpRes;
	if (hDiag==NULL) {
		/* 結果変数のアドレスを保存 */
		lpRes=(LPDWORD)iMsg;
		*lpRes=0;
		return 0;
	}
	switch (iMsg) {
		case WM_CREATE: /* ウインドウ作成時の処理 */
			
			/* ボタン作成 */
			hDiaBt1=CreateWindow(TEXT("BUTTON"),TEXT("OK"),WS_CHILD|WS_VISIBLE,
			  190,8,60,32,hDiag,(HMENU)0,hInst,NULL);

			hDiaBt2=CreateWindow(TEXT("EDIT"),TEXT(""),WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_RIGHT,
			  8,8,170,32,hDiag,(HMENU)1,hInst,NULL);
			return 0;

		case WM_COMMAND: /* コマンドメッセージ */
			switch (LOWORD(wParam)) {
				case 0: /* １番ボタン */
					*lpRes=1;
					GetWindowText(hDiaBt2,Input1,GetWindowTextLength(hDiaBt2)+2);				
					DestroyWindow(hDiag);
					break;
			}
			return 0;
	
		case WM_DESTROY : /* 終了処理 */

			if (*lpRes==0) /* どちらも選択されていなければ-1 */
				*lpRes=-1;
			return 0;
	}
	return DefWindowProc (hDiag, iMsg, wParam, lParam) ;
}

	//数値入力ダイアログボックス用のモーダルダイアログ関数
DWORD dialog(LPCTSTR Mess) {

	DWORD dwRes;
	MSG msg;
	
	/* ダイアログのウインドウプロシージャ－に結果変数のアドレスを渡す */
	DialogProc(NULL,(UINT)LOWORD(&dwRes),0,0);

	/* ダイアログボックス作成 */
	hEditDialog = CreateWindow(TEXT("CDialog"),Mess,
	  WS_OVERLAPPEDWINDOW | WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,
	  270,80,NULL,NULL,hInst,NULL);

	/* メインウインドウを無効化してモーダルに */
	EnableWindow(hWnd,FALSE);
	SetFocus(hDiaBt2);
	/* メッセージループ */
	while (dwRes==0) { /* ダイアログが結果を返すまでループ */
		GetMessage(&msg,NULL,0,0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	/* メインウインドウを有効にしてモーダル解除 */
	EnableWindow(hWnd,TRUE);
	BringWindowToTop(hWnd);
	/* ダイアログの選択結果を返す */
	return dwRes;
}

	//	整数値を入力するダイアログボックスを表示する。
	//	整数以外を入力すると0が出力される。
	//	単なるキー入力待ちとしても使用できる。
int Input_int(){

	DWORD dwMRes;
	static char mb[200];
	int num;

	dwMRes=dialog(TEXT("整数値を入力してください"));
	num = _tstoi(Input1);

	Printf("%dが入力されました\n", num);
	return num;
}


	//	実数を入力するダイアログボックスを表示する。
	//	double型で出力。数値以外を入力すると0が出力される。
double Input_double(){

	DWORD dwMRes;
	static char mb[200];
	int len,ret;
	double num;
	PCSTR  pD=NULL ;    // デフォルトキャラクタ
    PBOOL  pU=NULL ;

	dwMRes=dialog(TEXT("文字を入力してください"));
	
	len=(int)lstrlen(Input1);
	ret=WideCharToMultiByte(0,0, Input1,len,mb,len*2,pD,pU);

	num = atof(mb);
	Printf("%fが入力されました\n", num);

	return num;
}


	//	文字列を入力するダイアログボックスを表示する。
	//	入力された文字列の先頭、アドレスをTCHAR型で返す。
TCHAR *Input_text(){
	
	DWORD dwMRes;
	dwMRes=dialog(TEXT("文字を入力してください"));
	Print(Input1);
	Printf("が入力されました\n");

	return Input1;
}

	//	文字列を入力するダイアログボックスを表示する。
	//	入力された文字列の先頭、アドレスをTCHAR型で返す。
char *Input_char(){

	DWORD dwMRes;
	static char mb[200];
	int len,ret;
	PCSTR  pD=NULL ;    // デフォルトキャラクタ
    PBOOL  pU=NULL ;

	dwMRes=dialog(TEXT("文字を入力してください"));
		
	len=(int)lstrlen(Input1);
	ret=WideCharToMultiByte(0,0, Input1,len,mb,len*2,pD,pU);

	Printf(mb);
	Printf("が入力されました\n");

	return mb;
}

	//一時停止のメッセージボックスを出す
void Pause(){

	MessageBox(NULL , TEXT("一時停止中") ,
			TEXT("") ,
			MB_OK | MB_ICONHAND);
}

	//待ち時間をミリ秒で指定(Sleep関数と同じ)
void Delay(int msec){

	Sleep(msec);
}

	//画面描画を強制的に更新する
	//	通常、あらゆる描画関数はメモリに書き込まれるだけで描画せず、
	//	main関数終了時に自動的に描画する設定になっている。
	//	main関数内でリアルタイム描画が必要な場合、この関数呼び出しで強制的に画面描画を行う
	//	実質的には、UpdateWindow(hWnd)　と同じ
void Refresh(void) {

	UpdateWindow(hWnd);

}

