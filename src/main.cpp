#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main()
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "My window");

    // Ball propertiesk
    sf::CircleShape ball(20.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(sf::Vector2f{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    sf::Vector2f velocity(0, 0); // Initial velocity
    float gravity = 0.001;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Update
        // Collision detection with window boundaries
        if (ball.getPosition().x + ball.getRadius() * 2 > window.getSize().x || ball.getPosition().x < 0)
        {
            velocity.x = -velocity.x; // Reverse x velocity
        }
        if (ball.getPosition().y + ball.getRadius() * 2 > window.getSize().y || ball.getPosition().y < 0)
        {
            velocity.y = -velocity.y; // Reverse y velocity
        }

        velocity.y += gravity;
        ball.move(velocity);

        window.clear(sf::Color::Black);

        window.draw(ball);

        window.display();
    }
}
