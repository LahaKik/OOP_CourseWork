#pragma once
#include <vector>
#include "Book.h"
#include <qwidget.h>
#include <qvector.h>

class Rack : public QWidget
{
private:
	Q_OBJECT
	QVector<QVector<Book*>> shelf;
	bool IsSameBook(QDragEnterEvent*);
	void AddBook(int, int);
	bool CorrectBook(QDragEnterEvent*);
	int lastBook;
	int delBook = 0;
	QVector<bool> isFullShelf;

public:
	bool IsFull;
	int widthShelf = 0;
	int CountShelf;
	QVector<int> offset;

	Rack(int countShelf, QWidget* table, QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent*) override;
	void dragEnterEvent(QDragEnterEvent*);
	void dropEvent(QDropEvent* e);

private slots:
	void applyThickness(int);
	void DelBook(int);

signals:
	void deleteBook(int);
};

