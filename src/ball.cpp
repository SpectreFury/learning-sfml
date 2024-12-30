#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;

    Ball(sf::Vector2f position, float radius, sf::Color color)
    {
        this->shape.setRadius(radius);
        this->shape.setFillColor(color);
        this->shape.setPosition(position);
    };

    void applyForce(sf::Vector2f force)
    {
        acceleration += force;
    }

    void update(float deltaTime)
    {
        velocity += acceleration;
        shape.move(velocity * deltaTime);

        acceleration = sf::Vector2f{0, 0};
    };
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "My window");

    Ball ball(sf::Vector2f{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 10, sf::Color::Cyan);
    ball.velocity = sf::Vector2f{0, 0};

    sf::Clock clock;

    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2f wind{1, 0};
            ball.applyForce(wind);
        }

        float deltaTime = clock.restart().asSeconds();

        // Gravity
        ball.applyForce(sf::Vector2f{0, 0.1});

        ball.update(deltaTime);
        std::cout << "deltaTime: " << deltaTime << std::endl;

        // Collision detection with window boundaries
        if (ball.shape.getPosition().x + ball.shape.getRadius() * 2 > window.getSize().x || ball.shape.getPosition().x < 0)
        {
            ball.velocity.x = -ball.velocity.x; // Reverse x velocity
        }
        if (ball.shape.getPosition().y + ball.shape.getRadius() * 2 > window.getSize().y || ball.shape.getPosition().y < 0)
        {
            ball.velocity.y = -ball.velocity.y; // Reverse y velocity
        }

        window.clear(sf::Color::Black);

        window.draw(ball.shape);

        window.display();
    }
}