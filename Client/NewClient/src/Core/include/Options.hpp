#pragma once

#include "Structs.hpp"
#include "Utils.hpp"
#include <SFML/Window.hpp>

static const float base_window_sizex = 1920;
static const float base_window_sizey = 1080;
static const std::vector<int> antialiasinglevels = {0, 2, 4, 8, 16};
static const std::vector<int> maxframerates = {25, 30, 50, 59, 60, 75, 100, 120, 144};
static const std::vector<mystructs::vector2d<int>> resolutions = {
    {640, 480},
    {1024, 576},
    {800, 600},
    {1152, 648},
    {960, 720},
    {1280, 720},
    {1024, 768},
    {1366, 768},
    {1440, 900},
    {1600, 900},
    {1280, 960},
    {1400, 1050},
    {1680, 1050},
    {1440, 1080},
    {1920, 1080},
    {1920, 1200},
    {1600, 1200},
    {1856, 1392},
    {1920, 1440},
    {2560, 1440},
    {2048, 1536},
    {2560, 1600},
    {3840, 2160}
};
static const std::vector<int> possiblevolumelevels = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};


class Options {
    public:
        Options() {
            resolution.x = sf::VideoMode::getDesktopMode().width;
            resolution.y = sf::VideoMode::getDesktopMode().height;
            fullscreen = false;
            vsync = false;
            printfps = false;
            maxframerate = 60;
            mastervolume = 50;
            effectsvolume = 50;
            bgmvolume = 50;
            antialiasinglevel = 0;
        };
        Options(const std::string &filepath) {
            resolution.x = sf::VideoMode::getDesktopMode().width;
            resolution.y = sf::VideoMode::getDesktopMode().height;
            fullscreen = false;
            vsync = false;
            printfps = false;
            maxframerate = 60;
            mastervolume = 50;
            effectsvolume = 50;
            bgmvolume = 50;
            antialiasinglevel = 0;

            std::string line;
            std::vector<std::string> tab;
            std::vector<std::string> words;
            std::ifstream in(filepath);

            if (in.is_open()) {
                while (getline(in, line))
                    tab.push_back(line);
                in.close();
            }
            try {
                for (auto it : tab) {
                    words = Utils::strToWords(it);
                    if (words[0] == "resolution.x:")
                        Utils::loadIntInto(words[1], resolution.x);
                    if (words[0] == "resolution.y:")
                        Utils::loadIntInto(words[1], resolution.y);
                    if (words[0] == "maxframerate:")
                        Utils::loadIntInto(words[1], maxframerate);
                    if (words[0] == "fullscreen:")
                        Utils::loadBoolInto(words[1], fullscreen);
                    if (words[0] == "vsync:")
                        Utils::loadBoolInto(words[1], vsync);
                    if (words[0] == "printfps:")
                        Utils::loadBoolInto(words[1], printfps);
                    if (words[0] == "antialiasing:")
                        Utils::loadIntInto(words[1], antialiasinglevel);
                    if (words[0] == "mastervolume:")
                        Utils::loadIntInto(words[1], mastervolume);
                    if (words[0] == "effectsvolume:")
                        Utils::loadIntInto(words[1], effectsvolume);
                    if (words[0] == "bgmvolume:")
                        Utils::loadIntInto(words[1], bgmvolume);
                }
            } catch (Exception &err) {
                std::cerr << err.what() << std::endl;
            }
            antialiasinglevel = adjustantialiasing(antialiasinglevel);
            maxframerate = adjustmaxframerate(maxframerate);
            resolution = adjustresolution(resolution);
            mastervolume = adjustvolume(mastervolume);
            effectsvolume = adjustvolume(effectsvolume);
            bgmvolume = adjustvolume(bgmvolume);
            save(filepath);
        }
        ~Options() = default;
        void load(const std::string &filepath) {
            std::string line;
            std::vector<std::string> tab;
            std::vector<std::string> words;
            std::ifstream in(filepath);

            if (in.is_open()) {
                while (getline(in, line))
                    tab.push_back(line);
                in.close();
            }
            try {
                for (auto it : tab) {
                    words = Utils::strToWords(it);
                    if (words[0] == "resolution.x:")
                        Utils::loadIntInto(words[1], resolution.x);
                    if (words[0] == "resolution.y:")
                        Utils::loadIntInto(words[1], resolution.y);
                    if (words[0] == "maxframerate:")
                        Utils::loadIntInto(words[1], maxframerate);
                    if (words[0] == "fullscreen:")
                        Utils::loadBoolInto(words[1], fullscreen);
                    if (words[0] == "vsync:")
                        Utils::loadBoolInto(words[1], vsync);
                    if (words[0] == "printfps:")
                        Utils::loadBoolInto(words[1], printfps);
                    if (words[0] == "antialiasing:")
                        Utils::loadIntInto(words[1], antialiasinglevel);
                    if (words[0] == "mastervolume:")
                        Utils::loadIntInto(words[1], mastervolume);
                    if (words[0] == "effectsvolume:")
                        Utils::loadIntInto(words[1], effectsvolume);
                    if (words[0] == "bgmvolume:")
                        Utils::loadIntInto(words[1], bgmvolume);
                }
            } catch (Exception &err) {
                std::cerr << err.what() << std::endl;
            }
            antialiasinglevel = adjustantialiasing(antialiasinglevel);
            maxframerate = adjustmaxframerate(maxframerate);
            resolution = adjustresolution(resolution);
            mastervolume = adjustvolume(mastervolume);
            effectsvolume = adjustvolume(effectsvolume);
            bgmvolume = adjustvolume(bgmvolume);
            save(filepath);
        }
        void save(const std::string &file) {
            std::ofstream stream(file);

            if (!stream.is_open())
                return;
            stream << "resolution.x: " << resolution.x << std::endl;
            stream << "resolution.y: " << resolution.y << std::endl;
            stream << "fullscreen: " << fullscreen << std::endl;
            stream << "vsync: " << vsync << std::endl;
            stream << "antialiasing: " << antialiasinglevel << std::endl;
            stream << "printfps: " << printfps << std::endl;
            stream << "maxframerate: " << maxframerate << std::endl;
            stream << "mastervolume: " << mastervolume << std::endl;
            stream << "effectsvolume: " << effectsvolume << std::endl;
            stream << "bgmvolume: " << bgmvolume << std::endl;
        }
        void operator=(Options const &options) {
                this->resolution = options.resolution;
                this->fullscreen = options.fullscreen;
                this->vsync = options.vsync;
                this->printfps = options.printfps;
                this->maxframerate = options.maxframerate;
                this->mastervolume = options.mastervolume;
                this->effectsvolume = options.effectsvolume;
                this->bgmvolume = options.bgmvolume;
                this->antialiasinglevel = options.antialiasinglevel;
        };
        friend bool operator==(Options const &options1, Options const &options2) {
            if (options1.resolution == options2.resolution && options1.fullscreen == options2.fullscreen
            && options1.vsync == options2.vsync && options1.printfps == options2.printfps &&
            options1.maxframerate == options2.maxframerate && options1.mastervolume == options2.mastervolume
            && options1.effectsvolume == options2.effectsvolume && options1.bgmvolume == options2.bgmvolume
            && options1.antialiasinglevel == options2.antialiasinglevel)
                return (true);
            return (false);
        }
        static int adjustvolume(int const &volume) {
            if (volume < possiblevolumelevels[0])
                return (possiblevolumelevels[0]);
            if (volume > possiblevolumelevels[possiblevolumelevels.size() - 1])
                return (possiblevolumelevels[possiblevolumelevels.size() - 1]);
            for (std::size_t i = 0; i < possiblevolumelevels.size(); i++) {
                if (volume == possiblevolumelevels[i])
                    return (possiblevolumelevels[i]);
                if (i < (possiblevolumelevels.size() - 1) && volume >= possiblevolumelevels[i]
                && volume < possiblevolumelevels[i + 1])
                    return (possiblevolumelevels[i]);
            }
            return (possiblevolumelevels[0]);
        };
        static int adjustantialiasing(int const &antialiasinglevel) {
            if (antialiasinglevel < antialiasinglevels[0])
                return (antialiasinglevels[0]);
            if (antialiasinglevel > antialiasinglevels[antialiasinglevels.size() - 1])
                return (antialiasinglevels[antialiasinglevels.size() - 1]);
            for (std::size_t i = 0; i < antialiasinglevels.size(); i++) {
                if (antialiasinglevel == antialiasinglevels[i])
                    return (antialiasinglevels[i]);
                if (i < (antialiasinglevels.size() - 1) && antialiasinglevel >= antialiasinglevels[i]
                && antialiasinglevel < antialiasinglevels[i + 1])
                    return (antialiasinglevels[i]);
            }
            return (antialiasinglevels[0]);
        }
        static mystructs::vector2d<int> adjustresolution(mystructs::vector2d<int> const &res) {
            for (auto it : resolutions)
                if (res == it)
                    return (it);
            return (resolutions[0]);
        }
        static int adjustmaxframerate(int const &framerate)
        {
            if (framerate < maxframerates[0])
                return (maxframerates[0]);
            if (framerate > maxframerates[maxframerates.size() - 1])
                return (maxframerates[maxframerates.size() - 1]);
            for (std::size_t i = 0; i < maxframerates.size(); i++) {
                if (maxframerates[i] == framerate)
                    return (maxframerates[i]);
                if (i < (maxframerates.size() - 1) && framerate >= maxframerates[i] && framerate < maxframerates[i + 1])
                    return (maxframerates[i]);
            }
            return (maxframerates[0]);
        }

        mystructs::vector2d<int> resolution;
        bool fullscreen;
        bool vsync;
        bool printfps;
        int maxframerate;
        int mastervolume;
        int effectsvolume;
        int bgmvolume;
        int antialiasinglevel;
};
