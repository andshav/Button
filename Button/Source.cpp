#include<opencv2\opencv.hpp>
#include<fstream>
#include<iostream>
#include<vector>

using namespace cv;
using namespace std;


Mat src;
ofstream fout("tracing.txt");




vector <int> xcoord;
vector <int> ycoord;
vector <int> width;
vector <int> height;
vector <char*> name;


class Button
{
public:
	Button(Mat img, char* name, int width, int height, int x, int y);

	
	~Button();
	void addButton();

	void mouseHandler(int event, int x, int y, int flags, void*);

	
	
private:
	
	int x_;
	int y_;
	int w_;
	int h_;
	Mat img_;
	char* name_;
	
	

};


Button::Button(Mat img, char* name, int width, int height, int x, int y) : img_(img), name_(name), w_(width), h_(height), x_(x), y_(y)

{
	
}



Button::~Button()
{
}
 void Button::addButton()
{
		
	line(img_, CvPoint(x_ - w_ / 2, y_ + h_ / 4), CvPoint(x_ + w_ / 2, y_ + h_ / 4), CV_RGB(200, 200, 200), h_ / 2, CV_AA);
	line(img_, CvPoint(x_ - w_ / 2, y_ - h_ / 4), CvPoint(x_ + w_ / 2, y_ - h_ / 4), CV_RGB(200, 200, 200), h_ / 2, CV_AA);
	line(img_, CvPoint(x_ + w_ / 2, y_ + h_ / 4), CvPoint(x_ + w_ / 2, y_ - h_ / 4), CV_RGB(200, 200, 200), h_ / 2, CV_AA);
	line(img_, CvPoint(x_ - w_ / 2, y_ + h_ / 4), CvPoint(x_ - w_ / 2, y_ - h_ / 4), CV_RGB(200, 200, 200), h_ / 2, CV_AA);
	
	putText(img_, name_, CvPoint(x_ - w_/2,y_), 16, 0.4, Scalar(0, 0, 0, 0), 1);
	
	
	xcoord.push_back(x_);
	ycoord.push_back(y_);
	width.push_back(w_);
	height.push_back(h_);
	name.push_back(name_);

	
	
			
			
		
	
}

void Button::mouseHandler(int event, int x, int y, int flags, void* param)
{
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
			
		break;

	case CV_EVENT_LBUTTONDOWN:
		for (int i = 0; i < xcoord.size(); i++)
		{
			if (x<xcoord[i] + width[i] / 2 && x>xcoord[i] - width[i] / 2 && y<ycoord[i] + height[i] / 2 && y>ycoord[i] - height[i] / 2)
			{
				fout << "Clicked button << "<<name[i]<<" >>" << endl;
				cout << "Clicked button << " << name[i] << " >>" << endl;
				if (name[i] == "brightness+") { src *= 1.1; }
				if (name[i] == "brightness-") { src /= 1.1; }
				if (name[i] == "blue") 
				{
					for (int i = 0; i < src.rows; i++)
					{
						for (int j = 0; j < src.cols; j++) 
						{
							src.at<Vec3b>(i, j)[0] += 255 / 10;							
						}
					}
				}
				if (name[i] == "green")
				{
					for (int i = 0; i < src.rows; i++)
					{
						for (int j = 0; j < src.cols; j++)
						{
							src.at<Vec3b>(i, j)[1] += 255 / 10;
						}
					}
				}
				if (name[i] == "red")
				{
					for (int i = 0; i < src.rows; i++)
					{
						for (int j = 0; j < src.cols; j++)
						{
							src.at<Vec3b>(i, j)[2] += 255 / 10;
						}
					}
				}
				if (name[i] == "save") {

					imwrite("save_img.png", src);
				}
				if (name[i] == "exit") exit(0);
				
			}
		}
		break;

	case CV_EVENT_LBUTTONUP:
			
		break;
	}
}

Button* g_ptr;
void onMouse(int event, int x, int y, int flags, void* param)
{
	g_ptr->mouseHandler(event, x, y, flags, param);
}


int main()
{
	fout.clear();
	ifstream fin("image_path.txt");
	char image[260];
	fin.getline(image, 260);
	fin.close();

	
	Mat img = imread(image);
	src = imread(image);
	cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
	
	
	Button brightness(img, "brightness+", 70, 20, 95, 45);
	Button brightness_(img, "brightness-", 70, 20, 200, 45);
	Button b(img, "blue", 70, 20,305, 45);
	Button g(img, "green", 70, 20, 410, 45);
	Button r(img, "red", 70, 20, 515, 45);
	Button save(img, "save", 70, 20, 200, img.rows - 45);
	Button exit(img, "exit", 70, 20, img.cols-95, img.rows - 45);

	exit.addButton();
	save.addButton();
	b.addButton();
	g.addButton();
	r.addButton();
	brightness.addButton();
	brightness_.addButton();
	cvSetMouseCallback("image", onMouse, &src);
	char c = cvWaitKey(33);
	while (true) {
		// получаем кадр

		// показываем
		imshow("image", img);
		
		char c = cvWaitKey(33);
		if (c == 27) { // нажата ESC
			break;
		}

	}

	return 0;
}