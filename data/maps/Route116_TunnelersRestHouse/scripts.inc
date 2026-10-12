Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "El TÚNEL FERVERGAL…\pAl principio teníamos un equipo con el\núltimo grito en maquinaria trabajando\len él y tuvimos que parar.\pResulta que podríamos haber afectado\nnegativamente a los POKéMON\lsalvajes de la zona.\pPor eso ahora nos dedicamos\na tocarnos la barriga…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "Hay un hombre que está cavando\nun TÚNEL a VERDEGAL él solito.\lParece desesperado por terminar.\pDice que, si cava poco a poco, sin usar\nmáquinas, no molestará a los POKéMON\lni causará daños medioambientales…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "Para llegar a VERDEGAL sin usar\nel TÚNEL, tienes que atravesar el mar\lhasta AZULIZA, navegar a CIUDAD\lPORTUAL y luego viajar a MALVALONA…$"
	.string ""
	.string ""
	.string ""

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "¿Te has enterado?\n¡Han terminado el TÚNEL a VERDEGAL!\pA veces creo que, si lo deseas de veras,\ntus sueños se pueden hacer realidad…$"
	.string ""
	.string ""
	.string ""

