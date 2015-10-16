//添加子功能，case 0 代表第一个功能表
#define ShowSub_0Bar 3//addbar
#define ShowSub_1Bar 5
#define ShowSub_2Bar 3
#define ShowSub_3Bar 4
#define ShowSub_4Bar 1
#define ShowSub_9Bar 5

char subbar_0[8][20] = {"Kill me baby!","Clean Screen!","颜色","子功能4","子功能5","子功能6","子功能7","子功能8"};//addbar
char subbar_1[8][20] = {"DDA画线","正负法画线","Bresenham画线","正负法画圆","Bresenham算法绘制圆","子功能6","子功能7","子功能8"};
char subbar_2[8][20] = {"有顶点扫描线","四连通种子填充","线性种子填充","子功能4","子功能5","子功能6","子功能7","子功能8"};
char subbar_3[8][20] = {"Sutherland-Cohen","Cyrus-Beck","梁友栋-Barsky","H-S多边形逐边裁剪","子功能5","子功能6","子功能7","子功能8"};
char subbar_4[8][20] = {"单车","子功能2","子功能3","子功能4","子功能5","子功能6","子功能7","子功能8"};
char subbar_9[8][20] = {"火花","test","子功能3","子功能4","子功能5","子功能6","子功能7","子功能8"};
int SecondSelectedBar = -1;
int SecondSelectedBarStart = -1;
void ShowDetailBar ( int SelectedBar, int SelectedBarStart )
{
	int i;
	SecondBarPos = SelectedBarStart + SecondBarSpan;
	DrawBox( windowStart , SecondBarY , windowLength , OVERBOARD , Background , TRUE ) ;
	char (*sub_bar)[20];
	unsigned char show_bar;
	switch ( SelectedBar )
	{
	case 0: 
		{
			sub_bar = subbar_0;
			show_bar = ShowSub_0Bar;
			break;
		}
	case 1:
		{
			sub_bar = subbar_1;
			show_bar = ShowSub_1Bar;
			break;
		}
	case 2:
		{
			sub_bar = subbar_2;
			show_bar = ShowSub_2Bar;
			break;
		}
	case 3:
		{
			sub_bar = subbar_3;
			show_bar = ShowSub_3Bar;
			break;
		}
	case 4:
		{
			sub_bar = subbar_4;
			show_bar = ShowSub_4Bar;
			break;
		}
	case 9:
		{
			sub_bar = subbar_9;
			show_bar = ShowSub_9Bar;
			break;
		}
	default:
		{
			return ;
		}
	}
	for( i = 0 ; i < show_bar ; i++ )//addbar
	{
		StrLen = strlen( &sub_bar[i][0] );//addbar
		StrWidth = GetDrawStringWidth( &sub_bar[i][0] , StrLen ) ;//addbar
		if( ( MouseY < SELECTEDLOWER && MouseY > SELECTEDUPPER ) && ( MouseX <= SecondBarPos+StrWidth+7 && MouseX > SecondBarPos-8 ) )
		{
			DrawBox( SecondBarPos-8-1 , SecondBarY , SecondBarPos+StrWidth+7 , OVERBOARD , BarHBC , FALSE ) ;
			DrawBox( SecondBarPos-8 , SecondBarY+1 , SecondBarPos+StrWidth+7-1 , OVERBOARD-1 , BarHGC , TRUE ) ;
			//记录用于执行功能第0项的第i个功能
			SecondSelectedBar = i ;
		}
		DrawString( SecondBarPos , SecondBarY , &sub_bar[i][0] , BarSC , FALSE ) ;//addbar
		SecondBarPos = SecondBarPos + StrWidth + SecondBarSpan;
	}
	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && (MouseY > OVERBOARD || SecondBarPos < MouseX) )
	{
		doFlag = 0;
		SecondSelectedBar = -1;
	}
	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 &&  SecondSelectedBar != -1 )
	{
		// 押されている
		doFlag = 1;
	}
}

//一级菜单设置显示
#define ShowBar 10
int SelectedBar = -1;
int SelectedBarStart = -1;
char bar[BarNum][10] = {"功能", "基本图形" ,"填充算法", "裁剪算法" , "动画" , "功能6", "功能7" , "功能8", "功能9" , "Addition" };
void DrawBars(int x, int y)
{
	int i;
	//DrawBox( 0 , 0 , BarSizeX , BarSizeY , BarBGC , TRUE ) ;
	//工具条背景颜色渐变
	for( i = 0; i < 10 ; i++ )
	{
		BarBGC = GetColor( 240 + i , 240 + i , 240 + i ) ;
		DrawBox( ColorChange * i , 0 , ColorChange * (i+1) , BarSizeY , BarBGC , TRUE ) ;
	}
	BarBGC = GetColor( 240 + i , 240 + i , 240 + i ) ;
	DrawBox( ColorChange * i , 0 , BarSizeX , BarSizeY , BarBGC , TRUE ) ;
	//完
	//设置字体
	ChangeFont ( "微软雅黑" ) ;
	SetFontSize( BarFrontSize ) ;
	//完
	NextFunction = 8;
	for( i = 0; i < ShowBar ; i++)
	{
		StrLen = strlen( &bar[i][0] );
		StrWidth = GetDrawStringWidth( &bar[i][0] , StrLen ) ;
		if( ( y < BarSizeY-1 && y > -1 ) && ( x <= NextFunction+7+StrWidth+8 && x > NextFunction ) || (SelectedBar == i) )
		{
			DrawBox( NextFunction-1 , 1 , NextFunction+7+StrWidth+8 , 23 , BarHBC , FALSE ) ;
			DrawBox( NextFunction , 1+1 , NextFunction+7+StrWidth+8-1 , 23-1 , BarHGC , TRUE ) ;
			//记录用于二级菜单
			SelectedBar = i ;
			SelectedBarStart = NextFunction;
		}
		DrawString( NextFunction+7 , BarStringY , &bar[i][0] , BarSC) ;
		NextFunction = NextFunction+7+StrWidth+8;
	}
	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && (y > 24 || NextFunction < x) )
	{
		flag = 0;
	}
	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 &&  SelectedBar != -1 && !doFlag)
	{
		// 押されている
		flag = 1;
	}
	
	if( flag )
	{
		//DrawString( 30 , 30 , &bar[SelectedBar][0] , BarSC , FALSE ) ;
		//独立出来写到了function.h里面实现
		if(!(ProcessMessage() == 0))
			DxLib_End() ;
		ShowDetailBar( SelectedBar , SelectedBarStart );
	}
}

