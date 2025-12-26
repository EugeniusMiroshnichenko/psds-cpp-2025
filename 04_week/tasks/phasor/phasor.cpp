# include <cmath>
#include <iostream>
#include <iomanip>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};


class Phasor;
Phasor operator/(const Phasor& lhs, const Phasor& rhs);

class Phasor {
    public:
        Phasor() = default;

        Phasor(double ampl, double angle){
            SetPolar(ampl, angle);
        }

        Phasor(double ampl, double angle, ExpTag tag){
            (void)tag;
            SetPolar(ampl, angle);
        }

        Phasor(double ampl, double angleDeg, DegTag tag){
            (void)tag;
            SetPolar(ampl, angleDeg * M_PI / 180);
        }

        Phasor(double real, double imag, AlgTag tag){
            (void)tag;
            SetCartesian(real, imag);
        }

        void SetPolar(double ampl, double angle){
            real_ = ampl * cos(angle);
            imag_ = ampl * sin(angle);
        }

        void SetCartesian(double real, double imag){
            real_ = real;
            imag_ = imag;
        }

        double Magnitude() const {
            return sqrt(real_ * real_ + imag_ * imag_);
        }

        double Phase() const {
            return atan2(imag_, real_);
        }

        double PhaseDeg() const {
            double angle_deg = Phase() * 180 / M_PI;
            if (fabs(angle_deg + 180.0) < 1e-12) {
                return 180.0;
            }
            return angle_deg;
        }

        double Real() const {
            return real_;
        }

        double Imag() const {
            return imag_;
        }

        double Abs() const {
            return Magnitude();
        }

        double Angle() const {
            return Phase();
        }

        double AngleDeg() const {
            return PhaseDeg();
        }

        Phasor Conj() const{
            return Phasor(real_, -imag_, AlgTag{});
        }

        Phasor Inv() const{
            return Phasor(1, 0, AlgTag{}) / *this;
        }

    protected:
        double real_ = 0.0;
        double imag_ = 0.0;

};

Phasor operator-(const Phasor& phasor){
    return Phasor(-phasor.Real(), -phasor.Imag(), AlgTag{});
}

Phasor operator+(const Phasor& lhs, const Phasor& rhs){
    return Phasor(lhs.Real() + rhs.Real(), lhs.Imag() + rhs.Imag(), AlgTag{});
}

Phasor operator+(const Phasor& lhs, const double rhs) {
    return Phasor(lhs.Real() + rhs, lhs.Imag(), AlgTag{});
}

Phasor operator+(const double lhs, const Phasor& rhs) {
    return rhs + lhs;
}

Phasor operator-(const Phasor& lhs, const Phasor& rhs){
    return lhs + (-rhs);
}

Phasor operator-(const Phasor& lhs, const double rhs) {
    return Phasor(lhs.Real() - rhs, lhs.Imag(), AlgTag{});
}

Phasor operator-(const double lhs, const Phasor& rhs) {
    return Phasor(lhs - rhs.Real(), -rhs.Imag(), AlgTag{});
}

Phasor operator*(const Phasor& lhs, const Phasor& rhs){
    double real = lhs.Real() * rhs.Real() - lhs.Imag() * rhs.Imag();
    double imag = lhs.Real() * rhs.Imag() + lhs.Imag() * rhs.Real();
    return Phasor(real, imag, AlgTag{});
}

Phasor operator*(const Phasor& lhs, const double rhs) {
    return Phasor(lhs.Real() * rhs, lhs.Imag() * rhs, AlgTag{});
}

Phasor operator*(const double lhs, const Phasor& rhs) {
    return rhs * lhs;
}

Phasor operator/(const Phasor& lhs, const Phasor& rhs){

    double real = (lhs.Real() * rhs.Real() + lhs.Imag() * rhs.Imag()) / pow(rhs.Magnitude(), 2);
    double imag = (-lhs.Real() * rhs.Imag() + lhs.Imag() * rhs.Real()) / pow(rhs.Magnitude(), 2);
    return Phasor(real, imag, AlgTag{});
}

Phasor operator/(const Phasor& lhs, const double rhs) {
    return Phasor(lhs.Real() / rhs, lhs.Imag() / rhs, AlgTag{});
}

Phasor operator/(const double lhs, const Phasor& rhs) {
    return Phasor(lhs, 0, AlgTag{}) / rhs; 
}

Phasor& operator+=(Phasor& lhs, const Phasor& rhs) {
    lhs.SetCartesian(lhs.Real() + rhs.Real(), lhs.Imag() + rhs.Imag());
    return lhs;
}

Phasor& operator-=(Phasor& lhs, const Phasor& rhs) {
    lhs.SetCartesian(lhs.Real() - rhs.Real(), lhs.Imag() - rhs.Imag());
    return lhs;
}

Phasor& operator*=(Phasor& lhs, const Phasor& rhs) {
    lhs.SetCartesian(lhs.Real() * rhs.Real() - lhs.Imag() * rhs.Imag(),
                        lhs.Real() * rhs.Imag() + lhs.Imag() * rhs.Real());
    return lhs;
}

Phasor& operator/=(Phasor& lhs, const Phasor& rhs) {
    lhs.SetCartesian((lhs.Real() * rhs.Real() + lhs.Imag() * rhs.Imag()) / pow(rhs.Magnitude(), 2),
                     (lhs.Imag() * rhs.Real() - lhs.Real() * rhs.Imag()) / pow(rhs.Magnitude(), 2));
    return lhs;
}

bool operator==(const Phasor& lhs, const Phasor& rhs){
    return fabs(lhs.Real() - rhs.Real()) < 1e-9 && fabs(lhs.Imag() - rhs.Imag()) < 1e-9;
}

bool operator!=(const Phasor& lhs, const Phasor& rhs){
    return !(lhs == rhs);
}

std::ostream& operator << (std::ostream& os, const Phasor& phasor){
    os << std::fixed << std::setprecision(3) << phasor.Magnitude() << "*e(j*" << phasor.AngleDeg() << ") [" <<\
        phasor.Real() << " + j*" << phasor.Imag() << "]";
    return os;
}


Phasor MakePhasorCartesian(double real, double imag){
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorPolar(double ampl, double angle){
    return Phasor(ampl, angle, ExpTag{});
}

Phasor MakePhasorPolarDeg(double ampl, double angle){
    return Phasor(ampl, angle, DegTag{});
}