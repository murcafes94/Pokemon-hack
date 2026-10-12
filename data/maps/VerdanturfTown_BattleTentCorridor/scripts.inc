VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_VERDANTURF_TENT_CORRIDOR_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end


@ Leftover text from when this was a Contest Hall in R/S
@ Unused
VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "Which CONTEST are you entering?\nWant a piece of advice?\pIn any CONTEST, for example, a CUTE\nCONTEST, I don’t think they judge you\lonly on cuteness in the first round.\pYou need to work out ways for raising\nPOKéMON better.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "I raised my POKéMON to be cute.\pI found out you can put POKéMON in\na CONTEST for cuteness!\pI’m so glad I raised my POKéMON with\nloving care…$"
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "My POKéMON rules!\pIt’s cool, tough yet beautiful, cute,\nand smart. It’s complete!\pI may as well go for wins in every\nsingle CONTEST.$"
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "POKéMON CONTESTS\n"
	.string "NORMAL RANK STAGE!$"

