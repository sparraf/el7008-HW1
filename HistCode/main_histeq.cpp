#define _DEBUG
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

// Funcion para visualizar histogramas. Solo debug
// Referencia: https://stackoverflow.com/questions/33830208/how-to-find-the-pixel-value-that-corresponds-to-a-specific-number-of-pixels/33833349#33833349
/*
void drawHist(const vector<int>& data, Mat3b& dst, int binSize = 3, int height = 0, int ref_value = -1)
{
    int max_value = *max_element(data.begin(), data.end());
    int rows = 0;
    int cols = 0;
    float scale = 1;
    if (height == 0) {
        rows = max_value + 10;
    }
    else {
        rows = height;
        scale = float(height) / (max_value + 10);
    }
    cols = data.size() * binSize;
    dst = Mat3b(rows, cols, Vec3b(0, 0, 0));
    for (int i = 0; i < data.size(); ++i)
    {
        int h = rows - int(scale * data[i]);
        rectangle(dst, Point(i*binSize, h), Point((i + 1)*binSize - 1, rows), (i % 2) ? Scalar(0, 100, 255) : Scalar(0, 0, 255), FILLED);
    }

    if (ref_value >= 0)
    {
        int h = rows - int(scale * ref_value);
        line(dst, Point(0, h), Point(cols, h), Scalar(255,0,0));
    }
}
*/

// Funcion para calcular el nuevo valor del pixel ecualizado
int transformarPixel(int accHist, int minHist, int dim) {
    float aux = roundf((float)(accHist - minHist) / (dim - minHist) * 255);
    return (int) aux;
}

void ecualizar(Mat input, Mat output)
{
    // Crear arreglos para el histograma, el histograma acumulado, y una variable que guarde el minimo de este ultimo
	int hist[256];
	int accHist[256];
	int minHist;

	for (int i=0; i<256; i++)
		hist[i] = 0;

	// Calcular histograma
	for (int r=0; r<input.rows; r++)
	{
		for (int c=0; c<input.cols; c++)
		{
			int ind = input.at<unsigned char>(r,c);
			hist[ind] += 1;
		}
	}

	// Calcular histograma acumulado y su valor minimo distinto de cero
	accHist[0] = hist[0];
	if(accHist[0] != 0) {
	    minHist = accHist[0];
	}
    for (int j = 1; j < 256; ++j) {
        accHist[j] = accHist[j-1] + hist[j];
        if(accHist[j] != 0 && accHist[j-1] == 0) {
            minHist = accHist[j];
        }
    }

    // Generar salida
    int dim = input.rows * input.cols;
    for (int r=0; r<input.rows; r++)
    {
        for (int c=0; c<input.cols; c++)
        {
            int original = input.at<unsigned char>(r, c);
            output.at<unsigned char>(r, c) = transformarPixel(accHist[original], minHist, dim);
        }
    }

    // Debug, solo visualizacion de histogramas
    /*
    // Histogram
    vector<int> H(256, 0);
    for (int r = 0; r < output.rows; ++r) {
        for (int c = 0; c < output.cols; ++c) {
            H[output.at<unsigned char>(r, c)]++;
        }
    }

    // Cumulative histogram
    vector<int> C = H;
    for (int i = 1; i < H.size(); ++i) {
        C[i] = C[i - 1] + H[i];
    }

    Mat3b plotH;
    drawHist(C, plotH, 3, 300);
    imshow("Cum", plotH);
     */

    return;
}

int main(void)
{
	Mat originalRGB = imread("corteza.png"); //Leer imagen

	if(originalRGB.empty()) // No encontro la imagen
	{
		cout << "Imagen no encontrada" << endl;
		return 1;
	}
	
	Mat original;
	cvtColor(originalRGB, original, COLOR_BGR2GRAY);
	
	Mat output = Mat::zeros(original.rows, original.cols, CV_8UC1);
	ecualizar(original, output);

	imshow("ecualizado", output);   // Mostrar imagen
	imwrite("ecualizado.jpg", output); // Grabar imagen
	waitKey(0); // Pausa, permite procesamiento interno de OpenCV

	return 0; // Sale del programa normalmente
}
