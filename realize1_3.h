int ShowColorPad()
{
	int oldColor;
	int colors[COLORNUM*3] = {255,182,193 
					,255,192,203 
					,220,20,60 
					,255,240,245 
					,219,112,147 
					,255,105,180 
					,255,20,147 
					,199,21,133 
					,218,112,214 
					,216,191,216 
					,221,160,221 
					,238,130,238 
					,255,0,255 
					,255,0,255 
					,139,0,139 
					,128,0,128 
					,186,85,211 
					,148,0,211 
					,153,50,204 
					,75,0,130 
					,138,43,226 
					,147,112,219 
					,123,104,238 
					,106,90,205 
					,72,61,139 
					,230,230,250 
					,248,248,255 
					,0,0,255 
					,0,0,205 
					,25,25,112 
					,0,0,139 
					,0,0,128 
					,65,105,225 
					,100,149,237 
					,176,196,222 
					,119,136,153 
					,112,128,144 
					,30,144,255 
					,240,248,255 
					,70,130,180 
					,135,206,250 
					,135,206,235 
					,0,191,255 
					,173,216,230};
	int i,j;
	int x = windowLength-20-40, y = PAINTBOX;
	DrawString( windowLength-200 , OVERBOARD , "在这里选取颜色" , BarSC , FALSE ) ;
	for(i = 0; i < 11; i++)
	{
		for(j = 0; j < 4; j++)
		{
			DrawBox( x  , y  , x + 40 , y + 25 , GetColor( colors[i*3+j] , colors[i*3+j+1] , colors[i*3+2] ) , TRUE);
			x-=47;
		}
		y+=32;
		x = windowLength-20-40;
	}
	ScreenFlip() ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x = MouseX;
		y = MouseY;
	}
	oldColor = ColorDraw;
	ColorDraw = GetPixel( x , y ) ;
	DrawBox( windowLength-280 , OVERBOARD , windowLength , windowWidth , BGC , TRUE ) ;
	return oldColor;
}
//dda算法
void DDALine( )
{
	int x1 , y1 , x2 , y2 ;
	//	DrawLine(0,0,500,500,ColorDraw);
	x1 = x2 = y1 = y2 = 0 ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x1 = MouseX;
		y1 = MouseY;
	}
	//	debug(100);
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x2 = MouseX;
		y2 = MouseY;
	}
	//	debug(150);
	DDALine_M(x1,y1,x2,y2);
}

//dda实现
void DDALine_M(int x1,int y1,int x2,int y2)
{
	int k,i;
	float x,y,dx,dy;
	k=abs(x2-x1);
	if(abs(y2-y1)>k) k=abs(y2-y1);
	dx=float(x2-x1)/k;
	dy=float(y2-y1)/k;
	x=float(x1);
	y=float(y1);
	for(i = 0; i < k; i++)
	{
		DrawPixel(int(x+0.5), int(y+0.5), ColorDraw);
		x=x+dx;
		y=y+dy;
	}
}

