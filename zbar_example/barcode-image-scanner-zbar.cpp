#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "barcode-image-scanner-zbar.hpp"
#include <zbar.h>

// Find and decode barcodes and QR codes
void decode(cv::Mat &im, std::vector<decodedObject>&decodedObjects)
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

