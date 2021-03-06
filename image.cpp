#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "image.hpp"


// Construct an Image using existing matrix
Image::Image(cv::Mat& m) {
    mat = m;
    rows = m.rows;
    cols = m.cols;
}


// Construct an Image using image from a given path
Image::Image(std::string path) {
    if (path.empty())
        throw std::runtime_error("path error");
    
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


uint8_t* Image::vectorize() {
    auto row_vector = new uint8_t[rows*cols];

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
cv::Mat Image::vector_to_mat(uint8_t* row_vector, int rows, int cols) {
    return cv::Mat(rows, cols, CV_8UC1, row_vector);
}


uint8_t* Image::sort(uint8_t* in, int len, int k) {
    auto res = new uint8_t[len]();
    auto tmp = new int[k+1]();

    for (int i = 0; i < len; i++) {
        tmp[in[i]] += 1;
    }

    int counter = 0;
    for (int i = 0; i < k+1; i++) {
        while (tmp[i]) {
            res[counter] += i;
            tmp[i]       -= 1;
            counter      += 1;
        }
    }
   
    delete[] tmp;

    return res; 
}