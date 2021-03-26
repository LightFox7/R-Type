#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(Core &core) : _core(core)
{
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(200, 300), "PLAY", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(1200, 300), "OPTIONS", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttons.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(700, 700), "QUIT", sf::Color({170, 170, 170, 150}), sf::Color::White));

    _buttonsSelection.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(200, 700), "CREATE", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttonsSelection.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(1200, 700), "BACK", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttonsSelection.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(1200, 300), ">", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttonsSelection.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(200, 300), "<", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttonsOther.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(700, 300), "", sf::Color({170, 170, 170, 150}), sf::Color::White));

    _buttonsWaiting.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(200, 700), "BACK", sf::Color({170, 170, 170, 150}), sf::Color::White));
    _buttonsWaiting.push_back(std::make_shared<RectButton>(_core, mystructs::vector2d<float>(400, 100), 
    mystructs::vector2d<float>(1200, 700), "READY", sf::Color({170, 170, 170, 150}), sf::Color::White));

    _core.ressources.addTexture("menuback", "assets/r-type-menu.png");
    menuBackTexture = _core.ressources.getTexture("menuback");
    _core.id_room = 0;
}

MainMenu::~MainMenu()
{
    _core.ressources.removeTexture("menuback");
}

void handler(const boost::system::error_code &error, size_t bytes)
{
    std::cout << "Bytes transfered : " << bytes << std::endl;
}

void MainMenu::draw()
{
    if (!_core.window.isOpen())
        return;
    if (menuBackTexture) {
        menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
        _core.drawSprite(menuBackGround);
    }
    for (auto it : _buttons)
        it->draw();
    _core.playFrame();
}

void MainMenu::launchOptions()
{
    OptionMenu optionmenu(_core);

    optionmenu.loop();
}

void MainMenu::loop()
{
    while (!_core._quit && _core.window.isOpen()) {
        draw();
        for (auto it : _buttons)
            it->computeStatus();
        if (_buttons[MainMenu::buttonIdxs::QUIT]->getStatus() == Button::ButtonStatus::RELEASED)
            _core._quit = true;
        if (_buttons[MainMenu::buttonIdxs::OPTIONS]->getStatus() == Button::ButtonStatus::RELEASED)
            launchOptions();
        if (_buttons[MainMenu::buttonIdxs::PLAY]->getStatus() == Button::ButtonStatus::RELEASED)
            RoomSelection();
    }
}

void MainMenu::UpdateRoom()
{
    bool state = false;
    auto it = _core.listCommand.begin();

    _core._mutex.lock();
    for (size_t i = 0; i < _core.listCommand.size(); i++, it++) {
        if (it->code > 200)
            _core.listCommand.erase(it);
        if (it->code == Response::RoomCode::AddRoom) {
            state = it->running == 1 ? true : false;
            AddRoom(it->roomId, it->nbP, state);
            _core.listCommand.erase(it);
        }
    }
    _core._mutex.unlock();
}

void MainMenu::RoomSelection()
{
    Response::ResponseStruct data{};
    int i = listRooms.size() > 0 ? 0 : -1;
    int save = 0;
    unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    unsigned int tmp;
    std::string str;

    data.code = Response::RoomCode::WaitList;
    _core.socket.async_send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint, handler);

    while (!_core._quit && _core.window.isOpen()) {
        if (listRooms.size() == 0) {
            str = "NO ROOM";
            _buttonsOther[MainMenu::OtherIdxs::ROOM]->setText(str);
            i = -1;
        }
        if (listRooms.size() > 0 && i == -1) {
            if (listRooms.size() >= (size_t)save)
                i = save;
        }
        if (menuBackTexture) {
            menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
            _core.drawSprite(menuBackGround);
        }
        if (listRooms.size() > 0 && i > -1) {
            str = listRooms[i]->getMsg();
            _buttonsOther[MainMenu::OtherIdxs::ROOM]->setText(str);
        }
        for (auto it : _buttonsSelection)
            it->draw();
        for (auto it : _buttonsSelection)
            it->computeStatus();
        for (auto it : _buttonsOther)
            it->draw(3);
        for (auto it : _buttonsOther)
            it->computeStatus();
        _core.playFrame();
        if (_buttonsSelection[MainMenu::SelectionIdxs::RIGHT]->getStatus() == Button::ButtonStatus::RELEASED) {
            if ((size_t)i >= listRooms.size() - 1)
                i = 0;
            else
                i += 1;
        }
        if (_buttonsSelection[MainMenu::SelectionIdxs::LEFT]->getStatus() == Button::ButtonStatus::RELEASED) {
            if (i <= 0)
                i = listRooms.size() - 1;
            else
                i -= 1;
        }
        if (_buttonsSelection[MainMenu::SelectionIdxs::BACK]->getStatus() == Button::ButtonStatus::RELEASED)
            break;
        if (_buttonsSelection[MainMenu::SelectionIdxs::CREATE]->getStatus() == Button::ButtonStatus::RELEASED)
            create();
        if (_buttonsOther[MainMenu::OtherIdxs::ROOM]->getStatus() == Button::ButtonStatus::RELEASED && listRooms.size() > 0 && listRooms[i]->getState() == false)
            join(i);
        tmp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if (tmp - ms > 500) {
            save = i;
            ms = tmp;
            _core.socket.async_send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint, handler);
            listRooms.clear();
        }
        UpdateRoom();
    }
}

