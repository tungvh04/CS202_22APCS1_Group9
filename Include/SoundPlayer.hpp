#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <list>


class SoundPlayer : private sf::NonCopyable
{
	public:
		SoundPlayer();

		void play(SoundEffects::ID effect);
		void play(SoundEffects::ID effect, sf::Vector2f position);

		void removeStoppedSounds();
		void setListenerPosition(sf::Vector2f position);
		sf::Vector2f getListenerPosition() const;


	private:
		SoundBufferHolder mSoundBuffers;
		std::list<sf::Sound> mSounds;
};

#endif // SOUNDPLAYER_HPP