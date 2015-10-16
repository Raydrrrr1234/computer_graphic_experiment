#include "DxLib.h"
#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "bar.h"
#include "function.h"
#include "realize1_3.h"
#include "realize4_5.h"
#include "addition.h"
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
		 LPSTR lpCmdLine, int nCmdShow )
{
	char StrBuf[ 128 ] , StrBuf2[ 32 ];
	
	//设置为窗口模式
	ChangeWindowMode( TRUE ) ;
	SetGraphMode( windowLength , windowWidth , 16 ) ;
	SetMainWindowText( "Number:2009150110---Name:Dairuikang---Version:1.0" ) ;
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;	// エラーが起きたら直ちに終了
	}
	// 描画先画面を裏画面にセット
	SetDrawScreen( DX_SCREEN_BACK ) ;

	// マウスを表示状態にする
	SetMouseDispFlag( TRUE ) ;

	// 背景颜色
	SetBackgroundColor( 255 , 255 , 255 );

	// 白色の値を取得
	BGC = GetColor( 255 , 255 , 255 ) ;

	// 黒の値を取得
	BoxCr = GetColor( 0 , 0 , 0 ) ;

	DrawBox( windowStart , windowStart , windowLength , windowWidth , BGC , TRUE ) ;
	// キーが押されるまでループ
	while(ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
	{
		//ClearDrawScreen () ;
		// 每回使用后的一些变量需要重置
		SecondSelectedBar = -1;
		//
		GetMousePoint( &MouseX , &MouseY ) ;

		// 画菜单栏独立到bar.h里面
		DrawBars(MouseX, MouseY) ;
		// doFlag没有设置成0就工具栏将不会响应
		// doFunction接收连个参数一级菜单和二级菜单选择的项目
		if( doFlag )
			doFunction( SelectedBar , SecondSelectedBar );
		// 裏画面の内容を表画面に反映させる
		ScreenFlip() ;
	}

	DxLib_End() ;		// ＤＸライブラリ使用の終了処理

	return 0 ;		// ソフトの終了
}
