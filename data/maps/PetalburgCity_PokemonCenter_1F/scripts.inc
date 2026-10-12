PetalburgCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

PetalburgCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_PETALBURG_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

PetalburgCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_PETALBURG_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_FatMan::
	msgbox PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP, MSGBOX_NPC
	end

PetalburgCity_PokemonCenter_1F_EventScript_Woman::
	lock
	faceplayer
	msgbox PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsStarterInParty
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayStarterTypeInfo::
	call_if_eq VAR_STARTER_MON, 0, PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType
	call_if_eq VAR_STARTER_MON, 1, PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType
	call_if_eq VAR_STARTER_MON, 2, PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType
	release
	end

PetalburgCity_PokemonCenter_1F_EventScript_SayTreeckoType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayTorchicType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_EventScript_SayMudkipType::
	msgbox PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType, MSGBOX_DEFAULT
	return

PetalburgCity_PokemonCenter_1F_Text_PCStorageSystem:
	.string "Ese sistema de almacenamiento\nde POKéMON en PC es tremendo…\p¡Quienquiera que lo haya hecho\ndebe de ser un científico de categoría!$"
	.string ""
	.string ""
	.string ""

PetalburgCity_PokemonCenter_1F_Text_OranBerryRegainedHP:
	.string "¡Cuando mi POKéMON se comió\nuna BAYA ARANJA, recuperó PS!$"
	.string ""

PetalburgCity_PokemonCenter_1F_Text_ManyTypesOfPokemon:
	.string "Hay muchos tipos de POKéMON.\pTodos ellos tienen puntos fuertes\ny débiles con respecto a otros tipos.\pSegún los tipos de POKéMON\nque haya en un combate,\lasí será de fácil o difícil.$"
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgCity_PokemonCenter_1F_Text_TreeckoIsGrassType:
	.string "Por ejemplo, tu TREECKO\nes de tipo PLANTA.\pEs fuerte contra los tipos\nAGUA y TIERRA.\pPero es débil contra los\nPOKéMON de tipo FUEGO.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgCity_PokemonCenter_1F_Text_TorchicIsFireType:
	.string "Por ejemplo, tu TORCHIC\nes de tipo FUEGO.\pEs fuerte contra los tipos\nPLANTA y BICHO.\pPero es débil contra los\nPOKéMON de tipo AGUA.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgCity_PokemonCenter_1F_Text_MudkipIsWaterType:
	.string "Por ejemplo, tu MUDKIP\nes de tipo AGUA.\pEs fuerte contra los\nPOKéMON de tipo FUEGO.\pPero es débil contra los\ntipos PLANTA y ELÉCTRICO.$"
	.string ""
	.string ""
	.string ""
	.string ""

