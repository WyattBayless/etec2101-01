#include <bullet.h>

example::Bullet::Bullet()
{
}

example::Bullet::Bullet(float x, float y, float vx, float vy, float radius, const sf::Color& c) :
	mCircle(radius), mVelocity(vx, vy)
{
	mCircle.setOrigin(sf::Vector2f(radius, radius));
	mCircle.setPosition(sf::Vector2f(x, y));
	mCircle.setFillColor(c);
	mCircle.setOutlineColor(sf::Color::Black);
	mCircle.setOutlineThickness(2.0f);
}


bool example::Bullet::update(float dt, sf::FloatRect win_bounds)
{
	sf::Vector2f p = mCircle.getPosition();
	float r = mCircle.getRadius();
	p.x += mVelocity.x * dt;
	p.y += mVelocity.y * dt;
	sf::Vector2f wb_c = win_bounds.getCenter();
	sf::Vector2f wb_s = win_bounds.size;
	mCircle.setPosition(p);
	return (p.x < wb_c.x - wb_s.x - r || p.x > wb_c.x + wb_s.x + r  || 
		    p.y < wb_c.y - wb_s.y - r || p.y > wb_c.y + wb_s.y + r);
}


void example::Bullet::draw(sf::RenderWindow& rt)
{
	rt.draw(mCircle);
}

sf::Vector2f example::Bullet::get_position() const
{
	return mCircle.getPosition();
}


float example::Bullet::get_radius() const
{
	return mCircle.getRadius();
}
