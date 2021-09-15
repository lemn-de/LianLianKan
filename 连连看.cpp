//#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#define ROWS 6
#define COLS 6
int arr[ROWS][COLS];//储存地图
int arr1[2][25], arr2[2][25];//储存空位置坐标
int i, j, k, l;//循环变量
int x1, y1, x2, y2;//储存选中的坐标
int x3, x4, y3, y4;
int flag, x;//判断标志
MOUSEMSG m;
IMAGE bkground, image1, image2, image3, image4, image5, image6, image7, image8, image9;
void UI();//初始化用户界面
void menu();
void printimage();
void contralGame();
void storeLocation(int x1, int y1, int x2, int y2);
void judge();
void judge2();
void judge3(int x3, int y3, int x4, int y4);
void MySwap(int* pNum1, int* pNum2);
void finish();

void UI()
{
	
	cleardevice();

	loadimage(&bkground, _T("JPG"), _T("background"));
	putimage(0, 0, &bkground);//设置背景图

	srand((unsigned)time(NULL));

	for (i = 1; i <= (ROWS - 2 ) / 2; i++)//将数组上半部分复制到下半部分
	{
		for (j = 1; j < COLS - 1; j++)
		{
			arr[i][j] = arr[i + (ROWS - 2) / 2][j] = rand() % 8 + 1;
		}
	}
	for (int i = 0; i < 50; i++)//进行50次随机打乱
	{
		int index1 = rand() % (ROWS - 2) + 1;
		int index2 = rand() % (COLS - 2) + 1;
		int index3 = rand() % (ROWS - 2) + 1;
		int index4 = rand() % (COLS - 2) + 1;
		MySwap(&arr[index1][index2], &arr[index3][index4]);//随机产生两个下标并交换
	}

	loadimage(&image1, _T("JPG"), _T("JPG1"), 40, 40);
	loadimage(&image2, _T("JPG"), _T("JPG2"), 40, 40);
	loadimage(&image3, _T("JPG"), _T("JPG3"), 40, 40);
	loadimage(&image4, _T("JPG"), _T("JPG4"), 40, 40);
	loadimage(&image5, _T("JPG"), _T("JPG5"), 40, 40);
	loadimage(&image6, _T("JPG"), _T("JPG6"), 40, 40);
	loadimage(&image7, _T("JPG"), _T("JPG7"), 40, 40);
	loadimage(&image8, _T("JPG"), _T("JPG8"), 40, 40);
	for (i = 1; i < ROWS - 1; i++)
	{
		for (j = 1; j < COLS - 1; j++)
		{
			if (arr[i][j] == 0)
			{
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, 40, 40, &bkground, 4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40);
			}
			if (arr[i][j] == 1)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image1);
			if (arr[i][j] == 2)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image2);
			if (arr[i][j] == 3)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image3);
			if (arr[i][j] == 4)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image4);
			if (arr[i][j] == 5)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image5);
			if (arr[i][j] == 6)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image6);
			if (arr[i][j] == 7)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image7);
			if (arr[i][j] == 8)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image8);
		}
	}

}
void MySwap(int* pNum1, int* pNum2)//交换数组内容
{
	if (NULL == pNum1 || 0 == pNum1 || NULL == pNum2 || 0 == pNum2)
		return;

	int nTemp = *pNum1;
	*pNum1 = *pNum2;
	*pNum2 = nTemp;
}

void contralGame()
{
	char c = 0;
	while (1)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			for (i = 0; i < ROWS; i++)
			{
				for (j = 0; j < COLS; j++)
				{
					if (m.x - 40 >= 44 * j && m.x - 40 <= 40 * (j + 1) + 4 * j)
					{
						if (m.y - 80 >= 44 * i && m.y - 80 <= 40 * (i + 1) + 4 * i)
						{
							judge();
							if (x == 0 && arr[i][j] < 100)
							{
								x1 = i;
								y1 = j;
								arr[i][j] += 100;
							}
							if (x == 1 && arr[i][j] < 100)
							{
								x2 = i;
								y2 = j;
								arr[i][j] += 100;
								storeLocation(x1, y1, x2, y2);
								judge2();
							}
							printimage();
						}
					}	
				}
			}
		}
	}
	
}

