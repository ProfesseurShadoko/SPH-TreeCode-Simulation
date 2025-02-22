#pragma once

#include <tintoretto.hpp>
#include "animation.hpp"
#include <Eigen/Dense>
#include <memory>

/**
 * @brief Virtual class that can be drawn in an animation. To run an animation,
 * pass a bunch of frames that will be drawn one by one.
 * 
 * Usage: create a child class that implement sthe virtual functions:
 * ```cpp
 * class MyFrame : public Frame {
 *     void draw() {
 *        drawCircle({0, 0}, 1, {255, 255, 255});
 *        drawPixel({0, 0}, {255, 255, 255});
 *     };
 * 
 *      void configWindow() { // will be called every time too
 *          setFps(60); // defines how long the frame must stay on scrren
 *          setPhysicalRadius(10); // a point drawn at a distance 10 of the origin will be outside the frame.
 *          setBackgroundColor(0, 0, 0); // defines the background of the frame
 *      }
 * };
 * ```
 * 
 */
class Frame {
    Animation* window;
    
    public:

        /**
         * @brief Implement this function that will draw the frame on the window.
         */
        virtual void draw() = 0;

        /**
         * @brief adjust parameters of the window (such as setting background color, title, etc.)
         */
        virtual void configWindow() = 0;

        /**
         * Called by the animation function when the animation is created with a bunch of frames.
         */
        void _setWindow(Animation* animation) {window = animation;};

        /**
         * @brief Draw the frame on the window. This function is called by the animation function. This calls
         * _checkWindow() to make sure the window is not nullptr, then calls configWindow() to adjust the window's parameters,
         * and finally calls draw() to draw the frame.
         */
        void _draw(){
            _checkWindow();
            configWindow();
            draw();
        };

        /**
         * @brief Check if the window is not nullptr. If it is, throw an error.
         */
        void _checkWindow() {if (window == nullptr) throw std::runtime_error("Frame::window is nullptr. You are attemtping to draw the frame but no animation has been created to draw it on.");};

    // ------------- //
    // !-- Utils --! //
    // ------------- //

        /**
         * @brief Creates the animation and runs it. The frames will be rendered one by one.
         */
        static void runAnimation(std::vector<std::shared_ptr<Frame>> frames) { // cf animation class we need to pass it as shared ptrs
            if (frames.size() == 0) throw std::runtime_error("Frame::runAnimation: frames.size() == 0. You must pass at least one frame to run the animation.");
            Animation animation(frames); // this creates & runs the animation
        }; 

    protected:
        // Drawing functions
        void drawCircle(Eigen::Vector2d center, double radius, Eigen::Vector3i color) {window->drawCircle(center, radius, color);};
        void drawPixel(Eigen::Vector2d position, Eigen::Vector3i color) {window->drawPixel(position, color);};

        // Config
        void setBackgroundColor(Eigen::Vector3i color) {window->backgroundColor = color;};
        void setFps(double fps) {window->fps = fps;};
        void setPhysicalRadius(double radius) {window->physicalRadius = radius;};
};



