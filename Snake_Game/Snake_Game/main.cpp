#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameFinish;
const int width = 50;
const int height = 30;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int tm = 100;
int av = 30;


enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup()
{
	srand(time(0));  //its a statement placing it in setupa
	gameFinish = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls"); //its a window game
	cout << "Press 'q' to Pause and 'x' to Quit\n" << endl;
	cout << "Score: " << score << endl;
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
				
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "av: " << av << endl;
	cout << "tm: " << tm << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			system("pause");
			break;
		case 'x':
			cout << "\nGame Over! \n Your current score is: " << score << endl;
			cout << "Press any key to exit..." << endl;
			//_getch();
			gameFinish = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0)
	//{
	//	cout << "Game Over! \n Your current score is: " << score << endl;
	//	cout << "Press any key to exit..." << endl;
	//	//_getch();
	//	gameFinish = true;
	//}

	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x&& tailY[i] == y)
		{
			cout << "\nGame Over! \n Your current score is: " << score << endl;
			cout << "Press any key to exit..." << endl;
			//_getch();
			gameFinish = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		srand(time(0));
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		
		
		if (score == av)
		{
			tm -= 10;
			av += 30;
		}
	}
		
}

int main()
{
	cout << "Welcome to the Snake Game!\n";
	cout << "Use 'a' for right, 's' for down, 'd' for left and 'w' for up. \n Press any key to continue...\n";
	_getch();
	system("cls");

	Setup();
	while (!gameFinish)
	{
		Draw();
		Input();
		Logic();
		Sleep(tm);
	}
}