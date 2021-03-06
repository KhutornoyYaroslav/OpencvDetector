#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;


int main()
{
	cv::Mat src = cv::imread("image6.jpg", 1); // Инициализация изображения
	cv::Mat gray;
	cvtColor(src, gray, cv::COLOR_BGR2GRAY); // Перевод в чёрно-белое
	cv::CascadeClassifier cascadeSymbol; // Объявление каскада
	bool cascadeSymbolLoad = cascadeSymbol.load("haarcascade_russian_plate_number.xml"); // Загрузка каскада

	if (!cascadeSymbolLoad)
	{
		std::cerr << "Cascade not load. Check your directory \"haarcascade_russian_plate_number_symbol.xml\"" << std::endl;
		return false;
	}

	std::vector<cv::Rect> symbols;
	cascadeSymbol.detectMultiScale(gray, symbols); // Поиск с помощью каскада

	for (auto& p : symbols)
	{
		cv::Point symbolBegin = cv::Point(p.x, p.y);
		cv::Point symbolEnd = cv::Point(p.x + p.width, p.y + p.height);

		std::cout << "X: " << p.x << " Y: " << p.y << " Width: " << p.width << " Height: " << p.height << std::endl;


		rectangle(src, symbolBegin, symbolEnd, cv::Scalar(0, 255, 0), 2);
	}

	cv::imshow("Test", src);

	cv::waitKey(0);

	return 0;
}