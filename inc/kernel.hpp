#pragma once

#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <cmath>



// ------------------- //
// !-- Kernel Base --! //
// ------------------- //

/**
 * @brief virtual class to implement kernel for SPH
 * 
 * User must implement the virtual function the following way:
 * ```cpp
 * class MyKernel : public Kernel {
 *      //initialize smoothing radius
 *      MyKernel(...) : Kernel(smoothingRadius);
 * 
 *      // define the kernel function (is not necessarly of integral 1, but its volume must be given in getVolume())
 *      double operator()(double r) const = 0;
 * 
 *      // define its derivative
 *      double ddr(double r) const;
 * 
 *      // define the integral of the kernel over the smoothing radius
 *      double getVolume() const;
 * }
 * ```
 * 
 */
class Kernel {
    protected:
        const double h; // smoothing radius
    
    public:
        //constructor 
        Kernel(double smoothingRadius) : h(smoothingRadius){};


        double operator()(double r) const;
        double operator()(const Eigen::Vector3d& r) const;

        Eigen::Vector3d gradient(const Eigen::Vector3d& r) const;

        double getSmoothingRadius() const {return h;}

        /**
         * @brief Computes the integral of the Kernel over the sphere defined by the smoothin radius. For debugging purpous, should return 1
         */
        double computeIntegral() const;
        

    // --------------- //
    // !-- Virtual --! //
    // --------------- //
    private:
        /**
         * @brief Any Kernel function (allowed not to be normalized). However, its integral
         * over the unit sphere must be defined in V();
         */
        virtual double W(double u) const = 0;

        /**
         * @brief The derivative of the kernel function w.r.t. r
         */
        virtual double ddr(double u) const = 0;

        /**
         * @brief Defines the volume of the Kernel. Is actually only called once, by the constructor of Kernel
         */
        virtual double V() const = 0;
        
};



class LinearKernel : public Kernel {
    public:
        LinearKernel(double smoothingRadius) : Kernel(smoothingRadius) {};

        double W(double u) const;
        double ddr(double u) const;
        double V() const;
};


class QuarticKernel : public Kernel {
    public: 
        QuarticKernel(double smoothingRadius) : Kernel(smoothingRadius) {};

        double W(double u) const;
        double ddr(double u) const;
        double V() const;
};


