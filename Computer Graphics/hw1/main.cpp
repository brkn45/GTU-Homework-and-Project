#include <iostream>
#include <thread>
#include "imageRenderer.h"
#include "xmlParser.h"
#include "ConvertPPM.h"
#include <string>

using namespace parser;




using namespace std::chrono;

int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cout << "please enter xml file" << std::endl;
    return 1;
  }
  auto startTime = high_resolution_clock::now();
  ImageRenderer imageRenderer(argv[1]);
  std::string xmlFile(argv[1]);
  int pointIndex = xmlFile.find_last_of('.');
  char outputFile[50];
  std::string filename;
  if (pointIndex != std::string::npos) {
      filename = xmlFile.substr(0, pointIndex);
      filename = filename + ".ppm";
      
  } 
  else {
      std::cout << "There is not point" << std::endl;
  }
  for (const Camera& camera : imageRenderer.Cameras()) {
    const int width = camera.image_width;
    const int height = camera.image_height;
    Vec3i* pixels = new Vec3i[width * height];
    int coreCount = std::thread::hardware_concurrency();
    imageRenderer.SetUpScene(camera);
    if (coreCount == 0 || height < coreCount) {
      imageRenderer.RenderImage(camera, pixels, 0, height, width);
    } 
    else {
      std::thread* threads = new std::thread[coreCount];
      int heightIncrease = height / coreCount;

      for (int i = 0; i < coreCount; i++) {
        int minHeight = i * heightIncrease;
        int maxHeight =(i == coreCount - 1) ? height : (i + 1) * heightIncrease;
        threads[i] = std::thread(&ImageRenderer::RenderImage, &imageRenderer,camera, pixels, minHeight, maxHeight, width);

      }
      for (int i = 0; i < coreCount; i++) threads[i].join();
      delete[] threads;
    }
    unsigned char* image = new unsigned char[width * height * 3];

    int idx = 0;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        const Vec3i pixel = pixels[i * height + j];
        image[idx++] = pixel.x;
        image[idx++] = pixel.y;
        image[idx++] = pixel.z;
      }
    }
    delete[] pixels;
    convertPPM(filename.c_str(), image, width, height);
    delete[] image;
  }

    auto finishTime = high_resolution_clock::now();
    
    // Başlangıç ve bitiş arasındaki süreyi hesapla
    auto duration = duration_cast<milliseconds>(finishTime - startTime);
    
    // Süreyi ekrana yazdır
    std::cout << "Program running time: " << duration.count() << " millisecond.\n";
  return 0;
}
