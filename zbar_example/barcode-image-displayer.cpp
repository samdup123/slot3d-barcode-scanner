#include "barcode-image-scanner-zbar.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"

// Display barcode and QR code location  
void display(cv::Mat &im, std::vector<decodedObject>&decodedObjects)
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
      cv::line(im, hull[j], hull[ (j+1) % n], cv::Scalar(255,0,0), 3);
    }
    
  }
  
  // Display results 
  imshow("Results", im);
  cv::waitKey(0);
  
}

int main(int argc, char* argv[])
{
  
  // Read image
  cv::Mat im = cv::imread("b/2.jpg");
  
  // Variable for decoded objects 
  std::vector<decodedObject> decodedObjects;
  
  // Find and decode barcodes and QR codes
  decode(im, decodedObjects);

  // Display location 
  display(im, decodedObjects);
  
  return EXIT_SUCCESS;
}
