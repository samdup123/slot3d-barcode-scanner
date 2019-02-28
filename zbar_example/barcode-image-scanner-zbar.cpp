#include <opencv2/opencv.hpp>
#include "barcode-image-scanner-zbar.hpp"
#include <zbar.h>

// Find and decode barcodes and QR codes
void find_and_decode_symbologies(cv::Mat &im, std::vector<decodedObject>&decodedObjects)
{
  // Create zbar scanner
  zbar::ImageScanner scanner;

  // Configure scanner to look for no specific type of barcode, rather to look for all types
  // ZBAR code
  scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
  
  // Convert image to grayscale
  // OPNENCV code
  cv::Mat imGray;
  cv::cvtColor(im, imGray, cv::COLOR_BGR2GRAY);

  // Wrap image data in a zbar image
  // ZBAR code
  zbar::Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

  // Scan the image for barcodes and QRCodes
  // ZBAR code
  int n = scanner.scan(image);

  // add results to vector
  for(zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    decodedObject obj;
    
    obj.type = symbol->get_type_name();
    obj.data = symbol->get_data();
    
    // Obtain location
    for(int i = 0; i< symbol->get_location_size(); i++)
    {
      obj.location.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
    }
    
    decodedObjects.push_back(obj);
  }
}

void put_outlines_around_barcodes(cv::Mat &im, std::vector<decodedObject>&decodedObjects, uint8_t r, uint8_t g, uint8_t b, uint8_t lineWidth)
{
  // Loop over all decoded objects
  for(int i = 0; i < decodedObjects.size(); i++)
  {
    std::vector<cv::Point> points = decodedObjects[i].location;
    std::vector<cv::Point> hull;
    
    // If the points do not form a quad, find convex hull
    if(points.size() > 4)
      cv::convexHull(points, hull);
    else
      hull = points;
    
    // Number of points in the convex hull
    int n = hull.size();
    
    // draw the lines around the barcodes
    for(int j = 0; j < n; j++)
    {
      cv::line(im, hull[j], hull[ (j+1) % n], cv::Scalar(r,g,b), lineWidth);
    }
  }
}

