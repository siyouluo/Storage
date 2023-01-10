#include "cv_puttextzh.h"

int main() {
    cv::Mat image = cv::Mat(500, 500,CV_8UC3, cv::Scalar(144, 238, 144));
    cv::putTextZH(
       image,
       "你好！OpenCV",
       cv::Point(image.cols/3, image.rows / 2),
       CV_RGB(255, 255, 0),
       30
    );
    cv::imshow("中文图窗", image);
    cv::waitKey(0);

    return 0;
}
