#ifndef PLATERECOGNIZE_H
#define PLATERECOGNIZE_H

#include <QMainWindow>

#include "platecategory.h"

namespace Ui {
class PlateRecognize;
}

class PlateRecognize : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlateRecognize(QWidget *parent = nullptr);

    void learnIt();

    void testIt();

    ~PlateRecognize();

private:
    Ui::PlateRecognize *ui;
};

#endif // PLATERECOGNIZE_H
