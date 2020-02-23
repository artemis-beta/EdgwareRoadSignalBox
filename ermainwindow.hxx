#ifndef ERMAINWINDOW_HXX
#define ERMAINWINDOW_HXX

#include <QMainWindow>
#include <QImage>
#include <QMap>
#include <QSvgWidget>
#include <QSoundEffect>

#include <algorithm>

#include "leverframe.hxx"
#include "blocksection.hxx"
#include "signal.hxx"

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
    QSoundEffect* _lever_failed = new QSoundEffect;
    EWRB::LeverFrame* _lever_frame = new EWRB::LeverFrame(this);
    QMap<int, QPushButton*> _lever_frame_buttons;
    QMap<int, EWRB::BlockSection*> _block_sections;
    QMap<int, EWRB::Signal*> _signals;
    void _play_random_lever_sound();
    void _setup_block_sections();
    void _add_signals();
public slots:
    void _lever_action(const int& i);
};
#endif // ERMAINWINDOW_HXX
