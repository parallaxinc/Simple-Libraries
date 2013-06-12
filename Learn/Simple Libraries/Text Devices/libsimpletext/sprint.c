/*
 * very simple printf, adapted from one written by me
 * for the MiNT OS long ago
 * placed in the public domain
 *   - Eric Smith
 * 32 bit mode only. %b, %e, %f, %g added by Steve Denson
 */
#include <ctype.h>
#include <stdarg.h>
#include "simpletext.h"

/*
 * very simple printf -- just understands a few format features
 */

static int SPUTC(int c, char *buf)
{
  *buf++ = c;
  return 1;
}

static int SPUTS(char *s, char *obuf)
{
  char *buf = obuf;
    while (*s) {
      buf += SPUTC(*s++, buf);
    }
    return buf-obuf;
}


static int SPUTL(unsigned long u, int base, int width, int fill_char, char *obuf)
{
  int r = 0;
  static char outbuf[32];
  char *t;
  char *buf = obuf;

  t = outbuf;

  do {
    *t++ = "0123456789abcdef"[u % base];
    u /= base;
    width--;
  } while (u > 0);

  while (width-- > 0) {
    buf += SPUTC(fill_char,buf);
    r++;
  }
  while (t != outbuf) {
    buf += SPUTC(*--t, buf);
    r++;
  }
  return buf-obuf;
}

static int _dosprnt(const char *fmt, va_list args, char *obuf)
{
  char c, fill_char;
  char *s_arg;
  int i_arg;
  long l_arg;
  int width;
  int precision;
  char fstr[20];

  char *buf = obuf;
  while( (c = *fmt++) != 0 ) {

    if (c != '%') {
      buf += SPUTC(c, buf);
      continue;
    }
    c = *fmt++;
    width = 0;
    precision = 6;
    fill_char = ' ';
    if (c == '0') fill_char = '0';
    while (c && isdigit(c)) {
      width = 10*width + (c-'0');
      c = *fmt++;
    }
    if(c == '.') {
      precision = 0;
      c = *fmt++;
      while (c && isdigit(c)) {
        precision = 10*precision + (c-'0');
        c = *fmt++;
      }
    }
    if (!c)
      break;

    switch (c) {

      case '%':
        buf += SPUTC(c, buf);
        break;
  
      case 'b':
          l_arg = va_arg(args, int);
        buf += SPUTL(l_arg, 2, width, fill_char, buf);
        break;
  
      case 'c':
        i_arg = va_arg(args, int);
        buf += SPUTC(i_arg, buf);
        break;
  
      case 's':
        s_arg = va_arg(args, char *);
        buf += SPUTS(s_arg, buf);
        break;
  
      case 'd':
      case 'u':
        l_arg = va_arg(args, int);
        if (l_arg < 0 && c == 'd') {
          buf += SPUTC('-', buf);
          width--;
          l_arg = -l_arg;
        }
        buf += SPUTL(l_arg, 10, width, fill_char, buf);
        break;
#if 0
      case 'e':
      case 'g':
      {
        union { float f; int i; } a;
        a.i = va_arg(args, int);
        buf += SPUTS(floatToScientific(a.f), buf);
        break;
      }
#endif
      case 'f': {
        double d = va_arg(args, double);
        buf += SPUTS(float2string((float) d, fstr, width, precision), buf);
        break;
      }

      case 'x': {
        l_arg = va_arg(args, unsigned int);
        buf += SPUTL(l_arg, 16, width, fill_char, buf);
        break;
      }
    }
  }
  *buf = '\0';
  return buf-obuf;
}

int sprint(char *buf, const char *fmt, ...)
{
  va_list args;
  int r;
  va_start(args, fmt);
  r = _dosprnt(fmt, args, buf);
  va_end(args);
  return r;
}
