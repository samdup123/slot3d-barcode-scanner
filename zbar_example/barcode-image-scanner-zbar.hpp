#ifndef BARCODE_IMAGE_SCANNER_ZBAR_HPP
#define BARCODE_IMAGE_SCANNER_ZBAR_HPP

#include <string>
#include <vector>
#include <opencv/cv.h>

typedef struct
{
  std::string type;
  std::string data;
  std::vector <cv::Point> location;
} decodedObject;

void decode(cv::Mat &im, std::vector<decodedObject>&decodedObjects);

#endif