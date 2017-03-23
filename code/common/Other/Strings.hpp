#ifndef PROJET_STRINGS_HPP
#define PROJET_STRINGS_HPP

#include <string>

static const std::string GAME_STARTING_STRING = "GameStarting";
static const std::string CLASSIC_MODE = "ClassicMode";
static const std::string TIMED_MODE = "TimedMode";
static const std::string TEAM_MODE = "TeamMode";

static const std::string GAME_IN_PROGRESS_REQUEST = "games";
static const std::string POP_GAME_REQUEST = "PopGame";
static const std::string LEAVE_QUEUE_REQUEST = "LEAVEQUEUE";
static const std::string GAME_STARTED_STRING = "GameStartedStopListeningMatchmaker";

static const std::string PLACE_TOWER_COMMAND_STRING = "PlaceTower";
static const std::string DELETE_TOWER_COMMAND_STRING  = "DeleteTower";
static const std::string UPGRADE_TOWER_COMMAND_STRING = "UpgradeTower";
static const std::string SEND_MESSAGE_STRING = "SendMessage";
static const std::string RECEIVE_MESSAGE_STRING = "ReceiveMessage";
static const std::string NUCLEAR_BOMB_COMMAND_STRING = "NuclearBomb";
static const std::string FREEZE_PNJS_COMMAND_STRING = "FreezeSpell";
static const std::string AIR_STRIKE_COMMAND_STRING = "AirStrike";
static const std::string AD_SPELL_COMMAND_STRING = "adSpell";


static const std::string JOIN_GAME_AS_SPECTATOR = "Support";
static const std::string SUPPORT_PLAYER_STRING = "SupportPlayer";

static const std::string SETUP_GAME = "SetupGame";
static const std::string END_OF_GAME = "end";
static const std::string CHANGE_USERNAME = "CHANGEUSERNAME";
static const std::string CHANGE_PASSWORD = "CHANGEPASSWORD";
static const std::string CHANGE_ICON = "CHANGEICON";

static const std::string MESSAGES[3] = {"GG Easy", "Report", "J'aime les patates"};

static const std::string GET_FRIENDLIST = "getFriendList;";
static const std::string GET_FRIEND_REQUESTS = "getFriendRequests;";
static const std::string GET_PENDING_INVITATIONS = "getPendingInvitations;";
static const std::string ADD_FRIEND = "addFriend;";
static const std::string REMOVE_FRIEND = "removeFriend;";
static const std::string ACCEPT_FRIEND_REQUEST = "acceptFriendRequest;";
static const std::string DECLINE_FRIEND_REQUEST = "declineFriendRequest;";
static const std::string GET_PROFILE = "getProfileByUsername;";

// Towers
static const std::string GUN_TOWER_STR = "GunTower";
static const std::string GUN_TOWER_CHAR = "\033[31m♜\033[0m  ";

static const std::string SNIPER_TOWER_STR = "SniperTower";
static const std::string SNIPER_TOWER_CHAR = "\033[31m✛\033[0m  ";

static const std::string SHOCK_TOWER_STR = "ShockTower";
static const std::string SHOCK_TOWER_CHAR = "\033[31m⚡\033[0m  ";

static const std::string MISSILE_TOWER_STR = "MissileTower";
static const std::string MISSILE_TOWER_CHAR = "\033[31m☢\033[0m  ";

// PNJs
static const std::string MEXICAN_PNJ_STR = "MexicanPnj";
static const std::string MEXICAN_PNJ_CHAR = "\033[33m♿\033[0m  ";

static const std::string COMMUNIST_PNJ_STR = "CommunistPnj";
static const std::string COMMUNIST_PNJ_CHAR = "\033[33m☭\033[0m  ";

static const std::string MUSLIM_PNJ_STR = "MuslimPnj";
static const std::string MUSLIM_PNJ_CHAR = "\033[33m☪\033[0m  ";

#endif //PROJET_STRINGS_HPP
