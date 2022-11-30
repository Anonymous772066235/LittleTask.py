#include "BasicFunction.h"
#include <stdio.h>

using namespace std;

//ȥ���ļ��пո�
void BasicFunction::Trim(std::string & str)
{
	std::string blanks("\f\v\r\t\n ");
    str.erase(0,str.find_first_not_of(blanks));
    str.erase(str.find_last_not_of(blanks) + 1);
}
//��ȡ�ϼ��ļ���Ŀ¼ 
bool BasicFunction::GetFolderPath(std::string FilePath, std::string &FolderPath)
{
	auto Iter = std::find(FilePath.crbegin(), FilePath.crend(), '/');
	FolderPath = std::string(FilePath.cbegin(), Iter.base());
	return 1;
	
}
//���ж�ȡtxt��·��
bool BasicFunction::ReadImageNames(std::string ListPath, vector<std::string> &Data)
{
	ifstream infile;

	infile.open(ListPath);   //���ļ����������ļ��������� 
	if (infile.is_open())//��ʧ��,�����������Ϣ,����ֹ�������� 
	{
		string s;
		while (getline(infile, s))
		{
			Trim(s);
			Data.push_back(s.c_str());
			std::cout<<s<<endl;
		}
	}
	else
	{
		return 0;
	}
	infile.close();             //�ر��ļ�����
	return 1;
}

//��־-----------------------------------------------------------------------------------------------
//�����ļ���
int  BasicFunction::CreateFolder(std::string FolderPath)
{
	int State = mkdir(FolderPath.c_str(),0);
	return State;
}

//ɾ���ļ���
int BasicFunction::DeleteFolder(std::string FolderPath)
{
	int State = rmdir(FolderPath.c_str());
	return State;
}

//д��ָ��string���ļ�(û���򴴽���������)
void BasicFunction::Write2Text(std::string FilePath, std::string Data)
{
	ofstream os;     //����һ���ļ����������
	os.open(FilePath, ios::out);//���������ļ�������ios::app ׷�ӣ�������
	os << Data << endl;
	os.close();
}

