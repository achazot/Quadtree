#include <iostream>
#include <list>
#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "quadtree.hpp"

#define PSIZE 2048

int main ( int agrc, char *argv[] )
{
	cv::Mat src = cv::imread("map.png", CV_LOAD_IMAGE_GRAYSCALE);
	
	int **a = new int*[PSIZE];
	for (int i = 0; i < PSIZE; i++)
		a[i] = new int[PSIZE];
	
	
	std::clock_t start;

	
	start = std::clock();
	for (int x = 0; x < PSIZE; x++)
	for (int y = 0; y < PSIZE; y++)
	{
		a[x][y] = src.at<unsigned char>(x, y);
	}
	std::cout << "deep copy:             " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	
	start = std::clock();
	Quadtree q(PSIZE,a);
	std::cout << "qtree construction:    " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	
	start = std::clock();
	std::vector<Node*> ls = q.toList();
	std::cout << "list construction:     " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms";
	std::cout << " size = " << ls.size() << " (instead of " << PSIZE * PSIZE << ")" << std::endl;
	
	
	cv::Mat rec(PSIZE, PSIZE, CV_8UC1);
	for (int i=0; i<PSIZE; i++)
	for (int j=0; j<PSIZE; j++)
		rec.at<unsigned char>(i,j) = 0;
	
	
	start = std::clock();
	for (Node* n : ls)
	{
		rec.at<unsigned char>(n->x()+(n->size()-1), n->y()+(n->size()-1)) = n->value();
	}
	std::cout << "image reconstruction:  " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;;
	
	
	cv::imshow("src", src);
	cv::imshow("rec", rec);

	cv::waitKey(0);
	
	return 0;
}



