#ifndef _TOPIC_LOGGER_H_
#define _TOPIC_LOGGER_H_

#include <iostream>
#include <ros/ros.h>
#include <sys/time.h>
#include <Eigen/Dense>
#include <fstream>
#include <ctime>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef std::string TopicTime;

class TopicLogger {

public:
  TopicLogger(std::string folder_dir);
  ~TopicLogger();
 
  void stereo_img_addline(const cv::Mat& leftImg, const cv::Mat& rightImg, const TopicTime& stereoImgTime);

private:
  std::string folder_dir;

  std::ofstream file_image, file_imu, file_pose;
  std::string file_image_name, file_imu_name, file_pose_name;
};

#endif
