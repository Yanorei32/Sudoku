/*\
| | *GCC Options
| |   -Wall -pedantic --std=C99
\*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sudoku_def.h"

SudokuTable_t SudokuTable;

void board_horizontal_line_print(){
	// ループ用変数
	int i,j;

	// 区切りを表示
	for(i = 0;i < BOARD_M;i++){
		printf("+-");
		for(j = 0;j < BOARD_N;j++){
			printf("--");
		}
	}
	printf("+\n");
}

bool is_print_horizontal_position(int pos,int box_size){
	// 区切りを表示すべき場所の場合は1を、表示すべきでない場所の場合は0をreturn
	if( (pos + 1) % box_size == 0 )
		return true;
	else
		return false;
}

void board_print(){
	// ループ用変数
	int i,j;

	// 横線を表示
	board_horizontal_line_print();

	// 縦の列でループを回す
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		// 最初の区切り線印字
		printf("|");

		// 横の列でループを回す
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			//空白をprint
			printf(" ");

			// 値を表示(ただし、値が0の場合は、「.」を表示)
			if(SudokuTable.MainBoard[i][j].Value != 0)
				printf("%d",SudokuTable.MainBoard[i][j].Value);
			else
				printf(".");

			// 区切りを表示すべき場所の場合表示
			if(is_print_horizontal_position(j,BOARD_N)) printf(" |");
		}

		printf("\n");
		
		// 区切りの横棒を表示すべき場所の場合表示
		if(is_print_horizontal_position(i,BOARD_M))
			board_horizontal_line_print();
	}
}

void board_group_init(){
	// ループ用変数
	int i,j,k,l;
	// Index保持用変数
	int grpidx,cellidx;

	// Index保持用変数初期化
	grpidx = cellidx = 0;

	// 横向きのグループ作成
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			// Cellをグループへ紐づけ
			SudokuTable.Groups[grpidx].BoardTable[j] = &SudokuTable.MainBoard[i][j];
			// グループをCellに紐づけ
			SudokuTable.MainBoard[i][j].AssociatedGroups[0] = &SudokuTable.Groups[grpidx];
		}
		// グループのインデックス更新
		grpidx++;
	}
	
	// 縦向きのグループ作成
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			// Cellをグループへ紐づけ
			SudokuTable.Groups[grpidx].BoardTable[j] = &SudokuTable.MainBoard[j][i];
			// グループをCellに紐づけ
			SudokuTable.MainBoard[j][i].AssociatedGroups[1] = &SudokuTable.Groups[grpidx];
		}
		// グループのインデックス更新
		grpidx++;
	}
	
	// 3x3マスのグループ作成
	
	// 3x3マスの縦方向のループ
	for(l = 0;l < BOARD_N * BOARD_M;l += BOARD_N){
		// 3x3マスの横方向のループ
		for(k = 0;k < BOARD_N * BOARD_M;k += BOARD_M){
			// グループの中の、マスのインデックス
			cellidx = 0;
			// 3x3マスの縦向きのループ
			for(i = 0;i < BOARD_M;i++){
				// 3x3マスの横向きのループ
				for(j = 0;j < BOARD_N;j++){
					// Cellをグループへ紐づけ
					SudokuTable.Groups[grpidx].BoardTable[cellidx] = &SudokuTable.MainBoard[l+i][k+j];
					// グループをCellに紐づけ
					SudokuTable.MainBoard[l+i][k+j].AssociatedGroups[2] = &SudokuTable.Groups[grpidx];
					// グループ内のマスのインデックスの更新
					cellidx++;
				}
			}
			// グループのインデックスの更新
			grpidx++;
		}
	}
}

void candidate_init(){
	// ループ用の変数
	int i,j,k;
	// セル単位でループ
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			// Candidate配列単位でループ
			for(k = 0;k < BOARD_N * BOARD_M;k++){
				SudokuTable.MainBoard[i][j].Candidate[k] = SudokuTable.MainBoard[i][j].Value == 0;
			}
		}
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

	// 読み出した値を一時保管する変数
	int cache_value;

	// ファイルオープン
	if( (fp = fopen(filename,"r")) == NULL ){
		printf("ファイルのオープンに失敗しました。\n");
		exit(EXIT_FAILURE);
	}

	// spirntfのフォーマットとなる文字列を生成。
	sprintf(sprintf_format,"%%%ds%%*[^\n]",BOARD_N * BOARD_M);

	// %で始まる最初の行を読み飛ばす。
	fscanf(fp,"%*[^\n]");

	// 1行ずつ読み込む
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		// データの読み込み/エラーチェックを行う
		if(fscanf(fp,sprintf_format,buf) == EOF){
			// EOFの場合、必要行数がないことを報告し、終了
			printf("sudoku_def.hで、指定された量だけのデータが、ボードファイルに存在しません。\n");
			exit(EXIT_FAILURE);
		}
		// 一文字ずつ読み込む
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			if(buf[j] == '.'){
				// .の場合、0を代入
				cache_value = 0;
			}else if('0' <= buf[j] && buf[j] <= '9'){
				// 0-9の場合、0を引いた値を代入
				cache_value = buf[j] - '0';
			}else if('a' <= buf[j] && buf[j] <= 'z'){
				cache_value = buf[j] - 'a' + 10;
			}else if('A' <= buf[j] && buf[j] <= 'Z'){
				cache_value = buf[j] - 'A' + 10;
			}else if(buf[j] == '\0'){
				// NULL文字の場合、文字が足りないことを報告し、終了
				printf("sudoku_def.hで、指定された量だけのデータが、ボードファイルに存在しません。\n");
				exit(EXIT_FAILURE);
			}else{
				// それ以外の場合、不正な値が入力されたことを報告し、終了
				printf("不正な値が入力されました。%d,%d,%d\n",buf[j],i,j);
				exit(EXIT_FAILURE);
			}

			//正常な値かを確認
			if(0 <= cache_value && cache_value <= BOARD_N * BOARD_M){
				// 正常な値だった場合は代入
				SudokuTable.MainBoard[i][j].Value = cache_value;
				// 初期値であるフラグを立てる(必要性不明)
				SudokuTable.MainBoard[i][j].InitValue = true;
			}else{
				// それ以外の場合、不正な値が入力されたことを報告し、終了
				printf("不正な範囲の値が入力されました。%d,%d,%d\n",buf[j],i,j);
				exit(EXIT_FAILURE);
			}
		}
	}

	// ファイルをクローズ
	fclose(fp);
}

void board_size_valid(){
	// 2未満の場合、数独が成り立たないため、弾く。
	if(BOARD_N < 2 || BOARD_M < 2){
		printf("ヘッダファイルのボード指定サイズが2未満です。\n");
		exit(EXIT_FAILURE);
	}
}

void candidate_set_by_cell(Cell_t **set_cell,Cell_t **min_cand_cell,int *min_cand_cell_count){
	// ループ用変数
	int i,j,k;
	// カウンター
	int candidate_counter;
	
	// カウンタを最大値で初期化
	candidate_counter = BOARD_N * BOARD_M;
	
	// 探す値の決定
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		(*(*set_cell)).Candidate[i] = (*(*set_cell)).Value == 0;
		// AssociatedGroups単位でのループ
		for(j = 0;j < 3;j++){
			// グループ内でのCellループ
			for(k = 0;k < BOARD_N * BOARD_M;k++){
				// 探している値と等しいかを確認
				if((*(*(*(*set_cell)).AssociatedGroups[j]).BoardTable[k]).Value == i+1){
					// カウンタの値を下げる
					candidate_counter --;
					// flagも下げる
					(*(*set_cell)).Candidate[i] = false;
					// ループを2段抜ける
					break;
				}
			}
			// 2つめのループも抜ける
			if((*(*set_cell)).Candidate[i] == false) break;
		}
	}
	// 今までの値よりもCandidateCount小さい場合は、それを代入
	if(candidate_counter < *min_cand_cell_count){
		*min_cand_cell = &(*(*set_cell));
		*min_cand_cell_count = candidate_counter;
	}
}

void candidate_set(Cell_t **min_cand_cell,int *min_cand_cell_count){
	// ループ用変数
	int i,j,k,l,m;
	// カウント用内部変数
	int candidate_counter;

	// min_cand_cell_countを最大値(BOARD_N * BOARD_M)で初期化
	*min_cand_cell_count = BOARD_N * BOARD_M;
	*min_cand_cell = NULL;
	// Cell単位でループ
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			// マスに何も入っていない場合は論外なので条件分岐で外す。
			if(SudokuTable.MainBoard[i][j].Value == 0){
				// CandidateCounterの初期化
				candidate_counter = BOARD_N * BOARD_M ;
				// 探すものの決定(探すときは+1必須)
				for(k = 0;k < BOARD_N * BOARD_M;k++){
					// AssociatedGroups単位でのループ
					for(l = 0;l < 3;l++){
						// グループ内の、Cellループ
						for(m = 0;m < BOARD_N * BOARD_M;m++){
							// 探している値と等しいかを確認。
							if((*(*SudokuTable.MainBoard[i][j].AssociatedGroups[l]).BoardTable[m]).Value == k+1){
								// 等しい場合は、candidate_counterを減らし、2段階ループを抜ける。
								candidate_counter --;
								SudokuTable.MainBoard[i][j].Candidate[k] = false;
								break;
							}
						}
						// ループを抜けるための条件分岐
						if(SudokuTable.MainBoard[i][j].Candidate[k] == false) break;
					}
				}
				// candidate_counterの値が、min_cand_cell_countよりも小さい場合は、上書き。
				if(*min_cand_cell_count > candidate_counter){
					*min_cand_cell_count = candidate_counter;
					*min_cand_cell = &SudokuTable.MainBoard[i][j];
				}
			}
		}
	}
}

bool is_board_complete(){
	int i,j;
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		for(j = 0;j < BOARD_N * BOARD_M;j++){
			if(SudokuTable.MainBoard[i][j].Value == 0){
				return false;
			}
		}
	}
	return true;
}

bool solve(){
	// CellのCandidate用の変数
	int		min_cand_cell_count;
	Cell_t	*min_cand_cell;
	
	// ループ用変数
	int i;
	
	// CellのCandidateを初期化
	candidate_init();
	candidate_set(&min_cand_cell,&min_cand_cell_count);
	if(is_board_complete()){
		return true;
	}
	if(min_cand_cell_count == 0){
		return false;
	}
	for(i = 0;i < BOARD_N * BOARD_M;i++){
		if((*min_cand_cell).Candidate[i]){
			(*min_cand_cell).Value = i + 1;
			if(solve() == false){
				(*min_cand_cell).Value = 0;
			}else{
				return true;
			}
			candidate_set_by_cell(&min_cand_cell,&min_cand_cell,&min_cand_cell_count);
		}
	}
	return false;
}

int main(int argc,char *argv[]){
	// ボードのサイズを確認
	board_size_valid();

	// 引数の量を確認
	if(argc == 2){
		// ボードの読み込み
		board_read(argv[1]);

		// ボードのAssociatedGroupsやGroupsの初期化
		board_group_init();

		// 問題の表示
		board_print();

		// 再起呼び出し
		solve();
		
		board_print();
		printf("complete\n");
	}else if(argc == 1){
		printf("コマンドライン引数にボードファイルを指定してください。\n");
		exit(EXIT_FAILURE);
	}else{
		printf("コマンドライン引数が多すぎます。\n");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

