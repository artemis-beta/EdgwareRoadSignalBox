#ifndef ERMAINWINDOW_HXX
#define ERMAINWINDOW_HXX

#include <QMainWindow>
#include <QImage>
#include <QMap>
#include <QSvgWidget>
#include <QSoundEffect>
#include <QScreen>

#include <algorithm>

#include "leverframe.hxx"
#include "blocksection.hxx"
#include "signalindicator.hxx"
#include "signal.hxx"
#include "points.hxx"
#include "interlocking.hxx"
#include "dispatcher.hxx"

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
    EWRB::Dispatcher* _dispatcher = new EWRB::Dispatcher;
    EWRB::LeverFrame* _lever_frame = new EWRB::LeverFrame(this);
    EWRB::InterLocking* _interlocking = new EWRB::InterLocking(_lever_frame);
    QMap<int, QPushButton*> _lever_frame_buttons;
    void _add_indicators();
public:
    void _lever_action(const int& i);
    EWRB::Dispatcher* getDispatcher() const {return _dispatcher;}
};
#endif // ERMAINWINDOW_HXX
