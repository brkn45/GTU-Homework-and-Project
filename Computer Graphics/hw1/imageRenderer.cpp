#include "imageRenderer.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
using namespace parser;

namespace {

bool NotZero(const Vec3f vec) { return vec.x != 0 || vec.y != 0 || vec.z != 0; }

}  // namespace

const Vec3f ImageRenderer::CalculateS(int i, int j) const {
  return q + usu * (i + .5) - vsv * (j + .5);
}

const Vec3f ImageRenderer::TraceRay(const Ray& ray, int depth,const Object* hit_obj = nullptr) const {
  Vec3f color = scene_.background_color;
  const HitRecord hit_record =
      bounding_volume_hierarchy->GetIntersection(ray, hit_obj);
  const int material_id = hit_record.material_id;

  if (material_id != -1) {
    const Vec3f origin = ray.origin;
    const Vec3f direction = ray.direction;
    const Vec3f intersection_point = origin + direction * hit_record.t;
    const Vec3f normal = hit_record.normal;
    const Material material = scene_.materials[material_id];
    color = scene_.ambient_light.PointWise(material.ambient);

    for (const PointLight& light : scene_.point_lights) {
      // Shadow check
      const Vec3f wi = light.position - intersection_point;
      const Vec3f wi_normal = wi.Normalized();
      const Ray shadow_ray{
          intersection_point + wi_normal , wi_normal,
          true};
      if (bounding_volume_hierarchy->GetIntersection(
              shadow_ray, wi.Length() ,
              hit_record.obj)) {
        continue;
      }
      const float r_square = wi * wi;
      const Vec3f intensity = light.intensity / r_square;

      // Diffuse light
      const float cos_theta = wi_normal * normal;
      const float cos_thetap = cos_theta > 0. ? cos_theta : 0.;
      color += (material.diffuse * cos_thetap).PointWise(intensity);

      // Specular light
      const Vec3f h = (wi_normal - direction).Normalized();
      const float cos_alpha = normal * h;
      const float cos_alphap = cos_alpha > 0. ? cos_alpha : 0.;
      color += (material.specular * pow(cos_alphap, material.phong_exponent))
                   .PointWise(intensity);
    }
    // Specular reflection
    if (depth > 0 && NotZero(material.mirror)) {
      const Vec3f wi =
          (direction + normal * -2 * (direction * normal)).Normalized();
      const Ray reflection_ray{
          intersection_point + wi , wi, false};
      color += TraceRay(reflection_ray, depth - 1, hit_record.obj).PointWise(material.mirror);
    }
  }
  return color;
}

const Vec3i ImageRenderer::RenderPixel(int i, int j,const Camera& camera) const {
  const Vec3f origin = camera.position;
  const Vec3f direction = (CalculateS(i, j) - origin).Normalized();
  const Ray ray{origin, direction, false};
  //std::cout<<"burada RenderPixel\n";
  return ImageRenderer::TraceRay(ray, scene_.max_recursion_depth).ToVec3i();
}

void ImageRenderer::RenderImage(const Camera& camera, Vec3i* result,const int min_height, const int max_height, const int width) const {
  for (int j = min_height; j < max_height; j++) {
    for (int i = 0; i < width; i++) {
      result[j * width + i] = RenderPixel(i, j, camera);
    }
  }
}

ImageRenderer::ImageRenderer(const char* scene_path) {
  scene_.loadFromXml(scene_path);
  for (Mesh& mesh : scene_.meshes) {
    for (Face& obj : mesh.faces) {
      objects_.push_back(&obj);
    }
  }
  bounding_volume_hierarchy = new BoundingVolumeHierarchy(&objects_);
}

void ImageRenderer::SetUpScene(const Camera& camera) {
  const Vec4f view_plane = camera.near_plane;
  const Vec3f gaze = camera.gaze.Normalized();
  const float dist = camera.near_distance;
  const float l = view_plane.x;
  const float r = view_plane.y;
  const float b = view_plane.z;
  const float t = view_plane.w;
  const Vec3f u = gaze.CrossProduct(camera.up).Normalized();
  const Vec3f v = u.CrossProduct(gaze);
  const Vec3f m = camera.position + gaze * dist;
  q = m + u * l + v * t;
  usu = u * (r - l) / camera.image_width;
  vsv = v * (t - b) / camera.image_height;
}