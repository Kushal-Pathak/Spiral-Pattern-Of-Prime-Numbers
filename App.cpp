#include <iostream>
#include <cmath>
#include <conio.h>
#include <windows.h>
#define graph_height 500 // array height
#define graph_width 500 // array width
#define screen_height 49 // screen height
#define screen_width 105 // screen width
#define block (char)254 // pixel display
using namespace std;

int cx = screen_width / 2, cy = screen_height / 2; // center of screen 
int gx = graph_width / 2, gy = graph_height / 2; // center of graph of spiral world
int x = gx - cx, y = gy - cy; // starting coordinate value for rendering a certain portion of the spiral world
char buffer[graph_height][graph_width]; // array to store pixels

void init_buffer(); // initialize buffer with empty space
int is_prime(int); // returns 1 if prime number else returns 0
void prime_spirals(float,int); // function for calculation of location of the spiral pixels, takes scale and maxvalue as parameter
void control(int); // to navigate around the spiral coordinates
void formatted_render(); // to display a particular portion of the spiral coordinates
void maximizeWindow();

int main() {
	init_buffer();
	maximizeWindow();
	cout << "Navigation controls: " << endl;
	cout << "a: left  d: right  w: top  s: bottom" << endl;
	cout << "Press any key to start navigating Prime Spiral World" << endl;
	char ch = _getch();
	prime_spirals(100, 50000);
	while (1) {
		formatted_render();
		control(5); // takes parameter in integer as speed
		Sleep(100);
	}
	return 0;
}

void control(int speed) {
	if (_kbhit()) {
		char c = _getch();
		switch (c) {
		case 'a':
			x -= speed;
			break;
		case 'd':
			x += speed;
			break;
		case 'w':
			y -= speed;
			break;
		case 's':
			y += speed;
			break;
		}
	}
}

void formatted_render() {
	system("cls");
	for (int i = y; i < y + screen_height; i++) {
		for (int j = x; j < x + screen_width; j++) {
			cout << buffer[i][j]<<" ";
		}
		cout << endl;
	}
	cout << "X: " << x << ", Y: " << y;
}

void init_buffer() {
	for (int i = 0; i < graph_height; i++) {
		for (int j = 0; j < graph_width; j++) {
			buffer[i][j] = ' ';
		}
	}
}

int is_prime(int n) {
	for (int j = 2; j <= n/2; j++) {
		if (n % j == 0) return 0;
	}
	return 1;
}

void prime_spirals(float scale, int max) {
	int x = 0, y = 0;
	for (int i = 1; i < max; i++) {
		if (is_prime(i)) {
			x = (int)round(i * cos(i));
			y = (int)round(i * sin(i));
			x = (int)round(x / scale) + gx;
			y = (int)round(y / scale) + gy;
			if (x > -1 && x < graph_width - 1 && y > -1 && y < graph_height - 1) {
				buffer[y][x] = block;
			}
		}
	}
}

void maximizeWindow() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}