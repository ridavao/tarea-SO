#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace chrono;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <imagen_a_color> <imagen_escala_grises>" << endl;
        return -1;
    }

    // Cargar la imagen desde la ruta proporcionada
    Mat imagen = imread(argv[1]);

    if (imagen.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    // Crear una copia de la imagen para trabajar con ella
    Mat imagen_bn = imagen.clone();

    // Iniciar el cronómetro
    auto start = high_resolution_clock::now();

    // Procesar la imagen como matriz y transformar a blanco y negro (método de luminosidad)
    for (int i = 0; i < imagen.rows; ++i) {
        for (int j = 0; j < imagen.cols; ++j) {
            Vec3b &pixel = imagen_bn.at<Vec3b>(i, j);
            // Fórmula de luminosidad para transformar a blanco y negro
            int nuevo_valor = 0.2126 * pixel[2] + 0.7152 * pixel[1] + 0.0722 * pixel[0];
            pixel[0] = pixel[1] = pixel[2] = nuevo_valor;
        }
    }

    // Detener el cronómetro y calcular la duración
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Guardar la imagen en escala de grises
    imwrite(argv[2], imagen_bn);

    // Mostrar la imagen original y la imagen convertida a blanco y negro
    namedWindow("Imagen Original", WINDOW_NORMAL);
    namedWindow("Blanco y Negro", WINDOW_NORMAL);

    imshow("Imagen Original", imagen);
    imshow("Blanco y Negro", imagen_bn);

    cout << "Tiempo de procesamiento: " << duration.count() << " milisegundos" << endl;
    

    waitKey(0);
    destroyAllWindows();

    return 0;
}