void MainMenu::playGame()
{
    Response::ResponseStruct data{};
    bool state = false;
    std::string message = "Waiting for other players...";

    data.code = Response::RoomCode::Connection;
    _core.socket.send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint);
    data.code = Response::RoomCode::Ready;
    data.roomId = _core.id_room;
    std::strcpy(data.pseudo, "UgoLeBG");
    std::strcpy(data.roomName, "RoomDesBG");
    std::strcpy(data.password, "MdpDesBG");
    std::strcpy(data.event, "NMP");
    _core.socket.async_send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint, handler);


    auto it = _core.listCommand.begin();
    while (!_core._quit && _core.window.isOpen()) {
        if (menuBackTexture) {
            menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
            _core.drawSprite(menuBackGround);
        }
        _core.drawText(*_core.ressources.getFont("yoster"), message, 50, mystructs::vector2d<int>(500, 300), sf::Color::White, 2, sf::Color::White, false);
        _core.playFrame();
        _core._mutex.lock();
        for (size_t i = 0; i < _core.listCommand.size(); i++, it++) {
            if (it->code == Response::RoomCode::GameStart) {
                _core.listCommand.erase(it);
                state = true;
                break;
            }
        }
        if (it == _core.listCommand.end())
            it = _core.listCommand.begin();
        _core._mutex.unlock();
        if (state == true) {
            Game game(_core);
            game.loop();
            break;
        }
    }
}

void MainMenu::create()
{
    Response::ResponseStruct data{};
    bool state = false;

    data.code = Response::RoomCode::Connection;
    _core.socket.send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint);
    data.code = Response::RoomCode::CreateRoom;
    data.roomId = _core.id_room;
    std::strcpy(data.pseudo, "UgoLeBG");
    std::strcpy(data.roomName, "RoomDesBG");
    std::strcpy(data.password, "MdpDesBG");
    std::strcpy(data.event, "NMP");
    _core.socket.async_send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint, handler);

    auto it = _core.listCommand.begin();
    while (!_core._quit && _core.window.isOpen()) {
        if (menuBackTexture) {
            menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
            _core.drawSprite(menuBackGround);
        }
        _core.playFrame();
        _core._mutex.lock();
        for (size_t i = 0; i < _core.listCommand.size(); i++, it++) {
            if (it->code == Response::RoomCode::RoomCreated) {
                _core.id_room = it->roomId;
                _core.listCommand.erase(it);
                state = true;
                break;
            }
        }
        if (it == _core.listCommand.end())
            it = _core.listCommand.begin();
        _core._mutex.unlock();
        if (state == true) {
            waitingRoom();
            break;
        }
    }
}

void MainMenu::join(int i)
{
    Response::ResponseStruct data{};
    bool state = false;

    data.code = Response::RoomCode::Connection;
    _core.socket.send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint);
    _core.id_room = listRooms[i]->getRoomId();
    data.code = Response::RoomCode::JoinRoom;
    data.roomId = _core.id_room;
    _core.socket.async_send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint, handler);

    auto it = _core.listCommand.begin();
    while (!_core._quit && _core.window.isOpen()) {
        _core.playFrame();
        _core._mutex.lock();
        for (size_t i = 0; i < _core.listCommand.size(); i++, it++) {
            if (it->code == Response::RoomCode::JoindedRoom && it->port == _core.port) {
                _core.listCommand.erase(it);
                state = true;
                break;
            }
        }
        if (it == _core.listCommand.end())
            it = _core.listCommand.begin();
        _core._mutex.unlock();
        if (state == true) {
            waitingRoom();
            break;
        }
    }
}

void MainMenu::RoomCreation()
{

}

void MainMenu::AddRoom(int roomId, int nbP, bool state)
{
    bool exist = false;

    for (size_t i = 0; i < listRooms.size(); i++) {
        if (listRooms[i]->getRoomId() == roomId) {
            exist = true;
            listRooms[i]->setNbPlayer(nbP);
            listRooms[i]->setState(state);
        }
    }
    if (exist == false) {
        listRooms.push_back(std::make_shared<front_room>(roomId, nbP, state));
    }
}

void MainMenu::waitingRoom()
{
     while (!_core._quit && _core.window.isOpen()) {
        if (menuBackTexture) {
            menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
            _core.drawSprite(menuBackGround);
        }
        for (auto it : _buttonsWaiting)
            it->draw();
        for (auto it : _buttonsWaiting)
            it->computeStatus();
        if (_buttonsWaiting[WaitingIdxs::GO_BACK]->getStatus() == Button::ButtonStatus::RELEASED)
            break;
        if (_buttonsWaiting[WaitingIdxs::LAUNCH]->getStatus() == Button::ButtonStatus::RELEASED) {
            playGame();
            break;
        }
        _core.playFrame();
     }
     leaveRoom();
}

void MainMenu::leaveRoom()
{
    Response::ResponseStruct data{};
    bool state = false;

    data.code = Response::RoomCode::Connection;
    _core.socket.send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint);
    data.code = Response::RoomCode::LeaveRoom;
    data.roomId = _core.id_room;
    _core.socket.async_send_to(boost::asio::buffer((char *)&data, sizeof(data)), _core.receiver_endpoint, handler);

    auto it = _core.listCommand.begin();
    while (!_core._quit && _core.window.isOpen()) {
        if (menuBackTexture) {
            menuBackGround.setTexture(*_core.ressources.getTexture("menuback"));
            _core.drawSprite(menuBackGround);
        }
        _core.playFrame();
        _core._mutex.lock();
        for (size_t i = 0; i < _core.listCommand.size(); i++, it++) {
            if (it->code == Response::RoomCode::RoomLeaved && it->port == _core.port) {
                _core.listCommand.erase(it);
                state = true;
                break;
            }
        }
        if (it == _core.listCommand.end())
            it = _core.listCommand.begin();
        _core._mutex.unlock();
        if (state == true)
            break;
    }
    _core.listCommand.clear();
}