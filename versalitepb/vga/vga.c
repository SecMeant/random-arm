int volatile *fb;
int WIDTH = 640;
int fbuf_init(int mode)
{
  fb = (int *)(0x200000);
  *(volatile unsigned int *)(0x1000001c) = 0x2c77;
  *(volatile unsigned int *)(0x10120000) = 0x3f1f3f9c;
  *(volatile unsigned int *)(0x10120004) = 0x090b61df;
  *(volatile unsigned int *)(0x10120008) = 0x067f1800;

  *(volatile unsigned int *)(0x10120010) = 0x200000; // fbuf
  *(volatile unsigned int *)(0x10120018) = 0x82b;
}