//ɾ��ָ���ļ�
int BasicFunction::DeleteFile(std::string FilePath)
{
	if (remove(FilePath.c_str()) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//��ѯ�ļ��Ƿ����
bool BasicFunction::File_Exist(const std::string& FilePath)
{
	ifstream f(FilePath.c_str());
	return f.good();
}
bool BasicFunction::Path_Exist(const std::string& name)
{
	return access(name.c_str(), 0);
}
//��ָ������ת��Ϊjson��ʽ�����浽ָ���ļ�
std::string BasicFunction::Convert2Json_new(int Code, std::string Message, float Process, std::string isEnd)
{
	std::string JsonMessage;
	
	{
		//��ȡϵͳʱ��
		time_t timep;
		struct tm* p;
		time(&timep); //��ȡ��1970������˶����룬����time_t���͵�timep
		p = localtime(&timep);//��localtime������ת��Ϊstruct tm�ṹ��

		//��ʱ��תstring
		std::string sTime = std::to_string(p->tm_year + 1900) + "-" + std::to_string(p->tm_mon+1) + "-" + std::to_string(p->tm_mday) +
			" " + std::to_string(p->tm_hour) + ":" + std::to_string(p->tm_min) + ":" + std::to_string(p->tm_sec);
		//����
		//����
		JsonMessage = "{\"process\":\"";
		JsonMessage += std::to_string(Process) + "\",";

		//ʱ��
		JsonMessage += "\"time\":\"";
		JsonMessage += sTime;
		JsonMessage += "\",";


		//�������
		JsonMessage += "\"code\":\"";
		JsonMessage += std::to_string(Code) + "\",";

		//��Ϣ
		JsonMessage += "\"msg\":\"";
		JsonMessage += Message + "\",";

		//��Ϣ
		JsonMessage += "\"isEnd\":\"";
		JsonMessage += isEnd + "\"}";

		return JsonMessage;
	}
}

// original version of Convert2Json
string BasicFunction::Convert2Json(int Code, std::string Message, float Process, std::string CurrentWork)
{
	std::string JsonMessage;
	if (Process == 0)
	{
		//����Ϊ��
		JsonMessage = "{\"data\":\"\",";

		//�������
		JsonMessage += "\"code\":";
		JsonMessage += std::to_string(Code) + ",";

		//��Ϣ
		JsonMessage += "\"msg\":\"";
		JsonMessage += Message + "\"}";

		return JsonMessage;
	}
	else
	{
		//��ȡϵͳʱ��
		time_t timep;
		struct tm* p;
		time(&timep); //��ȡ��1970������˶����룬����time_t���͵�timep
		p = localtime(&timep);//��localtime������ת��Ϊstruct tm�ṹ��

		//��ʱ��תstring
		std::string sTime = std::to_string(p->tm_year + 1900) + "-" + std::to_string(p->tm_mon+1) + "-" + std::to_string(p->tm_mday) +
			" " + std::to_string(p->tm_hour) + ":" + std::to_string(p->tm_min) + ":" + std::to_string(p->tm_sec);
		//����
		//����
		JsonMessage = "{\"data\":[{\"process\":";
		JsonMessage += std::to_string(Process) + ",";

		//��ǰ����
		JsonMessage += "\"name\":\"";
		JsonMessage += CurrentWork + "\",";

		//ʱ��
		JsonMessage += "\"time\":\"";
		JsonMessage += sTime;
		JsonMessage += "\"}],";


		//�������
		JsonMessage += "\"code\":";
		JsonMessage += std::to_string(Code) + ",";

		//��Ϣ
		JsonMessage += "\"msg\":\"";
		JsonMessage += Message + "\"}";

		return JsonMessage;
	}
}
//��ȡָ����׺�����ļ�
void BasicFunction::LoadFilesPath(string FolderPath, string Exd, vector<string>& FilesPath)
{
	/*const std::string path0 = FolderPath;
    DIR* pDir;
    struct dirent* ptr;
 
    struct stat s;
    lstat(FolderPath.c_str(), &s);
 
    if(!S_ISDIR(s.st_mode)){
        std::cout << "not a valid directory: " << FolderPath << std::endl;
        return;
    }
 
    if(!(pDir = opendir(FolderPath.c_str()))){
        std::cout << "opendir error: " << FolderPath << std::endl;
        return;
    }
    int i = 0;
    std::string subFile;
    while((ptr = readdir(pDir)) != 0){
        subFile = ptr -> d_name;
        if(subFile == "." || subFile == "..")
            continue;
		if(BasicFunction::GetFileSuffix(subFile)==Exd)
		{
        subFile = path0 + subFile;
        std::cout << ++i << ": " << subFile << std::endl;
        FilesPath.push_back(subFile);
		}
    }
    closedir(pDir);*/

}


cv::Mat BasicFunction::ReadTifoneBand(std::string filename)
{
	char* Proj;
	double* GeoTransform;
	//��ʼ��GDAL��ע���
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	//��ȡӰ��
	GDALDataset* ImageData = (GDALDataset*)GDALOpen(filename.data(), GA_ReadOnly);
	//��ȡͶӰת��
	const char* const_prj = ImageData->GetProjectionRef();
	Proj = const_cast<char*>(const_prj);
	//std::cout << Proj << std::endl;
	//��ȡ������Ϣ
	GeoTransform = new double[6];
	ImageData->GetGeoTransform(GeoTransform);
	/*for (int i(0); i<6; ++i)
	{
		cout << GeoTransform[i] << endl;
	}*/
	//��ȡդ�����ݣ�Ĭ��ֻ������һ����
	int Width = ImageData->GetRasterXSize(); // �� 
	int Height = ImageData->GetRasterYSize(); // �� 
	//int BandSize = ImageData->GetRasterCount();//������
	float* Data_of_Band;   // �洢����
	Data_of_Band = new float[Width * Height];
	GDALRasterBand* pBand = ImageData->GetRasterBand(1);
	GDALDataType DataType = pBand->GetRasterDataType();
	pBand->RasterIO(GF_Read, 0, 0, Width, Height, Data_of_Band,
		Width, Height, GDT_Float32, 0, 0);
	cv::Mat Band_Image = cv::Mat(Height, Width, CV_32FC1, Data_of_Band);
	//2%��������ķ�ʽת��Ϊuint8
	cv::Mat nimg = LinearStrech(Band_Image, 0.01);
	Band_Image.release();
	if (Data_of_Band != NULL)
	{
		delete[] Data_of_Band;
	}
	return nimg;
}


std::vector<cv::Mat> BasicFunction::ReadTif(std::string filename)
{
	char* Proj;
	double* GeoTransform;
	//��ʼ��GDAL��ע���
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	//��ȡӰ��
	GDALDataset* ImageData = (GDALDataset*)GDALOpen(filename.data(), GA_ReadOnly);
	//��ȡͶӰת��
	const char* const_prj = ImageData->GetProjectionRef();
	Proj = const_cast<char*>(const_prj);
	//��ȡ������Ϣ
	GeoTransform = new double[6];
	ImageData->GetGeoTransform(GeoTransform);
	//��ȡդ�����ݣ�Ĭ��ֻ������һ����
	int Width = ImageData->GetRasterXSize(); // �� 
	int Height = ImageData->GetRasterYSize(); // �� 
	int BandSize = ImageData->GetRasterCount();//������
	std::vector<cv::Mat> imgs;
	for (int i(0); i < BandSize; ++i)
	{
		float* Data_of_Band;   // �洢����
		Data_of_Band = new float[Width * Height];
		GDALRasterBand* pBand = ImageData->GetRasterBand(i + 1);
		GDALDataType DataType = pBand->GetRasterDataType();
		pBand->RasterIO(GF_Read, 0, 0, Width, Height, Data_of_Band,
			Width, Height, GDT_Float32, 0, 0);
		cv::Mat Band_Image = cv::Mat(Height, Width, CV_32FC1, Data_of_Band);
		//2%��������ķ�ʽת��Ϊuint8
		cv::Mat nimg = LinearStrech(Band_Image, 0.01);
		Band_Image.release();
		if (Data_of_Band != NULL)
		{
			delete[] Data_of_Band;
		}
		imgs.push_back(nimg);
	}
	return imgs;
}


bool BasicFunction::GetBoundaryfromXML(std::string xmlpath, Boundary& bound)
{
	tinyxml2::XMLDocument XmlFile;
	if (XmlFile.LoadFile(xmlpath.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "��xml�ļ�ʧ�ܣ������ļ�Ŀ¼!" << std::endl;
		return false;
	}
	//tinyxml2::XMLElement* rootElement = XmlFile.RootElement()->FirstChildElement("ProductMetaData");
	tinyxml2::XMLElement* rootElement = XmlFile.RootElement();
	const char* tMetadata;
	//���Ͻ�
	if (rootElement->FirstChildElement("TopLeftLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopLeftLongitude")->GetText();
		bound.TopLeftLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��";
	}
	if (rootElement->FirstChildElement("TopLeftLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopLeftLatitude")->GetText();
		bound.TopLeftLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���Ͻ�γ�ȶ�ʧ��";
	}
	//���Ͻ�
	if (rootElement->FirstChildElement("TopRightLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopRightLongitude")->GetText();
		bound.TopRightLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��";
	}
	if (rootElement->FirstChildElement("TopRightLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopRightLatitude")->GetText();
		bound.TopRightLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��";
	}
	//���½�
	if (rootElement->FirstChildElement("BottomLeftLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomLeftLongitude")->GetText();
		bound.BottomLeftLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���½Ǿ���ʧ��";
	}
	if (rootElement->FirstChildElement("BottomLeftLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomLeftLatitude")->GetText();
		bound.BottomLeftLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���½Ǿ���ʧ��";
	}
	//���½�
	if (rootElement->FirstChildElement("BottomRightLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomRightLongitude")->GetText();
		bound.BottomRightLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��";
	}
	if (rootElement->FirstChildElement("BottomRightLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomRightLatitude")->GetText();
		bound.BottomRightLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��";
	}
	return true;
}

//��ȡ�ನ��Ӱ�񣨶���ļ���
ImageAndGeoinfo BasicFunction::ReadMulBandImageFromFolder(std::string ImagePath, GDALRPCInfo &RPCParams)
{
	//���ȶ�ȡָ��Ӱ��
	GDALDataset* FirstBand = BasicFunction::ReadGTiffImage(ImagePath, RPCParams);

	//ָ��Ӱ��ĳߴ�
	int Height = FirstBand->GetRasterYSize();
	int Width = FirstBand->GetRasterXSize();

	//�ָ��ļ������ļ���·��
	std::string FolderPath, FileName;
	BasicFunction::SegFilePath(ImagePath, FolderPath, FileName);

	//��ȡ��ǰ�ļ��ĺ�׺��
	std::string Suffix = BasicFunction::GetFileSuffix(ImagePath);
	std::vector<std::string>ImageFilePath;
	BasicFunction::LoadFilesPath(FolderPath, Suffix, ImageFilePath);
	

	//��Ҫ���صĶ���Ϣ
	ImageAndGeoinfo ImageData;
	//��ȡ��Ϣ
	for (int i = 0; i < ImageFilePath.size(); i++)
	{
		GDALRPCInfo iRPCParams;
		GDALDataset* iImageData = BasicFunction::ReadGTiffImage(ImageFilePath[i], iRPCParams);
		if (iImageData->GetRasterYSize() == Height && iImageData->GetRasterXSize() == Width)
		{
			//��ȡÿ������
			std::vector<cv::Mat> iBand;

			//
			char* iProjParams = new char[1000];
			double iGeoParams[6];
			if (BasicFunction::GDAL2Mat(iImageData, iBand, iProjParams, iGeoParams))
			{
				for (int j = 0; j < iBand.size(); j++)
				{
					ImageData._Image.push_back(iBand[j]);
				}
			}
			if (i == 0)
			{
				ImageData._GeoTrans = iGeoParams;
				ImageData._Proj = iProjParams;
			}
		}
		//iImageData->Release();
	}

	return ImageData;
}
//��ȡGF2Ӱ��RPB�ļ�
GDALDataset* BasicFunction::ReadGTiffImage(std::string ImagePath, GDALRPCInfo &RPCParams)
{
	//��ʼ��GDAL��ע���
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");

	//�ָ��ļ������ļ���·��
	std::string FolderPath, FileName;
	BasicFunction::SegFilePath(ImagePath, FolderPath, FileName);

	//��ȡ��ǰ�ļ��ĺ�׺��
	std::vector<std::string>ImageFilePath;
	BasicFunction::LoadFilesPath(FolderPath, "", ImageFilePath);

	for (int i = 0; i < ImageFilePath.size(); i++)
	{
		string iSuffix = BasicFunction::GetFileSuffix(ImageFilePath[i]);
		if (iSuffix == "rpb")
		{
			break;
		}
		else if (iSuffix == "rpc")
		{
			string NewImageFilePath;
			ChangeSuffix(ImageFilePath[i], "rpb", NewImageFilePath);
			int ret = rename(ImageFilePath[i].data(), NewImageFilePath.data());

			//break;
		}

	}

	//��ȡӰ��
	GDALDataset* ImageData = (GDALDataset*)GDALOpen(ImagePath.data(), GA_ReadOnly);
	
	if (ImageData == NULL)
	{
		std::cout << "��ȡӰ������ʧ�ܣ�����Ӱ��Ŀ¼" << std::endl;
		return FALSE;
	}
	else
	{

		//��ȡrpc����
		char** RPC = ImageData->GetMetadata("RPC");
		GDALExtractRPCInfo(RPC, &RPCParams);//��ʽ�����ṹ��oInfo������
		
		delete[]RPC;
		return ImageData;
	}
}
//��ȡhdfӰ��
GDALDataset* BasicFunction::ReadHDFImage(std::string ImagePath)
{

	//��ʼ��GDAL��ע���
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	//��ȡӰ��
	GDALDataset* ImageData_Total = (GDALDataset*)GDALOpen(ImagePath.data(), GA_ReadOnly);

	vector<string> vtDatasets;
	char** metadata = ImageData_Total->GetMetadata("SUBDATASETS");
	if (0 < CSLCount(const_cast<const char* const*>(metadata)))
	{
		for (int i = 0; metadata[i]; i ++)
		{
			string strDSName(metadata[i]);
			//std::cout << strDSName << '\n';
			strDSName = strDSName.substr(strDSName.find_first_of('=') + 1);
			vtDatasets.push_back(strDSName);
		}
	}

	GDALDataset* ImageData =  (GDALDataset*)GDALOpen(vtDatasets[4].c_str(), GA_ReadOnly);
	return ImageData;

}

bool isPointInRect(cv::Point p, cv::Rect rect)
{
	int x0 = p.x;
	int y0 = p.y;
	int x1 = rect.x;
	int y1 = rect.y;
	int x2 = rect.x + rect.width;
	int y2 = rect.y + rect.height;
	if ((x1 < x0 && x0 < x2) &&
		(y1 < y0 && y0 < y2))
		return true;
	else
		return false;
}
//
// ³����surfcuda����ƥ��
void BasicFunction::RobotSURF_CUDAMatch(const cv::Mat img1, const cv::Mat img2,
	vector<cv::Point2f>& p1, vector<cv::Point2f>& p2)
{
	//������ȡ
	cv::cuda::GpuMat keypoints1, descriptions1, keypoints2, descriptions2;
	cv::cuda::GpuMat dimg1(img1), dimg2(img2);
	cv::cuda::SURF_CUDA surf_cuda;
	surf_cuda(dimg1, cv::cuda::GpuMat(), keypoints1, descriptions1);
	surf_cuda(dimg2, cv::cuda::GpuMat(), keypoints2, descriptions2);
	//download�ؼ���
	vector<cv::KeyPoint> kp1, kp2;
	surf_cuda.downloadKeypoints(keypoints1, kp1);
	surf_cuda.downloadKeypoints(keypoints2, kp2);
	//Ӳƥ��
	auto matcher = cv::cuda::DescriptorMatcher::createBFMatcher(cv::NORM_L2);
	vector<cv::DMatch> matches;
	matcher->match(descriptions1, descriptions2, matches);
	//GMS�޳���ƥ��
	vector<cv::DMatch> mts;
	cv::xfeatures2d::matchGMS(img1.size(), img2.size(), kp1, kp2, matches, mts, 0, 0, 10.);
	//ransac�޳���ƥ��
	vector<cv::DMatch> GoodMatches = mts;
	//vector<cv::KeyPoint> RAN_KP1, RAN_KP2;
	//for (int i(0); i < GoodMatches.size(); ++i)
	//{
	//	RAN_KP1.push_back(kp1[mts[i].queryIdx]);
	//	RAN_KP2.push_back(kp2[mts[i].trainIdx]);
	//}
	////�����������ͱ任
	//vector<cv::Point2f> p01, p02;
	//for (int j(0); j < GoodMatches.size(); ++j)
	//{
	//	p01.push_back(RAN_KP1[j].pt);
	//	p02.push_back(RAN_KP2[j].pt);
	//}
	////RANSAC����
	//vector<uchar> RansacStatus;
	//cv::Mat Fundamental = cv::findFundamentalMat(p01, p02, RansacStatus, cv::FM_RANSAC);
	//int iter = 0;
	//for (int i(0); i < mts.size(); ++i)
	//{
	//	if (RansacStatus[i] == 0)
	//		GoodMatches.erase(GoodMatches.begin() + iter);
	//	else
	//		iter++;
	//}
	//����㼯
	for (int i(0); i < GoodMatches.size(); ++i)
	{
		int index1 = GoodMatches[i].queryIdx;
		int index2 = GoodMatches[i].trainIdx;
		p1.push_back(kp1[index1].pt);
		p2.push_back(kp2[index2].pt);
	}
}


void BasicFunction::RobotSURF_CUDAMatch(const cv::Mat img1, const cv::Mat img2, std::vector<cv::Point2f>& p1,
	std::vector<cv::Point2f>& p2, int patchheight, int patchwidth)
{
	//�ֿ���йؼ�����ȡ
	int rows = img1.rows;
	int cols = img1.cols;
	//��ȡ����Ŀ
	int rpatchnum = (float)rows / patchheight;
	int cpatchnum = (float)cols / patchwidth;
	//������С
	patchheight = (float)rows / rpatchnum;
	patchwidth = (float)cols / cpatchnum;
	for (int i(0); i < rpatchnum; ++i)
	{
		for (int j(0); j < cpatchnum; ++j)
		{
			//��ȡ����Ӱ��
			cv::Mat mimg1 = img1(cv::Rect(j * patchwidth, i * patchheight, patchwidth, patchheight)).clone();
			cv::Mat mimg2 = img2(cv::Rect(j * patchwidth, i * patchheight, patchwidth, patchheight)).clone();
			//����Ӱ��ƥ��
			std::vector<cv::Point2f> mp1, mp2;
			RobotSURF_CUDAMatch(mimg1, mimg2, mp1, mp2);
			//�ָ��ؼ������겢����ջ
			for (int k(0); k < mp1.size(); ++k)
			{
				mp1[k].x += j * patchwidth;
				mp1[k].y += i * patchheight;
				mp2[k].x += j * patchwidth;
				mp2[k].y += i * patchheight;
				p1.push_back(mp1[k]);
				p2.push_back(mp2[k]);
			}
		}
	}
}

//MatתGDAL��ʽ
GDALDataset* BasicFunction::Mat2GDAL(std::vector<cv::Mat>& IntputImage, char* Proj, double* GeoTransform)
{
	GDALDataset* tmp;
}
//��ȡdem�ı߽�
DEMBoundary BasicFunction::GetDEMBoundary(Boundary pImageBoundary)
{

	DEMBoundary pDEMBoundary;
	//��Ӱ��߽�д��cv����
	cv::Mat Lon(4, 1, CV_32F);
	cv::Mat Lat(4, 1, CV_32F);
	Lon.at<float>(0, 0) = pImageBoundary.BottomLeftLongitude;
	Lon.at<float>(0, 1) = pImageBoundary.BottomRightLongitude;
	Lon.at<float>(0, 2) = pImageBoundary.TopLeftLongitude;
	Lon.at<float>(0, 3) = pImageBoundary.TopRightLongitude;

	Lat.at<float>(0, 0) = pImageBoundary.BottomLeftLatitude;
	Lat.at<float>(0, 1) = pImageBoundary.BottomRightLatitude;
	Lat.at<float>(0, 2) = pImageBoundary.TopLeftLatitude;
	Lat.at<float>(0, 3) = pImageBoundary.TopRightLatitude;

	//��ȡ��ֵ
	double MinLon, MinLat, MaxLon, MaxLat;

	cv::minMaxIdx(Lon, &MinLon, &MaxLon);
	cv::minMaxIdx(Lat, &MinLat, &MaxLat);
	if (MinLon < 0)
	{
		MinLon = 0;
	}
	if (MinLat < 0)
	{
		MinLat = 0;
	}

	pDEMBoundary.MinP = MinLat;
	pDEMBoundary.MinL = MinLon;

	pDEMBoundary.MaxP = MaxLat;
	pDEMBoundary.MaxL = MaxLon;

	//std::cout << "DEM�߽�: " << std::endl;
	//std::cout << "MinLon: " << pDEMBoundary.MinL << "  MinLat" << pDEMBoundary.MinP << std::endl;
	//std::cout << "MaxLon: " << pDEMBoundary.MaxL << "  MaxLat" << pDEMBoundary.MaxP << std::endl;
	return pDEMBoundary;
}
//��ȡ�ļ���׺��
std::string BasicFunction::GetFileSuffix(std::string FilePath)
{
	std::string Suffix;
	for (int i = FilePath.size() - 1; i > 0; i--)
	{
		if (FilePath[i] == '.')
		{
			Suffix = FilePath.substr(i + 1);
			return Suffix;
		}
	}
	Suffix = FilePath;
	return Suffix;
}
//�ֿ��ļ���·���ͺ�׺��
bool BasicFunction::SegFilePath(std::string FilePath, std::string& FolderPath, std::string& FileName)
{
	int index = FilePath.find_last_of("\\");
	if (index == -1)
	{
		index = FilePath.find_last_of("/");
	}
	//std::cout << index << std::endl;
	//�ļ���
	FolderPath = FilePath.substr(0, index);
	//�ļ���
	FileName = FilePath.substr(index + 1, -1);


}
//�����ļ���׺��
bool BasicFunction::ChangeSuffix(std::string FilePath, std::string Suffix,std::string & NFilePath)
{

	auto Iter = std::find(FilePath.crbegin(), FilePath.crend(), '.');
	NFilePath = std::string(FilePath.cbegin(), Iter.base());
	NFilePath += Suffix;

	return true;
}

//��GDAL����д��ΪTIFF

void BasicFunction::SaveImageAsTiff(std::vector<cv::Mat> Image, std::string SaveFilePath, char* Proj, double* GeoTransform)
{
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	const int BandSize =Image.size();
	const int Height = Image[0].rows;
	const int Width = Image[0].cols;

	
	GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	GDALDataset* ImageData;
	
	ImageData = poDriver->Create(SaveFilePath.data(),Width, Height, BandSize, GDT_Float32, NULL);

	const char* Projection = Proj;
	ImageData->SetGeoTransform(GeoTransform);
	ImageData->SetProjection(Projection);

	int PatchSize = 1000;


	if (Width > 10 * PatchSize && Height > 10 * PatchSize)
	{
		int WLops = Width / PatchSize + 1;
		int HLops = Height / PatchSize + 1;

		//cout << float(Width) / float(PatchSize) <<"  " << Width / PatchSize << endl;
		//闂佽法鍠撶瑧濠靛倸鈧喐褰ч柟椋庡厴閺佹捇�?��妶鍡楊伓闂佽法鍠愰弸濠氬�?���?��顦ч梺璺ㄥ枑鐟欙箓鏁嶅畝鍐惧殝闁归鍏橀�?��诲�?閵堝棗�?�?1
		if (float(Width) / float(PatchSize) == Width / PatchSize)
		{
			WLops = WLops - 1;
		}
		if (float(Height) / float(PatchSize) ==  Height / PatchSize)
		{
			HLops = HLops - 1;
		}
		//cout << WLops << "  " << HLops << endl;
		for (int i = 0; i < BandSize; i++)
		{
			GDALRasterBand* pBand = ImageData->GetRasterBand(i + 1);

			for (int j = 0; j < HLops; j++)
			{
				for (int k = 0; k < WLops; k++)
				{
					if (j != HLops - 1 && k != WLops - 1)
					{
						float* Data_of_Band = new float[PatchSize * PatchSize];

						cv::Mat _kPatch;
						Image[i](cv::Rect(k* PatchSize, j* PatchSize, PatchSize, PatchSize)).copyTo(_kPatch );
						
						cv::Mat kPatch = _kPatch.reshape(1, 1);

						for (int l = 0; l < PatchSize * PatchSize; l++)
						{
							Data_of_Band[l] = kPatch.at<float>(0, l);

						}
						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, PatchSize, PatchSize, Data_of_Band,
							PatchSize, PatchSize, GDT_Float32, 0, 0);//闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?��氱+1闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?���?��鏌ㄩ悢璇测枏缁炬澘顦�?���?��鏌ㄩ悢鍛婄伄闁归鍏橀�?��诲�?閻ゎ垱褰ч柟�?庡厴閺佹捇�?妶鍡�?伓Data_of_Band

						delete[]Data_of_Band;
						_kPatch.release();
						kPatch.release();
					}
					else if (j != HLops - 1 && k == WLops - 1)
					{
						float* Data_of_Band = new float[PatchSize * (Width - k * PatchSize)];

						cv::Mat _kPatch;
						Image[i](cv::Rect(k* PatchSize, j* PatchSize, (Width - k * PatchSize), PatchSize)).copyTo(_kPatch);

						cv::Mat kPatch = _kPatch.reshape(1, 1);
						for (int l = 0; l < PatchSize * (Width - k * PatchSize); l++)
						{
							Data_of_Band[l] = kPatch.at<float>(0, l);

						}

						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, (Width - k * PatchSize), PatchSize, Data_of_Band,
							(Width - k * PatchSize), PatchSize, GDT_Float32, 0, 0);//闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?��氱+1闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?���?��鏌ㄩ悢璇测枏缁炬澘顦�?���?��鏌ㄩ悢鍛婄伄闁归鍏橀�?��诲�?閻ゎ垱褰ч柟�?庡厴閺佹捇�?妶鍡�?伓Data_of_Band

						delete[]Data_of_Band;
						_kPatch.release();
						kPatch.release();
					}
					else if (j == HLops - 1 && k != WLops - 1)
					{
						float* Data_of_Band = new float[(Height - j * PatchSize) * PatchSize];

						cv::Mat _kPatch;
						Image[i](cv::Rect(k* PatchSize, j* PatchSize, PatchSize, Height - j * PatchSize)).copyTo(_kPatch);
						cv::Mat kPatch = _kPatch.reshape(1, 1);

						for (int l = 0; l < (Height - j * PatchSize) * PatchSize; l++)
						{
							Data_of_Band[l] = kPatch.at<float>(0, l);

						}

						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, PatchSize, Height - j * PatchSize, Data_of_Band,
							PatchSize, Height - j * PatchSize, GDT_Float32, 0, 0);//闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?��氱+1闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?���?��鏌ㄩ悢璇测枏缁炬澘顦�?���?��鏌ㄩ悢鍛婄伄闁归鍏橀�?��诲�?閻ゎ垱褰ч柟�?庡厴閺佹捇�?妶鍡�?伓Data_of_Band

						delete[]Data_of_Band;
						_kPatch.release();
						kPatch.release();
					}
					else
					{
						float* Data_of_Band = new float[(Height - j * PatchSize) * (Width - k * PatchSize)];

						cv::Mat _kPatch;
						Image[i](cv::Rect(k* PatchSize, j* PatchSize, Width - k * PatchSize, Height - j * PatchSize)).copyTo(_kPatch);

						cv::Mat kPatch = _kPatch.reshape(1, 1);

						for (int l = 0; l < (Height - j * PatchSize) * (Width - k * PatchSize); l++)
						{
							Data_of_Band[l] = kPatch.at<float>(0, l);

						}

						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, Width - k * PatchSize, Height - j * PatchSize, Data_of_Band,
							Width - k * PatchSize, Height - j * PatchSize, GDT_Float32, 0, 0);//闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?��氱+1闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?���?��鏌ㄩ悢璇测枏缁炬澘顦�?���?��鏌ㄩ悢鍛婄伄闁归鍏橀�?��诲�?閻ゎ垱褰ч柟�?庡厴閺佹捇�?妶鍡�?伓Data_of_Band

						delete[]Data_of_Band;
						_kPatch.release();
						kPatch.release();
					}
				}
			}


		}
	}
	else
	{
		for (int i = 0; i < BandSize; i++)
		{
			GDALRasterBand* pBand = ImageData->GetRasterBand(i + 1);
			float* Data_of_Band = new float[Height * Width];

			cv::Mat strechimage = Image[i].reshape(1, 1);

			for (int j = 0; j < Height * Width; j++)
			{
				Data_of_Band[j] = strechimage.at<float>(0, j);

			}
			//闂佽法鍠�?��顏堝棘閵堝�?顏堕梺璺ㄥ枍閼煎酣妫�?��鍌氼伓鐎殿喖绻�?拹鐑T_Float32闂佽法鍠愰弸濠氬�?���?���?遍梺璺ㄥ枑閺�?��骞忛悿�?ｆ矗闂佽法鍠愰弸濠氬�?��勬壆瀹�
			pBand->RasterIO(GF_Write, 0, 0, Width, Height, Data_of_Band, Width, Height, GDT_Float32, 0, 0);
			delete[]Data_of_Band;

		}
	}




	
	delete[]Projection;

	//std::cout << "闂佽法鍠愰弸濠氬�?��戣姤鏅搁柡鍌樺€�?��氱銇愰柆�?嗘�?闁哄倶鍊�?���?���?��幒妤佹�?闁跨噦鎷�?!" << std::endl;
	GDALClose(ImageData);
}


