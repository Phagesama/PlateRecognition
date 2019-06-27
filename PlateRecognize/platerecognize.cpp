#include "platerecognize.h"
#include "ui_platerecognize.h"

#include "platecategory_svm.h"
#include "platelocator_v3.h"
#include <QDir>

#include <iostream>

PlateRecognize::PlateRecognize(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlateRecognize)
{
    ui->setupUi(this);
    //learnIt();

    //testIt();

    locatortest();
}

PlateRecognize::~PlateRecognize()
{
    delete ui;
}

void PlateRecognize::learnIt()
{
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";

    int label[3045] = {0};

    cv::Mat mat;
    std::vector<float> descriptor;

    cv::Mat descriptorMat = cv::Mat::zeros(3045, 1188, CV_32FC1);

    int i = 0;
    QString path = "E:/学习/专业实训3/车牌-字符样本/plates/非车牌";
    QDir* dir = new QDir(path);
    QStringList imgFileNames = dir->entryList(nameFilters);
    for (QString imgFileName : imgFileNames)
    {
        QString filePath = path + "\\" + imgFileName;
        std::string str = filePath.toLocal8Bit().toStdString();
        mat = cv::imread(str);

        descriptor = PlateCategory_SVM::ComputeHogDescriptors(mat);

        for(int j = 0; j < 1188; j++)
        {
            descriptorMat.at<float>(i, j) = descriptor.at(j);
        }
        label[i] = 0;
        i++;
    }
    path = "E:/学习/专业实训3/车牌-字符样本/plates/普通车牌";
    dir = new QDir(path);
    imgFileNames = dir->entryList(nameFilters);
    for (QString imgFileName : imgFileNames)
    {
        QString filePath = path + "\\" + imgFileName;
        std::string str = filePath.toLocal8Bit().toStdString();
        mat = cv::imread(str);

        descriptor = PlateCategory_SVM::ComputeHogDescriptors(mat);

        for(int j = 0; j < 1188; j++)
        {
            descriptorMat.at<float>(i, j) = descriptor.at(j);
        }
        label[i] = 1;
        i++;
    }
    path = "E:/学习/专业实训3/车牌-字符样本/plates/普通车牌_两行";
    dir = new QDir(path);
    imgFileNames = dir->entryList(nameFilters);
    for (QString imgFileName : imgFileNames)
    {
        QString filePath = path + "\\" + imgFileName;
        std::string str = filePath.toLocal8Bit().toStdString();
        mat = cv::imread(str);

        descriptor = PlateCategory_SVM::ComputeHogDescriptors(mat);

        for(int j = 0; j < 1188; j++)
        {
            descriptorMat.at<float>(i, j) = descriptor.at(j);
        }
        label[i] = 2;
        i++;
    }

    cv::Mat labelMat = cv::Mat(3045, 1, CV_32SC1, label);

    PlateCategory_SVM::Train(descriptorMat, labelMat);

    PlateCategory_SVM::Save("./WhatILearned.xml");
}

void PlateRecognize::testIt()
{
    int sum = 0;
    int error = 0;

    int temp = 0;

    cv::Mat mat;
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png" << "*.bmp";

    PlateCategory_SVM::Load("./WhatILearned.xml");

    QString path = "E:/学习/专业实训3/车牌-字符样本/test/非车牌";
    QDir* dir = new QDir(path);
    QStringList imgFileNames = dir->entryList(nameFilters);

    std::cout<<"非车牌"<<std::endl;
    for (QString imgFileName : imgFileNames)
    {
        QString filePath = path + "\\" + imgFileName;
        sum++;
        temp = PlateCategory_SVM::Test(filePath);
        if(temp != 0) error++;

        std::cout<<temp<<" ";
    }

    path = "E:/学习/专业实训3/车牌-字符样本/test/普通车牌";
    dir = new QDir(path);
    imgFileNames = dir->entryList(nameFilters);
    std::cout<<std::endl<<"普通车牌"<<std::endl;
    for (QString imgFileName : imgFileNames)
    {
        QString filePath = path + "\\" + imgFileName;
        sum++;
        temp = PlateCategory_SVM::Test(filePath);
        if(temp != 1) error++;

        std::cout<<temp<<" ";
    }

    path = "E:/学习/专业实训3/车牌-字符样本/test/普通车牌_两行";
    dir = new QDir(path);
    imgFileNames = dir->entryList(nameFilters);
    std::cout<<std::endl<<"普通车牌_两行"<<std::endl;
    for (QString imgFileName : imgFileNames)
    {
        QString filePath = path + "\\" + imgFileName;
        sum++;
        temp = PlateCategory_SVM::Test(filePath);
        if(temp != 2) error++;

        std::cout<<temp<<" ";
    }
    std::cout<<std::endl<<"total: "<<sum<<" error: "<<error<<" accuracy: "<<(float)(1 - (float)error/sum)<<std::endl;

}

void PlateRecognize::locatortest()
{
    PlateCategory_SVM::Load("./WhatILearned.xml");
    QString imgname = QString("E:/学习/专业实训3/车牌识别的素材/B9V636_2019-03-15-08-38-00-025052.jpg");
    std::string imgstr = imgname.toLocal8Bit().toStdString();
    cv::Mat matSource = cv::imread(imgstr);
    cv::Mat matProcess;
    QList<PlateInfo> plateinfos = PlateLocator_V3::LocatePlatesForAutoSample(matSource,matProcess);
    for (int i = 0;i < plateinfos.size();i++) {
        cv::Mat roi = plateinfos[i].originalMat;
        QString filename = QString("E:/学习/专业实训3/output/") + PlateCategoryString[plateinfos[i].plateCategory] + QString(".jpg");
        std::string str = filename.toLocal8Bit().toStdString();
        cv::imwrite(str,roi);

    }
}
