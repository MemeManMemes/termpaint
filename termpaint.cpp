#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <deque>
using namespace std;

uint8_t x = 0, y = 0;
uint16_t cols = 32, lines = 32;
char accepted[62] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
struct winsize w;
uint8_t mode = 0;
char key;
deque<uint8_t> color, character;

int gkey();
void setarea();
int dir(const char *path);

int main (int argc, char** argv)
{	
	for (int i = 0; i < lines * cols; i++) 
	{
		color.push_back(0);
		character.push_back(0);
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
			uint16_t i, j = 0;
			for (i = 2; i < (cols * lines) + 2; i++) color[i - 2] = fileinfo[i];
			for (;i < fileinfo.length(); i++)
			{
				character[j] = fileinfo[i];
				if ((y * cols) + x <= cols * lines) j++;
			}
		}
	}
	
	bool exit = false;
	system("clear");
	cout << "\e[?25l";
	cout << " ";
	cout << endl;
	setarea();
	cout << " ";
	
	while (true)
	{
		key = gkey();
		if (key == '\033') 
		{
			gkey();
			switch (gkey()) 
			{
				case 'A': if (y != 0) y--; break;
				case 'B': if (y < lines - 1) y++; break;
				case 'C': if (x < cols - 1) x++; break;
				case 'D': if (x != 0) x--; break;
			}
		}
		
		else if (mode == 1 && key != ' ') for (uint8_t i = 0; i < sizeof(accepted); i++) if (accepted[i] == key) 
		{
			character[(y * cols) + x] = key;
			if (y * cols + x < lines * cols && x == cols - 1) 
			{
				y++;
				x = 0;
			}
			
		}
		
		if (key == 'q' && mode == 0)
		{
			cout << "\e[?25h" << endl;
			return 0;
		}
		
		if (mode == 0)
		{	
			if (key == '1') color[(y * cols) + x] = 1;
			else if (key == '2') color[(y * cols) + x] = 2;
			else if (key == '3') color[(y * cols) + x] = 3;
			else if (key == '4') color[(y * cols) + x] = 4;
			else if (key == '5') color[(y * cols) + x] = 5;
			else if (key == '6') color[(y * cols) + x] = 6;
			else if (key == '7') color[(y * cols) + x] = 7;
			else if (key == '8') color[(y * cols) + x] = 8;
		
			//bold
			else if (key == '!') color[(y * cols) + x] = 11;
			else if (key == '@') color[(y * cols) + x] = 12;
			else if (key == '%') color[(y * cols) + x] = 15;
			else if (key == '^') color[(y * cols) + x] = 16;
			else if (key == '&') color[(y * cols) + x] = 17;
			else if (key == '*') color[(y * cols) + x] = 18;
		}
		
		if (key == 127)
		{
			color[(y * cols) + x] = 0;
			character[(y * cols) + x] = 0;
		}
		
		if (key == 'r' && mode == 0)
		{
			char c;
			cout << "\e[?25h";
			system("clear");
			cout << "Would you like to reset this grid?: ";
			cin >> c;
			if (c == 'y' || c == 'Y') for (uint16_t i = 0; i < cols * lines; i++) color[i] = 0;
			cout << "\e[?25l";
		}
		
		if (key == '0' && mode == 0)
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
					for (uint16_t i = 0; i < lines * cols; i++) file << char(color[i]);
					for (uint16_t i = 0; i < lines * cols; i++) file << char(character[i]);
				}
				
				else
				{
					if (dir(dirpath.c_str()))
					{
						file.open(str, ios::binary | ios::out);
						file << char(cols) << char(lines);
						for (uint16_t i = 0; i < lines * cols; i++) file << char(color[i]);
						for (uint16_t i = 0; i < lines * cols; i++) file << char(character[i]);
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
		
		if (key == ';')
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
				if (cols > w.ws_col || lines >> w.ws_row || cols > 48 || lines > 48) 
				{
					cols = backx;
					lines = backy;
				}
				x = 0;
				y = 0;
				for (uint16_t i = 0; i < size(color); i++) color.pop_front();
				for (uint16_t i = 0; i < lines * cols; i++) color.push_front(0);
				
				for (uint16_t i = 0; i < size(color); i++) character.pop_front();
				for (uint16_t i = 0; i < lines * cols; i++) character.push_front(0);
			}
			cout << "\e[?25l";
		}
		
		if (key == 'h' && exit && mode == 0)
		{
			exit = false;
			system("clear");
			cout << "termpaint: an application used to paint inside of a terminal - press keyboard keys to paint or do commands" << endl << endl << "(Press corresponding key on keyboard) Possible commands:" << endl << endl << "0  :  save file\n1  :  paint white  \033[37m■\033[0m  r\n";
			cout << "2  :  paint red    \033[0;31m■\033[0m  a\n3  :  paint orange \033[0;33m■\033[0m  i\n4  :  paint yellow \033[1;33m■\033[0m  n\n5  :  paint green  \033[0;32m■\033[0m  b\n6  :  paint cyan   \033[0;36m■\033[0m  o\n7  :  paint blue   \033[0;34m■\033[0m  w\n8  :  paint purple \033[0;35m■\033[0m  !";
			cout << "\nr  :  reset canvas\n;  :  resize canvas\nh  :  get help or exit help\nq  :  exit program without saving\nw or up arrow  :  move Y position up by one\na or left arrow  :  move X position left by one\ns or down arrow  :  move Y posiiton down by one\nd or right arrow  :  move X position right by one\n";
			cout << "~  :  switch between typing mode and coloring/command mode\n\nPressing shift + the number you want to paint will give a lighter version of that color except for orange and yellow which do not have that function\nPress enter to continue";
			cin.ignore();
		}
		
		else if (key == 'h' && !exit) exit = true;
		
		if (key == '~')
		{
			if (mode == 0) mode = 1;
			else if (mode == 1) mode = 0;
		}
		setarea();
	}
	return 0;
}

