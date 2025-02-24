#pragma once

#include "particle.hpp"
#include <vector>
#include <tintoretto.hpp>
#include <initializer_list>


/**
 * Handles a set of particles. This class is just a wrapper around a vector of particles.
 * The idea is to always use the method get(int i) that returns in place particle.
 * 
 * On the other hand, every particle passed into a particleSet is copied.
 */
class ParticleSet {
    public:
        std::vector<Particle> particles;

        ParticleSet();
        ParticleSet(std::initializer_list<Particle> init);

        /**
         * Copy constructor (deep copy! each particle is copied!)
         */
        ParticleSet(const ParticleSet& p);

        /**
         * @brief Copy and add a particle to the set.
         */
        void add(const Particle p); // a copy is made since the particle is passed by value

        /**
         * @brief Add a particle set to the particle set.
         * 
         * Every particle inside is copied => no more inplace modification. 
         * Very usefull to take a 'picture' of the curret set of particles.
         */
        void add(ParticleSet& ps);

        /**
         * @brief Get a particle in place. 
         *
         * @param i index of the particle
         * @return Particle& reference to the particle
         */
        Particle& get(int i);

        /**
         * @brief Number of particles in the set
         */
        int size() const;

        /**
         * @brief Show some statistics of the particle set i nthe terminal
         */
        void display();

        /**
         * @brief Update every particle time by dt.
         */
        void updateCurrentTime(double dt);

        /**
         * @brief Split the set into all distinct time steps. Assumes particles are sorted in time though.
         */
        std::vector<ParticleSet> split();

        /**
         * @brief Slice. If start greater than end (eg if end = -1), all particles are added. Returns copies.
         */
        ParticleSet slice(int start, int end);

        /**
         * @brief Take the first n particles. Returns copies.
         */
        ParticleSet slice(int n);

        /**
         * @brief Take the first n particles but keep the mass of the system constant (by scaling all masses up). Returns copies.
         */
        ParticleSet slice_m(int n);

        /**
         * @brief Changes velocities and positions to be in the center of mass frame, with center of mass on the origin.
         */
        void com();

        /**
         * @brief Returns random particles in the unit cube.
         */
        static ParticleSet random(int n);

        /**
         * @brief Returns random particles inside the unit sphere.
         */
        static ParticleSet random_sphere(int n);

        /**
         * @brief Exports to a csv file, with header, no index (but the running id from the particle though).
         */
        void export_csv(std::string filename);

        /**
         * @brief Load csv file.
         */
        static ParticleSet load_csv(std::string filename);
    

    private:
        double getTotalMass();
        double getDiameter();
        Eigen::Vector3d getCenterOfMass();
        Eigen::Vector3d getCenterOfMassVelocity();
};