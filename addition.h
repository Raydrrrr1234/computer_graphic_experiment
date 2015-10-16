// ショットとパーティクルの最大数
#define MAX_SHOT	4
#define MAX_SPARK	800

// ショットデータ型
typedef struct tagSHOT
{
	int Valid ;	// このデータが使用中か、フラグ
	int X ,Y ;	// ショットの位置
} SHOT ;

// 火花データ型
typedef struct tagSPARK
{
	int Valid ;	// このデータが使用中か、フラグ
	int X ,Y ;	// 火花の位置
	int Sx , Sy ;	// 火花の移動力
	int G ;	// 火花の重さ
	int Bright ;	// 火花の明るさ
} SPARK ;

int PlayerX , PlayerY ;	// プレイヤーの位置
SHOT Shot[ MAX_SHOT ] ;	// ショットデータ
SPARK Spark[ MAX_SPARK ] ;	// 火花データ


void CreateSpark( int x , int y  ) ;	// 火花を出す処理
void MoveSpark( void ) ;	// 火花移動処理
void CreateShot( void ) ;	// ショットを撃つ処理
void MoveShot( void ) ;	// ショットの移動処理

void gameOne()
{
	int Key = 0 ;
	int OldKey = 0 ;	// 前のキー入力状態
	int i , j ;
	// 描画先画面を裏画面にセット
	SetDrawScreen( DX_SCREEN_BACK ) ;

	// プレイヤーの初期位置をセット
	PlayerX = 320 ;
	PlayerY = 400 ;

	// ショットの存在を初期化する
	for( i = 0 ; i < MAX_SHOT ; i ++ )
		Shot[ i ].Valid = 0 ;

	// 火花の存在を初期化する
	for( i = 0 ; i < MAX_SPARK ; i ++ )
		Spark[ i ].Valid = 0 ;

	// ループ
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_Q ) == 0 )
	{
		//提示信息
		
		// キー入力取得
		OldKey = Key ;
		Key = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;

		if( Key & PAD_INPUT_RIGHT ) PlayerX += 3 ;	// 右を押していたら右に進む
		if( Key & PAD_INPUT_LEFT ) PlayerX -= 3 ;	// 左を押していたら左に進む

		// ショットの移動処理
		MoveShot() ;

		// 火花の移動処理
		MoveSpark() ;

		// ショットボタンを押していたらショットを出す
		if( ( Key & ~OldKey ) & PAD_INPUT_A ) CreateShot() ;
 
		// 画面を初期化する
		ClearDrawScreen() ;
		DrawString( 20 , 50 , "按下Q键退出 左右移动 Z射击" , Background , FALSE ) ;
		// プレイヤーを描画する
		DrawBox( PlayerX , PlayerY ,PlayerX + 48 , PlayerY + 48 , GetColor( 255 , 0 , 0 ) , TRUE ) ;

		// ショットを描画する
		for( j = 0 ; j < MAX_SHOT ; j ++ )
		{
			// ショットデータが有効な時のみ描画
			if( Shot[ j ].Valid == 1 )
				DrawBox( Shot[j].X , Shot[j].Y , Shot[j].X + 16 , Shot[j].Y + 16 ,
						 GetColor( 255 , 0 , 0 ) , TRUE ) ;
		}

		// 火花を描画する
		for( j = 0 ; j < MAX_SPARK ; j ++ )
		{
			// 火花データが有効な時のみ描画
			if( Spark[ j ].Valid == 1 )
				DrawPixel( Spark[j].X / 100 , Spark[j].Y / 100 , 
					GetColor( Spark[j].Bright , Spark[j].Bright , Spark[j].Bright ) ) ;

		}

		// 裏画面の内容を表画面に反映させる
		ScreenFlip() ;
	}
	DrawBox( 0 , 0 , 1280 , 720 , BGC , TRUE );
}
// 火花を出す処理
void CreateSpark( int x , int y  )
{
	int i ;

	// 使われていない火花データを探す
	for( i = 0 ; i < MAX_SPARK ; i ++ )
	{
		if( Spark[ i ].Valid == 0 ) break ;
	}

	// もし使われていない火花データがあったら火花を出す
	if( i != MAX_SPARK )
	{
		// 火花の位置を設定
		Spark[ i ].X = x * 100 ;
		Spark[ i ].Y = y * 100 ;

		// 移動力を設定
		Spark[ i ].Sx = GetRand( 1000 ) - 500 ;
		Spark[ i ].Sy = -GetRand( 500 )  ; 

		// 火花の重さをセット
		Spark[ i ].G = GetRand( 10 ) ;

		// 火花の明るさセット
		Spark[ i ].Bright = 255 ; 

		// 火花データを使用中にセット
		Spark[ i ].Valid = 1 ;
	}
}

