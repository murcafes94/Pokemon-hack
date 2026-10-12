LilycoveCity_CoveLilyMotel_1F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_1F_EventScript_MotelOwner::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_AquaHideoutBusted::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_GameClear::
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar, MSGBOX_DEFAULT
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

LilycoveCity_CoveLilyMotel_1F_EventScript_BlockingTV::
	lockall
	playse SE_PIN
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer
	waitmovement 0
	applymovement LOCALID_MOTEL_OWNER, LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn
	waitmovement 0
	release
	end

LilycoveCity_CoveLilyMotel_1F_Movement_PlayerPushFromTV:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerPushPlayer:
	walk_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Movement_OwnerReturn:
	face_down
	walk_down
	face_up
	step_end

LilycoveCity_CoveLilyMotel_1F_Text_GuestsDoubledByMascot:
	.string "Qué interesante: han duplicado\nel número de clientes usando\lPOKéMON como reclamo.\pMmmm… Quizás debería escoger\nun POKéMON como mascota del hostal.\pPuede que así consiga que vengan\nmás huéspedes…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_1F_Text_NoGuestsWithTeamAqua:
	.string "Oh, disculpa. Estaba viendo la tele\ny no te he visto llegar.\pEs que desde que llegó el EQUIPO\nAQUA, no vienen turistas, así que\lno esperaba a nadie…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_1F_Text_CantSeeTheTV:
	.string "¡Oye, quita de ahí, que no\neres transparente!$"
	.string ""

LilycoveCity_CoveLilyMotel_1F_Text_MonFoundLostItem:
	.string "¡Increíble! ¿Me estás diciendo que un\nPOKéMON encontró un objeto perdido?\pQué interesante: si tuviéramos un\nPOKéMON tan listo como ése…,\p¡recuperaríamos todo lo que perdieran\nnuestros huéspedes!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_1F_Text_HeardAquaHideoutBusted:
	.string "Oh, disculpa. Estaba viendo la tele\ny no te he visto llegar.\pMe han dicho que alguien ha destrozado\nla GUARIDA del EQUIPO AQUA.\pGracias a eso, la gente ha perdido el\nmiedo y acabo de recibir a un grupo.\pSon todos de la misma empresa…\n¿Cómo era? Ah, sí, GAME algo…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_1F_Text_HouseSittingMonCaughtBurglar:
	.string "¡Increíble! ¿Me estás diciendo que un\nPOKéMON guardián pilló a un ladrón?\pQué interesante: si tuviéramos\nun POKéMON tan fuerte como ése…,\p¡podríamos ofrecer el mejor servicio\nde seguridad a nuestros huéspedes!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_CoveLilyMotel_1F_Text_BetterGetWorkingOnGuestsDinner:
	.string "Oh, disculpa. Estaba viendo la tele\ny no te he visto llegar.\pAh, sí. Acaba de llegar un gran\ngrupo de huéspedes.\pPertenecen a la empresa GAME FREAK,\nasí que deben de crear videojuegos.\p¡Huy, huy, creo que tengo que irme\na prepararles la cena!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

