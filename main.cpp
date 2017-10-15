#include <iostream>
#include <sstream>
#include <chrono>
#include <functional>

#include "image.hpp"


void test();
uint8_t* sort(std::function<uint8_t* (uint8_t*, int, int)> fn, uint8_t* in, int len, int k);


int main() {
    test();
}


void test() {
    auto image_pool = std::vector<Image>();

    for (int i = 0; i < 8; i++) {
        std::ostringstream ss;
        ss << "./samples/s" << i+1 << ".jpg";
        image_pool.push_back(Image(ss.str()));
    }

    int counter = 1;
    for (auto& image : image_pool) {
        auto vec = image.vectorize();
        auto svec = sort(Image::sort, vec, image.get_rows() * image.get_cols(), 256);

        auto mat = Image::vector_to_mat(svec, image.get_rows(), image.get_cols());

        delete[] vec;
        delete[] svec;

        auto res = Image(mat);
        std::ostringstream ss;
        ss << "output_" << counter << ".jpg";
        res.save("./samples/", ss.str());

        counter += 1;
    }
}


uint8_t* sort(std::function<uint8_t* (uint8_t*, int, int)> fn, uint8_t* in, int len, int k) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = fn(in, len, k);
    auto t2 = std::chrono::high_resolution_clock::now();
    

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << len << " " << diff << std::endl;

    return res;
}
