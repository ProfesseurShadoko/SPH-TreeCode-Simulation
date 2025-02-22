#include "animation.hpp"



Animation::Animation() {

    // Start with some information
    Task("Running Animation");
    Message("Press ESC to exit");
    Task::sleep(1000);

    // create window and get information about the number of pixels
    this->window.create(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
    this->phyicalOriginPosition = {window.getSize().x / 2, window.getSize().y / 2};

    // run the animation and enjoy <3
    run();
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

    // Draw stuff here
    //drawCircle({0, 0}, 0.5, {0, 0, 0});
    //drawCircle({0.5 * std::cos(currentFrame / 60.0), 0.5 * std::sin(currentFrame / 60.0)}, 0.1, {255, 0, 0});
    drawPixel({0, 0}, {0, 255, 0});
    drawPixel({0.1, 0.1}, {255, 0, 0});
    drawPixel({0.5 * std::cos(currentFrame / 60.0), 0.5 * std::sin(currentFrame / 60.0)}, {0, 0, 255});


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

Eigen::Vector2f Animation::physicalToPixelCoordinates(Eigen::Vector2f position) {
    return {
        physicalToPixelDistance(position.x()) + phyicalOriginPosition.x(),
        - physicalToPixelDistance(position.y()) + phyicalOriginPosition.y()
    };
}

void Animation::drawCircle(Eigen::Vector2f center, double radius, Eigen::Vector3i color) {
    sf::CircleShape circle(physicalToPixelDistance(radius));
    circle.setFillColor(sf::Color(color.x(), color.y(), color.z()));
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    Eigen::Vector2f pixelPosition = physicalToPixelCoordinates(center);
    circle.setPosition(pixelPosition.x(), pixelPosition.y());
    window.draw(circle);
}


void Animation::drawPixel(Eigen::Vector2f position, Eigen::Vector3i color) {
    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    pixel.setFillColor(sf::Color(color.x(), color.y(), color.z()));

    Eigen::Vector2f pixelPosition = physicalToPixelCoordinates(position);
    pixel.setPosition(pixelPosition.x(), pixelPosition.y());
    window.draw(pixel);
}