// void BasicFunction::SaveImageAsTiff(std::vector<cv::Mat> Image, std::string SaveFilePath, char* Proj, double* GeoTransform)
// {
// 	  std::cout<<"692\n";
// 	const int BandSize =Image.size();
// 	const int Height = Image[0].rows;
// 	const int Width = Image[0].cols;

// 	GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
// 	GDALDataset* ImageData;
// 	//�½��ĸ�ʽΪGDT_Float32��һ��Ҫ��Ӧ
// 	ImageData = poDriver->Create(SaveFilePath.data(), Width, Height, BandSize, GDT_Float32, NULL);

// 	const char* Projection = Proj;
// 	ImageData->SetGeoTransform(GeoTransform);
// 	ImageData->SetProjection(Projection);

// 	int PatchSize = 1000;


// 	if (Width > 10 * PatchSize && Height > 10 * PatchSize)
// 	{
// 		int WLops = Width / PatchSize + 1;
// 		int HLops = Height / PatchSize + 1;

// 		//cout << float(Width) / float(PatchSize) <<"  " << Width / PatchSize << endl;
// 		//�պô�����ʱ�򣬲���1
// 		if (float(Width) / float(PatchSize) == Width / PatchSize)
// 		{
// 			WLops = WLops - 1;
// 		}
// 		if (float(Height) / float(PatchSize) ==  Height / PatchSize)
// 		{
// 			HLops = HLops - 1;
// 		}
// 		//cout << WLops << "  " << HLops << endl;
// 		for (int i = 0; i < BandSize; i++)
// 		{
// 			GDALRasterBand* pBand = ImageData->GetRasterBand(i + 1);

// 			for (int j = 0; j < HLops; j++)
// 			{
// 				for (int k = 0; k < WLops; k++)
// 				{
// 					if (j != HLops - 1 && k != WLops - 1)
// 					{
// 						float* Data_of_Band = new float[PatchSize * PatchSize];

// 						cv::Mat _kPatch;
// 						Image[i](cv::Rect(k* PatchSize, j* PatchSize, PatchSize, PatchSize)).copyTo(_kPatch );
						
// 						cv::Mat kPatch = _kPatch.reshape(1, 1);

// 						for (int l = 0; l < PatchSize * PatchSize; l++)
// 						{
// 							Data_of_Band[l] = kPatch.at<float>(0, l);

// 						}
// 						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, PatchSize, PatchSize, Data_of_Band,
// 							PatchSize, PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band

