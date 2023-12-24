#pragma once
#include <qvector.h>
#include "Book.h"

class Table : public QWidget
{
private:
	Q_OBJECT
	QVector<QVector<Book*>> stack;
	QVector<int> offset;
	int countStack;
	const int MaxStacks = 6;
	void AddBook(int, int, int);

public:
	Table(QWidget*, int countStack = 3, QWidget* parent = 0);

protected:
	void paintEvent(QPaintEvent*) override;
	void dragEnterEvent(QDragEnterEvent*);
	void dropEvent(QDropEvent* e);

signals:
	void calculatedThickness(int);
	void answer(bool);
	void removeFromRack(int);

private slots:
	void deferredInit();
	void checkBook(int);

public slots:
	void DeleteBook(int);

};

