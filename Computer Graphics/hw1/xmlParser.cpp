#include "xmlParser.h"
#include <sstream>
#include <stdexcept>
#include "tinyxml2.h"
#include <array>

std::array<float, 3> crossProduct(const std::array<float, 3>& v1, const std::array<float, 3>& v2) {
    std::array<float, 3> result;
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
  }

void parser::Scene::loadFromXml(const std::string& filepath) {
  tinyxml2::XMLDocument file;
  std::stringstream stream;

  auto res = file.LoadFile(filepath.c_str());
  if (res) {
    throw std::runtime_error("Error: The xml file cannot be loaded.");
  }

  auto root = file.FirstChild();
  if (!root) {
    throw std::runtime_error("Error: Root is not found.");
  }
  
  // Get BackgroundColor
  auto element = root->FirstChildElement("backgroundColor");
  if (element) {
    stream << element->GetText() << std::endl;
  } else {
    stream << "0 0 0" << std::endl;
  }
  stream >> background_color.x >> background_color.y >> background_color.z;
  //std::cout<<"burada 2\n";

 

  // Get MaxRecursionDepth
  element = root->FirstChildElement("maxraytracedepth");
  if (element) {
    stream << element->GetText() << std::endl;
  } else {
    stream << "0" << std::endl;
  }
  stream >> max_recursion_depth;

  // Get Cameras
  element = root->FirstChildElement("camera");
  
  Camera camera;
  while (element) {
    auto child = element->FirstChildElement("position");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("gaze");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("up");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("nearPlane");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("neardistance");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("imageresolution");
    stream << child->GetText() << std::endl;
    

    stream >> camera.position.x >> camera.position.y >> camera.position.z;
    stream >> camera.gaze.x >> camera.gaze.y >> camera.gaze.z;
    stream >> camera.up.x >> camera.up.y >> camera.up.z;
    stream >> camera.near_plane.x >> camera.near_plane.y >>
        camera.near_plane.z >> camera.near_plane.w;
    stream >> camera.near_distance;
    stream >> camera.image_width >> camera.image_height;
    

    cameras.push_back(camera);
    element = element->NextSiblingElement("camera");
  }
 
  // Get Lights
  element = root->FirstChildElement("lights");
  auto child = element->FirstChildElement("ambientlight");
  stream << child->GetText() << std::endl;
  stream >> ambient_light.x >> ambient_light.y >> ambient_light.z;
  element = element->FirstChildElement("pointlight");
  PointLight point_light;
  while (element) {
    child = element->FirstChildElement("position");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("intensity");
    stream << child->GetText() << std::endl;

    stream >> point_light.position.x >> point_light.position.y >>
        point_light.position.z;
    stream >> point_light.intensity.x >> point_light.intensity.y >>
        point_light.intensity.z;

    point_lights.push_back(point_light);
    element = element->NextSiblingElement("pointlight");
  }

  // Get Triangular Lights
 
  element = root->FirstChildElement("lights");
  element = element->FirstChildElement("triangularlight");
  TriangularLight triangularLight;
  PointLight pointLight2[3];
  PointLight pointLight3;
  while (element) {
    child = element->FirstChildElement("vertex1");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("vertex2");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("vertex3");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("intensity");
    stream << child->GetText() << std::endl;
    
    stream >> pointLight2[0].position.x >> pointLight2[0].position.y >>
        pointLight2[0].position.z;
    stream >> pointLight2[1].position.x >> pointLight2[1].position.y >>
        pointLight2[1].position.z;
    stream >> pointLight2[2].position.x >> pointLight2[2].position.y >>
    pointLight2[2].position.z;
    stream >> pointLight3.intensity.x >> pointLight3.intensity.y >>
        pointLight3.intensity.z;  
    

      std::array<float, 3> vector1 = {pointLight2[0].position.x - pointLight2[1].position.x, pointLight2[0].position.y- pointLight2[1].position.y, pointLight2[0].position.z - pointLight2[1].position.z};
      std::array<float, 3> vector2 = {pointLight2[0].position.x - pointLight2[2].position.x, pointLight2[0].position.y- pointLight2[2].position.y, pointLight2[0].position.z - pointLight2[2].position.z};
    
      // Çapraz çarpımı hesaplayın
      std::array<float, 3> cross_product = crossProduct(vector1, vector2);


      pointLight3.position.x = cross_product[1];
      pointLight3.position.y = cross_product[2];
      pointLight3.position.z = cross_product[3];
      std::cout<<"Triangular Lights Normal\n";
      std::cout<<"x:"<<cross_product[1]<<" y:" << cross_product[2] <<" z:"<<cross_product[3]<<"\n";
      

      /*pointLight2[1].intensity.x = pointLight2[0].intensity.x;
      pointLight2[1].intensity.y = pointLight2[0].intensity.y;
      pointLight2[1].intensity.z = pointLight2[0].intensity.z;

      pointLight2[2].intensity.x = pointLight2[0].intensity.x;
      pointLight2[2].intensity.y = pointLight2[0].intensity.y;
      pointLight2[2].intensity.z = pointLight2[0].intensity.z;*/

    //traingularLights.push_back(triangularLight);
    //point_lights.push_back(pointLight2[0]);
    //point_lights.push_back(pointLight2[1]);
    point_lights.push_back(pointLight3);
    element = element->NextSiblingElement("traingularlight");
  }
 
  // Get Materials
  element = root->FirstChildElement("materials");
  element = element->FirstChildElement("material");
  Material material;
  while (element) {
    child = element->FirstChildElement("ambient");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("diffuse");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("specular");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("mirrorreflactance");
    stream << child->GetText() << std::endl;
    child = element->FirstChildElement("phongexponent");
    stream << child->GetText() << std::endl;
    
    

    stream >> material.ambient.x >> material.ambient.y >> material.ambient.z;
    stream >> material.diffuse.x >> material.diffuse.y >> material.diffuse.z;
    stream >> material.specular.x >> material.specular.y >> material.specular.z;
    stream >> material.mirror.x >> material.mirror.y >> material.mirror.z;
    stream >> material.phong_exponent;
    
    materials.push_back(material);
    element = element->NextSiblingElement("material");
  }
  
  // Get VertexData
  element = root->FirstChildElement("vertexdata");
  stream << element->GetText() << std::endl;
  //std::cout<<element->GetText()<<"\n";
  
  Vec3f vertex;
  int i=0;
  
  while (!(stream >> vertex.x).eof()) {
    stream >> vertex.y >> vertex.z;
   
    vertex_data.push_back(vertex);
    i++;
  }
  stream.clear();
  
  // Get Meshes
  element = root->FirstChildElement("objects");
  element = element->FirstChildElement("mesh");
  Mesh mesh;
  while (element) {
    child = element->FirstChildElement("materialid");
    stream << child->GetText() << std::endl;
    stream >> mesh.material_id;
    mesh.material_id--;
    
    child = element->FirstChildElement("faces");
    stream << child->GetText() << std::endl;
    Face face;
    int v0_id, v1_id, v2_id;
    
    while (!(stream >> v0_id).eof()) {
      stream >> v1_id >> v2_id;
      
      
      face.v0 = vertex_data[v0_id - 1];
      face.v1 = vertex_data[v1_id - 1];
      face.v2 = vertex_data[v2_id - 1];
      
      face.material_id = mesh.material_id;
      face.CalculateNormal();
      mesh.faces.push_back(std::move(face));
      
    }
    stream.clear();
   
    meshes.push_back(std::move(mesh));
    mesh.faces.clear();
    element = element->NextSiblingElement("mesh");
  }
  stream.clear();
  
 
}



