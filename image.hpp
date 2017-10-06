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

    std::unique_ptr<uint8_t[]> vectorize_mat();
    cv::Mat vector_to_mat(std::unique_ptr<uint8_t[]>&);
};
