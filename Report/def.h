#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include<tchar.h>
#include<stdarg.h> 
#include<math.h> 
#include<stdio.h>

/**********************************/
/*   Window Parameter Setting     */
/**********************************/
	#define PROGRAM_TITLE "カラーボールゲーム"   // Caption of Title bar
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

	#define FIGMAX		20		//フィギュアウインドウに描ける図の最大数
	#define PALLET_NUM	(8*32)	//2D画像のカラーマップの諧調（8～256までで8の倍数を指定）

	#define BUFSIZE_W	81		//メモウィンドウの水平文字数
	#define BUFSIZE_H	1024	//メモウインドウの記憶行数
	#define DISPSIZE_H	2		//メモウインドウの表示行数
	#define MEMOWIN_H	(19*(DISPSIZE_H+1))		//メモウインドウの高さ
	#define PNMAX		20		//フィギュアウインドウに記憶できる線種の最大数
	#define BUFNMAX		25		//軸キャプション，数値ラベル等の最大文字サイズ

	#define MEMO_ID1	0
	#define SCRBAR_ID1	1
	#define DIALOG1		2
	#define BUTTON_ID1	3
	#define EDIT_ID1	(BUTTON_ID1+PB_NUM+CK_NUM+RD_NUM)
	#define STATIC_ID1	(EDIT_ID1+ED_NUM)
	
	//plflug
	#define GRAY		0		//グレイスケール
	#define RAINBOW		1		//フルカラー虹色　（一般）
	#define CYCLIC		2		//黒-青-白-赤-黒　（位相等の巡回的な数値用）

	//cbflug
	#define LEGEND_ON	1		//２Ｄプロットの凡例表示
	#define LEGEND_OFF	0		//２Ｄプロットの凡例非表示

	//szflug
	#define SIZE_NORMAL 0		//フィギュアウインドウの枠に２Ｄ画像表示
	#define SIZE_SQUARE 1		//フィギュアウインドウの縦横サイズをあわせる	
	#define SIZE_DATA	2		//フィギュアウインドウをデータのサイズに合わせる

	//bfflug　　　　　　　　
	#define	FILL_OFF	0		// 内部を塗らない(保存)
	#define	FILL_ON		1		//指定範囲を枠と同色で塗りつぶす，  
	#define	FILL_WHITE	2		// 枠内を白色で塗りつぶす

	//clflug
	#define	DRAW_OUTLINE -1		//枠のみ表示
	#define	CLEAR_INSIDE 0		//カレントフィギュアウインドウの内部消去，枠，軸は消さない	
	#define	CLEAR_FIG	 1		//カレントフィギュアウインドウの全消去
	#define	CLEAR_ALL	 2		//グラフィックウインドウの全消去

	//grflug
	#define	ZERO_LINE	0		//ゼロラインのみの描画
	#define	YGRID_LINE	1		//グリッドラインの描画	
	#define	XGRID_LINE	2		//グリッドラインの描画	
	#define	XYGRID_LINE	3		//グリッドラインの描画


/***********************/
/*     End　　　　*/
/***********************/


