#include <Animation.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


Animation::Animation()
: mSprite()
, mFrameSize()
, mNumFrames(0)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
{
}

Animation::Animation(const sf::Texture& texture)
: mSprite(texture)
, mFrameSize()
, mNumFrames(0)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
, isBuiltYet(true)
{
}

bool Animation::isBuilt() {
	return isBuiltYet;
}

void Animation::setTexture(const sf::Texture& texture)
{
	isBuiltYet=true;
	mSprite.setTexture(texture);
}

const sf::Texture* Animation::getTexture() const
{
	return mSprite.getTexture();
}
void Animation::setAnimation(const std::string& filename, int numFrame, int x, int y){
	sf::Texture texture;
	if (!texture.loadFromFile(filename)){
		throw "Invalid " + filename;
	}
	setTexture(texture);
	setNumFrames(numFrame);
	setFrameSize(sf::Vector2i(x, y));
	setRepeating(true);
	setDuration(sf::seconds(1));
}
void Animation::setFrameSize(sf::Vector2i frameSize)
{
	mFrameSize = frameSize;
}

sf::Vector2i Animation::getFrameSize() const
{
	return mFrameSize;
}

void Animation::setNumFrames(std::size_t numFrames)
{
	mNumFrames = numFrames;
}

std::size_t Animation::getNumFrames() const
{
	return mNumFrames;
}

void Animation::setDuration(sf::Time duration)
{
	mDuration = duration;
}

sf::Time Animation::getDuration() const
{
	return mDuration;
}

void Animation::setRepeating(bool flag)
{
	mRepeat = flag;
}

bool Animation::isRepeating() const
{
	return mRepeat;
}

void Animation::restart()
{
	isFinishedFlag = false;
	mCurrentFrame = 0;
}


bool Animation::isFinished() const
{
	return isFinishedFlag;
}

sf::FloatRect Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
	mElapsedTime += dt;

	sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
	sf::IntRect textureRect = mSprite.getTextureRect();

	if (mCurrentFrame == 0)
		textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
	
	while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
	{
		textureRect.left += textureRect.width;

		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		int tmp = (textureBounds.x + textureRect.width - 1) / textureRect.width;
		textureRect.left = textureRect.width * (mCurrentFrame%tmp);
		textureRect.top = textureRect.height * (mCurrentFrame/tmp);

		mElapsedTime -= timePerFrame;
		if (mRepeat)
		{
			if (mCurrentFrame>=mNumFrames) {
				isFinishedFlag = true;
			}

			mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;

			if (mCurrentFrame == 0)
				textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
		}
		else
		{
			mCurrentFrame++;
			if (mCurrentFrame>=mNumFrames) {
				mCurrentFrame=mNumFrames-1;
				isFinishedFlag = true;
			}
			if (mNumFrames<0) {
				mNumFrames=0;
			}
		}
	}


	mSprite.setTextureRect(textureRect);
	
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isHide) return;
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void Animation::hide() {
	isHide=true;
}

void Animation::show() {
	isHide=false;
}

bool Animation::isShow() {
	return !isHide;
}