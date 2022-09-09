#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int my_putchar(char c) {
  return write(1, &c, 1);
}

int my_putstr(char *str) {
  int index = 0;
  
  while (str[index] != '\0') {
    my_putchar(str[index]);
    index += 1;
  }
  return index;
}

size_t	hexalow(unsigned long n)
{
	static size_t	i;
	const char		*hex;

	hex = "0123456789abcdef";
	i = 0;
	if (n >= 16)
	{
		hexalow(n / 16);
	}
	i += my_putchar(hex[n % 16]);
	return (i);
}

size_t	ft_p(unsigned long int p)
{
	size_t	j;

	j = 2;
	write(1, "0", 1);
	write(1, "x", 1);
	j += hexalow(p);
	return (j);
}

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}

int changeChar(va_list *arg, char flag) {
  int sum = 0;
  char c;
  char *str;
  unsigned int i;

  if (flag == 's') {
    str = va_arg(*arg, char *);
    if(str == NULL){
        sum += my_putstr("(NULL)");
    }
    if (str) {
      sum += my_putstr(str);
    }
  }
  else if (flag == 'c') {
    c = va_arg(*arg, int);
    sum += my_putchar(c);    
  }
  else if (flag == 'd' ) {
    i = va_arg(*arg,int);
    
    if(i<0) 
    {
        i = -i;
        my_putchar('-'); 
    } 
    sum += my_putstr(convert(i,10));  
  }
  else if (flag == 'u') {
    i = va_arg(*arg, unsigned int);
    sum += my_putstr(convert(i,10)); 
  }
  else if (flag == 'x') {
    i = va_arg(*arg,unsigned int);
    puts(convert(i,16));    
  }
  else if (flag == 'o') {
    i = va_arg(*arg,unsigned int);
    puts(convert(i,8));    
  }
  else if (flag == 'p') {
    c = ft_p(va_arg(*arg, unsigned long int));
    
    sum += my_putchar(c);    
  }
  return sum;
}

int my_printf(char* format, ...) {
  va_list arg;
  int index = 0;
  int flag_spotted = 0;
  int sum = 0;

  va_start(arg, format); 
  while (format[index] != 0)
  {
    if (flag_spotted == 1) {
      sum += changeChar(&arg, format[index]);
      flag_spotted = 0;
    }
    else if (format[index] == '%') {
      flag_spotted = 1;
    }
    else {
      sum += my_putchar(format[index]);
    }
    index += 1;
  }
  va_end(arg);
  return sum;
}