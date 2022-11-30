#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "BasicFunction.h"
#include "GetEpipolarImage.h"
#include <SemiGlobalMatching.h>

using namespace std;

class CSamePointTrackSGM
{
private:
	std::vector<std::string>  m_imglist;
	string m_outpath;
	float m_mindisp, m_maxdisp;
	string m_projpath;
	string m_logfilename;

	vector<vector<ImagePoint>> m_samepoints;

	int m_gridr, m_gridc;//����׷��ͬ����ʱ�������

private:
	//��ȡRPC
	RPCcoeffcient readrpc(char* filename, cv::Mat rpcdata);
	bool isPointInRect(cv::Point p, cv::Rect rect);
	//���ɸ���
	void CMeshGrid(const cv::Range xr, const cv::Range yr, cv::Mat& outX, cv::Mat& outY);
	//�ֿ���ܼ�ƥ��
	cv::Mat GetDispSGM(cv::Mat le, cv::Mat re, float mindisp, float maxdisp);
	cv::Mat GetDispSGM(cv::Mat le, cv::Mat re, float mindisp, float maxdisp, int patchnum,int i_);
	//�����Ӳ�ͼ׷��ͬ����,���и����������ڵ��ϡ
	vector<vector<ImagePoint>> SamePointTrack(vector<cv::Mat> dispxs, vector<cv::Mat> dispys, int gridr, int gridc);
	//�Ӳ�ͼתλ��
	void calOriginalCoord(cv::Mat disp, vector<vector<float>>kb, cv::Mat& x, cv::Mat& y, double offx, double offy);
	//ͬ�������Ӱ��-->ԭʼӰ��
	vector<vector<ImagePoint>> HXImage2Image(cv::Mat disp, vector<vector<float>>kb, double offx, double offy, int gridr, int gridc, int id);
	//���ݷ�Χɸѡͬ����
	vector<vector<ImagePoint>> SamePointChoose(vector<vector<ImagePoint>> ps, cv::Rect roi);

public:
	CSamePointTrackSGM();
	~CSamePointTrackSGM();
	CSamePointTrackSGM(std::string projpath,std::vector<std::string> imglistpath, string imgpath, string rpcpath,
		float mind, float maxd,
		 int gridr = 10, int gridc = 10)
	{
		create( projpath,imglistpath,  mind, maxd,  gridr, gridc);
	}
	//����
	void create(std::string projpath,std::vector<std::string> imglistpath,
		float mind, float maxd,
		 int gridr = 10, int gridc = 10);
	//Ӱ��list·��
	void SetImageListPath(std::vector<std::string> imglistpath)
	{
		m_imglist= imglistpath;
	
	}


	//��С�Ӳ�
	void SetMinDisp(float mind)
	{
		m_mindisp = mind;
	}
	float GetMinDisp()
	{
		return m_mindisp;
	}
	//����Ӳ�
	void SetMaxDisp(float maxd)
	{
		m_maxdisp = maxd;
	}
	float GetMaxDisp()
	{
		return m_maxdisp;
	}
	//����·��
	void SetProjectPath(string projpath)
	{
		m_projpath = projpath;
	}
	string GetProjectPath()
	{
		return m_projpath;
	}
	//�������R
	void SetGridR(int gridr)
	{
		m_gridr = gridr;
	}
	int GetGridR()
	{
		return m_gridr;
	}
	//�������R
	void SetGridC(int gridc)
	{
		m_gridc = gridc;
	}
	int GetGridC()
	{
		return m_gridc;
	}
	//����
	void compute();
	//��ȡ���
	vector<vector<ImagePoint>> GetSamePoints()
	{
		return m_samepoints;
	}
};

