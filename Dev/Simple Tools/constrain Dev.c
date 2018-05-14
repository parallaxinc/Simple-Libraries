#include "simpletools.h"


int main()
{
  int val;
  //while(1)
  {
    int val;
    float fval;
    val = constrainInt(10, 1, 2);
    print("val = %d\r", val);
    val = constrainInt(-10, 1, 2);
    print("val = %d\r", val);
    val = constrainInt(1, 1, 2);
    print("val = %d\r", val);
    val = constrainInt(10, -3, -1);
    print("val = %d\r", val);
    val = constrainInt(-10, -3, -1);
    print("val = %d\r", val);
    val = constrainInt(-1, -3, -1);
    print("val = %d\r", val);
    val = constrainInt(-2, -3, -1);
    print("val = %d\r", val);
    val = constrainInt(-3, -3, -1);
    print("val = %d\r", val);
    fval = constrainFloat(10.0, 1.0, 2.0);
    print("fval = %f\r", fval);
    fval = constrainFloat(10.0, -3.0, -1.0);
    print("fval = %f\r", fval);
    fval = constrainFloat(2.0, -3.0, -1.0);
    print("fval = %f\r", fval);
    fval = constrainFloat(-2.0, -3.0, -1.0);
    print("fval = %f\r", fval);

  }    
}

