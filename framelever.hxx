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
            double _scale_factor = 1.;
            int _coords[2] = {0,0};
            bool _locked = false;
            LeverState _current_state = LeverState::Off;
        public:
            FrameLever(const QString& lever_name, QWidget* parent, const double scale_fac=1) :
                _scale_factor(scale_fac), _parent(parent)
            {
                _svgs[LeverState::Off] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverBack.svg"), _parent);
                _svgs[LeverState::Off]->setFixedSize(25, 100);
                _svgs[LeverState::Off]->hide();
                _svgs[LeverState::On] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverForward.svg"), _parent);
                _svgs[LeverState::On]->setFixedSize(25, 100);
                _svgs[LeverState::On]->hide();
            }
            QSvgWidget* getWidget() const {return _svgs[_current_state];}
            void Scale(double& scale_factor){_scale_factor *= scale_factor;}
            void PlaceAt(const int& x, const int& y);
            void hideSVG();
            void showSVG();
            void moveLever();
            void Lock(bool lock_lever) {_locked = lock_lever;}
            bool isLocked() const {return _locked;}
            EWRB::LeverState getState() const {return _current_state;}
    };

    class HomeLever : public FrameLever
    {
        public:
            HomeLever(QWidget* parent) : FrameLever(QString("Red"), parent) {}
    };

    class PointsLever : public FrameLever
    {
        public:
            PointsLever(QWidget* parent) : FrameLever(QString("Black"), parent) {}
    };
};



#endif // FRAMELEVER_HXX