// 						delete[]Data_of_Band;
// 						_kPatch.release();
// 						kPatch.release();
// 					}
// 					else if (j != HLops - 1 && k == WLops - 1)
// 					{
// 						float* Data_of_Band = new float[PatchSize * (Width - k * PatchSize)];

// 						cv::Mat _kPatch;
// 						Image[i](cv::Rect(k* PatchSize, j* PatchSize, (Width - k * PatchSize), PatchSize)).copyTo(_kPatch);

// 						cv::Mat kPatch = _kPatch.reshape(1, 1);
// 						for (int l = 0; l < PatchSize * (Width - k * PatchSize); l++)
// 						{
// 							Data_of_Band[l] = kPatch.at<float>(0, l);

// 						}

// 						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, (Width - k * PatchSize), PatchSize, Data_of_Band,
// 							(Width - k * PatchSize), PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band

// 						delete[]Data_of_Band;
// 						_kPatch.release();
// 						kPatch.release();
// 					}
// 					else if (j == HLops - 1 && k != WLops - 1)
// 					{
// 						float* Data_of_Band = new float[(Height - j * PatchSize) * PatchSize];

// 						cv::Mat _kPatch;
// 						Image[i](cv::Rect(k* PatchSize, j* PatchSize, PatchSize, Height - j * PatchSize)).copyTo(_kPatch);
// 						cv::Mat kPatch = _kPatch.reshape(1, 1);

// 						for (int l = 0; l < (Height - j * PatchSize) * PatchSize; l++)
// 						{
// 							Data_of_Band[l] = kPatch.at<float>(0, l);

// 						}

// 						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, PatchSize, Height - j * PatchSize, Data_of_Band,
// 							PatchSize, Height - j * PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band

// 						delete[]Data_of_Band;
// 						_kPatch.release();
// 						kPatch.release();
// 					}
// 					else
// 					{
// 						float* Data_of_Band = new float[(Height - j * PatchSize) * (Width - k * PatchSize)];

// 						cv::Mat _kPatch;
// 						Image[i](cv::Rect(k* PatchSize, j* PatchSize, Width - k * PatchSize, Height - j * PatchSize)).copyTo(_kPatch);

// 						cv::Mat kPatch = _kPatch.reshape(1, 1);

// 						for (int l = 0; l < (Height - j * PatchSize) * (Width - k * PatchSize); l++)
// 						{
// 							Data_of_Band[l] = kPatch.at<float>(0, l);

// 						}

// 						pBand->RasterIO(GF_Write, k * PatchSize, j * PatchSize, Width - k * PatchSize, Height - j * PatchSize, Data_of_Band,
// 							Width - k * PatchSize, Height - j * PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band

// 						delete[]Data_of_Band;
// 						_kPatch.release();
// 						kPatch.release();
// 					}
// 				}
// 			}


// 		}
// 	}
// 	else
// 	{
// 		for (int i = 0; i < BandSize; i++)
// 		{
// 			GDALRasterBand* pBand = ImageData->GetRasterBand(i + 1);
// 			float* Data_of_Band = new float[Height * Width];

// 			cv::Mat strechimage = Image[i].reshape(1, 1);

// 			for (int j = 0; j < Height * Width; j++)
// 			{
// 				Data_of_Band[j] = strechimage.at<float>(0, j);

// 			}
// 			//�½��ĸ�ʽΪGDT_Float32��һ��Ҫ��Ӧ
// 			pBand->RasterIO(GF_Write, 0, 0, Width, Height, Data_of_Band, Width, Height, GDT_Float32, 0, 0);
// 			delete[]Data_of_Band;

// 		}
// 	}




	
// 	delete[]Projection;

// 	//std::cout << "����Ӱ��ɹ�!" << std::endl;
// 	GDALClose(ImageData);
// }


