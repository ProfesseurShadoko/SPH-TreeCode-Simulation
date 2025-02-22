#include "animation.hpp"
#include "frame.hpp"



Animation::Animation(std::vector<std::shared_ptr<Frame>> frames) : frames(frames) {
    
    // Tell each frame that they are part of the animation
    Task setup("Setting Up Animation");

    if (frames.size() == 0) throw std::invalid_argument("You must pass at least one frame to the Animation constructor.");

    for (int i=0; i<frames.size(); i++) {
        frames[i]->_setWindow(this);
    }
    setup.complete();

    // Start with some information
    Task anim("Running Animation");
    Message("Press ESC to exit");
    Task::sleep(1000);

    // create window and get information about the number of pixels
    this->window.create(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
    this->phyicalOriginPosition = {window.getSize().x / 2.0, window.getSize().y / 2.0};

    // run the animation and enjoy <3
    run();
    anim.complete();
}


/**
 * ------------------
 * !-- EVENT LOOP --!
 * ------------------
 */

void Animation::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close(); // Close when Escape is pressed
        }
    }
}

void Animation::wait() {
    while (clock.getElapsedTime().asSeconds() < 1.0 / fps) {
        // Wait to maintain the desired frame rate
    }
    clock.restart();
}


void Animation::run() {

    while (window.isOpen()) {
        handleEvents();
        render();
        wait();
    }
}

void Animation::render() {
    // clear window and set new background color
    window.clear(sf::Color(backgroundColor.x(), backgroundColor.y(), backgroundColor.z()));

    // draw the current frame
    frames[currentFrame % frames.size()]->_draw(); // % makes the animation loop!

    // display and go to next frame
    window.display();
    currentFrame++;
}


/**
 * ---------------------
 * !-- DRAWING UTILS --!
 * ---------------------
 */

double Animation::physicalToPixelDistance(double distance) {
    return window.getSize().y / (2 * physicalRadius) * distance;
}

Eigen::Vector2d Animation::physicalToPixelCoordinates(Eigen::Vector2d position) {
    return {
        physicalToPixelDistance(position.x()) + phyicalOriginPosition.x(),
        - physicalToPixelDistance(position.y()) + phyicalOriginPosition.y()
    };
}

void Animation::drawCircle(Eigen::Vector2d center, double radius, Eigen::Vector3i color) {
    sf::CircleShape circle(physicalToPixelDistance(radius));
    circle.setFillColor(sf::Color(color.x(), color.y(), color.z()));
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    Eigen::Vector2d pixelPosition = physicalToPixelCoordinates(center);
    circle.setPosition(pixelPosition.x(), pixelPosition.y());
    window.draw(circle);
}


void Animation::drawPixel(Eigen::Vector2d position, Eigen::Vector3i color) {
    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    pixel.setFillColor(sf::Color(color.x(), color.y(), color.z()));

    Eigen::Vector2d pixelPosition = physicalToPixelCoordinates(position);
    pixel.setPosition(pixelPosition.x(), pixelPosition.y());
    window.draw(pixel);
}
