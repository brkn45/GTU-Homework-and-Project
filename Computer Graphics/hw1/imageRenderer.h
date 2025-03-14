#ifndef _IMAGERENDERER_H
#define _IMAGERENDERER_H

#include "RayTracing.h"
#include "xmlParser.h"

class ImageRenderer {
 private:
  parser::Vec3f q, usu, vsv;
  parser::Scene scene_;
  std::vector<Object*> objects_;
  BoundingVolumeHierarchy* bounding_volume_hierarchy;

  const parser::Vec3f TraceRay(const Ray& ray, int depth,
                               const Object* hit_obj) const;
  const parser::Vec3f CalculateS(int i, int j) const;
  const parser::Vec3i RenderPixel(int i, int j,
                                  const parser::Camera& camera) const;

 public:
  ImageRenderer(const char* scene_path);

  void SetUpScene(const parser::Camera& camera);
  const std::vector<parser::Camera>& Cameras() const { return scene_.cameras; }

  void RenderImage(const parser::Camera& camera, parser::Vec3i* result,
                   const int min_height, const int max_height,
                   const int width) const;
};

#endif
