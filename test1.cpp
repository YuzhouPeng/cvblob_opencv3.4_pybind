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
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <omp.h>
#include <time.h>
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


// C api version
std::vector<unsigned int> blobdet(cv::Mat img1,cv::Mat img_gray,unsigned int rows,unsigned int cols)
{


  std::vector<unsigned int> results;
  // for(int i = 0;i<10;i++){
  //   results.push_back(1);
  // }

  return results;
}


struct Result {
      unsigned int minx;
      unsigned int miny;
      unsigned int width;
      unsigned int height;
      unsigned int centroidx;
      unsigned int centroidy;
      unsigned int longedge;
      unsigned int area;
      unsigned int avggrayvalue;
      unsigned int uiNameDict;
};



std::vector<Result> blobdetNew(cv::Mat img1, cv::Mat img_gray, unsigned int rows, unsigned int cols)
{
  // cv::Mat img1 = cv::imread("/home/sycv/workplace/pengyuzhou/el_webservice/algorithm/after_proc_algo/result4.jpg");
  // cv::Mat img_gray;
  // cv::cvtColor(img1, img_gray, CV_BGR2GRAY);


	// cv::Mat img1 = cv::Mat(rows, cols, CV_8UC3, ptr1);
  // cv::imwrite("/home/sycv/workplace/pengyuzhou/cvblob/testresult.jpg",img1);
  IplImage* img;
  unsigned int imgcols = img1.cols;
  unsigned int imgrows = img1.rows;
  img = cvCreateImage(cvSize(img1.cols,img1.rows),8,3);
  IplImage ipltemp=cvIplImage(img1);
  cvCopy(&ipltemp,img);

  // img = cvCreateImage(cvSize(img1.cols,img1.rows),8,3);
  // IplImage ipltemp=cvIplImage(img1);
  // cvCopy(&ipltemp,img);

  // IplImage *img=cvCloneImage(&(IplImage)img1);
  // IplImage img = img1.operator IplImage()
  // IplImage *img = cv::imread("test.png",1);
  cvSetImageROI(img, cvRect(0, 0, imgcols, imgrows));

  IplImage *grey = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
  cvCvtColor(&img, grey, CV_BGR2GRAY);
  cvThreshold(grey, grey, 100, 255, CV_THRESH_BINARY);
  
  // bitwise_not(grayMaskSmallThresh, grayMaskSmallThreshInv);

  IplImage *labelImg = cvCreateImage(cvGetSize(grey),IPL_DEPTH_LABEL,1);

  CvBlobs blobs;
  unsigned int result = cvLabel(grey, labelImg, blobs);

  IplImage *imgOut = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3); cvZero(imgOut);
  //std::vector<Det> results =  
  cvRenderBlobs(labelImg, blobs, img, imgOut);
	// for (int i = 0; i < results.size(); i++) {
	// 	std::cout << results[i].area << std::endl;
	// }
  //unsigned int i = 0;

  Result results = {0};
  std::vector<Result> Ret;

  //cvRenderBlob(labelImg, (*it).second, img, imgOut);
  CvBlob *blob = NULL;
  double angle;

  double x1,y1,x2,y2;
  double lengthLine;

  unsigned int minx;
  unsigned int miny;

  unsigned int centroidx;
  unsigned int centroidy;
  unsigned int area;
  unsigned int width;
  unsigned int height;
  unsigned int longedge;
  unsigned int defectarea;
  double ratio1;
  double avggrayvalue;

  // Render contours:
