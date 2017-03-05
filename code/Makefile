all: server client


SERVERFILES = server/ServerLauncher.cpp common/Networking.cpp server/Server.cpp server/AccountServer.cpp server/Database.cpp \
                       common/Credentials.cpp common/Account.cpp server/Command.cpp server/LoginRegisterCommand.cpp \
                       server/MatchmakingCommand.cpp server/MatchMaker.cpp server/PendingMatch.cpp \
                       common/GameState.cpp server/GameServer.cpp server/TowerCommand.cpp server/Timer.cpp \
                       server/FriendListCommand.cpp common/AbstractTower.cpp server/PlayerConnection.cpp common/PlayerState.cpp common/Wave.cpp \
                       common/PNJ.cpp common/Position.cpp common/Map.cpp server/GameEngine.cpp server/GameEngine.hpp common/Constants.h common/Direction.h \
                       common/AttackTower.cpp common/Tools.hpp common/Tools.cpp server/UpdateStatsCommand.cpp common/GunTower.cpp common/ShockTower.cpp common/SniperTower.cpp

CLIENTFILES = client/NetworkedManager.cpp client/ClientLauncher.cpp client/LoginManager.cpp client/LoginUI.cpp \
                      client/RegisterManager.cpp client/RegisterUI.cpp common/Networking.cpp common/Credentials.cpp \
                      client/MainManager.cpp client/MainUI.cpp common/Map.cpp client/Drawing.cpp client/Drawing.hpp client/RankingManager.cpp client/RankingUI.cpp client/GameLauncher.cpp\
                      client/FriendListManager.cpp client/FriendListUI.cpp common/AbstractTower.cpp \
                      client/ProfileUI.cpp common/Position.cpp client/App.cpp client/App.hpp client/AbstractManager.cpp \
                      client/WelcomeManager.cpp client/WelcomeUI.cpp client/FriendList.cpp client/GameManager.cpp \
                      client/ProfileManager.cpp common/PNJ.cpp client/GameUI.cpp common/PlayerState.cpp \
                      common/GameState.cpp common/Wave.cpp common/Constants.h common/AttackTower.cpp common/Tools.hpp\
                      common/Tools.cpp client/SpectatorManager.cpp client/SpectatorManager.hpp client/SpectatorUI.cpp\
                      client/SpectatorUI.hpp client/GameInfo.cpp common/GunTower.cpp common/ShockTower.cpp common/SniperTower.cpp

WARNINGS = -Wall -Wextra

server: $(SERVERFILES)
	g++ -std=c++11 $(SERVERFILES) -o output/Server -pthread \
	-I/usr/include -lsqlite3 -lcrypt

client: $(CLIENTFILES)
	g++ -std=c++11 $(CLIENTFILES) -o output/Client -pthread \
	-I/usr/include -lsqlite3 -lcrypt