#include <text_circle.h>
#include <SFML/Graphics.hpp>


ssuds_drawing::TextCircle::TextCircle(const sf::Font& f, unsigned int font_size) : mText(f)
{
	mText.setCharacterSize(font_size);
}

ssuds_drawing::TextCircle::TextCircle(float x, float y, const sf::Font& font_ref, std::string text, unsigned int font_size) : mText(font_ref, text)
{
	// Set properties except position of the text object
	mText.setFillColor(sf::Color::White);
	mText.setCharacterSize(font_size);


	//mCircle.setFillColor(sf::Color(rand() % 128 + 127, rand() % 128 + 127, rand() % 128 + 127, 255));
	mCircle.setFillColor(sf::Color::Red);
	//mCircle.setPosition(sf::Vector2f(x, y));

	set_string(text);
	mText.setPosition(sf::Vector2f(x, y));
	float radius = mCircle.getRadius();
	mCircle.setPosition(sf::Vector2f(x - radius, y - radius));
}



void ssuds_drawing::TextCircle::draw(/*sf::RenderTarget*/sf::RenderWindow& target) const
{
	target.draw(mCircle);
	target.draw(mText);
}

void ssuds_drawing::TextCircle::set_circle_color(const sf::Color& c)
{
	mCircle.setFillColor(c);

}

void ssuds_drawing::TextCircle::set_font_color(const sf::Color& c)
{
	mText.setFillColor(c);
}

sf::Vector2f ssuds_drawing::TextCircle::get_position() const
{
	return mText.getPosition();
}


std::string ssuds_drawing::TextCircle::get_string() const
{
	return mText.getString();
}

sf::Color ssuds_drawing::TextCircle::get_color() const
{
	return mCircle.getFillColor();
}

void ssuds_drawing::TextCircle::set_position(const sf::Vector2f& p)
{
	float radius = mCircle.getRadius();
	mCircle.setPosition(sf::Vector2f(p.x - radius, p.y - radius));
	mText.setPosition(sf::Vector2f(p.x, p.y));
}

void ssuds_drawing::TextCircle::set_string(const std::string& s)
{
	mText.setString(s);

	// Center the text
	// reference: https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
	mTextRect = mText.getLocalBounds();
	mText.setOrigin(sf::Vector2f(mTextRect.position.x + mTextRect.size.x / 2.0f, mTextRect.position.y + mTextRect.size.y / 2.0f));

	// Set the position / radius of the circle
	float radius = (mTextRect.size.x > mTextRect.size.y ? mTextRect.size.x : mTextRect.size.y) / 2.0f + 3.0f;
	mCircle.setRadius(radius);
	sf::Vector2f cur_pos = mText.getPosition();
	mCircle.setPosition(sf::Vector2f(cur_pos.x - radius, cur_pos.y - radius));
}

bool ssuds_drawing::TextCircle::point_inside(sf::Vector2f v) const
{
	sf::Vector2f p = get_position();
	float dist = powf(powf(v.x - p.x, 2.0f) + powf(v.y - p.y, 2.0f), 0.5f);
	return dist <= mCircle.getRadius();
}

bool ssuds_drawing::TextCircle::circle_overlaps(const sf::Vector2f& other_center, float other_radius)
{
	sf::Vector2f p = get_position();
	float dist = powf(powf(other_center.x - p.x, 2.0f) + powf(other_center.y - p.y, 2.0f), 0.5f);
	return dist <= other_radius + mCircle.getRadius();
}


float ssuds_drawing::TextCircle::get_degrees()
{
	return mText.getRotation().asDegrees();
}


void ssuds_drawing::TextCircle::set_degrees(float new_degrees)
{
	mText.setRotation(sf::degrees(new_degrees));
}
