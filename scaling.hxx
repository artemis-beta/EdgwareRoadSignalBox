#ifndef SCALING_HXX
#define SCALING_HXX

#include <QScreen>
#include <QGuiApplication>

namespace EWRB {
    class Scaler {
        private:
            const float model_width_ = 1020;
            const float model_height_ = 600;
            int screen_width_;
            int screen_height_;
        public:
            Scaler() {
                const QScreen *screen_ = QGuiApplication::primaryScreen();
                const QRect screen_size_ = screen_->geometry();
                screen_height_ = screen_size_.height()*0.98;
                screen_width_ = (model_width_/model_height_)*screen_height_;
            }

            float scale_width(float width) const {
                return (screen_width_/model_width_)*width;
            }

            float scale_height(float height) const {
                return (screen_height_/model_height_)*height;
            }
            float screen_width() const {return screen_width_;}
            float screen_height() const {return screen_height_;}
    };
};

#endif // SCALING_HXX
