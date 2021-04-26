#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define maxstage 2

void gotoxy(int x, int y);
void print_board();
void playermoveaction();
BOOL testclear();

char stage[11][30];
int roundnum;
int roundx, roundy;

char game_board[maxstage][11][30] = {
{
	{"#############################"},
	{"###########    ##############"},
	{"########      o##############"},
	{"########      o #############"},
	{"######## ## ### #############"},
	{"######## ## ### #########  .#"},
	{"####       o               .#"},
	{"########### ### ####@####  .#"},
	{"###########     #############"},
	{"#############################"},
	{"#############################"},
},
{
	{"#############################"},
	{"#############################"},
	{"##############.##############"},
	{"############## ##############"},
	{"############## o@  o   .#####"},
	{"#########.     o o ##########"},
	{"################ ############"},
	{"################ ############"},
	{"################.############"},
	{"#############################"},
	{"#############################"},
},
};


void main(void)
{
	int x, y;

	roundnum = 1;

	while (1)
	{
		memcpy(stage, game_board[roundnum], sizeof(stage));

		for (x = 0; x < 30; x++)
		{
			for (y = 0; y < 11; y++)
			{
				if (stage[y][x] == '@')
				{
					roundx = x;
					roundy = y;
					stage[y][x] = ' ';
				}
			}
		}
		system("cls");
		while (1)
		{
			print_board();
			playermoveaction();
			if (testclear())
			{
				system("cls");
				gotoxy(30, 4);
				printf("축하합니다. 클리어");
				if (roundnum < maxstage - 1)
				{
					roundnum++;
				}
				break;
				
			}
		}

	}

}


void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void print_board()
{
	int x, y;
	for (x = 0; x < 30; x++)
	{
		for (y = 0; y < 11; y++)
		{
			gotoxy(x, y);
			_putch(stage[y][x]);
		}
	}
	gotoxy(roundx, roundy);
	_putch('@');
}

void playermoveaction()
{
	int dx=0, dy=0;
	char ch;

	ch = _getch();

	if (ch == -32)
	{
		ch = _getch();
		switch (ch)
		{
		case 75:
			dx = dx - 1;
			break;
		case 77:
			dx = dx + 1;
			break;
		case 72:
			dy = dy - 1;
			break;
		case 80:
			dy = dy + 1;
			break;
		}
		if (stage[roundy + dy][roundx + dx] == '#')
		{
			return;
		}
		if (stage[roundy + dy][roundx + dx] == 'o')
		{
			if (stage[roundy + dy * 2][roundx + dx * 2] == ' ')
			{
				stage[roundy + dy][roundx + dx] = ' ';
				stage[roundy + dy * 2][roundx + dx * 2] = 'o';
			}
			else if (stage[roundy + dy * 2][roundx + dx * 2] == '.')
			{
				stage[roundy + dy][roundx + dx] = ' ';
				stage[roundy + dy * 2][roundx + dx * 2] = '*';
			}
			else if (stage[roundy + dy * 2][roundx + dx * 2] == 'o')
			{
				return;
			}

			else if (stage[roundy + dy * 2][roundx + dx * 2] == '#')
			{
				return;
			}

		}
		roundx = roundx + dx;
		roundy = roundy + dy;
	}
}

BOOL testclear()
{
	int cx, cy;

	for (cy = 0; cy < 11; cy++)
	{
		for (cx = 0; cx < 30; cx++)
		{
			if (game_board[roundnum][cy][cx] == '.' && stage[cy][cx] != '*')
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}