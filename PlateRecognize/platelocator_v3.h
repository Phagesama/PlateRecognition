#ifndef PLATELOCATOR_V3_H
#define PLATELOCATOR_V3_H

#include <opencv2/ml/ml.hpp>

#include "platecategory.h"
#include "platecategory_svm.h"

class PlateLocator_V3
{
private:
    static QList<PlateInfo> LocatePlatesByColor(cv::Mat matSource,
                                                int blur_Size = 5,
                                                int morph_Size_Width = 17,
                                                int morph_Size_Height = 3,
                                                int minWidth = 60, int maxWidth = 180,
                                                int minHeight = 18, int maxHeight = 80,
                                                float minRatio = 0.15f, float maxRatio = 0.70f);

    static QList<PlateInfo> LocatePlatesBySobel(cv::Mat matSource,
                                                int blur_Size = 5,
                                                int sobel_Scale = 1,
                                                int sobel_Delta = 0,
                                                int sobel_X_Weight = 1,
                                                int sobel_Y_Weight = 0,
                                                int morph_Size_Width = 17,
                                                int morph_Size_Height = 3,
                                                int minWidth = 60, int maxWidth = 180,
                                                int minHeight = 18, int maxHeight = 80,
                                                float minRatio = 0.15f, float maxRatio = 0.70f);

public:
    PlateLocator_V3();

    static bool VerifyPlateSize(cv::Size size,
                                int minWidth = 60, int maxWidth = 180,
                                int minHeight = 18, int maxHeight = 80,
                                float minRatio = 0.15f, float maxRatio = 0.70f);

    static QList<PlateInfo> LocatePlatesForCameraAdjust(cv::Mat matSource,
                                                        cv::Mat matProcess,
                                                        int blur_Size = 5,
                                                        int sobel_Scale = 1,
                                                        int sobel_Delta = 0,
                                                        int sobel_X_Weight = 1,
                                                        int sobel_Y_Weight = 0,
                                                        int morph_Size_Width = 17,
                                                        int morph_Size_Height = 3,
                                                        int minWidth = 60, int maxWidth = 250,
                                                        int minHeight = 18, int maxHeight = 100,
                                                        float minRatio = 0.15f, float maxRatio = 0.70f);

    static QList<PlateInfo> LocatePlatesForAutoSample(cv::Mat matSource,
                                                      cv::Mat matProcess,
                                                      int blur_Size = 5,
                                                      int sobel_Scale = 1,
                                                      int sobel_Delta = 0,
                                                      int sobel_X_Weight = 1,
                                                      int sobel_Y_Weight = 0,
                                                      int morph_Size_Width = 17,
                                                      int morph_Size_Height = 3,
                                                      int minWidth = 60, int maxWidth = 180,
                                                      int minHeight = 18, int maxHeight = 80,
                                                      float minRatio = 0.15f, float maxRatio = 0.70f);

    static QList<PlateInfo> LocatePlates(cv::Mat matSource,
                                         int blur_Size = 5,
                                         int sobel_Scale = 1,
                                         int sobel_Delta = 0,
                                         int sobel_X_Weight = 1,
                                         int sobel_Y_Weight = 0,
                                         int morph_Size_Width = 17,
                                         int morph_Size_Height = 3,
                                         int minWidth = 60, int maxWidth = 180,
                                         int minHeight = 18, int maxHeight = 80,
                                         float minRatio = 0.15f, float maxRatio = 0.70f);

};

#endif // PLATELOCATOR_V3_H
