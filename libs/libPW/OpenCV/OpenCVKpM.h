/**
*-------------------------------------------------
*  Copyright 2016 by Tidop Research Group <daguilera@usal.se>
*
* This file is part of GRAPHOS - inteGRAted PHOtogrammetric Suite.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is free software: you can redistribute
* it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either
* version 3 of the License, or (at your option) any later version.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*-------------------------------------------------
*/
#ifndef OPENCVKPM_H
#define OPENCVKPM_H

#include "libPW_global.h"

#include <QMap>
#include <QString>
#include <QStringList>
#include <QVector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#ifdef USE_OPENCV
#include <opencv2/nonfree/nonfree.hpp>
#endif
#include <opencv2/highgui/highgui.hpp>

#include <QParams.h>
#include "OpenCVKpMParameters.h"

namespace PW
{

class LIBPWSHARED_EXPORT OpenCVKpM
{
public:
    OpenCVKpM();
    int detectOutliersInMatches(bool& printReport,
                                QString& strError);
    int getApplyOutliersDetection(bool& applyOutliersDetection,
                                  QString& strError);
    int getDetector(cv::FeatureDetector** ptrDetector, //cv::Feature2D** ptrDetector,
                    QString& strError);
    int getDescriptorParametersTagQParams(QString descriptorTag,
                                          QStringList& parametersTagQParams,
                                          QString &strError);
    int getDetectorParametersTagQParams(QString detectorTag,
                                        QStringList& parametersTagQParams,
                                        QString &strError);
    int getDetectorsTag(QStringList& detectorsTag,
                        QString& strError);
    int getDescriptor(cv::DescriptorExtractor **ptrDescriptor,
                      QString& strError);
    int getDescriptorsByDetector(QString& detectorTag,
                                 QString& defaultDescriptor,
                                 QStringList& descriptors,
                                 QString& strError);
    int getEngines(QStringList& engines,
                   QString& strError);
    int getMatcher(cv::DescriptorMatcher** ptrMatcher,
                   int& kBestMatches,
                   double& ratioTestDistance,
                   QString& strError);
    int getMatchersByDetectorAndDescriptor(QString& detectorTag,
                                           QString& descriptorTag,
                                           QString& defaultMatcher,
                                           QStringList& matchers,
                                           QString& strError);
    int getMatcherParametersTagQParams(QString matcherTag,
                                       QStringList& matchersTagQParams,
                                       QString &strError);
    int getNumberOfImages(int& numberOfImages,
                          QString& strError);
    int getNumberOfImagePairs(int& numberOfImagePairs,
                              QString& strError);
    int getNumberOfImagePairsProcessed(int& numberOfImagePairsProcessed,
                                       QString& strError);
    int getOutliersDetectionAzimuthParametersTag(QStringList& parametersTag,
                                                 QString& strError);
    int getOutliersDetectionDistanceParametersTag(QStringList& parametersTag,
                                                  QString& strError);
    int keyPointsDetections(QString& strError);
    int matching(QString& strError);
    int readImagePairsFileName(QString& strError);
    int readParameterFile(QString& fileName,
                          QString& strError);
    int removeDuplicatedMatches(bool toUniqueMatch,
                                bool removeMultipleToOne,
                                bool removeOneToMultiple,
                                QString& strError);
    int writeParametersFileFromEngine(QString& detector,
                                      QString& descriptor,
                                      QString& matcher,
                                      QVector<QParams::Param*>& detectorParameters,
                                      QVector<QParams::Param*>& descriptorParameters,
                                      QVector<QParams::Param*>& matcherParameters,
                                      int& numberOfBestMatches,
                                      bool& applyTestRatio,
                                      double& testRatioValue,
                                      bool& applyTestDistance,
                                      double& testDistanceValue,
                                      bool& applyOutliersDeteccion,
                                      bool& applyOutliersAzimuth,
                                      QVector<QParams::Param*>& outliersAzimuthParameters,
                                      bool& applyOutliersDistance,
                                      QVector<QParams::Param*>& outliersDistanceParameters,
                                      QString& imagesBasePath,
                                      QString &imagePairsFileName,
                                      QString& parametersFileName,
                                      QString& strError);
    int writeMatchesFiles(QString& strError);
private:
    double azimuth(double xi,double yi,double xj,double yj);
    double distance(double xi,double yi,double xj,double yj);
    void initialize();
    OpenCVKpMParameters mParameters;
    QMap<QString,QString> mImageFileNames;
    QMap<QString,int> mImageWidths;
    QMap<QString,int> mImageHeights;
    QMap<QString,QVector<QString> > mImagesPairs;
    int mNumberOfImagePairs;
    int mNumberOfImagePairsProcessed;
    QMap<QString,std::vector<cv::KeyPoint> > mImagesKeyPoints;
    QMap<QString,cv::Mat> mImagesKeyPointsDescriptors;
    QMap<QString,cv::Mat> mImages;
    QMap<QString,QVector<std::vector<cv::DMatch> > > mImagesPairsMatches;
    QMap<QString,QVector<std::vector<cv::DMatch> > > mImagesPairsMatchesReverse;
    QMap<QString,QVector<QVector<bool> > > mImagesPairsMatchesOutliers;
    QMap<QString,QVector<std::vector<cv::Point2f> > > mImagesPairsMatchesPointsFirsts;
    QMap<QString,QVector<std::vector<cv::Point2f> > > mImagesPairsMatchesPointsSeconds;
    QMap<QString,QVector<std::vector<int> > > mImagesPairsMatchesIndexesFirsts;
    QMap<QString,QVector<std::vector<int> > > mImagesPairsMatchesIndexesSeconds;
    QMap<QString,QVector<std::vector<cv::Point2f> > > mImagesPairsMatchesPointsFirstsReverse;
    QMap<QString,QVector<std::vector<cv::Point2f> > > mImagesPairsMatchesPointsSecondsReverse;
    QMap<QString,QVector<std::vector<int> > > mImagesPairsMatchesIndexesFirstsReverse;
    QMap<QString,QVector<std::vector<int> > > mImagesPairsMatchesIndexesSecondsReverse;
    QStringList mEngines;
    bool mDescriptorIsBinary;
};

}

#endif // OPENCVKPM_H
