float w=250,h=350;
const int kThreashold = 220;
const int kMaxVal = 255;
const Size kGaussianRedSize = Size(5, 5);


int main(){VideoCapture video;
     video.open("../resources/ood_red.mp4");
    Mat frame,grayImg,gray,binary,Gaussian,binary1,canny,result1,imgWarp;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Rect boundRect;
    RotatedRect box;
    vector<Point2f> boxPts(4);
    
    for (;;) {
    
        Rect point_array[20];
        video >> frame;
        if (frame.empty()) {
            break;
        }


    cvtColor(frame, grayImg, COLOR_BGR2GRAY); // ת��Ϊ�Ҷ�ͼ��
    GaussianBlur(grayImg, gray, Size(5, 5), 0, 0); // ��˹�˲�
    
    Canny(gray, canny,150,450); // ��Ե���
    threshold(canny, binary, kThreashold, kMaxVal, 0);
        GaussianBlur(binary, Gaussian, kGaussianRedSize, 0);
        cv::Mat template1 = imread("../resources/Hb6lWxmn.jpeg", cv::IMREAD_GRAYSCALE);
// ������������ģ��...
matchTemplate(gray,template1,result1,TM_CCOEFF_NORMED);
double minVal1, maxVal1;
Point minLoc1, maxLoc1;
Mat minMaxLoc(result1, &minVal1, &maxVal1, &minLoc1, &maxVal1);
//������ƥ�����õ�����꣬���ɵ�������ȡ���֡�4������λ�ã�Point2d������������޷��ó���
// Point2d src[4]={{minVal1,maxVal1},{minVal1,maxVal1},{minLoc1,maxVal1},{minLoc1,maxVal1}};
// Point2d dst[4]={{0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h}};
// Mat matrix=getPerspectiveTransform(src,dst);
// warpPerspective(frame,imgWarp,matrix,Point(w,h));
//imshow("Imgwarp",imgWarp);
auto start = std::chrono::high_resolution_clock::now();

        // ���������ͼ����

        



std::vector<std::vector<Point>> armorContours;
    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        if (area > 100) // ����ʵ���������ɸѡ����
        {
            armorContours.push_back(contours[i]);
        }
    }

    // ����ɸѡ�������
    Mat result = Mat::zeros(frame.size(), CV_8UC3);
    drawContours(result, armorContours, -1, Scalar(0, 255, 255), 2);

    // ��ʾ���
    imshow("Result", result);
