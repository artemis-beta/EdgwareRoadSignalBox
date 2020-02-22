#ifndef ERMAINWINDOW_HXX
#define ERMAINWINDOW_HXX

#include <QMainWindow>
#include <QImage>
#include <QMap>
#include <QSvgWidget>

#include "leverframe.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class ERMainWindow; }
QT_END_NAMESPACE

class ERMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ERMainWindow(QWidget *parent = nullptr);
    ~ERMainWindow();

private:
    Ui::ERMainWindow *ui;
    EWRB::LeverFrame* _lever_frame = new EWRB::LeverFrame(this);
};
#endif // ERMAINWINDOW_HXX