//正负画线
void AnotherDrawLine()
{
	int x1 , y1 , x2 , y2 ;
	//	DrawLine(0,0,500,500,ColorDraw);
	x1 = x2 = y1 = y2 = 0 ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x1 = MouseX;
		y1 = MouseY;
	}
	//debug(100);
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x2 = MouseX;
		y2 = MouseY;
	}
	//debug(150);
	AnotherDrawLine_M(x1,y1,x2,y2);
}
//正负法算法
void AnotherDrawLine_M(int x1,int y1,int x2,int y2)
{
	int tmp ;
	double k ;
	int a,b,dt1,dt2,d,x,y ;
	//预处理
	k = (double)(y1-y2) / (double)(x1-x2);
	if(k < 0)
	{
		y1 = -y1;
		y2 = -y2;
	}
	if(k > 1)
	{
		tmp = x1;
		x1 = y1;
		y1 = tmp;
		tmp = x2;
		x2 = y2;
		y2 = tmp;
	}
	if (x1 > x2)
	{
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	//预处理结束
	{
		a = y1 - y2;
		b = x2 - x1;
		d = 2*a+b;
		dt1 = 2*a;
		dt2 = 2*(a+b);
		x = x1; y = y1;
		while(x < x2)
		{

			if(d<0)
			{
				x++;
				if(y1 < y2)
					y++;
				else
					y--;
				d = d+dt2;
			}
			else
			{
				x++;
				d = d+dt1;
			}
			//四种情况对应画法
			if(k > 1)
				DrawPixel(y,x,ColorDraw);
			else if(k < 1 && k > 0)
				DrawPixel(x,y,ColorDraw);
			else if(k < -1)
				DrawPixel(-y,x,ColorDraw);
			else 
				DrawPixel(x,-y,ColorDraw);
		}
	}

}

//bresenham画线
void BresenhamLine()
{
	int x1 , y1 , x2 , y2 ;
	//	DrawLine(0,0,500,500,ColorDraw);
	x1 = x2 = y1 = y2 = 0 ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x1 = MouseX;
		y1 = MouseY;
	}
	//	debug(100);
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x2 = MouseX;
		y2 = MouseY;
	}
	//	debug(150);
	BresenhamLine_M(x1,y1,x2,y2);
}
//bresenham实现
void BresenhamLine_M(int x1,int y1,int x2,int y2)
{
	int dx,dy,x,y,i,tmp;
	double e,m;
	double k;
	//预处理
	k = (double)(y1-y2) / (double)(x1-x2);
	if(k < 0)
	{
		y1 = -y1;
		y2 = -y2;
	}
	if(k > 1)
	{
		tmp = x1;
		x1 = y1;
		y1 = tmp;
		tmp = x2;
		x2 = y2;
		y2 = tmp;
	}
	if (x1 > x2)
	{
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	//预处理结束
	x = x1;
	y = y1;
	dx = (x2-x1);
	dy = (y2-y1);
	m = (double)dy/(double)dx;
	e = m-0.5;
	for(i = 0; i < dx; i++)
	{
		//四种情况对应画法
		if(k > 1)
			DrawPixel(y,x,ColorDraw);
		else if(k < 1 && k > 0)
			DrawPixel(x,y,ColorDraw);
		else if(k < -1)
			DrawPixel(-y,x,ColorDraw);
		else 
			DrawPixel(x,-y,ColorDraw);
		if(e>=0)
		{
			y = y+1;
			e = e-1;
		}
		x = x+1;
		e = e+m;
	}
}

//正负法画圆
void AnotherDrawCircle()
{
	// 線の長さ入力指示文字列の描画
	char Msg_R[] = "按 ↑ ↓ 来选择圆的半径(0-500)";
	char Msg_P[] = "在空白处点击圆心";
	char Msg_radius[5];
	int radius;
	int x1, y1;
	int Key;
	StrLen = strlen( Msg_R );
	StrWidth = GetDrawStringWidth( Msg_R , StrLen ) ;
	DrawBox( MSG_X-8-1 , MSG_Y-5 , MSG_X+StrWidth+7 , MSG_Y+50 , BarSC , TRUE ) ;
	DrawString( MSG_X , MSG_Y , Msg_R , BarBGC ) ;
	// 圆の長さ入力
	radius = DEFAULT_RADIUS;
	itoa(radius, Msg_radius , 10);
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_RETURN ) == 0 )
	{
		// キー入力取得
		Key = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;

		// 上を押していたら上に進む
		if( Key & PAD_INPUT_UP ) 
		{
			radius++ ;
			itoa(radius, Msg_radius , 10);
		}

		// 下を押していたら下に進む
		if( Key & PAD_INPUT_DOWN ) 
		{
			radius-- ;
			itoa(radius, Msg_radius , 10);
		}

		// プレイヤーを描画する
		DrawBox( MSG_X , MSG_Y+16 , MSG_X+StrWidth , MSG_Y+30, BarSC , TRUE ) ;
		DrawString( MSG_X , MSG_Y+16 , Msg_radius , BarBGC ) ;
		WaitTimer( 25 ) ;

		// 裏画面の内容を表画面に反映させる
		ScreenFlip() ;
	}
	DrawBox( MSG_X-8-1 , MSG_Y-5 , MSG_X+StrWidth+7 , MSG_Y+100 , Background , TRUE ) ;

	DrawString( MSG_X , MSG_Y+55 , Msg_P , BarSC ) ;
	ScreenFlip() ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x1 = MouseX;
		y1 = MouseY;
	}
	AnotherDrawCircle_M(x1,y1,radius);
}
//正负法画圆实现
void AnotherDrawCircle_M(int x1,int y1,int radius)
{
	int x,y,f,i;
	x = 0 ;
	y = 0 + radius ;
	f = 0;
	while(y>0)
	{
		for( i = 0; i < 4; i++ )
		{
			DrawPixel(x*Symmetry_X[i]+x1,y*Symmetry_Y[i]+y1,ColorDraw);
		}

		if( f > 0 )
		{
			f = f - 2 * y + 1 ;
			y-- ;
		}
		else
		{
			f = f + 2 * x + 1 ;
			x++ ;
		}
	}
	if(y == 0 ) 
	{
		for( i = 0; i < 4; i++ )
		{
			DrawPixel(x*Symmetry_X[i]+x1,y*Symmetry_Y[i]+y1,ColorDraw);
		}
	}
	DrawBox( MSG_X-8-1 , MSG_Y-5 , MSG_X+StrWidth+7 , MSG_Y+100 , Background , TRUE ) ;
}

