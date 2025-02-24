#pragma once

#include <tintoretto.hpp>
#include <Eigen/Dense>
#include <initializer_list>


class Particle {
    public:
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        double mass;
        double current_time = 0;
    
    private:
        static inline int id_counter = 0;
        int id;

    public:
        Particle(Eigen::Vector3d position = Eigen::Vector3d::Zero(), Eigen::Vector3d velocity = Eigen::Vector3d::Zero(), double mass = 1.0) : position(position), velocity(velocity), mass(mass), id(id_counter++) {};
        Particle(std::initializer_list<double> init);
        /**
         * Copy constructor! Copy the id of the particle
         * alongside all other attributes!!
         */
        Particle(const Particle& p);

        /**
         * @brief Compares id of particles. Does not compare particle positions however!
         * Moreover, equality survives the copy constructor:
         * ```cpp
         * particle == Particle(particle) // true
         * ```
         */
        bool operator==(const Particle& p) const {return id == p.id;}

        /**
         * @brief Prints the particle (position, velocity, etc.) into the terminal
         */
        void display();

};