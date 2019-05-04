int v[] = {1,2,3,4,5,6,7,8,9,10};
int sum;

#include "string.c"
#include "uart.c"

int main()
{
  int i;
  char string[64];
  UART *up;
  uart_init();
  up = &uart[0];
  uprints(up, "Enter lines from serial terminal 0\n\r");
  while(1)
  {
    ugets(up, string);
    uprints(up, "    ");
    uprints(up, string);
    uprints(up, "\n\r");
    if(strcmp(string, "end")==0)
      break;
  }
  uprints(up, "Compute sum of array:\n\r");
  sum = 0;
  for(i = 0; i < 10; ++i)
    sum += v[i];
  uprintf(up, "sum = %d %c ASDF %c\r\n", sum, 'Z', 'G');
  uprints(up, "\n\rEND OF RUN\n\r");
}
