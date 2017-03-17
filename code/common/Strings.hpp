#ifndef PROJET_STRINGS_HPP
#define PROJET_STRINGS_HPP

#include <string>

#define GAME_STARTING_STRING "GameStarting"
#define CLASSIC_MODE "ClassicMode"
#define TIMED_MODE "TimedMode"
#define TEAM_MODE "TeamMode"

#define GAME_IN_PROGRESS_REQUEST "games"

static const std::string PLACE_TOWER_COMMAND_STRING =  "PlaceTower";
static const std::string DELETE_TOWER_COMMAND_STRING  = "DeleteTower";
static const std::string UPGRADE_TOWER_COMMAND_STRING = "UpgradeTower";
static const std::string USER_MESSAGE_STRING = "SendUserMessage";
static const std::string RECEIVE_USER_MESSAGE_STRING = "ReceiveUserMessage";

static const std::string JOIN_GAME_AS_SPECTATOR = "Support";
static const std::string SUPPORT_PLAYER_STRING = "SupportPlayer";

#define SETUP_GAME "SetupGame"
#define END_OF_GAME "end"

#define GET_FRIENDLIST "getFriendList;"
#define GET_FRIEND_REQUESTS "getFriendRequests;"
#define GET_PENDING_INVITATIONS "getPendingInvitations;"
#define ADD_FRIEND "addFriend;"
#define REMOVE_FRIEND "removeFriend;"
#define ACCEPT_FRIEND_REQUEST "acceptFriendRequest;"
#define DECLINE_FRIEND_REQUEST "declineFriendRequest;"
#define GET_PROFILE "getProfileByUsername;"

// Towers
#define GUN_TOWER_STR "GunTower"
#define GUN_TOWER_CHAR "\033[31m♜\033[0m  "

#define SNIPER_TOWER_STR "SniperTower"
#define SNIPER_TOWER_CHAR "\033[31m✛\033[0m  "

#define SHOCK_TOWER_STR "ShockTower"
#define SHOCK_TOWER_CHAR "\033[31m⚡\033[0m  "

#endif //PROJET_STRINGS_HPP