void storeLocation(int x1, int y1, int x2, int y2)
{
	for (l = 0; l < 25; l++)
	{
		arr1[0][l] = -1;
		arr1[1][l] = -1;
		arr2[0][l] = -1;
		arr2[1][l] = -1;
	}
	if (arr[x1][y1] == arr[x2][y2])
	{
		for (l = x1 + 1; l < ROWS; l++)
		{
			if (arr[l][y1] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr1[0][k] == -1)
					{
						arr1[0][k] = l;
						arr1[1][k] = y1;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = x1 - 1; l >= 0; l--)
		{
			if (arr[l][y1] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr1[0][k] == -1)
					{
						arr1[0][k] = l;
						arr1[1][k] = y1;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = y1 - 1; l >= 0; l--)
		{
			if (arr[x1][l] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr1[0][k] == -1)
					{
						arr1[1][k] = l;
						arr1[0][k] = x1;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = y1 + 1; l < COLS; l++)
		{
			if (arr[x1][l] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr1[0][k] == -1)
					{
						arr1[1][k] = l;
						arr1[0][k] = x1;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = x2 + 1; l < ROWS; l++)
		{
			if (arr[l][y2] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr2[0][k] == -1)
					{
						arr2[0][k] = l;
						arr2[1][k] = y2;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = x2 - 1; l >= 0; l--)
		{
			if (arr[l][y2] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr2[0][k] == -1)
					{
						arr2[0][k] = l;
						arr2[1][k] = y2;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = y2 - 1; l >= 0; l--)
		{
			if (arr[x2][l] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr2[0][k] == -1)
					{
						arr2[1][k] = l;
						arr2[0][k] = x2;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		for (l = y2 + 1; l < COLS; l++)
		{
			if (arr[x2][l] == 0)
			{
				for (k = 0; k < 25; k++)
				{
					if (arr2[0][k] == -1)
					{
						arr2[1][k] = l;
						arr2[0][k] = x2;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
}

void judge()
{
	x = 0;
	for (k = 1; k < ROWS - 1; k++)
	{
		for (l = 1; l < COLS - 1; l++)
		{
			if (arr[k][l] >= 100)
				x++;
		}
	}
}

void judge2()
{
	int s = 0;
	flag = 0;
	if (arr[x1][y1] == arr[x2][y2])
	{
		for (k = 0; k < 25; k++)//无拐点和一个拐点
		{
			for (l = 0; l < 25; l++)
			{
				if (arr1[0][k] == arr2[0][l] && arr1[1][k] == arr2[1][l] && arr1[0][k] != -1 && arr2[0][k] != -1)//判断是否有相交的位置
				{
					arr[x1][y1] = 0;
					arr[x2][y2] = 0;
				}
				else if (x1 == x2 && (y1 - y2 == 1 || y1 - y2 == -1))//判断是否横向相邻
				{
					arr[x1][y1] = 0;
					arr[x2][y2] = 0;
				}
				else if (y1 == y2 && (x1 - x2 == 1 || x1 - x2 == -1))//判断是否纵向相邻
				{
					arr[x1][y1] = 0;
					arr[x2][y2] = 0;
				}
				else
				{
					flag = 1;
				}
			}
		}
		if (flag == 1)//两个拐点
		{
			for (l = 0; l < 25; l++)//横向扫描
			{
				if (arr1[0][l] == x1)
				{
					for (k = 0; k < 25; k++)
					{
						if (arr1[1][l] == arr2[1][k])
						{

							judge3(x3, y3, x4, y4);
							s = 1;
							break;
						}
					}
				}
				if (s == 1)
					break;
			}
			if (s == 0)
			{
				for (l = 0; l < 25; l++)
				{
					if (arr1[1][l] == y1)
					{
						for (k = 0; k < 25; k++)
						{
							if (arr1[0][l] == arr2[0][k])
							{
								judge3(x3, y3, x4, y4);
								s = 1;
								break;
							}
						}
					}
					if (s == 1)
						break;
				}
			}
		}
	}
	for (k = 0; k < 15; k++)
	{
		for (l = 0; l < 15; l++)
		{
			arr[k][l] = arr[k][l] % 100;
		}
	}
}

void judge3(int x3, int y3, int x4, int y4)
{
	storeLocation(x3, y3, x4, y4);
	for (k = 0; k < 25; k++)
	{
		for (l = 0; l < 25; l++)
		{
			if (arr1[0][k] == arr2[0][l] && arr1[1][k] == arr2[1][l] && arr1[0][k] != -1 && arr2[0][k] != -1)
			{
				arr[x1][y1] = 0;
				arr[x2][y2] = 0;
			}
			else if (x3 == x4 && (y3 - y4 == 1 || y3 - y4 == -1))
			{
				arr[x1][y1] = 0;
				arr[x2][y2] = 0;
			}
			else if (y3 == y4 && (x3 - x4 == 1 || x3 - x4 == -1))
			{
				arr[x1][y1] = 0;
				arr[x2][y2] = 0;
			}
		}
	}
}

void printimage()
{
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if (arr[i][j] == 0)
			{
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, 40, 40, &bkground, 4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40);//消除方块打印背景
			}
			if (arr[i][j] == 1)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image1);
			if (arr[i][j] == 2)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image2);
			if (arr[i][j] == 3)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image3);
			if (arr[i][j] == 4)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image4);
			if (arr[i][j] == 5)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image5);
			if (arr[i][j] == 6)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image6);
			if (arr[i][j] == 7)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image7);
			if (arr[i][j] == 8)
				putimage(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, &image8);

			if (arr[i][j] > 100)
			{
				setcolor(RED);
				rectangle(4 * j + 40 * (j + 1), 4 * i + 40 * (i + 1) + 40, 4 * j + 40 * (j + 2) - 1, 4 * i + 40 * (i + 2) + 40 - 1);
			}
		}
	}
}

void menu()
{
	
	
}

void finish()
{
	int S = 0;
	for(i = 1; i < ROWS; i++)
		for ( j = 1; j < COLS; j++)
		{
			S = S + arr[i][j];
		}
	if (S == 0)
	{
		MessageBox(NULL, TEXT("恭喜你通过游戏"), TEXT("恭喜"), MB_OK);
	}
}
int main(void)
{
	initgraph(740, 640);
	
	UI();
	contralGame();
	finish();
	_getch();
	closegraph();
	return 0;
}