// #pragma omp parallel for num_threads(4)
  for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
  {
    results = {0};

    blob = (*it).second;
    angle = cvAngle(blob);

    lengthLine = MAX(blob->maxx-blob->minx, blob->maxy-blob->miny)/2.;

    x1=blob->centroid.x-lengthLine*cos(angle);
    y1=blob->centroid.y-lengthLine*sin(angle);
    x2=blob->centroid.x+lengthLine*cos(angle);
    y2=blob->centroid.y+lengthLine*sin(angle);
    minx = int(blob->minx);
    miny = int(blob->miny);

    centroidx = int(blob->centroid.x);
    centroidy = int(blob->centroid.y);
    area = int(blob->area);
    width = int(blob->maxx - blob->minx);
    height = int(blob->maxy - blob->miny);
    longedge = fabs(sqrt(int((x1)-(x2))*int((x1)-(x2))+int((y1)-(y2))*int((y1)-(y2))));
    defectarea = width*height;
    ratio1 = double(width)/double(height);
    avggrayvalue = 0;

    if (width>0&&height>0){
      for (int i = minx;i <minx+width;i++){
        for (int j = miny; j<miny+height;j++){
          avggrayvalue+=int(img_gray.at<unsigned char>(i,j));
        }
      }
    }


    avggrayvalue = (double(avggrayvalue)/(double(width)*double(height)));

    if (width>0 && height>0 && ratio1<1.6 && ratio1>0.4 && longedge<width*1.41&&longedge<height*1.41 and area>300 && area<width*height && ((centroidx>0 &&centroidx<double(imgcols)/6.0)||(centroidx>double(imgcols)/3.0 &&centroidx<double(imgcols)*2.0/3.0)) && (centroidy>double(imgrows)/3.0 and centroidy<double(imgrows)*2.0/3.0)){
      results.minx = (int(blob->minx));
      results.miny = (int(blob->miny));
      results.width = (width);
      results.height = (height);
      results.centroidx = (centroidx);
      results.centroidy = (centroidy);
      results.longedge = (longedge);
      results.area = (area);
      results.avggrayvalue = (avggrayvalue);
      results.uiNameDict = 0;
    }
    else if (width>0 && height>0 &&ratio1<1.6 && ratio1>0.4 && longedge<width*1.41&&longedge<height*1.41 and area>300 && area<width*height && ((centroidx>centroidx<double(imgcols)/6.0 &&centroidx<double(imgcols)/3.0)||(centroidx>double(imgcols)*2.0/3.0 &&centroidx<double(imgcols))) && ((centroidy>0 and centroidy<double(imgrows)/3.0) or (centroidy>double(imgrows)*2.0/3.0 && centroidy<double(imgrows)))){
      results.minx = (int(blob->minx));
      results.miny = (int(blob->miny));
      results.width = (width);
      results.height = (height);
      results.centroidx = (centroidx);
      results.centroidy = (centroidy);
      results.longedge = (longedge);
      results.area = (area);
      results.avggrayvalue = (avggrayvalue);
      results.uiNameDict = 1;
    }

    Ret.push_back(results);

    // results.push_back(width);

    
    CvScalar meanColor = cvBlobMeanColor((*it).second, labelImg, img);
    // cout << "Mean color: r=" << (unsigned int)meanColor.val[0] << ", g=" << (unsigned int)meanColor.val[1] << ", b=" << (unsigned int)meanColor.val[2] << endl;

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

  // for (int i = 0; i < results.size(); i++) {
	// 	std::cout << results[i] << std::endl;
	// }

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

  return Ret;
}



std::vector<unsigned int> outvalue(pybind11::array_t<uint8_t> img2,unsigned int rows,unsigned int cols){
  
  
  pybind11::buffer_info buf1 = img2.request();
	// unsigned char *ptr1 = (unsigned char *)buf1.ptr;
  cv::Mat img1(buf1.shape[0], buf1.shape[1], CV_8UC3, (unsigned char*)buf1.ptr);
  cv::Mat img_gray(buf1.shape[0], buf1.shape[1], CV_8UC1, (unsigned char*)buf1.ptr);
  // time_t start,end,time;

  std::vector<unsigned int> res;

  // start = clock();
  clock_t start = clock();
  res = blobdet(img1,img_gray,rows,cols);
  // end = clock();
  clock_t end = clock();
  // time = end-start;
  cout<<"endtime - begintime is"<<endl;
  cout<<(double)(((double)(end-start))/CLOCKS_PER_SEC)<<endl;

  // std::vector<Result> resNew;

  // clock_t start0 = clock();
  // resNew = blobdetNew(img1,img_gray,rows,cols);
  // // end = clock();
  // clock_t end0 = clock();
  // // time = end-start;
  // cout<<"new endtime - begintime is"<<endl;
  // cout<<(double)(((double)(end0-start0))/CLOCKS_PER_SEC)<<endl;



  return res;
}



PYBIND11_MODULE(test1, m)
{
    // optional module docstring
    m.doc() = "pybind11 example plugin";
    // expose add function, and add keyword arguments and default arguments
    m.def("outvalue", &outvalue, "blob detect shapes");
    
    // return m;
    // exporting variables
    // m.attr("the_answer") = 42;
    // py::object world = py::cast("World");
    // m.attr("what") = world;
}
