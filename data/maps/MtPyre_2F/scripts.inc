MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
	.string "Cómo recuerdo a mi querido SKITTY…\nEs que se me saltan las lágrimas…$"
	.string ""

MtPyre_2F_Text_TumbledFromFloorAbove:
	.string "Huy, huy… Este sitio está más\nagujereado que un queso gruyer.\pNo me di cuenta antes y me caí desde\nel piso de arriba.$"
	.string ""
	.string ""
	.string ""

MtPyre_2F_Text_MarkIntro:
	.string "¡Eh! ¿Buscas POKéMON?\n¡Me has estado siguiendo!\l¡Eso no se hace!$"
	.string ""

MtPyre_2F_Text_MarkDefeat:
	.string "¡Vale, vale, lo he entendido!\n¡No me estabas siguiendo, perdón!$"
	.string ""

MtPyre_2F_Text_MarkPostBattle:
	.string "Aquí no hay ni un alma, así que pensé\nque encontraría POKéMON raros…$"
	.string ""

MtPyre_2F_Text_LukeIntro:
	.string "LEO: Mi chica me ha lanzado un reto.\pJe, je, je… Tengo que demostrarle\nlo fuerte que soy derrotándote.\p¡Esto está hecho! La voy a dejar\nimpresionada.$"
	.string ""
	.string ""
	.string ""
	.string ""

MtPyre_2F_Text_LukeDefeat:
	.string "LEO: Ejem, ejem…$"

MtPyre_2F_Text_LukePostBattle:
	.string "LEO: Vale, he perdido, pero da igual.\nTengo muchas otras cualidades…\l¡Y pronto seré más fuerte que tú!$"
	.string ""
	.string ""

MtPyre_2F_Text_LukeNotEnoughMons:
	.string "LEO: Si quieres enfrentarte a mí,\ntrae más POKéMON.\p¡Si no lo haces, no podré fardar\nun poco delante de mi chica!$"
	.string ""
	.string ""
	.string ""

MtPyre_2F_Text_DezIntro:
	.string "DULCE: Le he lanzado un desafío.\pQuizás no debería ponerle a prueba,\npero me gusta verle en acción.\pEs que ni me preocupo, ¡mi chico\nse encarga de ti en un santiamén!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

MtPyre_2F_Text_DezDefeat:
	.string "DULCE: Pues qué decepción…$"

MtPyre_2F_Text_DezPostBattle:
	.string "DULCE: Qué más da ganar o perder…\nLo importante es quererse mucho.$"
	.string ""

MtPyre_2F_Text_DezNotEnoughMons:
	.string "DULCE: Si quieres desafiarnos, tendrás\nque traer al menos dos POKéMON.\pCon lo fuerte que es mi chico,\nun POKéMON no basta.$"
	.string ""
	.string ""
	.string ""

MtPyre_2F_Text_LeahIntro:
	.string "Es la primera vez que te veo…\n¡Vete antes de que lo lamentes!$"
	.string ""

MtPyre_2F_Text_LeahDefeat:
	.string "Mmmm…\nResistes lo que te echen.$"
	.string ""

MtPyre_2F_Text_LeahPostBattle:
	.string "En mi familia abundan los ENTRENADORES\ndesde tiempos ancestrales…\pProteger esta montaña es mi deber…$"
	.string ""
	.string ""
	.string ""

MtPyre_2F_Text_ZanderIntro:
	.string "¡Kiaaaaa!\n¡Menudo susto me has dado!$"
	.string ""

MtPyre_2F_Text_ZanderDefeat:
	.string "¡Nooooo!\n¡Los nervios han podido conmigo!$"
	.string ""

MtPyre_2F_Text_ZanderPostBattle:
	.string "Me echo a temblar cada vez que\nveo algo moviéndose…\pNo debería entrenarme en este lugar…$"
	.string ""
	.string ""

