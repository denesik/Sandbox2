#pragma once

#ifndef RenderRegion_h__
#define RenderRegion_h__

#include "region.h"

class Sector;
class Render;
class Camera;

class RenderRegion : public Region<Sector *, nullptr>
{
public:
  RenderRegion(void);
  ~RenderRegion(void);

  void Load(const Camera &camera);                  // ��������� ������ ��� �������� ������
  void Draw(const Camera &camera, Render *render);  // ���������� ������ � ������� ��������� ������� � ������

private:

  Vector3i mMapCenterPos;

protected:

  Sector *NewElement(const Vector3i &pos);                       // �� ����� �������� ����� ������� � �������� �������
  void DeleteElement(Sector *element, const Vector3i &pos);      // ��� ������ �� ����� ���� �������

};



#endif // RenderRegion_h__
