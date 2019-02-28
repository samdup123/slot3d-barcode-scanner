#ifndef BARCODE_IMAGE_SCANNER_ZBAR_HPP
#define BARCODE_IMAGE_SCANNER_ZBAR_HPP

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

typedef struct
{
  std::string type;
  std::string data;
  std::vector <cv::Point> location;
} decodedObject;

void find_and_decode_symbologies(cv::Mat &im, std::vector<decodedObject>&decodedObjects);

void put_outlines_around_barcodes(cv::Mat &im, std::vector<decodedObject>&decodedObjects, uint8_t r, uint8_t g, uint8_t b, uint8_t lineWidth);

#endif