double BasicFunction::CalEuDistance2D(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


//���ݶ���ʽ�仯����������λ��
cv::Point2f BasicFunction::PolynomialTransform(float x, float y, cv::Mat PolynomialParams)
{
	cv::Point2f Output;
	Output.x = PolynomialParams.at<float>(0, 0) + PolynomialParams.at<float>(1, 0) * x + PolynomialParams.at<float>(2, 0) * y +
		PolynomialParams.at<float>(3, 0) * x * x + PolynomialParams.at<float>(4, 0) * x * y + PolynomialParams.at<float>(5, 0) * y * y;
	Output.y = PolynomialParams.at<float>(6, 0) + PolynomialParams.at<float>(7, 0) * x + PolynomialParams.at<float>(8, 0) * y +
		PolynomialParams.at<float>(9, 0) * x * x + PolynomialParams.at<float>(10, 0) * x * y + PolynomialParams.at<float>(11, 0) * y * y;
	return Output;
}
//���ض���ʽУ���ı߽�
DEMBoundary BasicFunction::GetBoundaryFromPolynomialParams(cv::Size ImageSize, cv::Mat PolynomialParams)
{
	Boundary ImageBoundary;

	cv::Point2f tmp;
	tmp = PolynomialTransform(0, 0, PolynomialParams);
	ImageBoundary.TopLeftLongitude = tmp.x;
	ImageBoundary.TopLeftLatitude = tmp.y;

	tmp = PolynomialTransform(float(ImageSize.width), 0, PolynomialParams);
	ImageBoundary.TopRightLongitude = tmp.x;
	ImageBoundary.TopRightLatitude = tmp.y;

	tmp = PolynomialTransform(0, float(ImageSize.height), PolynomialParams);
	ImageBoundary.BottomLeftLongitude = tmp.x;
	ImageBoundary.BottomLeftLatitude = tmp.y;

	tmp = PolynomialTransform(float(ImageSize.width), float(ImageSize.height), PolynomialParams);
	ImageBoundary.BottomRightLongitude = tmp.x;
	ImageBoundary.BottomRightLatitude = tmp.y;

	return BasicFunction::GetDEMBoundary(ImageBoundary);
}
//д��Ϊָ����ʽ���ļ�������jpeg2000
void BasicFunction::SaveImage(std::vector<cv::Mat> Image, std::string Format, std::string SaveFilePath, char* Proj, double* GeoTransform)
{
	const int BandSize = Image.size();
	const int Height = Image[0].rows;
	const int Width = Image[0].cols;

	//GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName(Format.c_str());

	GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName(Format.c_str());
	GDALDataset* ImageData;
	//�½��ĸ�ʽΪGDT_Float32��һ��Ҫ��Ӧ
	ImageData = poDriver->Create(SaveFilePath.data(), Width, Height, BandSize, GDT_Float32, NULL);

	const char* Projection = Proj;

	if (GeoTransform != nullptr)
	{
		ImageData->SetGeoTransform(GeoTransform);
	}
	if (Projection != nullptr)
	{
		ImageData->SetProjection(Projection);
	}

	for (int i = 0; i < BandSize; i++)
	{
		GDALRasterBand* poBand = ImageData->GetRasterBand(i + 1);
		float* Banddata = new float[Height * Width];

		cv::Mat strechimage = Image[i].reshape(1, 1);

		for (int j = 0; j < Height * Width; j++)
		{
			Banddata[j] = strechimage.at<float>(0, j);

		}
		//�½��ĸ�ʽΪGDT_Float32��һ��Ҫ��Ӧ
		poBand->RasterIO(GF_Write, 0, 0, Width, Height, Banddata, Width, Height, GDT_Float32, 0, 0);
		delete[]Banddata;

	}

	delete[]Projection;

	//std::cout << "����Ӱ��ɹ�!" << std::endl;
	GDALClose(ImageData);
}

void BasicFunction::SaveImageASOtherFormat(std::vector<cv::Mat> Image, std::string Format, std::string SaveFilePath, char* Proj, double* GeoTransform)
{
	GDALAllRegister();
	const int BandSize = Image.size();
	const int Height = Image[0].rows;
	const int Width = Image[0].cols;

	GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName("MEM");
	GDALDataset* ImageData;
	//�½��ĸ�ʽΪGDT_Float32��һ��Ҫ��Ӧ
	ImageData = poDriver->Create("", Width, Height, BandSize, GDT_Int16, NULL);

	const char* Projection = Proj;
	if (GeoTransform != nullptr)
	{
		ImageData->SetGeoTransform(GeoTransform);
	}
	if (Projection != nullptr)
	{
		ImageData->SetProjection(Projection);
	}
	for (int i = 0; i < BandSize; i++)
	{
		GDALRasterBand* poBand = ImageData->GetRasterBand(i + 1);
		int* Banddata = new int[Height * Width];

		cv::Mat strechimage = Image[i].reshape(1, 1);

		for (int j = 0; j < Height * Width; j++)
		{
			Banddata[j] = strechimage.at<float>(0, j);

		}
		//�½��ĸ�ʽΪGDT_Float32��һ��Ҫ��Ӧ
		poBand->RasterIO(GF_Write, 0, 0, Width, Height, Banddata, Width, Height, GDT_Int16, 0, 0);
		delete[]Banddata;

	}
	GDALDriver* poDriverJP2 = GetGDALDriverManager()->GetDriverByName(Format.c_str());
	if (poDriverJP2 != nullptr)
	{
		poDriverJP2->CreateCopy(SaveFilePath.data(), ImageData, TRUE, 0, 0, 0);
	}
	else
	{
		std::cout << "û�����ʽ��!" << std::endl;
	}
	//delete[]Projection;
	//GDALClose(ImageData);
	//delete[]Projection;

	//GDALClose(ImageData);
}
//GDAL��ʽתCV::Mat
bool BasicFunction::GDAL2Mat(GDALDataset* InputImageData, std::vector<cv::Mat>& OutputImage, char* Proj, double* GeoTransform)
{
	//��ȡͶӰת��
	const char* const_prj = InputImageData->GetProjectionRef();
	string tmp(const_prj);
	//ת��һ��
	ConstChar2Char(const_prj, Proj);


	//std::cout << Proj << std::endl;
	int Width = InputImageData->GetRasterXSize(); // �� 
	int Height = InputImageData->GetRasterYSize(); // �� 
	int BandSize = InputImageData->GetRasterCount();//������ 

	double* adfGeoTransform = new double[6];
	InputImageData->GetGeoTransform(adfGeoTransform);

	GeoTransform = adfGeoTransform;
	for (int i = 0; i < 6; i++)
	{
		std::cout << GeoTransform[i] << std::endl;
	}

	std::vector <cv::Mat>Image;  // ����Ԫ��ΪMat��vecoter������������ÿһ��Ԫ�ش洢һ�����ε�����

	int PatchSize = 1000;


	if (Width > 10 * PatchSize && Height > 10 * PatchSize)
	{
		int WLops = Width / PatchSize;
		int HLops = Height / PatchSize;
		//�պô�����ʱ�򣬲���1
		if (float(Width) / float(PatchSize) == Width / PatchSize)
		{
			WLops = WLops - 1;
		}
		if (float(Height) / float(PatchSize) == Height / PatchSize)
		{
			HLops = HLops - 1;
		}
		for (int i = 0; i < BandSize; i++)
		{
			GDALRasterBand* pBand = InputImageData->GetRasterBand(i + 1);//��ȡ��i+1�����ε�����
			
			GDALDataType DataType = pBand->GetRasterDataType();

			cv::Mat Band_Image = cv::Mat(Height, Width, CV_32FC1);//����i+1�����ε����ݴ����A��

			for (int j = 0; j < HLops; j++)
			{
				for (int k = 0; k < WLops; k++)
				{
					if (j != HLops - 1 && k != WLops - 1)
					{
						float* Data_of_Band = new float[PatchSize * PatchSize];

						pBand->RasterIO(GF_Read, k * PatchSize, j * PatchSize, PatchSize, PatchSize, Data_of_Band,
							PatchSize, PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band

						
						cv::Mat kPatch(PatchSize, PatchSize, CV_32FC1, Data_of_Band);
						kPatch.copyTo(Band_Image(cv::Rect(k * PatchSize, j * PatchSize, PatchSize, PatchSize)));

						delete[]Data_of_Band;
					}
					else if (j != HLops - 1 && k == WLops - 1)
					{
						float* Data_of_Band = new float[PatchSize * (Width - k * PatchSize)];

						pBand->RasterIO(GF_Read, k * PatchSize, j * PatchSize, (Width - k * PatchSize), PatchSize, Data_of_Band,
							(Width - k * PatchSize), PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band
						cv::Mat kPatch(PatchSize, (Width - k * PatchSize), CV_32FC1, Data_of_Band);
						kPatch.copyTo(Band_Image(cv::Rect(k * PatchSize, j * PatchSize, (Width - k * PatchSize), PatchSize)));

						delete[]Data_of_Band;
					}
					else if (j == HLops - 1 && k != WLops - 1)
					{
						float* Data_of_Band = new float[(Height - j * PatchSize) * PatchSize];

						pBand->RasterIO(GF_Read, k * PatchSize, j * PatchSize, PatchSize, Height - j * PatchSize, Data_of_Band,
							PatchSize, Height - j * PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band
						cv::Mat kPatch(Height - j * PatchSize, PatchSize, CV_32FC1, Data_of_Band);
						kPatch.copyTo(Band_Image(cv::Rect(k * PatchSize, j * PatchSize, PatchSize, Height - j * PatchSize)));

						delete[]Data_of_Band;
					}
					else
					{
						float* Data_of_Band = new float[(Height - j * PatchSize) * (Width - k * PatchSize)];

						pBand->RasterIO(GF_Read, k * PatchSize, j * PatchSize, Width - k * PatchSize, Height - j * PatchSize, Data_of_Band,
							Width - k * PatchSize, Height - j * PatchSize, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���Data_of_Band
						cv::Mat kPatch(Height - j * PatchSize, Width - k * PatchSize, CV_32FC1, Data_of_Band);
						kPatch.copyTo(Band_Image(cv::Rect(k * PatchSize, j * PatchSize, Width - k * PatchSize, Height - j * PatchSize)));

						delete[]Data_of_Band;
					}
				}
			}

			Image.push_back(Band_Image.clone());
			if (i == BandSize - 1)
			{
				delete pBand;
			}
			Band_Image.release();
		}
	}
	else
	{
		for (int i = 0; i < BandSize; i++)
		{
			float* Data_of_Band = new float[Width * Height];

			GDALRasterBand* pBand = InputImageData->GetRasterBand(i + 1);//��ȡ��i+1�����ε�����
			GDALDataType DataType = pBand->GetRasterDataType();

			pBand->RasterIO(GF_Read, 0, 0, Width, Height, Data_of_Band,
				Width, Height, GDT_Float32, 0, 0);//����i+1�����ε����ݴ���pafScan
			cv::Mat Band_Image = cv::Mat(Height, Width, CV_32FC1, Data_of_Band);//����i+1�����ε����ݴ����A��
			Image.push_back(Band_Image.clone());

			if (i == BandSize - 1)
			{
				delete pBand;
			}
			delete[]Data_of_Band;
			Band_Image.release();
		}
	}
	OutputImage = Image;
	// GDALClose((GDALDatasetH)ImageData);
	return true;
}
//const char *תchar *
void BasicFunction::ConstChar2Char(const char* Input, char* Output)
{
	/*string tmp(Input);
	Output = new char(tmp.length());
	strcpy(Output, tmp.c_str());
	std::cout << tmp << endl;
	cout << Output << endl;*/
	char* str = nullptr;
	str = const_cast<char*>(Input);
	int length = std::strlen(Input);
	for (int i = 0; i < length; i++) 
	{
		char itmp = str[i];
		Output[i] = itmp;
	}
}
//��ȡxml�ļ�
bool BasicFunction::LoadXmlFile(std::string XmlFilePath,GF2Metadata & MetaData)
{


	tinyxml2::XMLDocument XmlFile;
	if (XmlFile.LoadFile(XmlFilePath.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "��xml�ļ�ʧ�ܣ������ļ�Ŀ¼!" << std::endl;
		return false;
	}
	
	//��ȡ���ڵ�
	tinyxml2::XMLElement* rootElement = XmlFile.RootElement();
	const char* tMetadata;
	//������
	if (rootElement->FirstChildElement("Bands")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("Bands")->GetText();
		MetaData.Bands = atoi(tMetadata);
	}
	else
	{
		std::cout << "��ȡ������ʧ��!" << std::endl;
	}
	//���½�γ��
	if (rootElement->FirstChildElement("BottomLeftLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomLeftLatitude")->GetText();
		MetaData.BottomLeftLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���½�γ��ʧ��!" << std::endl;
	}
	
	//���½Ǿ���
	if (rootElement->FirstChildElement("BottomLeftLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomLeftLongitude")->GetText();
		MetaData.BottomLeftLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���½Ǿ���ʧ��!" << std::endl;
	}
	
	//���½�γ��
	if (rootElement->FirstChildElement("BottomRightLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomRightLatitude")->GetText();
		MetaData.BottomRightLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���½�γ��ʧ��!" << std::endl;
	}
	
	//���½Ǿ���
	if (rootElement->FirstChildElement("BottomRightLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("BottomRightLongitude")->GetText();
		MetaData.BottomRightLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���½Ǿ���ʧ��!" << std::endl;
	}

	
	//������
	if (rootElement->FirstChildElement("EarthEllipsoid")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("EarthEllipsoid")->GetText();
		MetaData.EarthEllipsoid = tMetadata;
	}
	else
	{
		std::cout << "��ȡ������ʧ��!" << std::endl;
	}
	
	//����ֱ���
	if (rootElement->FirstChildElement("ImageGSD")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("ImageGSD")->GetText();
		MetaData.ImageGSD = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ����ֱ���ʧ��!" << std::endl;
	}
	
	//�ȼ�
	if (rootElement->FirstChildElement("IntegrationLevel")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("IntegrationLevel")->GetText();
		MetaData.IntegrationLevel = tMetadata;
	}
	else
	{
		std::cout << "��ȡIntegrationLevelʧ��!" << std::endl;
	}
	
	//ʱ��
	if (rootElement->FirstChildElement("IntegrationTime")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("IntegrationTime")->GetText();
		MetaData.IntegrationTime = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡIntegrationTimeʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("MtfCorrection")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("MtfCorrection")->GetText();
		MetaData.MtfCorrection = tMetadata;
	}
	else
	{
		std::cout << "��ȡMtfCorrectionʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("PitchSatelliteAngle")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("PitchSatelliteAngle")->GetText();
		MetaData.PitchSatelliteAngle = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡPitchSatelliteAngleʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("PitchViewingAngle")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("PitchViewingAngle")->GetText();
		MetaData.PitchViewingAngle = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡPitchViewingAngleʧ��!" << std::endl;
	}
	
	//��ʽ
	if (rootElement->FirstChildElement("ProductFormat")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("ProductFormat")->GetText();
		MetaData.ProductFormat = tMetadata;
	}
	else
	{
		std::cout << "��ȡProductFormatʧ��!" << std::endl;
	}

	
	//����ʱ��
	if (rootElement->FirstChildElement("ReceiveTime")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("ReceiveTime")->GetText();
		MetaData.ReceiveTime = tMetadata;
	}
	else
	{
		std::cout << "��ȡReceiveTimeʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("RollSatelliteAngle")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("RollSatelliteAngle")->GetText();
		MetaData.RollSatelliteAngle = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡRollSatelliteAngleʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("RollViewingAngle")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("RollViewingAngle")->GetText();
		MetaData.RollViewingAngle = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡRollViewingAngleʧ��!" << std::endl;
	}

	
	//
	if (rootElement->FirstChildElement("SatelliteAzimuth")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("SatelliteAzimuth")->GetText();
		MetaData.SatelliteAzimuth = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡSatelliteAzimuthʧ��!" << std::endl;
	}
	
	//����ID
	if (rootElement->FirstChildElement("SatelliteID")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("SatelliteID")->GetText();
		MetaData.SatelliteID = tMetadata;
	}
	else
	{
		std::cout << "��ȡ����IDʧ��!" << std::endl;
	}

	//
	if (rootElement->FirstChildElement("SatelliteZenith")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("SatelliteZenith")->GetText();
		MetaData.SatelliteZenith = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡSatelliteZenithʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("SensorID")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("SensorID")->GetText();
		MetaData.SensorID = tMetadata;
	}
	else
	{
		std::cout << "��ȡSensorIDʧ��!" << std::endl;
	}

	//
	if (rootElement->FirstChildElement("SolarAzimuth")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("SolarAzimuth")->GetText();
		MetaData.SolarAzimuth = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡSolarAzimuthʧ��!" << std::endl;
	}
	
	//
	if (rootElement->FirstChildElement("SolarZenith")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("SolarZenith")->GetText();
		MetaData.SolarZenith = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡSolarZenithʧ��!" << std::endl;
	}
	
	//���Ͻ�γ��
	if (rootElement->FirstChildElement("TopLeftLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopLeftLatitude")->GetText();
		MetaData.TopLeftLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���Ͻ�γ��ʧ��!" << std::endl;
	}
	
	//���ϽǾ���
	if (rootElement->FirstChildElement("TopLeftLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopLeftLongitude")->GetText();
		MetaData.TopLeftLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��!" << std::endl;
	}
	
	//���Ͻ�γ��
	if (rootElement->FirstChildElement("TopRightLatitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopRightLatitude")->GetText();
		MetaData.TopRightLatitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���Ͻ�γ��ʧ��!" << std::endl;
	}
	
	//���ϽǾ���
	if (rootElement->FirstChildElement("TopRightLongitude")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("TopRightLongitude")->GetText();
		MetaData.TopRightLongitude = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡ���ϽǾ���ʧ��!" << std::endl;
	}

	
	//
	if (rootElement->FirstChildElement("YawSatelliteAngle")->GetText() != NULL)
	{
		tMetadata = rootElement->FirstChildElement("YawSatelliteAngle")->GetText();
		MetaData.YawSatelliteAngle = atof(tMetadata);
	}
	else
	{
		std::cout << "��ȡYawSatelliteAngleʧ��!" << std::endl;
	}
	
	return 1;
}
//��Ԫ�����л�ȡӰ��߽�
Boundary BasicFunction::GetBoundaryFromMetadata(GF2Metadata Metadata)
{
	Boundary OutputBoundary;
	OutputBoundary.BottomLeftLatitude = Metadata.BottomLeftLatitude;
	OutputBoundary.BottomLeftLongitude = Metadata.BottomLeftLongitude;
	OutputBoundary.BottomRightLatitude = Metadata.BottomRightLatitude;
	OutputBoundary.BottomRightLongitude = Metadata.BottomRightLongitude;
	OutputBoundary.TopLeftLatitude = Metadata.TopLeftLatitude;
	OutputBoundary.TopLeftLongitude = Metadata.TopLeftLongitude;
	OutputBoundary.TopRightLatitude = Metadata.TopRightLatitude;
	OutputBoundary.TopRightLongitude = Metadata.TopRightLongitude;
	return OutputBoundary;
}
//��GeotransformParams��ȡ�߽�
Boundary BasicFunction::GetBoundaryFromGeotransformParams(double* GeotransformParams,cv::Size ImageSize)
{
	Boundary OutputBoundary;
	OutputBoundary.BottomLeftLatitude = GeotransformParams[3] + (0.5) * GeotransformParams[4] + (ImageSize.height - 0.5) * GeotransformParams[5];
	OutputBoundary.BottomLeftLongitude = GeotransformParams[0] + (0.5) * GeotransformParams[1] + (ImageSize.height - 0.5) * GeotransformParams[2];

	OutputBoundary.BottomRightLatitude = GeotransformParams[3] + (ImageSize.width - 0.5) * GeotransformParams[4] + (ImageSize.height - 0.5) * GeotransformParams[5];
	OutputBoundary.BottomRightLongitude = GeotransformParams[0] + (ImageSize.width - 0.5) * GeotransformParams[1] + (ImageSize.height - 0.5) * GeotransformParams[2];

	OutputBoundary.TopLeftLatitude = GeotransformParams[3] + (0.5) * GeotransformParams[4] + (0.5) * GeotransformParams[5];
	OutputBoundary.TopLeftLongitude = GeotransformParams[0] + (0.5) * GeotransformParams[1] + (0.5) * GeotransformParams[2];

	OutputBoundary.TopRightLatitude = GeotransformParams[3] + (ImageSize.width - 0.5) * GeotransformParams[4] + (0.5) * GeotransformParams[5];
	OutputBoundary.TopRightLongitude = GeotransformParams[0] + (ImageSize.width - 0.5) * GeotransformParams[1] + (0.5) * GeotransformParams[2];
	return OutputBoundary;
}
std::string BasicFunction::GetXmlFilePath(std::string ImageFilePath)
{
	//����xml�ļ���·��
	std::string sxmlPath;
	sxmlPath.assign(ImageFilePath.begin(), (--ImageFilePath.end() - 4));
	sxmlPath = sxmlPath + ".xml";
	return sxmlPath;
}

//ֱ��ͼƥ��--------------------------------------------------------------------------------------
//Ѱ��vector��Сֵλ��
int BasicFunction::GetMinNumIndex(vector<float> data)
{
	float minnum(99999999);
	int index(0);
	for (int i(0); i < data.size(); ++i)
	{
		if (data[i] < minnum)
		{
			minnum = data[i];
			index = i;
		}
	}
	return index;
}

//cv::Mat BasicFunction::CHistMatch(cv::Mat img1, cv::Mat img2, int code)
//{
//	/// @brief img2��img1����ͨ��
//	/// @param img1 ��һ��Ӱ��
//	/// @param img2 �ڶ���Ӱ��
//	/// @param code ��������----8(bit),12(bit),16(bit)
//	/// @return 
//	cv::Mat mimg1 = img1.clone();
//	cv::Mat mimg2 = img2.clone();
//	//�任��������
//	mimg1.convertTo(mimg1, CV_32FC1);
//	mimg2.convertTo(mimg2, CV_32FC1);
//	//����
//	mimg1 = mimg1.reshape(1, mimg1.rows * mimg1.cols);
//	mimg2 = mimg2.reshape(1, mimg2.rows * mimg2.cols);
//	//�Ҷȼ�
//	int length(1);
//	for (size_t i = 0; i < code; i++)
//	{
//		length *= 2;
//	}
//	//�Ҷ�ֱ��ͼ
//	std::vector<float> hist1(length), hist2(length);
//	long long int fucklaijisit = mimg1.rows;
//	for (long long int i = 0; i < fucklaijisit; i++)
//	{
//		int num1 = (int)mimg1.at<float>(i, 0);
//		if (num1 < 0)
//			num1 = 0;
//		if (num1 >= length)
//			num1 = length - 1;
//		int num2 = (int)mimg2.at<float>(i, 0);
//		if (num2 < 0)
//			num2 = 0;
//		if (num2 >= length)
//			num2 = length - 1;
//		hist1[num1] ++;
//		hist2[num2] ++;
//	}
//	for (size_t i = 0; i < length; i++)
//	{
//		hist1[i] /= mimg1.rows;
//		hist2[i] /= mimg2.rows;
//		//std::cout << hist1[i] << "  " << hist2[i] << std::endl;
//	}
//	//�ۼƻҶ�ֱ��ͼ
//	std::vector<float> count_hist1 = hist1;
//	std::vector<float> count_hist2 = hist2;
//	for (size_t i = 1; i < count_hist1.size(); i++)
//	{
//		count_hist1[i] = count_hist1[i - 1] + count_hist1[i];
//	}
//	for (size_t i = 1; i < count_hist2.size(); i++)
//	{
//		count_hist2[i] = count_hist2[i - 1] + count_hist2[i];
//	}
//	//����ӳ��
//	vector<int> nindex;
//	for (int i(0); i < count_hist2.size(); ++i)
//	{
//		float num = count_hist2[i];
//		vector<float> absnum(count_hist1.size());
//		for (int j(0); j < count_hist1.size(); ++j)
//		{
//			absnum[j] = abs(count_hist1[j] - count_hist2[i]);
//		}
//		int index = GetMinNumIndex(absnum);
//		nindex.push_back(index);
//	}
//	//vector<int> nindex;
//	//for (int i(0); i < count_hist2.size(); ++i)
//	//{
//	//	float num = count_hist2[i];
//	//	int index(0);
//	//	for (int j(0); j < count_hist1.size()-1; ++j)
//	//	{
//	//		//����ֵ
//	//		float num1 = count_hist1[j];
//	//		float num2 = count_hist2[j + 1];
//	//		if (num <= num1)
//	//		{
//	//			index = j;
//	//		}
//	//		else if (num1 < num && num < num2)
//	//		{
//	//			float dert1 = abs(num-num1);
//	//			float dert2 = abs(num-num2);
//	//			index = dert1 > dert2 ? j + 1 : j;
//	//		}
//	//		else if (num >= num2)
//	//		{
//	//			index = j + 1;
//	//		}
//	//	}
//	//	nindex.push_back(index);
//	//}
//	//��ʼӳ��
//	for (long long int i = 0; i < fucklaijisit; i++)
//	{
//		int num = (int)mimg2.at<float>(i, 0);
//		if (num < 0)
//			num = 0;
//		if (num >= length)
//			num = length - 1;
//		mimg2.at<float>(i, 0) = nindex[num];
//	}
//	cv::Mat nimg2 = img2.clone();
//	mimg2.reshape(1, img2.rows).convertTo(nimg2, img2.type());
//	return nimg2;
//}

cv::Mat BasicFunction::CHistMatch(const cv::Mat img1, const cv::Mat img2)
{
	/// @brief img2��img1����ͨ��
	/// @param img1 ��һ��Ӱ��
	/// @param img2 �ڶ���Ӱ��
	/// @return 
	cv::Mat mimg1 = img1.clone();
	cv::Mat mimg2 = img2.clone();
	//�任��������
	mimg1.convertTo(mimg1, CV_32FC1);
	mimg2.convertTo(mimg2, CV_32FC1);
	//����
	mimg1 = mimg1.reshape(1, mimg1.rows * mimg1.cols);
	mimg2 = mimg2.reshape(1, mimg2.rows * mimg2.cols);
	//���򲢼������
	vector<FloatSort> mmimg1(mimg1.rows), mmimg2(mimg2.rows);
	for (size_t i = 0; i < mmimg1.size(); i++)
	{
		mmimg1[i].index = i;
		mmimg1[i].value = mimg1.at<float>(i, 0);
		mmimg2[i].index = i;
		mmimg2[i].value = mimg2.at<float>(i, 0);
	}
	sort(mmimg1.begin(), mmimg1.end(), compare);
	sort(mmimg2.begin(), mmimg2.end(), compare);
	//��������������ӳ��
	for (size_t i = 0; i < mmimg1.size(); i++)
	{
		float num1 = mmimg1[i].value;
		float num2 = mmimg2[i].value;
		if (num1 != num2)
		{
			mimg2.at<float>(mmimg2[i].index, 0) = num1;
		}
	}
	//�任������
	cv::Mat nimg2 = cv::Mat(img2.rows, img2.cols, img2.type());
	mimg2.reshape(1, img2.rows).convertTo(nimg2, img2.type());
	return nimg2;
}

bool BasicFunction::compare(FloatSort a, FloatSort b)
{
	return a.value < b.value;
}

//��ӳ������һ��ֱ��ͼ��һ��
//int length = mmimg1[mmimg1.size() - 1].value >= mmimg2[mmimg2.size() - 1].value ? mmimg1[mmimg1.size() - 1].value : mmimg2[mmimg2.size() - 1].value;
//std::vector<float> hist1(length), hist2(length);
//long long int fucklaijisit = mimg1.rows;
//for (long long int i = 0; i < fucklaijisit; i++)
//{
//	int num1 = (int)mimg1.at<float>(i, 0);
//	if (num1 < 0)
//		num1 = 0;
//	if (num1 >= length)
//		num1 = length - 1;
//	int num2 = (int)mimg2.at<float>(i, 0);
//	if (num2 < 0)
//		num2 = 0;
//	if (num2 >= length)
//		num2 = length - 1;
//	hist1[num1] ++;
//	hist2[num2] ++;
//}
////����
//ofstream fout1("testline1.txt");
//for (size_t i = 0; i < hist1.size(); i++)
//{
//	fout1 << hist1[i] << std::endl;
//}
//fout1.close();
//ofstream fout2("testline2.txt");
//for (size_t i = 0; i < hist2.size(); i++)
//{
//	fout2 << hist2[i] << std::endl;
//}
//fout2.close();

//template <typename T>
//vector<T> sort_indexes(vector<T>& v)
//{
//	vector<T> idx(v.size());
//	iota(idx.begin(), idx.end(), 0);
//	sort(idx.begin(), idx.end(),
//		[&v](T i1, T i2) {return v[i1] < v[i2]; });
//	return idx;
//}


cv::Mat BasicFunction::LinearStrech(cv::Mat img, float ratio, int code, int dtype)
{
	cv::Mat mimg = img.clone();
	mimg.convertTo(mimg, CV_32FC1);
	cv::Mat nimg = mimg.clone();
	int counts = img.rows * img.cols;
	mimg = mimg.reshape(1, counts);
	cv::sort(mimg, mimg, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
	float cutmin = mimg.at<float>(int(counts * ratio), 0);
	float cutmax = mimg.at<float>(int(counts * (1 - ratio)) - 1, 0);
	int num(1);
	for (size_t i = 0; i < code; i++)
	{
		num *= 2;
	}
	nimg.setTo(cutmin, nimg < cutmin);
	nimg.setTo(cutmax, nimg > cutmax);
	nimg = (num - 1) * (nimg - cutmin) / (cutmax - cutmin);
	nimg.convertTo(nimg, dtype);
	return nimg;
}

cv::Point3f BasicFunction::WGS842Proj(int des_code, double lon, double lat,double H)
{
	std::cout<<"call WGS842Proj"<<std::endl;
	int src_code = 4326;
	std::cout<<"lon\t"<<lon<<"\tlat\t"<<lat<<std::endl;
	//ת��-----------------------
	OGRSpatialReference source_geo, des_geo;
	OGRCoordinateTransformation* source2des;
	std::cout<<"des_code\t"<<des_code<<std::endl;
	source_geo.importFromEPSG(src_code);
	des_geo.importFromEPSG(des_code);
	char* src_coor = NULL;
	source_geo.exportToWkt(&src_coor);
	char* des_coor = NULL;
	des_geo.exportToWkt(&des_coor);
	source2des = OGRCreateCoordinateTransformation(&source_geo, &des_geo);
	std::cout<<"src_code\t"<<src_code<<std::endl;
	double x = lon;
	double y = lat;
	std::cout<<"x\t"<<x<<"\ty\t"<<y<<std::endl;
	source2des->Transform(1, &x, &y);

	std::cout<<"okkkkk"<<std::endl;
	return cv::Point3f(x, y, H);
}



int BasicFunction::search_epsg_code(string datum, string proj_mode, double lon)
{
	int code;
	// std::vector<std::string> baga;
	// Stringsplit(mode, "_", baga);
	// std::string datum = baga[0];
	// std::string proj_mode = baga[1];
	if (datum == "WGS84" and proj_mode == "6")
	{
		// WGS84 -> UTM projection
		if (lon >= 132 && lon <= 138) { code = 32653; }
		if (lon >= 126 && lon <= 132) { code = 32652; }
		if (lon >= 120 && lon <= 126) { code = 32651; }
		if (lon >= 114 && lon <= 120) { code = 32650; }
		if (lon >= 108 && lon <= 114) { code = 32649; }
		if (lon >= 102 && lon <= 108) { code = 32648; }
		if (lon >= 96 && lon <= 102) { code = 32647; }
		if (lon >= 90 && lon <= 96) { code = 32646; }
		if (lon >= 84 && lon <= 90) { code = 32645; }
		if (lon >= 78 && lon <= 84) { code = 32644; }
		if (lon >= 72 && lon <= 78) { code = 32643; }
	}
	if (datum == "CGCS2000" and proj_mode == "6")
	{
		if (lon >= 132 && lon <= 138) { code = 32653; }
		if (lon >= 126 && lon <= 132) { code = 32652; }
		if (lon >= 120 && lon <= 126) { code = 32651; }
		if (lon >= 114 && lon <= 120) { code = 32650; }
		if (lon >= 108 && lon <= 114) { code = 32649; }
		if (lon >= 102 && lon <= 108) { code = 32648; }
		if (lon >= 96 && lon <= 102) { code = 32647; }
		if (lon >= 90 && lon <= 96) { code = 32646; }
		if (lon >= 84 && lon <= 90) { code = 32645; }
		if (lon >= 78 && lon <= 84) { code = 32644; }
		if (lon >= 72 && lon <= 78) { code = 32643; }
	}
	if (datum == "CGCS2000" and proj_mode == "3")
	{
		if (lon >= 133.5) { code = 4554; }
		if (lon >= 130.5 && lon <= 133.5) { code = 4553; }
		if (lon >= 127.5 && lon <= 130.5) { code = 4552; }
		if (lon >= 124.5 && lon <= 127.5) { code = 4551; }
		if (lon >= 121.5 && lon <= 124.5) { code = 4550; }
		if (lon >= 118.5 && lon <= 121.5) { code = 4549; }
		if (lon >= 115.5 && lon <= 118.5) { code = 4548; }
		if (lon >= 112.5 && lon <= 115.5) { code = 4547; }
		if (lon >= 109.5 && lon <= 112.5) { code = 4546; }
		if (lon >= 106.5 && lon <= 109.5) { code = 4545; }
		if (lon >= 103.5 && lon <= 106.5) { code = 4544; }
		if (lon >= 100.5 && lon <= 103.5) { code = 4543; }
		if (lon >= 97.5 && lon <= 100.5) { code = 4542; }
		if (lon >= 94.5 && lon <= 97.5) { code = 4541; }
		if (lon >= 91.5 && lon <= 94.5) { code = 4540; }
		if (lon >= 88.5 && lon <= 91.5) { code = 4539; }
		if (lon >= 85.5 && lon <= 88.5) { code = 4538; }
		if (lon >= 82.5 && lon <= 85.5) { code = 4537; }
		if (lon >= 79.5 && lon <= 82.5) { code = 4536; }
		if (lon >= 76.5 && lon <= 79.5) { code = 4535; }
		if (lon <= 76.5) { code = 4534; }
	}
	if (datum == "CGCS2000" and proj_mode == "6")
	{
		if (lon >= 132) { code = 4512; }
		if (lon >= 126 && lon <= 132) { code = 4511; }
		if (lon >= 120 && lon <= 126) { code = 4510; }
		if (lon >= 114 && lon <= 120) { code = 4509; }
		if (lon >= 108 && lon <= 114) { code = 4508; }
		if (lon >= 102 && lon <= 108) { code = 4507; }
		if (lon >= 96 && lon <= 102) { code = 4506; }
		if (lon >= 90 && lon <= 96) { code = 4505; }
		if (lon >= 84 && lon <= 90) { code = 4504; }
		if (lon >= 78 && lon <= 84) { code = 4503; }
		if (lon <= 78) { code = 4502; }
	}
	if (datum == "Xian1980" and proj_mode == "3")
	{
		if (lon >= 133.5) { code = 2390; }
		if (lon >= 130.5 && lon <= 133.5) { code = 2389; }
		if (lon >= 127.5 && lon <= 130.5) { code = 2388; }
		if (lon >= 124.5 && lon <= 127.5) { code = 2387; }
		if (lon >= 121.5 && lon <= 124.5) { code = 2386; }
		if (lon >= 118.5 && lon <= 121.5) { code = 2385; }
		if (lon >= 115.5 && lon <= 118.5) { code = 2384; }
		if (lon >= 112.5 && lon <= 115.5) { code = 2383; }
		if (lon >= 109.5 && lon <= 112.5) { code = 2382; }
		if (lon >= 106.5 && lon <= 109.5) { code = 2381; }
		if (lon >= 103.5 && lon <= 106.5) { code = 2380; }
		if (lon >= 100.5 && lon <= 103.5) { code = 2379; }
		if (lon >= 97.5 && lon <= 100.5) { code = 2378; }
		if (lon >= 94.5 && lon <= 97.5) { code = 2377; }
		if (lon >= 91.5 && lon <= 94.5) { code = 2376; }
		if (lon >= 88.5 && lon <= 91.5) { code = 2375; }
		if (lon >= 85.5 && lon <= 88.5) { code = 2374; }
		if (lon >= 82.5 && lon <= 85.5) { code = 2373; }
		if (lon >= 79.5 && lon <= 82.5) { code = 2372; }
		if (lon >= 76.5 && lon <= 79.5) { code = 2371; }
		if (lon <= 76.5) { code = 2370; }
	}
	if (datum == "Xian1980" and proj_mode == "6")
	{
		if (lon >= 132) { code = 2348; }
		if (lon >= 126 && lon <= 132) { code = 2347; }
		if (lon >= 120 && lon <= 126) { code = 2346; }
		if (lon >= 114 && lon <= 120) { code = 2345; }
		if (lon >= 108 && lon <= 114) { code = 2344; }
		if (lon >= 102 && lon <= 108) { code = 2343; }
		if (lon >= 96 && lon <= 102) { code = 2342; }
		if (lon >= 90 && lon <= 96) { code = 2341; }
		if (lon >= 84 && lon <= 90) { code = 2340; }
		if (lon >= 78 && lon <= 84) { code = 2339; }
		if (lon <= 78) { code = 2338; }
	}
	if (datum == "Beijing1954" and proj_mode == "3")
	{
		if (lon >= 133.5) { code = 2442; }
		if (lon >= 130.5 && lon <= 133.5) { code = 2441; }
		if (lon >= 127.5 && lon <= 130.5) { code = 2440; }
		if (lon >= 124.5 && lon <= 127.5) { code = 2439; }
		if (lon >= 121.5 && lon <= 124.5) { code = 2438; }
		if (lon >= 118.5 && lon <= 121.5) { code = 2437; }
		if (lon >= 115.5 && lon <= 118.5) { code = 2436; }
		if (lon >= 112.5 && lon <= 115.5) { code = 2435; }
		if (lon >= 109.5 && lon <= 112.5) { code = 2434; }
		if (lon >= 106.5 && lon <= 109.5) { code = 2433; }
		if (lon >= 103.5 && lon <= 106.5) { code = 2432; }
		if (lon >= 100.5 && lon <= 103.5) { code = 2431; }
		if (lon >= 97.5 && lon <= 100.5) { code = 2430; }
		if (lon >= 94.5 && lon <= 97.5) { code = 2429; }
		if (lon >= 91.5 && lon <= 94.5) { code = 2428; }
		if (lon >= 88.5 && lon <= 91.5) { code = 2427; }
		if (lon >= 85.5 && lon <= 88.5) { code = 2426; }
		if (lon >= 82.5 && lon <= 85.5) { code = 2425; }
		if (lon >= 79.5 && lon <= 82.5) { code = 2424; }
		if (lon >= 76.5 && lon <= 79.5) { code = 2423; }
		if (lon <= 76.5) { code = 2422; }
	}
	if (datum == "Beijing1954" and proj_mode == "6")
	{
		if (lon >= 132) { code = 21463; }
		if (lon >= 126 && lon <= 132) { code = 21462; }
		if (lon >= 120 && lon <= 126) { code = 21461; }
		if (lon >= 114 && lon <= 120) { code = 21460; }
		if (lon >= 108 && lon <= 114) { code = 21459; }
		if (lon >= 102 && lon <= 108) { code = 21458; }
		if (lon >= 96 && lon <= 102) { code = 21457; }
		if (lon >= 90 && lon <= 96) { code = 21456; }
		if (lon >= 84 && lon <= 90) { code = 21455; }
		if (lon >= 78 && lon <= 84) { code = 21454; }
		if (lon <= 78) { code = 21453; }
	}
	return code;
}

void BasicFunction::Stringsplit(const std::string& str, const std::string& splits, std::vector<std::string>& res)
{
	if (str == "")		return;
	//���ַ���ĩβҲ����ָ����������ȡ���һ��
	std::string strs = str + splits;
	size_t pos = strs.find(splits);
	int step = splits.size();
	res.clear();
	// ���Ҳ����������ַ��������������� npos
	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		res.push_back(temp);
		//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
		strs = strs.substr(pos + step, strs.size());
		pos = strs.find(splits);
	}
}

std::vector<cv::Mat> BasicFunction::GetSubPatch(std::string Img_path, cv::Point2d TLPoint, cv::Point2d BRPoint)
{
	// ��һ������ȡ����Ӱ��ķ���任����
	// 1����ȡӰ��
	GDALRPCInfo RPCParams_ref;
	GDALDataset* InputImageData = BasicFunction::ReadGTiffImage(Img_path, RPCParams_ref);
	// 2����ȡ����任����
	double* adfGeoTransform = new double[6];
	InputImageData->GetGeoTransform(adfGeoTransform);

	// �ڶ��������ݸ��������ϡ����½ǵ㣬������������Ӱ���ϵ��෽����
	// 1����ȡ����
	double TLP_x, TLP_y, BRP_x, BRP_y;
	TLP_x = TLPoint.x;
	TLP_y = TLPoint.y;
	BRP_x = BRPoint.x;
	BRP_y = BRPoint.y;

	// 2�����ݷ���任���������Ӧ�෽���꣬�Ӽ�1��Ϊ�˱�����int�Ĳ�������ʧ���
	int Pix_x_l, Pix_x_r, Pix_y_l, Pix_y_r;
	Pix_x_l = int((TLP_x - adfGeoTransform[0]) / adfGeoTransform[1]) - 1;
	Pix_x_r = int((BRP_x - adfGeoTransform[0]) / adfGeoTransform[1]) + 1;
	Pix_y_l = int((TLP_y - adfGeoTransform[3]) / adfGeoTransform[5]) - 1;
	Pix_y_r = int((BRP_y - adfGeoTransform[3]) / adfGeoTransform[5]) + 1;

	int xsize = Pix_x_r - Pix_x_l;
	int ysize = Pix_y_r - Pix_y_l;

	// �������������෽���������Ӱ���вü���Ӱ��
	int Width = InputImageData->GetRasterXSize(); // �� 
	int Height = InputImageData->GetRasterYSize(); // �� 
	int BandSize = InputImageData->GetRasterCount();//������

	std::vector<cv::Mat> sub_patch;
	for (int i = 0; i < BandSize; i++)
	{
		GDALRasterBand* pBand = InputImageData->GetRasterBand(i + 1);
		unsigned int* Data_of_Band = new unsigned int[xsize * ysize];
		pBand->RasterIO(GF_Read, Pix_x_l, Pix_y_l, xsize, ysize, Data_of_Band,
			xsize, ysize, GDT_Byte, 0, 0);//����i+1�����ε����ݴ���Data_of_Band
		cv::Mat sub_band(ysize, xsize, CV_8UC1, Data_of_Band);

		sub_patch.push_back(sub_band.clone());
		delete[] Data_of_Band;
		if (i == BandSize - 1)
		{
			delete pBand;
		}
		sub_band.release();
	}
	//������Ϣ
	cv::Mat xxxx = cv::Mat::zeros(ysize, xsize, CV_64FC1);
	cv::Mat yyyy = cv::Mat::zeros(ysize, xsize, CV_64FC1);
	for (size_t i = 0; i < ysize; i++)
	{
		for (size_t j = 0; j < xsize; j++)
		{
			xxxx.at<double>(i, j) = TLP_x + j * adfGeoTransform[1];
			yyyy.at<double>(i, j) = TLP_y + i * adfGeoTransform[5];
		}
	}
	sub_patch.push_back(xxxx);
	sub_patch.push_back(yyyy);
	return sub_patch;
}


std::vector<cv::Mat> BasicFunction::GetSubPatch(std::string Img_path, cv::Point2d TLPoint, int width, int height)
{
	// ��һ������ȡ����Ӱ��ķ���任����
	// 1����ȡӰ��
	GDALRPCInfo RPCParams_ref;
	GDALDataset* InputImageData = BasicFunction::ReadGTiffImage(Img_path, RPCParams_ref);
	// 2����ȡ����任����
	double* adfGeoTransform = new double[6];
	InputImageData->GetGeoTransform(adfGeoTransform);

	// �ڶ��������ݸ��������ϡ����½ǵ㣬������������Ӱ���ϵ��෽����
	// 1����ȡ����
	double TLP_x, TLP_y;
	TLP_x = TLPoint.x;
	TLP_y = TLPoint.y;

	// 2�����ݷ���任���������Ӧ�෽���꣬�Ӽ�1��Ϊ�˱�����int�Ĳ�������ʧ���
	int Pix_x_l, Pix_y_l;
	Pix_x_l = int((TLP_x - adfGeoTransform[0]) / adfGeoTransform[1]) - 1;
	Pix_y_l = int((TLP_y - adfGeoTransform[3]) / adfGeoTransform[5]) - 1;

	int xsize = width;
	int ysize = height;

	// �������������෽���������Ӱ���вü���Ӱ��
	int Width = InputImageData->GetRasterXSize(); // �� 
	int Height = InputImageData->GetRasterYSize(); // �� 
	int BandSize = InputImageData->GetRasterCount();//������

	std::vector<cv::Mat> sub_patch;
	for (int i = 0; i < BandSize; i++)
	{
		GDALRasterBand* pBand = InputImageData->GetRasterBand(i + 1);
		unsigned int* Data_of_Band = new unsigned int[xsize * ysize];
		pBand->RasterIO(GF_Read, Pix_x_l, Pix_y_l, xsize, ysize, Data_of_Band,
			xsize, ysize, GDT_Byte, 0, 0);//����i+1�����ε����ݴ���Data_of_Band
		cv::Mat sub_band(ysize, xsize, CV_8UC1, Data_of_Band);

		sub_patch.push_back(sub_band.clone());
		delete[] Data_of_Band;
		if (i == BandSize - 1)
		{
			delete pBand;
		}
		sub_band.release();
	}
	//������Ϣ
	cv::Mat xxxx = cv::Mat::zeros(ysize, xsize, CV_64FC1);
	cv::Mat yyyy = cv::Mat::zeros(ysize, xsize, CV_64FC1);
	for (size_t i = 0; i < ysize; i++)
	{
		for (size_t j = 0; j < xsize; j++)
		{
			xxxx.at<double>(i, j) = TLP_x + j * adfGeoTransform[1];
			yyyy.at<double>(i, j) = TLP_y + i * adfGeoTransform[5];
		}
	}
	sub_patch.push_back(xxxx);
	sub_patch.push_back(yyyy);
	return sub_patch;
}

std::string BasicFunction::GetBaseMapMode(std::string imgpath)
{
	char* Proj;
	double* GeoTransform;
	//��ʼ��GDAL��ע���
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	//��ȡӰ��
	GDALDataset* ImageData = (GDALDataset*)GDALOpen(imgpath.data(), GA_ReadOnly);
	//��ȡͶӰת��
	const char* const_prj = ImageData->GetProjectionRef();
	Proj = const_cast<char*>(const_prj);
	std::string tstr = (std::string)Proj;
	std::vector<std::string> linestrs;
	Stringsplit(tstr, "\"", linestrs);
	return linestrs[1];
}


int BasicFunction::readXML4Boundary(string xmlPath, vector<vector<double>> &CornerPoints )
{
    xmlDocPtr doc;           //��������ĵ�ָ��
    xmlNodePtr curNode;      //������ָ��(����Ҫ��Ϊ���ڸ��������ƶ�)
    xmlChar *szKey;          //��ʱ�ַ�������
    // char *szDocName="/home/wj/Downloads/ZY302/zy302a_bwd_016497_003126_20190520112310_01_sec_0001_1905228482.xml";
    char *szDocName=(char *)xmlPath.data();
    
    std::cout.precision(12);




    doc = xmlReadFile(szDocName,"GB2312",XML_PARSE_RECOVER); //�����ļ�
    //�������ĵ��Ƿ�ɹ���������ɹ���libxml��ָһ��ע��Ĵ���ֹͣ��
    //һ�����������ǲ��ʵ��ı��롣XML��׼�ĵ�������UTF-8��UTF-16�⻹�����������뱣�档
    //����ĵ���������libxml���Զ���Ϊ��ת����UTF-8���������XML������Ϣ������XML��׼��.
    if (NULL == doc)
    {  
       cout<<"Xml not parsed successfully\n";    
       return -1;
    }
    curNode = xmlDocGetRootElement(doc); //ȷ���ĵ���Ԫ��
    /*���ȷ�ϵ�ǰ�ĵ��а�������*/
    if (NULL == curNode)
    {
       cout<<"empty xml\n";
       xmlFreeDoc(doc);
       return -1;
    }
    /*����������У�������Ҫȷ���ĵ�����ȷ�����͡���root���������ʾ����ʹ���ĵ��ĸ����͡�*/
    if (xmlStrcmp(curNode->name, BAD_CAST "sensor_corrected_metadata"))
    {
       cout<<"Xml of the wrong type, root node != sensor_corrected_metadata";
       xmlFreeDoc(doc);
       return -1;
    }

   
 
    curNode = curNode->xmlChildrenNode;
    while (curNode != NULL) {
    if ((!xmlStrcmp(curNode->name, (const xmlChar *)"productInfo"))) {
        curNode = curNode->xmlChildrenNode;
        break;
    }
    curNode= curNode->next;
    }

    while (curNode != NULL) {
    if ((!xmlStrcmp(curNode->name, (const xmlChar *)"ProductGeographicRange"))) {
        curNode = curNode->xmlChildrenNode;
        break;
    }
    curNode= curNode->next;
    }

   
    CornerPoints.clear();
    vector<double> LonLat;
    
    while (curNode != NULL) 
    {
        if ((!xmlStrcmp(curNode->name, (const xmlChar *)"LeftTopPoint"))) 
        {
            cout<<curNode->name<<endl;
            xmlNodePtr PointNode=curNode->xmlChildrenNode;
            while (PointNode != NULL) {
            if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Longtitude"))) 
            {
                cout<<"\t"<<PointNode->name<<"\t";
                szKey = xmlNodeGetContent(PointNode);
                cout<<szKey<<endl;
                LonLat.push_back(stof((char*)szKey));

            }
            else if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Latitude")))
            {
                cout<<"\t"<<PointNode->name<<"\t";
                szKey = xmlNodeGetContent(PointNode);
                cout<<szKey<<endl;
                LonLat.push_back(stof((char*)szKey));
                CornerPoints.push_back(LonLat);
                LonLat.clear();
            }
            PointNode= PointNode->next;
            }
        }
        else if ((!xmlStrcmp(curNode->name, (const xmlChar *)"RightTopPoint"))) 
        {
            cout<<curNode->name<<endl;
            xmlNodePtr PointNode=curNode->xmlChildrenNode;
            while (PointNode != NULL) {
                if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Longtitude"))) 
                {
                    cout<<"\t"<<PointNode->name<<"\t";
                    szKey = xmlNodeGetContent(PointNode);
                    cout<<szKey<<endl;
                    LonLat.push_back(stof((char*)szKey));

                }
                else if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Latitude")))
                {
                    cout<<"\t"<<PointNode->name<<"\t";
                    szKey = xmlNodeGetContent(PointNode);
                    cout<<szKey<<endl;
                    LonLat.push_back(stof((char*)szKey));
                    CornerPoints.push_back(LonLat);
                    LonLat.clear();
                }
                
                PointNode= PointNode->next;
                }
            }
        else if ((!xmlStrcmp(curNode->name, (const xmlChar *)"RightBottomPoint"))) 
        {
            cout<<curNode->name<<endl;
            xmlNodePtr PointNode=curNode->xmlChildrenNode;
            while (PointNode != NULL) {
                if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Longtitude"))) 
                {
                    cout<<"\t"<<PointNode->name<<"\t";
                    szKey = xmlNodeGetContent(PointNode);
                    cout<<szKey<<endl;
                    LonLat.push_back(stof((char*)szKey));

                }
                else if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Latitude")))
                {
                    cout<<"\t"<<PointNode->name<<"\t";
                    szKey = xmlNodeGetContent(PointNode);
                    cout<<szKey<<endl;
                    LonLat.push_back(stof((char*)szKey));
                    CornerPoints.push_back(LonLat);
                    LonLat.clear();
                }
                PointNode= PointNode->next;
                }
            }
        else if ((!xmlStrcmp(curNode->name, (const xmlChar *)"LeftBottomPoint"))) 
        {
            cout<<curNode->name<<endl;
            xmlNodePtr PointNode=curNode->xmlChildrenNode;
            while (PointNode != NULL) {
                if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Longtitude"))) 
                {
                    cout<<"\t"<<PointNode->name<<"\t";
                    szKey = xmlNodeGetContent(PointNode);
                    cout<<szKey<<endl;
                    LonLat.push_back(stof((char*)szKey));

                }
                else if ((!xmlStrcmp(PointNode->name, (const xmlChar *)"Latitude")))
                {
                    cout<<"\t"<<PointNode->name<<"\t";
                    szKey = xmlNodeGetContent(PointNode);
                    cout<<szKey<<endl;
                    LonLat.push_back(stof((char*)szKey));
                    CornerPoints.push_back(LonLat);
                    LonLat.clear();
                }
                PointNode= PointNode->next;
                }
        }
    curNode= curNode->next;

    }

	   

    return 0;
}
