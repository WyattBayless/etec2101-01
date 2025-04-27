#pragma once
#pragma warning(disable:4275)
#include <SFML/Graphics.hpp>


namespace example
{
	class Bullet
	{
	private:
		float mRadius;
		sf::CircleShape mCircle;
		sf::Vector2f mVelocity;
	public:
		Bullet();
		Bullet(float x, float y, float vx, float vy, float radius, const sf::Color& c);
		bool update(float dt, sf::FloatRect win_bounds);
		void draw(sf::RenderWindow& rt);
		sf::Vector2f get_position() const;
		float get_radius() const;
	};
}
