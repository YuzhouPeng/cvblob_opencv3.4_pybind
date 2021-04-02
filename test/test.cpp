// Copyright (C) 2007 by Cristóbal Carnero Liñán
// grendel.ccl@gmail.com
//
// This file is part of cvBlob.
//
// cvBlob is free software: you can redistribute it and/or modify
// it under the terms of the Lesser GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// cvBlob is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// Lesser GNU General Public License for more details.
//
// You should have received a copy of the Lesser GNU General Public License
// along with cvBlob.  If not, see <http://www.gnu.org/licenses/>.
//

#include <iostream>
//#include <iomanip>
#include <opencv2/imgcodecs.hpp>
// #include <opencv2/imgproc/imgproc.hpp>

using namespace std;

#if (defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || (defined(__APPLE__) & defined(__MACH__)))
#include <cv.h>
#include <highgui.h>
#else
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif
#include <cvblob.h>
// #include "../cvBlob/cvblob.h"
using namespace cvb;
struct Det {
unsigned int width;
unsigned int height;
unsigned int centeriodx;
unsigned int centeriody;
unsigned int longedge;
unsigned int area;
};

// int main(){
//   return 0;
// }

// C api version
extern "C" std::vector<Det> blobdet()
{
  cv::Mat img1 = cv::imread("/home/sycv/workplace/pengyuzhou/el_webservice/algorithm/after_proc_algo/result6.jpg");
  // cv::Mat img_gray;
  // cv::cvtColor(img1, img_gray, CV_BGR2GRAY);
  IplImage* img;
  img = cvCreateImage(cvSize(img1.cols,img1.rows),8,3);
  IplImage ipltemp=cvIplImage(img1);
  cvCopy(&ipltemp,img);

  // IplImage *img=cvCloneImage(&(IplImage)img1);
  // IplImage img = img1.operator IplImage()
  // IplImage *img = cv::imread("test.png",1);
  cvSetImageROI(img, cvRect(0, 0, 800, 500));

  IplImage *grey = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
  cvCvtColor(img, grey, CV_BGR2GRAY);
  cvThreshold(grey, grey, 100, 255, CV_THRESH_BINARY);
  
  // bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);

  IplImage *labelImg = cvCreateImage(cvGetSize(grey),IPL_DEPTH_LABEL,1);

  CvBlobs blobs;
  unsigned int result = cvLabel(grey, labelImg, blobs);

  IplImage *imgOut = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3); cvZero(imgOut);
  //std::vector<Det> results =  
  cvRenderBlobs(labelImg, blobs, img, imgOut,0x0010);
	// for (int i = 0; i < results.size(); i++) {
	// 	std::cout << results[i].area << std::endl;
	// }
  //unsigned int i = 0;

  std::vector<Det> results;


  // Render contours:
  for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
  {
    //cvRenderBlob(labelImg, (*it).second, img, imgOut);
    CvBlob *blob = (*it).second;
    double angle = cvAngle(blob);

    double x1,y1,x2,y2;
    double lengthLine = MAX(blob->maxx-blob->minx, blob->maxy-blob->miny)/2.;

    x1=blob->centroid.x-lengthLine*cos(angle);
    y1=blob->centroid.y-lengthLine*sin(angle);
    x2=blob->centroid.x+lengthLine*cos(angle);
    y2=blob->centroid.y+lengthLine*sin(angle);
    unsigned int centroidx = int(blob->centroid.x);
    unsigned int centroidy = int(blob->centroid.y);
    unsigned int area = int(blob->area);
    unsigned int width = int(1 + blob->maxx - blob->minx);
    unsigned int height = int(1 + blob->maxy - blob->miny);
    unsigned int longedge = fabs(sqrt(int((x1)-(x2))*int((x1)-(x2))+int((y1)-(y2))*int((y1)-(y2))));;

    struct Det temp = {width,height,centroidx,centroidy,longedge,area};
    results.push_back(temp);
    
    CvScalar meanColor = cvBlobMeanColor((*it).second, labelImg, img);
    cout << "Mean color: r=" << (unsigned int)meanColor.val[0] << ", g=" << (unsigned int)meanColor.val[1] << ", b=" << (unsigned int)meanColor.val[2] << endl;

    CvContourPolygon *polygon = cvConvertChainCodesToPolygon(&(*it).second->contour);

    CvContourPolygon *sPolygon = cvSimplifyPolygon(polygon, 10.);
    CvContourPolygon *cPolygon = cvPolygonContourConvexHull(sPolygon);
    
    // cout<< "polygons are: "<< *polygon<<endl;
    // cout<< "sploycons are" << *sPolygon<<endl;
    // cout<< "cpolygons are" << *cPolygon<<endl;

    cvRenderContourChainCode(&(*it).second->contour, imgOut);
    // cvRenderContourPolygon(sPolygon, imgOut, CV_RGB(0, 0, 255));
    // cvRenderContourPolygon(cPolygon, imgOut, CV_RGB(0, 255, 0));

    delete cPolygon;
    delete sPolygon;
    delete polygon;

    // Render internal contours:
    for (CvContoursChainCode::const_iterator jt=(*it).second->internalContours.begin(); jt!=(*it).second->internalContours.end(); ++jt)
      cvRenderContourChainCode((*jt), imgOut);

    //stringstream filename;
    //filename << "blob_" << setw(2) << setfill('0') << i++ << ".png";
    //cvSaveImageBlob(filename.str().c_str(), imgOut, (*it).second);
  }

  for (int i = 0; i < results.size(); i++) {
		std::cout << results[i].area << std::endl;
	}

  // cvNamedWindow("test", 1);
  // cvShowImage("test", imgOut);
  // //cvShowImage("grey", grey);
  // cvWaitKey(0);
  // cvDestroyWindow("test");

  cvReleaseImage(&imgOut);
  cvReleaseImage(&grey);
  cvReleaseImage(&labelImg);
  cvReleaseImage(&img);

  cvReleaseBlobs(blobs);

  return results;
}
