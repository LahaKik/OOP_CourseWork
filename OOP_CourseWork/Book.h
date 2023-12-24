#pragma once
#include <random>
#include <qwidget.h>
#include <qpainter.h>


class Book : public QWidget
{
private:
	Q_OBJECT
	bool IsFocus;
	bool isAvailible;
	static QVector<int> remainingVolumes;

public:
	int NumVolume;
	static int Width;
	static int Height;
	int Thickness;
	static int ThickMin, ThickMax;

	Book(int thick, int numVol, QWidget* parent);

	Book(QWidget* parent = nullptr);

	static int GetRandVolume();
	void RemoveFocus();

signals:
	void checkAvailability(int);

public slots:
	void recieve(bool);

protected:
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent*) override;
};
