#include "RenderRegion.h"



RenderRegion::RenderRegion(void)
  : Region(7, 0)
{

}

RenderRegion::~RenderRegion(void)
{

}

void RenderRegion::Draw(const Camera &camera, Render *render)
{

}

Sector *RenderRegion::NewElement(const Vector3i &pos)
{
  return nullptr;
}

void RenderRegion::DeleteElement(Sector *element, const Vector3i &pos)
{

}

void RenderRegion::Load(const Camera &camera)
{

}
