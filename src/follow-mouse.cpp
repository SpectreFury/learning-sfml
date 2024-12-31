#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

namespace SFMLVectorMath
{

    sf::Vector2f Add(sf::Vector2f a, sf::Vector2f b)
    {
        sf::Vector2f newVector;

        newVector.x = a.x + b.x;
        newVector.y = a.y + b.y;

        return newVector;
    };

    sf::Vector2f Subtract(sf::Vector2f a, sf::Vector2f b)
    {
        sf::Vector2f newVector;

        newVector.x = a.x - b.x;
        newVector.y = a.y - b.y;

        return newVector;
    };

    sf::Vector2f Scale(sf::Vector2f a, float factor)
    {
        sf::Vector2f newVector;

        newVector.x = a.x * factor;
        newVector.y = a.y * factor;

        return newVector;
    };

};

void log(sf::Vector2i vector)
{
    std::cout << "X: " << vector.x << " Y: " << vector.y << std::endl;
};

class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    Ball(sf::Vector2f position, float radius, sf::Color color)
    {
        shape.setRadius(radius);
        shape.setOrigin(sf::Vector2f{radius, radius});
        shape.setPosition(position);
        shape.setFillColor(color);
    }

    void applyForce(sf::Vector2f force)
    {
        // f = m*a, since there is no mass f = a
        // we also wanna add all the forces up so we add it

        acceleration += force;
    }

    void update(float deltaTime)
    {
        velocity += acceleration;
        shape.move(velocity * deltaTime);

        // Once acceleration is applied, remove it
        acceleration = sf::Vector2f{0, 0};
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Follow the mouse");
    sf::Clock clock;
    sf::Font font("arial.ttf");
    sf::Text velocityText(font);

    Ball planet(sf::Vector2f{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 50, sf::Color::Red);

    // Initial velocity
    planet.velocity = sf::Vector2f{0, 0};

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // update
        float deltaTime = clock.restart().asSeconds();

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f planetPosition = planet.shape.getPosition();

        sf::Vector2f direction = SFMLVectorMath::Subtract(sf::Vector2f(mousePosition), planetPosition).normalized();
        std::stringstream ss;
        ss << "Velocity: " << planet.velocity.x << " " << planet.velocity.y;

        velocityText.setString(ss.str());

        planet.applyForce(direction);
        planet.update(deltaTime);

        window.clear();

        window.draw(planet.shape);
        window.draw(velocityText);

        window.display();
    }
}