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

  void Load(const Camera &camera);                  // Загрузить регион для заданной камеры
  void Draw(const Camera &camera, Render *render);  // Нарисовать регион с помощью заданного рендера и камеры

private:

  Vector3i mMapCenterPos;

protected:

  Sector *NewElement(const Vector3i &pos);                       // Мы хотим добавить новый элемент в заданную позицию
  void DeleteElement(Sector *element, const Vector3i &pos);      // Нам больше не нужен этот элемент

};



#endif // RenderRegion_h__
