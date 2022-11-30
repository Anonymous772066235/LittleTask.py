#pragma once

#include "CMulti_SpaceIntersection.h"
#include "CSamePointTrackSGM.h"
#include "BasicFunction.h"

class CRPCBased3DReconstruction
{
public:
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//设置输入从参数
	void SetParams( std::vector<std::string> ImageListName, 
		float Mind, float Maxd, int Gridr, int Gridc,
		int ProjectErr_T, int m,std::string projpath);
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void run();

private:
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//提取同名点
	void runSamePointTrackSGM();
	//多片前方交会
	void runMulti_SpaceIntersection();
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//影像列表txt路径
	std::vector<std::string> p_ImageListName;
	//视差控制
	float p_Mind;
	float p_Maxd;
	//格网大小
	int p_Gridr;
	int p_Gridc;
	//反投影误差
	int p_ProjectErr_T;
	//去噪控制参数
	int p_m;
	std::string p_projpath;

	vector<vector<vector<float>>> kb;
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//同名点
	vector<vector<ImagePoint>> CorrespondigPoints;
};

