#include "cc_charm.hpp"
#include "cc_user_info.hpp"
#include "cg_arranged_complete.hpp"
#include "cg_arranged_reject.hpp"
#include "cg_auth.hpp"
#include "cg_card.hpp"
#include "cg_charm.hpp"
#include "cg_essence.hpp"
#include "cg_exit.hpp"
#include "cg_game_item.hpp"
#include "cg_game_state.hpp"
#include "cg_hit.hpp"
#include "cg_hit_essence.hpp"
#include "cg_log.hpp"
#include "cg_map_object.hpp"
#include "cg_mesg.hpp"
#include "cg_motion.hpp"
#include "cg_move.hpp"
#include "cg_move_report.hpp"
#include "cg_player_change.hpp"
#include "cg_pve_area_trigger.hpp"
#include "cg_pve_event_object.hpp"
#include "cg_pve_floor.hpp"
#include "cg_pve_get_item.hpp"
#include "cg_pve_hit_n2p.hpp"
#include "cg_pve_hit_npc.hpp"
#include "cg_pve_hit_npc_to_object.hpp"
#include "cg_pve_hit_object.hpp"
#include "cg_pve_respawn_req.hpp"
#include "cg_pve_round_start.hpp"
#include "cg_pve_start.hpp"
#include "cg_ready.hpp"
#include "cg_respawn.hpp"
#include "cg_room.hpp"
#include "cg_room_info.hpp"
#include "cg_score.hpp"
#include "cg_shoot.hpp"
#include "cg_shoot_report.hpp"
#include "cg_start.hpp"
#include "cg_sync.hpp"
#include "cg_target.hpp"
#include "cg_weapon.hpp"
#include "cs_rtt_request.hpp"
#include "gc_arranged_accept.hpp"
#include "gc_arranged_conn.hpp"
#include "gc_card.hpp"
#include "gc_charm.hpp"
#include "gc_disconnect.hpp"
#include "gc_essence.hpp"
#include "gc_exit.hpp"
#include "gc_game_item.hpp"
#include "gc_game_state.hpp"
#include "gc_hit.hpp"
#include "gc_hit_essence.hpp"
#include "gc_join.hpp"
#include "gc_map_object.hpp"
#include "gc_master_log.hpp"
#include "gc_mesg.hpp"
#include "gc_motion.hpp"
#include "gc_move.hpp"
#include "gc_player_change.hpp"
#include "gc_pve_area_trigger_init.hpp"
#include "gc_pve_destroy_object.hpp"
#include "gc_pve_destroy_parts.hpp"
#include "gc_pve_die_npc.hpp"
#include "gc_pve_door.hpp"
#include "gc_pve_event_object.hpp"
#include "gc_pve_hit_n2n.hpp"
#include "gc_pve_hit_n2p.hpp"
#include "gc_pve_hit_npc.hpp"
#include "gc_pve_hit_npc_to_object.hpp"
#include "gc_pve_hit_object.hpp"
#include "gc_pve_item_init.hpp"
#include "gc_pve_move_nodes_npc.hpp"
#include "gc_pve_move_npc.hpp"
#include "gc_pve_new_round.hpp"
#include "gc_pve_npc_init.hpp"
#include "gc_pve_object_init.hpp"
#include "gc_pve_object_move.hpp"
#include "gc_pve_round_end.hpp"
#include "gc_pve_score_result.hpp"
#include "gc_pve_shoot_n2p.hpp"
#include "gc_pve_special_attack.hpp"
#include "gc_pve_start.hpp"
#include "gc_pve_user_init.hpp"
#include "gc_quest.hpp"
#include "gc_ready.hpp"
#include "gc_respawn.hpp"
#include "gc_room.hpp"
#include "gc_room_info.hpp"
#include "gc_score.hpp"
#include "gc_score_result.hpp"
#include "gc_shoot.hpp"
#include "gc_start.hpp"
#include "gc_sync.hpp"
#include "gc_target.hpp"
#include "gc_weapon.hpp"
#include "gg_reload.hpp"
#include "p_cs_rtt_report.hpp"
#include "p_cs_rtt_response.hpp"


TNL_IMPLEMENT_NETEVENT(CCCharm, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CCUserInfo, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGArrangedComplete, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGArrangedReject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGAuth, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGCard, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGCharm, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGEssence, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGExit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGGameItem, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGGameState, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGHit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGHitEssence, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGLog, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGMapObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGMesg, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGMotion, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGMove, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGMoveReport, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPlayerChange, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEAreaTrigger, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEEventObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEFloor, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEGetItem, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEHitN2P, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEHitNpc, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEHitNpcToObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEHitObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvERespawnReq, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvERoundStart, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGPvEStart, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGReady, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGRespawn, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGRoom, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGRoomInfo, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGScore, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGShoot, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGShootReport, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGStart, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGSync, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGTarget, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CGWeapon, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(CSRttRequest, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCArrangedAccept, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCArrangedConn, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCCard, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCCharm, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCDisconnect, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCEssence, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCExit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCGameItem, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCGameState, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCHit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCHitEssence, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCJoin, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCMapObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCMasterLog, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCMesg, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCMotion, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCMove, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPlayerChange, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEAreaTriggerInit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEDestroyObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEDestroyParts, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEDieNpc, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEDoor, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEEventObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEHitN2N, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEHitN2P, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEHitNpc, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEHitNpcToObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEHitObject, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEItemInit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEMoveNodesNpc, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEMoveNpc, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvENewRound, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvENpcInit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEObjectInit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEObjectMove, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvERoundEnd, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEScoreResult, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEShootN2P, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvESpecialAttack, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEStart, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCPvEUserInit, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCQuest, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCReady, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCRespawn, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCRoom, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCRoomInfo, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCScore, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCScoreResult, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCShoot, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCStart, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCSync, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCTarget, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GCWeapon, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(GGReload, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(P_CSRttReport, NetClassGroupGameMask, 0);
TNL_IMPLEMENT_NETEVENT(P_CSRttResponse, NetClassGroupGameMask, 0);
