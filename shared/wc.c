// John SchraderBachar - on line 20 I have an if statement checking for if the current character is a vowel, than increase vowel count. And then on line 40, I add the vowel count to the print statement to print the vowel count
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

void wc(int fd, char *name)
{
  int i, n;
  int l, w, c, v, inword;

  l = w = c = v = 0;
  inword = 0;
  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    for (i = 0; i < n; i++)
    {
      c++;
      if (buf[i] == 'a' || buf[i] == 'A' || buf[i] == 'e' || buf[i] == 'E' || buf[i] == 'i' || buf[i] == 'I' || buf[i] == 'o' || buf[i] == 'O' || buf[i] == 'u' || buf[i] == 'U')
      {
        v++;
      }
      if (buf[i] == '\n')
        l++;
      if (strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if (!inword)
      {
        w++;
        inword = 1;
      }
    }
  }
  if (n < 0)
  {
    printf("wc: read error\n");
    exit(1);
  }
  printf("%d %d %d %d %s\n", l, w, c, v, name);
}

int main(int argc, char *argv[])
{
  int fd, i;

  if (argc <= 1)
  {
    wc(0, "");
    exit(0);
  }

  for (i = 1; i < argc; i++)
  {
    if ((fd = open(argv[i], 0)) < 0)
    {
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }
    wc(fd, argv[i]);
    close(fd);
  }
  exit(0);
}
