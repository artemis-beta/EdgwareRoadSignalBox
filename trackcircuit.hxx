#ifndef TRACKCIRCUIT_HXX
#define TRACKCIRCUIT_HXX

#include <QSvgWidget>
#include <QSoundEffect>
#include <QMap>
#include <QDebug>

#include "global_params.hxx"

namespace EWRB {
    class TrackCircuit {
    private:
        TrackCircuitStatus state_ = TrackCircuitStatus::Clear;
        const QString label_ = "";
        QSvgWidget* lit_ = nullptr;
        QSoundEffect* indicator_sound_ = new QSoundEffect;
        int position_[2] = {0, 0};
    public:
        TrackCircuit(const QString& label, QWidget* parent, const QString& image_path) : label_(label), lit_(new QSvgWidget(image_path, parent)) {
            indicator_sound_->setSource(QUrl::fromLocalFile(":/audio/audio/track_circuit_indicator.wav"));
        }
        void PlaceAt(const int& x, const int& y){
            position_[0] = x; position_[1] = y;
            lit_->move(x, y);
        }
        void SetSize(const int& x, const int& y) {
            lit_->setFixedSize(x, y);
        }
        void update() {
            if(state_ == TrackCircuitStatus::Clear) lit_->show();
            else lit_->hide();
        }
        TrackCircuitStatus getState() const {
            return state_;
        }
        void SetState(TrackCircuitStatus state) {
            state_ = state;
            update();
        }
    };

    QMap<QString, TrackCircuit*> TrackCircuits(QWidget* parent);
};

#endif // TRACKCIRCUIT_HXX
