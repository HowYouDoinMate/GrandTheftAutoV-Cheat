#pragma once

struct VehicleModelPicturesStruct
{
	std::string DictName;
	std::string PreviewName;
};

struct WeaponHashesStruct
{
	std::string WeaponName;
	DWORD WeaponHash;
};

namespace Cheat
{
	namespace GameArrays
	{
		extern const int RankPointsArray[8000];
		extern const std::vector<std::string> CayoPericoHeistModels;
		extern const std::vector<std::string> SummerSpecialModels;
		extern const std::vector<std::string> PedModels;
		extern const std::vector<std::string> BoatModels;
		extern const std::vector<std::string> SmugglersRunModels;
		extern const std::vector<std::string> CunningStuntsDLCModels;
		extern const std::vector<std::string> DiamondCasinoHeistDLCModels;
		extern const std::vector<std::string> CasinoDLCModels;
		extern const std::vector<std::string> ArenaWarModels;
		extern const std::vector<std::string> AfterHoursModels;
		extern const std::vector<std::string> GunrunningModels;
		extern const std::vector<std::string> DoomsdayModels;
		extern const std::vector<std::string> SSASSSModels;
		extern const std::vector<std::string> VanModels;
		extern const std::vector<std::string> UtilityModels;
		extern const std::vector<std::string> TrainModels;
		extern const std::vector<std::string> SUVModels;
		extern const std::vector<std::string> SuperModels;
		extern const std::vector<std::string> TrailerModels;
		extern const std::vector<std::string> SportClassicModels;
		extern const std::vector<std::string> SportModels;
		extern const std::vector<std::string> ServiceModels;
		extern const std::vector<std::string> SedanModels;
		extern const std::vector<std::string> PlaneModels;
		extern const std::vector<std::string> OffRoadModels;
		extern const std::vector<std::string> MuscleModels;
		extern const std::vector<std::string> MotorcycleModels;
		extern const std::vector<std::string> MilitaryModels;
		extern const std::vector<std::string> IndustrialModels;
		extern const std::vector<std::string> HelicopterModels;
		extern const std::vector<std::string> EmergencyModels;
		extern const std::vector<std::string> CycleModels;
		extern const std::vector<std::string> CoupesModels;
		extern const std::vector<std::string> CompactsModels;
		extern const std::vector<std::string> CommercialModels;
		extern const std::vector<VehicleModelPicturesStruct> VehicleModelPictures;
		extern const std::vector<WeaponHashesStruct> WeaponsHashList;
	}
}