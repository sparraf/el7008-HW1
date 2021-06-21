#define _DEBUG

// Instruciones:
// Dependiendo de la versión de opencv, deben usar los primeros dos includes (cv.h, highgui.h) o bien los dos includes
// siguientes (imgproc.hpp, highgui.hpp)

//#include <cv.h>
//#include <highgui.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

void convolucion(Mat input, Mat mask, Mat output)
{
	for (int r=0; r<input.rows; r++)
	{
		for (int c=0 ; c<input.cols; c++)
		{
			float sum = 0;
			//Calcular posicion (fila,columna) donde se debe comenzar a calcular la convolución (i.e. la vecindad del
			//punto ancla)
			int convR = r - mask.rows/2;
			int convC = c - mask.cols/2;
			for (int maskR=0; maskR < mask.rows; maskR++)
			{
				for (int maskC=0; maskC < mask.cols; maskC++)
				{
					//Caso de borde: Si el pixel de la vecindad no existe, rellenar con ceros
					if(convR >= 0 && convR < input.rows && convC >= 0 && convC < input.cols)
					{
						sum += input.at<float>(convR,convC) * mask.at<float>(maskR,maskC);
					}
					convC++;
				}
				convC = c - mask.cols/2;
				convR++;
			}	
			output.at<float>(r,c) = sum;
		}
	}
}

// No es necesario modificar esta funcion
Mat fft(Mat I)
{
	Mat padded;

	int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;

	merge(planes, 2, complexI);
	
	dft(complexI, complexI);
	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];
	magI += Scalar::all(1);
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols/2;
	int cy = magI.rows/2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, NORM_MINMAX);
	
	Mat res;
	magI = magI*255;
	magI.convertTo(res, CV_8UC1);
	return res;
}

int main(void) {
    Mat originalRGB = imread("figuras.png"); //Leer imagen

    if (originalRGB.empty()) // No encontro la imagen
    {
        cout << "Imagen no encontrada" << endl;
        return 1;
    }

    Mat original;
    cvtColor(originalRGB, original, COLOR_BGR2GRAY);

    Mat input;
    original.convertTo(input, CV_32FC1);

    Mat output = input.clone();


    Mat esp_in;
    esp_in = fft(input);
    imshow("spectrum_in", esp_in);
    imwrite("spectrum_in.jpg", esp_in); // Grabar imagen


    // Pregunta 2.1: Filtro pasa bajos recto de 3x3
    /*
    Mat mask = Mat(3, 3, CV_32FC1);

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            mask.at<float>(i,j) = static_cast<float>(1.0 / 9);

    convolucion(input, mask, output);
    */
    // FIN PREGUNTA 2.1

    // Pregunta 2.2: Filtro pasa bajos unidimensional aplicado por filas y columnas
    /*
    Mat hMask = Mat(1, 3, CV_32FC1);
    Mat vMask = Mat(3, 1, CV_32FC1);

    for (int j=0; j<3; j++)
        hMask.at<float>(0,j) = static_cast<float>(1.0 / 3);

    transpose(hMask, vMask);

    convolucion(input, hMask, output);
    input = output.clone();
    convolucion(input, vMask, output);
    */
    // FIN PREGUNTA 2.2

    // Pregunta 2.3: Filtro gaussiano pasa bajos de 5x5 con sigma=1
    /*
    Mat auxMask = getGaussianKernel(5, 1.0, CV_32F);
    Mat temp = Mat(1, 5, CV_32FC1);

    transpose(auxMask, temp);

    Mat mask = auxMask*temp;

    convolucion(input, mask, output);
    */
    // FIN PREGUNTA 2.3

    // Pregunta 2.4: Filtro gausssiano pasa bajos de 1x5 por filas y columnas
    /*
    Mat hMask = getGaussianKernel(5, 1.0, CV_32F);
    Mat vMask = Mat(5, 1, CV_32FC1);

    transpose(hMask, vMask);

    convolucion(input, hMask, output);
    input = output.clone();
    convolucion(input, vMask, output);
    */
    // FIN PREGUNTA 2.4

    // Pregunta 3.1: Filtro pasa altos Prewitt vertical
    /*
    Mat mask = Mat(3, 3, CV_32FC1);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            if (j == 0)
                mask.at<float>(i, j) = static_cast<float>(-1.0 / 9);
            else if (j == 1)
                mask.at<float>(i, j) = 0.0;
            else
                mask.at<float>(i, j) = static_cast<float>(1.0 / 9);
        }
    }

    convolucion(input, mask, output);
    */
    // FIN PREGUNTA 3.1

    // Pregunta 3.2: Filtro pasa altos Prewitt horizontal
    /*
    Mat mask = Mat(3, 3, CV_32FC1);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            if (i == 0)
                mask.at<float>(i, j) = static_cast<float>(-1.0 / 9);
            else if (i == 1)
                mask.at<float>(i, j) = 0.0;
            else
                mask.at<float>(i, j) = static_cast<float>(1.0 / 9);
        }
    }

    convolucion(input, mask, output);
    */
    // FIN PREGUNTA 3.2

    // Pregunta 3.3: Filtro Laplaciano de 3x3

    Mat mask = Mat(3, 3, CV_32FC1);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1)
                mask.at<float>(i, j) = static_cast<float>(8.0 / 9);
            else
                mask.at<float>(i, j) = static_cast<float>(-1.0 / 9);
        }
    }

    convolucion(input, mask, output);

    // FIN PREGUNTA 3.3

    // Pregunta 3.4: Filtro laplaciano de guassiana de 5x5 con sigma=1
    /*
    Mat mask = Mat(5, 5, CV_32FC1);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++) {
            mask.at<float>(i,j) = 0;
        }
    }

    mask.at<float>(0, 2) = 1.0/25;
    mask.at<float>(1, 1) = 1.0/25;
    mask.at<float>(1, 3) = 1.0/25;
    mask.at<float>(2, 0) = 1.0/25;
    mask.at<float>(2, 4) = 1.0/25;
    mask.at<float>(3, 1) = 1.0/25;
    mask.at<float>(3, 3) = 1.0/25;
    mask.at<float>(4, 2) = 1.0/25;

    mask.at<float>(1, 2) = 2.0/25;
    mask.at<float>(2, 1) = 2.0/25;
    mask.at<float>(2, 3) = 2.0/25;
    mask.at<float>(3, 2) = 2.0/25;

    mask.at<float>(2, 2) = -16.0/25;

    convolucion(input, mask, output);
    */
    // FIN PREGUNTA 3.4

    Mat esp_out;
	esp_out = fft(output);
	imshow("spectrum_out", esp_out);
	imwrite("spectrum_out.jpg", esp_out); // Grabar imagen

	output = abs(output);

	Mat last;
	output.convertTo(last, CV_8UC1);

	imshow("filtered", last);   // Mostrar imagen
	imwrite("filtered.jpg", last); // Grabar imagen
	waitKey(0); // Pausa, permite procesamiento interno de OpenCV

	return 0; // Sale del programa normalmente
}
