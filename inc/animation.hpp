#pragma once

#include <tintoretto.hpp>
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <vector>
#include <memory>

// forward definition of Frame to avoid circular imports
class Frame;

/**
 * @brief Handles drawing, animation loops, and physical to pixel corredinates. It takes a vector of frames and renders them one by one
 * by calling the draw method of the current frame.
 */
class Animation {
    private:
        sf::RenderWindow window;
        sf::Clock clock;
        int currentFrame = 0;
        // std::vector<Frame> frames; // we c'ant do that, the class expects Frame but Frame is virtual, only children classes will be passed here, hence we need to use smart pointers
        std::vector<std::shared_ptr<Frame>> frames;

    public:
        double fps = 60;
        double physicalRadius = 1;
        Eigen::Vector2d phyicalOriginPosition; // maybe using integer here would be wiser? idk
        Eigen::Vector3i backgroundColor = {0, 0, 0};
    

    public:
        /**
         * Creates th animation and calls the run function. The frames will be rendere one by one.
         * We need to use shared pointers because the Frame class is virtual => we need polymorphism => this functions needs to 
         * be able to accept children of the frame class => hence we need to use shared pointers.
         */
        Animation(std::vector<std::shared_ptr<Frame>> frames);
    
    /**
     * ------------------
     * !-- EVENT LOOP --!
     * ------------------
     */
    private:
        /**
         * @brief Main loop of the program. Handle events, call render, wait for next frame.
         */
        void run();

        /**
         * @brief Draws the current frame by calling the frame's render function. Also fills background color.
         */
        void render();


        void wait();

    private:
        void handleEvents();

    /**
     * -------------------------
     * !-- DRAWING FUNCTIONS --!
     * -------------------------
     */
        /**
         * @brief Translates a distance in the physical world into a distance in pixels.
         * 
         * @returns window.getSize().y / (2 * physicalRadius) * distance
         */
        double physicalToPixelDistance(double distance);

        /**
         * @brief Translates a coordinate into a pixel corrdinate (by applying physicalToPixelDistance to each component, and switching the y axis).
         */
        Eigen::Vector2d physicalToPixelCoordinates(Eigen::Vector2d position);

    public:
        /**
         * Based on the physicalRadius of the simulation, this function will draw a circle in the pixel coordinates.
         */
        void drawCircle(Eigen::Vector2d center, double radius, Eigen::Vector3i color);

        /**
         * Based on the physicalRadius of the simulation, this function will draw a line in the pixel coordinates.
         */
        void drawPixel(Eigen::Vector2d position, Eigen::Vector3i color);

};