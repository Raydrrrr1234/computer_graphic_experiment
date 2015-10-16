void doFunction(int FirstBar , int SecondBar )
{
	switch( FirstBar )
	{
	case 0: 
		{
			if( SecondBar == 0 )
				DxLib_End() ;
			if( SecondBar == 1 )
			{
				DrawBox( 0 , 0 , 1280 , 720 , BGC , TRUE ) ;
			}
			if( SecondBar == 2 )
			{
				ShowColorPad();
			}
			break;
		}
	case 1:
		{
			switch( SecondBar )
			{
			//case 0: DDA直线算法实现
			case 0:
				{	
					DDALine() ;
					break;
				}
			//case 1:正负法
			case 1:
				{
					AnotherDrawLine();
					break;
				}
			case 2:
				{
					BresenhamLine();
					break;
				}
			case 3:
				{
					AnotherDrawCircle();
					break;
				}
			case 4:
				{
					BresenhamCircle();
					break;
				}
			}
			ScreenFlip() ;
			break;
		}
	case 2:
		{
			switch( SecondBar )
			{
			case 0:
				{
					withVertexLineScan();
					break;
				}
			case 1:
				{
					seedFill();
					break;
				}
			case 2:
				{
					lineScanSeedFill();
					break;
				}
			case 3:
				{
					break;
				}
			case 4:
				{
					break;
				}
			}
			break;
		}
	case 3:
		{
			switch( SecondBar )
			{
			case 0:
				{
					Sutherland_Cohen();
					break;
				}
			case 1:
				{
					Cyrus_Beck();
					break;
				}
			case 2:
				{
					LYD_Barsky();
					break;
				}
			case 3:
				{
					H_S_Polygon();
					break;
				}
			}
			break;
		}
	case 4:
		{
			switch ( SecondBar )
			{
			case 0:
				{
					bike( );
					break;
				}
			}
			break;
		}
	case 9:
		{
			switch( SecondBar )
			{
			case 0:
				{
					SetBackgroundColor( 0 , 0 , 0 );
					gameOne();
					SetBackgroundColor( 255 , 255 , 255 );
					break;
				}
			case 1:
				{
					//video_input();
					turn_around();
					break;
				}
			case 2:
				{
					break;
				}
			case 3:
				{
					break;
				}
			case 4:
				{
					break;
				}
			}
			break;
		}
	}
	// 功能结束
	doFlag = 0;
}