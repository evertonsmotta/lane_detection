#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Função para processar a imagem (cinza, suavização, Canny)
cv::Mat preprocessImage(cv::Mat img) {
    cv::Mat gray, blurred;

    // Converter para escala de cinza
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Aplicar desfoque gaussiano para suavizar a imagem
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

    return blurred;
}

// Função para isolar a região de interesse (ROI)
Mat regionOfInterest(Mat image) {
	Mat mask = Mat::zeros(image.size(), image.type());
	Point pts[1][4] = {
		{ Point(100, image.rows), Point(image.cols - 100, image.rows), Point(image.cols / 2 + 50, image.rows / 2), Point(image.cols / 2 - 50, image.rows / 2) }
	};
	const Point* ppt[1] = { pts[0] };
	int npt[] = { 4 };
	fillPoly(mask, ppt, npt, 1, Scalar(255));
	Mat maskedImage;
	bitwise_and(image, mask, maskedImage);
	return maskedImage;
}

// Função para detectar linhas usando Transformada de Hough
vector<Vec4i> detectLines(Mat edges) {
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 150);
	return lines;
}

// Função para desenhar as linhas detectadas na imagem original
void drawLines(Mat &frame, vector<Vec4i> lines) {
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 3, LINE_AA);
	}
}

int main() {
	// Carregar a imagem
	Mat image = imread("images/road.jpeg");

	if (image.empty()) {
		cout << "Erro ao carregar a imagem!" << endl;
		return -1;
	}

	// Processar a imagem
	Mat edges = preprocessImage(image);
	Mat roi = regionOfInterest(edges);
	vector<Vec4i> lines = detectLines(roi);

	// Desenhar as linhas detectadas
	drawLines(image, lines);

	// Exibir o resultado
	imshow("Lane Detection", image);
	waitKey(0); // Esperar pressionamento de tecla

	return 0;
}
