#include <iostream>
#include <Windows.h>
#include <list>
#include <thread>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;

int ekranoPlotis = 120;
int ekranoIlgis = 30;
int choice = 9;
int pinigai = 50;
bool running = true;
bool arGyva = false;
int maistokiek = 0;
int sansokiek = 0;
bool maistoAmuletas;
bool sansas = true;
int maistas2X = 10;
int maistas2Y = 10;
int taskai = 0;

struct snakeKoord {

	int x;
	int y;

};

int main() {
	string nick;
	cout << "Iveskite nickname: ";
	cin >> nick;


	while (choice != 0) {
		system("cls");
		cout << nick << "   Pinigai: " << pinigai << endl;
		cout << "  MENIU  " << endl;
		cout << "1. Naujas zaidimas" << endl;
		cout << "2. Inventorius" << endl;
		cout << "3. Parduotuve" << endl;
		cout << "4. Irasyti taskus" << endl;
		cout << "0. Iseiti" << endl;
		cout << endl;
		cout << " Pasirinkimas: ";
		cin >> choice;
		switch (choice) {
		case 1:
			arGyva = false;
			{wchar_t* screen = new wchar_t[ekranoPlotis * ekranoIlgis];
			for (int i = 0; i < ekranoPlotis * ekranoIlgis; i++) screen[i] = L' ';
			HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
			SetConsoleActiveScreenBuffer(hConsole);
			DWORD dwBytesWritten = 0;
			while (1) {
				list<snakeKoord> snake = { { 60, 15} };
				int maistasX = 30;
				int maistasY = 15;
				int snakeKryptis = 3;
				int pinigasY = 25;
				int pinigasX = 10;

				bool bKeyLeft = false, bKeyRight = false, bKeyLeftOld = false, bKeyRightOld = false;

				while (!arGyva) {

					auto t1 = chrono::system_clock::now();
					while ((chrono::system_clock::now() - t1) < ((snakeKryptis % 2 == 1) ? 110ms : 200ms)) {

						bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('\x27'))) != 0;
						bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('\x25'))) != 0;

						if (bKeyRight && !bKeyRightOld) {
							snakeKryptis++;
							if (snakeKryptis == 4) snakeKryptis = 0;
						}
						if (bKeyLeft && !bKeyLeftOld) {
							snakeKryptis--;
							if (snakeKryptis == -1) snakeKryptis = 3;
						}
						bKeyRightOld = bKeyRight;
						bKeyLeftOld = bKeyLeft;

					}
					switch (snakeKryptis) {
					case 0:
						snake.push_front({ snake.front().x, snake.front().y - 1 });
						break;
					case 1:
						snake.push_front({ snake.front().x + 1, snake.front().y });
						break;
					case 2:
						snake.push_front({ snake.front().x, snake.front().y + 1 });
						break;
					case 3:
						snake.push_front({ snake.front().x - 1, snake.front().y });
						break;

					}
					if (snake.front().x < 0 && sansas==true|| snake.front().x >= ekranoPlotis && sansas == true) {
						sansas = false;
						while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0) {
							wsprintf(&screen[ekranoPlotis + 60], L" Praradote gyvybe! paspauskite 'Space', kad testi");
						}
						snake.front().x = 60;
						snake.front().y = 15;
					}
					else if (snake.front().x < 0 || snake.front().x >= ekranoPlotis) {
						arGyva = true;
					}

					if (snake.front().y < 3 && sansas == true || snake.front().y >= ekranoIlgis && sansas == true) {
						sansas = false;
						snake.front().x = 60;
						snake.front().y = 15;
					}
					else if (snake.front().y < 3 || snake.front().y >= ekranoIlgis) {
						arGyva = true;
					}
				

					if (snake.front().x == maistasX && snake.front().y == maistasY) {
						taskai += 10;
						while (screen[maistasY * ekranoPlotis + maistasX] != L' ') {
							maistasX = rand() % ekranoPlotis;
							maistasY = (rand() % (ekranoIlgis - 3)) + 3;

						}
						for (int i = 0; i < 1; i++)
							snake.push_back({ snake.back().x, snake.back().y });

					}
					if (snake.front().x == pinigasX && snake.front().y == pinigasY) {
						pinigai++;
						while (screen[pinigasY * ekranoPlotis + pinigasX] != L' ') {

							pinigasX = rand() % ekranoIlgis;
							pinigasY = (rand() % (ekranoIlgis - 3)) + 3;
						}
					}
					
					for (list<snakeKoord>::iterator i = snake.begin(); i != snake.end(); i++) 
						if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y) 
							arGyva = true;
					

					snake.pop_back();

					for (int i = 0; i < ekranoIlgis * ekranoPlotis; i++) {
						screen[i] = L' ';
					}
					for (int i = 0; i < ekranoPlotis; i++) {
						screen[i] = L'=';
						screen[2 * ekranoPlotis + i] = L'=';
					}
					
					if (sansas == true)
					{
						wsprintf(&screen[ekranoPlotis + 35], L" Antras Sansas  - [X]");
					}
					else {
						wsprintf(&screen[ekranoPlotis + 35], L" Antras Sansas  - [0]");
					}
					if (maistoAmuletas == true) { wsprintf(&screen[ekranoPlotis + 65], L"Maisto Amuletas - [ X ]"); }
					else
					{
						wsprintf(&screen[ekranoPlotis + 65], L"Maisto Amuletas  - [0]");
					}
					wsprintf(&screen[ekranoPlotis + 20], L" Taskai: %d", taskai);
					wsprintf(&screen[ekranoPlotis], L" Pinigai: %d", pinigai);
					/*if (maistoAmuletas == true) {
						wsprintf(&screen[ekranoPlotis+50]. L' Uzsideti daiktai: Maisto Amuletas ',)
					}*/
					for (auto s : snake)
						screen[s.y * ekranoPlotis + s.x] = arGyva ? L'+' : L'O';

					screen[snake.front().y * ekranoPlotis + snake.front().x] = arGyva ? L'X' : L'@';

					screen[maistasY * ekranoPlotis + maistasX] = L'%';
					screen[pinigasY * ekranoPlotis + pinigasX] = L'$';
					if (maistoAmuletas == true) {
						
						if (snake.front().x == maistas2X && snake.front().y == maistas2Y) {
							taskai += 10;
							while (screen[maistas2Y * ekranoPlotis + maistas2X] != L' ') {
								maistas2X = rand() % ekranoPlotis;
								maistas2Y = (rand() % (ekranoIlgis - 3)) + 3;

							}
							for (int i = 0; i < 1; i++)
								snake.push_back({ snake.back().x, snake.back().y });

						}

						screen[maistas2Y * ekranoPlotis + maistas2X] = L'O';
						
					}

					

					WriteConsoleOutputCharacter(hConsole, screen, ekranoPlotis * ekranoIlgis, { 0,0 }, &dwBytesWritten);

					if (arGyva) {
						CloseHandle(hConsole);
						system("cls");

						cout << "Zaidimo pabaiga! Taskai - " << taskai << "   Pinigai - " << pinigai << endl;
						system("pause");


					}
				}


				break;
			}
			}
			break;
		case 2:
		{int x = 3;

		if (maistokiek > 0 || sansokiek > 0) {
			while (x != 0) {
				cout << "Inventorius: " << endl;
				cout << "1. Maisto amuletas - " << maistokiek << endl;
				cout << "2. Papildomas sansas - " << sansokiek << endl;
				cout << "0. iseiti" << endl;
				cin >> x;
				switch (x) {
				case 1:
					if (maistoAmuletas == false && maistokiek > 0) {
						maistoAmuletas = true;
						maistokiek--;
					}
					else if (maistoAmuletas == true)
						cout << "Jau esate uzsideje si daikta" << endl;
					break;
				case 2:
					if (sansas == false && sansokiek > 0) {
						sansas = true;
						sansokiek--;
					}
					else if (sansas==true)
						cout << "Jau esate uzsideje si daikta" << endl;
				}
			}
		}
		else
			cout << " Neturite jokiu daiktu" << endl;
		system("pause");
		}
		break;
		case 3:
		{int x = 3;
		
			while (x != 0) {
				cout << "  Prekes :" << endl;
				cout << "1. Maisto amuletas - 15  " << endl;
				cout << "2. Papildomas sansas - 35 " << endl;
				cout << "0. iseiti" << endl;
				cout << "Pasirinkimas: ";
				cin >> x;
				cout << endl;
				switch (x) {
				case 1:
					if (pinigai >= 15) {
						maistokiek++;
						pinigai -= 15;
						cout << " Nusipirkote" << endl;
						cout << endl;
					}
					else
						cout << "Neuztenka pinigu" << endl;
					cout << endl;

					break;
				case 2:
					if (pinigai >= 35) {
						cout << " Nusipirkote" << endl;
						cout << endl;
						sansokiek++;
						pinigai -= 35;
					}
					else
						cout << "Neuztenka pinigu" << endl;
					cout << endl;
					break;
				}
			}
		}
		
		break;
		case 4:
			ofstream output("score.html");



			output << "<html><head>";
			output << "<style>table, th, td {border: 1px solid black;}</style>";
			output << "<h2>Tasku lentele</h2> <table style='width:20%'>";
			output << "<tr>";
			output << " <th>Vieta</th>";
			output << "  <th>Slapyvardis</th> ";
			output << " <th>Taskai</th>";
			output << " </tr>";
			output << " <tr>";
				output << "   <td>";
				output << " <td>";
				output << nick << "</td>";
				output << "  <td>";
				output << taskai << "</td>";
				output << " </tr>";
			output << "</table>";
			output << "</head></html>";
			break;
		
		}
	}
}

	