﻿#include "../Header/Main.h"
int Cheat::CheatFeatures::selectedPlayer;
float TeleportFoward = 1.f;																					//Used by Teleport Forward option
int engine_multiplier, torque_multiplier;																	//Used by Vehicle Multipliers options
int SetTimeHour = 0, SetTimeMinutes = 0, SetTimeSeconds = 0;												//Used by World Time options	
int SessionTimeHour, SessionTimeMinutes, SessionTimeSeconds;												//Used by Session Time option
int VehiclePrimaryColorRed, VehiclePrimaryColorGreen, VehiclePrimaryColorBlue;								//Used by Vehicle Color features
int VehicleSecondaryColorRed, VehicleSecondaryColorGreen, VehicleSecondaryColorBlue;						//Used by Vehicle Color features	
int VehicleNeonLightRed, VehicleNeonLightGreen, VehicleNeonLightBlue;										//Used by Vehicle Color features	
int WheelColorRed, WheelColorGreen, WheelColorBlue;															//Used by Vehicle Color features
int PlayerWantedLevelInteger = 0;																			//Used by Set Wanted Level Option
int intexploits, intoffensive, REPORTSTRENGTH, OFFENSIVETAGPLATE, OFFENSIVEUGC,								//Used by Report Stats		
    EXPLOITS, GRIEFING, COMMENDSTRENGTH, FRIENDLY, HELPFUL, VCANNOYINGME, VCHATE,						
	BADCREWNAME, BADCREWMOTTO, BADCREWSTATUS, BADCREWEMBLEM, ISPUNISHED;		
int SetPedTexture_Torso = 0, SetPedTexture_TorsoTexture = 0, SetPedTexture_Face = 0,						//Used by SetPedTexture
    SetPedTexture_FaceTexture = 0, SetPedTexture_Head = 0, SetPedTexture_HeadTexture = 0, 
	SetPedTexture_Hair = 0, SetPedTexture_HairTexture = 0, SetPedTexture_Legs = 0, 
	SetPedTexture_LegsTexture = 0, SetPedTexture_Hands = 0, SetPedTexture_HandsTexture = 0, 
	SetPedTexture_Feet = 0, SetPedTexture_FeetTexture = 0, SetPedTexture_Eyes = 0,
	SetPedTexture_EyesTexture = 0, SetPedTexture_Accesories = 0, SetPedTexture_AccesoriesTexture = 0, 
	SetPedTexture_AccesoriesSec = 0, SetPedTexture_AccesoriesSecTexture = 0, SetPedTexture_Textures = 0, 
	SetPedTexture_TexturesTexture = 0, SetPedTexture_TorsoSec = 0,  SetPedTexture_TorsoSecTexture = 0;

