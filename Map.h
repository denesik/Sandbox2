#pragma once

#ifndef Map_h__
#define Map_h__

#include "Sector.h"


class Map
{
public:
  Map(void);
  ~Map(void);

  void LoadSector();  // ��������� ������

  bool IsSectorLoaded();  // �������� �� ������?

  Sector *OwnSector();
  void ReleaseSector(Sector *sector);

};



#endif // Map_h__
