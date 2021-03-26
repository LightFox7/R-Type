#include "RessourceManager.hpp"

RessourceManager::RessourceManager()
{
}

RessourceManager::~RessourceManager()
{
}

int RessourceManager::addTexture(std::string const &id, std::string const &path)
{
    if (_textures.find(id) != _textures.end()) {
        std::cerr << "Can't load texture \"" << path << "\" with id \"" << id << "\": Id is already taken." << std::endl;
        return (2);
    }
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(path) != true) {
        std::cerr << "Can't load texture \"" << path << "\" with id \"" << id << "\": Can't load texture from path." << std::endl;
        return (1);
    }
    _textures.emplace(id, texture);
    return (0);
}

int RessourceManager::removeTexture(std::string const &id)
{
    if (_textures.find(id) == _textures.end()) {
        return (2);
    }
    _textures.erase(id);
    return (0);
}

std::shared_ptr<sf::Texture> RessourceManager::getTexture(std::string const &id)
{
    auto it = _textures.find(id);

    if (it == _textures.end()) {
        std::cerr << "Can't get texture with id \"" << id << "\": Does not exist" << std::endl;
        return (nullptr);
    }
    return (it->second);
}

bool RessourceManager::isTextureLoaded(std::string const &id)
{
    return (_textures.find(id) != _textures.end());
}

int RessourceManager::addFont(std::string const &id, std::string const &path)
{
    if (_fonts.find(id) != _fonts.end()) {
        std::cerr << "Can't load font \"" << path << "\" with id \"" << id << "\": Id is already taken." << std::endl;
        return (2);
    }
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    if (font->loadFromFile(path) != true) {
        std::cerr << "Can't load font \"" << path << "\" with id \"" << id << "\": Can't load font from path." << std::endl;
        return (1);
    }
    _fonts.emplace(id, font);
    return (0);
}

int RessourceManager::removeFont(std::string const &id)
{
    if (_fonts.find(id) == _fonts.end()) {
        std::cerr << "Can't unload font with id \"" << id << "\": Does not exist." << std::endl;
        return (2);
    }
    _fonts.erase(id);
    return (0);
}

std::shared_ptr<sf::Font> RessourceManager::getFont(std::string const &id)
{
    auto it = _fonts.find(id);

    if (it == _fonts.end()) {
        std::cerr << "Can't get texture with id \"" << id << "\": Does not exist" << std::endl;
        return (nullptr);
    }
    return (it->second);
}

bool RessourceManager::isFontLoaded(std::string const &id)
{
    return (_fonts.find(id) != _fonts.end());
}

int RessourceManager::addMusic(std::string const &id, std::string const &path)
{
    if (_musics.find(id) != _musics.end()) {
        std::cerr << "Can't load music \"" << path << "\" with id \"" << id << "\": Id is already taken." << std::endl;
        return (2);
    }
    std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
    if (music->openFromFile(path) != true) {
        std::cerr << "Can't load music \"" << path << "\" with id \"" << id << "\": Can't load music from path." << std::endl;
        return (1);
    }
    _musics.emplace(id, music);
    return (0);
}

int RessourceManager::removeMusic(std::string const &id)
{
    if (_musics.find(id) == _musics.end()) {
        std::cerr << "Can't unload music with id \"" << id << "\": Does not exist." << std::endl;
        return (2);
    }
    _musics.erase(id);
    return (0);
}

std::shared_ptr<sf::Music> RessourceManager::getMusic(std::string const &id)
{
    auto it = _musics.find(id);

    if (it == _musics.end()) {
        std::cerr << "Can't get music with id \"" << id << "\": Does not exist" << std::endl;
        return (nullptr);
    }
    return (it->second);
}

bool RessourceManager::isMusicLoaded(std::string const &id)
{
    return (_musics.find(id) != _musics.end());
}

int RessourceManager::addSound(std::string const &id, std::string const &path)
{
    if (_sounds.find(id) != _sounds.end()) {
        std::cerr << "Can't load sound \"" << path << "\" with id \"" << id << "\": Id is already taken." << std::endl;
        return (2);
    }
    std::shared_ptr<sf::SoundBuffer> soundbuffer = std::make_shared<sf::SoundBuffer>();
    std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();
    if (soundbuffer->loadFromFile(path) != true) {
        std::cerr << "Can't load sound \"" << path << "\" with id \"" << id << "\": Can't load sound from path." << std::endl;
        return (1);
    }
    sound->setBuffer(*soundbuffer);
    _soundbuffers.emplace(id, soundbuffer);
    _sounds.emplace(id, sound);
    return (0);
}

int RessourceManager::removeSound(std::string const &id)
{
    if (_sounds.find(id) == _sounds.end()) {
        std::cerr << "Can't unload sound with id \"" << id << "\": Does not exist." << std::endl;
        return (2);
    }
    _sounds.erase(id);
    _soundbuffers.erase(id);
    return (0);
}

std::shared_ptr<sf::Sound> RessourceManager::getSound(std::string const &id)
{
    auto it = _sounds.find(id);

    if (it == _sounds.end()) {
        std::cerr << "Can't get sound with id \"" << id << "\": Does not exist" << std::endl;
        return (nullptr);
    }
    return (it->second);
}

bool RessourceManager::isSoundLoaded(std::string const &id)
{
    return (_sounds.find(id) != _sounds.end());
}

void RessourceManager::setMusicsVolume(float volume)
{
    for (auto it : _musics)
        it.second->setVolume(volume);
}

void RessourceManager::setSoundsVolume(float volume)
{
    for (auto it : _sounds)
        it.second->setVolume(volume);
}