#include <ros/ros.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <algorithm>
#define position_offset 45

using namespace cv;
using namespace std;

int iLowH = 22;int iHighH = 46;int iLowS = 38;int iHighS = 192;int iLowV = 131;int iHighV = 255;
int x = 108;int y = 23;int width = 392;int height = 386;
Mat thresh, frame, gray, blr, cannyed, hsv, hand; //image variables declaration
char sen[74]; //to store the output binary string
vector<Point2f> crdlib(34); //vector to store the latched coordinates of the white squares
bool flag=false;
bool send_flag=false;

bool check_x(Point2f a,Point2f b)
{
if(a.x>b.x)
	return true;
else
	return false;
}

bool check_y(Point2f a,Point2f b)
{
if(a.y>b.y)
	return true;
else
	return false;
}

char checkpoint(Point2f crd)
	{
	int pix=0;
	crd.x=crd.x-20;crd.y=crd.y-20;
	for(int i=0;i<40;i++)
		for(int j=0;j<40;j++)
			if(thresh.at<uchar>(crd.y+j,crd.x+i) == 255)
				pix++;
	if(pix>20)
	return '1';
	else
	return '0';
	}

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    if(!cv_bridge::toCvShare(msg, "bgr8")->image.empty())
    {
	cv_bridge::toCvShare(msg, "bgr8")->image.copyTo(frame);

	//cropping
	Rect roi;
	roi.x=x;roi.y=y;roi.width=width;roi.height=height;
	frame=frame(roi);

	//piece detection
	cvtColor(frame, hsv, CV_BGR2HSV);
	inRange(hsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresh);
	  //morphological opening (remove small objects from the foreground)
	  erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	  dilate( thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	  //morphological closing (fill small holes in the foreground)
	  dilate( thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	  erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	//hand detection
	int count=0; //counter for hand detection
	inRange(hsv, Scalar(57, 127, 17), Scalar(179, 255, 255), hand);
  	//morphological opening (remove small objects from the foreground)
		erode(hand, hand, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate( hand, hand, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		//morphological closing (fill small holes in the foreground)
		dilate( hand, hand, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		erode(hand, hand, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		for(int i=0;i<hand.cols;i++) //count the number of white pixels in the thresh image TODO:countNonZero(hand)
			for(int j=0;j<hand.rows;j++)
				if((int)hand.at<uchar>(j,i) == 255)
					{count++;}

	//contour detection and central point generaton
        cvtColor(frame, gray, CV_BGR2GRAY);
        GaussianBlur(gray, blr, Size(7, 7), 0, 0);
        Canny(blr, cannyed, 50, 200, 3);

        vector< vector<Point> > contours; //vector holding contours
              findContours(cannyed, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
        vector<Point> approx;
              vector<Moments> mu(contours.size()); //vector holding moments for the contours
              for (int i = 0; i < contours.size(); i++) {
                  mu[i] = moments(contours[i], false);
              }

              vector<Point2f> mc(contours.size()); //vector holding the centres of all the moments
              for (int i = 0; i < contours.size(); i++) {
                  mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
              }

              Mat dst;

              frame.copyTo(dst);

              vector<Rect> rects;vector<Point2f> centres(34); //vector holding centres of the white squares
							int index=0;
              for (int i = 0; i < contours.size(); i+=2)
              {
              approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
              double a = contourArea(contours[i]);
              if ((approx.size() == 4 || approx.size() == 5) && a>1000 && a<5000)
              {
                      drawContours(dst, contours, i, Scalar(255, 0, 0));
                      Rect r = boundingRect(contours[i]);
                      centres[index]=mc[i];
                      rects.push_back(r);index++;
                      //circle( dst, mc[i], 3, Scalar( 0, 0, 255 ), -1, 8 );
              }
              }

  if(index==32) //update white square coordinate latch set
	{
		sort(centres.begin(),centres.end(),check_y);
		for(int k=0,p=4;p<index+2;k+=4,p+=4)
			{sort(centres.begin()+k,centres.begin()+p,check_x);}

		for (int j=0; j<index; j++)
			{crdlib[j]=centres[j];}
		/*for (int j=0; j<index; j++) {cout<<crdlib[j]<<endl;}
			cout<<index<<endl;*/
		ROS_INFO("Coordinate set UPDATED");
		flag=true;
	}

	if(count==0 && flag==true)
	{
		int j=0;Point2f temp; //variable to hold the temporary black square centre
		bool chk_cng=false;
		for(int i=0;i<32;i++)
		{
			if((i+4)%4==0){if(chk_cng==false){chk_cng=true;}else{chk_cng=false;}if(i!=0){sen[j++]=',';}}
			sen[j++]=checkpoint(crdlib[i]);
			if(chk_cng==true)
				{temp.x=crdlib[i].x-position_offset;temp.y=crdlib[i].y;}
			else
				{temp.x=crdlib[i].x+position_offset;temp.y=crdlib[i].y;}
			sen[j++]=checkpoint(temp);
			circle( dst, crdlib[i], 3, Scalar( 0, 0, 255 ), -1, 8 );
			circle( dst, temp, 3, Scalar( 0, 0, 255 ), -1, 8 );
		}
		sen[j]='\0';
	  //cout<<sen<<endl;
    send_flag=true;
	}

  imshow("thresh", thresh);
	imshow("detected squares", dst);
	imshow("canny", cannyed);
  imshow("hand detection", hand);
	cv::waitKey(1);
    }
    else
    {
			ROS_INFO("ERROR: image is empty");
    }
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "frame_handler");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("bot_data", 1000);

  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera_frame", 1, imageCallback);


    namedWindow("Control", CV_WINDOW_NORMAL);

    //dynamic color detection
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    //dynamic crop
    cvCreateTrackbar("x", "Control", &x, 640);
    cvCreateTrackbar("y", "Control", &y, 480);
    cvCreateTrackbar("width", "Control", &width, 640);
    cvCreateTrackbar("height", "Control", &height, 480);

    ros::Rate loop_rate(60);
    while(ros::ok())
   	{
    if(send_flag==true)
    {
    	std_msgs::String bin_mat;
      bin_mat.data=sen;
      pub.publish(bin_mat);
    	loop_rate.sleep();
      send_flag=false;
    }
    ros::spinOnce();
   	}
	return 0;
}
