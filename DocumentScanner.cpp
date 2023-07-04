#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

float w = 420, h = 596;
Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThre, imgDia, imgErode, imgWarp, imgCrop;

vector<Point> biggest;
vector<Point> initialPoints, docPoints;

vector<Point> reOrder(vector<Point> points) {
	vector<Point> newPoints;
	vector<int> sumPoints,subPoints;
	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);

	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);

	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);

	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

	return newPoints;
	//points[0].x+ points[0].y + points[0].x +
}

void drawPoints(vector<Point> points, Scalar color) {

	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOriginal, points[i],10,color,FILLED);
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
	}
}

Mat preProcessing(Mat img) {

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDia, kernel);
	erode(imgCanny, imgErode, kernel);

	return imgDia;
}



vector<Point> getCotours(Mat imgDil) {
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	int maxArea = 0;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		vector<vector<Point>>conPoly(contours.size());
		vector<Rect>boundRect(contours.size());
		string objType;

		if (area > 1000) {

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;
			 
			if (area > maxArea && conPoly[i].size()==4) {
				biggest = { conPoly[i][0], conPoly[i][1],  conPoly[i][2],  conPoly[i][3] };
				maxArea = area;
			}
			//rectangle(imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);


			//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);


		}
	}
	return biggest;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h) {

	Point2f src[4] = { points[0], points[1],  points[2],  points[3] };
	Point2f drc[4] = { {0.0f,0.0f}, {w,0.0f},{0.0f,h },{w,h} };

	Mat matrix = getPerspectiveTransform(src, drc);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	return imgWarp;
}

void main() {

	VideoCapture video(0);

	string path = "gfdgfh.png";
	imgOriginal = imread(path);
	//resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
	//Preprpcessing
	imgThre = preProcessing(imgOriginal);
	//Get Contours - Biggest
	initialPoints=getCotours(imgThre);
	//drawPoints(initialPoints, Scalar(0, 0, 255));
	docPoints = reOrder(initialPoints);

	//drawPoints(docPoints, Scalar(0, 255, 0));

	//Warp
	int cropVal = 5;
	imgWarp = getWarp(imgOriginal, docPoints, w, h);


	Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
	imgCrop = imgWarp(roi);
	imshow("Frame", imgOriginal);
	//imshow("Dia", imgThre);
	//imshow("wrap", imgWarp);
	imshow("crop", imgCrop);


	waitKey(0);
}