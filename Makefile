all:
	zcc +gal -create-app  -pragma-redirect:fputc_cons=fputc_cons_generic -o 2048-gal 2048-gal.c
