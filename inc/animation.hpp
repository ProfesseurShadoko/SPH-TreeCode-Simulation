#pragma once

#include <tintoretto.hpp>
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>

/**
 * @brief Handles drawing, animation loops, and physical to pixel corredinates.
 */
class Animation {
    private:
        sf::RenderWindow window;
        sf::Clock clock;
        int currentFrame = 0;
    
    public:
        double fps = 60;
        double physicalRadius = 1;
        Eigen::Vector2i phyicalOriginPosition;
        Eigen::Vector3i backgroundColor = {0, 0, 0};
    

    public:
        /**
         * Creates th animation and calls the run function. The frames will be rendere one by one.
         */
        Animation();
    
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
        Eigen::Vector2f physicalToPixelCoordinates(Eigen::Vector2f position);

        /**
         * Based on the physicalRadius of the simulation, this function will draw a circle in the pixel coordinates.
         */
        void drawCircle(Eigen::Vector2f center, double radius, Eigen::Vector3i color);

        /**
         * Based on the physicalRadius of the simulation, this function will draw a line in the pixel coordinates.
         */
        void drawPixel(Eigen::Vector2f position, Eigen::Vector3i color);

};