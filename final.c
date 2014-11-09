/*
最終課題
344153
井本　壮平
*/

#include <stdio.h>
#include <stdlib.h>
#include <eggx.h>
#include<time.h>
#include<math.h>

int win;//ウインドウの大きさ
double xc=-200.0; //除雪車の基準x座標
double yc=1.0;//除雪車の振動
double y=0.0;//雪の高さ
double bigsnow_x[50], bigsnow_y[50]; //大きい雪の座標
double minisnow_x[50], minisnow_y[50]; //小さい雪の座標
double smoke_x[10], smoke_y[10], smoke_r[10];//煙

//座標の初期化
void shokika(){
	int i;
	//座標の初期化
	for(i=0;i<=50;i++){
		bigsnow_x[i]=0.0;
		bigsnow_y[i]=0.0;
		
		minisnow_x[i]=0.0;
		minisnow_y[i]=0.0;
	}
	for(i=0;i<=10;i++){
		smoke_x[i]=0.0;
		smoke_y[i]=0.0;
		smoke_r[i]=0.0;
	}
	//大きい雪の初期座標
	for(i=0;i<=50;i++){
		bigsnow_x[i]=(double)(rand() % 800);
		bigsnow_y[i]=(double)(rand() % 600);
	}
	//小さい雪の初期座標
	for(i=0;i<50;i++){
		minisnow_x[i]=(double)(rand() % 800);
		minisnow_y[i]=(double)(rand() % 600);
	}
	//煙の座標と半径
	for(i=0;i<=10;i++){
		smoke_x[i]=0.0;
		smoke_y[i]=140.0;
		smoke_r[i]=4.0;
	}
}

//大きい雪
void big_snow(int random){
	double w=6.0;//雪の大きさ
	int i;
	int n=0;
	for(i=0; i<50; i++){
		newpen(win,1);
		fillcirc(win, bigsnow_x[i], bigsnow_y[i], w, w);
		bigsnow_x[i] += 0.1*sin(n+M_PI / 360);
		bigsnow_y[i] -= w/3.0;
		n += 10;
		if(bigsnow_y[i] < 0){
			bigsnow_x[i] = (double)(rand() % 800);
			bigsnow_y[i] = 600;
		}
	}
}

//小さい雪
void small_snow(int random){
	double w=3.0;//雪の大きさ
	int i;
	int n=0;
	for(i=0; i<50; i++){
		newpen(win,9);
		fillcirc(win, minisnow_x[i], minisnow_y[i], w, w);
		minisnow_x[i] += 0.05*sin(n+M_PI / 360);
		minisnow_y[i] -= w/3.0;
		n += 10;
		if(minisnow_y[i] < 0){
			minisnow_x[i] = (double)(rand() % 800);
			minisnow_y[i] = 600;
		}
	}
}
void smoke(){
	int i;
	for(i=0; i<10; i++){
		newrgbcolor(win, 110, 110, 110);
		fillcirc(win, smoke_x[i]+20, smoke_y[i], smoke_r[i], smoke_r[i]);
		smoke_x[i] = xc;
		smoke_y[i] += 2.0;
		smoke_r[i] += 5.0;
		//printf("%lf\n", smoke_x[1]);
		if(smoke_r[i] > 15.0) {
			smoke_y[i]=140.0;
			smoke_r[i]=3.0;
		}
	}
}

