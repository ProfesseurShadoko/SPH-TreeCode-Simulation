#include "frame.hpp"
#include <Eigen/Dense>


/**
 * ------------------------
 * !-- CREATE PARTICLES --!
 * ------------------------
 */

class BouncingParticle {
    private:
        Eigen::Vector2d g = {0, 0};
        Eigen::Vector2d velocity = {0, 0};
    
    public:
        static inline const std::vector<double> box = {-10, 10, -10, 10}; // x_min, x_max, y_min, y_max // all particles will be inside the same box and bounce!

        Eigen::Vector3i color = {255, 255, 255};
        double radius = 0.1;
        Eigen::Vector2d position = {0, 0};
    
    void resolveCollisions() {
        if (position[0] - radius < box[0]) {
            position[0] = box[0] + radius;
            velocity[0] = -velocity[0];
        }
        if (position[0] + radius > box[1]) {
            position[0] = box[1] - radius;
            velocity[0] = -velocity[0];
        }
        if (position[1] - radius < box[2]) {
            position[1] = box[2] + radius;
            velocity[1] = -velocity[1];
        }
        if (position[1] + radius > box[3]) {
            position[1] = box[3] - radius;
            velocity[1] = -velocity[1];
        }
    }

    void update(double dt) {
        velocity += g * dt;
        position += velocity * dt;
        resolveCollisions();
    }

    void print() {
        std::cout << "Particle at " << position[0] << ", " << position[1] << " with velocity " << velocity[0] << ", " << velocity[1] << std::endl;
    }

    static BouncingParticle random() {
        BouncingParticle particle;
        particle.position = Eigen::Vector2d(
            box[0] + (rand() % 1000) / 1000.0 * (box[1] - box[0]),
            box[2] + (rand() % 1000) / 1000.0 * (box[3] - box[2])
        );
        particle.velocity = Eigen::Vector2d(
            (rand() % 1000 - 500) / 100.0,
            (rand() % 1000 - 500) / 100.0
        );
        particle.color = Eigen::Vector3i(rand() % 256, rand() % 256, rand() % 256);

        return particle;
    }
};

/**
 * ---------------------
 * !-- CREATE FRAMES --!
 * ---------------------
 */

class ParticleFrame : public Frame {
    std::vector<BouncingParticle> particles;

    public:
        ParticleFrame(std::vector<BouncingParticle> particles) : particles(particles) {};

        void draw() {
            for (BouncingParticle particle : particles) {
                drawCircle(particle.position, particle.radius, particle.color);
            }
        }

        void configWindow() {
            setBackgroundColor(Eigen::Vector3i(0, 0, 0));
            setFps(60);
            setPhysicalRadius(10);
        }
};


/*
 class MyFrame : public Frame {
    std::vector<MyParticle> particles;

    public:
        MyFrame(std::vector<MyParticle> particles) : particles(particles) {};

        void draw() {
            for (MyParticle particle : particles) {
                drawCircle(particle.position, particle.radius, particle.color());
            }
        };

        void configWindow() {
            setBackgroundColor(Eigen::Vector3i(0, 0, 0));
            setFps(60);
            setPhysicalRadius(10);            
        };

        static std::vector<std::shared_ptr<Frame>> createFrames() {
            std::vector<std::shared_ptr<Frame>> frames;
            int n_frames = 600; // 60 fps => 10s clip
            int n_particles = 10; // let's draw 10 particles each time
            std::vector<MyParticle> particles;
            for (int i = 0; i < n_particles; i++) {
                particles.push_back(MyParticle::random());
            }

            // let's create the frames!
            for (int i = 0; i < n_frames; i++) {                
                MyFrame frame(particles); // for now the particles don't move, we will make them move later!
                frames.push_back(
                    // transform the frame into a shared pointer
                    std::make_shared<MyFrame>(frame)
                );
            }
            return frames;
        }
        


 };*/

int main() {
    std::vector<ParticleFrame> frames; // let's start with this. we will convert them into shared pointers later

    /**
     * --------------------------------
     * !-- Create Initial Particles --!
     * -------------------------------- 
     */
    std::vector<BouncingParticle> particles;
    int n_particles = 1000;

    for (int i = 0; i < n_particles; i++) {
        particles.push_back(BouncingParticle::random());
        particles[i].print();
    }


    /**
     * ---------------------
     * !-- Create Frames --!
     * ---------------------
     */
    int n_frames = 6000; // 60 fps => 100s clip
    double dt = 1.0 / 60.0; // 60 fps;
    for (int i = 0; i < n_frames; i++) {
        ParticleFrame frame(particles);
        frames.push_back(frame);
        for (int j = 0; j < n_particles; j++) {
            particles[j].update(dt);
        }
    }

    /**
     * ---------------------
     * !-- Run Animation --!
     * ---------------------
     */

    // convert frames into pointers
    std::vector<std::shared_ptr<Frame>> shared_frames;
    for (ParticleFrame frame : frames) {
        shared_frames.push_back(std::make_shared<ParticleFrame>(frame));
    }

    Frame::runAnimation(shared_frames);

    return 0;
}