#pragma once

#ifndef TestRegion_h__
#define TestRegion_h__

#include "region.h"

class TestRegion : public Region<int, 0>
{
public:
  TestRegion(unsigned int maxRadius, unsigned int mPrecacheLayerCount);
  ~TestRegion(void);

  void Print();

protected:

  int NewElement(const Vector3i &pos);                        // Добавляем новый элемент в заданную позицию
  void DeleteElement(int element, const Vector3i &pos);      // Элемент больше не нужен, удалим

};



#endif // TestRegion_h__
