#pragma once


#include <iostream>
#include <stdlib.h> 
#include <io.h>
#include <vector>
#include <fstream>
//#ifdef WIN32
// #include <direct.h>
//#endif
//UBUNTU �µ�io��



#include <gdal.h>
#include <gdal_priv.h>
#include <gdal_alg.h>
#include <gdal_mdreader.h>
#include <cpl_conv.h>
#include <cpl_string.h>

#include "cpl_multiproc.h"
//#include "commonutils.h"
//#include "gdal_utils_priv.h"


#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/calib3d.hpp>
//#include "gms_matcher.h"
#include "tinyxml2.h"

//  for  readXML4Boundary
//  sudo apt-get install libxml2 
//  sudo ln -s /usr/include/libxml2/libxml   /usr/include/libxml
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>




struct SATPoint2D
{
	// ------>sample
	// |
	// |
	// |
	// line

	double sample, line;
};

struct SATPoint3D
{
	//
	double L, P, H;
};

typedef struct RPCcoeffcient
{
	double LINE_OFF;
	double SAMP_OFF;
	double LAT_OFF;
	double LONG_OFF;
	double HEIGHT_OFF;
	double LINE_SCALE;
	double SAMP_SCALE;
	double LAT_SCALE;
	double LONG_SCALE;
	double HEIGHT_SCALE;
	double LINE_NUM_COEFF[20];
	double LINE_DEN_COEFF[20];
	double SAMP_NUM_COEFF[20];
	double SAMP_DEN_COEFF[20];
};


//����RPC ͶӰ����Ҫʹ�����·���任�任��Ӱ��ռ���ܻ�ȡ��Ӧ��������
struct RPCImAffine
{
	//L=lineb0+lineb1*L+lineb2*S
	//S=samplea0+samplea1*S+samplea2*L
	double samplea0; //shift parameters
	double samplea1;
	double samplea2;

	double lineb0; //shift parameters
	double lineb1;
	double lineb2;
};


//Ӱ���ṹ��
struct ImagePoint
{
	float X, Y;//Ӱ������
	short ID;//Ӱ����
	ImagePoint(float x, float y, short id)
	{
		X = x;
		Y = y;
		ID = id;
	}
};

struct FloatSort
{
	int index;
	float value;
};

struct ImageAndGeoinfo
{
	std::vector<cv::Mat> _Image;
	char * _Proj;
	double * _GeoTrans;
};

//xml����Ҫ��Ԫ����
struct GF2Metadata
{
	std::string SatelliteID;
	std::string SensorID;
	std::string ReceiveTime;
	std::string ProductFormat;
	int Bands;
	float ImageGSD;
	float RollViewingAngle;
	float PitchViewingAngle;
	float RollSatelliteAngle;
	float PitchSatelliteAngle;
	float YawSatelliteAngle;
	float SolarAzimuth;
	float SolarZenith;
	float SatelliteAzimuth;
	float SatelliteZenith;
	float IntegrationTime;
	std::string IntegrationLevel;
	std::string EarthEllipsoid;
	std::string MtfCorrection;
	float TopLeftLatitude;
	float TopLeftLongitude;
	float TopRightLatitude;
	float TopRightLongitude;
	float BottomRightLatitude;
	float BottomRightLongitude;
	float BottomLeftLatitude;
	float BottomLeftLongitude;

};
//Ӱ��߽�
struct Boundary
{
	float TopLeftLatitude;
	float TopLeftLongitude;
	float TopRightLatitude;
	float TopRightLongitude;
	float BottomRightLatitude;
	float BottomRightLongitude;
	float BottomLeftLatitude;
	float BottomLeftLongitude;
};
//dem�߽�
struct DEMBoundary
{
	double MaxP, MaxL, MaxH;
	double MinP, MinL, MinH;
};


namespace BasicFunction
{

	//--------------------------------------------------------------------------------------------����----------------------------------------------------------------------------------------------
	//GDAL��ʽתcv::Mat
	bool GDAL2Mat(GDALDataset* InputImageData, std::vector<cv::Mat>& OutputImage, char* Proj, double* GeoTransform);
	//Mat2GDAL
	GDALDataset* Mat2GDAL(std::vector<cv::Mat>& IntputImage, char* Proj, double* GeoTransform);

	//��Ӱ���ļ��л�ȡxml�ļ���
	std::string GetXmlFilePath(std::string ImageFilePath);
	//��ȡxml�ļ�
	bool LoadXmlFile(std::string XmlFilePath, GF2Metadata& MetaData);

	//��metadata��ȡ�߽�
	Boundary GetBoundaryFromMetadata(GF2Metadata Metadata);
	//��ȡӰ��߽�
	DEMBoundary GetDEMBoundary(Boundary pImageBoundary);
	//��GeotransformParams��ȡ�߽�
	Boundary GetBoundaryFromGeotransformParams(double * GeotransformParams, cv::Size ImageSize);
	//�Ӷ���ʽ�任�л�ȡ�߽�
	DEMBoundary GetBoundaryFromPolynomialParams(cv::Size ImageSize, cv::Mat PolynomialParams);

	//constcharתchar
	void ConstChar2Char(const char* Input, char* Output);

	//����ʽ�任
	cv::Point2f PolynomialTransform(float x, float y, cv::Mat PolynomialParams);

