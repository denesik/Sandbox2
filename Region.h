#pragma once

#ifndef Region_h__
#define Region_h__

#include "Sector.h"
#include <Eigen/Dense>

#include <assert.h>

using Eigen::Vector3i;
using Eigen::Vector3f;

template<class Type, Type defaultValue>
class Region
{
public:
  Region(const unsigned int maxRadius, const unsigned int precacheLayerCount);
  virtual ~Region();

  void SetRadius(unsigned int radius);

  void Move(unsigned int w, unsigned int h, unsigned int d); // ������������ �� ��������� ��������


protected:

  const unsigned int mPrecacheLayerCount;   // ������� ����� �� ����� �������������� ���������
  const unsigned int mMaxRadius;            // ������������ ������ �������, � ������ mPrecacheLayerCount
  const unsigned int mCenter;               // ���������� ������
  const unsigned int mMaxSideSize;          // ������������ ������ ������� �������

  unsigned int mRadius;                     // ������� ������
  Type *mRegion;                            // ��������� �� ������

protected:

  virtual Type NewElement(const Vector3i &pos) = 0;                   // �� ����� �������� ����� ������� � �������� �������
  virtual void DeleteElement(Type element, const Vector3i &pos) = 0;  // ��� ������ �� ����� ���� �������

};




template<class Type, Type defaultValue>
Region<Type, defaultValue>::Region(const unsigned int maxRadius, const unsigned int precacheLayerCount)
  : mMaxRadius(maxRadius), 
  mPrecacheLayerCount(precacheLayerCount),
  mMaxSideSize((mMaxRadius + mPrecacheLayerCount) * 2 + 1),
  mCenter(maxRadius + mPrecacheLayerCount)
{
  mRadius = 0;
  mRegion = new Type[mMaxSideSize * mMaxSideSize * mMaxSideSize];

  for(unsigned int i = 0 ; i < mMaxSideSize * mMaxSideSize * mMaxSideSize; i++)
  {
    mRegion[i] = defaultValue;
  }
}


template<class Type, Type defaultValue>
Region<Type, defaultValue>::~Region()
{
  delete[] mRegion;
}


template<class Type, Type defaultValue>
void Region<Type, defaultValue>::SetRadius(unsigned int radius)
{
  // ����� ������ �� ������ ��������� ������������� ������� 
  assert(radius + mPrecacheLayerCount <= mMaxRadius);

  unsigned int or = mRadius + mPrecacheLayerCount;
  unsigned int nr = radius + mPrecacheLayerCount;

  for(unsigned int z = 0; z < mMaxSideSize; z++)
    for(unsigned int y = 0; y < mMaxSideSize; y++)
      for(unsigned int x = 0; x < mMaxSideSize; x++)
      {
        unsigned int offset = z * mMaxSideSize * mMaxSideSize + y * mMaxSideSize + x;
        if(x < mCenter - nr || x > mCenter + nr ||
           y < mCenter - nr || y > mCenter + nr ||
           z < mCenter - nr || z > mCenter + nr)
        {
          // ������ ���� �� ��������� ������ �������
          DeleteElement(mRegion[offset], Vector3i(x, y, z));
          mRegion[offset] = defaultValue;
        }
        else
        if(x < mCenter - or || x > mCenter + or ||
           y < mCenter - or || y > mCenter + or ||
           z < mCenter - or || z > mCenter + or)
        {
          // ��������� �������� �� ���������, ���� � �������� ������ �������, �� �� ��������� �������
          mRegion[offset] = defaultValue;
        }
      }

  mRadius = radius;
}


template<class Type, Type defaultValue>
void Region<Type, defaultValue>::Move(unsigned int w, unsigned int h, unsigned int d)
{
  if(w == 0 && h == 0 && d == 0)
    return;

  unsigned int r = mRadius + mPrecacheLayerCount;
  if(w > r || h > r || d > r)
  {
    // �� ������������� ������� ������
    for(unsigned int z = mCenter - r; z <= mCenter + r; z++)
      for(unsigned int y = mCenter - r; y <= mCenter + r; y++)
        for(unsigned int x = mCenter - r; x <= mCenter + r; x++)    
        {
          unsigned int offset = z * mMaxSideSize * mMaxSideSize + y * mMaxSideSize + x;
          DeleteElement(mRegion[offset], Vector3i(x, y, z));
          mRegion[offset] = NewElement(Vector3i(x, y, z));
        }
  }
  else
  {
    unsigned int regionSideSize = r * 2 + 1;
    Type *mRegionTemp = new Type[regionSideSize * regionSideSize * regionSideSize];

    unsigned int regionOffset = mCenter - r;
    for(unsigned int z = 0; z < regionSideSize; z++)
      for(unsigned int y = 0; y < regionSideSize; y++)
        for(unsigned int x = 0; x < regionSideSize; x++)
        {
          mRegionTemp[z * regionSideSize * regionSideSize + y * regionSideSize + x] = 
            mRegion[(z + regionOffset) * mMaxSideSize * mMaxSideSize + (y + regionOffset) * mMaxSideSize + x + regionOffset];
        }

    for(unsigned int z = mCenter - r; z <= mCenter + r; z++)
      for(unsigned int y = mCenter - r; y <= mCenter + r; y++)
        for(unsigned int x = mCenter - r; x <= mCenter + r; x++)    
        {
          unsigned int offset = z * mMaxSideSize * mMaxSideSize + y * mMaxSideSize + x;
          unsigned int tx = x + w;
          unsigned int ty = y + h;
          unsigned int tz = z + d;

          if(x < mCenter - r + w || x > mCenter + r + w ||
             y < mCenter - r + h || y > mCenter + r + h ||
             z < mCenter - r + d || z > mCenter + r + d)
          {
            // ������ ���� �� ��������� ������ �������
            DeleteElement(mRegion[offset], Vector3i(x, y, z));
            mRegion[offset] = defaultValue;
          }

          if(tx < mCenter - r || tx > mCenter + r ||
             ty < mCenter - r || ty > mCenter + r ||
             tz < mCenter - r || tz > mCenter + r)
          {
            if(mRegion[offset] != defaultValue)
            {
              DeleteElement(mRegion[offset], Vector3i(x, y, z));
            }
            mRegion[offset] = NewElement(Vector3i(x, y, z));
          }
          else
          {
            mRegion[offset] = 
              mRegionTemp[(z - mCenter + r) * regionSideSize * regionSideSize + 
                          (y - mCenter + r) * regionSideSize + 
                           x - mCenter + r];
            if(mRegion[offset] == defaultValue)
            {
              mRegion[offset] = NewElement(Vector3i(x, y, z));
            }
          }
        }

    delete[] mRegionTemp;
  }
}


#endif // Region_h__
