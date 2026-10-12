PacifidlogTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition:
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume:
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy::
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl::
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman::
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign::
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent:
	.string "El mar que separa OROMAR de CIUDAD\nPORTUAL tiene muchas corrientes.\p¡Si haces SURF en él, puedes acabar\nen cualquier sitio!$"
	.string ""
	.string ""
	.string ""

PacifidlogTown_Text_NeatHousesOnWater:
	.string "Mira qué cosa más chula.\n¡Las casas flotan sobre el agua!\p¡Yo he nacido aquí!$"
	.string ""
	.string ""

PacifidlogTown_Text_SkyPillarTooScary:
	.string "¿El PILAR CELESTE?\pAh, tú te refieres a esa torre\naltísima que está más allá.\pLo que es yo, no subía hasta arriba\nni loco. Ese sitio me da escalofríos.\pPor el contrario, vivir a nivel del\nmar en OROMAR es una gozada.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PacifidlogTown_Text_TownSign:
	.string "PUEBLO OROMAR\p“Donde el radiante sol ilumina\nlas aguas cada día.”$"
	.string ""
	.string ""