void Cheat::FiberMain()
{ 
	Cheat::CheatFeatures::NonLooped();
	while (true)
	{
		Cheat::CheatFunctions::LoopedFunctions();

		switch (Cheat::GUI::currentMenu) {
		case MainMenu:
		{
			Cheat::GUI::Title("Main Menu");
			Cheat::GUI::MenuOption("Self Options", SelfOptionsMenu);
			Cheat::GUI::MenuOption("Online Options", OnlineOptionsMenu);
			Cheat::GUI::MenuOption("Weapon Options", weaponmenu);
			Cheat::GUI::MenuOption("Vehicle Options", vehiclemenu);
			Cheat::GUI::MenuOption("Teleport Options", teleportmenu);
			Cheat::GUI::MenuOption("World Options", worldmenu);
			Cheat::GUI::MenuOption("Misc Options", miscmenu);
			Cheat::GUI::MenuOption("Settings", SettingsMenu);
		}
		break;
		case AllPlayersMenu:
		{
			Cheat::GUI::Title("All Players");
			Cheat::GUI::MenuOption("ESP", ESPMenu);
			Cheat::GUI::MenuOption("Weapon Options", allplayers_weaponoptionsmenu);
			Cheat::GUI::MenuOption("Troll Options", allplayers_trolloptionsmenu);
			if (Cheat::GUI::Option("Host Kick All Players", "Kick all players from session - Host only")) 
			{
				for (int i = 1; i <= 32; i++)
				{
					if (Cheat::GameFunctions::PlayerID != i) { NETWORK::NETWORK_SESSION_KICK_PLAYER(i); }
				}
			}
		}
		break;
		case allplayers_weaponoptionsmenu:
		{
			Cheat::GUI::Title("Weapon Options");
			if (Cheat::GUI::Option("Give All Weapons", "Give all players all weapons"))
			{
				for (int i = 0; i < 32; i++) 
				{
					if (Cheat::GameFunctions::PlayerID != i) 
					{
						Cheat::GameFunctions::SubtitleNotification("Giving all weapons to all players in session, one moment", 2000);
						Cheat::GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			}
		}
		break; 
		case allplayers_trolloptionsmenu:
		{
			Cheat::GUI::Title("Troll Options"); 
			Cheat::GUI::Toggle("Freeze All Players", Cheat::CheatFeatures::FreezeAllPlayersBool, "Freeze all players in session", false);
			if (Cheat::GUI::Option("Kick All Out Of Vehicle", "Kick all players from their vehicle"))
			{
				for (int i = 0; i < 32; i++)
				{
					if (Cheat::GameFunctions::PlayerID != i)
					{
						Cheat::GameFunctions::RequestNetworkControlOfEntity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_TASKS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						AI::CLEAR_PED_SECONDARY_TASK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					}
				}
			}
			if (Cheat::GUI::Option("Airstrike All Players", ""))
			{
				for (int i = 1; i < 32; i++) {
					if (Cheat::GameFunctions::PlayerID != i) {
						Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1);
						Coords.z += 15;
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, 1, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 1, 1, 500);
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 30, Coords.x, Coords.y, Coords.z, 250, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), 0, 1, 1, 500);
						GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 55, Coords.x, Coords.y, Coords.z, 100, false, 0xF8A3939F, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true, true, 600);
					}
				}
			}
			if (Cheat::GUI::Option("Trap All Players", ""))
			{
				for (int i = 1; i < 32; i++) {
					if (Cheat::GameFunctions::PlayerID != i) 
					{
						Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0);
						OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
					}
				}
			}
			if (Cheat::GUI::Option("Attach Beach Fire", "Burn them all!")) 
			{ 
				for (int i = 1; i <= 32; i++) 
				{
					if (Cheat::GameFunctions::PlayerID != i) 
					{
						Cheat::GameFunctions::AttachObjectToPed(i, "prop_beach_fire");
					}
				}
			}
		}
		break;
		case OnlineOptionsMenu:
		{
			Cheat::GUI::Title("Online Options");
			Cheat::GUI::MenuOption("Player List", PlayerListMenu);
			Cheat::GUI::MenuOption("All Players", AllPlayersMenu);
			Cheat::GUI::MenuOption("Protections", protections);
			Cheat::GUI::MenuOption("Stats Options", statsoptionsmenu);
			Cheat::GUI::MenuOption("Session Options", sessionoptionsmenu);
			Cheat::GUI::Toggle("Off Radar", Cheat::CheatFeatures::OffRadarBool, "Enables Lester Off Radar Feature");
			Cheat::GUI::Toggle("No Idle Kick", Cheat::CheatFeatures::NoIdleKickBool, "Does not work when out of game focus");
			Cheat::GUI::Toggle("Bribe Authorities", Cheat::CheatFeatures::BribeAuthoritiesBool, "Enables Bribe Authorities");
			if (Cheat::GUI::Option("Get Empty Session", "Get Empty (Public) Session")) { Sleep(10000); }
		}
		break; 
		case sessionoptionsmenu:
		{
			Cheat::GUI::Title("Session Options");
			Cheat::GUI::MenuOption("Session Weather", sessionweathermenu);
			Cheat::GUI::MenuOption("Session Time", sessiontimemenu);
			Cheat::GUI::MenuOption("Chat", SessionChatMenu);
		}
		break;
		case SessionChatMenu:
		{
			Cheat::GUI::Title("Session Chat");
			Cheat::GUI::Toggle("Log Chat Messages", Cheat::CheatFeatures::LogChatMessages, "Chat gets logged to console");
		}
		break;
		case sessiontimemenu:
		{
			Cheat::GUI::Title("Session Time");
			Cheat::GUI::Int("Hour", SessionTimeHour, 0, 23, 1, false);
			Cheat::GUI::Int("Minutes", SessionTimeMinutes, 0, 59, 1, false);
			Cheat::GUI::Int("Seconds", SessionTimeSeconds, 0, 59, 1, false);
			if (Cheat::GUI::Option("Set Time", ""))
			{
				if (NETWORK::NETWORK_IS_SESSION_STARTED())
				{
					Cheat::GameFunctions::SetSessionTime(SessionTimeHour, SessionTimeMinutes, SessionTimeSeconds);
				}
			}
		}
		break;
		case sessionweathermenu:
		{
			Cheat::GUI::Title("Session Weather");
			if (NETWORK::NETWORK_IS_SESSION_STARTED())
			{
				if (Cheat::GUI::Option("Extra Sunny", "")) { GameHooking::session_weather(true, 0, 76, 0); }
				if (Cheat::GUI::Option("Clear", "")) { GameHooking::session_weather(true, 1, 76, 0); }
				if (Cheat::GUI::Option("Clouds", "")) { GameHooking::session_weather(true, 2, 76, 0); }
				if (Cheat::GUI::Option("Smog", "")) { GameHooking::session_weather(true, 3, 76, 0); }
				if (Cheat::GUI::Option("Foggy", "")) { GameHooking::session_weather(true, 4, 76, 0); }
				if (Cheat::GUI::Option("Overcast", "")) { GameHooking::session_weather(true, 5, 76, 0); }
				if (Cheat::GUI::Option("Rain", "")) { GameHooking::session_weather(true, 6, 76, 0); }
				if (Cheat::GUI::Option("Thunder", "")) { GameHooking::session_weather(true, 7, 76, 0); }
				if (Cheat::GUI::Option("Clearing", "")) { GameHooking::session_weather(true, 8, 76, 0); }
				if (Cheat::GUI::Option("Neutral", "")) { GameHooking::session_weather(true, 9, 76, 0); }
				if (Cheat::GUI::Option("Snow", "")) { GameHooking::session_weather(true, 10, 76, 0); }
				if (Cheat::GUI::Option("Blizzard", "")) { GameHooking::session_weather(true, 11, 76, 0); }
				if (Cheat::GUI::Option("Snowlight", "")) { GameHooking::session_weather(true, 12, 76, 0); }
				if (Cheat::GUI::Option("Xmas", "")) { GameHooking::session_weather(true, 13, 76, 0); }
				if (Cheat::GUI::Option("Halloween", "")) { GameHooking::session_weather(true, 14, 76, 0); }
			}
			else
			{
				Cheat::GUI::Break("GTA Online Only", false);
			}
		}
		break; 
		case statsoptionsmenu:
		{
			Cheat::GUI::Title("Stats Options"); 
			Cheat::GUI::MenuOption("Reports", reportsmenu_stats);
			Cheat::GUI::MenuOption("Rank", rankmenu); 
			Cheat::GUI::MenuOption("Unlocks", unlocksmenu);
			Cheat::GUI::MenuOption("Misc Stats", miscstatsmenu);
		}
		break; 
		case reportsmenu_stats:
		{
			Cheat::GUI::Title("Reports"); 
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"),	&REPORTSTRENGTH,	-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GAME_EXPLOITS"),		&intexploits,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), &intoffensive,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), &OFFENSIVETAGPLATE, -1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"),		&OFFENSIVEUGC,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_EXPLOITS"),			&EXPLOITS,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_GRIEFING"),			&GRIEFING,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"),	&COMMENDSTRENGTH,	-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_FRIENDLY"),			&FRIENDLY,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_HELPFUL"),			&HELPFUL,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_ANNOYINGME"),		&VCANNOYINGME,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VC_HATE"),			&VCHATE,			-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_NAME"),		&BADCREWNAME,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"),		&BADCREWMOTTO,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"),	&BADCREWSTATUS,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"),	&BADCREWEMBLEM,		-1);
			STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_ISPUNISHED"),			&ISPUNISHED,		-1);
			Cheat::GUI::Option("Report Strength: " + std::to_string(REPORTSTRENGTH), "");
			Cheat::GUI::Option("Game Exploits: " + std::to_string(intexploits), "");
			Cheat::GUI::Option("Offensive Language: " + std::to_string(intoffensive), "");
			Cheat::GUI::Option("Offensive Tagplate: " + std::to_string(OFFENSIVETAGPLATE), "");
			Cheat::GUI::Option("Offensive UGC: " + std::to_string(OFFENSIVEUGC), "");
			Cheat::GUI::Option("Exploits: " + std::to_string(EXPLOITS), "");
			Cheat::GUI::Option("Griefing: " + std::to_string(GRIEFING), "");
			Cheat::GUI::Option("Friendly: " + std::to_string(FRIENDLY), "");
			Cheat::GUI::Option("Helpful: " + std::to_string(HELPFUL), "");
			Cheat::GUI::Option("VC Annoying Me: " + std::to_string(VCANNOYINGME), "");
			Cheat::GUI::Option("Vchate: " + std::to_string(VCHATE), "");
			Cheat::GUI::Option("Bad Crew Name: " + std::to_string(BADCREWNAME), "");
			Cheat::GUI::Option("Bad Crew Motto: " + std::to_string(BADCREWMOTTO), "");
			Cheat::GUI::Option("Bad Crew Status: " + std::to_string(BADCREWSTATUS), "");
			Cheat::GUI::Option("Bad Crew Emblem: " + std::to_string(BADCREWEMBLEM), "");
			Cheat::GUI::Option("Is Punished: " + std::to_string(ISPUNISHED), "");
		}
		break; 
		case unlocksmenu:
		{
			Cheat::GUI::Title("Unlocks");
			if (Cheat::GUI::Option("Unlock All", "Unlocks most unlockable GTA Online items")) 
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_11")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_12")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_CLOTHES_GV_BS_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ADMIN_WEAPON_GV_BS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AIR_LAUNCHES_OVER_40M")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_5STAR_WANTED_AVOIDANCE")), 50, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ACTIVATE_2_PERSON_KEY")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ALL_ROLES_HEIST")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_BUY_EVERY_GUN")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CAR_BOMBS_ENEMY_KILLS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CARS_EXPORTED")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CONTROL_CROWDS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DAILYOBJCOMPLETED")), 100, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DAILYOBJMONTHBONUS")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DAILYOBJWEEKBONUS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DO_HEIST_AS_MEMBER")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DO_HEIST_AS_THE_LEADER")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DRIVELESTERCAR5MINS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_DROPOFF_CAP_PACKAGES")), 100, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FINISH_HEIST_NO_DAMAGE")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FINISH_HEIST_SETUP_JOB")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FINISH_HEISTS")), 50, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTDM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTRACES")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFITEMSCLOTHES")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM6DARTCHKOUT")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_KILLSTREAK")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_STOLENKILL")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_TOTALKILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_WINS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_BIRDIES")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_HOLE_IN_1")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_WON")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GTA_RACES_WON")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACE_LAST_FIRST")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACES_FASTEST_LAP")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_CT_WON")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_GRAN_WON")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_RT_WON")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_TG_WON")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_MVP")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_WINS")), 50, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_5_SET_WINS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_ACE")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_STASETWIN")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_WON")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMATTGANGHQ")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBASEJMP")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBBETWIN")), 50000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMCRATEDROPS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMDRIVEWITHOUTCRASH")), 30, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMFULLYMODDEDCAR")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMHORDWAVESSURVIVE")), 10, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILL3ANDWINGTARACE")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLBOUNTY")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLSTREAKSDM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSGANGHIDE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSSURVIVE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMPICKUPDLCCRATE1ST")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRACEWORLDRECHOLDER")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONDRIVE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONNAV")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMREVENGEKILLSDM")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMSHOOTDOWNCOPHELI")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMTATTOOALLBODYPARTS")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINAIRRACE")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINALLRACEMODES")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINCUSTOMRACE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINEVERYGAMEMODE")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINRACETOPOINTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINSEARACE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_HOLD_UP_SHOPS")), 20, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_KILL_CARRIER_CAPTURE")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_KILL_PSYCHOPATHS")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_KILL_TEAM_YOURSELF_LTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LAPDANCES")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LESTERDELIVERVEHICLES")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_MENTALSTATE_TO_NORMAL")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_NIGHTVISION_KILLS")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_NO_HAIRCUTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ODISTRACTCOPSNOEATH")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_ONLY_PLAYER_ALIVE_LTS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_20M")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_50M")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PASSENGERTIME")), 4, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PICKUP_CAP_PACKAGES")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_RACES_WON")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SECURITY_CARS_ROBBED")), 25, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SPLIT_HEIST_TAKE_EVENLY")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_STORE_20_CAR_IN_GARAGES")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TAKEDOWNSMUGPLANE")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TIME_IN_HELICOPTER")), 4, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TRADE_IN_YOUR_PROPERTY")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_VEHICLES_JACKEDR")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_AT_DARTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_CAPTURE_DONT_DYING")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_CAPTURES")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_GOLD_MEDAL_HEISTS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_LAST_TEAM_STANDINGS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_BOTTLE_IN_POSSESSION")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CARS_EXPLODED")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_4_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_5_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_6_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_CARMOD_7_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_4_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_ADDON_5_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_UNLOCKED")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_WEAP_UNLOCKED2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_10_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_11_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_12_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_1_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_2_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_3_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_4_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_5_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_6_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_7_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_8_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_9_FM_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE11")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE12")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHASE9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WANTED_LEVEL_TIME5STAR")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WEAP_FM_PURCHASE")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WEAP_FM_PURCHASE2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_BERD_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_DECL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_FEET_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_JBIB_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_LEGS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_OUTFIT")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_PROPS_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL2_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_SPECIAL_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TEETH")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TEETH_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TEETH_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_ACQUIRED_TORSO")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_BERD_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_DECL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_FEET_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_HAIR_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_JBIB_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_LEGS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_OUTFIT")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_PROPS_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL2_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_SPECIAL_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TEETH")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TEETH_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TEETH_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLTHS_AVAILABLE_TORSO")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_0")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_10")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_11")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_12")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_13")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_14")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_15")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_16")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_17")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_18")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_19")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_20")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_21")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_22")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_23")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_24")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_25")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_26")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_27")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_28")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_29")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_30")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_31")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_32")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_33")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_34")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_35")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_36")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_37")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_38")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_39")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_40")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DLC_APPAREL_ACQUIRED_9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_GRENADE_ENEMY_KILLS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_KILLS_PLAYERS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LONGEST_WHEELIE_DIST")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_ARM_WRESTLING_WINS")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_FLIPS_IN_ONE_JUMP")), 5, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_SPINS_IN_ONE_JUMP")), 5, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_SLIPSTREAMS_IN_RACE")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_TURBO_STARTS_IN_RACE")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PASS_DB_PLAYER_KILLS")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PISTOL_ENEMY_KILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_HEADSHOTS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_RACES_WON")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SAWNOFF_ENEMY_KILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_DRIV")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_FLY")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_LUNG")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_MECH")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_SHO")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STAM")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STL")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STRN")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_STKYBMB_ENEMY_KILLS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_UNARMED_ENEMY_KILLS")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_USJS_COMPLETED")), 50, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_WEAP_FM_ADDON_PURCH5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CRDEADLINE")), 10, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_ABILITY_1_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_ABILITY_2_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_ABILITY_3_UNLCK")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BUY_COMPLETE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BUY_UNDERTAKEN")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_SELL_COMPLETE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_SELL_UNDERTAKEN")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_CONTRA_EARNINGS")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA1")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA2")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA3")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA4")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_COMPLET5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_BUY_UNDERTA5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_COMPLET5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BIKER_SELL_UNDERTA5")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS0")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS1")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS2")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS3")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS4")), 20000000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LIFETIME_BKR_SELL_EARNINGS5")), 20000000, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SR_TIER_1_REWARD")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SR_TIER_3_REWARD")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SR_INCREASE_THROW_CAP")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_COMPLET_HEIST_MEM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FLEECA_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HST_ORDER")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HST_SAME_TEAM")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HST_ULT_CHAL")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_HUMANE_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_PACIFIC_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_PRISON_FIN")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_SERIESA_FIN")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_HEIST_ACH_TRACKER")), -1, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_IAA")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_SUBMARINE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_ALLINORDER")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_LOYALTY")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_CRIMMASMD")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_MISSILE")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_LOYALTY2")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_LOYALTY3")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_CRIMMASMD2")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_CRIMMASMD3")), true, true);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_GANGOPS_SUPPORT")), true, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NO_BOUGHT_YUM_SNACKS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NO_BOUGHT_HEALTH_SNACKS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NO_BOUGHT_EPIC_SNACKS")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_OF_ORANGE_BOUGHT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_1_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_2_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_3_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_4_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MP_CHAR_ARMOUR_5_COUNT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_NUMBER_OF_BOURGE_BOUGHT")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_1_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_1_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_1_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_2_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_2_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_2_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_3_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_3_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_3_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_4_WHITE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_4_RED")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FIREWORK_TYPE_4_BLUE")), 1000, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_DM_MADE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_PLAYED_BY_PEEP")), 100, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_RACES_MADE")), 25, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PHN")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH2")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH3")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH4")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH5")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_VEH_TX1")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH6")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH7")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH8")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_ACT_PH9")), -1, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SNIPERRFL_ENEMY_KILLS")), 500, true);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_HVYSNIPER_ENEMY_KILLS")), 500, true);
				


				Cheat::GameFunctions::MinimapNotification("'Unlocked All' completed");
			}
			if (Cheat::GUI::Option("Max Skills", "Max out all skill levels")) 
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STAM")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STRN")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_LUNG")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_DRIV")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_FLY")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_SHO")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SCRIPT_INCREASE_STL")), 100, 0);
				Cheat::GameFunctions::MinimapNotification("Maxed out all skill values for your current character"); 	
			}
			if (Cheat::GUI::Option("Unlock Tattoo's", "Unlock most tattoo's")) 
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_WINS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_MVP")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_TOTALKILLS")), 500, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMATTGANGHQ")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBBETWIN")), 50000, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINEVERYGAMEMODE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRACEWORLDRECHOLDER")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMFULLYMODDEDCAR")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSSURVIVE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILL3ANDWINGTARACE")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLBOUNTY")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMREVENGEKILLSDM")), 50, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLSTREAKSDM")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_HOLD_UP_SHOPS")), 20, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LAPDANCES")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SECURITY_CARS_ROBBED")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CAR_BOMBS_ENEMY_KILLS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_HEADSHOTS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_DB_PLAYER_KILLS")), 1000, 1);
			}
			if (Cheat::GUI::Option("Unlock All Heist Vehicles", "Unlock Heist Vehicles")) 
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E2")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E3")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E4")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E5")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E6")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E7")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E8")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E9")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E10")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E11")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_FM_PURCHAS E12")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_1_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_2_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_3_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_4_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_5_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_6_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_7_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_8_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_9_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_10_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_11_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_KIT_12_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_races_won")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_number_turbo_starts_in_race")), 100, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_usjs_found")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_usjs_completed")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmwinairrace")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmwinsearace")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmrallywonnav")), 50, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fmrallywondrive ")), 500, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_awd_fm_races_fastest_lap")), 500, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_0_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_1_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_2_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_3_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_4_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_5_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_6_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_char_fm_carmod_7_unlck")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_VEHICLE_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_ABILITY_3_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_1_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_2_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_3_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_4_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_5_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_6_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_7_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_8_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_PACKAGE_9_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_HEALTH_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_FM_HEALTH_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_HOLDUPS_BITSET")), -1, 0);
			}
			if (Cheat::GUI::Option("Unlock Awards & Trophies", "")) 
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_HEADSHOTS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PISTOL_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SAWNOFF_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MICROSMG_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_SNIPERRFL_ENEMY_KILLS")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_UNARMED_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_STKYBMB_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_GRENADE_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_RPG_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CARS_EXPLODED")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_5STAR_WANTED_AVOIDANCE")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CAR_BOMBS_ENEMY_KILLS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_CARS_EXPORTED")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PASS_DB_PLAYER_KILLS")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_WINS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GTA_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_CT_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_RT_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_TG_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_WINS")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_WON")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_SPINS_IN_ONE_JUMP")), 5, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_DM_MADE")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMHORDWAVESSURVIVE")), 10, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_HOLD_UP_SHOPS")), 20, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_ASLTRIFLE_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MG_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_LAPDANCES")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_ARM_WRESTLING_WINS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_NO_HAIRCUTS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_SECURITY_CARS_ROBBED")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_VEHICLES_JACKEDR")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_MOST_FLIPS_IN_ONE_JUMP")), 5, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_WIN_AT_DARTS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PASSENGERTIME")), 4, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_TIME_IN_HELICOPTER")), 4, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_3KILLSAMEGUY")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_KILLSTREAK")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_STOLENKILL")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_DM_TOTALKILLS")), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_BIRDIES")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_GOLF_HOLE_IN_1")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACE_LAST_FIRST")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_RACES_FASTEST_LAP")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_SHOOTRANG_GRAN_WON")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TDM_MVP")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_ACE")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_STASETWIN")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM6DARTCHKOUT")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMATTGANGHQ")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_20M")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_PARACHUTE_JUMPS_50M")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AIR_LAUNCHES_OVER_40M")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_BUY_EVERY_GUN")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINEVERYGAMEMODE")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMDRIVEWITHOUTCRASH")), 255, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMCRATEDROPS")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTDM")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM_TENNIS_5_SET_WINS")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_PLAYED_BY_PEEP")), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "MPPLY_AWD_FM_CR_RACES_MADE")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFFERENTRACES")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FM25DIFITEMSCLOTHES")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMFULLYMODDEDCAR")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLBOUNTY")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_KILLS_PLAYERS")), 1000, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMPICKUPDLCCRATE1ST")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMSHOOTDOWNCOPHELI")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILL3ANDWINGTARACE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMKILLSTREAKSDM")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSGANGHIDE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMMOSTKILLSSURVIVE")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRACEWORLDRECHOLDER")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONDRIVE")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMRALLYWONNAV")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMREVENGEKILLSDM")), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINAIRRACE")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINCUSTOMRACE")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINRACETOPOINTS")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMWINSEARACE")), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMBASEJMP")), 25, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "__AWD_FMWINALLRACEMODES")), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_AWD_FMTATTOOALLBODYPARTS")), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CHAR_WANTED_LEVEL_TIME5STAR")), 2147483647, 1);
				STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_LONGEST_WHEELIE_DIST")), 1000, 1);		
				Cheat::GameFunctions::MinimapNotification("GTA Online Awards & Trophies unlocked");
			}
		}
		break;
		case miscstatsmenu:
		{
			Cheat::GUI::Title("Misc Stats");
			if (Cheat::GUI::Option("Set Max Nightclub Popularity", "Set NightClub Popularity to 100%"))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_CLUB_POPULARITY")), 9999, false);
				Cheat::GameFunctions::MinimapNotification("Maxed out Nightclub Popularity");
			}
			if (Cheat::GUI::Option("Redesign Character Prompt", "")) 
			{
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_FM_CHANGECHAR_ASKED")), false, true);
				Cheat::GameFunctions::MinimapNotification("Leave GTAO and rejoin to receive the notification");
			}
			if (Cheat::GUI::Option("Clear Badsport", "Clears Badsport status")) 
			{
				DWORD date[12];
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT "), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BAD_SPORT_BITSET"), 0, 1);
				STATS::STAT_SET_DATE(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_DT"), &date[0], 7, 1);
				Cheat::GameFunctions::MinimapNotification("Cleared Badsport Status");
			}
			if (Cheat::GUI::Option("Clear Mental State", "Clear current mental state"))
			{
				STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(Cheat::GameFunctions::ReturnCurrentGTAOCharacter() + "_PLAYER_MENTAL_STATE")), 0.0, true);
				Cheat::GameFunctions::MinimapNotification("Mental State Reset");
			}
		}
		break; 
		case rankmenu:
		{
			Cheat::GUI::Title("Rank");
			if (Cheat::GUI::Option("Custom Rank", "Input a custom Rank")) 
			{
				Cheat::GameFunctions::SetRankRockstarGift(Cheat::GameFunctions::DisplayKeyboardAndReturnInputInteger(4));
			}
			if (Cheat::GUI::Option("Rank 1",""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(1);
			}
			if (Cheat::GUI::Option("Rank 25", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(25);
			}
			if (Cheat::GUI::Option("Rank 50", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(50);
			}
			if (Cheat::GUI::Option("Rank 100", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(100);
			}
			if (Cheat::GUI::Option("Rank 120", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(120);
			}
			if (Cheat::GUI::Option("Rank 135", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(135);
			}
			if (Cheat::GUI::Option("Rank 200", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(200);
			}
			if (Cheat::GUI::Option("Rank 300", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(300);
			}
			if (Cheat::GUI::Option("Rank 500", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(500);
			}
			if (Cheat::GUI::Option("Rank 750", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(750);
			}
			if (Cheat::GUI::Option("Rank 1000", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(1000);
			}
			if (Cheat::GUI::Option("Rank 2000", ""))
			{
				Cheat::GameFunctions::SetRankRockstarGift(2000);
			}
			if (Cheat::GUI::Option("Rank 5000", ""))
			{	
				Cheat::GameFunctions::SetRankRockstarGift(5000);
			}
			if (Cheat::GUI::Option("Rank 8000", "Seems legit :-)"))
			{
				Cheat::GameFunctions::SetRankRockstarGift(8000);
			}
		}
		break; 	
		case ModelChangerMenu:
		{
			Cheat::GUI::Title("Model Changer");
			if (Cheat::GUI::Option("Custom Input", "Input custom Ped model"))
			{
				char* KeyboardInput = Cheat::GameFunctions::DisplayKeyboardAndReturnInput(30);
				if (KeyboardInput == "0") { break; }
				DWORD model = GAMEPLAY::GET_HASH_KEY(KeyboardInput);
				if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
				{
					Cheat::GameFunctions::MinimapNotification("~r~That is not a valid ped model");
				}
				else
				{
					GameFunctions::ChangePedModelLocalPlayer(model);
				}
			}
			Cheat::GUI::Break("Ped List", true);
			for (auto const& i : Cheat::GameArrays::PedModels)
			{
				if (Cheat::GUI::Option(i, ""))
				{
					GameFunctions::ChangePedModelLocalPlayer(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)));
				}
			}
		}
		break;
		case vehiclespawnermenu:
		{
			Cheat::GUI::Title("Vehicle Spawner");
			Cheat::GUI::MenuOption("Spawn Settings", VehicleSpawnSettings);
			if (Cheat::GUI::Option("Custom Input", "Input custom vehicle model"))
			{
				char* KeyboardInput = Cheat::GameFunctions::DisplayKeyboardAndReturnInput(30);
				if (KeyboardInput == "0") { break; }
				Cheat::GameFunctions::SpawnVehicle(KeyboardInput);
			}
			Cheat::GUI::Toggle("Show Vehicle Info & Preview", Cheat::CheatFeatures::ShowVehicleInfoAndPreview, "Shows selected vehicle info & picture");
			Cheat::GUI::Break("Categories", true);
			Cheat::GUI::MenuOption("DLC Vehicles", DLCVehiclesMenu);
			Cheat::GUI::MenuOption("Super", Super);
			Cheat::GUI::MenuOption("Sports", Sports);
			Cheat::GUI::MenuOption("Sport Classic", SportClassic);
			Cheat::GUI::MenuOption("Offroad", Offroad);
			Cheat::GUI::MenuOption("Sedans", Sedans);
			Cheat::GUI::MenuOption("Coupes", Coupes);
			Cheat::GUI::MenuOption("Muscle", Muscle);
			Cheat::GUI::MenuOption("Boats", Boats);
			Cheat::GUI::MenuOption("Commercial", Commercial);
			Cheat::GUI::MenuOption("Compacts", Compacts);
			Cheat::GUI::MenuOption("Cycles", Cycles);
			Cheat::GUI::MenuOption("Emergency", Emergency);
			Cheat::GUI::MenuOption("Helicopters", Helicopters);
			Cheat::GUI::MenuOption("Industrial", Industrial);
			Cheat::GUI::MenuOption("Military", Military);
			Cheat::GUI::MenuOption("Motorcycles", Motorcycles);
			Cheat::GUI::MenuOption("Planes", Planes);
			Cheat::GUI::MenuOption("Service", Service);
			Cheat::GUI::MenuOption("SUV", SUV);
			Cheat::GUI::MenuOption("Trailer", Trailer);
			Cheat::GUI::MenuOption("Trains", Trains);
			Cheat::GUI::MenuOption("Utility", Utility);
			Cheat::GUI::MenuOption("Vans", Vans);
		}
		break;
		case DLCVehiclesMenu:
		{
			Cheat::GUI::Title("DLC Vehicles");
			Cheat::GUI::MenuOption("The Cayo Perico Heist", CayoPericoHeistDLCMenu);
			Cheat::GUI::MenuOption("2020 Summer Special", SummerSpecialDLCMenu);
			Cheat::GUI::MenuOption("The Diamond Casino Heist", diamondcasinoheist);
			Cheat::GUI::MenuOption("The Diamond Casino & Resort", casinodlc);
			Cheat::GUI::MenuOption("Arena War", arenawardlc);
			Cheat::GUI::MenuOption("After Hours", afterhoursdlc);
			Cheat::GUI::MenuOption("SSASSS", SSASSSDLC);
			Cheat::GUI::MenuOption("The Doomsday Heist", doomsdayheistdlc);
			Cheat::GUI::MenuOption("Smuggler's Run", smugglersrun);
			Cheat::GUI::MenuOption("Gunrunning", gunrunningdlc);
			Cheat::GUI::MenuOption("Cunning Stunts", CunningStuntsDLCMenu);
		}
		break;
		case CayoPericoHeistDLCMenu:
		{
			Cheat::GUI::Title("The Cayo Perico Heist");
			for (auto const& i : Cheat::GameArrays::CayoPericoHeistModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SummerSpecialDLCMenu:
		{
			Cheat::GUI::Title("2020 Summer Special");
			for (auto const& i : Cheat::GameArrays::SummerSpecialModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case CunningStuntsDLCMenu:
		{
			Cheat::GUI::Title("Cunning Stunts");
			for (auto const& i : Cheat::GameArrays::CunningStuntsDLCModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case diamondcasinoheist:
		{
			Cheat::GUI::Title("The Diamond Casino Heist");
			for (auto const& i : Cheat::GameArrays::DiamondCasinoHeistDLCModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case casinodlc:
		{
			Cheat::GUI::Title("The Diamond Casino & Resort");
			for (auto const& i : Cheat::GameArrays::CasinoDLCModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case arenawardlc:
		{
			Cheat::GUI::Title("Arena War");
			for (auto const& i : Cheat::GameArrays::ArenaWarModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case smugglersrun:
		{
			Cheat::GUI::Title("Smuggler's Run");
			for (auto const& i : Cheat::GameArrays::SmugglersRunModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Super:
		{
			Cheat::GUI::Title("Super");
			for (auto const& i : Cheat::GameArrays::SuperModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Sports:
		{
			Cheat::GUI::Title("Sports");
			for (auto const& i : Cheat::GameArrays::SportModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SportClassic:
		{
			Cheat::GUI::Title("Sports Classic");
			for (auto const& i : Cheat::GameArrays::SportClassicModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}

		}
		break;
		case Offroad:
		{
			Cheat::GUI::Title("Offroad");
			for (auto const& i : Cheat::GameArrays::OffRoadModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}

		}
		break;
		case Sedans:
		{
			Cheat::GUI::Title("Sedans");
			for (auto const& i : Cheat::GameArrays::SedanModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}

		}
		break;
		case Coupes:
		{
			Cheat::GUI::Title("Coupes");
			for (auto const& i : Cheat::GameArrays::CoupesModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Muscle:
		{
			Cheat::GUI::Title("Muscle");
			for (auto const& i : Cheat::GameArrays::MuscleModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Boats:
		{
			Cheat::GUI::Title("Boats");
			for (auto const& i : Cheat::GameArrays::BoatModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Commercial:
		{
			Cheat::GUI::Title("Commercial");
			for (auto const& i : Cheat::GameArrays::CommercialModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Compacts:
		{
			Cheat::GUI::Title("Compacts");
			for (auto const& i : Cheat::GameArrays::CompactsModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Cycles:
		{
			Cheat::GUI::Title("Cycles");
			for (auto const& i : Cheat::GameArrays::CycleModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Emergency:
		{
			Cheat::GUI::Title("Emergency");
			for (auto const& i : Cheat::GameArrays::EmergencyModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Helicopters:
		{
			Cheat::GUI::Title("Helicopters");
			for (auto const& i : Cheat::GameArrays::HelicopterModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Industrial:
		{
			Cheat::GUI::Title("Industrial");
			for (auto const& i : Cheat::GameArrays::IndustrialModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Military:
		{
			Cheat::GUI::Title("Military");
			for (auto const& i : Cheat::GameArrays::MilitaryModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Motorcycles:
		{
			Cheat::GUI::Title("Motorcycles");
			for (auto const& i : Cheat::GameArrays::MotorcycleModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Planes:
		{
			Cheat::GUI::Title("Planes");
			for (auto const& i : Cheat::GameArrays::PlaneModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Service:
		{
			Cheat::GUI::Title("Service");
			for (auto const& i : Cheat::GameArrays::ServiceModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SUV:
		{
			Cheat::GUI::Title("SUV");
			for (auto const& i : Cheat::GameArrays::SUVModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Trailer:
		{
			Cheat::GUI::Title("Trailer");
			for (auto const& i : Cheat::GameArrays::TrailerModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Trains:
		{
			Cheat::GUI::Title("Trains");
			for (auto const& i : Cheat::GameArrays::TrainModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Utility:
		{
			Cheat::GUI::Title("Utility");
			for (auto const& i : Cheat::GameArrays::UtilityModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case Vans:
		{
			Cheat::GUI::Title("Vans");
			for (auto const& i : Cheat::GameArrays::VanModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case SSASSSDLC:
		{
			Cheat::GUI::Title("SSASSS");
			for (auto const& i : Cheat::GameArrays::SSASSSModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case doomsdayheistdlc:
		{
			Cheat::GUI::Title("The Doomsday Heist");
			for (auto const& i : Cheat::GameArrays::DoomsdayModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case gunrunningdlc:
		{
			Cheat::GUI::Title("Gunrunning");
			for (auto const& i : Cheat::GameArrays::GunrunningModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		case afterhoursdlc:
		{
			Cheat::GUI::Title("After Hours");
			for (auto const& i : Cheat::GameArrays::AfterHoursModels)
			{
				if (Cheat::GUI::VehicleOption(UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(GAMEPLAY::GET_HASH_KEY(CheatFunctions::StringToChar(i)))), i))
				{
					Cheat::GameFunctions::SpawnVehicle(CheatFunctions::StringToChar(i));
				}
			}
		}
		break;
		break; 
		case vehiclemenu:
		{
			Cheat::GUI::Title("Vehicle Options");
			Cheat::GUI::MenuOption("Spawner", vehiclespawnermenu);
			Cheat::GUI::MenuOption("Vehicle Customizer", VehicleCustomizerMenu);
			Cheat::GUI::MenuOption("Vehicle Weapons", vehicleweaponsmenu);
			if (Cheat::GUI::Option("Delete Current Vehicle", "Delete the current vehicle"))
			{
				if (!Cheat::GameFunctions::DeleteVehicle(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID))) 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}		
			}
			if (Cheat::GUI::Option("Flip Up", "Flip vehicle up")) { VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, false)); }
			if (Cheat::GUI::Option("Set Max Vehicle Speed", "")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, false)) 
				{
					int MaxSpeedInput = Cheat::GameFunctions::DisplayKeyboardAndReturnInputInteger(3);
					Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID);
					if (Cheat::CheatFeatures::UseKMH) 
					{
						ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, Cheat::GameFunctions::KMHToMS(MaxSpeedInput));
						Cheat::GameFunctions::MinimapNotification("Max Speed Set (KM/H)");
					}
					else
					{
						ENTITY::SET_ENTITY_MAX_SPEED(VehicleHandle, Cheat::GameFunctions::MPHToMS(MaxSpeedInput));
						Cheat::GameFunctions::MinimapNotification("Max Speed Set (MP/H)");
					}
				}
				else
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}		
			Cheat::GUI::Toggle("Vehicle Godmode", Cheat::CheatFeatures::VehicleGodmodeBool, "Makes current vehicle invincible");
			Cheat::GUI::Toggle("Vehicle Invisible", Cheat::CheatFeatures::VehicleInvisibleBool, "Makes current vehicle invisible");
			Cheat::GUI::Toggle("Vehicle Horn Boost", Cheat::CheatFeatures::VehicleHornBoostBool, "Press horn button to use");
			Cheat::GUI::Toggle("Unlimited Rocket Boost", Cheat::CheatFeatures::UnlimitedRocketBoostBool, "");
			Cheat::GUI::StringVector("Speedometer", { "Disabled", "On-Screen", "License Plate", "Both" }, Cheat::CheatFeatures::SpeedometerVectorPosition, "Set speedometer");
			Cheat::GUI::Toggle("Rainbow Vehicle", Cheat::CheatFeatures::RainbowVehicleBool, "Loops rainbow colors on current vehicle");
			Cheat::GUI::Toggle("Drive On Water", Cheat::CheatFeatures::DriveOnWaterBool, "Drive your vehicle on water");
			Cheat::GUI::Toggle("Super Brakes", Cheat::CheatFeatures::SuperBrakesBool, "");
		}
		break; 
		case VehicleCustomizerMenu:
		{
			Cheat::GUI::Title("Vehicle Customizer");
			if (Cheat::GUI::Option("Repair & Clean", "Repair & Clean current vehicle"))
			{
				Cheat::GameFunctions::RepairAndCleanVehicle();
			}
			if (Cheat::GUI::Option("Max Upgrade", "Max Upgrade current vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) {
					Cheat::GameFunctions::MaxUpgradeVehicle(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID));
					Cheat::GameFunctions::AdvancedMinimapNotification("Vehicle Max Upgraded", "Textures", "AdvancedNotificationImage", false, 4, "Vehicle Customizer", "", 1.0, "");
				}
				else 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (Cheat::GUI::Option("Max Downgrade", "Max downgrade current vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) {
					Cheat::GameFunctions::MaxDowngradeVehicle(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID));
					Cheat::GameFunctions::AdvancedMinimapNotification("Vehicle Max Downgraded", "Textures", "AdvancedNotificationImage", false, 4, "Vehicle Customizer", "", 1.0, "");
				}
				else 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (Cheat::GUI::Option("Add Blip Registration", "Add Blip To Current Vehicle")) {
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) {

					Cheat::GameFunctions::AddBlipToVehicle(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID));
				}
				else
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (Cheat::GUI::Option("Change License Plate Text", "Input custom vehicle license plate text"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) {			
					Vehicle VehicleHandle = PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID);
					char* KeyboardInput = Cheat::GameFunctions::DisplayKeyboardAndReturnInput(8);
					if (KeyboardInput == "0") { break; }
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(VehicleHandle, KeyboardInput);
					Cheat::GameFunctions::AdvancedMinimapNotification("License Plate Text Updated", "Textures", "AdvancedNotificationImage", false, 4, "Vehicle Customizer", "", 1.0, "");
				}
				else 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			Cheat::GUI::MenuOption("Color Options", VehicleCustomizerColorMenu);
			Cheat::GUI::MenuOption("Neon Options", vehicle_lsc_neon_options);
			Cheat::GUI::MenuOption("Multipliers", vehiclemultipliersmenus);
			Cheat::GUI::MenuOption("Door Options", vehicledooroptionsmenu);
		}
		break;
		case VehicleCustomizerColorMenu:
		{
			Cheat::GUI::Title("Custom Color");
			Cheat::GUI::Int("Primary Color: Red", VehiclePrimaryColorRed, 0, 255, 1);
			Cheat::GUI::Int("Primary Color: Green", VehiclePrimaryColorGreen, 0, 255, 1);
			Cheat::GUI::Int("Primary Color: Blue", VehiclePrimaryColorBlue, 0, 255, 1);
			if (Cheat::GUI::Option("Set Primary Color", "")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, VehiclePrimaryColorRed, VehiclePrimaryColorGreen, VehiclePrimaryColorBlue);
				}
				else
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			Cheat::GUI::Int("Secondary Color: Red", VehicleSecondaryColorRed, 0, 255, 1);
			Cheat::GUI::Int("Secondary Color: Green", VehicleSecondaryColorGreen, 0, 255, 1);
			Cheat::GUI::Int("Secondary Color: Blue", VehicleSecondaryColorBlue, 0, 255, 1);
			if (Cheat::GUI::Option("Set Secondary Color", "")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, VehicleSecondaryColorRed, VehicleSecondaryColorGreen, VehicleSecondaryColorBlue);
				}
				else
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
		}
		break;
		case vehicle_lsc_color_options:
		{
			Cheat::GUI::Title("Color Options");
			if (Cheat::GUI::Option("Random", "Get random color")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh))
				{
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255);
				}
			}
			Cheat::GUI::MenuOption("Custom Color", VehicleCustomizerColorMenu);
			Cheat::GUI::Break("~bold~Color Presets", true);
			if (Cheat::GUI::Option("Chrome", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 120, 120);
			}
			if (Cheat::GUI::Option("Black", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("White", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 255, 255);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Red", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Blue", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 255);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Orange", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 128, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Yellow", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Purple", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 204, 0, 204);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Grey", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 96, 96, 96);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Brown", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 165, 42, 42);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Pink", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 51, 255);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Cool Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 196);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Hot Pink", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 145);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Lime", "")) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 128, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Lava Red", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 60, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Mint Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 255, 119);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
			if (Cheat::GUI::Option("Neon Green", "")) 
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 187, 255, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, 0, 0);
			}
		}
		break;
		case vehicle_lsc_neon_options:
		{
			Cheat::GUI::Title("Neon Options");
			if (Cheat::GUI::Option("Enable Neons", "Enable Vehicle Neons")) 
			{
				for (int i = 0; i <= 7; i++)
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, false), i, true);
				}
			}
			if (Cheat::GUI::Option("Disable Neons", "Disable Vehicle Neons")) 
			{
				for (int i = 0; i <= 7; i++)
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, false), i, false);
				}
			}
			Cheat::GUI::Int("Neon Color: Red", VehicleNeonLightRed, 0, 255, 1);
			Cheat::GUI::Int("Neon Color: Green", VehicleNeonLightGreen, 0, 255, 1);
			Cheat::GUI::Int("Neon Color: Blue", VehicleNeonLightBlue, 0, 255, 1);
			if (Cheat::GUI::Option("Set Neon Color", "Set Vehicle Neon Colors")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, VehicleNeonLightRed, VehicleNeonLightGreen, VehicleNeonLightBlue);
				}
				else
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			Cheat::GUI::Break("Neon Presets", true);
			if (Cheat::GUI::Option("Red", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 255, 0, 0);
			}
			if (Cheat::GUI::Option("Green", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 255, 0);
			}
			if (Cheat::GUI::Option("Blue", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 0, 255);
			}
			if (Cheat::GUI::Option("Hot Pink", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 226, 35, 157);
			}
			if (Cheat::GUI::Option("Yellow", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 247, 244, 0);
			}
			if (Cheat::GUI::Option("Orange", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 247, 91, 0);
			}
			if (Cheat::GUI::Option("Aqua", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 40, 255, 255);
			}
			if (Cheat::GUI::Option("White", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 255, 255, 255);
			}
			if (Cheat::GUI::Option("Magenta", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 102, 0, 35);
			}
			if (Cheat::GUI::Option("Purple", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 53, 0, 83);
			}
			if (Cheat::GUI::Option("Dark Green", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 118, 0);
			}
			if (Cheat::GUI::Option("Rose Red", "")) 
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0);
				VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 161, 0, 0);
			}
		}
		break;
		case vehiclemultipliersmenus:
		{
			Cheat::GUI::Title("Multipliers");	
			Cheat::GUI::Int("Engine Multiplier", engine_multiplier, 0, 1000, 1, "Set Engine Multiplier value");
			Cheat::GUI::Int("Engine Torque Multiplier", torque_multiplier, 0, 1000, 1, "Set engine torque multiplier value");
			if (Cheat::GUI::Option("Set", "Set Multiplier")) 
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(Cheat::GameFunctions::PlayerPedID, 0)) 
				{
					Vehicle CurrentVehicle = PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID);
					VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(CurrentVehicle, engine_multiplier); // Engine Multiplier
					VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(CurrentVehicle, torque_multiplier); // Engine Torque Multiplier
				}
				else
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
		}
		break;
		case vehicledooroptionsmenu:
		{
			Cheat::GUI::Title("Door Options");
			if (Cheat::GUI::Option("Open All Doors", "Open All Vehicle Doors"))
			{
				for (int CurrentDoorIndex = 0; CurrentDoorIndex < 8; CurrentDoorIndex++)
				{
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID), CurrentDoorIndex, true, false);
				}
			}
			if (Cheat::GUI::Option("Close All Doors", "Close All Vehicle Doors")) { VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID), true); }
			if (Cheat::GUI::Option("Lock All Doors", "Lock All Vehicle Doors")) { VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID), 4); }
			if (Cheat::GUI::Option("Unlock All Doors", "Unlock All Vehicle Doors")) { VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(Cheat::GameFunctions::PlayerPedID), 0); }
		}
		break;
		case vehicleweaponsmenu:
		{
			Cheat::GUI::Title("Vehicle Weapons");
			Cheat::GUI::Toggle("Toggle Vehicle Weapons", Cheat::CheatFeatures::VehicleWeaponsBool, "Press horn button to use");
			Cheat::GUI::Toggle("Show Lines", Cheat::CheatFeatures::VehicleWeapons_DrawLaser, "Show lines in front of vehicle");
			if (Cheat::CheatFeatures::VehicleWeapons_TankRounds) 
			{
				Cheat::GUI::Break("Current: ~c~Tank Rounds", false);
			}
			if (Cheat::CheatFeatures::VehicleWeapons_VehicleRockets) 
			{
				Cheat::GUI::Break("Current: ~c~Vehicle Rockets", false);
			}
			if (Cheat::CheatFeatures::VehicleWeapons_Fireworks) 
			{
				Cheat::GUI::Break("Current: ~c~Fireworks", false);
			}
			if (Cheat::GUI::Option("Tank Rounds", "")) 
			{
				Cheat::CheatFeatures::VehicleWeapons_TankRounds = true;
				Cheat::CheatFeatures::VehicleWeapons_Fireworks = false;
				Cheat::CheatFeatures::VehicleWeapons_VehicleRockets = false;
			}
			if (Cheat::GUI::Option("Vehicle Rockets", "")) 
			{
				Cheat::CheatFeatures::VehicleWeapons_VehicleRockets = true;
				Cheat::CheatFeatures::VehicleWeapons_Fireworks = false;
				Cheat::CheatFeatures::VehicleWeapons_TankRounds = false;
			}
			if (Cheat::GUI::Option("Fireworks", "")) 
			{
				Cheat::CheatFeatures::VehicleWeapons_Fireworks = true;
				Cheat::CheatFeatures::VehicleWeapons_TankRounds = false;
				Cheat::CheatFeatures::VehicleWeapons_VehicleRockets = false;
			}
		}
		break;
		case VehicleSpawnSettings:
		{
			Cheat::GUI::Title("Vehicle Spawn Settings");
			Cheat::GUI::Toggle("Spawn Inside Vehicle", Cheat::CheatFeatures::VehicleSpawnerSpawnInsideVehicle, "");
			Cheat::GUI::Toggle("Spawn With Godmode", Cheat::CheatFeatures::VehicleSpawnerSpawnWithGodmode, "");
			Cheat::GUI::Toggle("Spawn Max Upgraded", Cheat::CheatFeatures::VehicleSpawnerSpawnMaxUpgraded, "");
			Cheat::GUI::Toggle("Delete Old Vehicle", Cheat::CheatFeatures::VehicleSpawnerDeleteOldVehicle, "");
			Cheat::GUI::Toggle("Spawn With Blip", Cheat::CheatFeatures::VehicleSpawnerSpawnWithBlip, "");
		}
		break; 
		case worldmenu:
		{
			Cheat::GUI::Title("World Options");
			Cheat::GUI::MenuOption("Time Options", timemenu);
			Cheat::GUI::MenuOption("Weather Options", weathermenu);
			Cheat::GUI::MenuOption("Nearby Vehicles", nearbyvehicles_menu);
			Cheat::GUI::MenuOption("Nearby Peds", nearbypeds_menu); 
			Cheat::GUI::Toggle("Snow (local)", Cheat::CheatFeatures::WorldSnowLocalBool, "GTA Online Only");
			if (Cheat::GUI::Option("Clear Area", "Clear area of vehicles, objects etc")) 
			{
				Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, false);
				GAMEPLAY::CLEAR_AREA(MyPos.x, MyPos.y, MyPos.z, 250, true, 0, 0, 0);
				GAMEPLAY::CLEAR_AREA_OF_COPS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_OBJECTS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_VEHICLES(MyPos.x, MyPos.y, MyPos.z, 250, 0, 0, 0, 0, 0);
				GAMEPLAY::CLEAR_AREA_OF_PEDS(MyPos.x, MyPos.y, MyPos.z, 250, 0);
				GAMEPLAY::CLEAR_AREA_OF_PROJECTILES(MyPos.x, MyPos.y, MyPos.z, 250, 0);

				//Seperate Remove Nearby Vehicles: for spawned vehicles
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Vehicle *vehs = new Vehicle[ArrSize];
				vehs[0] = ElementAmount;
				int VehFound = PED::GET_PED_NEARBY_VEHICLES(Cheat::GameFunctions::PlayerPedID, vehs);

				for (int i = 0; i < VehFound; i++)
				{
					int OffsetID = i * 2 + 2;
					if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, false))
					{
						Cheat::GameFunctions::RequestNetworkControlOfEntity(vehs[OffsetID]);
						ENTITY::SET_ENTITY_COORDS(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
					}
				}
				delete[] vehs;
				Cheat::GameFunctions::MinimapNotification("Area Cleared");
			}
			Cheat::GUI::Toggle("No Gravity", Cheat::CheatFeatures::NoGravityBool, "Disable gravity in the world");
			Cheat::GUI::Toggle("Blackout", Cheat::CheatFeatures::WorldBlackoutBool, "Disable All Map Lights");
		}
		break; 
		case nearbypeds_menu:
		{
			Cheat::GUI::Title("Nearby Peds");
			if (Cheat::GUI::Option("Explode Peds", "Explode nearby peds"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Ped *peds = new Ped[ArrSize];
				peds[0] = ElementAmount;

				int PedFound = PED::GET_PED_NEARBY_PEDS(Cheat::GameFunctions::PlayerPedID, peds, -1);

				for (int i = 0; i < PedFound; i++)
				{
					int OffsetID = i * 2 + 2;
					Cheat::GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
					if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && Cheat::GameFunctions::PlayerPedID != peds[OffsetID])
					{
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds[OffsetID], false);
						FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 0, 1000.f, true, false, 0.f);
					}
				}
			}
			if (Cheat::GUI::Option("Kill Peds", "Kill nearby peds"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Ped *peds = new Ped[ArrSize];
				peds[0] = ElementAmount;

				int PedFound = PED::GET_PED_NEARBY_PEDS(Cheat::GameFunctions::PlayerPedID, peds, -1);

				for (int i = 0; i < PedFound; i++)
				{
					int OffsetID = i * 2 + 2;
					Cheat::GameFunctions::RequestNetworkControlOfEntity(peds[OffsetID]);
					if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && Cheat::GameFunctions::PlayerPedID != peds[OffsetID])
					{
						PED::APPLY_DAMAGE_TO_PED(peds[OffsetID], 1000, false);
					}
				}
			}
			Cheat::GUI::Break("~bold~Scenarios", true);
			if (Cheat::GUI::Option("Paparizzi", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_PAPARAZZI");
			}
			if (Cheat::GUI::Option("Drug Dealer", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_DRUG_DEALER_HARD");
			}
			if (Cheat::GUI::Option("Drinking Coffee", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_AA_COFFEE");
			}
			if (Cheat::GUI::Option("Playing Instruments", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_MUSICIAN");
			}
			if (Cheat::GUI::Option("Flexing", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_MUSCLE_FLEX");
			}
			if (Cheat::GUI::Option("Jogging", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_JOG_STANDING");
			}
			if (Cheat::GUI::Option("Binoculars", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_BINOCULARS");
			}
			if (Cheat::GUI::Option("Clipboard", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_CLIPBOARD");
			}
			if (Cheat::GUI::Option("Bench Press", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS");
			}
			if (Cheat::GUI::Option("Chin Ups", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("PROP_HUMAN_MUSCLE_CHIN_UPS");
			}
			if (Cheat::GUI::Option("BBQ", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("PROP_HUMAN_BBQ");
			}
			if (Cheat::GUI::Option("Superhero", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_SUPERHERO");
			}
			if (Cheat::GUI::Option("Fishing", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_STAND_FISHING");
			}
			if (Cheat::GUI::Option("Security", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_SECURITY_SHINE_TORCH");
			}
			if (Cheat::GUI::Option("Leaf Blower", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_GARDENER_LEAF_BLOWER");
			}
			if (Cheat::GUI::Option("Film Shocking", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_MOBILE_FILM_SHOCKING");
			}
			if (Cheat::GUI::Option("Idle Cop", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_COP_IDLES");
			}
			if (Cheat::GUI::Option("Drinking", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_DRINKING");
			}
			if (Cheat::GUI::Option("Golf Player", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_GOLF_PLAYER");
			}
			if (Cheat::GUI::Option("Welding", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_WELDING");
			}
			if (Cheat::GUI::Option("Smoking Pot", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_SMOKING_POT");
			}
			if (Cheat::GUI::Option("Hammering", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_HAMMERING");
			}
			if (Cheat::GUI::Option("Tennis", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_TENNIS_PLAYER");
			}
			if (Cheat::GUI::Option("Drilling", "")) 
			{
				Cheat::GameFunctions::PlayScenarioNearbyPeds("WORLD_HUMAN_CONST_DRILL");

			}
			Cheat::GUI::Break("~bold~Animations", true);
			if (Cheat::GUI::Option("Sex Receiver", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("rcmpaparazzo_2", "shag_loop_poppy");
			}
			if (Cheat::GUI::Option("Sex Giver", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("rcmpaparazzo_2", "shag_loop_a");
			}
			if (Cheat::GUI::Option("Stripper Dance", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1");
			}
			if (Cheat::GUI::Option("Pole Dance", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
			}
			if (Cheat::GUI::Option("Push Ups", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("amb@world_human_push_ups@male@base", "base");
			}
			if (Cheat::GUI::Option("Sit Ups", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("amb@world_human_sit_ups@male@base", "base");
			}
			if (Cheat::GUI::Option("Celebrate", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("rcmfanatic1celebrate", "celebrate");
			}
			if (Cheat::GUI::Option("Electrocution", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("ragdoll@human", "electrocute");
			}
			if (Cheat::GUI::Option("Suicide", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("mp_suicide", "pistol");
			}
			if (Cheat::GUI::Option("Showering", "")) 
			{
				Cheat::GameFunctions::ClearNearbyPedAnimations();
				Cheat::GameFunctions::DoNearbyPedsAnimation("mp_safehouseshower@male@", "male_shower_idle_b");
			}
		}
		break; 
		case nearbyvehicles_menu:
		{
			Cheat::GUI::Title("Nearby Vehicles");
			if (Cheat::GUI::Option("Explode Vehicles", "Explode nearby vehicles"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Vehicle *vehs = new Vehicle[ArrSize];
				vehs[0] = ElementAmount;
				int VehFound = PED::GET_PED_NEARBY_VEHICLES(Cheat::GameFunctions::PlayerPedID, vehs);

				for (int i = 0; i < VehFound; i++)
				{
					int OffsetID = i * 2 + 2;
					if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, false))
					{
						Cheat::GameFunctions::RequestNetworkControlOfEntity(vehs[OffsetID]);
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehs[OffsetID], false);
						FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 0.f);
					}
				}
				delete[] vehs;
			}
			if (Cheat::GUI::Option("Delete Vehicles", "Delete nearby vehicles"))
			{
				const int ElementAmount = 10;
				const int ArrSize = ElementAmount * 2 + 2;

				Vehicle *vehs = new Vehicle[ArrSize];
				vehs[0] = ElementAmount;
				int VehFound = PED::GET_PED_NEARBY_VEHICLES(Cheat::GameFunctions::PlayerPedID, vehs);

				for (int i = 0; i < VehFound; i++)
				{
					int OffsetID = i * 2 + 2;
					if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, false))
					{
						Cheat::GameFunctions::RequestNetworkControlOfEntity(vehs[OffsetID]);
						ENTITY::SET_ENTITY_COORDS(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
					}
				}
				delete[] vehs;
			}
			if (Cheat::GUI::Option("Boost Vehicles", "Speed boost nearby vehicles"))
			{
				const int numElements = 10;
				const int arrSize = numElements * 2 + 2;
				Vehicle veh[arrSize];
				veh[0] = numElements;
				int count = PED::GET_PED_NEARBY_VEHICLES(Cheat::GameFunctions::PlayerPedID, veh);
				if (veh != NULL)
				{
					for (int i = 1; i <= count; i++)
					{
						int offsettedID = i;
						if (veh[offsettedID] != NULL && ENTITY::DOES_ENTITY_EXIST(veh[offsettedID]))
						{
							Cheat::GameFunctions::RequestNetworkControlOfEntity(veh[offsettedID]);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh[offsettedID], 10000.0f);
						}
					}
				}
			}
		}
		break;
		case timemenu:
		{
			Cheat::GUI::Title("Time Options");
			if (Cheat::GUI::Int("Hour", SetTimeHour, 0, 23, 1, false)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(SetTimeHour, TIME::GET_CLOCK_MINUTES(), TIME::GET_CLOCK_SECONDS()); }
			if (Cheat::GUI::Int("Minutes", SetTimeMinutes, 0, 59, 1, false)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TIME::GET_CLOCK_HOURS(), SetTimeMinutes, TIME::GET_CLOCK_SECONDS()); }
			if (Cheat::GUI::Int("Seconds", SetTimeSeconds, 0, 59, 1, false)) { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(TIME::GET_CLOCK_HOURS(), TIME::GET_CLOCK_MINUTES(), SetTimeSeconds); }
			Cheat::GUI::Break("Current Time", true);
			std::string CurrentGameTimeString = "Game Time: ~c~" + std::to_string(TIME::GET_CLOCK_HOURS()) + ":" + std::to_string(TIME::GET_CLOCK_MINUTES()) + ":" + std::to_string(TIME::GET_CLOCK_SECONDS());
			Cheat::GUI::Break(CurrentGameTimeString.c_str(), false);
			std::string CurrentSystemTimeString = "System Time: ~c~" + CheatFunctions::ReturnDateTimeFormatAsString("%H:%M:%S");
			Cheat::GUI::Break(CurrentSystemTimeString.c_str(), false);
			Cheat::GUI::Break("Misc", true);
			Cheat::GUI::Toggle("Slow Motion", Cheat::CheatFeatures::SlowMotionBool, "Slows Down Game Time");
			Cheat::GUI::Toggle("Pause Time", Cheat::CheatFeatures::PauseTimeBool, "Pause Game Time");
		}
		break;
		case weathermenu:
		{
			Cheat::GUI::Title("Weather Options");
			if (Cheat::GUI::Option("Extra Sunny", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("EXTRASUNNY"); }
			if (Cheat::GUI::Option("Sunny", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("CLEAR"); }
			if (Cheat::GUI::Option("Cloudy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("CLOUDS"); }
			if (Cheat::GUI::Option("Smoggy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("SMOG"); }
			if (Cheat::GUI::Option("Foggy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("FOGGY"); }
			if (Cheat::GUI::Option("Overcast", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("OVERCAST"); }
			if (Cheat::GUI::Option("Stormy", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("THUNDER"); }
			if (Cheat::GUI::Option("Snow", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("SNOW"); }
			if (Cheat::GUI::Option("Snowlight", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("SNOWLIGHT"); }
			if (Cheat::GUI::Option("Blizzard", "")) { GAMEPLAY::SET_OVERRIDE_WEATHER("BLIZZARD"); }
		}
		break;
		case miscmenu:
		{
			Cheat::GUI::Title("Misc Options");
			Cheat::GUI::MenuOption("HUD", hudmenu); 
			Cheat::GUI::MenuOption("IPL Loader", iplloader);
			Cheat::GUI::Toggle("Disable Phone", Cheat::CheatFeatures::DisablePhoneBool, "Disable phone controls");
			Cheat::GUI::Toggle("Get 6 Fake Wanted Level Stars", Cheat::CheatFeatures::FakeWantedLevelBool, "");
			Cheat::GUI::Toggle("No-Clip", Cheat::CheatFeatures::NoClipBool, "Use W and mouse to control");
			Cheat::GUI::Toggle("Jump Around Mode", Cheat::CheatFeatures::JumpAroundModeBool, "Nearby vehicles will 'jump around'");
			Cheat::GUI::Toggle("Free Cam", Cheat::CheatFeatures::FreeCamBool, "Use W and S to control. Shift to go faster");
			Cheat::GUI::Toggle("Show Joining Players Notification", Cheat::CheatFeatures::ShowJoiningPlayersNotification, "");
			Cheat::GUI::Toggle("No Orbital Cannon Cooldown", Cheat::CheatFeatures::OrbitalCannonCooldownBypassBool, "");
			Cheat::GUI::Toggle("Rockstar Developer Mode", Cheat::CheatFeatures::GTAODeveloperMode, "Toggles GTAO Spectator Options");
			Cheat::GUI::Toggle("Auto Teleport To Waypoint", Cheat::CheatFeatures::AutoTeleportToWaypointBool, "");
			Cheat::GUI::Toggle("Force Field", Cheat::CheatFeatures::PlayerForceFieldBool, "Gives your character a force field");
			Cheat::GUI::Toggle("Show Session Information", Cheat::CheatFeatures::ShowSessionInformationBool, "Show session info (next to radar)");
			Cheat::GUI::Toggle("Show FPS", Cheat::CheatFeatures::ShowFPSBool, "Show game FPS");
			Cheat::GUI::Toggle("Mobile Radio", Cheat::CheatFeatures::MobileRadioBool, "");
			if (Cheat::GUI::Option("Drive To Waypoint", "A NPC drives you to waypoint"))
			{
				int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
				if (UI::DOES_BLIP_EXIST(WaypointHandle))
				{
					Vector3 waypoint1 = UI::GET_BLIP_COORDS(UI::GET_FIRST_BLIP_INFO_ID(8));
					STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("marshall"));
					while (!STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("marshall"))) GameHooking::PauseMainFiber(0);
					Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Cheat::GameFunctions::PlayerPedID, 0.0, 5.0, 0);
					Vehicle veh = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("marshall"), pos.x, pos.y, pos.z, ENTITY::GET_ENTITY_HEADING(Cheat::GameFunctions::PlayerPedID), 1, 1);
					if (veh != 0)
					{
						Ped Driver = PED::CREATE_RANDOM_PED_AS_DRIVER(veh, false);
						PED::SET_PED_INTO_VEHICLE(Driver, veh, -1);
						PED::SET_PED_INTO_VEHICLE(Cheat::GameFunctions::PlayerPedID, veh, 0);
						AI::TASK_VEHICLE_DRIVE_TO_COORD(Driver, veh, waypoint1.x, waypoint1.y, waypoint1.z, 40, 1, ENTITY::GET_ENTITY_MODEL(veh), 7, 6, -1);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "CRUSADER");
						Cheat::GameFunctions::MinimapNotification("NPC Driver Spawned");
					}
				}
				else { Cheat::GameFunctions::MinimapNotification("Please set a waypoint first to use this feature"); }
			}		
		}
		break;
		case hudmenu:
		{
			Cheat::GUI::Title("HUD Options");
			Cheat::GUI::Toggle("Hide All HUD Elements", Cheat::CheatFeatures::HideHUDBool, "");
		}
		break; 
		case iplloader:
		{
			Cheat::GUI::Title("IPL Loader");
			Cheat::GUI::MenuOption("Go to IPL Teleports submenu", iplteleports);
			if (Cheat::GUI::Option("Load MP data", ""))
			{
				DLC2::ON_ENTER_MP();
			}
			if (Cheat::GUI::Option("Unload MP data", ""))
			{
				DLC2::ON_ENTER_SP();
			}
			if (Cheat::GUI::Option("Load North Yankton", ""))
			{
				STREAMING::REQUEST_IPL("plg_01");
				STREAMING::REQUEST_IPL("prologue01");
				STREAMING::REQUEST_IPL("prologue01_lod");
				STREAMING::REQUEST_IPL("prologue01c");
				STREAMING::REQUEST_IPL("prologue01c_lod");
				STREAMING::REQUEST_IPL("prologue01d");
				STREAMING::REQUEST_IPL("prologue01d_lod");
				STREAMING::REQUEST_IPL("prologue01e");
				STREAMING::REQUEST_IPL("prologue01e_lod");
				STREAMING::REQUEST_IPL("prologue01f");
				STREAMING::REQUEST_IPL("prologue01f_lod");
				STREAMING::REQUEST_IPL("prologue01g");
				STREAMING::REQUEST_IPL("prologue01h");
				STREAMING::REQUEST_IPL("prologue01h_lod");
				STREAMING::REQUEST_IPL("prologue01i");
				STREAMING::REQUEST_IPL("prologue01i_lod");
				STREAMING::REQUEST_IPL("prologue01j");
				STREAMING::REQUEST_IPL("prologue01j_lod");
				STREAMING::REQUEST_IPL("prologue01k");
				STREAMING::REQUEST_IPL("prologue01k_lod");
				STREAMING::REQUEST_IPL("prologue01z");
				STREAMING::REQUEST_IPL("prologue01z_lod");
				STREAMING::REQUEST_IPL("plg_02");
				STREAMING::REQUEST_IPL("prologue02");
				STREAMING::REQUEST_IPL("prologue02_lod");
				STREAMING::REQUEST_IPL("plg_03");
				STREAMING::REQUEST_IPL("prologue03");
				STREAMING::REQUEST_IPL("prologue03_lod");
				STREAMING::REQUEST_IPL("prologue03b");
				STREAMING::REQUEST_IPL("prologue03b_lod");
				STREAMING::REQUEST_IPL("prologue03_grv_dug");
				STREAMING::REQUEST_IPL("prologue03_grv_dug_lod");
				STREAMING::REQUEST_IPL("prologue_grv_torch");
				STREAMING::REQUEST_IPL("plg_04");
				STREAMING::REQUEST_IPL("prologue04");
				STREAMING::REQUEST_IPL("prologue04_lod");
				STREAMING::REQUEST_IPL("prologue04b");
				STREAMING::REQUEST_IPL("prologue04b_lod");
				STREAMING::REQUEST_IPL("prologue04_cover");
				STREAMING::REQUEST_IPL("des_protree_end");
				STREAMING::REQUEST_IPL("des_protree_start");
				STREAMING::REQUEST_IPL("des_protree_start_lod");
				STREAMING::REQUEST_IPL("plg_05");
				STREAMING::REQUEST_IPL("prologue05");
				STREAMING::REQUEST_IPL("prologue05_lod");
				STREAMING::REQUEST_IPL("prologue05b");
				STREAMING::REQUEST_IPL("prologue05b_lod");
				STREAMING::REQUEST_IPL("plg_06");
				STREAMING::REQUEST_IPL("prologue06");
				STREAMING::REQUEST_IPL("prologue06_lod");
				STREAMING::REQUEST_IPL("prologue06b");
				STREAMING::REQUEST_IPL("prologue06b_lod");
				STREAMING::REQUEST_IPL("prologue06_int");
				STREAMING::REQUEST_IPL("prologue06_int_lod");
				STREAMING::REQUEST_IPL("prologue06_pannel");
				STREAMING::REQUEST_IPL("prologue06_pannel_lod");
				STREAMING::REQUEST_IPL("prologue_m2_door");
				STREAMING::REQUEST_IPL("prologue_m2_door_lod");
				STREAMING::REQUEST_IPL("plg_occl_00");
				STREAMING::REQUEST_IPL("prologue_occl");
				STREAMING::REQUEST_IPL("plg_rd");
				STREAMING::REQUEST_IPL("prologuerd");
				STREAMING::REQUEST_IPL("prologuerdb");
				STREAMING::REQUEST_IPL("prologuerd_lod");			
				Cheat::GameFunctions::MinimapNotification("North Yankton IPL loaded");
			}
			if (Cheat::GUI::Option("Unload North Yankton", ""))
			{
				STREAMING::REMOVE_IPL("plg_01");
				STREAMING::REMOVE_IPL("prologue01");
				STREAMING::REMOVE_IPL("prologue01_lod");
				STREAMING::REMOVE_IPL("prologue01c");
				STREAMING::REMOVE_IPL("prologue01c_lod");
				STREAMING::REMOVE_IPL("prologue01d");
				STREAMING::REMOVE_IPL("prologue01d_lod");
				STREAMING::REMOVE_IPL("prologue01e");
				STREAMING::REMOVE_IPL("prologue01e_lod");
				STREAMING::REMOVE_IPL("prologue01f");
				STREAMING::REMOVE_IPL("prologue01f_lod");
				STREAMING::REMOVE_IPL("prologue01g");
				STREAMING::REMOVE_IPL("prologue01h");
				STREAMING::REMOVE_IPL("prologue01h_lod");
				STREAMING::REMOVE_IPL("prologue01i");
				STREAMING::REMOVE_IPL("prologue01i_lod");
				STREAMING::REMOVE_IPL("prologue01j");
				STREAMING::REMOVE_IPL("prologue01j_lod");
				STREAMING::REMOVE_IPL("prologue01k");
				STREAMING::REMOVE_IPL("prologue01k_lod");
				STREAMING::REMOVE_IPL("prologue01z");
				STREAMING::REMOVE_IPL("prologue01z_lod");
				STREAMING::REMOVE_IPL("plg_02");
				STREAMING::REMOVE_IPL("prologue02");
				STREAMING::REMOVE_IPL("prologue02_lod");
				STREAMING::REMOVE_IPL("plg_03");
				STREAMING::REMOVE_IPL("prologue03");
				STREAMING::REMOVE_IPL("prologue03_lod");
				STREAMING::REMOVE_IPL("prologue03b");
				STREAMING::REMOVE_IPL("prologue03b_lod");
				STREAMING::REMOVE_IPL("prologue03_grv_dug");
				STREAMING::REMOVE_IPL("prologue03_grv_dug_lod");
				STREAMING::REMOVE_IPL("prologue_grv_torch");
				STREAMING::REMOVE_IPL("plg_04");
				STREAMING::REMOVE_IPL("prologue04");
				STREAMING::REMOVE_IPL("prologue04_lod");
				STREAMING::REMOVE_IPL("prologue04b");
				STREAMING::REMOVE_IPL("prologue04b_lod");
				STREAMING::REMOVE_IPL("prologue04_cover");
				STREAMING::REMOVE_IPL("des_protree_end");
				STREAMING::REMOVE_IPL("des_protree_start");
				STREAMING::REMOVE_IPL("des_protree_start_lod");
				STREAMING::REMOVE_IPL("plg_05");
				STREAMING::REMOVE_IPL("prologue05");
				STREAMING::REMOVE_IPL("prologue05_lod");
				STREAMING::REMOVE_IPL("prologue05b");
				STREAMING::REMOVE_IPL("prologue05b_lod");
				STREAMING::REMOVE_IPL("plg_06");
				STREAMING::REMOVE_IPL("prologue06");
				STREAMING::REMOVE_IPL("prologue06_lod");
				STREAMING::REMOVE_IPL("prologue06b");
				STREAMING::REMOVE_IPL("prologue06b_lod");
				STREAMING::REMOVE_IPL("prologue06_int");
				STREAMING::REMOVE_IPL("prologue06_int_lod");
				STREAMING::REMOVE_IPL("prologue06_pannel");
				STREAMING::REMOVE_IPL("prologue06_pannel_lod");
				STREAMING::REMOVE_IPL("prologue_m2_door");
				STREAMING::REMOVE_IPL("prologue_m2_door_lod");
				STREAMING::REMOVE_IPL("plg_occl_00");
				STREAMING::REMOVE_IPL("prologue_occl");
				STREAMING::REMOVE_IPL("plg_rd");
				STREAMING::REMOVE_IPL("prologuerd");
				STREAMING::REMOVE_IPL("prologuerdb");
				STREAMING::REMOVE_IPL("prologuerd_lod");			
				Cheat::GameFunctions::MinimapNotification("North Yankton IPL unloaded");
			}
			if (Cheat::GUI::Option("Load Heist Yacht", ""))
			{
				STREAMING::REQUEST_IPL("hei_yacht_heist");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
				STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
				STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
				STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
				STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
				Cheat::GameFunctions::MinimapNotification("Heist Yacht IPL loaded");
			}
			if (Cheat::GUI::Option("Unload Heist Yacht", ""))
			{
				STREAMING::REMOVE_IPL("hei_yacht_heist");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Bar");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Bedrm");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Bridge");
				STREAMING::REMOVE_IPL("hei_yacht_heist_DistantLights");
				STREAMING::REMOVE_IPL("hei_yacht_heist_enginrm");
				STREAMING::REMOVE_IPL("hei_yacht_heist_LODLights");
				STREAMING::REMOVE_IPL("hei_yacht_heist_Lounge");			
				Cheat::GameFunctions::MinimapNotification("Heist Yacht IPL unloaded");
			}
			if (Cheat::GUI::Option("Load Destroyed hospital", ""))
			{
				STREAMING::REQUEST_IPL("RC12B_Destroyed");
				STREAMING::REQUEST_IPL("RC12B_HospitalInterior");			
				Cheat::GameFunctions::MinimapNotification("Destroyed Hospital IPL Loaded");
			}
			if (Cheat::GUI::Option("Unload Destroyed hospital", ""))
			{
				STREAMING::REMOVE_IPL("RC12B_Destroyed");
				STREAMING::REMOVE_IPL("RC12B_HospitalInterior");		
				Cheat::GameFunctions::MinimapNotification("Destroyed Hospital IPL unloaded");
			}
			if (Cheat::GUI::Option("Load Jewelry Store", ""))
			{
				STREAMING::REQUEST_IPL("post_hiest_unload");
				STREAMING::REMOVE_IPL("jewel2fake");
				STREAMING::REMOVE_IPL("bh1_16_refurb");			
				Cheat::GameFunctions::MinimapNotification("Jewelry Store IPL loaded");
			}
			if (Cheat::GUI::Option("Unload Jewelry Store", ""))
			{
				STREAMING::REMOVE_IPL("post_hiest_unload");		
				Cheat::GameFunctions::MinimapNotification("Jewelry Store IPL unloaded");
			}
			if (Cheat::GUI::Option("Load Morgue", ""))
			{
				STREAMING::REQUEST_IPL("Coroner_Int_on");			
				Cheat::GameFunctions::MinimapNotification("Morgue IPL loaded");
			}
			if (Cheat::GUI::Option("Unload Morgue", ""))
			{
				STREAMING::REMOVE_IPL("Coroner_Int_on");		
				Cheat::GameFunctions::MinimapNotification("Morgue IPL unloaded");
			}
			if (Cheat::GUI::Option("Load Cargoship", ""))
			{			
				STREAMING::REQUEST_IPL("cargoship");
				Cheat::GameFunctions::MinimapNotification("Cargoship IPL loaded");
			}
			if (Cheat::GUI::Option("Unload Cargoship", ""))
			{		
				STREAMING::REMOVE_IPL("cargoship");
				Cheat::GameFunctions::MinimapNotification("Cargoship IPL unloaded");
			}
		}
		break; 
		case weaponmenu: 
		{
			Cheat::GUI::Title("Weapon Options");
			if (Cheat::GUI::Option("Give All Weapons", ""))
			{
				Cheat::GameFunctions::GiveAllWeaponsToPlayer(Cheat::GameFunctions::PlayerPedID);
			}
			if (Cheat::GUI::Option("Remove All Weapons", ""))
			{
				if (Cheat::CheatFeatures::AutoGiveAllWeaponsBool) { Cheat::GameFunctions::MinimapNotification("Disable 'Auto Give All Weapons' to use this"); }
				else { WEAPON::REMOVE_ALL_PED_WEAPONS(Cheat::GameFunctions::PlayerPedID, true); }
			}
			if (Cheat::GUI::Option("Max Upgrade Weapons", "Max Upgrade All Weapons"))
			{
				//Mk2 Weapons
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_PISTOL_MK2_CLIP_INCENDIARY"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_PISTOL_MK2_CAMO_IND_01"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_SMG_MK2_CLIP_FMJ"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_PI_SUPP"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_MUZZLE_07"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_SB_BARREL_02"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_SMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_SMG_MK2_CAMO_IND_01"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CLIP_FMJ"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_AR_SUPP_02"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_MUZZLE_07"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_AR_BARREL_02"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_ASSAULTRIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_ASSAULTRIFLE_MK2_CAMO_IND_01"));
				
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CLIP_FMJ"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_AR_SUPP"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_MUZZLE_07"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_CR_BARREL_02"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_CARBINERIFLE_MK2_CAMO"));


				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CLIP_FMJ"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_SCOPE_MEDIUM_MK2"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_MUZZLE_07"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_MG_BARREL_02"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_COMBATMG_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_COMBATMG_MK2_CAMO_IND_01"));
				
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CLIP_EXPLOSIVE"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_SR_SUPP_03"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_MUZZLE_09"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_AT_SR_BARREL_02"));
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, GAMEPLAY::GET_HASH_KEY("WEAPON_HEAVYSNIPER_MK2"), GAMEPLAY::GET_HASH_KEY("COMPONENT_HEAVYSNIPER_MK2_CAMO_IND_01"));

				// Attachments FlashLight
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xAF113F99, 0x359B7AAE); //Advanced Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x0A3D4D34, 0x7BC4CDDC); //Combat PDW
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x13532244, 0x359B7AAE); //Micro SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x22D8FE39, 0x359B7AAE); //AP Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xD205520E, 0x359B7AAE); //Heavy Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7F229F94, 0x7BC4CDDC); //Bullpump Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x1B06D571, 0x359B7AAE); //Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x5EF9FEC4, 0x359B7AAE); //Combat Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x99AEEB3B, 0x359B7AAE); //.50 Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x2BE6766B, 0x7BC4CDDC); //SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xEFE7E2DF, 0x7BC4CDDC); //Assault SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xBFEFFF6D, 0x7BC4CDDC); //Assault Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 0x7BC4CDDC); //Carbine Rifle

				//Attachments Clips
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xAF113F99, 0x8EC1C979); //Extened Clip Advanced Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x05FC3C11, 0xBC54DA77); //Advanced scope Sniper Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x22D8FE39, 0x249A17D5); //Extended Clip AP Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x0C472FE2, 0xBC54DA77); //Advanced scope Heavy Sniper
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xD205520E, 0x64F9C62B); //Heavy Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xBFD21232, 0x7B0033B3); //SNS Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC0A3098D, 0x7C8BD10E); //Special Carbine
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xE284C527, 0x86BD7F72); //Assault Shotgun
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7F229F94, 0xB3688B0F); //Bullpump Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7FD62962, 0xD6C59CD6); //Combat MG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x1B06D571, 0xED265A1C); //Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x5EF9FEC4, 0xD67B4F2D); //Combat Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x99AEEB3B, 0xD9D3AC92); //.50 Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x083839C4, 0x33BA12E8); //Vintage Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x13532244, 0x10E6BA2B); //Micro SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x2BE6766B, 0x350966FB); //SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xEFE7E2DF, 0xBB46E417); //Assault SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x0A3D4D34, 0x334A5203); //Combat PDW
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x9D07F764, 0x82158B47); //MG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x61012683, 0xEAC8C270); //Gusenberg
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xBFEFFF6D, 0xB1214F9B); //Assault Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 0x91109691); //Carbine Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC734385A, 0xCCFD2AC5); //Marksman Rifle

				//Attachments Scopes
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xAF113F99, 0xAA2C45B4); //Extened Clip Advanced Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x05FC3C11, 0xD2443DDC); //Advanced scope Sniper Rifle, 
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x0C472FE2, 0xD2443DDC); //Advanced scope Heavy Sniper
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC0A3098D, 0xA0D89C42); //Special Carbine
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7F229F94, 0xAA2C45B4); //Bullpump Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x13532244, 0x9D2FBF29); //Micro SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x2BE6766B, 0x3CC6BA57); //SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xEFE7E2DF, 0x9D2FBF29); //Assault SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x0A3D4D34, 0xAA2C45B4); //Combat PDW
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x3C00AFED, 0x82158B47); //MG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xBFEFFF6D, 0x9D2FBF29); //Assault Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 0xA0D89C42); //Carbine Rifle

				//Attachments Supressors
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xAF113F99, 0x8EC1C979); //Advanced Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x05FC3C11, 0xA73D4664); //Sniper Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x22D8FE39, 0xC304849A); //AP Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xD205520E, 0xC304849A); //Heavy Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC0A3098D, 0xA73D4664); //Special Carbine
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7F229F94, 0x837445AA); //Bullpump Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x1B06D571, 0x65EA7EBB); //Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x5EF9FEC4, 0xC304849A); //Combat Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x083839C4, 0xC304849A); //Vintage Pistol
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x2BE6766B, 0xC304849A); //SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xEFE7E2DF, 0xA73D4664); //Assault SMG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xBFEFFF6D, 0xA73D4664); //Assault Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 0x837445AA); //Carbine Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC734385A, 0x837445AA); //Marksman Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x1D073A89, 0xE608B35E); //Pump Shotgun

				//Attachments Grip
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC0A3098D, 0xC164F53); //Special Carbine
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7F229F94, 0xC164F53); //Bullpump Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x9D61E50F, 0xC164F53); //Bullpump ShotGun
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xBFEFFF6D, 0xC164F53); //Assault Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 0xC164F53); //Carbine Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xC734385A, 0xC164F53); //Marksman Rifle
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x0A3D4D34, 0xC164F53); //Combat PDW
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x7FD62962, 0xC164F53); //Combat MG
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0xE284C527, 0xC164F53); //Assault Shotgun

				//Special Finish
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 0xD89B9658); //Carbine Rifle

				//Paints
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x1B06D571, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x5EF9FEC4, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x22D8FE39, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x99AEEB3B, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x13532244, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x2BE6766B, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xEFE7E2DF, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xBFEFFF6D, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x83BF0278, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xAF113F99, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x9D07F764, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x7FD62962, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x1D073A89, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x7846A318, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xE284C527, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x9D61E50F, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x05FC3C11, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x0C472FE2, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xA284510B, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xB1CA77B1, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x42BF8A85, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x687652CE, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x61012683, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xC0A3098D, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xD205520E, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xBFD21232, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x7F229F94, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x083839C4, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x7F7497E5, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xA89CB99E, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x63AB0442, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xC734385A, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x0A3D4D34, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0xF9D04ADB, 2);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Cheat::GameFunctions::PlayerPedID, 0x0A3D4D34, 2);
			}
			Cheat::GUI::MenuOption("Custom Bullets", custombulletsmenu);
			Cheat::GUI::MenuOption("Vehicle Gun", vehiclegunmenu);
			Cheat::GUI::MenuOption("Triggerbot", aimbotsettingsmenu);		
			Cheat::GUI::Toggle("No reload", Cheat::CheatFeatures::NoWeaponReloadBool, "Always have max amount of ammo");
			Cheat::GUI::Toggle("Auto Give All Weapons", Cheat::CheatFeatures::AutoGiveAllWeaponsBool, "Always have all weapons");
			Cheat::GUI::Toggle("Teleport Gun", Cheat::CheatFeatures::TeleportGunBool, "Teleport to where you shoot");
			Cheat::GUI::Toggle("Entity Information Gun", Cheat::CheatFeatures::EntityInformationGunBool, "Shows info about aimed entity");
			Cheat::GUI::Toggle("Cartoon Gun", Cheat::CheatFeatures::CartoonGunBool, "Shows cartoon effects while shooting");
			Cheat::GUI::Toggle("Delete Gun", Cheat::CheatFeatures::DeleteGunBool, "Use SNS Pistol with this option");
			Cheat::GUI::Toggle("Rapid Fire", Cheat::CheatFeatures::WeaponRapidFireBool, "Shoot very fast");
			Cheat::GUI::Toggle("Money Gun", Cheat::CheatFeatures::MoneyGunBool, "Drops money bags where you shoot");
			Cheat::GUI::Toggle("Weapon Damage Multiplier", Cheat::CheatFeatures::OneHitKillBool, "Better known as 'one-hit kill'");
			Cheat::GUI::Toggle("Gravity Gun", Cheat::CheatFeatures::GravityGunBool, "Use Combat Pistol for this option");
			Cheat::GUI::Toggle("Airstrike Gun", Cheat::CheatFeatures::AirstrikeGunBool, "");
			Cheat::GUI::Toggle("Rainbow Gun", Cheat::CheatFeatures::RainbowGunBool, "Loops colors on your equipped weapon");
		}
		break; 
		case vehiclegunmenu:
		{
			Cheat::GUI::Title("Vehicle Gun");
			Cheat::GUI::Toggle("Toggle Vehicle Gun", Cheat::CheatFeatures::VehicleGunBool, "Toggle Vehicle Gun");
			Cheat::GUI::Break("Current: ~t~" + Cheat::CheatFeatures::VehicleGun_VehicleNameString, false);
			Cheat::GUI::Break("Vehicles", true);
			if (Cheat::GUI::Option("Custom Input", "Custom Vehicle Gun Input"))
			{
				char* SpawnVehicle = Cheat::GameFunctions::DisplayKeyboardAndReturnInput(30);
				if (SpawnVehicle == "0") { break; }

				Hash model = GAMEPLAY::GET_HASH_KEY(SpawnVehicle);
				if (!STREAMING::IS_MODEL_IN_CDIMAGE(model) || !STREAMING::IS_MODEL_A_VEHICLE(model)) 
				{ 
					Cheat::GameFunctions::MinimapNotification("~r~Not a valid vehicle model"); 
				}
				else
				{
					Cheat::CheatFeatures::VehicleGun_VehicleNameString = SpawnVehicle;
					Cheat::GameFunctions::MinimapNotification("Custom Vehicle Set");
				}
			}
			if (Cheat::GUI::Option("Rhino Tank", "")) { Cheat::CheatFeatures::VehicleGun_VehicleNameString = "RHINO"; }
			if (Cheat::GUI::Option("Hydra", "")) { Cheat::CheatFeatures::VehicleGun_VehicleNameString = "HYDRA"; }
			if (Cheat::GUI::Option("Airport Bus", "")) { Cheat::CheatFeatures::VehicleGun_VehicleNameString = "AIRBUS"; }
			if (Cheat::GUI::Option("Brickade", "")) { Cheat::CheatFeatures::VehicleGun_VehicleNameString = "BRICKADE"; }
			if (Cheat::GUI::Option("Cargo Plane", "")) { Cheat::CheatFeatures::VehicleGun_VehicleNameString = "CARGOPLANE"; }
			if (Cheat::GUI::Option("Dump", "")) { Cheat::CheatFeatures::VehicleGun_VehicleNameString = "DUMP"; }
		}
		break;
		case custombulletsmenu: 
		{
			Cheat::GUI::Title("Custom Bullets");
			Cheat::GUI::Toggle("Toggle Custom Bullets", Cheat::CheatFeatures::CustomWeaponBulletsBool, "");
			Cheat::GUI::Toggle("Valkyrie Bullets", Cheat::CheatFeatures::CustomWeaponBullets_ValkyrieGun, "");
			Cheat::GUI::Toggle("Tank Bullets", Cheat::CheatFeatures::CustomWeaponBullets_TankBullets, "");
			Cheat::GUI::Toggle("RPG Bullets", Cheat::CheatFeatures::CustomWeaponBullets_RpgBullets, "");
			Cheat::GUI::Toggle("Firework Bullets", Cheat::CheatFeatures::CustomWeaponBullets_FireworkBullets, "");
		}
		break; 
		case aimbotsettingsmenu:
		{
			Cheat::GUI::Title("Triggerbot");
			Cheat::GUI::Toggle("Toggle Triggerbot", Cheat::CheatFeatures::TriggerBotBool, "Toggle Triggerbot");
			Cheat::GUI::Toggle("Shoot NPC's", Cheat::CheatFeatures::TriggerBot_ShootNPCBool, "Triggerbot shoots at NPC's");
			Cheat::GUI::Toggle("Shoot Players", Cheat::CheatFeatures::TriggerBot_ShootPlayersBool, "Triggerbot shoots at players");
		}
		break;
		case teleportmenu:
		{
			Cheat::GUI::Title("Teleport Options");
			if (Cheat::GUI::Option("Teleport To Waypoint", "")) { Cheat::GameFunctions::TeleportToBlipCoord(SpriteWaypoint); }
			if (Cheat::GUI::Option("Teleport To Personal Vehicle", "")) { Cheat::GameFunctions::TeleportToBlipCoord(SpritePersonalVehicleCar);  }
			if (Cheat::GUI::Option("Teleport To Objective", "")) { Cheat::GameFunctions::TeleportToObjective(); }
			if (Cheat::GUI::Option("Teleport Into Last Used Vehicle", "")) 
			{
				PED::SET_PED_INTO_VEHICLE(Cheat::GameFunctions::PlayerPedID, VEHICLE::GET_LAST_DRIVEN_VEHICLE(), -1);
			}
			if (Cheat::GUI::Float("Teleport Forward", TeleportFoward, 1.f, 10.f, 1.f, false, false, "Select to teleport"))
			{
				Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Cheat::GameFunctions::PlayerPedID, 0.0, TeleportFoward, 0.0);
				int Handle = Cheat::GameFunctions::PlayerPedID;
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) { Handle = PED::GET_VEHICLE_PED_IS_IN(Cheat::GameFunctions::PlayerPedID, 0); }
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 1);
			}
			Cheat::GUI::MenuOption("IPL Teleports", iplteleports);
			Cheat::GUI::MenuOption("Common Locations", CommonTeleportLocations);
		}
		break;
		case CommonTeleportLocations:
		{
			Cheat::GUI::Title("Common Teleport Locations");	
			if (Cheat::GUI::Option("High In The Sky", ""))
			{
				Vector3 Coords;
				Coords.x = 240.93f; Coords.y = -765.19f; Coords.z = 2558.83f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Diamond Casino & Resort", ""))
			{
				Vector3 Coords;
				Coords.x = 916.37f; Coords.y = 51.22f; Coords.z = 80.89f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Mount Chiliad", "")) 
			{
				Vector3 Coords;
				Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}		
			if (Cheat::GUI::Option("Maze Bank", "")) 
			{
				Vector3 Coords;
				Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (Cheat::GUI::Option("Military Base", "")) 
			{
				Vector3 Coords;
				Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Zancudo Tower", "")) 
			{
				Vector3 Coords;
				Coords.x = -2356.0940f; Coords.y = 3248.645f; Coords.z = 101.4505f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Mask Shop", "")) 
			{
				Vector3 Coords;
				Coords.x = -1338.16f; Coords.y = -1278.11f; Coords.z = 4.87f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (Cheat::GUI::Option("LSC", "")) {
				Vector3 Coords;
				Coords.x = -373.01f; Coords.y = -124.91f; Coords.z = 38.31f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Ammunation", "")) 
			{
				Vector3 Coords;
				Coords.x = 247.3652f; Coords.y = -45.8777f; Coords.z = 69.9411f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (Cheat::GUI::Option("Airport", "")) 
			{
				Vector3 Coords;
				Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Clothes Store", "")) 
			{
				Vector3 Coords;
				Coords.x = -718.91f; Coords.y = -158.16f; Coords.z = 37.00f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Waterfall", "")) 
			{
				Vector3 Coords;
				Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("FIB", "")) 
			{
				Vector3 Coords;
				Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
			if (Cheat::GUI::Option("Human Labs", "")) 
			{
				Vector3 Coords;
				Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}	
			if (Cheat::GUI::Option("MMI", "")) 
			{
				Vector3 Coords;
				Coords.x = -222.1977f; Coords.y = -1185.8500f; Coords.z = 23.0294f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}		
			if (Cheat::GUI::Option("Sandy Shores Airfield", "")) 
			{
				Vector3 Coords;
				Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f;
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, Coords, false, false);
			}
		}
		break;
		case iplteleports:
		{
			Cheat::GUI::Title("IPL Teleports");
			Cheat::GUI::MenuOption("Go to IPL Loader submenu", iplloader);
			if (Cheat::GUI::Option("North Yankton", ""))
			{
				ENTITY::SET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, 5309.519f, -5212.37f, 83.522f, true, false, false, true);
			}
			if (Cheat::GUI::Option("Yacht", ""))
			{
				ENTITY::SET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, -2045.8f, -1031.2f, 11.9f, true, false, false, true);
			}
			if (Cheat::GUI::Option("Destroyed Hospital", ""))
			{
				ENTITY::SET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, 356.8f, -590.1f, 43.3f, true, false, false, true);
			}
			if (Cheat::GUI::Option("Jewelry Store", ""))
			{
				ENTITY::SET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, -630.4f, -236.7f, 40.0f, true, false, false, true);
			}
			if (Cheat::GUI::Option("Morgue", ""))
			{
				ENTITY::SET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, 244.9f, -1374.7f, 39.5f, true, false, false, true);
			}
			if (Cheat::GUI::Option("Cargo Ship", ""))
			{
				ENTITY::SET_ENTITY_COORDS(Cheat::GameFunctions::PlayerPedID, -90.0f, -2365.8f, 14.3f, true, false, false, true);
			}
		}
		break; 
		case ESPMenu:
		{
			Cheat::GUI::Title("ESP Options");
			Cheat::GUI::Toggle("Basic ESP", Cheat::CheatFeatures::PlayerESPBool, "Toggle Player ESP");
		}
		break; 
		case SelectedPlayerTrollMenu:
		{
			Cheat::GUI::Title("Troll Options");
			Cheat::GUI::MenuOption("Attachment Options", SelectedPlayerAttachmentOptions);
			Cheat::GUI::Toggle("Explode Loop", Cheat::CheatFeatures::ExplodeLoopSelectedPlayerBool, "Run explode loop on selected player", false);
			Cheat::GUI::Toggle("Freeze Player", Cheat::CheatFeatures::FreezeSelectedPlayerBool, "Freeze character of selected player", false);
			Cheat::GUI::Toggle("Shake Cam", Cheat::CheatFeatures::ShakeCamSelectedPlayerBool, "Shake selected player character camera", false);
			if (Cheat::GUI::Option("Set Off Car Alarm", "Enable Car Alarm of Selected Player"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					Cheat::GameFunctions::SetOffAlarmPlayerVehicle(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer));
				}
				else 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}
			}
			if (Cheat::GUI::Option("Burst Vehicle Tires", "Burst selected player vehicle tires"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					Cheat::GameFunctions::BurstSelectedPlayerTires(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer));
				}
				else 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle");
				}			
			}
			if (Cheat::GUI::Option("Airstrike Player", "Airstrike selected player"))
			{
				Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), 1);
				Coords.z += 15;
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, 1, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), 1, 1, 500);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 30, Coords.x, Coords.y, Coords.z, 250, 0, GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_SPACE_ROCKET"), 0, 1, 1, 500);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 55, Coords.x, Coords.y, Coords.z, 100, false, 0xF8A3939F, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), true, true, 600);
			}
			if (Cheat::GUI::Option("Attach to player", "Attach to selected player"))
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer) != Cheat::GameFunctions::PlayerPedID)
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(Cheat::GameFunctions::PlayerPedID, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
				}
			}
			if (Cheat::GUI::Option("Detach from player", "Detach from selected player"))
			{
				ENTITY::DETACH_ENTITY(Cheat::GameFunctions::PlayerPedID, true, true);
			}
			if (Cheat::GUI::Option("Slingshot Vehicle", "Slingshot selected player vehicle"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer);
				if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) 
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), true));
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), true)))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
					}
				}
				else 
				{
					Cheat::GameFunctions::MinimapNotification("~r~Player is not in a vehicle"); 
				}
			}
			if (Cheat::GUI::Option("Ram With Vehicle", "Ram selected player with vehicle"))
			{
				Hash model = GAMEPLAY::GET_HASH_KEY("trophytruck2");
				if (STREAMING::IS_MODEL_VALID(model))
				{
					for (int i = 0; i < 3; i++)
					{
						STREAMING::REQUEST_MODEL(model);
						while (!STREAMING::HAS_MODEL_LOADED(model)) GameHooking::PauseMainFiber(0);
						Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), false);
						float forward = 10.f;
						float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer));
						float xVector = forward * sin(Cheat::GameFunctions::DegreesToRadians(heading)) * -1.f;
						float yVector = forward * cos(Cheat::GameFunctions::DegreesToRadians(heading));
						Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x - xVector, ourCoords.y - yVector, ourCoords.z, heading, true, true);
						Cheat::GameFunctions::RequestNetworkControlOfEntity(veh);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 250);
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					}
				}
			}
			if (Cheat::GUI::Option("Trap Player", "Trap selected player"))
			{
				Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), 0);
				Object obj = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
			}
			if (Cheat::GUI::Option("Clone Player", "Clone selected player"))
			{
				Cheat::GameFunctions::ClonePed(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer));
			}
			if (Cheat::GUI::Option("Kick out of vehicle", "Kick selected player out of vehicle"))
			{
				Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer);
				Cheat::GameFunctions::RequestNetworkControlOfEntity(playerPed);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				AI::CLEAR_PED_TASKS(playerPed);
				AI::CLEAR_PED_SECONDARY_TASK(playerPed);
			}
			if (Cheat::GUI::Option("Spawn Enemy", "Spawn enemy to attack selected player"))
			{
				int eclone[1000];
				int egcount = 1;
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm)) { GameHooking::PauseMainFiber(0); }
				eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			if (Cheat::GUI::Option("Spawn Bodyguard", "Spawn Bodyguard for selected player")) 
			{
				int clone[1000];
				int gcount = 1;
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_m_jesus_01");
				STREAMING::REQUEST_MODEL(pedm);
				while (!STREAMING::HAS_MODEL_LOADED(pedm)) { GameHooking::PauseMainFiber(0); }
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}		
		}
		break;
		case PlayerListMenu:
		{
			Cheat::GUI::Title("Player List");
			for (int i = 0; i < 32; ++i)
			{
				std::string PlayernameString = PLAYER::GET_PLAYER_NAME(i);
				if (Cheat::GameFunctions::IsPlayerIDValid(i))
				{
					if (Cheat::CheatFeatures::ShowPlayerTagsPlayerList)
					{
						if (Cheat::GameFunctions::PlayerIsFreemodeScriptHost(i)) { PlayernameString.append(" ~o~[Host]"); }
						if (Cheat::GameFunctions::IsPlayerFriend(i)) { PlayernameString.append(" ~b~[Friend]"); }
						if (Cheat::GameFunctions::IsEntityInInterior(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) { PlayernameString.append(" ~p~[Interior]"); }
						if (Cheat::GameFunctions::PlayerID == i) { PlayernameString.append(" ~g~[You]"); }
					}
					Cheat::GUI::MenuOptionPlayerList(PlayernameString, SelectedPlayerMenu) ? Cheat::CheatFeatures::selectedPlayer = i : NULL;
					if (Cheat::GUI::currentOption == Cheat::GUI::optionCount) { Cheat::GameFunctions::ShowPlayerInformationBox(i); }
				}
			}
		}
		break;
		case SelectedPlayerMenu:
		{
			Cheat::GUI::Title(PLAYER::GET_PLAYER_NAME(Cheat::CheatFeatures::selectedPlayer));
			Cheat::GUI::Toggle("Spectate Player", Cheat::CheatFeatures::SpectatePlayerBool, "Spectate Selected Player", false);
			if (Cheat::GUI::Option("Host Kick", "Kick selected player - Host only")) { NETWORK::NETWORK_SESSION_KICK_PLAYER(Cheat::CheatFeatures::selectedPlayer); }
			if (Cheat::GUI::Option("Teleport To", "Teleport to selected player coords"))
			{
				Cheat::GameFunctions::TeleportToCoords(Cheat::GameFunctions::PlayerPedID, ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), false), 
					                                   false, false);
			}
			Cheat::GUI::MenuOption("Teleport Options", SelectedPlayerTeleportMenu);
			Cheat::GUI::MenuOption("Friendly Options", SelectedPlayerFriendlyMenu);
			Cheat::GUI::MenuOption("Troll Options", SelectedPlayerTrollMenu);
			Cheat::GUI::MenuOption("Remote Options", SelectedPlayerRemoteOptions, true);
			if (Cheat::GUI::Option("Copy Outfit", "Get Selected Player Outfit")) { Cheat::GameFunctions::CopySelectedPlayerOutfit(Cheat::CheatFeatures::selectedPlayer); }
			if (Cheat::GUI::Option("View Profile", "View Selected Player Social Club Profile")) { int playerHandle; NETWORK::NETWORK_HANDLE_FROM_PLAYER(Cheat::CheatFeatures::selectedPlayer, &playerHandle, 13); NETWORK::NETWORK_SHOW_PROFILE_UI(&playerHandle); }
		}
		break;
		case SelectedPlayerFriendlyMenu:
		{
			Cheat::GUI::Title("Friendly Options");
			Cheat::GUI::MenuOption("Money Options", SelectedPlayerMoneyMenu);
			if (Cheat::GUI::Option("Give All Weapons", "Give all weapons to selected player")) { Cheat::GameFunctions::GiveAllWeaponsToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer)); }
		}
		break;
		case SelectedPlayerRemoteOptions:
		{
			Cheat::GUI::Title("Remote Options");
			if (Cheat::GUI::Option("Kick To Single Player", "Kick Selected Player to SP")) 
			{
				if (NETWORK::NETWORK_IS_SESSION_STARTED())
				{
					//uint64_t kick_sp[4] = { 1667907776, Cheat::CheatFeatures::selectedPlayer, 0, 0 };
					//SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick_sp, 4, 1 << Cheat::CheatFeatures::selectedPlayer);
				}
			}
		}
		break; 
		case SelectedPlayerTeleportMenu:
		{
			Cheat::GUI::Title("Teleport Options"); 
			if (Cheat::GUI::Option("Teleport Into Vehicle", "Teleport into Selected Player vehicle"))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), false);
				for (int i = -1; i < 16; i++) { if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i)) { PED::SET_PED_INTO_VEHICLE(Cheat::GameFunctions::PlayerPedID, veh, i); } }
			}
		}
		break; 
		case SelfOptionsMenu:
		{
			Cheat::GUI::Title("Self Options");
			Cheat::GUI::MenuOption("Model Changer", ModelChangerMenu);
			Cheat::GUI::MenuOption("Animations & Scenarios", AnimationsAndScenariosMenu);
			Cheat::GUI::MenuOption("Clothing", clothingmenu);
			Cheat::GUI::Toggle("Godmode", Cheat::CheatFeatures::GodmodeBool, "Makes your character invincible", true);
			Cheat::GUI::Toggle("No Ragdoll & Seatbelt", Cheat::CheatFeatures::NoRagdollAndSeatbeltBool, "Disables ragdoll on your character");
			Cheat::GUI::Toggle("Super Jump", Cheat::CheatFeatures::SuperJumpBool, "Makes your character jump higher");
			Cheat::GUI::Toggle("Super Run", Cheat::CheatFeatures::SuperRunBool, "Run very fast");
			Cheat::GUI::Toggle("Fast Run", Cheat::CheatFeatures::FastRunBool, "Multiplies run speed");
			Cheat::GUI::Toggle("Unlimited Special Ability", Cheat::CheatFeatures::UnlimitedSpecialAbilityBool, "Always 100% Special Ability");
			Cheat::GUI::Toggle("Ignored By Everyone", Cheat::CheatFeatures::PlayerIgnoredBool, "NPC's will (mostly) ignore you");
			Cheat::GUI::Toggle("Never Wanted", Cheat::CheatFeatures::NeverWantedBool, "Never get a wanted level");
			if (Cheat::GUI::Int("Wanted Level", PlayerWantedLevelInteger, 0, 5, 1, false, "Set Wanted Level")) { Cheat::CheatFeatures::NeverWantedBool = false; PLAYER::SET_PLAYER_WANTED_LEVEL(Cheat::GameFunctions::PlayerID, PlayerWantedLevelInteger, false); PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(Cheat::GameFunctions::PlayerID, false); }
			Cheat::GUI::Toggle("Invisible", Cheat::CheatFeatures::PlayerInvisibleBool, "Makes your character invisible");
			Cheat::GUI::Toggle("Explosive Melee", Cheat::CheatFeatures::ExplosiveMeleeBool, "Objects you hit with melee explode");
			Cheat::GUI::Toggle("Tiny Player", Cheat::CheatFeatures::TinyPlayerBool, "Lowers your character's scaling");
			Cheat::GUI::Toggle("Super Man", Cheat::CheatFeatures::SuperManBool, "Fly around like a superman!");
			if (Cheat::GUI::Int("Player Opacity", Cheat::CheatFeatures::PlayerOpacityInt, 50, 250, 50, false, "Changes local player opacity")) { ENTITY::SET_ENTITY_ALPHA(Cheat::GameFunctions::PlayerPedID, (Cheat::CheatFeatures::PlayerOpacityInt), false); }
			if (Cheat::GUI::Option("Suicide", "Kill your character")) { PED::APPLY_DAMAGE_TO_PED(Cheat::GameFunctions::PlayerPedID, 300, true); }
			if (Cheat::GUI::Option("Give BST", "Get Bull Shark Testosterone - GTAO Only")) { globalHandle(2540384).At(4620).As<int>() = 1; }
			if (Cheat::GUI::Option("Clean Player", "Remove any damage from player character")) { PED::CLEAR_PED_BLOOD_DAMAGE(Cheat::GameFunctions::PlayerPedID); PED::RESET_PED_VISIBLE_DAMAGE(Cheat::GameFunctions::PlayerPedID); Cheat::GameFunctions::MinimapNotification("Player Cleaned"); }	
		}
		break;
		case SelectedPlayerMoneyMenu:
		{
			Cheat::GUI::Title("Money Options");
			Cheat::GUI::Toggle("Toggle", Cheat::CheatFeatures::MoneyDropBool, "Enable Money Drop on selected player", false);
			Cheat::GUI::Int("Drop Delay", Cheat::CheatFeatures::MoneyDropDelay, 50, 2000, 50, false, "Set to 1500 to prevent transaction errors");
		} 
		break;
		case clothingmenu:
		{
			Cheat::GUI::Title("Clothing Options"); 
			Cheat::GUI::MenuOption("Outfits", outfitsmenu); 
			Cheat::GUI::MenuOption("Components Changer", componentschangermenu);
		}
		break; 
		case componentschangermenu:
		{
			Cheat::GUI::Title("Components Changer");
			if (Cheat::GUI::Int("Face", SetPedTexture_Face, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 0, SetPedTexture_Face, 0); }
			if (Cheat::GUI::Int("Face Texture", SetPedTexture_FaceTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 0, SetPedTexture_Face, SetPedTexture_Face); }
			if (Cheat::GUI::Int("Head", SetPedTexture_Head, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 0, SetPedTexture_Head, 0); }
			if (Cheat::GUI::Int("Head Texture", SetPedTexture_HeadTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 1, SetPedTexture_Head, SetPedTexture_HeadTexture); }
			if (Cheat::GUI::Int("Hair", SetPedTexture_Hair, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, 0); }
			if (Cheat::GUI::Int("Hair Texture", SetPedTexture_HairTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 2, SetPedTexture_Hair, SetPedTexture_HairTexture); }
			if (Cheat::GUI::Int("Torso", SetPedTexture_Torso, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, 0); }
			if (Cheat::GUI::Int("Torso Texture", SetPedTexture_TorsoTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 3, SetPedTexture_Torso, SetPedTexture_TorsoTexture); }
			if (Cheat::GUI::Int("Legs", SetPedTexture_Legs, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, 0); }
			if (Cheat::GUI::Int("Legs Texture", SetPedTexture_LegsTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 4, SetPedTexture_Legs, SetPedTexture_LegsTexture); }
			if (Cheat::GUI::Int("Hands", SetPedTexture_Hands, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, 0); }
			if (Cheat::GUI::Int("Hands Texture", SetPedTexture_HandsTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 5, SetPedTexture_Hands, SetPedTexture_HandsTexture); }
			if (Cheat::GUI::Int("Feet", SetPedTexture_Feet, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, 0); }
			if (Cheat::GUI::Int("Feet Texture", SetPedTexture_FeetTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 6, SetPedTexture_Feet, SetPedTexture_FeetTexture); }
			if (Cheat::GUI::Int("Eyes", SetPedTexture_Eyes, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, 0); }
			if (Cheat::GUI::Int("Eyes Texture", SetPedTexture_EyesTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 7, SetPedTexture_Eyes, SetPedTexture_EyesTexture); }
			if (Cheat::GUI::Int("Accesories", SetPedTexture_Accesories, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, 0); }
			if (Cheat::GUI::Int("Accesories Texture", SetPedTexture_AccesoriesTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 8, SetPedTexture_Accesories, SetPedTexture_AccesoriesTexture); }
			if (Cheat::GUI::Int("Accesories2", SetPedTexture_AccesoriesSec, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, 0); }
			if (Cheat::GUI::Int("Accesories2 Texture", SetPedTexture_AccesoriesSecTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 9, SetPedTexture_AccesoriesSec, SetPedTexture_AccesoriesSecTexture); }
			if (Cheat::GUI::Int("Torso 2", SetPedTexture_TorsoSec, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, 0); }
			if (Cheat::GUI::Int("Torso 2 Texture", SetPedTexture_TorsoSecTexture, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 11, SetPedTexture_TorsoSec, SetPedTexture_TorsoSecTexture); }
			if (Cheat::GUI::Int("Textures", SetPedTexture_Textures, 0, 255, 1, false, "")) { Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 10, SetPedTexture_Textures, 0); }
			if (Cheat::GUI::Int("Textures Texture", SetPedTexture_TexturesTexture, 0, 255, 1, false, "")) {  Cheat::GameFunctions::SetPedTexture(Cheat::GameFunctions::PlayerPedID, 9, SetPedTexture_Textures, SetPedTexture_TexturesTexture); }
		}
		break;
		case outfitsmenu:
		{
			Cheat::GUI::Title("Outfits");
			if (Cheat::GUI::Option("Random Outfit", "Get random outfit")) { PED::SET_PED_RANDOM_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, true); }
			if (Cheat::GUI::Option("Police Uniform", "Get police uniform"))
			{
				PED::SET_PED_PROP_INDEX(Cheat::GameFunctions::PlayerPedID, 0, 45, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 11, 48, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 4, 34, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 3, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 6, 25, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 8, 35, 0, 0);			
			}
			if (Cheat::GUI::Option("Default Variation", "Get default pedmodel variation")) 
			{
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID);
			}
			if (Cheat::GUI::Option("Random Variation", "Get random pedmodel variation"))
			{
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, true);
			}
			if (Cheat::GUI::Option("Random Accessories", "")) 
			{
				PED::SET_PED_RANDOM_PROPS(Cheat::GameFunctions::PlayerPedID);
			}
			if (Cheat::GUI::Option("Reset Appearance", "")) 
			{
				PED::CLEAR_ALL_PED_PROPS(Cheat::GameFunctions::PlayerPedID);
				PED::CLEAR_PED_DECORATIONS(Cheat::GameFunctions::PlayerPedID);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 1, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 5, 0, 0, 0);
				PED::SET_PED_COMPONENT_VARIATION(Cheat::GameFunctions::PlayerPedID, 9, 0, 0, 0);
			}

		}
		break; 
		case SelectedPlayerAttachmentOptions:
		{
			Cheat::GUI::Title("Attach Options");
			if (Cheat::GUI::Option("Plate", ""))				{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "p_oil_slick_01"); }
			if (Cheat::GUI::Option("EMP", ""))				{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "hei_prop_heist_emp"); }
			if (Cheat::GUI::Option("Beach Fire", ""))		{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_beach_fire"); }
			if (Cheat::GUI::Option("Orange Ball", ""))		{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_juicestand"); }
			if (Cheat::GUI::Option("Weed", ""))				{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_weed_01"); }
			if (Cheat::GUI::Option("Safe", ""))				{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "p_v_43_safe_s"); }
			if (Cheat::GUI::Option("UFO", ""))				{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "p_spinning_anus_s"); }
			if (Cheat::GUI::Option("Toilet", ""))			{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_ld_toilet_01"); }
			if (Cheat::GUI::Option("Christmas Tree", ""))	{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_xmas_tree_int"); }
			if (Cheat::GUI::Option("Windmill", ""))			{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_windmill_01"); }
			if (Cheat::GUI::Option("Radar", ""))				{ Cheat::GameFunctions::AttachObjectToPed(Cheat::CheatFeatures::selectedPlayer, "prop_air_bigradar"); }

			if (Cheat::GUI::Option("Detach All Objects", "Only detaches above attached objects")) 
			{
				const std::vector<std::string> ObjectsToRemoveArray = { 
					"p_oil_slick_01",  "hei_prop_heist_emp", "prop_beach_fire",  "prop_juicestand",
					"prop_weed_01",  "p_v_43_safe_s",  "p_spinning_anus_s",  "prop_ld_toilet_01",
					"prop_xmas_tree_int",  "prop_windmill_01",  "prop_air_bigradar"
				};
				for (auto const& i : ObjectsToRemoveArray) 
				{ 
					Cheat::GameFunctions::DetachObjectFromPed(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Cheat::CheatFeatures::selectedPlayer), CheatFunctions::StringToChar(i));
				}			
				Cheat::GameFunctions::MinimapNotification("Objects Detached & Removed");
			}
		}
		break;
		case protections:
		{
			Cheat::GUI::Title("Protections");	
			if (Cheat::GUI::Option("Enable/Disable Anti-Crash Camera", "Changes camera position to prevent crash")) { Cheat::GameFunctions::EnableDisableAntiCrashCamera(); }
			Cheat::GUI::Break("Protection Options", true);
			if (Cheat::GUI::Option("Enable All", "Enable all protection options")) {
				Cheat::CheatFeatures::ProtectionVoteKickBool = true;
				Cheat::CheatFeatures::ProtectionFreezeBool = true;
				Cheat::CheatFeatures::ProtectionSessionWeatherBool = true;
				Cheat::CheatFeatures::ProtectionGiveRemoveWeaponsBool = true;
				Cheat::CheatFeatures::ProtectionSessionTimeBool = true;
				Cheat::CheatFeatures::ProtectionWorldEventsBool = true;
				Cheat::CheatFeatures::ProtectionAlterWantedLevelBool = true;
				Cheat::CheatFeatures::ProtectionVehicleBool = true;
				Cheat::CheatFeatures::BlockMaliciousScriptEvents = true;
			}
			if (Cheat::GUI::Option("Disable All", "Disable all protection options")) {
				Cheat::CheatFeatures::ProtectionVoteKickBool = false;
				Cheat::CheatFeatures::ProtectionFreezeBool = false;
				Cheat::CheatFeatures::ProtectionSessionWeatherBool = false;
				Cheat::CheatFeatures::ProtectionGiveRemoveWeaponsBool = false;
				Cheat::CheatFeatures::ProtectionSessionTimeBool = false;
				Cheat::CheatFeatures::ProtectionWorldEventsBool = false;
				Cheat::CheatFeatures::ProtectionAlterWantedLevelBool = false;
				Cheat::CheatFeatures::ProtectionVehicleBool = false;
				Cheat::CheatFeatures::BlockMaliciousScriptEvents = false;
			}
			Cheat::GUI::Toggle("Remote Events", Cheat::CheatFeatures::BlockMaliciousScriptEvents, "Some GTAO missions might not work");
			Cheat::GUI::Toggle("Remote Events -> Block All", Cheat::CheatFeatures::BlockAllScriptEvents, "Join GTAO before enabling", false);
			Cheat::GUI::Toggle("Vote Kick", Cheat::CheatFeatures::ProtectionVoteKickBool, "");
			Cheat::GUI::Toggle("Freeze", Cheat::CheatFeatures::ProtectionFreezeBool, "");
			Cheat::GUI::Toggle("Session Weather", Cheat::CheatFeatures::ProtectionSessionWeatherBool, "");
			Cheat::GUI::Toggle("Session Time", Cheat::CheatFeatures::ProtectionSessionTimeBool, "");
			Cheat::GUI::Toggle("Give/Remove Weapons", Cheat::CheatFeatures::ProtectionGiveRemoveWeaponsBool, "");
			Cheat::GUI::Toggle("Alter Wanted Level", Cheat::CheatFeatures::ProtectionAlterWantedLevelBool, "");
			Cheat::GUI::Toggle("World Events", Cheat::CheatFeatures::ProtectionWorldEventsBool, "Fire, explosions and more");
			Cheat::GUI::Toggle("Vehicle", Cheat::CheatFeatures::ProtectionVehicleBool, "Control & Explosions");
		}
		break; 
		case AnimationsAndScenariosMenu:
		{
			Cheat::GUI::Title("Animations & Scenarios");
			if (Cheat::GUI::Option("Stop Scenarios & Animations", "")) { Cheat::GameFunctions::ClearAllAnimations(); }
			Cheat::GUI::Break("Animations", true);
			if (Cheat::GUI::Option("Sex Receiver", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("rcmpaparazzo_2", "shag_loop_poppy");
			}
			if (Cheat::GUI::Option("Sex Giver", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("rcmpaparazzo_2", "shag_loop_a");
			}
			if (Cheat::GUI::Option("Stripper Dance", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1");
			}
			if (Cheat::GUI::Option("Pole Dance", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
			}
			if (Cheat::GUI::Option("Push Ups", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("amb@world_human_push_ups@male@base", "base");
			}
			if (Cheat::GUI::Option("Sit Ups", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("amb@world_human_sit_ups@male@base", "base");
			}
			if (Cheat::GUI::Option("Celebrate", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("rcmfanatic1celebrate", "celebrate");
			}
			if (Cheat::GUI::Option("Electrocution", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("ragdoll@human", "electrocute");
			}
			if (Cheat::GUI::Option("Suicide", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("mp_suicide", "pistol");
			}
			if (Cheat::GUI::Option("Showering", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				Cheat::GameFunctions::DoLocalPedAnimation("mp_safehouseshower@male@", "male_shower_idle_b");
			}
			Cheat::GUI::Break("Scenarios", true);
			if (Cheat::GUI::Option("Paparizzi", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_PAPARAZZI", 0, true);
			}
			if (Cheat::GUI::Option("Drug Dealer", ""))
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_DRUG_DEALER_HARD", 0, true);
			}
			if (Cheat::GUI::Option("Drinking Coffee", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_AA_COFFEE", 0, true);
			}
			if (Cheat::GUI::Option("Playing Instruments", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_MUSICIAN", 0, true);
			}
			if (Cheat::GUI::Option("Flexing", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_MUSCLE_FLEX", 0, true);
			}
			if (Cheat::GUI::Option("Jogging", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_JOG_STANDING", 0, true);
			}
			if (Cheat::GUI::Option("Binoculars", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_BINOCULARS", 0, true);
			}
			if (Cheat::GUI::Option("Clipboard", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_CLIPBOARD", 0, true);
			}
			if (Cheat::GUI::Option("Bench Press", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, true);
			}
			if (Cheat::GUI::Option("Chin Ups", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, true);
			}
			if (Cheat::GUI::Option("BBQ", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "PROP_HUMAN_BBQ", 0, true);
			}
			if (Cheat::GUI::Option("Superhero", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_SUPERHERO", 0, true);
			}
			if (Cheat::GUI::Option("Fishing", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_STAND_FISHING", 0, true);
			}
			if (Cheat::GUI::Option("Security", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, true);
			}
			if (Cheat::GUI::Option("Leaf Blower", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, true);
			}
			if (Cheat::GUI::Option("Film Shocking", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, true);
			}
			if (Cheat::GUI::Option("Idle Cop", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_COP_IDLES", 0, true);
			}
			if (Cheat::GUI::Option("Drinking", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_DRINKING", 0, true);
			}
			if (Cheat::GUI::Option("Golf Player", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_GOLF_PLAYER", 0, true);
			}
			if (Cheat::GUI::Option("Welding", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_WELDING", 0, true);
			}
			if (Cheat::GUI::Option("Smoking Pot", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_SMOKING_POT", 0, true);
			}
			if (Cheat::GUI::Option("Hammering", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_HAMMERING", 0, true);
			}
			if (Cheat::GUI::Option("Tennis", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_TENNIS_PLAYER", 0, true);
			}
			if (Cheat::GUI::Option("Drilling", "")) 
			{
				Cheat::GameFunctions::ClearAllAnimations();
				AI::TASK_START_SCENARIO_IN_PLACE(Cheat::GameFunctions::PlayerPedID, "WORLD_HUMAN_CONST_DRILL", 0, true);
			}
		}
		break; 
		case SettingsMenu:
		{
			Cheat::GUI::Title("Settings");
			Cheat::GUI::MenuOption("GUI Settings", guisettings);
			Cheat::GUI::MenuOption("Cheat Settings", CheatSettingsMenu);
			if (Cheat::GUI::Option("Visit Github Page", ""))
			{
				system("start https://github.com/HatchesPls/GrandTheftAutoV-Cheat");
			}
		}
		break;
		case CheatSettingsMenu:
		{
			Cheat::GUI::Title("Cheat Settings");
			Cheat::GUI::Break("Player List", true);
			Cheat::GUI::Toggle("Show Player Information", Cheat::CheatFeatures::ShowPlayerInformationPlayerList, "Toggle Player Information Box");
			Cheat::GUI::Toggle("Show Player Tags", Cheat::CheatFeatures::ShowPlayerTagsPlayerList, "Toggle Player Tags");
			Cheat::GUI::Toggle("Hide Own IP Address", Cheat::CheatFeatures::HideOwnIPAddress, "Hiddes Local IP Address");
			Cheat::GUI::Break("Speed", true);
			Cheat::GUI::Toggle("Use KM/H", Cheat::CheatFeatures::UseKMH, "If disabled MP/H is used");
			Cheat::GUI::Break("Protection", true);
			Cheat::GUI::Toggle("Blocked Script Notifications", Cheat::CheatFeatures::ShowBlockedScriptEventNotifications, "");
		}
		break;
		case guisettings:
		{
			Cheat::GUI::Title("GUI Settings");
			Cheat::GUI::MenuOption("Theme Loader", ThemeLoaderMenu);
			Cheat::GUI::Break("Settings", true);
			Cheat::GUI::MenuOption("Colors", GUIColorsMenu);
			Cheat::GUI::MenuOption("Header Options", headeroptionsmenu);
			Cheat::GUI::StringVector("Toggles", { "Shop Box", "Circle" }, Cheat::CheatFeatures::BoolOptionVectorPosition, "Select Boolean Toggle", false);
			Cheat::GUI::Int("Max Visible Menu Options", Cheat::GUI::maxVisOptions, 5, 16, 1, false);
			Cheat::GUI::Toggle("Restore To Previous Submenu", Cheat::GUI::RestorePreviousSubmenu, "When opening restores previous submenu", false);
			Cheat::GUI::Float("X-Axis", Cheat::GUI::guiX, 0.11f, 0.86f, 0.01f, true, false, "");
			Cheat::GUI::Float("Y-Axis", Cheat::GUI::guiY, 0.10f, 0.90f, 0.01f, true, false, "");
			Cheat::GUI::Float("GUI Width", Cheat::GUI::guiWidth, 0.21f, 0.30f, 0.01f, true, false, "TODO: Text Scaling not implemented");
			std::string OpenKeyString = "Open Key: ~c~" + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::OpenGUIKey);
			if (Cheat::GUI::Option(OpenKeyString.c_str(), "Select to change"))
			{
				int PressedKey = Cheat::CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0) { Cheat::GUI::OpenGUIKey = PressedKey; Cheat::GameFunctions::MinimapNotification("Open Key has been set"); }
			}
			std::string GUINavigationKeyString = "Cursor Navigation: ~c~" + Cheat::CheatFunctions::VirtualKeyCodeToString(Cheat::GUI::GUINavigationKey);
			if (Cheat::GUI::Option(GUINavigationKeyString.c_str(), "Select to change"))
			{
				int PressedKey = Cheat::CheatFunctions::WaitForAndReturnPressedKey();
				if (PressedKey != 0) { Cheat::GUI::GUINavigationKey = PressedKey; Cheat::GameFunctions::MinimapNotification("Cursor Navigation Key has been set"); }
			}
			Cheat::GUI::Int("Key Press Delay", Cheat::GUI::keyPressDelay, 1, 250, 1, false);
		}
		break; 
		case headeroptionsmenu:
		{
			Cheat::GUI::Title("Header Options");
			Cheat::GUI::Toggle("Show Header GUI", Cheat::GUI::ShowHeaderGUI, "Toggle Header GUI", false);
			Cheat::GUI::Toggle("Show Header Background", Cheat::GUI::ShowHeaderBackground, "Toggle Header Background", false);
			Cheat::GUI::Toggle("Show Header Glare", Cheat::GUI::ShowHeaderGlare, "Show GTAO Interaction Menu Glare", false);
		}
		break;
		case GUIColorsMenu:
		{
			Cheat::GUI::Title("Colors");
			Cheat::GUI::MenuOption("Title Background", GUITitleBackgroundColorMenu);
			Cheat::GUI::MenuOption("Header Background", settingsheaderbackground);
			Cheat::GUI::MenuOption("Menu Background", settingsmenubackground);
			Cheat::GUI::MenuOption("Menu Bottom Background", settingsmenubottombackground);
			Cheat::GUI::MenuOption("Small Title Background", settingssmalltitlebackground);
			Cheat::GUI::MenuOption("Options Scroller", settingsscroller);
			Cheat::GUI::MenuOption("Option Text", settingsoptiontext);
			Cheat::GUI::MenuOption("Line And Arrow", settingsbottomline);
		}
		break;
		case settingsmenubottombackground:
		{
			Cheat::GUI::Title("Menu Bottom Background");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::MenuBottomRect.r = 0;
				Cheat::GUI::MenuBottomRect.g = 0;
				Cheat::GUI::MenuBottomRect.b = 0;
				Cheat::GUI::MenuBottomRect.a = 255;
			}		
			Cheat::GUI::Int("Red", Cheat::GUI::MenuBottomRect.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::MenuBottomRect.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::MenuBottomRect.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::MenuBottomRect.a, 0, 255, 1, false);
		}
		break;
		case settingsmenubackground:
		{
			Cheat::GUI::Title("Menu Background");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::MenuBackgroundRect.r = 0;
				Cheat::GUI::MenuBackgroundRect.g = 0;
				Cheat::GUI::MenuBackgroundRect.b = 0;
				Cheat::GUI::MenuBackgroundRect.a = 220;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::MenuBackgroundRect.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::MenuBackgroundRect.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::MenuBackgroundRect.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::MenuBackgroundRect.a, 0, 255, 1, false);
		}
		break;
		case settingssmalltitlebackground:
		{
			Cheat::GUI::Title("Small Title Background");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::titleRect.r = 0;
				Cheat::GUI::titleRect.g = 0;
				Cheat::GUI::titleRect.b = 255;
				Cheat::GUI::titleRect.a = 255;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::titleRect.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::titleRect.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::titleRect.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::titleRect.a, 0, 255, 1, false);
		}
		break;
		case settingsbottomline:
		{
			Cheat::GUI::Title("Line And Arrow");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::TopAndBottomLine.r = 0;
				Cheat::GUI::TopAndBottomLine.g = 0;
				Cheat::GUI::TopAndBottomLine.b = 255;
				Cheat::GUI::TopAndBottomLine.a = 255;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::TopAndBottomLine.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::TopAndBottomLine.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::TopAndBottomLine.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::TopAndBottomLine.a, 0, 255, 1, false);
		}
		break;
		case settingsheaderbackground:
		{
			Cheat::GUI::Title("Header Background");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::headerRect.r = 0;
				Cheat::GUI::headerRect.g = 0;
				Cheat::GUI::headerRect.b = 255;
				Cheat::GUI::headerRect.a = 200;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::headerRect.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::headerRect.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::headerRect.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::headerRect.a, 0, 255, 1, false);
		}
		break;
		case ThemeLoaderMenu:
		{
			Cheat::GUI::Title("Theme Loader");
			Cheat::GUI::MenuOption("Theme Files", ThemeFilesMenu);
			if (!Cheat::GUI::CurrentTheme.empty())
			{
				Cheat::GUI::Break("Active Theme: ~c~" + Cheat::GUI::CurrentTheme, false);
				if (Cheat::GUI::Option("Save To Current Theme", ""))
				{
					Cheat::GUI::SaveTheme(Cheat::GUI::CurrentTheme);
				}
				if (Cheat::GUI::Option("Delete Current Theme", "Delete active theme"))
				{
					Cheat::GUI::DeleteCurrentTheme();
				}
			}
			else
			{
				Cheat::GUI::Break("Active Theme: ~c~None", false);
			}
			if (Cheat::GUI::Option("Save To New", "Save current GUI to new theme file"))
			{
				char* NewThemeFileName = Cheat::GameFunctions::DisplayKeyboardAndReturnInput(20);
				if (NewThemeFileName == "0") { break; }
				Cheat::GUI::SaveTheme(NewThemeFileName);
			}
		}
		break;
		case ThemeFilesMenu:
		{
			Cheat::GUI::Title("Theme Files");
			if (!Cheat::GUI::ThemeFilesVector.empty())
			{
				for (auto const& i : Cheat::GUI::ThemeFilesVector)
				{
					if (Cheat::GUI::Option(i, ""))
					{
						std::string ThemeFilePathMenuList = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Themes\\" + i + ".ini";
						if (!Cheat::CheatFunctions::FileOrDirectoryExists(ThemeFilePathMenuList)) { Cheat::GameFunctions::MinimapNotification("~r~Unable to locate theme file"); break; }
						Cheat::GUI::LoadTheme(CheatFunctions::StringToChar(i), false);
					}
				}
			}
			else
			{
				Cheat::GUI::Break("No Theme Files Available", false);
			}
		}
		break;
		case GUITitleBackgroundColorMenu:
		{
			Cheat::GUI::Title("Title Background");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::MainTitleRect.r = 0;
				Cheat::GUI::MainTitleRect.g = 0;
				Cheat::GUI::MainTitleRect.b = 0;
				Cheat::GUI::MainTitleRect.a = 255;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::MainTitleRect.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::MainTitleRect.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::MainTitleRect.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::MainTitleRect.a, 0, 255, 1, false);
		}
		break;
		case settingsoptiontext:
		{
			Cheat::GUI::Title("Option Text");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::optionText.r = 255;
				Cheat::GUI::optionText.g = 255;
				Cheat::GUI::optionText.b = 255;
				Cheat::GUI::optionText.a = 255;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::optionText.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::optionText.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::optionText.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::optionText.a, 0, 255, 1, false);
		}
		break;
		case settingsscroller:
		{
			Cheat::GUI::Title("Options Scroller");
			if (Cheat::GUI::Option("Set Default", ""))
			{
				Cheat::GUI::scroller.r = 0;
				Cheat::GUI::scroller.g = 0;
				Cheat::GUI::scroller.b = 255;
				Cheat::GUI::scroller.a = 255;
			}
			Cheat::GUI::Int("Red", Cheat::GUI::scroller.r, 0, 255, 1, false);
			Cheat::GUI::Int("Green", Cheat::GUI::scroller.g, 0, 255, 1, false);
			Cheat::GUI::Int("Blue", Cheat::GUI::scroller.b, 0, 255, 1, false);
			Cheat::GUI::Int("Opacity", Cheat::GUI::scroller.a, 0, 255, 1, false);
		}
		break;
		}
		Cheat::GUI::End();
		GameHooking::PauseMainFiber(0, false);
	}
}

DWORD WINAPI InitThread(LPVOID lpParam)
{
	Cheat::CheatFunctions::CreateConsole();
	Cheat::LogFunctions::Init();
	GameHooking::DoGameHooking();
	//Hooks created - this thread is no longer needed
	return 0;
}

HMODULE Cheat::CheatModuleHandle;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		Cheat::CheatModuleHandle = hModule;
		//Create 'gtav' directory
		std::string GtavDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav";
		if (!Cheat::CheatFunctions::FileOrDirectoryExists(GtavDirectoryPath)) {  Cheat::CheatFunctions::CreateNewDirectory(GtavDirectoryPath); }	
		//Create 'Logs' directory
		std::string LogsDirectoryPath = Cheat::CheatFunctions::ReturnCheatModuleDirectoryPath() + (std::string)"\\gtav\\Logs";
		if (!Cheat::CheatFunctions::FileOrDirectoryExists(LogsDirectoryPath)) { Cheat::CheatFunctions::CreateNewDirectory(LogsDirectoryPath); }
		//Continue cheat loading
		CreateThread(NULL, NULL, InitThread, hModule, NULL, NULL);
		break;
	}
	return TRUE;
}