#include<stdio.h>

typedef struct AweStruct
{
  int charmed;
  int floored[2];
  
}AWESOME;


void main()
{
  AWESOME as, *asp, *aspa, asme[2];
  
  as.charmed = 1;
  as.floored[0] = 5;
  as.floored[1] = 6;
  
  asme[0].charmed = 2;
  asme[0].floored[0] = 7;
  asme[0].floored[1] = 77;
  
  asme[1].charmed = 3;
  asme[1].floored[0] = 71;
  asme[1].floored[1] = 777;
  
  printf("\nConnecting dots...%d %d %d\n", as.charmed, as.floored[0], as.floored[1]);
  
  asp = &as;
  
  printf("\nPointing...%d %d %d\n", asp->charmed, asp->floored[0], asp->floored[1]);
  
  aspa = asme;
  
  printf("\nPointing even more...%d %d %d %d %d %d\n", aspa->charmed, aspa->floored[0], aspa->floored[1], (aspa+1)->charmed, (aspa+1)->floored[0], (aspa+1)->floored[1]);
  
  
  
  
  
  


}
