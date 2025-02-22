#include "kernel.hpp"
#include <tintoretto.hpp>
#include <typeinfo>


void testKernel(Kernel& kernel, std::string className) { // you need to pass addres here since Kernel can't be constructed or copied => it's virtual
    
    // let's compute the integral of the kernel
    Test test(className + " integral = 1");
    test.complete(
        std::abs(1.0 - kernel.computeIntegral()) < 1e-6
    );

    Test test2(className + " gradient");
    // let's compute the gradient of the kernel at 27% & 18% of smoothing radius
    double h = kernel.getSmoothingRadius();
    Eigen::Vector3d r = Eigen::Vector3d(0.25, 0.17, 0.10) * h;
    Eigen::Vector3d grad = kernel.gradient(r);

    // let's compute the gradient by hand
    double d = 1e-6 * h;

    Eigen::Vector3d dx, dy, dz;

    dx = Eigen::Vector3d(d, 0.0, 0.0);
    dy = Eigen::Vector3d(0.0, d, 0.0);
    dz = Eigen::Vector3d(0.0, 0.0, d);

    Eigen::Vector3d grad_custom = {
        (kernel(r + dx) - kernel(r - dx)) / (2 * d),
        (kernel(r + dy) - kernel(r - dy)) / (2 * d),
        (kernel(r + dz) - kernel(r - dz)) / (2 * d)
    };

    // let's compare the two gradients
    test2.complete(
        (grad - grad_custom).norm() < 1e-6
    );
}


int main() {
    double h = 10.0;
    LinearKernel lkernel(h);
    testKernel(lkernel, "LinearKernel");
    QuarticKernel qkernel(h);
    testKernel(qkernel, "QuarticKernel");
}



