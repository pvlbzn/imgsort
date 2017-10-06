#include <string>
#include <iostream>
#include <memory>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "image.hpp"


// Construct an Image using existing matrix
Image::Image(cv::Mat m) {
    mat = m;
    rows = m.rows;
    cols = m.cols;
}


// Construct an Image using image from a given path
Image::Image(std::string path, bool is_bw=true) {
    if (path.empty())
        throw std::runtime_error("path error");
    
    if (is_bw)
        mat = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);

    if (!mat.data)
        throw std::runtime_error("no data error");
    
    rows = mat.rows;
    cols = mat.cols;
}


void Image::save(std::string where="./", std::string name="out.jpg") {
    if (!mat.data)
        throw std::runtime_error("no data error");
    
    if (!cv::imwrite(where + name, mat))
        throw std::runtime_error("imwrite error");
}


std::unique_ptr<uint8_t[]> Image::vectorize_mat() {
    auto row_vector = std::unique_ptr<uint8_t[]>{ new uint8_t[rows*cols] };

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            row_vector[index] = mat.at<uchar>(i, j);
            index += 1;
        }
    }

    return row_vector;
}


// Construct a Mat from a vector. Reverse of vectorization.
cv::Mat Image::vector_to_mat(std::unique_ptr<uint8_t[]>& row_vector) {
    return cv::Mat(rows, cols, CV_8UC1, row_vector.get());
}
