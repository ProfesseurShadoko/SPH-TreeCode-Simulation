#include <tintoretto.hpp>
#include <window.hpp>
#include <Eigen/Dense>
#include <memory>

/**
 * @brief A frame is a single image that is displayed in a window. A frame is thus a collection of objects. 
 * The frame must implement how to draw itself on the window.
 * 
 * Creating classes that inherit from frame allows for easy construction of different simulations.
 * For instance, one can want to draw each particle as a circle with a color corresponding to density.
 */

class Frame {
    std::shared_ptr<Window> window = nullptr; // else we have an issue => when to delete window? because all frames share same ptr
    // this ptr gets deleted automatically, great!

    
    public:
        /**
         * @brief Implement this function that will draw the frame on the window.
         */
        virtual void draw() = 0;

        /**
         * @brief adjust parameters of the window (such as setting background color, title, etc.)
         */
        virtual void configWindow(Window &window) = 0;

    // ------------- //
    // !-- Utils --! //
    // ------------- //
    protected:

        void drawPixel(Eigen::Vector2i pos, Eigen::Vector3i rgb_color) {
            checkWindow();
            window->drawPixel(pos, rgb_color);
        }

        void drawCircle(Eigen::Vector2i pos, int radius, Eigen::Vector3i rgb_color = {255, 255, 255}) {
            checkWindow();
            window->drawCircle(pos, radius, rgb_color);
        }

        void drawLine(Eigen::Vector2i pos1, Eigen::Vector2i pos2, Eigen::Vector3i rgb_color = {255, 255, 255}) {
            checkWindow();
            window->drawLine(pos1, pos2, rgb_color);
        }

        void drawRectangle(Eigen::Vector2i pos1, Eigen::Vector2i pos2, Eigen::Vector3i rgb_color = {255, 255, 255}) {
            checkWindow();
            window->drawRectangle(pos1, pos2, rgb_color);
        }

        void setBackgroundColor(Eigen::Vector3i rgb_color = {0, 0, 0}) {
            checkWindow();
            window->setBackgroundColor(rgb_color);
        }

        



    private:
        void checkWindow() {
            if (window == nullptr) {
                throw std::runtime_error("Window not set");
            }
        }
};

