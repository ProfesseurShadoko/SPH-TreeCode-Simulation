
#include "particleSet.hpp"
#include <tintoretto.hpp>


/**
 * ----------------------------------------
 * !-- Constructor, destructor, wrapper --!
 * ----------------------------------------
 */

ParticleSet::ParticleSet() {
    particles = std::vector<Particle>();
}

ParticleSet::ParticleSet(std::initializer_list<Particle> init) {
    particles = std::vector<Particle>(init);
}

ParticleSet::ParticleSet(const ParticleSet& ps) {
    this->particles = ps.particles; // this is indeed a deep copy because std::vector does deep copy on its own
}

void ParticleSet::add(Particle p) {
    particles.push_back(p); // a copy is made since the particle is passed by value
}

void ParticleSet::add(ParticleSet& ps) {
    for (int i = 0; i < ps.size(); i++) {
        add(ps.get(i)); // a copy is made since the particle is passed by value
    }
}

Particle& ParticleSet::get(int i) {
    return particles[i];
}

int ParticleSet::size() const {
    return particles.size();
}


/**
 * ---------------
 * !-- Display --!
 * ---------------
 */
void ParticleSet::display() {
    Message::print(cstr("ParticleSet").blue() + " <" + cstr("#").green() + cstr(size()).green() + ">:");
    Message::tab();
    Message::print("- Total mass: " + std::to_string(getTotalMass()));
    Message::print("- Center of mass: " + std::to_string(getCenterOfMass().norm()) + " (distance from origin)");
    Message::print("- Center of mass velocity: " + std::to_string(getCenterOfMassVelocity().norm()));
    Message::print("- Diameter: " + std::to_string(getDiameter()));
    Message::untab();
}


/**
 * ----------------------
 * !-- Apply to all p --!
 * ----------------------
 */

void ParticleSet::updateCurrentTime(double dt) {
    for (int i = 0; i < size(); i++) {
        get(i).current_time += dt;
    }
}

void ParticleSet::com() {
    Eigen::Vector3d com = getCenterOfMass();
    Eigen::Vector3d com_velocity = getCenterOfMassVelocity();
    for (int i = 0; i < size(); i++) {
        get(i).position -= com;
        get(i).velocity -= com_velocity;
    }
}


/**
 * -------------------------
 * !-- Private Functions --!
 * -------------------------
 */

double ParticleSet::getTotalMass() {
    double total_mass = 0;
    for (int i = 0; i < size(); i++) {
        total_mass += get(i).mass;
    }
    return total_mass;
}

Eigen::Vector3d ParticleSet::getCenterOfMass() {
    double total_mass = getTotalMass();
    Eigen::Vector3d center_of_mass = Eigen::Vector3d::Zero();
    for (int i = 0; i < size(); i++) {
        center_of_mass += get(i).mass * get(i).position;
    }
    return center_of_mass / total_mass;
}

Eigen::Vector3d ParticleSet::getCenterOfMassVelocity() {
    double total_mass = getTotalMass();
    Eigen::Vector3d center_of_mass_velocity = Eigen::Vector3d::Zero();
    for (int i = 0; i < size(); i++) {
        center_of_mass_velocity += get(i).mass * get(i).velocity;
    }
    return center_of_mass_velocity / total_mass;
}

double ParticleSet::getDiameter() {
    double diameter = 0;
    Eigen::Vector3d com = getCenterOfMass();
    for (int i = 0; i < size(); i++) {
        diameter = std::max(diameter, (get(i).position - com).norm());
    }
    return diameter * 2;
};