#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <Eigen/Dense>
#include "TestRegion.h"

const float eps = 0.0000000000001f;

const unsigned int greedCenter = 20;
const unsigned int greedSize = greedCenter * 2 + 1;
int greed[greedSize][greedSize];
//  амера всегда находитс€ в центре сетки

const unsigned int cellSize = 16; // в метрах

const float posx = 5.6f;  //  оординаты относительно начала блока в котором находимс€
const float posy = 3.7f;

const float dirx = -1;
const float diry = 0;


void RandGreed()
{

  for(unsigned int i = 0; i < greedSize; i++)
    for (unsigned int j = 0; j < greedSize; j++)
    {
      greed[i][j] = (rand() % 100) < 10 ? 1 : 0;
    }

}

void PrintGreed()
{
  for(unsigned int i = 0; i < greedSize; i++)
  {
    for (unsigned int j = 0; j < greedSize; j++)
    {
      printf("%i", greed[i][j]);
    }
    printf("\n");
  }
}





int main()
{
//   srand(unsigned int(time(nullptr)));
// 
//   RandGreed();
//   PrintGreed();
// 
//   int stepx = 0;
//   int stepy = 0;
// 
//   float tMaxX = 0.0f;
//   float tMaxY = 0.0f;
// 
//   if(dirx < 0)
//   {
//     stepx = -1;
//     tMaxX = posx / (stepx * dirx + eps);
//   }
//   else
//   {
//     stepx = 1;
//     tMaxX = (cellSize - posx) / (dirx + eps);
//   }
//   if(diry < 0)
//   {
//     stepy = -1;
//     tMaxY = posy / (stepy * diry + eps);
//   }
//   else
//   {
//     stepy = 1;
//     tMaxY = (cellSize - posy) / (diry + eps);
//   }
// 
//   // ¬ычисл€ем приращение по x и y дл€ блока.
//   float tDeltaX = cellSize / (stepx * dirx + eps);
//   float tDeltaY = cellSize / (stepy * diry + eps);
// 
//   unsigned int greedPosx = greedCenter;
//   unsigned int greedPosy = greedCenter;
// 
//   while(greedPosx < greedSize && greedPosx >= 0 && 
//         greedPosy < greedSize && greedPosy >= 0)
//   {
//     if(tMaxX < tMaxY)
//     {
//       tMaxX += tDeltaX;
//       greedPosx += stepx;
//     }
//     else
//     {
//       tMaxY += tDeltaY;
//       greedPosy += stepy;
//     }
//     if(greed[greedPosy][greedPosx] == 1)
//     {
//       break;
//     }
//   };
// 

  TestRegion testRegion(5, 0);

  testRegion.SetRadius(4);

  testRegion.SetRadius(2);

  testRegion.Move(1, 1, 1);

  testRegion.SetRadius(3);

  testRegion.SetRadius(2);

  testRegion.Print();

  system("pause");

  return 0;
}



// 
//
//
//
//
//
//
//








