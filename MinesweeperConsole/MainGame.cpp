#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<ctime>

#define WINDOWS_WIDTH 10
#define WINDOWS_HEIGHT 10
#define MINES 20

struct Point {
	int x;
	int y;
};

void render(char**);
void createNewBoard(char**,char**);
void neighbour8(int x, int y, Point*);
int isContain(Point, Point *,int);
void openBox(int, Point, char**,char**);
void drawNum(char** mineMap);

//void main() {
//	char** table = new char*[WINDOWS_WIDTH];
//	Point *mines = new Point[MINES];
//	char** mineMap = new char*[WINDOWS_WIDTH];
//
//	for (int i = 0; i < WINDOWS_WIDTH; i++) {
//		table[i] = new char[WINDOWS_HEIGHT];
//		mineMap[i] = new char[WINDOWS_HEIGHT];
//	}
//	for (int i = 0; i < WINDOWS_WIDTH; i++)
//		for (int j = 0; j < WINDOWS_HEIGHT; j++) {
//			table[i][j] = ' ';
//			mineMap[i][j] = ' ';
//		}
//
//	int isGameOver = false;
//	int isFirstTime = true;
//	render(table);
//	while (!isGameOver) {
//		printf("1- Open, 2- Set flag: ");
//		int func = 1;
//		scanf("%d", &func);
//		printf("Enter x, y: ");
//		int x, y = 0;
//		scanf("%d%d", &y, &x);
//		if (func == 1) {
//			if (isFirstTime == true) {
//				srand(time(0));
//				Point *listNeigh = new Point[8];
//				neighbour8(x, y, listNeigh);
//				int mineCount = 0;
//				while (mineCount < MINES) {
//					Point newMine;
//					newMine.x = rand() % 10;
//					newMine.y = rand() % 10;
//					if (((isContain(newMine, listNeigh, 8) == 0 || newMine.x != x || newMine.y != y)) && (!isContain(newMine, mines, mineCount))) {
//						mines[mineCount] = newMine;
//						mineMap[newMine.x][newMine.y] = 'X';
//						mineCount++;
//					}
//				}
//				drawNum(mineMap);
//				isFirstTime = false;
//			}
//			Point curr;
//			curr.x = x;
//			curr.y = y;
//			openBox(isGameOver, curr, table, mineMap);
//		}
//		else {
//			if (table[x][y] == 'F')
//				table[x][y] = ' ';
//			if (table[x][y] == ' ')
//				table[x][y] = 'F';
//		}
//		render(table);
//	}
//	getch();
//}

void createNewBoard(char** table,char** mineMap) {


}
void neighbour8(int x, int y, Point *result) {
	Point p0,p1,p2,p3,p4,p5,p6,p7;
	p0.x = x - 1;
	p0.y = y;

	p1.x = x - 1;
	p1.y = y - 1;

	p2.x = x - 1;
	p2.y = y + 1;

	p3.x = x;
	p3.y = y - 1;

	p4.x = x;
	p4.y = y + 1;
	
	p5.x = x + 1;
	p5.y = y;

	p6.x = x + 1;
	p6.y = y - 1;

	p7.x = x + 1;
	p7.y = y + 1;

	result[0] = p0;
	result[1] = p1;
	result[2] = p2;
	result[3] = p3;
	result[4] = p4;
	result[5] = p5;
	result[6] = p6;
	result[7] = p7;
}
int isContain(Point p0, Point *listPoint, int size) {
	for (int i = 0; i < size; i++) {
		if (p0.x == listPoint[i].x&&p0.y == listPoint[i].y)
			return 1;
	}
	return 0;
}
void openBox(int isGameOver, Point current, char** table, char**mineMap) {
	if (!isGameOver) {
		if (mineMap[current.x][current.y] == 'X') {
			isGameOver = true;
			return;
		}
		else {
			table[current.x][current.y] = mineMap[current.x][current.y];
			Point *listNeigh=new Point[8];
			neighbour8(current.x, current.y, listNeigh);
			for (int i = 0; i < 8; i++) {
				if (listNeigh[i].x >= 0 && listNeigh[i].x < WINDOWS_WIDTH && listNeigh[i].y >= 0 && listNeigh[i].y < WINDOWS_HEIGHT) {
					openBox(isGameOver, listNeigh[i], table, mineMap);
				}
			}
		}
	}
	else {
		return;
	}
}
void drawNum(char** mineMap) {
	for(int i=0;i<WINDOWS_WIDTH;i++)
		for (int j = 0; j < WINDOWS_HEIGHT; j++) {
			if (mineMap[i][j] != 'X') {
				Point *listNeigh=new Point[8];
				neighbour8(i, j, listNeigh);
				int count = 0;
				for (int k = 0; k < 8; i++)
					if (listNeigh[k].x >= 0 && listNeigh[k].x < WINDOWS_WIDTH&&listNeigh[k].y >= 0 && listNeigh[k].y < WINDOWS_HEIGHT)
						if (mineMap[listNeigh[k].x][listNeigh[k].y] == 'X')
							count++;
				if (count != 0)
					mineMap[i][j] = char(count);
			}
		}
}
void render(char** table) {
	system("CLS");
	for (int i = -1; i < WINDOWS_WIDTH; i++) {
		for (int j = -1; j < WINDOWS_HEIGHT; j++) {
			if (j == -1) {
				printf("%d\t", i);
				continue;
			}
			if (i == -1) {
			
				printf("  %d ", j);
				continue;
			}
			if(table[i][j]!='X')
				printf("| %c ", table[i][j]);
			else {
				printf("|   ", table[i][j]);
			}
		}
		printf("|\n");
	}
}