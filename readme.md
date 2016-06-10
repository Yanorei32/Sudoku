#Sudoku - 数独

ここでは、変数等の扱いに関して、書く。
突起がない限り、`BOARD_N`、`BOARD_M`はそれぞれ`3`の場合である。

##`BOARD_N` / `BOARD_M`に関して

`BOARD_N`は、小さいBOXの横向きの数。  
`BOARD_M`は、小さいBOXの縦向きの数となる。  
これは、印字の際もファイル読み込みの際も守られる。


##`Cell_t`に関して

`Cell_t`は以下のような構造になっている。  
サイズは、`BOARD_N * BOARD_M`で決まる。

<table>
	<tr>
		<td><code>[0][0]</code></td>
		<td><code>[0][1]</code></td>
		<td><code>[0][2]</code></td>
		<td><code>[0][3]</code></td>
		<td><code>[0][4]</code></td>
		<td><code>[0][5]</code></td>
		<td><code>[0][6]</code></td>
		<td><code>[0][7]</code></td>
		<td><code>[0][8]</code></td>
	</tr>
	<tr>
		<td><code>[1][0]</code></td>
		<td><code>[1][1]</code></td>
		<td><code>[1][2]</code></td>
		<td><code>[1][3]</code></td>
		<td><code>[1][4]</code></td>
		<td><code>[1][5]</code></td>
		<td><code>[1][6]</code></td>
		<td><code>[1][7]</code></td>
		<td><code>[1][8]</code></td>
	</tr>
	<tr>
		<td><code>[2][0]</code></td>
		<td><code>[2][1]</code></td>
		<td><code>[2][2]</code></td>
		<td><code>[2][3]</code></td>
		<td><code>[2][4]</code></td>
		<td><code>[2][5]</code></td>
		<td><code>[2][6]</code></td>
		<td><code>[2][7]</code></td>
		<td><code>[2][8]</code></td>
	</tr>
	<tr>
		<td><code>[3][0]</code></td>
		<td><code>[3][1]</code></td>
		<td><code>[3][2]</code></td>
		<td><code>[3][3]</code></td>
		<td><code>[3][4]</code></td>
		<td><code>[3][5]</code></td>
		<td><code>[3][6]</code></td>
		<td><code>[3][7]</code></td>
		<td><code>[3][8]</code></td>
	</tr>
	<tr>
		<td><code>[4][0]</code></td>
		<td><code>[4][1]</code></td>
		<td><code>[4][2]</code></td>
		<td><code>[4][3]</code></td>
		<td><code>[4][4]</code></td>
		<td><code>[4][5]</code></td>
		<td><code>[4][6]</code></td>
		<td><code>[4][7]</code></td>
		<td><code>[4][8]</code></td>
	</tr>
	<tr>
		<td><code>[5][0]</code></td>
		<td><code>[5][1]</code></td>
		<td><code>[5][2]</code></td>
		<td><code>[5][3]</code></td>
		<td><code>[5][4]</code></td>
		<td><code>[5][5]</code></td>
		<td><code>[5][6]</code></td>
		<td><code>[5][7]</code></td>
		<td><code>[5][8]</code></td>
	</tr>
	<tr>
		<td><code>[6][0]</code></td>
		<td><code>[6][1]</code></td>
		<td><code>[6][2]</code></td>
		<td><code>[6][3]</code></td>
		<td><code>[6][4]</code></td>
		<td><code>[6][5]</code></td>
		<td><code>[6][6]</code></td>
		<td><code>[6][7]</code></td>
		<td><code>[6][8]</code></td>
	</tr>
	<tr>
		<td><code>[7][0]</code></td>
		<td><code>[7][1]</code></td>
		<td><code>[7][2]</code></td>
		<td><code>[7][3]</code></td>
		<td><code>[7][4]</code></td>
		<td><code>[7][5]</code></td>
		<td><code>[7][6]</code></td>
		<td><code>[7][7]</code></td>
		<td><code>[7][8]</code></td>
	</tr>
	<tr>
		<td><code>[8][0]</code></td>
		<td><code>[8][1]</code></td>
		<td><code>[8][2]</code></td>
		<td><code>[8][3]</code></td>
		<td><code>[8][4]</code></td>
		<td><code>[8][5]</code></td>
		<td><code>[8][6]</code></td>
		<td><code>[8][7]</code></td>
		<td><code>[8][8]</code></td>
	</tr>
</table>

##`Group_t`に関して

|番号 |内容                                                            |
|-----|----------------------------------------------------------------|
|`[0]`|`[0][0],[0][1],[0][2],[0][3],[0][4],[0][5],[0][6],[0][7],[0][8]`|
|`[1]`|`[1][0],[1][1],[1][2],[1][3],[1][4],[1][5],[1][6],[1][7],[1][8]`|
|`[2]`|`[2][0],[2][1],[2][2],[2][3],[2][4],[2][5],[2][6],[2][7],[2][8]`|
|`[3]`|`[3][0],[3][1],[3][2],[3][3],[3][4],[3][5],[3][6],[3][7],[3][8]`|
|`[4]`|`[4][0],[4][1],[4][2],[4][3],[4][4],[4][5],[4][6],[4][7],[4][8]`|
|`[5]`|`[5][0],[5][1],[5][2],[5][3],[5][4],[5][5],[5][6],[5][7],[5][8]`|
|`[6]`|`[6][0],[6][1],[6][2],[6][3],[6][4],[6][5],[6][6],[6][7],[6][8]`|