#include "TestRegion.h"
#include <iostream>


TestRegion::TestRegion(unsigned int maxRadius, unsigned int mPrecacheLayerCount)
  : Region(maxRadius, mPrecacheLayerCount)
{

}


TestRegion::~TestRegion(void)
{
}


void TestRegion::Print()
{
  for(unsigned int z = 0; z < mMaxSideSize; z++)
  {
    for(unsigned int y = 0; y < mMaxSideSize; y++)
    {
      for(unsigned int x = 0; x < mMaxSideSize; x++)
      {
        std::cout << mRegion[z * mMaxSideSize * mMaxSideSize + y * mMaxSideSize + x] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
  }
}

int TestRegion::NewElement(const Vector3i &pos)
{
  return 1;
}


void TestRegion::DeleteElement(int element, const Vector3i &pos)
{

}
