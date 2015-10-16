//flag MOVE_LINE 画线—— flag MOVE_BOX 画框
void GetRange(int *fx, int *fy, int *tx, int *ty, bool flag )
{
	int tmp;
	int StrLen;
	DrawString( windowStart+20 , OVERBOARD , "点击空白区域(起始)" , BarSC , FALSE ) ;
	ScreenFlip() ;

	WaitTimer( WAIT_TIME_MOUSE ) ;
	WaitKey();
	GetMousePoint( fx , fy ) ;
	
//	tmp = MakeGraph(windowLength,windowWidth-OVERBOARD) ;
//	GetDrawScreenGraph(windowStart,windowStart+OVERBOARD,windowLength,windowWidth, tmp) ;
//  刷新消息
	DrawBox(windowStart+20,OVERBOARD,windowStart+20+150,OVERBOARD+20,Background,TRUE);
	ScreenFlip() ;
	DrawString( windowStart+20 , OVERBOARD , "点击空白区域(终点)" , BarSC , FALSE ) ;

	SaveDrawScreen( windowStart , OVERBOARD , windowLength , windowWidth , "Save.bmp" ) ;
	tmp = LoadGraph( "Save.bmp" ) ;

	WaitTimer(WAIT_TIME_MOUSE) ;

	while(ProcessMessage() == 0 && ( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0 )
	{
		GetMousePoint( tx , ty ) ;
		DrawGraph( 0 , OVERBOARD , tmp , FALSE ) ;
		if( flag )
			DrawBox( *fx , *fy , *tx , *ty , ColorDraw , FALSE ) ;
		else
			DrawLine( *fx , *fy , *tx , *ty , ColorDraw ) ;
		ScreenFlip() ;
	}
	DrawBox(windowStart+20,OVERBOARD,windowStart+20+150,OVERBOARD+20,Background,TRUE);
	if( ( ( *fx - *tx )*( *fx - *tx ) + ( *fy - *ty )*( *fy - *ty ) ) <= 25 )
		DrawString( windowWidth-300 , OVERBOARD , "错误，距离太短！！" , BarSC , FALSE ) ;
}
// 画多边形 k 表示有多少个点
void GetArea(int *k, int pos[MAX_POINT_NUM][2])
{
	int tmp;
	int i;
	WaitKey();
	GetMousePoint( &pos[0][0] , &pos[0][1] );
	for( i = 1; i <= *k ; i++ )
	{
		SaveDrawScreen( windowStart , OVERBOARD , windowLength , windowWidth , "Save.bmp") ;
		tmp = LoadGraph( "Save.bmp" ) ;
		WaitTimer(WAIT_TIME_MOUSE) ;
		while( ProcessMessage() == 0 && ( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0 )
		{
			GetMousePoint( &pos[i][0] , &pos[i][1] ) ;
			DrawGraph( windowStart , OVERBOARD , tmp , FALSE ) ;
			DrawLine( pos[i-1][0] , pos[i-1][1] , pos[i][0] , pos[i][1] , ColorDraw ) ;
			ScreenFlip() ;
		}
		if( ( (pos[i][0]-pos[0][0])*(pos[i][0]-pos[0][0]) + (pos[i][1]-pos[0][1])*(pos[i][1]-pos[0][1]) ) <= 100 )
		{
			pos[i][0] = pos[0][0] ;
			pos[i][1] = pos[0][1] ;
			break ;
		}
		DrawGraph( windowStart , OVERBOARD , tmp , FALSE ) ;
		DrawLine( pos[i-1][0] , pos[i-1][1] , pos[i][0] , pos[i][1] , ColorDraw ) ;
	}
	*k = i ;
}

unsigned char code(float x, float y )
{
	unsigned char c = 0;
	if( x < xl ) c = c | 1;
	else if ( x > xr ) c = c | 2 ;
	if( y > yb ) c = c | 4;
	else if ( y < yt ) c = c | 8;
	return c;
}
void clip( int *fx , int *fy , int *tx , int *ty )
{
	unsigned char c1, c2, c;
	float x, y, wx, wy;
	float x0 = *fx , y0 = *fy , x3 = *tx , y3 = *ty ;
	c1 = code( x0 , y0 ) ;
	c2 = code( x3 , y3 ) ;
	while(( !( c1 == 0 )) || ( !( c2 == 0 )))
	{
		if(( c1 & c2 )) return;
		c = c1;
		if( c == 0 ) c = c2 ;
		wx = x3 - x0; wy = y3 - y0;
		if(( c & 1 ) == 1 ) 
		{
			y = y0 + wy * ( xl - x0 ) / wx;
			x = xl ;
		}
		else if(( c & 2 ) == 2 ) 
		{
			y = y0 + wy * ( xr - x0 ) / wx;
			x = xr ;
		}
		else if(( c & 4 ) == 4 )
		{
			x = x0 + wx * ( yb - y0 ) / wy;
			y = yb;
		}
		else if(( c & 8 ) == 8 )
		{
			x = x0 + wx * ( yt - y0 ) / wy;
			y = yt;
		}
		if( c == c1 )
		{
			x0 = x;
			y0 = y;
			c1 = code( x0, y0 );
		}
		else
		{
			x3 = x;
			y3 = y;
			c2 = code( x3, y3 );
		}
	}
	
	*fx = int(x0);
	*fy = int(y0);
	*tx = int(x3);
	*ty = int(y3);
}

void Sutherland_Cohen()
{
	
	int x0, y0, x3, y3 ;
	GetRange( &x0 , &y0 , &x3 , &y3 , MOVE_LINE ) ;
	WaitTimer(WAIT_TIME_MOUSE) ;
	GetRange( &xl , &yt , &xr , &yb , MOVE_BOX ) ;
	DrawBox( windowStart , OVERBOARD , windowLength , windowWidth , Background , TRUE ) ;
	clip( &x0 , &y0 , &x3 , &y3 ) ;
	DrawLine( x0 , y0 , x3 , y3 , ColorDraw ) ;
}

int Cyrus_Beck_M(int k, double A[][2], double N[][2],double x[2], double y[2] , double * ts , double *te)
{
	int i,j;
	double t,dn,nw;
	*ts = 0;
	*te = 1;
	for( i = 0 ; i < k ; i++ )
	{
		dn = N[i][0] * (x[1]-x[0]) + N[i][1] * (y[1]- y[0]);
		nw = N[i][0] * (x[0]-A[i][0]) + N[i][1] * (y[0] - A[i][1]);
		if(fabs(dn)<1.0e-6)
		{
			if(nw<0) return 0;
		}
		else
		{
			t = -nw/dn;
			if(dn<0)
			{
				if(t < *te)
				{
					*te = t;
				}
				
			}
			else if(t > *ts)
			{
				*ts = t;
			}
		}
		if(*ts>*te) return 0;
	}
	return 1;
}
void Cyrus_Beck()
{
	int i , j ;
	int x0, y0, x3, y3 ;
	double ts , te;
	int position[MAX_POINT_NUM][2];
	double N[MAX_POINT_NUM-1][2];
	double A[MAX_POINT_NUM-1][2];
	double tmpK,tmpKe,tmpX[2],tmpY[2];
	int k = MAX_POINT_NUM;

	GetRange( &x0 , &y0 , &x3 , &y3 , MOVE_LINE ) ;
/*
//testS:
	y0 = 250;
	x0 = 150;
	y3 = 350;
	x3 = 250;
	DrawLine(x0,y0,x3,y3,ColorDraw) ;
//testE:
*/
	if(x3-x0 != 0)
	{
		DrawString( windowStart+20 , OVERBOARD , "至多按下20个点！" , BarSC , FALSE ) ;
		GetArea( &k , position ) ;
/*
//testS:
		k = 4 ;
		position[0][1] = position[0][0] = 200;
		position[3][0] = position[3][1] = 350;
		position[1][0] = 100;
		position[1][1] = 300;
		position[2][0] = 200;
		position[2][1] = 400;
		for(i = 0; i < 4; i++)
		{
			DrawLine(position[i][0],position[i][1],position[i+1][0],position[i+1][1],ColorDraw) ;
		}
//testE:
*/
		// equal 0???
		tmpK = (y3-y0) / (x3-x0) ;
		for( i = 0; i < k; i++ )
		{
			A[i][0] =  position[i][0];
			A[i][1] =  position[i][1];
			// N = A向量顺时针旋转90度
			N[i][0] =  position[i+1][1] - position[i][1] ;
			N[i][1] = -(position[i+1][0] - position[i][0]) ;
/*
			if(A[i][0] != 0)
			{
				tmpKe = A[i][1]/A[i][0] ;
				P[i][0] =( tmpK*x0 - tmpKe*position[i][0] + position[i][1] - y0 ) / ( tmpK - tmpKe ) ;
			}
			else
				P[i][0] = position[i][0];
			P[i][1] = tmpK*P[i][0] - tmpK*x0 + y0 ;
*/
		}
	}
	tmpX[0] = x0;
	tmpX[1] = x3;
	tmpY[0] = y0;
	tmpY[1] = y3;
	if(Cyrus_Beck_M( k , A , N ,tmpX , tmpY , &ts , &te ) )
	{
		DrawBox( windowStart , OVERBOARD , windowLength , windowWidth , BGC , TRUE ) ;
		DrawLine( x0 + ( x3 - x0 )*ts , y0 + ( y3 - y0 )*ts , x0 + ( x3 - x0 )*te , y0 + ( y3 - y0 )*te , ColorDraw ) ;
	}
	else DrawBox( windowStart , OVERBOARD , windowLength , windowWidth , BGC , TRUE ) ;
}


void LYD_Barsky_M(int x[2], int y[2])
{

	double dx, dy ;
	dx = x[1] - x[0];
	dy = y[1] - y[0];
	ts = 0;
	te = 1;
	if(clipt(-dx,x[0]-xl))
		if(clipt(dx,xr-x[0]))
			if(clipt(-dy,y[0]-yb))
				if(clipt(dy,yt-y[0]))
					DrawLine( x[0] + ( x[1] - x[0] )*ts , y[0] + ( y[1] - y[0] )*ts , x[0] + ( x[1] - x[0] )*te , y[0] + ( y[1] - y[0] )*te , ColorDraw ) ;
}

bool clipt(double r, double s)
{
	double t;
	if( r < 0 )
	{
		t = s / r;
		if(t > te) return FALSE;
		else if(t > ts) ts = t;
	}
	else if( r > 0 )
	{
		t = s / r;
		if( t < ts ) return FALSE;
		else if( t < te ) te = t;
	}
	else if( s < 0 ) return FALSE;
	return TRUE;
}

void LYD_Barsky()
{
	int x[2], y[2] ;
	GetRange( &x[0] , &y[0] , &x[1] , &y[1] , MOVE_LINE ) ;
	GetRange( &xl , &yb , &xr , &yt , MOVE_BOX ) ;
	DrawBox( windowStart , OVERBOARD , windowLength , windowWidth , Background , TRUE ) ;
	LYD_Barsky_M( x , y ) ;
}
bool checkPosition( int x , int y )
{
	if( x >= xl && x <= xr && y <= yb && y >= yt )
		return TRUE;
	return FALSE;
}
void H_S_Polygon_M( int k , int position[][2] )
{
	int new_position[45][2] ;
	int new_k = 0 ;
	int i;
	int px = position[k - 1][0] , py = position[k - 1][1] , tx = position[0][0] , ty = position[0][1] ;
	bool flag = checkPosition( px , py ) ;
	for(i = 0; i <= k ; )
	{
		if( checkPosition( tx , ty ) )
		{
			if(FALSE == flag)
			{
				flag = TRUE;
				clip( &px , &py , &tx , &ty ) ;
				new_position[new_k][0] = px;
				new_position[new_k][1] = py;
				new_k++;
			}
			new_position[new_k][0] = tx;
			new_position[new_k][1] = ty;
			new_k++;
		}
		else
		{
			if(TRUE == flag)
			{
				flag = FALSE;
				clip( &px , &py , &tx , &ty ) ;
				new_position[new_k][0] = tx;
				new_position[new_k][1] = ty;
				new_k++;
			}
			else
			{
				clip( &px , &py , &tx , &ty ) ;
				if( tx != position[i][0])
				{
					new_position[new_k][0] = px;
					new_position[new_k][1] = py;
					new_k++;
					new_position[new_k][0] = tx;
					new_position[new_k][1] = ty;
					new_k++;
				}
				
			}
		}
		i++;
		px = position[i-1][0];
		py = position[i-1][1];
		tx = position[i][0];
		ty = position[i][1];
	}
	new_position[new_k][0] = tx;
	new_position[new_k][1] = ty;
	new_k++;
	DrawBox( windowStart , OVERBOARD , windowLength , windowWidth , Background , TRUE ) ;
	for( i = 0; i < new_k-2 ; i++ )
	{
		DrawLine( new_position[i][0] , new_position[i][1] , new_position[i+1][0] , new_position[i+1][1] , ColorDraw) ;
	}
}
void H_S_Polygon()
{
	int k = MAX_POINT_NUM ;
	int position[MAX_POINT_NUM][2] ;
	GetArea( &k , position ) ;
	GetRange( &xl , &yt , &xr , &yb , MOVE_BOX ) ;
	H_S_Polygon_M( k , position ) ;
}
// TRUE 下板 FALSE 上板
int DrawLine_Roller( int x1, int y1, int radius , int adjust , int Color , bool flag )
{
	if(flag)
		DrawLine( x1, y1, x1+radius*(sin(PI*(windowLength/2 - x1 + adjust )/180)), y1+radius*(cos(PI*(windowLength/2 - x1 + adjust )/180)), Color);
	else
		DrawLine( x1, y1, x1-radius*(sin(PI*(windowLength/2 - x1 + adjust )/180)), y1-radius*(cos(PI*(windowLength/2 - x1 + adjust )/180)), Color);
	return 0;
}
void DrawBike_m(int startx, int starty)
{
	
	//mid static 骨架

	DrawLine( startx , starty , startx-BACK_ROLLER_POS/2 , starty-SUPPORTER_POS , ColorDraw ) ;
	DrawLine( startx-BACK_ROLLER_POS/2 , starty-SUPPORTER_POS , startx-BACK_ROLLER_POS , starty , ColorDraw ) ;
	DrawLine( startx-BACK_ROLLER_POS/2 , starty-SUPPORTER_POS , startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER , starty-SUPPORTER_POS , ColorDraw ) ;
	DrawLine( startx-BACK_ROLLER_POS/2 , starty-SUPPORTER_POS , startx-BACK_ROLLER_POS/2 , starty-SUPPORTER_POS-12 , ColorDraw ) ;
	DrawLine( startx-BACK_ROLLER_POS/2-7 , starty-SUPPORTER_POS-12 ,startx-BACK_ROLLER_POS/2+10 , starty-SUPPORTER_POS-12 , ColorDraw) ;//座凳
	DrawLine( startx , starty , startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER , starty-SUPPORTER_POS , ColorDraw ) ;
	DrawLine( startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER , starty-SUPPORTER_POS ,  startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER-9 , starty-SUPPORTER_POS-17 , ColorDraw ) ;//把手
	DrawLine( startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER-9-10 , starty-SUPPORTER_POS-17+15 , startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER-9+8 , starty-SUPPORTER_POS-17-12 , ColorDraw ) ;
	DrawLine( startx-BACK_ROLLER_POS/2+FRONT_SUPPORTER , starty-SUPPORTER_POS , startx+FRONT_ROLLER_POS , starty , ColorDraw ) ;//前支架
	//mid move
	DrawCircle( startx , starty , ROLLER_RADIUS , ColorDraw , FALSE ) ;

	DrawLine_Roller( startx , starty , MID_ROLLER_RADIUS , 0 , ColorDraw , TRUE ) ;//踏板
	DrawLine_Roller( startx , starty , MID_ROLLER_RADIUS , 0 , ColorDraw , FALSE) ;

	//back
	DrawCircle( startx-BACK_ROLLER_POS , starty , BACK_ROLLER_RADIUS , ColorDraw  , FALSE ) ;
	DrawCircle( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , ColorDraw , FALSE ) ;
	DrawLine( startx , starty+(ROLLER_RADIUS) , startx-BACK_ROLLER_POS , starty+BACK_ROLLER_RADIUS , ColorDraw ) ;//链子
	DrawLine( startx , starty-(ROLLER_RADIUS) , startx-BACK_ROLLER_POS , starty-BACK_ROLLER_RADIUS , ColorDraw ) ;
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 0 , ColorDraw , TRUE ) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 0 , ColorDraw , FALSE) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 30 , ColorDraw , TRUE ) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 30 , ColorDraw , FALSE) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 60 , ColorDraw , TRUE ) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 60 , ColorDraw , FALSE) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 90 , ColorDraw , TRUE ) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 90 , ColorDraw , FALSE) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 120 , ColorDraw , TRUE ) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 120 , ColorDraw , FALSE) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 150 , ColorDraw , TRUE ) ;// 后轮轴
	DrawLine_Roller( startx-BACK_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS, 150 , ColorDraw , FALSE) ;// 后轮轴

	//front
	DrawCircle( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , ColorDraw , FALSE ) ; 
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 0 , ColorDraw , TRUE ) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 0 , ColorDraw , FALSE) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 30 , ColorDraw , TRUE ) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 30 , ColorDraw , FALSE) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 60 , ColorDraw , TRUE ) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 60 , ColorDraw , FALSE) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 90 , ColorDraw , TRUE ) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 90 , ColorDraw , FALSE) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 120 , ColorDraw , TRUE ) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 120 , ColorDraw , FALSE) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 150 , ColorDraw , TRUE ) ;// 前轮轴
	DrawLine_Roller( startx+FRONT_ROLLER_POS , starty , BIGGER_ROLLER_RADIUS , 150 , ColorDraw , FALSE) ;// 前轮轴
	ScreenFlip() ;
} 
void DrawBike()
{
	int startx = windowLength/2 , starty = windowWidth/2;
		
	ScreenFlip();
	while( ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_Q) == 0 )
	{
		DrawBox( windowStart , OVERBOARD , windowLength , windowWidth , Background , TRUE ) ;
		DrawString( windowStart+20 , OVERBOARD , "按键盘Q键退出动画！" , BarSC , FALSE ) ;
		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 )
			GetMousePoint( &MouseX , &MouseY );
		startx = MouseX;
		DrawBike_m(startx , starty) ;
	}
}
void bike()
{
	DrawBike();
}