int gkey() 
{
  system("/bin/stty raw");
  int c;
  system("/bin/stty -echo");
  c = getc(stdin);
  system("/bin/stty echo");
  system("/bin/stty cooked");
  return c;
}

void setarea()
{
	system("clear");
	cout << "IRRADIX TERMPAINT - ";
	if (cols < 10) cout << "0";
	cout << uint16_t(cols) << "x";
	if (lines < 10) cout << "0";
	cout << uint16_t(lines) << " canvas";
	cout << endl << " ";
	for (uint8_t i = 0; i < cols; i++) cout << "__";
	cout << endl;
	for (uint16_t i = 0; i < lines; i++)
	{
		cout << "|";
		for (uint16_t j = 0; j < cols; j++)
		{
			if ((y * cols) + x == (i * cols) + j)
			{
				if (character[(i * cols) + j] == 0)
				{
					if (color[(i * cols) + j] == 0) cout << " \033[4m \033[0m";
					else if (color[(i * cols) + j] == 1) cout << " \033[4m\033[37m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 2) cout << " \033[4m\033[31m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 3) cout << " \033[4m\033[33m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 4) cout << " \033[4m\033[1;33m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 5) cout << " \033[4m\033[32m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 6) cout << " \033[4m\033[36m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 7) cout << " \033[4m\033[34m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 8) cout << " \033[4m\033[35m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 11) cout << " \033[4m\033[1;37m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 12) cout << " \033[4m\033[1;31m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 15) cout << " \033[4m\033[1;32m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 16) cout << " \033[4m\033[1;36m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 17) cout << " \033[4m\033[1;34m■\033[0m\033[0m";
					else if (color[(i * cols) + j] == 18) cout << " \033[4m\033[1;35m■\033[0m\033[0m";
				}
				
				else
				{
					if (color[(i * cols) + j] == 0) cout << " \033[4m" << char(character[(i * cols) + j]) << "\033[0m";
					else if (color[(i * cols) + j] == 1) cout << " \033[4m\033[37m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 2) cout << " \033[4m\033[31m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 3) cout << " \033[4m\033[33m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 4) cout << " \033[4m\033[1;33m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 5) cout << " \033[4m\033[32m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 6) cout << " \033[4m\033[36m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 7) cout << " \033[4m\033[34m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 8) cout << " \033[4m\033[35m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 11) cout << " \033[4m\033[1;37m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 12) cout << " \033[4m\033[1;31m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 15) cout << " \033[4m\033[1;32m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 16) cout << " \033[4m\033[1;36m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 17) cout << " \033[4m\033[1;34m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
					else if (color[(i * cols) + j] == 18) cout << " \033[4m\033[1;35m" << char(character[(i * cols) + j]) << "\033[0m\033[0m";
				}
			}
			
			else
			{
				if (character[(i * cols) + j] == 0)
				{
					if (color[(i * cols) + j] == 0) cout << "  ";
					else if (color[(i * cols) + j] == 1) cout << " \033[37m■\033[0m";
					else if (color[(i * cols) + j] == 2) cout << " \033[31m■\033[0m";
					else if (color[(i * cols) + j] == 3) cout << " \033[33m■\033[0m";
					else if (color[(i * cols) + j] == 4) cout << " \033[1;33m■\033[0m";
					else if (color[(i * cols) + j] == 5) cout << " \033[32m■\033[0m";
					else if (color[(i * cols) + j] == 6) cout << " \033[36m■\033[0m";
					else if (color[(i * cols) + j] == 7) cout << " \033[34m■\033[0m";
					else if (color[(i * cols) + j] == 8) cout << " \033[35m■\033[0m";
					else if (color[(i * cols) + j] == 11) cout << " \033[1;37m■\033[0m";
					else if (color[(i * cols) + j] == 12) cout << " \033[1;31m■\033[0m";
					else if (color[(i * cols) + j] == 15) cout << " \033[1;32m■\033[0m";
					else if (color[(i * cols) + j] == 16) cout << " \033[1;36m■\033[0m";
					else if (color[(i * cols) + j] == 17) cout << " \033[1;34m■\033[0m";
					else if (color[(i * cols) + j] == 18) cout << " \033[1;35m■\033[0m";
				}
				
				else
				{
					if (color[(i * cols) + j] == 0) cout << " " << char(character[(i * cols) + j]);
					if (color[(i * cols) + j] == 1) cout << " \033[37m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 2) cout << " \033[31m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 3) cout << " \033[33m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 4) cout << " \033[1;33m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 5) cout << " \033[32m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 6) cout << " \033[36m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 7) cout << " \033[34m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 8) cout << " \033[35m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 11) cout << " \033[1;37m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 12) cout << " \033[1;31m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 15) cout << " \033[1;32m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 16) cout << " \033[1;36m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 17) cout << " \033[1;34m" << char(character[(i * cols) + j]) << "\033[0m";
					if (color[(i * cols) + j] == 18) cout << " \033[1;35m" << char(character[(i * cols) + j]) << "\033[0m";
				}
			}
			
		}
		cout << "|" << endl;
	} 
	cout << " ";
	for (uint8_t i = 0; i < cols; i++) cout << "⎺⎺";
	if (mode == 0) cout << endl << "Double-click the 'h' key for help";
	if (mode == 1) cout << "\nText mode enabled - arrow key movement only and you may not resize the canvas, save the file, or reset the canvas - press the '~' key to return to command/paint mode";
}

int dir(const char *path)
{
    struct stat stats;
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode)) return 1;
    return 0;
}
