#include <iostream>
#include <opencv2/opencv.hpp>
#include "VideoIO.h"
#include "MeshFlow.h"
#include "Fast_klt.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    char *name = "../data/test.avi";

    double m_fps;

    vector<cv::Mat> m_frames = VideoIO::GetFrames(name, m_fps);

    cv::Size m_size = m_frames[0].size();
    int m_height = m_size.height;
    int m_width = m_size.width;
    int m_frameNum = m_frames.size();

    vector<cv::Mat> map_X, map_Y;

    map_X.resize(m_frameNum - 1);
    for (int i = 0; i < map_X.size(); i++) map_X[i].create(m_size, CV_32F);

    map_Y.resize(m_frameNum - 1);
    for (int i = 0; i < map_Y.size(); i++) map_Y[i].create(m_size, CV_32F);

    MeshFlow meshflow(m_width, m_height);
    vector<cv::Point2f> sourceFeatures, targetFeatures;

    cout << "MeshFlow starts." << endl;
    for (int i = 1; i < m_frameNum; i++) {
//        for (int i = 1; i < 10; i++) {
        meshflow.ReInitialize();
        sourceFeatures.clear();
        targetFeatures.clear();

        myKLT(m_frames[i - 1], m_frames[i], sourceFeatures, targetFeatures);
        meshflow.SetFeature(sourceFeatures, targetFeatures);

        meshflow.Execute();
        meshflow.GetMotions(map_X[i-1], map_Y[i-1]);
        cout << i << "...";
    }
    cout << "[DONE]" << endl;

    /*
     * Visualize
     */
    cv::namedWindow("MeshFlow");
    for (int i = 1; i < m_frameNum; i++) {

        cv::Mat canvas = m_frames[i-1].clone();

        for (int meshVertex_X = 100; meshVertex_X <= 600; meshVertex_X += 100){
            for (int meshVertex_Y = 100; meshVertex_Y <= 300; meshVertex_Y += 100){
                cv::arrowedLine(canvas,
                                cv::Point(meshVertex_X,meshVertex_Y),
                                cv::Point(meshVertex_X+map_X[i-1].at<float>(meshVertex_X,meshVertex_Y), meshVertex_Y+map_Y[i-1].at<float>(meshVertex_X,meshVertex_Y)),
                                cv::Scalar(255,0,0),2,8,0,0.6
                );
            }
        }

        cv::imshow("MeshFlow", canvas);
        cv::waitKey(50);
    }

    cv::destroyAllWindows();

	return 0;
}
