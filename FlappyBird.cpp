#include <iostream>
#include <string.h>
#include<windows.h> 
#include <conio.h>
using namespace std;

class flappyBird
{
public:
	bool gameState;
	bool shouldGenWall;
	bool currentState; // 0 freefall, 1 jump

	char gameTable[60][30];
	bool wallTable[60][30];
	char bird = 'W', wall = '|';

	int generateIndex = 0;
	int xmax = 60, ymax = 25;
	int birdx = 2, birdy = 12;
	int points = 0;
	int difficulty = 10;
	int gameSpeed = 50;
	flappyBird()
	{
		//cin >> difficulty;
		shouldGenWall = true;
		generateIndex = 0;
		currentState = 0;
		gameState = true;
		for (int i = 0; i < ymax; i++)
		{
			for (int k = 0; k < xmax; k++)
			{
				gameTable[k][i] = ' ';
				wallTable[k][i] = false;
			}
			cout << '\n';
		}


	}
public:
	void clearConsole()
	{
		system("CLS"); //CLEARS CONSOLE
	}

	void update()
	{
		clearConsole();
		updateWall();
		generateWall();
		dedectMovement();
		doMovement();
		dedectCollision();
		render();
	}

	void render()
	{
		gameTable[birdx][birdy] = bird;
		for (int i = 0; i < ymax; i++)
		{
			for (int k = 0; k < xmax; k++)
			{

				if (k == birdx && i == birdy)
					gameTable[birdx][birdy] = bird;
				else if (wallTable[k][i])
					gameTable[k][i] = wall;
				else
					gameTable[k][i] = ' ';

				cout << gameTable[k][i];
			}
			cout << '\n';
		}
		cout << "points: " << points << '\n';
		if (!gameState)
			cout << "Thanks for playing! Game by Batuhan Arda Bekar, Can Sari";
	}

	void dedectCollision()
	{
		if (gameState)
			for (int i = 0; i < ymax; i++)
				for (int k = 0; k < xmax; k++)
					if ((wallTable[k][i] == true && k == birdx && birdy == i) || (birdy < 0 || birdy > 24))
					{
						gameState = false;
						bird = 'x';
					}
	}

	void dedectMovement()
	{
		if (_kbhit()) // keyboard hit function 
		{
			switch (_getch()) // gets the key which was hit
			{
			case 'w':
				this->currentState = 1;
				break;
			case ' ':
				this->currentState = 1;
				break;
			default: //w 
				this->currentState = 0;
				break;
			}
		}
		else
		{
			this->currentState = 0;
		}
	}

	void generateWall()
	{
		if (generateIndex < difficulty)
			return;

		int wall1 = 4, wall2 = 4;

		int temp = rand() % 11;
		wall1 += temp;
		wall2 += 10 - temp;

		for (int i = 0; i < 25; i++)
		{
			if (wall1 == 0)
				break;

			wallTable[59][i] = true;
			wall1--;
		}

		for (int i = 24; i > -1; i--)
		{
			if (wall2 == 0)
				break;
			wallTable[59][i] = true;
			wall2--;
		}

		generateIndex = 0;
	}

	void updateWall()
	{
		for (int i = 0; i < 60; i++)
		{
			if (i == 0)
			{
				if (wallTable[i][0] == true)
					points++;
				for (int k = 0; k < 25; k++)
					wallTable[i][k] = false;
				continue;
			}

			if (wallTable[i][0] == true)
			{
				for (int k = 0; k < 25; k++)
					if (wallTable[i][k])
					{
						wallTable[i - 1][k] = true;
						wallTable[i][k] = false;
					}

			}
		}
	}

	void doMovement()
	{

		if (currentState)
			birdy -= 4;
		else
			birdy += 1;

	}
};



int main()
{
	srand(time(NULL));
	flappyBird game;

	cout << "Enter Game Speed (50 Recommended): ";
	cin >> game.gameSpeed;

	cout << "Enter Difficulty (10 Recommended): ";
	cin >> game.difficulty;

	while (game.gameState)
	{
		game.generateIndex++;
		game.update();
		Sleep(game.gameSpeed);
	}

}