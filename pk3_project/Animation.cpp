#include "Animation.h"

#pragma Constructors

Animation::Animation() {}

#pragma endregion

#pragma Class Methods

void Animation::PlayNext(const Sprite& animation)
{
	if (getAnimation() != &animation) //next frame of animation
		SetAnimation(animation);
	paused = false;
}

void Animation::StopAnimation()
{
	paused = true; //stop the animation
	actual_frame = 0;
	SetFrame(actual_frame, true);
}

void Animation::Updating(sf::Time deltaTime) //updating current animations depending on the situation
{
	if ((paused == false) && (const_sprite != nullptr)) //if it is not paused and the same animation continues
	{
		actual_time += deltaTime;

		if (actual_time >= frame_time)
		{
			actual_time = sf::microseconds(actual_time.asMicroseconds() % frame_time.asMicroseconds());

			if (actual_frame + 1 < const_sprite->GetSize())
			{
				actual_frame++;
			}
			else
			{
				actual_frame = 0;

				if (looped == false)
					paused = true;

			}
			SetFrame(actual_frame, false);
		}
	}
}

void Animation::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const //draw animation
{
	if ((const_sprite!=nullptr) && (const_texture!=nullptr))
	{
		render_states.texture = const_texture;
		render_states.transform *= getTransform();
		render_target.draw(coord, 4, sf::Quads, render_states);
	}
}

void Animation::SetFrame(int newFrame, bool reset_time) //set frame
{
	if (reset_time == true)
		actual_time = sf::Time::Zero;

	if (const_sprite == nullptr)
		return;

	sf::IntRect rect = const_sprite->GetFrame(newFrame); //calculate new vertex positions and texture coordiantes

	coord[0].position = sf::Vector2f(0.f, 0.f);
	coord[1].position = sf::Vector2f(0.f, static_cast<double>(rect.height));
	coord[2].position = sf::Vector2f(static_cast<double>(rect.width), static_cast<double>(rect.height));
	coord[3].position = sf::Vector2f(static_cast<double>(rect.width), 0.f);

	double to_left = static_cast<double>(rect.left) + 0.0001f;
	double to_right = to_left + static_cast<double>(rect.width);
	double to_top = static_cast<double>(rect.top);
	double to_bot = to_top + static_cast<double>(rect.height);

	coord[0].texCoords = sf::Vector2f(to_left, to_top); //set verticles
	coord[1].texCoords = sf::Vector2f(to_left, to_bot);
	coord[2].texCoords = sf::Vector2f(to_right, to_bot);
	coord[3].texCoords = sf::Vector2f(to_right, to_top);
}

#pragma endregion

#pragma Accessors

void Animation::SetAnimation(const Sprite& animation) //set animation
{
	const_sprite = &animation;
	const_texture = const_sprite->GetSpriteSheet();
	actual_frame = 0;
	SetFrame(actual_frame, true);
}

void Animation::setFrameTime(sf::Time frame_time)
{
	this->frame_time = frame_time;
}

const Sprite* Animation::getAnimation() const
{
	return this->const_sprite;
}

bool Animation::GetIsLooped() const
{
	return this->looped;
}

bool Animation::GetIsPlaying() const
{
	return !paused;
}

sf::Time Animation::getFrameTime() const
{
	return this->frame_time;
}

#pragma endregion