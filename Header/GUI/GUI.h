#pragma once

enum SubMenus
{
	NOMENU,
	MainMenu,
	SelfOptionsMenu,
	SettingsMenu,
	GUIColorsMenu,
	ThemeLoaderMenu,
	ThemeFilesMenu,
	GUITitleBackgroundColorMenu,
	settingsheaderbackground,
	settingssmalltitlebackground,
	settingsscroller,
	settingsmenubackground,
	settingsoptiontext,
	settingsbottomline,
	settingsmenubottombackground,
	PlayerListMenu,
	SelectedPlayerMenu,
	teleportmenu,
	weaponmenu,
	VehicleCustomizerColorMenu,
	miscmenu,
	worldmenu,
	vehiclemenu,
	AnimationsAndScenariosMenu,
	nearbyvehicles_menu,
	nearbypeds_menu,
	iplloader,
	iplteleports,
	weathermenu,
	VehicleSpawnSettings,
	AllPlayersMenu,
	ModelChangerMenu,
	vehiclespawnermenu,
	Super,
	Sports,
	smugglersrun,
	SportClassic,
	Offroad,
	Sedans,
	Coupes,
	Muscle,
	Boats,
	Commercial,
	Compacts,
	Cycles,
	Emergency,
	Helicopters,
	Industrial,
	Military,
	Motorcycles,
	Planes,
	Service,
	SUV,
	Trailer,
	Trains,
	vehicle_lsc_neon_options,
	vehicle_lsc_color_options,
	Utility,
	Vans,
	SSASSSDLC,
	doomsdayheistdlc,
	gunrunningdlc,
	CunningStuntsDLCMenu,
	afterhoursdlc,
	arenawardlc,
	casinodlc,
	diamondcasinoheist,
	SummerSpecialDLCMenu,
	CayoPericoHeistDLCMenu,
	OnlineOptionsMenu,
	timemenu,
	CommonTeleportLocations,
	SelectedPlayerAttachmentOptions,
	SelectedPlayerTrollMenu,
	SelectedPlayerFriendlyMenu,
	protections,
	ESPMenu,
	clothingmenu,
	outfitsmenu,
	componentschangermenu,
	SelectedPlayerMoneyMenu,
	SelectedPlayerRemoteOptions,
	sessionweathermenu,
	sessiontimemenu,
	SessionChatMenu,
	vehicleweaponsmenu,
	allplayers_trolloptionsmenu,
	statsoptionsmenu,
	vehicledooroptionsmenu,
	vehiclemultipliersmenus,
	custombulletsmenu,
	vehiclegunmenu,
	aimbotsettingsmenu,
	rankmenu,
	miscstatsmenu,
	SelectedPlayerTeleportMenu,
	sessionoptionsmenu,
	hudmenu,
	guisettings,
	CheatSettingsMenu,
	unlocksmenu,
	reportsmenu_stats,
	allplayers_weaponoptionsmenu,
	headeroptionsmenu,
	VehicleCustomizerMenu,
	DLCVehiclesMenu,
	SUBMENUS_END //Used to get total size of SubMenus (SUBMENUS_END - 2) 
};

typedef struct VECTOR2 { float x, y; };
typedef struct VECTOR2_2 { float w, h; };
typedef struct RGBAF { int r, g, b, a, f; };
typedef struct RGBA { int r, g, b, a; };
typedef struct RGB { int r, g, b; };

namespace Cheat
{
	namespace GUI
	{
		namespace Drawing
		{
			void Text(std::string text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
			void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
			void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
			void InitTextureFile();
			void DrawScaleform(const float x, const float y, const float sx, const float sy, const int r, const int g, const int b);
		}

		extern void ControlsLoop();
		extern float guiX;
		extern float guiY;
		extern float guiWidth;
		extern std::vector <std::string> ThemeFilesVector;
		extern bool ShowHeaderBackground;
		extern bool ShowHeaderGUI;
		extern bool ShowHeaderGlare;
		extern bool HideGUIElements;
		extern bool CheatGUIHasBeenOpened;
		extern bool CurrentOptionIsSavable;
		extern std::string CurrentTheme;
		extern bool ControlsDisabled;
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool RestorePreviousSubmenu;
		extern int maxVisOptions;
		extern int currentOption;
		extern int currentOptionMenuBottom;
		extern int previousOption;
		extern int optionCount;
		extern int optionCountMenuBottom;
		extern int TotalOptionsCount;
		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int PreviousMenuLevel;
		extern SubMenus PreviousMenu;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];
		extern RGBAF count;
		extern RGBAF titleText;
		extern RGBA titleRect;
		extern RGBA MainTitleRect;
		extern RGBA headerRect;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBAF integre;
		extern RGBA optionRect;
		extern RGBA MenuBackgroundRect;
		extern RGBA MenuBottomRect;
		extern RGBA scroller;
		extern RGBA TopAndBottomLine;
		extern RGBA primary;
		extern RGBA secondary;
		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int OpenGUIKey;
		extern int GUINavigationKey;
		extern int SaveItemKey;
		extern void DeleteCurrentTheme();
		void MoveMenu(SubMenus menu);
		void BackMenu();
		void CloseGUI();
		void End();
		void ChangeControlsState(bool State);
		void LoadTheme(std::string ThemeFileName, bool StartUp);
		void SaveTheme(std::string ThemeFileName);
		extern bool SelectableHandler(bool DisabledState);

		void Title(std::string title);
		void AddPlayerInfoBoxTextEntry(std::string text, int Row1 = NULL, int Row2 = NULL, int Row3 = NULL, int Row4 = NULL);
		bool Break(std::string option, bool TextCentered);
		bool Option(std::string option, std::string InformationText, bool Disabled = false);
		bool VehicleOption(std::string option, std::string ModelName);
		bool MenuOption(std::string option, SubMenus newSub, bool Disabled = false);
		bool MenuOptionPlayerList(std::string PlayerName, SubMenus newSub);
		bool Toggle(std::string option, bool& b00l, std::string InformationText, bool IsSavable = true, bool Disabled = false);
		bool Int(std::string option, int& _int, int min, int max, int step, bool IsSavable = true, std::string InformationText = "Select to change", bool Disabled = false);
		bool Float(std::string option, float& _float, float min, float max, float steps, bool ReturnTrueWithValueChange, bool IsSavable = true, std::string InformationText = "", bool Disabled = false);
		bool IntVector(std::string option, std::vector<int> Vector, int& position, bool IsSavable = true, bool Disabled = false);
		bool FloatVector(std::string option, std::vector<float> Vector, int& position, bool IsSavable = true, bool Disabled = false);
		bool StringVector(std::string option, std::vector<std::string> Vector, int& position, std::string InformationText, bool IsSavable = true, bool Disabled = false);
	}
}