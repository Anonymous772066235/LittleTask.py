#pragma once

#include <future>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include "BasicFunction.h"

using namespace std;
// //
// //RPC����
// // //RPCCOEFFCIENT
// struct RPCcoeffcient
// {
// 	double LINE_OFF;
// 	double SAMP_OFF;
// 	double LAT_OFF;
// 	double LONG_OFF;
// 	double HEIGHT_OFF;
// 	double LINE_SCALE;
// 	double SAMP_SCALE;
// 	double LAT_SCALE;
// 	double LONG_SCALE;
// 	double HEIGHT_SCALE;
// 	double LINE_NUM_COEFF[20];
// 	double LINE_DEN_COEFF[20];
// 	double SAMP_NUM_COEFF[20];
// 	double SAMP_DEN_COEFF[20];
// };

// //����RPCͶӰ����Ҫʹ�����·���任�任��Ӱ��ռ���ܻ�ȡ��Ӧ�������꣨�Ż���
// struct RPCImAffine
// {
// 	//L=lineb0+lineb1*L+lineb2*S
// 	//S=samplea0+samplea1*S+samplea2*L
// 	double samplea0; //shift parameters
// 	double samplea1;
// 	double samplea2;

// 	double lineb0; //shift parameters
// 	double lineb1;
// 	double lineb2;
// };

// //��ά��ṹ��
// struct SATPoint2D
// {
// 	// ------>sample
// 	// |
// 	// |
// 	// |
// 	// line
// 	double sample, line;
// };
// //�������
// struct SATPoint3D
// {
// 	//��γ�ȸ߳�
// 	double L, P, H;
// };

// //Ӱ���ṹ��
// struct ImagePoint
// {
// 	float X, Y;//Ӱ������
// 	int ID;//Ӱ����
// 	ImagePoint(float x, float y, int id)
// 	{
// 		X = x;
// 		Y = y;
// 		ID = id;
// 	}
// };


class CMulti_SpaceIntersection
{

public:
	//���졢��������
	CMulti_SpaceIntersection();
	~CMulti_SpaceIntersection();
	//����RPC����
	void SetInputPathParams(std::vector<std::string>  ImageListPath);
	//������������
	void SetOtherParams(int T_ProjectErr, int k, double m,std::string projpath);
	//����ͬ����
	void SetInputCorreImagePoints(std::vector<std::vector<ImagePoint>> CorrespondingImagePoints);
	//��Ƭǰ������
	bool Multi_SpaceIntersection(std::vector<SATPoint3D> &PointCloud,std::string PointCloudSavePath="./PointClouds.txt");
private:
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//·������

	// std::vector<std::string>  p_ImageListPath;
	std::vector<std::string> p_RPCParamsPaths;
	std::vector<std::string> p_RPCImAffineParamsPaths;


	//Ӱ���б�
	vector<std::string> p_ImageList;
	
	//����Ӱ��RPC����
	int p_T_ProjectErr;
	int p_k;
	double p_m;

	RPCcoeffcient p_lRPC, p_rRPC;
	RPCImAffine p_lAffine, p_rAffine;
	
	//����RPC����
	std::vector<RPCcoeffcient>p_RPCParams;
	std::vector<RPCImAffine>p_ImAffineParams;

	//����Ŀ¼
	std::string p_projpath;

	//ͬ����
	std::vector<std::vector<ImagePoint>> p_CorrespondingImagePoints;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool LoadRPCParams();
	//��
	std::vector<std::vector<double>> ReadRPCImAffineParamsFromTxt(std::string FilePath);
	RPCcoeffcient ReadRPC(char* filename);
	//�ָ�
	void Stringsplit(const std::string& str, const std::string& splits, std::vector<std::string>& res);
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//�����˲�
	vector<cv::Point3f> SOR(vector<cv::Point3f> InputPointCloud, int kdnum, double m);
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//����ת��
	SATPoint3D XYZ2BLH(double x, double y, double z);
	cv::Point3f BLH2XYZ(double b, double l, double h);
	void LonLat2UTM(double longitude, double latitude, double& UTME, double& UTMN);
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//����һ������任���� ��������任����
	bool GetInverseAffPara(RPCImAffine& srcAffPara, RPCImAffine& dstAffPara);

	//RPC����
	void SetImgAffine(RPCImAffine lAffine, RPCImAffine rAffine);
	void SetRPCParams(RPCcoeffcient& lRPCcoef, RPCcoeffcient& rRPCcoef);

	//��Ƭǰ������
	SATPoint3D Multi_RPCIntersection(vector<ImagePoint> sp,  int& flag);
	//ǰ������
	bool RPCIntersection(SATPoint2D* lpt, SATPoint2D* rpt, int npt, SATPoint3D* ptObj);

	//һ��Ӱ�����A��L����
	cv::Mat GetAandL(SATPoint2D* lpt, SATPoint3D* ptObj, int flag);
	//����Ӱ�����A��L
	cv::Mat Multi_GetAandL(vector<ImagePoint> sp, SATPoint3D* pt3d);
	//��ȡARC
	cv::Mat GetAandRCandL(SATPoint2D* lpt, SATPoint3D* ptObj, RPCImAffine imaffine);

	//�������ͶӰ��Ӱ��
	SATPoint2D RPCObj2Img(RPCcoeffcient& RPCcoef, SATPoint3D& ObjPt, RPCImAffine& affpara);
	//���������߳�ȷ�����������
	void RPCImg2Obj(RPCcoeffcient& RPCcoef, double H, RPCImAffine& affpara, SATPoint2D pimgpt, SATPoint3D& ObjPt);
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//����
	int inv(double* m1, int n);
	//�����
	void matrixmulti(double* r1, double* r2, double* r, int m, int n, int p);

	//ƫ����
	double getpartialderivativeofL1(double* rpc, double L, double P, double H);
	double getpartialderivativeofP1(double* rpc, double L, double P, double H);
	double getpartialderivativeofH1(double* rpc, double L, double P, double H);
	//���
	double getaccumulation1(double* rpc, double L, double P, double H);
	double getaccumulation1(double rpc[20], SATPoint3D& ObjPt);
	//�񷽵��﷽
	double GetPartialDerivativeofP(double Numrpc[20], double Denrpc[20], SATPoint3D& objpt, double SL);
	double GetPartialDerivativeofL(double Numrpc[20], double Denrpc[20], SATPoint3D& objpt, double SL);


};

