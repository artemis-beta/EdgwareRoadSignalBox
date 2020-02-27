#ifndef FRAMELEVER_HXX
#define FRAMELEVER_HXX

#include <QMainWindow>
#include <QSvgWidget>
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QPushButton>
#include <QSoundEffect>
#include <QSound>
#include <QTimer>

#include "global_params.hxx"

namespace EWRB
{
    class FrameLever;

    class PointsChange : public QObject
    {
        Q_OBJECT
        private:
            FrameLever* _parent;
            QSoundEffect* _sound_effect = new QSoundEffect;
            QTimer* _timer = new QTimer();
            bool _sound_finished = false;
        public:
            PointsChange(FrameLever* _parent);
            bool getState();
            void run()
            {
                _sound_finished = false;
                _sound_effect->play();
                _timer->start(2000);
            }
        public slots:
            void timerEnded()
            {
                if(_sound_finished) emit soundFinished();
                _sound_finished = false;
            }

        signals:
            void soundFinished();
    };

    class FrameLever : public QObject
    {
        Q_OBJECT
        private:
            QWidget* _parent = nullptr;
            QMap<LeverState, QSvgWidget*> _svgs = {{}};
            PointsChange* _points_change = new PointsChange(this);
            EWRB::LeverType _type;
            int _coords[2] = {0,0};
            bool _locked = false;
            LeverState _current_state = LeverState::Off, _prev_state= EWRB::LeverState::Off;
        public:
            FrameLever(){}
            FrameLever(const QString& lever_name, QWidget* parent, EWRB::LeverType type) :
                _parent(parent), _type(type)
            {
                connect(_points_change, SIGNAL(soundFinished()), this, SLOT(pointsChangedFinished()));
                _svgs[LeverState::Off] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverBack.svg"), _parent);
                _svgs[LeverState::Off]->setFixedSize(25, 100);
                _svgs[LeverState::Off]->hide();
                _svgs[LeverState::Mid] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverMid.svg"), _parent);
                _svgs[LeverState::Mid]->setFixedSize(25, 100);
                _svgs[LeverState::Mid]->hide();
                _svgs[LeverState::On] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverForward.svg"), _parent);
                _svgs[LeverState::On]->setFixedSize(25, 100);
                _svgs[LeverState::On]->hide();
            }
            EWRB::LeverState reverse(EWRB::LeverState state) const
            {
                return (state == EWRB::LeverState::On) ? EWRB::LeverState::Off : EWRB::LeverState::On;
            }
            QSvgWidget* getWidget() const {return _svgs[_current_state];}
            void PlaceAt(const int& x, const int& y);
            void hideSVG();
            void showSVG();
            void moveLever(EWRB::LeverState state = EWRB::LeverState::Off, bool points_delay=false);
            void Lock(bool lock_lever) {_locked = lock_lever;}
            bool isLocked() const {return _locked;}
            EWRB::LeverType getType() const {return _type;}
            EWRB::LeverState getState() const {return _current_state;}
        public slots:
            void pointsChangedFinished();
    };

    class HomeLever : public FrameLever
    {
        public:
            HomeLever(QWidget* parent) : FrameLever(QString("Red"), parent, EWRB::LeverType::Signal) {}
    };

    class PointsLever : public FrameLever
    {
        public:
            PointsLever(QWidget* parent) : FrameLever(QString("Black"), parent, EWRB::LeverType::Points){}
    };

    class EmergencySignalReleaseLever : public FrameLever
    {
        public:
            EmergencySignalReleaseLever(QWidget* parent) : FrameLever(QString("Yellow"), parent, EWRB::LeverType::Points){}
    };

    class SpareLever : public FrameLever
    {
        public:
            SpareLever(QWidget* parent) : FrameLever(QString("White"), parent, EWRB::LeverType::Points){}
    };
};



#endif // FRAMELEVER_HXX
