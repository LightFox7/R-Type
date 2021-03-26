/*
** EPITECH PROJECT, 2020
** game-proto
** File description:
** Utils
*/

#pragma once

#include "Exception.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>


class Utils {
    public:
        static std::vector<std::string> strToWords(std::string const &str) {
            std::istringstream iss(str);
            std::vector<std::string> results(std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>());

            return (results);
        }
        static void loadIntInto(std::string const &str, int &to_load) {
            int val = 0;

            try {
                val = std::stoi(str);
            } catch (...) {
                throw (Exception("Invalid value to load int\n"));
                return;
            }
            to_load = val;
        }
        static void loadBoolInto(std::string const &str, bool &to_load) {
            bool val = 0;

            try {
                val = std::stoi(str);
            } catch (...) {
                throw (Exception(std::string("Invalid value to load bool : " + str + "\n").c_str()));
                return;
            }
            if (val != 1 && val != 0) {
                throw (Exception(std::string("Invalid value to load bool : " + str + "\n").c_str()));
                return;
            }
            to_load = val;
        }

    protected:
    private:
};
