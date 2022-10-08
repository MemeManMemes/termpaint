#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <deque>
using namespace std;

uint16_t x = 0;
uint16_t y = 0;

uint16_t cols = 32;
uint16_t lines = 32;

struct winsize w;

deque<uint16_t> color;
	
int gkey() 
{
  system ("/bin/stty raw");
  int c;
  system ("/bin/stty -echo");
  c = getc(stdin);
  system ("/bin/stty echo");
  system ("/bin/stty cooked");
  return c;
}

int dir(const char *path)
{
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode)) return 1;
    return 0;
}

void setarea()
{
	system("clear");
	cout << "IRRADIX TERMPAINT v1.00 - ";
	if (cols < 10) cout << "0";
	cout << uint16_t(cols) << "x";
	if (lines < 10) cout << "0";
	cout << uint16_t(lines) << " canvas";
	
	cout << endl << " ";
	
	for (uint8_t i = 0; i < cols; i++)
	{
		cout << "__";
	}
	
	cout << endl;
	
	for (uint16_t i = 0; i < lines; i++)
	{
		cout << "|";
		for (uint16_t j = 0; j < cols; j++)
		{
			if ((y * cols) + x == (i * cols) + j)
			{
				
				if (color[(i * cols) + j] == 1) // white
				{
					cout << " \033[4m\033[37m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 2) // red
				{
					cout << " \033[4m\033[31m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 3) // orange
				{
					cout << " \033[4m\033[33m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 4) // yellow
				{
					cout << " \033[4m\033[1;33m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 5) // green
				{
					cout << " \033[4m\033[32m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 6) // cyan
				{
					cout << " \033[4m\033[36m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 7) // blue
				{
					cout << " \033[4m\033[34m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 8) // purple
				{
					cout << " \033[4m\033[35m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 11) // l white
				{
					cout << " \033[4m\033[1;37m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 12) // l red
				{
					cout << " \033[4m\033[1;31m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 15) // l green
				{
					cout << " \033[4m\033[1;32m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 16) // l cyan
				{
					cout << " \033[4m\033[1;36m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 17) // l blue
				{
					cout << " \033[4m\033[1;34m■\033[0m\033[0m";
				}
				
				else if (color[(i * cols) + j] == 18) // l purple
				{
					cout << " \033[4m\033[1;35m■\033[0m\033[0m";
				}


				else
					cout << " \033[4m \033[0m";
			}
			
			else
			{
				
				if (color[(i * cols) + j] == 1)
				{
					cout << "\033[0;37m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 2)
				{
					cout << "\033[0;31m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 3)
				{
					cout << "\033[0;33m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 4)
				{
					cout << "\033[1;33m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 5)
				{
					cout << "\033[0;32m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 6)
				{
					cout << "\033[0;36m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 7)
				{
					cout << "\033[0;34m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 8)
				{
					cout << "\033[0;35m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 11)
				{
					cout << "\033[1;37m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 12)
				{
					cout << "\033[1;31m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 15)
				{
					cout << "\033[1;32m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 16)
				{
					cout << "\033[1;36m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 17)
				{
					cout << "\033[1;34m ■\033[0m";
				}
				
				else if (color[(i * cols) + j] == 18)
				{
					cout << "\033[1;35m ■\033[0m";
				}
				
				else
					cout << "  ";
				
			}
		}
		cout << "|" << endl;
	} 
	
	cout << " ";
	
	for (uint8_t i = 0; i < cols; i++) cout << "⎺⎺";
	
	cout << endl << "Press the 'h' key for help";
}

int main (int argc, char** argv)
{	
	for (int i = 0; i < lines * cols; i++)
	{
			color.push_back(0);
	}
	
	if (argc == 2)
	{
		ifstream file;
		file.open(argv[1], ios::binary | ios::in);
		
		if (file.is_open())
		{
			string fileinfo;
			getline(file, fileinfo);
			cols = fileinfo[0];
			lines = fileinfo[1];
			for (uint16_t i = 2; i < fileinfo.length(); i++)
			{
				color[i - 2] = fileinfo[i];
			}
		}
	}
	
	bool typingmode = false;
	
	bool exit = false;
	system("clear");
	cout << "\e[?25l";
	
    char key;
	
	cout << " ";
	
	cout << endl;
	
	setarea();
	
	cout << " ";
	
	while (true)
	{
		key = gkey();
		if (key == 'q')
		{
			for (uint8_t i = 0; i < sizeof(color); i++) 
			{
				color[i] = 0;
			}
			cout << "\e[?25h" << endl;
			return 0;
		}
		
		else if (key == 'w')
		{
			if (y != 0)
			{
				y--;
				setarea();
			}
		}
		
		else if (key == 'a')
		{
			if (x != 0)
			{
				x--;
				setarea();
			}
		}
		
		else if (key == 's')
		{
			if ( y < lines - 1)
			{
				y++;
				setarea();
			}
		}
		
		else if (key == 'd')
		{
			if (x < cols - 1)
			{
				x++;
				setarea();
			}
		}
		
		else if (key == '\033') 
		{
			gkey();
			switch (gkey()) 
			{
				case 'A':
					if (y != 0) 
					{
						y--;
						setarea();
					}
				break;
				
				case 'B':
					if (y < lines - 1) 
					{
						y++;
						setarea();
					}
				break;
				
				case 'C':
					if (x < cols - 1) 
					{
						x++;
						setarea();
					}
				break;
				
				case 'D':
					if (x != 0) 
					{
						x--;
						setarea();
					}
				break;
			}
		}
		
		else if (key == '1')
		{
			color[(y * cols) + x] = 1;
			setarea();
		}
		
		else if (key == '2')
		{
			color[(y * cols) + x] = 2;
			setarea();
		}
		
		else if (key == '3')
		{
			color[(y * cols) + x] = 3;
			setarea();
		}
		
		else if (key == '4')
		{
			color[(y * cols) + x] = 4;
			setarea();
		}
		
		else if (key == '5')
		{
			color[(y * cols) + x] = 5;
			setarea();
		}
		
		else if (key == '6')
		{
			color[(y * cols) + x] = 6;
			setarea();
		}
		
		else if (key == '7')
		{
			color[(y * cols) + x] = 7;
			setarea();
		}
		
		else if (key == '8')
		{
			color[(y * cols) + x] = 8;
			setarea();
		}
		
		else if (key == '!')
		{
			color[(y * cols) + x] = 11;
			setarea();
		}
		
		else if (key == '@')
		{
			color[(y * cols) + x] = 12;
			setarea();
		}
		
		else if (key == '%')
		{
			color[(y * cols) + x] = 15;
			setarea();
		}
		
		else if (key == '^')
		{
			color[(y * cols) + x] = 16;
			setarea();
		}
		
		else if (key == '&')
		{
			color[(y * cols) + x] = 17;
			setarea();
		}
		
		else if (key == '*')
		{
			color[(y * cols) + x] = 18;
			setarea();
		}
		
		else if (key == ' ')
		{
			color[(y * cols) + x] = 0;
			setarea();
		}
		
		else if (key == 'r')
		{
			char c;
			cout << "\e[?25h";
			system("clear");
			cout << "Would you like to reset this grid?: ";
			cin >> c;
			if (c == 'y' || c == 'Y')
			{
				for (uint16_t i = 0; i < cols * lines; i++) 
				{
					color[i] = 0;
				}
			}
			cout << "\e[?25l";
		}
		
		else if (key == '0')
		{
			string path;
			string name;
			cout << "\e[?25h";
			char s;
			system("clear");
			cout << "Would you like to save? (y/n): ";
			cin >> s;
			if (s == 'y' || s == 'Y')
			{
				cout << endl << "What would you like to call this file?: ";
				string str;
				string dirpath;
				cin >> str;
				bool skill = false;
				for (int32_t i = str.length(); i > -1; i--)
				{
					if (skill) dirpath = str[i] + dirpath;
					
					if (str[i] == '/') skill = true;
				}
				
				if (!str.ends_with(".sdpiff")) str += ".sdpiff";
				
				ofstream file;
				
				if (!skill)
				{
					string homeDir = getenv("HOME");
					str = homeDir + "/" + str;
					file.open(str, ios::binary | ios::out);
					file << char(cols) << char(lines);
					for (uint16_t i = 0; i < lines * cols; i++)
					{
						file << char(color[i]);
					}
				}
				
				else
				{
					if (dir(dirpath.c_str()))
					{
						file.open(str, ios::binary | ios::out);
						file << char(cols) << char(lines);
						for (uint16_t i = 0; i < lines * cols; i++)
						{
							file << char(color[i]);
						}
					}
					
					else
					{
						cout << endl << "FILE SAVING DID NOT WORK - REASON: DIRECTORY LOCATION '" << dirpath << "' DOES NOT EXIST" << endl << "Press enter to continue\n";
						cin.ignore();
					}
				}
				
			}
			cout << "\e[?25l";
		}
		
		else if (key == ';')
		{
			uint16_t backx = cols;
			uint16_t backy = lines;
			char c;
			cout << "\e[?25h";
			system("clear");
			cout << "Canvas sizer\n!!IF YES IS SELECTED, THEN ALL PROGRESS WILL BE ERASED!!\nWould you like to resize the canvas?(y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
			{
				cout << "\n\nEnter in two numbers, the first being the with of the canvas and the second being the height\nPlease enter the new size of the canvas separted by a space: ";
				cin >> cols;
				cin >> lines;
				
				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				
				if (cols > w.ws_col || lines >> w.ws_row) 
				{
					cols = backx;
					lines = backy;
				}
					
				x = 0;
				y = 0;
				
				for (uint16_t i = 0; i < size(color); i++) color.pop_front();
					
				for (uint16_t i = 0; i < lines * cols; i++) color.push_front(0);
				
			}
			cout << "\e[?25l";
		}
		
		else if (key == 'h' && exit)
		{
			exit = false;
			system("clear");
			cout << "termpaint: an application used to paint inside of a terminal - press keyboard keys to paint or do commands" << endl << endl << "(Press corresponding key on keyboard) Possible commands:" << endl << endl << "0  :  save file\n1  :  paint white  \033[37m■\033[0m  r\n";
			cout << "2  :  paint red    \033[0;31m■\033[0m  a\n3  :  paint orange \033[0;33m■\033[0m  i\n4  :  paint yellow \033[1;33m■\033[0m  n\n5  :  paint green  \033[0;32m■\033[0m  b\n6  :  paint cyan   \033[0;36m■\033[0m  o\n7  :  paint blue   \033[0;34m■\033[0m  w\n8  :  paint purple \033[0;35m■\033[0m  !";
			cout << "\nr  :  reset canvas\n;  :  resize canvas\nh  :  get help or exit help\nq  :  exit program without saving\nw or up arrow  :  move Y position up by one\na or left arrow  :  move X position left by one\ns or down arrow  :  move Y posiiton down by one\nd or right arrow  :  move X position right by one\n";
			cout << "\nPressing shift + the number you want to paint will give a lighter version of that color except for orange and yellow which do not have that function";
		}
		
		else if (key == 'h' && !exit)
		{
			exit = true;
			setarea();
		}
		
		else
		{
			setarea();
		}
	}
	return 0;
}
