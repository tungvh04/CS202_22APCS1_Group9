#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


class MusicPlayer : private sf::NonCopyable
{
	public:
		MusicPlayer();
		void updateFilenames();

		void play(Music::ID theme);
		void stop();

		void setPaused(bool paused);
		void setVolume(float volume);
		float getVolume();

	private:
		sf::Music mMusic;
		std::map<Music::ID, std::string> mFilenames;
		float mVolume;
};

#endif // MUSICPLAYER_HPP