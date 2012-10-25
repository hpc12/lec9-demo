int main()
{
  int result = 0;

  {
    double 
      x00 = 0,
      x01 = 3,
      x02 = 1,
      x03 = 5,
      x04 = 2,
      x05 = 8,
      x06 = 9,
      x07 = 11,
      x08 = 99,
      x09 = 111,
      x10 = 33+0,
      x11 = 33+3,
      x12 = 33+1,
      x13 = 33+5,
      x14 = 33+2,
      x15 = 33+8,
      x16 = 33+9,
      x17 = 33+11,
      x18 = 33+99,
      x19 = 33+111,
      x20 = 17+0,
      x21 = 17+3,
      x22 = 17+1,
      x23 = 17+5,
      x24 = 17+2,
      x25 = 17+8,
      x26 = 17+9,
      x27 = 17+11,
      x28 = 17+99,
      x29 = 17+111;

      double a = 0;
      for (int i = 0; i< 1000*1000; ++i)
      {
#define ALL (\
    x00 + x01 + x02 + x03 + x04 + x05 + x06 + x07 + x08 + x09 /*+ \
    x10 + x11 + x12 + x13 + x14 + x15 + x16 + x17 + x18 + x19 + \
    x20 + x21 + x22 + x23 + x24 + x25 + x26 + x27 + x28 + x29 */\
    )

        x00 += i*ALL;
        x01 += i*ALL;
        x02 += i*ALL;
        x03 += i*ALL;
        x04 += i*ALL;
        x05 += i*ALL;
        x06 += i*ALL;
        x07 += i*ALL;
        x08 += i*ALL;
        x09 += i*ALL;
        /*
        x10 += i*ALL;
        x11 += i*ALL;
        x12 += i*ALL;
        x13 += i*ALL;
        x14 += i*ALL;
        x15 += i*ALL;
        x16 += i*ALL;
        x17 += i*ALL;
        x18 += i*ALL;
        x19 += i*ALL;
        x20 += i*ALL;
        x21 += i*ALL;
        x22 += i*ALL;
        x23 += i*ALL;
        x24 += i*ALL;
        x25 += i*ALL;
        x26 += i*ALL;
        x27 += i*ALL;
        x28 += i*ALL;
        x29 += i*ALL;
        */
      }
      result += ALL;
    }

  return result;
}

