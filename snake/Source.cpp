#include <iostream>
#include <time.h>
#include <vector>
#include <conio.h>
#include <string>
#include <windows.h>


bool ProgramON{ true };
int SizeHeight{ 20 };//меняется(10 мин)
int SizeLong{ 100 };//меняется(25 мин)
char** Map;
bool Game{ true };
int HeadSneakX{ SizeLong / 2 };
int HeadSneakY{ SizeHeight / 2 };
int AppleX{ rand() % SizeLong };
int AppleY{ rand() % SizeHeight };
int LongSnake{ 2 }; //Меняется
int LongSnakeInGame{ LongSnake };
std::vector<int> TailSnakeX(LongSnake);
std::vector<int> TailSnakeY(LongSnake);
//char LastDirectionSnake;

char SkinHeadSnake{ 'H' };
char SkinTailSnake{ 'h' };
char SkinApple{ 'a' };


void CreateMap()
{

	for (int i{ 0 }; i < SizeHeight; i++)
	{
		for (int j{ 0 }; j < SizeLong; j++)
		{
			if ((i == 0) || (j == 0) || (i == SizeHeight - 1) || (j == SizeLong - 1))
			{
				Map[i][j] = '*';
			}
			else
			{
				Map[i][j] = ' ';
			}
		}
	}

}


void WatchMap()
{
	for (int i{ 0 }; i < SizeHeight; i++)
	{
		for (int j{ 0 }; j < SizeLong; j++)
		{
			std::cout << Map[i][j];
		}
		std::cout << std::endl;
	}
}

void ScreenTextDraw(std::string text, int Height = ((SizeHeight - 1) / 2))
{

	for (int i{ 0 }; i < text.length(); i++)
	{
		Map[Height][(SizeLong - 1) / 2 - text.length() / 2 + i] = text[i];
	}
}

void RandApple()
{

	AppleX = rand() % (SizeLong - 2) + 1;
	AppleY = rand() % (SizeHeight - 2) + 1;
	if (Map[AppleY][AppleX] == ' ')
		Map[AppleY][AppleX] = SkinApple;
	else
		RandApple();

}

void EatApple()
{
	++LongSnakeInGame;
	RandApple();
}

bool HeadInApple()
{
	if ((HeadSneakX == AppleX) && (HeadSneakY == AppleY))
	{
		Map[AppleY][AppleX];
		EatApple();
		return true;
	}
	else
		return false;
}

void Tail()
{

	for (int i{ LongSnakeInGame - 1 }; i >= 1; --i)
	{
		TailSnakeY[i] = TailSnakeY[i - 1];
		TailSnakeX[i] = TailSnakeX[i - 1];
	}

	TailSnakeY[0] = HeadSneakY;
	TailSnakeX[0] = HeadSneakX;

	Map[TailSnakeY[0]][TailSnakeX[0]] = SkinTailSnake;
}

void AllMoving()
{


	if (HeadInApple())
	{


		TailSnakeX.push_back(TailSnakeX[LongSnakeInGame - 2]);
		TailSnakeY.push_back(TailSnakeY[LongSnakeInGame - 2]);
		Tail();
	}
	else
	{
		Map[TailSnakeY[LongSnakeInGame - 1]][TailSnakeX[LongSnakeInGame - 1]] = ' ';
		Tail();
	}
}

void Snake()
{

	if (_kbhit)
	{
		switch (_getch())
		{
		case('w')://up
		{
			Map[--HeadSneakY][HeadSneakX] = SkinHeadSnake;
			//LastDirectionSnake = 'w';
			break;
		}
		case('s')://down
		{
			Map[++HeadSneakY][HeadSneakX] = SkinHeadSnake;
			//LastDirectionSnake = 's';
			break;
		}
		case('a')://left
		{
			Map[HeadSneakY][--HeadSneakX] = SkinHeadSnake;
			//LastDirectionSnake = 'a';
			break;
		}
		case('d')://right
		{
			Map[HeadSneakY][++HeadSneakX] = SkinHeadSnake;
			//LastDirectionSnake = 'd';
			break;
		}
		case('0')://exit
		{
			Game = 0;
		}
		}

	}
}

bool Collision()
{
	if ((HeadSneakX == 0) || (HeadSneakX == SizeLong - 1) || (HeadSneakY == 0) || (HeadSneakY == SizeHeight - 1))
		return true;
	else
	{
		bool TimeCheck{ false };
		for (int i{ 0 }; i < LongSnakeInGame; i++)
		{
			if ((HeadSneakX == TailSnakeX[i]) && (HeadSneakY == TailSnakeY[i]))
				return true;
		}
		return false;
	}
}

