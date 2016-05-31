#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int board[9][9];

void board_init(){
	int i,j;
	for(i = 0;i < 9;i++)
		for(j = 0;j < 9;j++)
			board[i][j] = 0;
}

void board_horizontal_line_print(){
	printf("+-------+-------+-------+\n");
}

int is_print_horizontal_position(int pos){
	if( (pos + 1) % 3 == 0 )
		return 1;
	else
		return 0;
}

void board_print(){
	int i,j;
	board_horizontal_line_print();
	for(i = 0;i < 9;i++){
		printf("|");
		for(j = 0;j < 9;j++){
			printf(" %d",board[i][j]);
			if(is_print_horizontal_position(j) == 1)
				printf(" |");
		}
		printf("\n");
		if(is_print_horizontal_position(i) == 1)
			board_horizontal_line_print();
	}
}

int main(int argc,char *argv[]){
	if(argc == 2){
		/* File Pointerを作成 */
		FILE *fp;
		/* ファイルオープン */
		if( (fp = fopen(argv[1],"r")) == NULL ){
			printf("ファイルのオープンに失敗しました。\n");
			exit(EXIT_FAILURE);
		}
		
		board_init();
		board_print();
		fclose(fp);
	}else if(argc == 1){
		printf("コマンドライン引数にボードファイルを指定してください。\n");
		exit(EXIT_FAILURE);
	}else{
		printf("コマンドライン引数が多すぎます。\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
