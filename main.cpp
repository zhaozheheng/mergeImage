#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>

using namespace std;
using namespace cv;

void GetFileNames(string path, vector<string>& filenames){
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir)) != 0){
        if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            filenames.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);
}

int main()
{
    vector<string> input_names;
    vector<string> mesh_names;

    string input_path = "Res/input";
    string mesh_path = "Res/mesh";
    string output_path = "Res/output";

    GetFileNames(input_path, input_names);
    GetFileNames(mesh_path, mesh_names);

    for (int k = 0; k < input_names.size(); ++k) {
        cout << input_names[k] << endl;
    }
    for (int k = 0; k < mesh_names.size(); ++k) {
        cout << mesh_names[k] << endl;
    }
    cout << input_names.size() << endl;
    cout << mesh_names.size() << endl;

    for (int i = 0; i < input_names.size(); ++i) {
        for (int j = 0; j < mesh_names.size(); ++j) {
            if (stoi(input_names[i].substr(10, 4)) + 1 == stoi(mesh_names[j].substr(9, 4))){
                string out = input_names[i].substr(10, 8);
                cout << input_names[i] << endl;
                cout << mesh_names[j] << endl;
                double alpha = 0.5;
                double beta;

                Mat src1, src2, dst;

                /// Read image ( same size, same type )，注意，这里一定要相同大小，相同类型，否则出错
                src1 = imread(input_names[i]);
                src2 = imread(mesh_names[j]);

                if (!src1.data) { printf("Error loading src1 \n"); return -1; }
                if (!src2.data) { printf("Error loading src2 \n"); return -1; }

                beta = (1.0 - alpha);
                addWeighted(src1, 1.0, src2, 0.5, 0.0, dst); //这里调用了addWeighted函数，得到的结果存储在dst中
                imshow("test", dst);
                wait(0);
                imwrite("Res/output/" + out, dst);
            }
        }
    }
    Mat img1 = imread("Res/input/0159.png");
    Mat img2 = imread("Res/mesh/0159.png");

    Mat res;
    addWeighted(img1, 1.0, img2, 0.5, 0.0, res); //这里调用了addWeighted函数，得到的结果存储在dst中

    imwrite("Res/output/0159_res.png", res);
    std::cout << "end" << std::endl;

    return 0;
}
