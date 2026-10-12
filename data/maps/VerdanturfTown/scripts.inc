VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "Me lo ha dicho mi papá.\pDice que este túnel está lleno\nde POKéMON asustadizos.\pSi escuchan algún ruido fuerte, se\nasustan y montan alborotos.\pPor eso detuvieron el proyecto de\nconstrucción del túnel.\p¡Pero hay un hombre empeñado en\nterminar el túnel él solito!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "Un hombre excavó un túnel para\nla mujer que amaba…\pEs decir, para poder ir a verla más\nfácilmente. ¡Eso es amor, señores!$"
	.string ""
	.string ""

VerdanturfTown_Text_AirCleanHere:
	.string "Por cómo sopla el viento, aquí nunca\nllega la ceniza volcánica.\pAl contrario, el aire de aquí es puro\ny agradable. Es muy bueno para las\lpersonas de salud delicada.$"
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "Mis POKéMON y yo estamos de racha.\pAsí que he decidido probar suerte en\nla TIENDA de BATALLA que hay aquí.$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "¿Has visto la cueva que hay cerca de\nla TIENDA POKéMON?\pDentro hay un tipo que intenta romper\nrocas para poder llegar al otro lado.\pSería estupendo tener el túnel…\nVisitar CIUDAD FÉRRICA sería\lmás sencillo.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "La cueva que hay cerca de la TIENDA\nPOKéMON es ahora un túnel que\lconecta dos ciudades.\pEs lo mejor. Ahora no cuesta nada ir\na comprar productos DEVON a\lCIUDAD FÉRRICA.$"
	.string ""
	.string ""
	.string ""

VerdanturfTown_Text_TownSign:
	.string "PUEBLO VERDEGAL\p“Las ventosas tierras altas que\nsiempre huelen a hierba fresca.”$"
	.string ""
	.string ""

VerdanturfTown_Text_WandasHouse:
	.string "CASA de CLARA$"

VerdanturfTown_Text_BattleTentSign:
	.string "TIENDA de BATALLA de PUEBLO VERDEGAL\n“¡Disfruta de los mejores combates!”$"
	.string ""

VerdanturfTown_Text_RusturfTunnelSign:
	.string "TÚNEL FERVERGAL\n“Conecta CIUDAD FÉRRICA y VERDEGAL.\pEl proyecto de construcción del\ntúnel ha sido cancelado.”$"
	.string ""
	.string ""
	.string ""

