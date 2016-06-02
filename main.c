/*\
| | *GCC Options
| |   -Wall -pedantic --std=C99
\*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku_def.h"


int board[BOARD_N * BOARD_M][BOARD_M * BOARD_N];

void board_horizontal_line_print(){
	int i = 0;

	// 区切りを表示
	printf("+-------+-------+-------+");



	printf("\n");
}

bool is_print_horizontal_position(int pos){
	// 区切りを表示すべき場所の場合は1を、表示すべきでない場所の場合は0をreturn
	if( (pos + 1) % BOARD_N == 0 )
		return true;
	else
		return false;
}

void board_print(){
	int i,j;
	board_horizontal_line_print();
	for(i = 0;i < BOARD_N * BOARD_N;i++){
		printf("|");
		for(j = 0;j < BOARD_N * BOARD_N;j++){
			if(board[i][j] != 0)
				printf(" %d",board[i][j]);
			else
				printf(" .");

			if(is_print_horizontal_position(j)) printf(" |");
		}
		printf("\n");
		if(is_print_horizontal_position(i))
			board_horizontal_line_print();
	}
}

void board_read(const char *filename){
	// File Pointerを作成
	FILE *fp;
	// 読みだしたデータの保管用
	char buf[BOARD_N * BOARD_M + 1];
	// ループ用の変数
	int i,j;
	// sprintfフォーマット保管用
	char sprintf_format[16];

	// ファイルオープン
	if( (fp = fopen(filename,"r")) == NULL ){
		printf("ファイルのオープンに失敗しました。\n");
		exit(EXIT_FAILURE);
	}

	// spirntfのフォーマットとなる文字列を生成。
	sprintf(sprintf_format,"%%%ds%%*[^\\n]",BOARD_N * BOARD_M);

	// %で始まる最初の行を読み飛ばす。
	fscanf(fp,"%*[^\n]");

	// 1行ずつ読み込む
	for(i = 0;(fscanf(fp,sprintf_format,buf)) != EOF;i++){
		// 一文字ずつ読み込む
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			if(buf[j] == '.'){
				board[i][j] = 0;
			}else if('0' <= buf[j] && buf[j] <= '9'){
				board[i][j] = buf[j] - '0';
			}else{
				printf("不正な値が入力されました。%d,%d,%d\n",buf[j],i,j);
				exit(EXIT_FAILURE);
			}
		}
	}
	fclose(fp);
}

int main(int argc,char *argv[]){
	if(argc == 2){
		board_read(argv[1]);
		board_print();
	}else if(argc == 1){
		printf("コマンドライン引数にボードファイルを指定してください。\n");
		exit(EXIT_FAILURE);
	}else{
		printf("コマンドライン引数が多すぎます。\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}