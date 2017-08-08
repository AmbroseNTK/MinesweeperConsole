#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<ctime>

//Default setting
#define WIDTH 10
#define HEIGHT 10
#define MINES 20

#define STATE_NOT_OPEN 'N'
#define STATE_OPEN 'O'
#define STATE_MINE 'M'
#define STATE_FLAG 'F'

#define CHAR_FLAG 'F'
#define CHAR_OPEN 'O'
#define CHAR_MINE 'X'
#define CHAR_NOT_OPEN ' '

struct Cell {
	int x;
	int y;
	char behavior;
	char state;
	int isOpen;
};

void render(Cell**);
void createNewTable(Cell**);
int validCell(Cell);
int validCell(int, int);
void getAround(int, int, Cell**,Cell*);
void createMineMap(int , int, Cell**);
int isContain(int, int, Cell *,int);
void open(int, int, int&, Cell**);
int checkWin(Cell**);

void main() {
	Cell  **table = new Cell*[WIDTH];
	int isGameOver = false;
	int isFirstTime = true;
	createNewTable(table);

	while (!isGameOver||!checkWin(table)) {
		render(table);
		printf("\n1-Open , 2-Set/Unset Flag ");
		int mode;
		scanf("%d", &mode);
		printf("Select x,y: ");
		int x, y;
		scanf("%d%d", &y, &x);
		if (validCell(x, y)) {
			if (mode == 1) {
				if (isFirstTime) {
					createMineMap(x, y, table);
					isFirstTime = false;
				}
				table[x][y].isOpen = true;
				open(x, y, isGameOver, table);
			}
			else {
				if (table[x][y].behavior == CHAR_NOT_OPEN) {
					table[x][y].behavior = CHAR_FLAG;
					continue;
				}
				if (table[x][y].behavior == CHAR_FLAG) {
					table[x][y].behavior = CHAR_NOT_OPEN;
					continue;
				}
			}
		}
		
	}
	if (isGameOver)
		printf("\nGAME OVER");
	getch();
}

void createNewTable(Cell **table) {
	//Declare new 2d array
	for (int i = 0; i < WIDTH; i++) {
		table[i] = new Cell[HEIGHT];
	}
	//Fill default state for all cell in the table
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			table[i][j].x = i;
			table[i][j].y = j;
			table[i][j].state = STATE_NOT_OPEN;
			table[i][j].behavior = CHAR_NOT_OPEN;
			table[i][j].isOpen = false;
		}
	}
}

int validCell(Cell cell) {
	if (cell.x >= 0 && cell.x < WIDTH && cell.y >= 0 && cell.y < HEIGHT)
		return true;
	return false;
}
//Override validCell method with another arguments
int validCell(int cellX, int cellY) {
	Cell cell;
	cell.x = cellX;
	cell.y = cellY;
	return validCell(cell);
}

void getAround(int x, int y, Cell **table, Cell *result) {
	Cell c0, c1, c2, c3, c4, c5, c6, c7;
	c0.x = x;
	c0.y = y - 1;

	c1.x = x;
	c1.y = y + 1;

	c2.x = x - 1;
	c2.y = y;

	c3.x = x - 1;
	c3.y = y - 1;
	
	c4.x = x - 1;
	c4.y = y + 1;

	c5.x = x + 1;
	c5.y = y;

	c6.x = x + 1;
	c6.y = y - 1;

	c7.x = x + 1;
	c7.y = y + 1;

	result[0] = c0;
	result[1] = c1;
	result[2] = c2;
	result[3] = c3;
	result[4] = c4;
	result[5] = c5;
	result[6] = c6;
	result[7] = c7;
}
void createMineMap(int x, int y, Cell** table) {
	Cell *around = new Cell[9];
	getAround(x, y, table, around);
	around[9].x = x;
	around[9].y = y;

	int mineNum = 0;
	srand(time(0));
	while (mineNum != MINES) {
		int genX = rand() % WIDTH;
		int genY = rand() % HEIGHT;
		if (!isContain(genX, genY, around, 9)) {
			table[genX][genY].behavior = STATE_MINE; //Delete
			table[genX][genY].state = STATE_MINE;
			mineNum++;
		}
	}
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (table[i][j].state != STATE_MINE) {
				around = new Cell[8];
				getAround(i, j, table, around);
				int count = 0;
				for (int i = 0; i < 8; i++) {
					if (validCell(around[i])) {
						if (table[around[i].x][around[i].y].state == STATE_MINE) {
							count++;
						}
					}
				}
				if (count != 0) {
					table[i][j].state = char(48 + count);
				}
			}
		}
	}

}

int isContain(int x, int y, Cell *list, int size) {
	for (int i = 0; i < size; i++) {
		if (list[i].x == x && list[i].y == y)
			return true;
	}
	return false;
}
void open(int x, int y, int &isGameOver, Cell **table) {
	if (table[x][y].state == STATE_MINE&&table[x][y].isOpen) {
		isGameOver = true;
		return;
	}
	if (table[x][y].state == STATE_MINE) {
		return;
	}
	if (table[x][y].state != STATE_MINE) {
		if (table[x][y].state == STATE_NOT_OPEN) {
			table[x][y].behavior = CHAR_OPEN;
			table[x][y].state = STATE_OPEN;
			table[x][y].isOpen = true;
		}
		else if (table[x][y].behavior != CHAR_FLAG) {
			table[x][y].behavior = table[x][y].state;
			table[x][y].isOpen = true;
			return;
		}
		if (table[x][y].state == STATE_OPEN) {
			table[x][y].behavior = CHAR_OPEN;
			table[x][y].isOpen = true;
		}
		Cell *around = new Cell[8];
		getAround(x,y,table,around);
		for (int i = 0; i < 8; i++) {
			if (validCell(around[i])) {
				open(around[i].x, around[i].y, isGameOver, table);
			}
		}
		
	}
}
int checkWin(Cell **table) {
	for (int i = 0; i < WIDTH;i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (table[i][j].state != STATE_MINE && !table[i][j].isOpen)
				return false;
		}
	}
	printf("\nYOU WIN");
	return true;
}
void render(Cell **table) {
	system("CLS");
	for (int i = -1; i < WIDTH; i++) {
		for (int j = -1; j < HEIGHT; j++) {
			if (i == -1) {
				printf("| %d ", j);
				continue;
			}
			if (j == -1) {
				printf("  %d  ", i);
				continue;
			}
			printf("| %c ", table[i][j].behavior);
		}
		printf("|\n");
	}
}