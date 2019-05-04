#include <stdarg.h>

#define TXFE 0x80
#define RXFF 0x40
#define TXFF 0x20
#define RXFE 0x10
#define BUSY 0x08

#define UDR 0x00
#define UFR 0x18

#define GETCHAR(c, fmt) \
  c = *fmt; \
  ++fmt;

#define VA_GET(ap, type) \
  *(type*)(ap); \
  ap += sizeof(type);

typedef volatile struct uart{
  char *base;
  int n;
}UART;

UART uart[4];

int uart_init()
{
  int i; UART *up;
  for(i=0; i<4; ++i)
  {
    up = &uart[i];
    up->base = (char*)(0x101f1000 + i*0x1000);
    up->n = i;
  }
  uart[3].base = (char *)(0x10009000);
}


int ugetc(UART *up)
{
  while(*(up->base+UFR) & RXFE);
  return *(up->base+UDR);
}

int uputc(UART *up, char c)
{
  while(*(up->base+UFR) & TXFF);
  return *(up->base+UDR) = c;
}

int ugets(UART *up, char *string)
{
  char c;
  int i = 0;

  while((c = ugetc(up)) != '\r')
  {
    string[i] = c;
    ++i;
  }

  string[i] = 0;
  return i;
}

int uprints(UART *up, const char *string)
{
  while(*string)
  {
    uputc(up, *string);
    ++string;
  }

  return 0;
}

__attribute__(( regparm(2) ))
int uprintf(UART *up, const char *fmt, ...)
{
  void *ap;
  char c;

  // Get stack base pointer for var arg
  asm("mov %0, %%fp"
      :"=r"(ap)
      :
      :);

  // point ap to beggining of var args
  ap += 4;

  while(1)
  {
    GETCHAR(c, fmt);

    if(c == 0)
      break;

    if(c == '%')
    {
      GETCHAR(c, fmt);

      switch(c)
      {
        // variable c can be reused in this switch
        // it will be read again on next loop iteration
        case 'd':
        {
          int pocket = VA_GET(ap, unsigned);

          while(pocket)
          {
            c = (char)(pocket%10) + '0';
            pocket /= 10;
            uputc(up, c);
          }
          break;
        }
        case 'c':
        {
          c = VA_GET(ap, char);
          uputc(up, c);
          break;
        }
        default:
          break;
      }
    }

    uputc(up, c);
  }

  return 0;
}




