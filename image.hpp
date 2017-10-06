#include <opencv2/core/core.hpp>


class Image {
private:
    cv::Mat mat;
    uint rows;
    uint cols;

public:
    Image() {};
    Image(cv::Mat);
    Image(std::string, bool);
    ~Image() {};

    uint get_rows() { return rows; };
    uint get_cols() { return cols; };

    void open(std::string);
    void save(std::string, std::string);

    uint8_t* vectorize_mat();
    static cv::Mat vector_to_mat(uint8_t*, int, int);

    static uint8_t* sort(uint8_t*, int, int, bool);
};