//Bresenham画圆
void BresenhamCircle()
{
	
	char Msg_R[] = "按 ↑ ↓ 来选择圆的半径(0-500)";
	char Msg_P[] = "在空白处点击圆心";
	char Msg_radius[5];
	int radius;
	int x1, y1;
	int Key;
	StrLen = strlen( Msg_R );
	StrWidth = GetDrawStringWidth( Msg_R , StrLen ) ;
	DrawBox( MSG_X-8-1 , MSG_Y-5 , MSG_X+StrWidth+7 , MSG_Y+50 , BarSC , TRUE ) ;
	DrawString( MSG_X , MSG_Y , Msg_R , BarBGC ) ;
	// 圆の長さ入力
	radius = DEFAULT_RADIUS;
	itoa(radius, Msg_radius , 10);
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_RETURN ) == 0 )
	{
		// キー入力取得
		Key = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;

		// 上を押していたら上に進む
		if( Key & PAD_INPUT_UP ) 
		{
			radius++ ;
			itoa(radius, Msg_radius , 10);
		}

		// 下を押していたら下に進む
		if( Key & PAD_INPUT_DOWN ) 
		{
			radius-- ;
			itoa(radius, Msg_radius , 10);
		}

		// プレイヤーを描画する
		DrawBox( MSG_X , MSG_Y+16 , MSG_X+StrWidth , MSG_Y+30, BarSC , TRUE ) ;
		DrawString( MSG_X , MSG_Y+16 , Msg_radius , BarBGC ) ;
		WaitTimer( 25 ) ;

		// 裏画面の内容を表画面に反映させる
		ScreenFlip() ;
	}
	DrawBox( MSG_X-8-1 , MSG_Y-5 , MSG_X+StrWidth+7 , MSG_Y+100 , Background , TRUE ) ;

	DrawString( MSG_X , MSG_Y+55 , Msg_P , BarSC ) ;
	ScreenFlip() ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x1 = MouseX;
		y1 = MouseY;
	}
	BresenhamCircle_M(x1,y1,radius);
}
//Bresenham画圆实现
void BresenhamCircle_M(int x1,int y1,int radius)
{
	int x,y,d,i;
	x = 0;
	y = radius;
	d = 3 - 2 * radius;
	while(x<y)
	{
		for( i = 0; i < 4; i++ )
		{
			DrawPixel(x*Symmetry_X[i]+x1,y*Symmetry_Y[i]+y1,ColorDraw);
			DrawPixel(y*Symmetry_X[i]+x1,x*Symmetry_Y[i]+y1,ColorDraw);
		}
		if(d<0) 
			d = d + 4 * x + 6 ;
		else
		{
			d = d + 4 *( x-y ) + 10;
			y = y - 1;
		}
		x = x + 1;
	}
	if(y == 0 ) 
	{
		for( i = 0; i < 4; i++ )
		{
			DrawPixel(x*Symmetry_X[i]+x1,y*Symmetry_Y[i]+y1,ColorDraw);
			DrawPixel(y*Symmetry_X[i]+x1,x*Symmetry_Y[i]+y1,ColorDraw);
		}
	}
	DrawBox( MSG_X-8-1 , MSG_Y-5 , MSG_X+StrWidth+7 , MSG_Y+100 , Background , TRUE ) ;
}
/*
void antialiasedLine( )
{
	int x1 , y1 , x2 , y2 ;
	//	DrawLine(0,0,500,500,ColorDraw);
	x1 = x2 = y1 = y2 = 0 ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x1 = MouseX;
		y1 = MouseY;
	}
	//	debug(100);
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x2 = MouseX;
		y2 = MouseY;
	}
	//	debug(150);
	cg_antialiased_line(x1,y1,x2,y2);
}
*/
//反走样算法
/*
void cg_antialiased_line(int x1,int y1,int x2,int y2)  
{  
    int d, x, y, ax, ay, sx, sy, dx, dy, fx, fy, bk;  
      
    dx = x2-x1;  fx=ABS(dx);  ax = fx<<1;  sx = SGN(dx);  
    dy = y2-y1;  fy=ABS(dy);  ay = fy<<1;  sy = SGN(dy);  
      
    x = x1;  
    y = y1;  
  
    //// +    
    int incrE,incrNE;         
    double invDenom=1.0/(2.0*sqrt(1.0*dx*dx+dy*dy));  
    double temp=0;  
    double temp2=0;  
    //// +  
  
    if (ax>ay) {     // x dominant 
        d = ay-fx;  
        /// +  
        int two_v_dx=0;  
        incrE=(dy<<1);  
        incrNE=((dy-dx)<<2);  
        double two_dx_invDenom=2.0*dx*invDenom;  
        /// +  
        for (;;) {  
            /// +  
            temp=two_v_dx*invDenom;  
            temp2=sx>0?temp:-temp;  
            bk=getpixel(x,y);putpixel(x,y,LERP_COLOR(ColorDraw,bk,WCG_FILTER(temp)));  
            bk=getpixel(x,y+sy);putpixel(x,y+sy,LERP_COLOR(ColorDraw,bk,WCG_FILTER(two_dx_invDenom-temp2)));  
            bk=getpixel(x,y-sy);putpixel(x,y-sy,LERP_COLOR(ColorDraw,bk,WCG_FILTER(two_dx_invDenom+temp2)));  
  
            /// +  
            if (x==x2) return;  
            if (d>=0) {  
                two_v_dx=d-fx;   /// +  
                y += sy;  
                d -= ax;                  
            }  
            else  
                two_v_dx=d+fx;   /// +  
            x += sx;  
            d += ay;  
              
        }  
    }  
    else {          // y dominant 
        d = ax-fy;  
        /// +  
        int two_v_dy=0;  
        incrE=(dx<<1);  
        incrNE=((dx-dy)<<1);  
        double two_dy_invDenom=2.0*dy*invDenom;  
        /// +  
        for (;;) {  
            /// +  
            temp=two_v_dy*invDenom;  
            temp2=sy>0?temp:-temp;  
            bk=GetPixel(x,y);DrawPixel(x,y,ColorDraw);  
            bk=GetPixel(x+sx,y);DrawPixel(x+sx,y,LERP_COLOR(ColorDraw,bk,WCG_FILTER(two_dy_invDenom-temp2)));  
            bk=GetPixel(x-sx,y);DrawPixel(x-sx,y,LERP_COLOR(ColorDraw,bk,WCG_FILTER(two_dy_invDenom+temp2)));  
  
            /// +  
            if (y==y2) return;  
            if (d>=0) {  
                two_v_dy=d-fy;  /// +  
                x += sx;  
                d -= ay;  
                  
            }  
            else  
                two_v_dy=d+fy;   /// +  
            y += sy;  
            d += ax;          
              
        }  
    }  
} 
*/
void withVertexLineScan()
{
	int i,j,k,l;
	int points[MAX_POINT_NUM][2];
	int area[20];
	int num;
	int tmp;
	DrawString( windowStart+20 , OVERBOARD , "至多按下20个点！" , BarSC , FALSE ) ;
	ScreenFlip() ;
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		points[0][0] = MouseX;
		points[0][1] = MouseY;
	}
	points[1][0] = points[0][0];
	points[1][1] = points[0][1];
	DrawPixel(points[1][0],points[1][1], ColorDraw);
	ScreenFlip() ;
	for( i = 2; i < MAX_POINT_NUM; i++ )
	{
		WaitKey();
		GetMousePoint( &MouseX , &MouseY ) ;
		if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
		{
			points[0][0] = MouseX;
			points[0][1] = MouseY;
		}
		if((points[0][0]-points[1][0])*(points[0][0]-points[1][0])+(points[0][1]-points[1][1])*(points[0][1]-points[1][1]) <= 100)
		{
			points[i][0] = points[1][0];
			points[i][1] = points[1][1];
			break;
		}
		else
		{
			points[i][0] = points[0][0];
			points[i][1] = points[0][1];
		}
		DrawLine( points[i-1][0] , points[i-1][1] , points[i][0] , points[i][1] , ColorDraw , TRUE );
		ScreenFlip() ;
	}
	DrawLine( points[i-1][0] , points[i-1][1] , points[i][0] , points[i][1] , ColorDraw , TRUE );
	points[0][0] = points[i-1][0];
	points[0][1] = points[i-1][1];

	num = i;
		
	for( i = 0; i < windowWidth ; i++ )
	{
		k = 0;
		for( j = 1; j < num; j++ )
		{
			if(points[j][1] < i )
			{
				if( points[j+1][1] > i )
				{
					area[k] = (i - points[j][1])*(points[j+1][0] - points[j][0])/(points[j+1][1] - points[j][1]) + points[j][0];
					k++;
				}
				if( points[j-1][1] > i )
				{
					area[k] = (i - points[j][1])*(points[j-1][0] - points[j][0])/(points[j-1][1] - points[j][1]) + points[j][0];
					k++;
				}
			}
			else if( points[j][1] == i )
			{
				if( (points[j][1] - points[j+1][1])*(points[j][1] - points[j-1][1]) < 0 )
				{
					area[k] = points[j][0];
					k++;
				}
			}
		}
		//排序..
		for( j = 0; j < k-1; j++ )
		{
			for( l = 0; l < k-j-1; l++ )
			{
				if(area[l] > area[l+1])
				{
					tmp = area[l];
					area[l] = area[l+1];
					area[l+1] = tmp;
				}
			}
		}
		for( j = 0; j < k; j+=2 )
		{
			DrawLine( area[j], i, area[j+1] , i , ColorDraw , TRUE );
		}
	}
}
void seedFill()
{
	int x,y;
	int oldColor;
	DrawString( 20 , 50 , "点击需要填充的区域！" , BarSC , FALSE ) ;
	ScreenFlip();
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x = MouseX;
		y = MouseY;
	}
	DrawString( 20 , 50 , "点击需要填充的区域！" , Background , FALSE ) ;
	ScreenFlip();
	oldColor = ShowColorPad();
	errorFlag = 0;
	flood_fill_4(x,y,GetPixel( x , y ));
	ColorDraw = oldColor;
}

