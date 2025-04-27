#pragma once
#pragma warning(disable:4275)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <functional>
#include <cstddef>

namespace ssuds_drawing
{
	/// <summary>
	/// A Simple Circle with text centered in it
	/// </summary>
	class TextCircle
	{
	protected:
		/// <summary>
		/// The SFML text object 
		/// </summary>
		sf::Text mText;

		/// <summary>
		/// The SFML circle object
		/// </summary>
		sf::CircleShape mCircle;

		/// <summary>
		/// The bounding area for the text
		/// </summary>
		sf::FloatRect mTextRect;

	public:
		/// <summary>
		/// 
		/// </summary>
		TextCircle(const sf::Font& f, unsigned int font_size);


		/// <summary>
		/// The Constructor that DOES initialize everything
		/// </summary>
		/// <param name="x">starting x-position of the center of the text/circle</param>
		/// <param name="y">starting y-position of the center of the text/circle</param>
		/// <param name="font_ref">the font to use for the text</param>
		/// <param name="text">the text for the circle</param>
		TextCircle(float x, float y, const sf::Font& font_ref, std::string text, unsigned int font_size);

		/// <summary>
		/// Draws the object to the given render target
		/// </summary>
		/// <param name="target">target to draw to</param>
		virtual void draw(/*sf::RenderTarget*/ sf::RenderWindow& target) const;

		/// <summary>
		/// Setter to set the circle color
		/// </summary>
		/// <param name="c"></param>
		void set_circle_color(const sf::Color& c);


		/// <summary>
		/// Sets the text color
		/// </summary>
		/// <param name="c">new text color</param>
		void set_font_color(const sf::Color& c);

		/// <summary>
		/// Getter to get the current position of the center of the circle and text
		/// </summary>
		/// <returns></returns>
		sf::Vector2f get_position() const;

		/// <summary>
		/// Getter to get the string
		/// </summary>
		/// <returns>the string</returns>
		std::string get_string() const;

		/// <summary>
		/// Gets the circle color
		/// </summary>
		/// <returns></returns>
		sf::Color get_color() const;

		/// <summary>
		/// Sets the current position of the center of the circle and text
		/// </summary>
		/// <param name="p"></param>
		void set_position(const sf::Vector2f& p);

		/// <summary>
		/// Sets the string
		/// </summary>
		/// <param name="s">new string value</param>
		void set_string(const std::string& s);

		/// <summary>
		/// Determines if the given point is within the boundaries of the circle
		/// </summary>
		/// <param name="v">the position of interest</param>
		/// <returns>true if it is within, false if not</returns>
		bool point_inside(const sf::Vector2f v) const;

		bool circle_overlaps(const sf::Vector2f& other_center, float other_radius);

		float get_degrees();
		void set_degrees(float new_degrees);
	};
}

