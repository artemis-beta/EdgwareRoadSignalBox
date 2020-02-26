#ifndef FRAMELEVER_HXX
#define FRAMELEVER_HXX

#include <QMainWindow>
#include <QSvgWidget>
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QPushButton>

#include "global_params.hxx"

namespace EWRB
{
    class FrameLever
    {
        private:
            QWidget* _parent = nullptr;
            QMap<LeverState, QSvgWidget*> _svgs = {{}};
            EWRB::LeverType _type;
            int _coords[2] = {0,0};
            bool _locked = false;
            LeverState _current_state = LeverState::Off, _prev_state= EWRB::LeverState::Off;
        public:
            FrameLever(){}
            FrameLever(const QString& lever_name, QWidget* parent, EWRB::LeverType type) :
                _parent(parent), _type(type)
            {
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
            void moveLever(EWRB::LeverState state = EWRB::LeverState::Off);
            void Lock(bool lock_lever) {_locked = lock_lever;}
            bool isLocked() const {return _locked;}
            EWRB::LeverType getType() const {return _type;}
            EWRB::LeverState getState() const {return _current_state;}
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
