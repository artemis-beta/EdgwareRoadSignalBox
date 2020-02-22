#ifndef ERMAINWINDOW_HXX
#define ERMAINWINDOW_HXX

#include <QMainWindow>
#include <QImage>
#include <QMap>
#include <QSvgWidget>
#include <QSoundEffect>

#include <algorithm>

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
    QList<QSoundEffect*> _lever_sounds;
    EWRB::LeverFrame* _lever_frame = new EWRB::LeverFrame(this);
    QMap<int, QPushButton*> _lever_frame_buttons;
    void _play_random_lever_sound();
public slots:
    void _lever_action(const int& i);
};
#endif // ERMAINWINDOW_HXX
