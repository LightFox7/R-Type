/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** room
*/

#ifndef FRONTROOM_HPP_
#define FRONTROOM_HPP_

#include <SFML/Graphics.hpp>
#include <string>

class front_room {
    public:
        front_room(int id, int nbPlayer, bool state);
        ~front_room() {}
        std::string getName() const;
        int getNbPlayer() const;
        bool getState() const;
        int getRoomId();
        std::string getMdp();
        void setNbPlayer(int nb);
        std::string getMsg();
        void setState(bool state) {
            _state = state;
        }

    protected:
    private:
        std::string _name;
        std::string mdp;
        int _nbPlayer;
        bool _state; // public or private
        int roomId;
};

#endif /* !FRONTROOM_HPP_ */
