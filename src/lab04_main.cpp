// Optional -- ignores a dll-interface warning coming from sFML
#pragma warning(disable:4275)
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <optional>
#include <array_list.h>
#include <word_reader.h>
#include <text_circle.h>
#include <random>
#include <bullet.h>
#include <iostream>

int main()
{
    // @@@@@@@@@@@@@@@@@@@@@@
    // @ SETUP              @
    // @@@@@@@@@@@@@@@@@@@@@@
    // ... create the window
    unsigned int win_width = 800, win_height = 600;
    sf::RenderWindow window(sf::VideoMode({ win_width, win_height }), "Lab4 (WyattB)");
    sf::FloatRect window_bounds(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)win_width, (float)win_height));
    window.setMouseCursorGrabbed(true);

    // ... create the wordReader which will be used to get random "SCOWL" words
    example::WordReader WR("../../../media/american-words.50");

    // ... make an Array of TextCircle *pointers*.  I'm not surper crazy about this solution: 
    //     when we spawn a new TextCircle, I dynamically create a new TextCircle.  I have to make
    //     darn sure I free up this memory (happens when a TextCircle is destroyed by a bullet or goes off
    //     screen, or when the program ends).  I would've preferred to make an ArrayList of TextCircles, but
    //     since we don't (and can't) have a default constructor in TextCircle, I can't do this.  This was
    //     the point of my (failed) attempt at using an array of char's in ArrayList.
    // ... more important node: I have multiple arrayLists here -- I'm using it to store different
    //     bits of info about a circle.  So if I'm in a loop circle_list[i] is the CircleItself, 
    //     circle_speed_list[i] is its speed, circle_rotate_list[i] is the rotation, etc.  It's important
    //     when a circle is removed, that we remove the data from each list.
    ssuds::ArrayList<ssuds_drawing::TextCircle*> circle_list;
    ssuds::ArrayList<float> circle_speed_list;
    ssuds::ArrayList<float> circle_rotrate_list;
    float time_to_spawn = 1.0f;                     // ... time to spawn a circle

    // ... Load some assets and data for the pointy-hand
    sf::Texture hand_img("../../../media/hand.png");
    sf::Sprite hand_sprite(hand_img);
    sf::FloatRect hand_rect = hand_sprite.getLocalBounds();
    hand_sprite.setOrigin(sf::Vector2f(hand_rect.size.x, hand_rect.size.y / 2));
    hand_sprite.setPosition(sf::Vector2f(win_width / 2.0f, (float)win_height));
    hand_sprite.setRotation(sf::degrees(90));

    // ... Load the font used pretty much everywhere.
    sf::Font my_font("../../../media/Oswald/Oswald/static/Oswald-Regular.ttf");

    // ... do some C++ style RNG (Random Number Generation) -- these values are used when spawning
    //     a new random word circle
    std::random_device random_device;
    std::mt19937 random_algorithm(random_device());
    std::uniform_int_distribution<std::mt19937::result_type> random_color_distribution(128, 255);
    std::uniform_int_distribution<std::mt19937::result_type> random_x_distribution(0, win_width - 1);
    std::uniform_int_distribution<std::mt19937::result_type> random_rotrate_distribution(0, 360);
    std::uniform_int_distribution<std::mt19937::result_type> random_speed_distribution(10, 60);
    std::uniform_int_distribution<std::mt19937::result_type> random_angle_distribution(0, 360);
 
    // ... Load background image (and a black background for the letter-counts)
    sf::Texture background_img("../../../media/space.png");
    sf::Sprite background_sprite(background_img);
    sf::RectangleShape text_background(sf::Vector2f(win_width - 20.0f, 50.0f));
    text_background.setPosition(sf::Vector2f(10, 15));
    text_background.setFillColor(sf::Color::Black);

    // ... Load the counts of each leter (and some resources related to them)
    ssuds::ArrayList<int> letter_counts;
    float letter_spacing = win_width / 27.0f;
    float letter_x = letter_spacing;
    sf::Text letter_text(my_font, "x", 16);
    for (int i = 0; i < 26; i++)
        letter_counts.append(0);
        
    // ... Create an array and some data used for the bullets
    ssuds::ArrayList<example::Bullet> bullet_list;
    float bullet_speed = 200.0f;            // pixels / second

    // ... Load the clock (used to make things move at a frame-rate-independent speed)
    sf::Clock main_clock;

    // @@@@@@@@@@@@@@@@@@@@@@@@@@
    // @ The GAME LOOP          @
    // @@@@@@@@@@@@@@@@@@@@@@@@@@
    while (window.isOpen())
    {
        // ##################################
        // # UPDATES (not related to input) #
        // ##################################
        // ... Get time (in seconds) since the clock was created [first pass through this loop]
        //     or since the last time [every other time through this loop].  This is used extensively
        //     to make things move at a frame-rate-independent rate
        float delta_time = main_clock.getElapsedTime().asSeconds();
        main_clock.restart();

        // ... See if we need to spawn a new text-circle
        time_to_spawn -= delta_time;
        if (time_to_spawn <= 0)
        {
            // ... Wait one more second till we spawn again
            time_to_spawn += 1.0f;

            // ... Get the data for the new circle
            float angle = (float)random_angle_distribution(random_algorithm);
            float move_speed = (float)random_speed_distribution(random_algorithm);
            float rot_speed = (float)random_rotrate_distribution(random_algorithm) - 180.0f;
            circle_speed_list.append(move_speed);
            circle_rotrate_list.append(rot_speed);
            unsigned int x = random_x_distribution(random_algorithm);
            unsigned char red = random_color_distribution(random_algorithm);
            unsigned char green = random_color_distribution(random_algorithm);
            unsigned char blue = random_color_distribution(random_algorithm);

            // ... Actually create the TextCircle and related data and add to the appropriate list
            // Note: I'm dynamically allocating some memory here.  The array list just holds this, but can't
            // free it up -- the loop at the end (and the code when we remove a circle is very important to prevent 
            // a memory leak!). 
            ssuds_drawing::TextCircle* new_tc = new ssuds_drawing::TextCircle((float)x, -100.0f, my_font, WR.extract_word(), 12);
            new_tc->set_degrees(angle);
            if ((red + green + blue) / 3 > 128)
                new_tc->set_font_color(sf::Color::Black);
            new_tc->set_circle_color(sf::Color(red, green, blue));
            circle_list.append(new_tc);
            std::cout << "Spawning object '" << new_tc->get_string() << ";\n";
        }

        // ... Loop through all the bullets that are still active
        ssuds::ArrayList<example::Bullet>::ArrayListIterator it = bullet_list.begin();
        while (it != bullet_list.end())
        {
            // ... used to tell if we need to destroy this bullet (for whatever reason)
            bool remove = false;

            // ... update (move and check for boundary) the bullet.  If this returns true it indicates
            //     the bullet has left the playfield, so should be removed.
            if ((*it).update(delta_time, window_bounds))
                remove = true;

            // ... If the bullet hasn't been removed, do further checks.  Here, I'm checking it against
            //   each TextCircle to see if they overlap.
            if (!remove)
            {
                // ... Get an iterator to visit each TextCircle.  Note the nesting of this check is important
                //     -- we're looking at things from *it (the current bullet)'s perspective, but then we're
                //     checking that one bullet against ALL the TextCircles.  I'm running the other iterators for
                //     the speed and rotation along with this one -- see the note when I destroy the circle for an
                //     explanation
                ssuds::ArrayList<ssuds_drawing::TextCircle*>::ArrayListIterator it2 = circle_list.begin();
                ssuds::ArrayList<float>::ArrayListIterator speed_iterator = circle_speed_list.begin();
                ssuds::ArrayList<float>::ArrayListIterator rotation_iterator = circle_rotrate_list.begin();
                while (it2 != circle_list.end())
                {
                    // ... see if the current bullet (it) overlaps the current textCircle (it2)
                    if ((*it2)->circle_overlaps((*it).get_position(), (*it).get_radius()))
                    {
                        // ... They do overlap.  Mark the bullet for removal (later)
                        remove = true;

                        // ... and update the word counts.  Note the "clever" math using ASCII character values
                        std::string s = (*it2)->get_string();
                        for (int j = 0; j < s.size(); j++)
                        {
                            if (s[j] >= 'a' && s[j] <= 'z')
                                letter_counts[s[j] - 'a']++;
                            if (s[j] >= 'A' && s[j] <= 'Z')
                                letter_counts[s[j] - 'A']++;
                        }

                        // Very important to prevent a memory leak!
                        delete (*it2);

                        // Now remove that item from the array list of text circles.  Since I (perhaps unwisely?)
                        // chose to represent all data about the falling circle in 3 "parallel" lists, it's important
                        // when I remove from one, that I also remove from the others.  That's why I needed the speed and
                        // rotation iterators to be run along with the main it2 iterator
                        circle_list.remove(it2);
                        circle_speed_list.remove(speed_iterator);
                        circle_rotrate_list.remove(rotation_iterator);
                        break;
                    }
                    else
                    {
                        // ... Advance all the text circle iterators
                        ++it2;
                        ++speed_iterator;
                        ++rotation_iterator;
                    }
                }
               
            }
            // ... if we removed the bullet for any reason, remove it now.
            if (remove)
            {
                std::cout << "Bullet removed\n";
                it = bullet_list.remove(it);        // A very important idea in our iterator and std::vector --
                                                    // removal while iterating is fine, but you have to update
                                                    // it in response to removing.  It generally will now point to
                                                    // the one after the removed bullet, but could be end-iterator if
                                                    // the one removed was the last one.
            }
            // ... otherwise, go on to the next bullet
            else
            {
                ++it;
            }  
        }

        // ... update all (remaining) text circles
        for (unsigned int i = 0; i < circle_list.size(); i++)
        {
            sf::Vector2f v = circle_list[i]->get_position();
            circle_list[i]->set_degrees(circle_list[i]->get_degrees() + circle_rotrate_list[i] * delta_time);
            v.y += 100 * delta_time;
            circle_list[i]->set_position(v);
        }


        // ############################
        // # PROCESS INPUT EVENTS     #
        // ############################
        // ... by looping through all waiting events -- I check for "interesting" events by using
        //     SFML (and C++17's interesting "optional" feature)
        while (const std::optional event = window.pollEvent())
        {
            // ... check to see if the close button was pressed
            if (event->is<sf::Event::Closed>())
                window.close();

            // ... check to see if a key was pressed
            else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
            {
                // ... now look to see if this was a key I care about
                if (keyEvt->code == sf::Keyboard::Key::Escape)
                    window.close();
            }

            // ... check to see if the mouse was moved
            else if (const sf::Event::MouseMoved* moveEvt = event->getIf<sf::Event::MouseMoved>())
            {
                // ... if so, make the hand point towards it
                sf::Vector2f mouse_pos = sf::Vector2f((float)moveEvt->position.x, (float)moveEvt->position.y);
                sf::Vector2f offset = mouse_pos - hand_sprite.getPosition();
                float angle = atan2f(offset.y, offset.x) + 3.1416f;
                hand_sprite.setRotation(sf::radians(angle));
            }

            // ... check to see if a mouse button was pressed
            else if (const sf::Event::MouseButtonPressed* buttonEvt = event->getIf<sf::Event::MouseButtonPressed>())
            {
                // ... see if the left-mouse button was the one pressed
                if (buttonEvt->button == sf::Mouse::Button::Left)
                {
                    // ... It was.  Spawn a bullet in response.
                    float hand_radians = hand_sprite.getRotation().asRadians() - 3.1416f;
                    float finger_dist = 210.0f;
                    float adjacent = cosf(hand_radians);
                    float opposite = sinf(hand_radians);
                    float x = hand_sprite.getPosition().x + adjacent * finger_dist;
                    float y = hand_sprite.getPosition().y + opposite * finger_dist;
                    float vx = bullet_speed * adjacent;
                    float vy = bullet_speed * opposite;
                    bullet_list.append(example::Bullet(x, y, vx, vy, 10, sf::Color::White));
                    std::cout << "Pew! (" << x << ", " << y << ") vel=(" << vx << ", " << vy << ")\n";
                }
            }
        }


        // #########################
        // # DRAWING               #
        // #########################
        // ... I don't need this in this program since I'm (re-) drawing the background.  But if
        //     we didn't have a background this might be useful
        //window.clear(sf::Color(255,0,0));

        // ... Draw the background (this also has the effect of erasing the old contents of the screen
        //     to prepare for new drawing)
        window.draw(background_sprite);

        // ... Draw the hand (the rotation code is all in the mouse movement area)
        window.draw(hand_sprite);

        // ... Draw any active text circles
        for (ssuds_drawing::TextCircle* tc : circle_list)
            tc->draw(window);

        // ... Draw any active bullets
        for (example::Bullet b : bullet_list)
            b.draw(window);

        // ... Draw the black text-background area and then the letter counts on top
        window.draw(text_background);
        letter_x = letter_spacing;
        for (unsigned int i = 0; i < letter_counts.size(); i++, letter_x += letter_spacing)
        {
            // ... I chose to just have one sfml Text object.  I'm updating the position and text
            // as a I go.  The first step is to construct a string.  The
            std::string s = "?";            // Makes internal c string as least one character
            s[0] = 'A' + i;                 // Replace that one character with the one I really want

            // ... Now set the position of the letter and draw
            letter_text.setString(s);
            letter_text.setOrigin(sf::Vector2f(letter_text.getGlobalBounds().size.x / 2.0f, 0));
            letter_text.setPosition(sf::Vector2f(letter_x, 20.0f));
            window.draw(letter_text);

            // ... Put the letter count (stored in my letter_counts ArrayList) and draw that below the caption
            letter_text.setString(std::to_string(letter_counts[i]));
            letter_text.setOrigin(sf::Vector2f(letter_text.getGlobalBounds().size.x / 2.0f, 0));
            letter_text.setPosition(sf::Vector2f(letter_x, 40.0f));
            window.draw(letter_text);
        }

        // ... This makes all our drawings visible
        window.display();
    }


    // Free up memory for any remaining circle objects (that were on-screen when the program ended)
    for (unsigned int i = 0; i < circle_list.size(); i++)
        delete circle_list[i];
}