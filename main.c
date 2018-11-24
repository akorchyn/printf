#include <stdio.h>
#include "ft_printf.h"
#include <locale.h>
int	main(void) {
	char *b;

	long x = 4294967296;
	long double a = 340282346638528859811704183484516925434.777770000;
	char* l = setlocale(LC_ALL, "");
//	printf("%i\n", printf("%C\n", 159));
//	fflush(stdout);
	wchar_t kk;
	kk = 945;
	printf("Ret value : %i\n", printf("{%30S}", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
	fflush(stdout);
	printf("Ret value : %i\n", ft_printf("{%30S}", L"жM-M-^QжM-^XѓдЄM-еM-^O™зM-^LЂгM-M-^B"));
//	printf("Ret value : %i\n", ft_printf("My:       %Lf\n", a));
	//print_unicode(94+5);
//	printf("%d", 128 | (945 >> 0) - (945 >> 6);
//	char 	arr[2];
//	arr[0] = (945 >> 6) | 0b11000000;
//	arr[1] = 0b10000000 | (945 & 63);
//	write(1, arr, 2);

}
