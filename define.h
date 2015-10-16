//main cpp
int MouseX , MouseY ;
int BGC , BoxCr ;
#define windowStart 0
#define windowLength 1024
#define windowWidth 720
// divided from bar.h FirstBar
#define ColorChange 60
#define BarNum 10
//显示多少个功能条 (不得超过10个)

#define BarFrontSize 17
#define BarSizeX windowLength
#define BarSizeY 25
#define BarStringY 4
#define SecondBarY 28
#define SELECTEDLOWER 54
#define SELECTEDUPPER 27
//barY边界
#define OVERBOARD 51
int StrLen;
//BarBGC = Background Color, BarHGC = HoverGround Color, BarSC = String Color, BarHBC = HoverBoard Color
int	BarBGC = GetColor( 250 , 250 , 250 ) ,
	BarHGC = GetColor( 192 , 221 , 252 ) ,
	BarSC = GetColor( 0 , 0 , 0 ) ,
	BarHBC = GetColor ( 51 , 153 , 255) ,
	Background = GetColor ( 255 , 255 , 255);

int StrWidth;
int NextFunction;
int flag = 0;
void ShowDetailBar ( int SelectedBar, int SelectedBarStart);
void DrawBars(int x, int y);






// divided from bar.h SecondBar
#define SecondBarSpan 15
#define SecondBarY 30
int SecondBarPos;
int doFlag = 0;



// divided from function.h
void doFunction(int FirstBar , int SecondBar );


#define MAX_POINT_NUM 21
//divided from realize1_3.h
#define PAINTBOX 80
#define	COLORNUM 44
#define DRAWAREAUPPERx 51
#define DRAWAREAUPPERy 54
void DDALine( ) ;
int fx , fy , tx , ty ;
void debug( int num1 , int num2 , int y );
void AnotherDrawLine();
void BresenhamLine();
void AnotherDrawCircle();
void BresenhamCircle();
#define MSG_X windowLength-200
#define MSG_Y 200
int Symmetry_X[4] = {1,1,-1,-1};
int Symmetry_Y[4] = {1,-1,1,-1};
#define DEFAULT_RADIUS 10

void DDALine( );
void DDALine_M(int x1,int y1,int x2,int y2);
void AnotherDrawLine();
void AnotherDrawLine_M(int x1,int y1,int x2,int y2);
void BresenhamLine();
void BresenhamLine_M(int x1,int y1,int x2,int y2);
void AnotherDrawCircle();
void AnotherDrawCircle_M(int x1,int y1,int radius);
void BresenhamCircle();
void BresenhamCircle_M(int x1,int y1,int radius);
void withVertexLineScan();
void seedFill();
void debug(int y);
void flood_fill_4(int x, int y, int area_color);

void lineScanSeedFill();
void lineScanSeedFill_M(int x, int y, int area_color);
int seed_stack[3][2];
int seed_flag;
void set_stack_empty();
bool stack_not_empty();
void push(int x, int y);
void pop( int *x, int *y );
//全局画图用的颜色
int errorFlag;
int ColorDraw = GetColor ( 0 , 0 , 0);
int ShowColorPad();
//addition.h
#define PI 3.14159
void gameOne();
void turn_around();
//void video_input();
//#include "videoInput.h"
//#pragma comment(linker, "/videoInput.lib")
//devided from realize4_5.h
void GetRange(int *fx, int *fy, int *tx, int *ty);
void Sutherland_Cohen();
void Cyrus_Beck();
void LYD_Barsky();
void H_S_Polygon();
bool clipt(double r, double s);
void LYD_Barsky_M(double x[2], double y[2]);
int Cyrus_Beck_M(int k, double A[][2], double N[][2],double x[2], double y[2] , double * ts , double *te);
#define MOVE_BOX TRUE
#define MOVE_LINE FALSE
#define WAIT_TIME_MOUSE 200
int xl , yt , xr , yb ;
double te , ts ; 
void bike();


#define ROLLER_RADIUS 17 
#define BACK_ROLLER_RADIUS 10 
#define BIGGER_ROLLER_RADIUS 52 
#define MID_ROLLER_RADIUS 25
#define BACK_ROLLER_POS 76 
#define FRONT_ROLLER_POS 94 
#define SUPPORTER_POS 67 
#define FRONT_SUPPORTER 95 