//小さめの木
void mini_tree(){
	//1つ目の木の葉っぱ部分
	double leaf_x1[3]={110.0, 115.0, 120.0};
	double leaf_x2[3]={105.0, 115.0, 125.0};
	double leaf_x3[3]={100.0, 115.0, 130.0}; 
	//2つ目の木の葉っぱ部分
	double leaf_x4[3]={310.0, 315.0, 320.0};
	double leaf_x5[3]={305.0, 315.0, 325.0};
	double leaf_x6[3]={300.0, 315.0, 330.0};
	//3つ目の木の葉っぱ部分
	double leaf_x7[3]={510.0, 515.0, 520.0};
	double leaf_x8[3]={505.0, 515.0, 525.0};
	double leaf_x9[3]={500.0, 515.0, 530.0};
	//4つ目の木の葉っぱ部分
	double leaf_x10[3]={710.0, 715.0, 720.0};
	double leaf_x11[3]={705.0, 715.0, 725.0};
	double leaf_x12[3]={700.0, 715.0, 730.0};
	//葉っぱの部分のy座標
	double leaf_y1[3]={295, 300, 295};
	double leaf_y2[3]={285, 295, 285};
	double leaf_y3[3]={270, 285, 270};
	//葉っぱの描画
	newrgbcolor(win, 0, 100, 0);
	fillpoly(win, leaf_x1, leaf_y1, 3, 0);
	fillpoly(win, leaf_x2, leaf_y2, 3, 0);
	fillpoly(win, leaf_x3, leaf_y3, 3, 0);
	fillpoly(win, leaf_x4, leaf_y1, 3, 0);
	fillpoly(win, leaf_x5, leaf_y2, 3, 0);
	fillpoly(win, leaf_x6, leaf_y3, 3, 0);
	fillpoly(win, leaf_x7, leaf_y1, 3, 0);
	fillpoly(win, leaf_x8, leaf_y2, 3, 0);
	fillpoly(win, leaf_x9, leaf_y3, 3, 0);
	fillpoly(win, leaf_x10, leaf_y1, 3, 0);
	fillpoly(win, leaf_x11, leaf_y2, 3, 0);
	fillpoly(win, leaf_x12, leaf_y3, 3, 0);
	//幹の部分の描画
	newrgbcolor(win,139, 69, 0);
	fillrect(win,110, 250, 10, 20);
	fillrect(win,310, 250, 10, 20);
	fillrect(win,510, 250, 10, 20);
	fillrect(win,710, 250, 10, 20);
}

//大きめの木
void big_tree(){
	//1つ目の木の葉っぱ部分
	double leaf_x1[3]={170.0, 180.0, 190.0};
	double leaf_x2[3]={160.0, 180.0, 200.0};
	double leaf_x3[3]={150.0, 180.0, 210.0}; 
	//2つ目の木の葉っぱ部分
	double leaf_x4[3]={370.0, 380.0, 390.0};
	double leaf_x5[3]={360.0, 380.0, 400.0};
	double leaf_x6[3]={350.0, 380.0, 410.0}; 
	//3つ目の木の葉っぱ部分
	double leaf_x7[3]={570.0, 580.0, 590.0};
	double leaf_x8[3]={560.0, 580.0, 600.0};
	double leaf_x9[3]={550.0, 580.0, 610.0}; 
	//葉っぱの部分のy座標
	double leaf_y1[3]={240.0, 250.0, 240.0};
	double leaf_y2[3]={220.0, 240.0, 220.0};
	double leaf_y3[3]={190.0, 220.0, 190.0};
	//葉っぱの描画
	newpen(win, 3);
	fillpoly(win, leaf_x1, leaf_y1, 3, 0);
	fillpoly(win, leaf_x2, leaf_y2, 3, 0);
	fillpoly(win, leaf_x3, leaf_y3, 3, 0);
	fillpoly(win, leaf_x4, leaf_y1, 3, 0);
	fillpoly(win, leaf_x5, leaf_y2, 3, 0);
	fillpoly(win, leaf_x6, leaf_y3, 3, 0);
	fillpoly(win, leaf_x7, leaf_y1, 3, 0);
	fillpoly(win, leaf_x8, leaf_y2, 3, 0);
	fillpoly(win, leaf_x9, leaf_y3, 3, 0);
	//幹の部分の描画
	newrgbcolor(win, 255, 165, 79);
	fillrect(win,170, 150, 20, 40);
	fillrect(win,370, 150, 20, 40);
	fillrect(win,570, 150, 20, 40);
}

