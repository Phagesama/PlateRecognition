#ifndef CHARSEGMENT_V3_H
#define CHARSEGMENT_V3_H

#include<opencv2/opencv.hpp>
#include"platecategory.h"

class CharSegment_V3
{
public:
    CharSegment_V3();
    static cv::Mat ClearMaoding(cv::Mat threshold);
    static cv::Mat ClearBorder(cv::Mat threshold);
    static cv::Mat ClearMaodingAndBorder(cv::Mat gray, PlateColor plateColor);
    static QList<CharInfo> SpliteCharslnPlateMat(cv::Mat plateMat, QList<cv::Rect> rects);
    static QList<CharInfo> SplitePlateForAutoSample(cv::Mat plateMat);
    static QList<CharInfo> SplitePlateByIndexTransform(cv::Mat originalMat,PlateColor plateColor,
                                                       int leftLimit = 0,int rightLimit = 0,
                                                       int topLimit = 0,int bottomLimit = 0,
                                                       int minWidth = 2,int maxWidth = 30,
                                                       int minHeight = 10,int maxHeight = 80,
                                                       float minRatio = 0.08f,float maxRatio = 2.0f);
    static QList<CharInfo> SplitePlateByGammaTransform(cv::Mat originalMat,PlateColor plateColor,
                                                       float gammaFactor = 0.40f,int leftLimit = 0,
                                                       int rightLimit = 0,int topLimit = 0,
                                                       int bottomLimit = 0,int minWidth = 2,
                                                       int maxWidth = 30,int minHeight = 10,
                                                       int maxHeight = 80,float minRatio = 0.08f,float maxRatio = 2.0f);
    static QList<CharInfo> SplitePlateByOriginal(cv::Mat originalMat,cv::Mat plateMat,PlateColor plateColor,
                                                 CharSplitMethod charSplitMethod = CharSplitMethod::原图,
                                                 int leftLimit = 0,int rightLimit = 0,
                                                 int topLimit = 0,int bottomLimit = 0,
                                                 int minWidth = 2,int maxWidth = 30,
                                                 int minHeight = 10,int maxHeight = 80,
                                                 float minRatio = 0.08f,float maxRatio = 2.0f);
    static bool VerifyRect(cv::Rect rect,
                           int minWidth = 2,int maxWidth = 30,
                           int minHeight = 10,int maxHeight = 80,
                           float minRatio = 0.08f,float maxRatio = 2.0f);
    static bool NotOnBorder(cv::Rect rectToJudge,cv::Size borderSize,
                            int leftLimit = 0,int rightLimit = 0,
                            int topLimit = 0,int bottomLimit = 0);
    static void SortRectsByLeft_ASC(QList<cv::Rect> rects);
    static void SortRectsByHeight_ASC(QList<cv::Rect> rects);
    static cv::Rect MergeRect(cv::Rect A,cv::Rect B);
    static QList<cv::Rect> AdjustRects(QList<cv::Rect> rects);
    static QList<cv::Rect> MergeRects(QList<cv::Rect> rects);
    static QList<cv::Rect> RejectInnerRectFromRects(QList<cv::Rect> rects);
    static float GetRectsAverageHeight(QList<cv::Rect> rects);
    static int GetRectsMaxHeight(QList<cv::Rect> rects);
    static int GetMedianRectsTop(QList<cv::Rect> rects);
    static int GetMedianRectsBottom(QList<cv::Rect> rects);

private:
    class RectTopComparer
    {
    public:
        int Compare(cv::Rect x,cv::Rect y);
    };
    class RectBottomComparer
    {
    public:
        int Compare(cv::Rect x,cv::Rect y);
    };
    class RectHeightComparer
    {
    public:
        int Compare(cv::Rect x,cv::Rect y);
    };
    class RectLeftComparer
    {
    public:
        int Compare(cv::Rect x,cv::Rect y);
    };
    class CharInfoLeftCompare
    {
    public:
        int Compare(CharInfo x,CharInfo y);
    };

};

#endif // CHARSEGMENT_V3_H
