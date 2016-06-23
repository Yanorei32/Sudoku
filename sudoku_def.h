#ifndef SUDOKU_DEF
	#define SUDOKU_DEF
	#define BOARD_N	3
	#define BOARD_M	3
	
	typedef struct Group_ Group_t;
	typedef struct Cell_ Cell_t;

	struct Cell_ {
		Cell_t	*p_prev;
		int		Value;
#ifdef debug
		bool	InitValue;
		int x;
		int y;
#endif
		Group_t	*AssociatedGroups[3];
		bool	Candidate[BOARD_N * BOARD_M];
		int		CandidateCount;
		Cell_t	*p_next;
	};

	struct Group_ {
		Cell_t	*BoardTable[BOARD_N * BOARD_M];
		int NCandTable[BOARD_N * BOARD_M];
	};
	
	typedef struct SudokuTable_ {
		Cell_t	MainBoard[BOARD_N * BOARD_M][BOARD_N * BOARD_M];
		Group_t	Groups[BOARD_M * BOARD_N + BOARD_N * BOARD_M + BOARD_N * BOARD_M];
		Cell_t	*CanNumTable[BOARD_N * BOARD_M];
	} SudokuTable_t;
#endif
