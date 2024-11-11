/* Header file with specific GALAKSIJA functions */

#define z80_bpoke(a,b)  (*(unsigned char *)(a) = b)
#define z80_wpoke(a,b)  (*(unsigned int *)(a) = b)
#define z80_lpoke(a,b)  (*(unsigned long *)(a) = b)
#define z80_bpeek(a)    (*(unsigned char *)(a))
#define z80_wpeek(a)    (*(unsigned int *)(a))
#define z80_lpeek(a)    (*(unsigned long *)(a))

unsigned char _scr_x, _scr_y;

// Clear the screen (generic or VT100 console)
void gal_cls() { 
	_scr_x = 0;
	_scr_y = 0;
	printf("%c",12);
	printf("\x0c");
}

// Set internal position of cursor for low-level putc and call gotoxy
void gal_gotoxy(char x, char y) {
	_scr_x = x;
	_scr_y = y;
}

// Low-level write character to internal cursor position
void gal_putc(char ch) {
	z80_bpoke(0x2800 + (_scr_y << 5) + _scr_x, ch);
	_scr_x++;
	if (_scr_x > 32) {
		_scr_x = 0;
		_scr_y++;
	}
}

// Low-level write string to internal cursor position
int gal_puts (char *str) {
	char ch;
	int len = 0;
	while ((ch = *str) != 0x0) {
		z80_bpoke(0x2800 + (_scr_y << 5) + _scr_x, ch);
		str++;
		len++;
		_scr_x++;
		if (_scr_x > 32) {
			_scr_x = 0;
			_scr_y++;
		}
	}
	return len;
}