void ScreenMenu()
{
	Map = new char* [SizeHeight];
	for (int i{ 0 }; i < SizeHeight; i++)
	{
		Map[i] = new char[SizeLong];
	}

	CreateMap();
	ScreenTextDraw("SNAKE", (((SizeHeight - 1) / 2) - 2));
	ScreenTextDraw("1) Start game");
	ScreenTextDraw("2) Settings", (((SizeHeight - 1) / 2) + 1));
	ScreenTextDraw("0) Exit", (((SizeHeight - 1) / 2) + 2));
	WatchMap();

	for (int i{ 0 }; i < SizeHeight; i++)
	{
		delete[] Map[i];
	}
	delete[] Map;
}

void ScreenSettings()
{
	Map = new char* [SizeHeight];
	for (int i{ 0 }; i < SizeHeight; i++)
	{
		Map[i] = new char[SizeLong];
	}

	CreateMap();
	ScreenTextDraw("SETTINGS", (((SizeHeight - 1) / 2) - 4));
	ScreenTextDraw("1) Long map", (((SizeHeight - 1) / 2) - 2));
	ScreenTextDraw("2) Height map", (((SizeHeight - 1) / 2) - 1));
	ScreenTextDraw("3) Long snake(at start)");
	ScreenTextDraw("4) Skin head snake", (((SizeHeight - 1) / 2) + 1));
	ScreenTextDraw("5) Skin tail snake", (((SizeHeight - 1) / 2) + 2));
	ScreenTextDraw("6) Skin apple", (((SizeHeight - 1) / 2) + 3));
	ScreenTextDraw("0) Save and back", (((SizeHeight - 1) / 2) + 4));
	WatchMap();


}

void MenuSetting()
{
	bool SettingON{ true };
	int LocalSizeLong{ SizeLong }, LocalSizeHeight{ SizeHeight }, LocalLongSnake{ LongSnake };
	while (SettingON)
	{
		system("cls");
		ScreenSettings();
		if (_kbhit)
		{
			switch (_getch())
			{
			case('1'):
			{
				LocalSizeLong = 0;
				while (LocalSizeLong < 25)
				{
					system("cls");
					CreateMap();
					ScreenTextDraw("LONG MAP");
					ScreenTextDraw("min 25", (((SizeHeight - 1) / 2) + 1));
					ScreenTextDraw("recommended 100", (((SizeHeight - 1) / 2) + 2));
					WatchMap();
					std::cout << "Enter long map: ";
					try
					{
						std::cin >> LocalSizeLong;
						if (LocalSizeLong < 25)
							throw LocalSizeLong;
						std::cout << "OK";
					}
					catch (int Error)
					{
						std::cout << "!!! " << Error << " < 25 !!!";
						Sleep(1000);
					}
				}
				break;
			}
			case('2'):
			{
				LocalSizeHeight = 0;
				while (LocalSizeHeight < 10)
				{
					system("cls");
					CreateMap();
					ScreenTextDraw("HEIGHT MAP");
					ScreenTextDraw("min 10", (((SizeHeight - 1) / 2) + 1));
					ScreenTextDraw("recommended 20", (((SizeHeight - 1) / 2) + 2));
					WatchMap();
					std::cout << "Enter height map: ";
					try
					{
						std::cin >> LocalSizeHeight;
						if (LocalSizeHeight < 10)
							throw LocalSizeHeight;
						std::cout << "OK";
					}
					catch (int Error)
					{
						std::cout << "!!! " << Error << " < 10 !!!";
						Sleep(1000);
					}
				}
				break;
			}
			case('3'):
			{
				LocalLongSnake = 0;
				int MaxLong{ SizeHeight / 2 - 2 };
				while ((LocalLongSnake < 2) || (LocalLongSnake > (MaxLong)))
				{
					system("cls");
					CreateMap();
					ScreenTextDraw("LONG SNAKE");
					{
						std::string message = "min 2 max " + std::to_string(MaxLong) + " (depends on map height)";
						ScreenTextDraw(message, (((SizeHeight - 1) / 2) + 1));
					}
					ScreenTextDraw("recommended 20", (((SizeHeight - 1) / 2) + 2));
					WatchMap();
					std::cout << "Enter long snake: ";
					try
					{
						std::cin >> LocalLongSnake;
						if ((LocalLongSnake < 2) && (LocalLongSnake > (MaxLong)))
							throw LocalLongSnake;
						std::cout << "OK";
					}
					catch (int Error)
					{
						if (Error < 2)
							std::cout << "!!! " << Error << " < 2 !!!";
						std::cout << "!!! " << Error << " > " << MaxLong << " !!!";
						Sleep(1000);
					}

					if (LocalLongSnake != LongSnake)
						if (LocalLongSnake > LongSnake)
							for (int i{ 0 }; i < (LocalLongSnake - LongSnake); i++)
							{
								TailSnakeX.push_back(0);
								TailSnakeY.push_back(0);
							}
						else
							for (int i{ 0 }; i < (LongSnake - LocalLongSnake); i++)
							{
								TailSnakeX.pop_back();
								TailSnakeY.pop_back();
							}
					LongSnake = LocalLongSnake;
				}
				break;
			}
			case('4'):
			{
				system("cls");
				CreateMap();
				ScreenTextDraw("SKIN HEAD SNAKE");
				WatchMap();
				std::cout << "Enter the symbol for snake: ";
				std::cin >> SkinHeadSnake;
				break;
			}
			case('5'):
			{
				system("cls");
				CreateMap();
				ScreenTextDraw("SKIN TAIL SNAKE");
				WatchMap();
				std::cout << "Enter the symbol for tail snake: ";
				std::cin >> SkinTailSnake;
				break;
			}
			case('6'):
			{
				system("cls");
				CreateMap();
				ScreenTextDraw("SKIN APPLE");
				WatchMap();
				std::cout << "Enter the symbol for apple: ";
				std::cin >> SkinApple;
				break;
			}
			case('0'):
			{
				for (int i{ 0 }; i < SizeHeight; i++)
				{
					delete[] Map[i];
				}
				delete[] Map;

				SizeHeight = LocalSizeHeight;
				SizeLong = LocalSizeLong;

				system("cls");

				SettingON = false;

				break;
			}
			}
		}
	}
}





