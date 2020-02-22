#ifndef FRAMELEVER_HXX
#define FRAMELEVER_HXX

#include <QMainWindow>
#include <QSvgWidget>
#include <QMap>

namespace EWRB
{
    enum class State
    {
        Off,
        On
    };

    class FrameLever
    {
        private:
            QWidget* _parent = nullptr;
            QMap<State, QSvgWidget*> _svgs = {{}};
            double _scale_factor = 1.;
            int _coords[2] = {0,0};
            State _current_state = State::Off;
        public:
            FrameLever(const QString& lever_name, QWidget* parent, const double scale_fac=1) :
                _parent(parent), _scale_factor(scale_fac)
            {
                _svgs[State::Off] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverBack.svg"), _parent);
                _svgs[State::Off]->setFixedSize(20, 80);
                _svgs[State::Off]->hide();
                _svgs[State::On] = new QSvgWidget(QString(":/svgs/svgs/")+lever_name+QString("_LeverForward.svg"), _parent);
                _svgs[State::On]->setFixedSize(20, 80);
                _svgs[State::On]->hide();
            }
            QSvgWidget* getWidget() const {return _svgs[_current_state];}
            void Scale(double& scale_factor){_scale_factor *= scale_factor;}
            void PlaceAt(const int& x, const int& y)
            {
                _coords[0] = x; _coords[1] = y;

                for(auto svg : _svgs) svg->move(_coords[0], _coords[1]);
            }

            void hide()
            {
                _svgs[_current_state]->hide();
            }

            void show()
            {
                _svgs[_current_state]->show();
            }
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