	//�����άŷʽ����
	double CalEuDistance2D(double x1, double y1, double x2, double y2);
	//������ȡ
	void RobotSURF_CUDAMatch(const cv::Mat img1, const cv::Mat img2, std::vector<cv::Point2f>& p1, std::vector<cv::Point2f>& p2);
	//������ȡ
	void RobotSURF_CUDAMatch(const cv::Mat img1, const cv::Mat img2, std::vector<cv::Point2f>& p1,
		std::vector<cv::Point2f>& p2, int patchheight, int patchwidth);
	//Ӱ��ֱ��ͼƥ��-------------------------------------------------------------
	//cv::Mat CHistMatch(cv::Mat img1, cv::Mat img2, int code = 8);
	cv::Mat CHistMatch(const cv::Mat img1, const cv::Mat img2);
	bool compare(FloatSort a, FloatSort b);
	int GetMinNumIndex(std::vector<float> data);
	//std::vector<float> CInterP(std::vector<float> data1, std::vector<float> data2);

	//�ֿ��ļ���·���ͺ�׺��
	bool SegFilePath(std::string FilePath, std::string &FolderPath, std::string &FileName);
	//��ȡָ����׺�����ļ�
	void LoadFilesPath(std::string FolderPath, std::string Exd, std::vector<std::string>& FilesPath);
	//�����ļ���׺��
	bool ChangeSuffix(std::string FilePath, std::string Suffix, std::string& NFilePath);
	//��ȡ�ļ���׺��
	std::string GetFileSuffix(std::string FilePath);
	//���ж�ȡtxt��·��
	bool ReadImageNames(std::string ListPath, std::vector<std::string>& Data);
	//��ȡ�ϼ��ļ���Ŀ¼ 
	bool GetFolderPath(std::string FilePath, std::string &FolderPath);
	//ȥ���ļ���һЩ�ո�
	void Trim(std::string & str);

	//--------------------------------------------------------------------------------------------��-----------------------------------------------------------------------------------------------
	//��ȡGTiffӰ��
	GDALDataset* ReadGTiffImage(std::string ImagePath, GDALRPCInfo& RPCParams);
	//��ȡ�ನ��Ӱ�񣨶���ļ���
	ImageAndGeoinfo ReadMulBandImageFromFolder(std::string ImagePath, GDALRPCInfo& RPCParams);
	//��ȡHDF��ʽ�ļ�
	GDALDataset* ReadHDFImage(std::string ImagePath);

	//bageyalu--------------------------------------------------------------------------------------
	//��xml��ȡ�߽�
	bool GetBoundaryfromXML(std::string xmlpath, Boundary& bound);
	//��ȡ������tif��mat
	cv::Mat ReadTifoneBand(std::string filename);
	//��ȡ�ನ��tif��mat
	std::vector<cv::Mat> ReadTif(std::string filename);
	//ͶӰϵ������ϵת��-----------------------------------------------------------------
	cv::Point3f WGS842Proj(int des_code, double lon, double lat,double H);
	cv::Point2d Proj2WGS84(int code, cv::Point2d p);
	cv::Point2d WGS842Proj(std::string mode, double lon, double lat);//x��y
	cv::Point2d Proj2WGS84(std::string mode, cv::Point2d p, double mean_lon);//lon��lat
	int search_epsg_code(std::string datum,std::string mode, double lon);

	//�ַ����ָ�
	void Stringsplit(const std::string& str, const std::string& splits, std::vector<std::string>& res);

	//--------------------------------------------------------------------------------------------д-----------------------------------------------------------------------------------------------
	//��cv::Matд��Ϊtiff
	void SaveImageAsTiff(std::vector<cv::Mat> Image, std::string SaveFilePath, char* Proj, double* GeoTransform);
	//��ָ����ʽд��Ӱ�񣬳���JPEG2000
	void SaveImage(std::vector<cv::Mat> Image, std::string Format, std::string SaveFilePath, char* Proj, double* GeoTransform);
	//��JPEG2000д��
	void SaveImageASOtherFormat(std::vector<cv::Mat> Image, std::string Format, std::string SaveFilePath, char* Proj, double* GeoTransform);
	//----------------------------------------------------------------------------------------------��־--------------------------------------------------------------------------------------------
	//�����ļ���
	int CreateFolder(std::string FolderPath);
	//ɾ���ļ���
	int DeleteFolder(std::string FolderPath);
	//д��ָ��string���ļ�(û���򴴽���������)
	void Write2Text(std::string FilePath, std::string Data);
	//ɾ��ָ���ļ�
	int DeleteFile(std::string FilePath);
	//��ѯ�ļ��Ƿ����
	bool File_Exist(const std::string& name);
	//��ѯ�ļ����Ƿ����
	bool Path_Exist(const std::string& name);
	//��ָ������ת��Ϊjson��ʽ�����浽ָ���ļ�
	std::string Convert2Json_new(int Code, std::string Message, float Process, std::string isEnd);
	//original version of Convert2Json
	std::string Convert2Json(int Code, std::string Message, float Process = 0, std::string CurrentWork = "");
	//��������
	cv::Mat LinearStrech(cv::Mat img, float ratio=0.02, int code=8, int dtype= CV_8UC1);
	//��ȡ��ͼ��,ǰ������rgb����������x��y
	std::vector<cv::Mat> GetSubPatch(std::string Img_path, cv::Point2d TLPoint, cv::Point2d BRPoint);
	std::vector<cv::Mat> GetSubPatch(std::string Img_path, cv::Point2d TLPoint, int width, int height);
	//��ȡ��ͼ��Ӧ������ϵͳ
	std::string GetBaseMapMode(std::string imgpath);
	//��ȡZY3��xml�еĽǵ�
	int readXML4Boundary(std::string xmlPath, std::vector<std::vector<double>> & CornerPoints );
};

