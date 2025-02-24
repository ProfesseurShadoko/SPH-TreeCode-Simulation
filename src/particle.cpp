#include "particle.hpp"
#include <string>


Particle::Particle(std::initializer_list<double> init) {
    position = Eigen::Vector3d::Zero();
    velocity = Eigen::Vector3d::Zero();
    mass = 1.0;

    if (init.size() == 3) {
        position = Eigen::Vector3d(*(init.begin()), *(init.begin() + 1), *(init.begin() + 2));
    } else if (init.size() == 6) {
        position = Eigen::Vector3d(*(init.begin()), *(init.begin() + 1), *(init.begin() + 2));
        velocity = Eigen::Vector3d(*(init.begin() + 3), *(init.begin() + 4), *(init.begin() + 5));
    } else if (init.size() == 7) {
        position = Eigen::Vector3d(*(init.begin()), *(init.begin() + 1), *(init.begin() + 2));
        velocity = Eigen::Vector3d(*(init.begin() + 3), *(init.begin() + 4), *(init.begin() + 5));
        mass = *(init.begin() + 6);
    } else {
        throw std::invalid_argument("Invalid number of arguments. Must be 3, 6 or 7.");
    }
    id = id_counter++;
}


Particle::Particle(const Particle& p) {
    position = p.position;
    velocity = p.velocity;
    mass = p.mass;
    id = p.id;
}

void Particle::display() {
    Message::print(
        cstr("Particle").blue() + "<" + cstr(id).green() + ">:"
    );
    Message::tab();
    Message::print(
        "- Position: " + std::to_string(position.x()) + ", " + std::to_string(position.y()) + ", " + std::to_string(position.z())
    );
    Message::print(
        "- Velocity: " + std::to_string(velocity.x()) + ", " + std::to_string(velocity.y()) + ", " + std::to_string(velocity.z())
    );
    Message::print(
        "- Mass: " + std::to_string(mass)
    );
    Message::print(
        "- Time: " + std::to_string(current_time)
    );
    Message::untab();
}