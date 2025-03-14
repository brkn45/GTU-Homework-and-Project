#include "ConvertPPM.h"
#include <stdexcept>

void convertPPM(const char* filename, unsigned char* data, int width,int height) {
  FILE* outputFile;

  if ((outputFile = fopen(filename, "w")) == NULL) {
    throw std::runtime_error(
        "Error: The ppm file dont open");
  }

  (void)fprintf(outputFile, "P3\n%d %d\n255\n", width, height);

  unsigned char color;
  for (size_t j = 0, idx = 0; j < height; ++j) {
    for (size_t i = 0; i < width; ++i) {
      for (size_t c = 0; c < 3; ++c, ++idx) {
        color = data[idx];

        if (i == width - 1 && c == 2) {
          (void)fprintf(outputFile, "%d", color);
        } else {
          (void)fprintf(outputFile, "%d ", color);
        }
      }
    }

    (void)fprintf(outputFile, "\n");
  }

  (void)fclose(outputFile);
}
