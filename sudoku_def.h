#ifndef SUDOKU_DEF
	#define SUDOKU_DEF
	#define BOARD_N	4
	#define BOARD_M	4
	
	typedef struct Candidate_ {
		int		Val;
		bool	Possible;
	} Candidate_t;

	typedef struct Board_ {
		int			Value;
		bool		InitValue;
		Candidate_t	Candidate[BOARD_N * BOARD_M];
	} Board_t;

	typedef struct ValNum_ {
		int			Value;
		int			Num;
	} ValNum_t;

	typedef struct Group_ {
		Board_t		BoardTable[BOARD_N * BOARD_M];
		ValNum_t	ValNumTable[BOARD_N * BOARD_M];
	} Group_t;

	typedef struct SudokuTable_ {
		Board_t		MainBoard[BOARD_N * BOARD_M][BOARD_N * BOARD_M];
		Group_t		Groups[BOARD_M * BOARD_N + BOARD_N * BOARD_M + BOARD_N * BOARD_M];
	} SudokuTable_t;
#endif
