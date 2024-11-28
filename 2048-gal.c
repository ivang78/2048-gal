#include <stdlib.h>
#include <conio.h>
#include "galaksija.h"

unsigned char c, d, a, won;
int f[17][17];
int score, bestscore, rnd;

// Print frame
void frame() {
	int x, y;
	gal_cls();	
	gal_gotoxy(11 ,3); gal_puts("2048 GAME");
	gal_gotoxy(11 ,4); 
	for (x = 0; x < 9; x++) {
		gal_putc(140);
	}
	gal_gotoxy(4,6);  gal_puts("ARROW KEYS - UP, DOWN");
	gal_gotoxy(4,7);  gal_puts("             LEFT, RIGHT");
	gal_gotoxy(4,8);  gal_puts("R - NEW GAME");
	gal_gotoxy(4,9);  gal_puts("DEL - QUIT");
	gal_gotoxy(4,10); gal_puts("PRESS ENTER");	
	gal_gotoxy(4, 13);gal_puts("BY IVAN ILYICHEV 2024"); 
	gal_gotoxy(0,0);
	gal_putc(215);
	for (x = 1; x <= 30; x++) {
		gal_putc(195);
	}
	gal_putc(149);
	for (y = 1; y <= 14; y++) {
		gal_gotoxy(0, y); gal_putc(213);
		gal_gotoxy(31,y); gal_putc(149);
	}
	gal_gotoxy(0,15);
	for (x = 0; x <= 30; x++) {
		gal_putc(131);
	}
	gal_putc(129);
}


// Print board
void print() {
	int nlen = 0;
	int x, y, z, ii;
	char nstr[10];
	for (y = 1; y <= d + 1; y++) {
		gal_gotoxy(5, y*3-1);
		for (x = 1; x <= d; x++) {
			if (y < d + 1) {
				if (x <= d) {
					gal_putc(215); // left top corner
					gal_putc(195); // top line
					gal_putc(195);
					gal_putc(195);
					gal_putc(195);
					if (x == d) {
						gal_putc(149); // right top corner
					}						
				}
			} else if (y == d + 1) {
				if (x <= d) {
					gal_putc(131); // left bottom corner
					gal_putc(131); // bottom line
					gal_putc(131);
					gal_putc(131);
					gal_putc(131);
					if (x == d) {
						gal_putc(129); // right bottom corner
					}
				}  
			}
		}
		if (y <= d) {
			for (z = 0; z <= 1; z++) {
				gal_gotoxy(5, y*3+z);
				for (x = 1; x <= d; x++) {
					gal_putc(213); // vertical left line 
					if (f[x][y] > 0) {
						if (z == 0) {
							itoa(f[x][y], nstr, 10);
							nlen = gal_puts(nstr);
							for (ii = 1; ii <= 4 - nlen; ii++) {
								gal_putc(32);
							}
						} else {
							gal_puts("    ");
						}
					} else {
						gal_puts("    ");
					}
				}
				gal_putc(149); // vertical right line
			}
		}
	}
	gal_gotoxy(11,0); gal_puts("      ");
	itoa(score, nstr, 10);
	gal_gotoxy(11,0); gal_puts(nstr);
	if (score > bestscore) {
		bestscore = score;
		gal_gotoxy(23,0); gal_puts("      ");
		itoa(bestscore, nstr, 10);
		gal_gotoxy(23,0); gal_puts(nstr);
	}
}

void you_win() {
	int x, y;
	gal_gotoxy(11, 7); gal_putc(213); gal_puts("YOU WIN!"); gal_putc(149);
	gal_gotoxy(11, 8); gal_putc(213); gal_puts("        "); gal_putc(149);
	gal_gotoxy(11, 6);
	gal_putc(215);
	for (x = 1; x <= 8; x++) {
		gal_putc(195);
	}
	gal_putc(149);
	gal_gotoxy(11,9);
	for (x = 1; x <= 9; x++) {
		gal_putc(131);
	}
	gal_putc(129);
	do {
		c = fgetc_cons();
	} while (c != 10);
}

void dshf(int x0, int y0, int dx, int dy) {
	int x, y, n;
	do {
		x = x0; 
		y = y0; 
		n = 0;
		do {
			x += dx; 
			y += dy;
			n = f[x][y];
		} while (!((n > 0) || (x < 1) || (x > d) || (y < 1) || (y > d)));
		if (n == 0) {
			return;
		}
		if (f[x0][y0] == 0) {
			f[x0][y0] = n; 
			f[x][y] = 0;
		} else {
			if (f[x0][y0] == n) {
				f[x0][y0] = 2 * n; 
				f[x][y] = 0; 
				score += 2 * n;
				if (2 * n == 2048) {
					won = 1;
				}
			}
			x0 += dx;
			y0 += dy;
		}
	} while (1);
}

void shft(int dx, int dy) {
	int x, y, n;
	for (n = 1; n <= d; n++) {
		if (dx == -1) dshf(1, n, 1, 0);
		if (dx == 1) dshf(d, n, -1, 0);
		if (dy == -1) dshf(n, 1, 0, 1);
		if (dy == 1) dshf(n, d, 0, -1);
	}
	n = 0;
	for (x = 1; x <= d; x++) {
		for (y = 1; y <= d; y++) {
			if (f[x][y] == 0) n++;
		}
	}
	if (n > 0) {
		do {
			x = (rand() / (RAND_MAX / d)) + 1; 
			y = (rand() / (RAND_MAX / d)) + 1;
		} while (f[x][y] != 0);
		f[x][y] = a;
	}
}

int main() {
	d = 4;
	frame();
	do {
		c = fgetc_cons();
	} while (c != 10);
	gal_cls();
	rnd = z80_wpeek(RND_ADDR);
	srand(rnd);
L1:
	won = 0;
	score = 0;
	memset(f, 0, sizeof(f));
	a = 2;
	shft(0, 0); 
	shft(0, 0);
	gal_gotoxy(4,0);  gal_puts("SCORE:");
	gal_gotoxy(17,0); gal_puts("BEST:");

	do {
		print();
		c = fgetc_cons();
		switch (c) {
			case 29: // left 
				shft(-1, 0);
				break;
			case 27: // up 
				shft(0, -1);
				break;
			case 28: // down
				shft(0, 1);
				break;
			case 30: // right
				shft(1, 0);
				break;
			case 82: // repeat
				goto L1;
			case 0:
				break;
			default:
				break;			
		}
		if (won == 1) {
			you_win();
			c = 0;
		}
	} while (c != 0);
	gal_cls();
	return 0;
}
