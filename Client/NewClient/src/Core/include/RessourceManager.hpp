#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class RessourceManager {
    public:
        RessourceManager();
        ~RessourceManager();
        int addTexture(std::string const &id, std::string const &path);
        int removeTexture(std::string const &id);
        std::shared_ptr<sf::Texture> getTexture(std::string const &id);
        bool isTextureLoaded(std::string const &id);
        int addFont(std::string const &id, std::string const &path);
        int removeFont(std::string const &id);
        std::shared_ptr<sf::Font> getFont(std::string const &id);
        bool isFontLoaded(std::string const &id);
        int addMusic(std::string const &id, std::string const &path);
        int removeMusic(std::string const &id);
        std::shared_ptr<sf::Music> getMusic(std::string const &id);
        bool isMusicLoaded(std::string const &id);
        int addSound(std::string const &id, std::string const &path);
        int removeSound(std::string const &id);
        std::shared_ptr<sf::Sound> getSound(std::string const &id);
        bool isSoundLoaded(std::string const &id);
        void setMusicsVolume(float volume);
        void setSoundsVolume(float volume);

    private:
        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;
        std::unordered_map<std::string, std::shared_ptr<sf::Font>> _fonts;
        std::unordered_map<std::string, std::shared_ptr<sf::Music>> _musics;
        std::unordered_map<std::string, std::shared_ptr<sf::Sound>> _sounds;
        std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> _soundbuffers;
};
