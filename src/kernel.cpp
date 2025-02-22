#include "kernel.hpp"

// ------------------- //
// !-- Kernel Base --! //
// ------------------- //

double Kernel::operator()(double r) const {
    if (r >= h) {return 0;};
    return W(r/h) / V() / std::pow(h, 3); // Kernel homogenous to L^-3
}

double Kernel::operator()(const Eigen::Vector3d& r) const {
    return (*this)(r.norm());
}

Eigen::Vector3d Kernel::gradient(const Eigen::Vector3d& r) const {
    if (r.norm() >= h || r.norm() == 0.0) return Eigen::Vector3d::Zero();
    return ddr(r.norm() / h) * r.normalized() / V() / std::pow(h, 4); // Kernel derivative homogenous to L^-3 * L^-1
}


double Kernel::computeIntegral() const {
    double s = 0;
    double dr = 0.001; // we can assume spherically symetric kernel in 3d
    for (double r = 0; r < h; r += dr) {
        s += (*this)(r) * 4 * M_PI * r * r * dr;
    }
    return s;
}




// -------------------- //
// !-- LinearKernel --! //
// -------------------- //

double LinearKernel::W(double u) const {
    return 1.0 - u;
}

double LinearKernel::V() const {
    return 1.0/3 * M_PI;
}

double LinearKernel::ddr(double u) const {
    return -1;
}



// --------------------- //
// !-- QuarticKernel --! //
// --------------------- //

double QuarticKernel::W(double u) const {
    if (u >= 1) return 0.0;
    return std::pow(1 - std::pow(u, 2), 2);
}

double QuarticKernel::V() const {
    return 32.0 * M_PI / 105.0;
}

double QuarticKernel::ddr(double u) const {
    return -4.0 * (1 - std::pow(u, 2)) * u;
}