#include "barcode-image-scanner-zbar.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char* argv[])
{
  
  // Read image
  cv::Mat im = cv::imread("zbar-test.jpg");
  
  // Variable for decoded objects 
  std::vector<decodedObject> decodedObjects;
  
  // Find and decode barcodes and QR codes
  find_and_decode_symbologies(im, decodedObjects);

  put_outlines_around_barcodes(im, decodedObjects, 255, 0, 0, 3);

  cv::imshow("Results", im);
  cv::waitKey(0);
  
  return EXIT_SUCCESS;
}
