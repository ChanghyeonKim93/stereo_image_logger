#include <TopicLogger.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>

TopicLogger::TopicLogger(std::string folder_dir_){
	std::string folder_create_command, file_name, folder_dir_temp;
	this->folder_dir = folder_dir_;
  	folder_dir_temp = this->folder_dir;

// 1. imu folder
	//if(strcmp(*folder_dir_temp.end(),'/')!=0) folder_dir_temp+='/';

	folder_create_command = "mkdir " + folder_dir_temp;
	system(folder_create_command.c_str());
	folder_create_command = "mkdir " + folder_dir_temp + "/image";
	system(folder_create_command.c_str());
	folder_create_command = "mkdir " + folder_dir_temp + "/image/left";
	system(folder_create_command.c_str());
	folder_create_command = "mkdir " + folder_dir_temp + "/image/right";
	system(folder_create_command.c_str());

	file_name = folder_dir_temp+"association.txt";
	std::cout<<file_name.c_str()<<std::endl;
	file_image.open(file_name.c_str(),std::ios::trunc);
	file_image << "# time filename";

};

TopicLogger::~TopicLogger(){
	file_image.close();
	ROS_INFO_STREAM("  Logger is terminated.\n");
};

  void TopicLogger::stereo_img_addline(const cv::Mat& leftImg, const cv::Mat& rightImg, const TopicTime& stereoImgTime){
	bool static png_param_on=false;
	std::vector<int> static png_parameters;
	if(png_param_on==false){
			png_parameters.push_back( CV_IMWRITE_PNG_COMPRESSION );	// We save with no compression for faster processing
			png_parameters.push_back(0);
			png_param_on = true;
	}
	std::string imgLeftFileName = folder_dir+"image/left/"+stereoImgTime+".png";
	std::string imgRightFileName = folder_dir+"image/right/"+stereoImgTime+".png";
	cv::imwrite(imgLeftFileName, leftImg,png_parameters);
	cv::imwrite(imgRightFileName,rightImg,png_parameters);
	file_image << stereoImgTime<<"\t"<< stereoImgTime<<".png"<<"\n";	// association save
};