void flood_fill_4(int x, int y, int area_color)
{
	errorFlag++;
	if( GetPixel( x , y ) == area_color && errorFlag < 5000)
	{
		DrawPixel( x, y, ColorDraw ) ;
		if(ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_K ) == 0 )
			ScreenFlip() ;
		if(ProcessMessage() == 0 && !(CheckHitKey( KEY_INPUT_Q ) == 0) )
			return ;
		flood_fill_4( x-1 , y ,area_color);
		flood_fill_4( x , y+1 ,area_color);
		flood_fill_4( x+1 , y ,area_color);
		flood_fill_4( x , y-1 ,area_color);
	}
}

void lineScanSeedFill()
{
	int x,y;
	int oldColor;
	DrawString( 20 , 50 , "点击需要填充的区域！" , BarSC , FALSE ) ;
	ScreenFlip();
	WaitKey();
	GetMousePoint( &MouseX , &MouseY ) ;
	if( (( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0) && (MouseY > DRAWAREAUPPERy && MouseX > 0) )
	{
		x = MouseX;
		y = MouseY;
	}
	DrawString( 20 , 50 , "点击需要填充的区域！" , Background , FALSE ) ;
	ScreenFlip();
	oldColor = ShowColorPad();
	lineScanSeedFill_M(x,y,GetPixel( x , y ));
	ColorDraw = oldColor;
}
void set_stack_empty()
{
	seed_flag = 0;
}
bool stack_not_empty()
{
	if(seed_flag == -1)
		return false;
	return true;
}
void push(int x, int y)
{
	seed_flag++;
	seed_stack[seed_flag][0] = x;
	seed_stack[seed_flag][1] = y;
}
void pop( int * x, int * y )
{
	*x = seed_stack[seed_flag][0];
	*y = seed_stack[seed_flag][1];
	seed_flag--;
}

void lineScanSeedFill_M(int x, int y, int area_color)
{
	bool span_need_fill;
	int xleft,xright,savex;
	set_stack_empty();
	push(x,y);
	while(stack_not_empty())
	{
		pop(&x,&y);
		savex = x;
		while(GetPixel( x , y ) == area_color) //boundary_color
		{
			DrawPixel( x , y , ColorDraw );
			x += 1 ;
		}
		debug( x , y , 100 ) ;
		xright = x - 1 ;
		x = savex - 1 ;
		while( GetPixel( x , y ) == area_color )  //boundary_color
		{
			DrawPixel( x , y , ColorDraw );
			x -= 1;
		}
		xleft = x + 1 ;
		x = xleft;
		y = y + 1;
		while(x <= xright) 
		{
			span_need_fill = false;
			while( GetPixel( x, y ) == area_color )
			{
				span_need_fill = true;
				x += 1;
			}
			if( span_need_fill )
			{
				push( x - 1, y );
				span_need_fill = false;
			}
			while( GetPixel( x , y) != area_color && x <= xright ) x = x + 1;
		}
		x = xleft;
		y = y - 2;
		while(x <= xright) 
		{
			span_need_fill = false;
			while( GetPixel( x, y ) == area_color )
			{
				span_need_fill = true;
				x += 1;
			}
			if( span_need_fill )
			{
				push( x - 1, y );
				span_need_fill = false;
			}
			while( GetPixel( x , y) != area_color && x <= xright ) x = x + 1;
		}
		if(ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_K ) == 0 )
			ScreenFlip() ;
	}
}
//y代表输出的y坐标
void debug(int num1,int num2,int y)
{
	char StrBuf[ 128 ] , StrBuf2[ 32 ];
	DrawBox( MSG_X , y , MSG_X , y+32 , BGC , TRUE );
	lstrcpy( StrBuf , "座標 Ｘ" ) ; // 文字列"座標 Ｘ"をStrBufにコピー	
	itoa( num1 , StrBuf2 , 10 ) ; // MouseXの値を文字列にしてStrBuf2に格納
	lstrcat( StrBuf , StrBuf2 ) ; // StrBufの内容にStrBuf2の内容を付け足す
	lstrcat( StrBuf , "　Ｙ " ) ; // StrBufの内容に文字列"　Ｙ "を付け足す
	itoa( num2 , StrBuf2 , 10 ) ; // MouseYの値を文字列にしてStrBuf2に格納
	lstrcat( StrBuf , StrBuf2 ) ; // StrBufの内容にStrBuf2の内容を付け足す
	// 座標文字列を描く
	DrawString( MSG_X-200 , y , StrBuf , BarSC ) ;
}