//除雪車
void josetu(){
	//車体（胴体）
	double j_x1[4]={xc, xc, xc+130, xc+150};
	double j_y1[4]={20+yc, 100+yc, 100+yc, 20+yc};
	newrgbcolor(win,255, 165, 0);
	fillpoly(win, j_x1, j_y1, 4, 0 );
	
	//車体（窓）
	double j_x2[4]={xc+60, xc+60, xc+90, xc+120};
	double j_y2[4]={100+yc, 140+yc, 140+yc, 100+yc};
	newrgbcolor(win,255, 165, 0);
	fillpoly(win, j_x2, j_y2, 4, 0 );
	
	//車体（窓ガラス）
	double j_x3[4]={xc+70, xc+70, xc+95, xc+120};
	double j_y3[4]={100+yc, 130+yc, 130+yc, 100+yc};
	newrgbcolor(win, 175, 238, 238);
	fillpoly(win, j_x3, j_y3, 4, 0);
	
	//煙突
	double j_x4[4]={ xc+10, xc+10, xc+30, xc+30};
	double j_y4[4]={ 100+yc, 130+yc, 150+yc, 100+yc};
	newrgbcolor(win, 176, 176, 176);
	fillpoly(win, j_x4, j_y4, 4, 0);
	
	//アーム部分
	newrgbcolor(win,255, 165, 0);
	fillrect(win, xc+120, 60, 50, 10);
	fillrect(win, xc+170, 0, 10, 110);
	fillrect(win, xc+180, 0, 20, 10);
	newrgbcolor(win, 220,220,220);
	fillcirc(win, xc+120, 60, 5, 5);
	//タイヤ
	newrgbcolor(win, 33, 33, 33);
	fillcirc(win, xc+10, 40, 40, 40);
	fillcirc(win, xc+120, 25, 25, 25);
	newpen(win, 9);
	fillcirc(win, xc+10, 40, 20, 20);
	fillcirc(win, xc+120, 25, 14, 14);
}

//積雪
void sekisetu(){
	newpen(win, 1);
	fillrect(win, xc+180, 0, 820-xc, y);
}

//白夜
void byakuya(int mile){
	double feet=0.0;
	int r=360;
	
	feet=r*sin( M_PI*mile/1000 - 100);
	newrgbcolor(win, 255, 255, 0);
	fillcirc(win, mile, feet+200, 40, 40);
}

int main(void){  
	int random;//乱数
	srand(time(0));
	random = rand();
	
	int r=0,g=0,b=0; //背景色のグラデーション変数
	int count=0; //回った回数のカウント
	double mile=0;
	shokika();
	
	win=gopen(800,600);     // 描画ウィンドウを開く
	winname(win, "final");  // 名前をつける
	
	while(1){
		layer(win,0,1);
		newrgbcolor(win, r, g, b);
		fillrect(win, 0, 250, 800, 350);
		byakuya(mile);
		newpen(win, 0);
		fillrect(win, 0, 0, 800, 250);
		
		mini_tree();//奥行きをだしたいのでわざと描く順番をずらす
		copylayer(win,1,0);
		layer(win,0,1);
		small_snow(random);//奥行きをだしたいのでわざと描く順番をずらす
		big_tree();//奥行きをだしたいのでわざと描く順番をずらす
		
		/******積雪と除雪******/
		sekisetu();
		y+=0.2;
		if(y>=70){
			xc+=4;
			yc*=(-1);
			josetu();
			smoke();
		}
		if(xc >= 820){
			y=0;
			xc=-200;
		}
		/*******************/
	
		big_snow(random);//奥行きをだしたいのでわざと描く順番をずらす
		copylayer(win,1,0);
		
		/********背景の変化********/
		count+=1;
		mile+=0.5;
		if(mile > 900) mile=-50; 
		if(count >=0 && count <=600){
			r=0;
			g=0;
			b=0;
		}
		else if(count > 600 && count <=1200 && count%5==0 ){
			if(b==255){
				r=0;
				g=191;
				b=255;
			}
			b+=2;
		}
		else if(count > 1200 && count <= 1800 && count%5==0){
			if(r==255){
				r=255;
				g=127; 
				b=0;
			}
			r+=2;
			g+=1;
			b-=1;
		}
		else if(count > 1800 && count <= 2100 && count%5==0){
			r-=1;
			g-=1;
			b-=1;
		}
		else if(count > 2100 && count < 2400 && count%5==0){
			r-=5;
			g-=5;
			b-=1;
		}
		else if(count ==2400) count=0;
		/************************/
		msleep(30);
		gclr(win);
	}
}
//終わらないプログラム