/**************************************************/
/* Definition of gloval variables (never change)  */
/**************************************************/

	int iID_Cfw;				//現在のフィギュアウインドウのID
	int iNum_fw;				//作られたフィギュアウインドウの最大数

	struct figure				//各フィギュアウインドウの位置、最大値、最小値等の構造体
	{
		int xwin;				//フィギュアウインドウ左上のｘ座標
		int ywin;				//フィギュアウインドウ左上のｙ座標
		int wwin;				//フィギュアウインドウの幅
		int	hwin;				//フィギュアウインドウの高さ

		int hn;					//グラフィックウインドウでの縦方向のフィギュアウインドウの数
		int wn;					//グラフィックウインドウでの横方向のフィギュアウインドウの数
		int nn;					//その表示位置

		double ymin;			//ｙ軸スケール最小値
		double ymax;			//ｙ軸スケール最大値
		double xmin;			//ｘ軸スケール最小値
		double xmax;			//ｘ軸スケール最大値

		size_t nobm;				//ｙ軸数値ラベルの最大文字数

		double xs;				//ｘ軸の数値ラベル最小値
		double ys;				//ｙ軸の数値ラベル最小値
		double xe;				//ｘ軸の数値ラベル最大値
		double ye;				//ｙ軸の数値ラベル最大値
		double xd;				//ｘ軸の数値ラベル間隔
		double yd;				//ｙ軸の数値ラベル間隔
		int N;					//ウインドウに描画される点の個数
		char  xlabel[BUFNMAX+1];		//ｘ軸キャプション（25文字まで）
		char  ylabel[BUFNMAX+1];		//ｙ軸キャプション（25文字まで）

		int pf[PNMAX];				//フィギュアウインドウに重ね書きされた図のペンスタイルを記憶
		int pw[PNMAX];				//フィギュアウインドウに重ね書きされた図のペン幅を記憶
		COLORREF pc[PNMAX];				//フィギュアウインドウに重ね書きされた図のペンカラーを記憶
		int pn;					//フィギュアウインドウに重ね書きされた個数
	}sFW[FIGMAX];

	struct controle				//コントロールの位置、サイズ、キャプション情報の構造体
	{
		HWND hdl;
		int x;					//ウインドウ左上のｘ座標
		int y;					//ウインドウ左上のｙ座標
		int w;					//ウインドウの幅
		int	h;					//ウインドウの高さ
		long chk;				//チェックボタン等のチェック状態が入るフラグ
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
	BYTE Italic_Font_Flug=0;			//0 -- normal、1 -- Italic

/**************/
/*    End     */
/**************/



/**********************************************************/
/*   グラフィックウインドウ内の各フィギュアウインドウの	  */
/*   左右上下のマージンを定めるグローバル変数の変更箇所   */
/**********************************************************/

	int MERGIN_L=80;		// Left mergin in figure window、when caption in y-axis is wide, increase the value here
	int MERGIN_R=30;		//Right mergin in figure window
	int MERGIN_T=12;		//Upper mergin in figure window
	int MERGIN_B=60;		//Lower mergin in figure window

/******************/
/*    ここまで　  */
/******************/



void component(){

	/**************************************************/
	/*   ウインドウ内の各コントロール情報の変更箇所   */
	/**************************************************/

	//標準のエディットウインドウ、ボタン情報のグローバル変数への登録
	//ウインドウ配置を標準から変えたい場合はここで構造体変数を直接変更する
	int i;
	int MERGIN_W=20;		//メインウィンドウの端マージン
	int MERGIN_C=10	;		//各コントロール間隔のマージン
	int BTWIN_W=120;		//プッシュボタンの幅
	int BTWIN_H=50;			//プッシュボタンの高さ
	int EDBOX_W=80;			//EditBox の高さ
	int EDBOX_H=27;			//EditBox の高さ
	TCHAR buf[BUFNMAX+1];

	//各プッシュボタンの情報登録（iはボタン番号に対応）
	//for(i=0;i<PB_NUM;i++){
	sPB[0].x=MERGIN_W+(BTWIN_W+MERGIN_C)*0;	//各ボタン左上のｘ座標
	sPB[0].y=MERGIN_W;						//各ボタン左上のｙ座標
	sPB[0].w=BTWIN_W*2;						//各ボタンの幅
	sPB[0].h=BTWIN_H;						//各ボタンの高さ
	wsprintf(buf,TEXT("ネクスト"));
	lstrcpy(sPB[0].name,buf);				//各ボタンのキャプション
	//}
	//sPB[1].x = MERGIN_W + (BTWIN_W + MERGIN_C) * 1;	//各ボタン左上のｘ座標
	//sPB[1].y = MERGIN_W;						//各ボタン左上のｙ座標
	//sPB[1].w = BTWIN_W;						//各ボタンの幅
	//sPB[1].h = BTWIN_H;						//各ボタンの高さ
	//wsprintf(buf, TEXT("RESET"));
	//lstrcpy(sPB[1].name, buf);				//各ボタンのキャプション

	//チェックボックスの情報登録（iはチェックボックス番号に対応）
	for(i=0;i<CK_NUM;i++){
		sCK[i].x=MERGIN_W+MERGIN_C				//各チェックボックス左上のｘ座標
			+((BTWIN_W+MERGIN_C)*PB_NUM-MERGIN_C)/3;	
		sCK[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//各チェックボックス左上のｙ座標
			+(EDBOX_H+MERGIN_C)*i;	
		sCK[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//各チェックボックスの幅
			-MERGIN_C)/3-MERGIN_C;	
		sCK[i].h=EDBOX_H;						//各チェックボックスの高さ
		wsprintf(buf,TEXT("Check Box%d"),i);
		lstrcpy(sCK[i].name,buf);				//チェックボックスのキャプション
	}

	//ラジオボタンの情報登録（iは各ラジオボタン番号に対応）
	for(i=0;i<RD_NUM;i++){
		sRD[i].x=MERGIN_W+MERGIN_C				//各ラジオボタン左上のｘ座標
			+2*((BTWIN_W+MERGIN_C)*PB_NUM-MERGIN_C)/3;	
		sRD[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//各ラジオボタン左上のｙ座標
			+(EDBOX_H+MERGIN_C)*i;	
		sRD[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//各ラジオボタンの幅
			-MERGIN_C)/3-MERGIN_C;	
		sRD[i].h=EDBOX_H;						//各ラジオボタンの高さ
		sRD[i].chk=FALSE;
		wsprintf(buf,TEXT("Radio Button%d"),i);
		lstrcpy(sRD[i].name,buf);				//各ラジオボタンのキャプション
	}

		//ラジオボタンのグループ化の指定　以下の指定ではラジオボタンの数が4個のとき
		//ID=0,1 と2,3がそれぞれグループになる
		//sRD[0].chk=TRUE;sRD[2].chk=TRUE;
		sRD[0].chk=TRUE;
		sRD[3].chk=TRUE;

	//各エディットウインドウの情報登録
	for(i=0;i<ED_NUM;i++){
		sED[i].x=MERGIN_W;						//各エディットウインドウ上のｘ座標
		sED[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//各エディットウインドウ左上のｙ座標
			+(EDBOX_H+MERGIN_C)*i;	
		sED[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//各エディットウインドウの幅
			-MERGIN_C)/3-MERGIN_C;	
		sED[i].h=EDBOX_H;						//各エディットウインドウの高さ
		//wsprintf(buf,TEXT("Edit%d"),i);
		wsprintf(buf, TEXT(""));
		lstrcpy(sED[i].name,buf);				//各エディットウインドウのキャプション
	}

	for(i=0;i<ST_NUM;i++){
		sST[i].x=MERGIN_W;						//各スタティックのｘ座標
		sST[i].y=MERGIN_W+BTWIN_H+MERGIN_C		//各スタティックのｙ座標
			+(EDBOX_H+MERGIN_C)*i;	
		sST[i].w=((BTWIN_W+MERGIN_C)*PB_NUM		//各スタティックの幅
			-MERGIN_C)/3-MERGIN_C;	
		sST[i].h=EDBOX_H;						//各スタティックの高さ
		wsprintf(buf,TEXT("STATIC%d"),i);
		lstrcpy(sST[i].name,buf);				//各スタティックのキャプション	
	}
	lstrcpy(sST[0].name, L"スタティック");
	lstrcpy(sST[1].name, TEXT("文字列"));
	wsprintf(sST[2].name, _T("%d番目"), 3);

	//メモウインドウの情報登録
	sME.x=MERGIN_W+(BTWIN_W+MERGIN_C)*PB_NUM;	//メモウィンドウの左上X座標
	sME.y=MERGIN_W;								//メモウィンドウの左上Y座標	
	sME.w=MAINWIN_W-MERGIN_W-(MERGIN_W			//メモウインドウの幅
		+(BTWIN_W+MERGIN_C)*PB_NUM)-18; 
	sME.h=MEMOWIN_H ;							//メモウインドウの高さ
	lstrcpy(sME.name,TEXT(""));


	//グラフィックウインドウの情報登録
	sGW.x=MERGIN_W;								//グラフィックウィンドウの左上X座標
	sGW.y=MERGIN_W*2+BTWIN_H					//グラフィックウィンドウの左上Y座標	20*2+50+37*0
		+(MERGIN_C+EDBOX_H)*ED_NUM;		
	sGW.w=MAINWIN_W-MERGIN_W*3;					//グラフィックウインドウの幅1000-40 960
	sGW.h=MAINWIN_H-sGW.y-MERGIN_W*3;			//グラフィックウインドウの高さ750-90-20*2=620
	lstrcpy(sGW.name,TEXT(""));
}

/*****************/
/*   ここまで　　*/
/*****************/