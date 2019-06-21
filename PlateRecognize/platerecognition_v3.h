#ifndef PLATERECOGNITION_V3_H
#define PLATERECOGNITION_V3_H

#include <opencv2/ml/ml.hpp>

#include "platecategory.h"

class PlateRecognition_V3
{
private:
    static void CheckLeftAndRightToRemove(PlateInfo plateInfo);

    static void CheckPlateColor(PlateInfo plateInfo);

public:
    PlateRecognition_V3();

    static QList<PlateInfo> Recognite(cv::Mat matSource);

    static PlateInfo GetPlateInfoByMutilMethodAndMutilColor(PlateInfo plateInfo);

    static bool JudgePlateRightful(PlateInfo plateInfo);

    static PlateInfo GetPlateInfoByMutilMethod(PlateInfo plateInfo, PlateColor plateColor);

    static PlateInfo GetPlateInfo(PlateInfo plateInfo, PlateColor plateColor, CharSplitMethod splitMethod);


};

#endif // PLATERECOGNITION_V3_H
