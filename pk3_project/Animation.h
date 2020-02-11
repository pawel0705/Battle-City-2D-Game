#ifndef Animation_hpp
#define Animation_hpp

#include "Sprite.h"

class Animation : public sf::Transformable, public sf::Drawable //The class that supports the sprite animation. Inherits from two classes of the SFML library (Transformable, Drawable)
{
	int actual_frame = 0; //The current frame of the animation
	bool paused = false; //whether the animation is paused or looped
	bool looped = false;

	const Sprite* const_sprite = nullptr; //Pointer on CLASS 'Sprite' (not on sf :: Sprite from SFML library)
	const sf::Texture* const_texture = nullptr; //texture indicator

	sf::Time frame_time = sf::seconds(0.1f); //the animation frame lasts for 0.1 seconds
	sf::Time actual_time = sf::seconds(0);

	sf::Vertex coord[4]; //array to define a point with texture coordinates

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const; //virtual function to draw sprites

public:
	Animation();
	~Animation() = default;

	void Updating(sf::Time); //Updating the animation state

	void PlayNext(const Sprite&); //go to the next frame of the animation
	void StopAnimation(); //Stopthe animation

	void SetFrame(int, bool); //set frame
	void SetAnimation(const Sprite& animation); //set animation
	void setFrameTime(sf::Time time); //set frame time

	bool GetIsLooped() const; //Is it looped
	bool GetIsPlaying() const; //Is it paused
	const Sprite* getAnimation() const; //take the current frame of current animation
	sf::Time getFrameTime() const; //get time of frame
};

#endif