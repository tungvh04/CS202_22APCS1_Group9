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
		mSoundBuffers.load(SoundEffects::getInstance(), "Media/Sound/Hurt.mp3");
		mSoundBuffers.load(SoundEffects::getInstance(), "Media/Sound/Death.mp3");
		mSoundBuffers.load(SoundEffects::getInstance(), "Media/Sound/Heal.mp3");
		mSoundBuffers.load(SoundEffects::getInstance(), "Media/Sound/Button.mp3");
		mSoundBuffers.load(SoundEffects::getInstance(), "Media/Sound/Invicible.mp3");


	private:
		SoundBufferHolder mSoundBuffers;
		std::list<sf::Sound> mSounds;
};

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
	mSounds.push_back(sf::Sound());
	sf::Sound& sound = mSounds.back();

	sound.setBuffer(mSoundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

#endif // SOUNDPLAYER_HPP