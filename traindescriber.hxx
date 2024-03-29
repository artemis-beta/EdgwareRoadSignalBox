#ifndef TRAINDESCRIBER_HXX
#define TRAINDESCRIBER_HXX

#include <QSvgWidget>
#include <QMap>
#include <QScreen>
#include <QGuiApplication>

#include "dispatcher.hxx"
#include "scaling.hxx"

namespace EWRB
{
    class TrainDescriber
    {
        private:
            QWidget* _parent;
            bool _illuminated = false;
            Dispatcher* _dispatcher;
            int _location[2] = {0,0};
            int _id = -1;
            QMap<bool, QSvgWidget*> _svgs;
        public:
            TrainDescriber(const int& id, Dispatcher* dispatcher, QWidget* parent, QString type) : _id(id), _dispatcher(dispatcher), _parent(parent)
            {
                const Scaler* scaler_ = new Scaler;
                _svgs[false] = new QSvgWidget(":/svgs/svgs/TrainDescriberOff.svg", parent);
                _svgs[false]->setFixedSize(scaler_->scale_width(37), scaler_->scale_height(35));
                _svgs[true] = new QSvgWidget(":/svgs/svgs/TrainDescriber"+type+".svg", parent);
                _svgs[true]->setFixedSize(scaler_->scale_width(37), scaler_->scale_height(35));
            }
            bool isOn() const {return _illuminated;}
            void PlaceAt(const int& x, const int& y);
            void update();
            int id() const {return _id;}
    };
};

#endif // TRAINDESCRIBER_HXX