// 火花移動処理
void MoveSpark( void )
{
	int i ;

	// 火花の移動処理
	for( i = 0 ; i < MAX_SPARK ; i ++ )
	{
		// 火花データが無効だったらスキップ
		if( Spark[ i ].Valid == 0 ) continue ;

		// 位置を移動力に応じてずらす
		Spark[ i ].Y += Spark[ i ].Sy ;
		Spark[ i ].X += Spark[ i ].Sx ;

		// 移動力を変更
		Spark[ i ].Sy += Spark[ i ].G ;

		// 火花の明るさを下げる
		Spark[ i ].Bright -= 2 ;

		// 火花の明るさが０以下になったら火花データを無効にする
		if( Spark[ i ].Bright < 0 ) Spark[ i ].Valid = 0 ;
	}
}

// ショットを撃つ処理
void CreateShot( void )
{
	int i ;

	// 使われていないショットデータを探す
	for( i = 0 ; i < MAX_SHOT ; i ++ )
	{
		if( Shot[ i ].Valid == 0 ) break ;
	}
		
	// もし使われていないショットデータがあったらショットを出す
	if( i != MAX_SHOT )
	{
		// ショットの位置を設定
		Shot[ i ].X = PlayerX + 16 ;
		Shot[ i ].Y = PlayerY ;

		// ショットデータを使用中にセット
		Shot[ i ].Valid = 1 ;
	}
}

// ショットの移動処理
void MoveShot( void )
{
	int i , j , R ;

	// ショットの移動処理
	for( i = 0 ; i < MAX_SHOT ; i ++ )
	{
		// ショットデータが無効だったらスキップ
		if( Shot[ i ].Valid == 0 ) continue ;

		// 位置を上にずらす
		Shot[ i ].Y -= 8 ;

		// 画面外に出ていたら火花を出したあとショットデータを無効にする
		if( Shot[ i ].Y < 150 )
		{
			// 火花を出す数をセット
			R = GetRand( 60 ) ; 
			for( j = 0 ; j < R ; j ++ )
			{
				// 火花を生成
				CreateSpark( Shot[ i ].X + 8 , Shot[ i ].Y + 8 ) ;
			}

			// ショットデータを無効にする
			Shot[ i ].Valid = 0 ;
		}
	}
}
void turn_around()
{
	int x,y,xd,yd;
	// 最初の座標を設定
	x = 100 ;
	y = 0 ;

	// ＥＳＣキーが押されるまでループ
	while(ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_Q ) == 0 )
	{
		// 画面をクリア
		ClearDrawScreen() ;

		// 座標を3度回転してやる
		xd = x * cos( PI / 180 * 3 ) - y * sin( PI / 180 * 3 ) ;
		yd = x * sin( PI / 180 * 3 ) + y * cos( PI / 180 * 3 ) ;

		// 回転後の座標を保存
		x = xd ;
		y = yd ;

		// 円を描画(画面の原点は画面の一番左上にあるので、無理やり画面の
		// 中心に原点があるかのように座標を移動させる)
		DrawCircle( x + 320, y + 240, 16, GetColor( 255, 0, 0 ), TRUE ) ;

		// 画面を表示
		ScreenFlip() ;

	}
}