#include "Table.h"
#include <qevent.h>
#include <qmimedata.h>

Table::Table(QWidget* Sender, int countStack, QWidget* parent) : QWidget(parent), countStack(countStack)
{
	setAcceptDrops(true);
	setObjectName("Table");
	connect(Sender, SIGNAL(complete()), this, SLOT(deferredInit()));
}

void Table::paintEvent(QPaintEvent*)
{
	QLine lines[3];
	lines[0] = QLine(50, this->height() - 10, 50, this->height() - 100);
	lines[1] = QLine(25, this->height() - 100, this->width() - 25, this->height() - 100);
	lines[2] = QLine(this->width() - 50, this->height() - 10, this->width() - 50, this->height() - 100);
	QPainter painter;
	painter.begin(this);
	painter.drawLines(lines, 3);
	painter.end();
}

void Table::dragEnterEvent(QDragEnterEvent* e)
{
	e->acceptProposedAction();
}

void Table::dropEvent(QDropEvent* e)
{
	if (e->mimeData()->hasText())
	{
		QStringList spl = e->mimeData()->text().split(" ");
		int numVol = spl[0].toInt();
		int thick = spl[1].toInt();
		if (spl[2] == "Rack")
			emit removeFromRack(numVol);
		int NumStack = (e->pos().x() + 200) / (width() / 6) - 1;
		qDebug() << NumStack;
		AddBook(thick, numVol, NumStack);
	}
}

void Table::checkBook(int numVol)
{
	bool ans = false;
	for (size_t i = 0; i < stack.count(); i++)
	{
		if (!stack[i].isEmpty() && numVol == stack[i].last()->NumVolume)
		{
			ans = true;
			emit answer(ans);
			break;
		}
	}
	if (!ans)
		emit answer(ans);
}

void Table::AddBook(int thick, int Vol, int numStack)
{
	DeleteBook(Vol);
	Book* book = new Book(thick, Vol, this);
	stack[numStack].append(book);
	book->setGeometry(
		Book::Width * 4 * numStack + 100,
		height() - 100 - offset[numStack] - book->Thickness,
		Book::Width,
		book->Thickness);

	book->show();
	book->repaint();
	offset[numStack] += book->Thickness + 1;
	connect(book, SIGNAL(checkAvailability(int)), this, SLOT(checkBook(int)));
	connect(this, SIGNAL(answer(bool)), book, SLOT(recieve(bool)));
}

void Table::deferredInit() //Модуль лишний, созданный чтобы устранить ошибку при вызове ф-ций width(), height(), не решает данную проблему
{
	int thickness = 0;
	stack = QVector<QVector<Book*>>();
	for (size_t i = 0; i < MaxStacks; i++)
	{
		stack.append(QVector<Book*>());
		offset.append(0);
	}

	for (size_t i = 0; i < 30; i++)
	{
		int ind = rand() % countStack + 1;
		Book* book = new Book(this);
		stack[ind].append(book);

		book->setGeometry(
			Book::Width * 4 * ind + 100,
			height() * 3 - 121 - offset[ind] - book->Thickness,
			Book::Width,
			book->Thickness);

		thickness += book->Thickness;
		offset[ind] += book->Thickness + 1;

		connect(book, SIGNAL(checkAvailability(int)), this, SLOT(checkBook(int)));
		connect(this, SIGNAL(answer(bool)), book, SLOT(recieve(bool)));
	}

	emit calculatedThickness(thickness);
}

void Table::DeleteBook(int numVol)
{
	for (size_t i = 0; i < stack.count(); i++)
	{
		if (!stack[i].isEmpty() && numVol == stack[i].last()->NumVolume)
		{
			offset[i] -= stack[i].last()->Thickness + 1;
			delete stack[i].last();
			stack[i].removeLast();
			break;
		}
	}
}
