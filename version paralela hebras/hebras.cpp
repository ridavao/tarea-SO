#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace cv;

void convertToGrayThreaded(Mat& image, Mat& grayImage, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            // Fórmula de luminosidad para convertir a escala de grises
            int grayValue = 0.21 * image.at<Vec3b>(i, j)[2] +
                            0.72 * image.at<Vec3b>(i, j)[1] +
                            0.07 * image.at<Vec3b>(i, j)[0];

            grayImage.at<uchar>(i, j) = grayValue;
        }
    }
}

void convertToGrayUsingThreads(const string& inputFileName, const string& outputFileName, int numThreads) {
    Mat image = imread(inputFileName);

    if (image.empty()) {
        cout << "No se pudo abrir la imagen. Verifica la ruta." << endl;
        return;
    }

    Mat grayImage(image.rows, image.cols, CV_8UC1);

    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    int rowsPerThread = image.rows / numThreads;
    int extraRows = image.rows % numThreads;
    int startRow = 0;

    for (int i = 0; i < numThreads; ++i) {
        int endRow = startRow + rowsPerThread + (i < extraRows ? 1 : 0);
        threads.emplace_back(convertToGrayThreaded, ref(image), ref(grayImage), startRow, endRow);
        startRow = endRow;
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedSeconds = end - start;

    cout << "Tiempo de procesamiento: " << elapsedSeconds.count() << " segundos" << endl;

    namedWindow("Imagen Original", WINDOW_NORMAL);
    imshow("Imagen Original", image);
    waitKey(0);

    namedWindow("Imagen en Escala de Grises", WINDOW_NORMAL);
    imshow("Imagen en Escala de Grises", grayImage);
    waitKey(0);

    imwrite(outputFileName, grayImage);
    destroyAllWindows();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_hebras>" << endl;
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[2];
    int numThreads = atoi(argv[3]);

    convertToGrayUsingThreads(inputFileName, outputFileName, numThreads);

    return 0;
}