int main()
{

	srand(time(NULL));
	while (ProgramON)
	{
		//menu
		system("cls");
		ScreenMenu();

		if (_kbhit)
		{
			switch (_getch())
			{

			case('1')://game on
			{
				system("cls");

				{
					LongSnakeInGame = LongSnake;
					Game = true;

					Map = new char* [SizeHeight];
					for (int i{ 0 }; i < SizeHeight; i++)
					{
						Map[i] = new char[SizeLong];
					}


					CreateMap();
					HeadSneakX = (SizeLong / 2);
					HeadSneakY = (SizeHeight / 2);
					Map[HeadSneakY][HeadSneakX] = SkinHeadSnake;
					for (int i{ 0 }; i < LongSnake; i++)
					{
						TailSnakeX[i] = HeadSneakX;
						TailSnakeY[i] = HeadSneakY + i + 1;
						Map[TailSnakeY[i]][TailSnakeX[i]] = SkinTailSnake;
					}
					RandApple();
					WatchMap();
					std::cout << "Control: w - UP, s - DOWN, a - LEFT, d - RIGHT, 0 - EXIT (English layout required)" << std::endl;
				}

				while (Game)
				{
					AllMoving();
					Snake();
					if (Collision())
						Game = 0;;
					system("cls");
					WatchMap();
					std::cout << "Long snake: " << LongSnakeInGame << std::endl;
					std::cout << "0 - EXIT" << std::endl;
				}
				system("cls");

				CreateMap();
				ScreenTextDraw("Game over");
				WatchMap();

				std::cout << "Long snake: " << LongSnakeInGame << std::endl;
				Sleep(2000);

				for (int i{ 0 }; i < (LongSnakeInGame - LongSnake); i++)
				{
					TailSnakeX.pop_back();
					TailSnakeY.pop_back();
				}
				//delete

				for (int i{ 0 }; i < SizeHeight; i++)
				{
					delete[] Map[i];
				}
				delete[] Map;
				system("cls");
				break;
			}
			case('2'):
			{
				system("cls");
				MenuSetting();
				break;
			}
			case('0'):
			{
				system("cls");
				std::cout << "Exit...";
				ProgramON = false;
				break;
			}
			}
		}
	}
	TailSnakeX.clear();
	TailSnakeY.clear();
	return 0;
}//hep

