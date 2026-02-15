#include <iostream>

// GraphVM tests
void test_basic_arithmetic();
void test_subtraction();
void test_multiplication();
void test_division();
void test_division_by_zero();
void test_comparison();
void test_conditional_jump();
void test_variables();

// ECS tests
void test_create_entity();
void test_destroy_entity();
void test_tick_callback();

// ECS Component tests
void test_add_and_get_component();
void test_has_component();
void test_remove_component();
void test_multiple_components();
void test_destroy_entity_removes_components();
void test_component_update();

// Asset tests
void test_asset_binary_roundtrip();
void test_asset_registry_scan();

// Network tests
void test_net_init();
void test_net_authority();
void test_net_shutdown();

// Network queue tests
void test_net_add_peer();
void test_net_remove_peer();
void test_net_send_receive();
void test_net_broadcast_receive();
void test_net_shutdown_clears_queues();

// World tests
void test_cube_sphere_projection();
void test_cube_sphere_chunk_roundtrip();
void test_cube_sphere_neighbors();
void test_cube_sphere_lod();
void test_voxel_chunk_roundtrip();
void test_voxel_neighbors();

// Terrain mesh tests
void test_terrain_flat_mesh();
void test_terrain_heightmap_mesh();
void test_terrain_normals_computed();
void test_terrain_resolution_one();

// Noise tests
void test_perlin_range();
void test_perlin_deterministic();
void test_perlin_seed_variation();
void test_fbm_octaves();
void test_fbm_deterministic();
void test_perlin_spatial_variation();

// Streaming tests
void test_streamer_request_load();
void test_streamer_set_chunk_data();
void test_streamer_unload_chunk();
void test_streamer_get_loaded_chunks();
void test_streamer_disk_cache();
void test_streamer_duplicate_request();

// Galaxy tests
void test_galaxy_system_count();
void test_galaxy_deterministic();
void test_galaxy_seed_variation();
void test_galaxy_region_filter();
void test_galaxy_unique_ids();
void test_galaxy_star_classes();

// Compiler tests
void test_compile_constants_and_add();
void test_compile_and_execute_full();
void test_compile_multiply();

// Engine tests
void test_engine_init_and_shutdown();
void test_engine_run_loop_ticks();
void test_engine_capabilities();
void test_engine_net_mode_from_config();

// Console tests
void test_console_spawn_entity();
void test_console_ecs_dump();
void test_console_set_tickrate();
void test_console_net_mode();
void test_console_help();
void test_console_unknown_command();

// Project tests
void test_project_load_valid();
void test_project_load_minimal();
void test_project_load_missing_file();
void test_project_invalid_schema();
void test_project_missing_name();
void test_project_missing_name_field();
void test_project_invalid_version();
void test_project_schema_validation();
void test_project_load_full_modules();
void test_project_resolve_module_path();
void test_project_unload();

// Command tests
void test_command_execute();
void test_command_undo();
void test_command_redo();
void test_command_redo_cleared_on_execute();
void test_command_clear();
void test_command_last_executed();
void test_command_multiple_undo_redo();

// WorldGraph tests
void test_worldgraph_add_nodes();
void test_worldgraph_remove_node();
void test_worldgraph_compile_empty();
void test_worldgraph_compile_single_node();
void test_worldgraph_compile_chain();
void test_worldgraph_deterministic();
void test_worldgraph_clamp_node();

// Interaction tests
void test_intent_registry_dispatch();
void test_intent_registry_missing();
void test_intent_registry_has_handler();
void test_pattern_resolver();
void test_pattern_resolver_no_match();
void test_pattern_resolver_case_insensitive();

// Voice Command tests
void test_voice_register_command();
void test_voice_match_command();
void test_voice_no_match();
void test_voice_get_by_context();

// Plugin System tests
void test_plugin_validate_valid();
void test_plugin_validate_no_name();
void test_plugin_validate_nondeterministic();
void test_plugin_validate_incompatible_version();
void test_plugin_registry_register();
void test_plugin_registry_find();
void test_plugin_registry_unregister();
void test_plugin_registry_get_by_type();

// Heightfield tests
void test_heightfield_at();
void test_heightfield_mesh_generation();
void test_heightfield_mesh_lod();

// StrategyGraph tests
void test_strategygraph_add_nodes();
void test_strategygraph_remove_node();
void test_strategygraph_compile_empty();
void test_strategygraph_compile_single_node();
void test_strategygraph_compile_chain();
void test_strategygraph_execute();
void test_strategygraph_deterministic();
void test_strategygraph_objective_score();
void test_strategygraph_read_ai_signal();
void test_strategygraph_emit_action();

// Server Rules tests
void test_server_rules_register();
void test_server_rules_get_value();
void test_server_rules_set_multiplier();
void test_server_rules_clamp_multiplier();
void test_server_rules_missing_rule();
void test_server_rules_hot_reload_flag();
void test_server_rules_clear();

// ConversationGraph tests
void test_conversation_add_nodes();
void test_conversation_remove_node();
void test_conversation_compile_empty();
void test_conversation_dialogue_node();
void test_conversation_chain();
void test_conversation_relationship_delta();
void test_conversation_player_choice();

// AI Signal tests
void test_ai_signal_register();
void test_ai_signal_read_write();
void test_ai_signal_missing();
void test_ai_signal_namespace();
void test_ai_signal_clear();

// AI Memory tests
void test_ai_memory_store_recall();
void test_ai_memory_has();
void test_ai_memory_forget();
void test_ai_memory_decay();
void test_ai_memory_permanent();
void test_ai_memory_clear();

// Relationship Model tests
void test_relationship_set_get();
void test_relationship_default_zero();
void test_relationship_modify();
void test_relationship_has();
void test_relationship_remove();
void test_relationship_clear();

// SoundGraph tests
void test_soundgraph_add_nodes();
void test_soundgraph_remove_node();
void test_soundgraph_compile_empty();
void test_soundgraph_compile_single_node();
void test_soundgraph_compile_chain();
void test_soundgraph_execute();
void test_soundgraph_deterministic();

// TileGraph tests
void test_tilegraph_add_nodes();
void test_tilegraph_remove_node();
void test_tilegraph_compile_empty();
void test_tilegraph_compile_single_node();
void test_tilegraph_compile_chain();
void test_tilegraph_execute();
void test_tilegraph_deterministic();

// CharacterGraph tests
void test_charactergraph_add_nodes();
void test_charactergraph_remove_node();
void test_charactergraph_compile_empty();
void test_charactergraph_compile_single_node();
void test_charactergraph_compile_chain();
void test_charactergraph_execute();
void test_charactergraph_deterministic();

// BehaviorGraph tests
void test_behaviorgraph_add_nodes();
void test_behaviorgraph_remove_node();
void test_behaviorgraph_compile_empty();
void test_behaviorgraph_compile_single_node();
void test_behaviorgraph_compile_chain();
void test_behaviorgraph_execute();
void test_behaviorgraph_deterministic();

// AnimationGraph tests
void test_animationgraph_add_nodes();
void test_animationgraph_remove_node();
void test_animationgraph_compile_empty();
void test_animationgraph_compile_single_node();
void test_animationgraph_compile_chain();
void test_animationgraph_execute();
void test_animationgraph_modifier();
void test_animationgraph_deterministic();

// WeaponGraph tests
void test_weapongraph_add_nodes();
void test_weapongraph_remove_node();
void test_weapongraph_compile_empty();
void test_weapongraph_compile_single_node();
void test_weapongraph_compile_chain();
void test_weapongraph_execute();
void test_weapongraph_wear_degrades_stats();
void test_weapongraph_deterministic();

// UIGraph tests
void test_uigraph_add_nodes();
void test_uigraph_remove_node();
void test_uigraph_compile_empty();
void test_uigraph_compile_single_node();
void test_uigraph_compile_chain();
void test_uigraph_execute();
void test_uigraph_deterministic();

// GameFlowGraph tests
void test_gameflowgraph_add_nodes();
void test_gameflowgraph_remove_node();
void test_gameflowgraph_compile_empty();
void test_gameflowgraph_compile_single_node();
void test_gameflowgraph_compile_chain();
void test_gameflowgraph_execute();
void test_gameflowgraph_deterministic();

// Schema Validator tests
void test_schema_valid();
void test_schema_empty_id();
void test_schema_zero_version();
void test_schema_duplicate_node_id();
void test_schema_empty_node_id();
void test_schema_no_nodes();

// Graph Cache tests
void test_cache_store_and_get();
void test_cache_has();
void test_cache_invalidate();
void test_cache_invalidate_all();
void test_cache_evict_before();
void test_cache_hash_key();

// Graph Serialization tests
void test_json_builder_object();
void test_json_builder_array();
void test_json_reader_parse();
void test_json_reader_array();
void test_json_roundtrip();

// Graph Commands tests
void test_graph_cmd_add_node();
void test_graph_cmd_add_node_undo();
void test_graph_cmd_add_node_redo();
void test_graph_cmd_remove_node();
void test_graph_cmd_remove_node_undo();
void test_graph_cmd_add_edge();
void test_graph_cmd_add_edge_undo();
void test_graph_cmd_remove_edge();
void test_graph_cmd_remove_edge_undo();
void test_graph_cmd_sequence();

// RenderGraph tests
void test_rendergraph_add_nodes();
void test_rendergraph_remove_node();
void test_rendergraph_compile_empty();
void test_rendergraph_compile_single_node();
void test_rendergraph_compile_chain();
void test_rendergraph_execute();
void test_rendergraph_deterministic();

// ShaderGraph tests
void test_shadergraph_add_nodes();
void test_shadergraph_remove_node();
void test_shadergraph_compile_empty();
void test_shadergraph_compile_single_node();
void test_shadergraph_compile_chain();
void test_shadergraph_execute();
void test_shadergraph_lerp_node();
void test_shadergraph_deterministic();

// Node Editor Model tests
void test_node_editor_add_node();
void test_node_editor_remove_node();
void test_node_editor_set_position();
void test_node_editor_add_link();
void test_node_editor_remove_link();
void test_node_editor_link_invalid_pins();
void test_node_editor_selection();
void test_node_editor_canvas();
void test_node_editor_hit_test();
void test_node_editor_clear();
void test_node_editor_get_node_ids();
void test_node_editor_pin_position();

// AI Inspector tests
void test_ai_inspector_create();
void test_ai_inspector_set_sources();
void test_ai_inspector_filter();
void test_ai_inspector_visibility();

// Graph Diff tests
void test_graph_diff_empty();
void test_graph_diff_added_node();
void test_graph_diff_removed_node();
void test_graph_diff_added_edge();
void test_graph_diff_removed_edge();
void test_graph_diff_no_changes();
void test_graph_diff_complex();

// Graph Timeline tests
void test_timeline_empty();
void test_timeline_record_frame();
void test_timeline_seek();
void test_timeline_step();
void test_timeline_seek_to_end();
void test_timeline_diff_to_next();
void test_timeline_diff_from_previous();
void test_timeline_tick_range();
void test_timeline_clear();
void test_timeline_get_frame_at_tick();

// LLM Context Builder tests
void test_llm_context_builder_reset();
void test_llm_context_builder_add_layers();
void test_llm_context_builder_build_prompt();
void test_llm_context_builder_schema_content();
void test_llm_context_builder_empty_prompt();

// LLM Request Types tests
void test_llm_request_type_allow();
void test_llm_request_type_defaults();
void test_llm_request_type_clear();
void test_llm_request_type_unknown_tool();

// LLM Response Validator tests
void test_llm_response_valid_structure();
void test_llm_response_empty();
void test_llm_response_not_json_object();
void test_llm_response_graph_target_valid();
void test_llm_response_graph_target_invalid();
void test_llm_response_safety_pass();
void test_llm_response_safety_fail();
void test_llm_response_full_validate();
void test_llm_response_validator_clear();

// LLM Cache tests
void test_llm_cache_store_and_lookup();
void test_llm_cache_has();
void test_llm_cache_evict_before();
void test_llm_cache_clear();
void test_llm_cache_deterministic_key();
void test_llm_cache_overwrite();

// AI Prompt Debugger tests
void test_ai_prompt_debug_create();
void test_ai_prompt_debug_set_sources();
void test_ai_prompt_debug_layer_count();
void test_ai_prompt_debug_raw_prompt();
void test_ai_prompt_debug_response();
void test_ai_prompt_debug_validate();
void test_ai_prompt_debug_visibility();

// AI Graph Sandbox tests
void test_sandbox_propose();
void test_sandbox_approve();
void test_sandbox_reject();
void test_sandbox_double_approve();
void test_sandbox_get_by_status();
void test_sandbox_get_by_graph();
void test_sandbox_purge_resolved();
void test_sandbox_clear();

// Replay Capture tests
void test_replay_record();
void test_replay_get_by_graph();
void test_replay_get_by_tick();
void test_replay_tick_range();
void test_replay_get_by_tick_range();
void test_replay_deterministic_hash();
void test_replay_clear();
void test_replay_metadata();

// Replay Diff tests
void test_replay_diff_identical();
void test_replay_diff_event_count_mismatch();
void test_replay_diff_snapshot_mismatch();
void test_replay_diff_event_type_mismatch();
void test_replay_diff_empty();
void test_replay_diff_hash_values();

// Determinism Validator tests
void test_determinism_register();
void test_determinism_pass();
void test_determinism_run_all();
void test_determinism_not_found();
void test_determinism_hash_snapshot();
void test_determinism_clear();

// AI Execution Model tests
void test_ai_exec_init();
void test_ai_exec_authority();
void test_ai_exec_submit();
void test_ai_exec_submit_rejected();
void test_ai_exec_results();
void test_ai_exec_receive_result();
void test_ai_exec_shutdown();
void test_ai_exec_clear();

// AI Replication tests
void test_ai_repl_queue_state();
void test_ai_repl_flush_state();
void test_ai_repl_queue_signal();
void test_ai_repl_queue_memory();
void test_ai_repl_apply_state();
void test_ai_repl_apply_signal();
void test_ai_repl_apply_memory();
void test_ai_repl_clear();

// AI Visualization tests
void test_ai_viz_update_entity();
void test_ai_viz_has_entity();
void test_ai_viz_get_active();
void test_ai_viz_stale_detection();
void test_ai_viz_purge_stale();
void test_ai_viz_entity_count();
void test_ai_viz_clear();
void test_ai_viz_missing_entity();

// Plugin Scanner tests
void test_scanner_valid();
void test_scanner_missing_required();
void test_scanner_forbidden_found();
void test_scanner_empty_binary();
void test_scanner_missing_symbols_query();
void test_scanner_found_forbidden_query();
void test_scanner_clear();

// Plugin Permission tests
void test_perm_register();
void test_perm_has_permission();
void test_perm_missing_permission();
void test_perm_validate_manifest();
void test_perm_validate_exceeds();
void test_perm_get_permissions();
void test_perm_clear();

// Mod Manifest tests
void test_mod_parse();
void test_mod_validate_valid();
void test_mod_validate_empty_name();
void test_mod_validate_empty_version();
void test_mod_register();
void test_mod_sorted();
void test_mod_dependencies_met();
void test_mod_dependencies_missing();
void test_mod_clear();

// Mod Overlay tests
void test_overlay_add_resolve();
void test_overlay_highest_wins();
void test_overlay_has_key();
void test_overlay_get_owner();
void test_overlay_get_overlays_for_key();
void test_overlay_key_count();
void test_overlay_clear();

// Mod Signal Policy tests
void test_signal_policy_allowed();
void test_signal_policy_denied_namespace();
void test_signal_policy_denied_core();
void test_signal_policy_unregistered();
void test_signal_policy_core_locked();
void test_signal_policy_get_namespaces();
void test_signal_policy_clear();

// ECS Inspector Panel tests
void test_ecs_inspector_empty_world();
void test_ecs_inspector_entity_list();
void test_ecs_inspector_component_types();
void test_ecs_inspector_select_entity();
void test_ecs_inspector_draw_calls_refresh();

// Net Inspector Panel tests
void test_net_inspector_standalone();
void test_net_inspector_server_mode();
void test_net_inspector_client_mode();
void test_net_inspector_peer_list();
void test_net_inspector_draw_calls_refresh();

int main() {
    std::cout << "=== Atlas Engine Tests ===" << std::endl;

    // GraphVM
    std::cout << "\n--- Graph VM ---" << std::endl;
    test_basic_arithmetic();
    test_subtraction();
    test_multiplication();
    test_division();
    test_division_by_zero();
    test_comparison();
    test_conditional_jump();
    test_variables();

    // ECS
    std::cout << "\n--- ECS ---" << std::endl;
    test_create_entity();
    test_destroy_entity();
    test_tick_callback();

    // ECS Components
    std::cout << "\n--- ECS Components ---" << std::endl;
    test_add_and_get_component();
    test_has_component();
    test_remove_component();
    test_multiple_components();
    test_destroy_entity_removes_components();
    test_component_update();

    // Assets
    std::cout << "\n--- Asset System ---" << std::endl;
    test_asset_binary_roundtrip();
    test_asset_registry_scan();

    // Networking
    std::cout << "\n--- Networking ---" << std::endl;
    test_net_init();
    test_net_authority();
    test_net_shutdown();

    // Network Queue
    std::cout << "\n--- Network Queue ---" << std::endl;
    test_net_add_peer();
    test_net_remove_peer();
    test_net_send_receive();
    test_net_broadcast_receive();
    test_net_shutdown_clears_queues();

    // World
    std::cout << "\n--- World Layout ---" << std::endl;
    test_cube_sphere_projection();
    test_cube_sphere_chunk_roundtrip();
    test_cube_sphere_neighbors();
    test_cube_sphere_lod();
    test_voxel_chunk_roundtrip();
    test_voxel_neighbors();

    // Terrain Mesh
    std::cout << "\n--- Terrain Mesh ---" << std::endl;
    test_terrain_flat_mesh();
    test_terrain_heightmap_mesh();
    test_terrain_normals_computed();
    test_terrain_resolution_one();

    // StrategyGraph
    std::cout << "\n--- Strategy Graph ---" << std::endl;
    test_strategygraph_add_nodes();
    test_strategygraph_remove_node();
    test_strategygraph_compile_empty();
    test_strategygraph_compile_single_node();
    test_strategygraph_compile_chain();
    test_strategygraph_execute();
    test_strategygraph_deterministic();
    test_strategygraph_objective_score();
    test_strategygraph_read_ai_signal();
    test_strategygraph_emit_action();

    // Server Rules
    std::cout << "\n--- Server Rules ---" << std::endl;
    test_server_rules_register();
    test_server_rules_get_value();
    test_server_rules_set_multiplier();
    test_server_rules_clamp_multiplier();
    test_server_rules_missing_rule();
    test_server_rules_hot_reload_flag();
    test_server_rules_clear();

    // ConversationGraph
    std::cout << "\n--- Conversation Graph ---" << std::endl;
    test_conversation_add_nodes();
    test_conversation_remove_node();
    test_conversation_compile_empty();
    test_conversation_dialogue_node();
    test_conversation_chain();
    test_conversation_relationship_delta();
    test_conversation_player_choice();

    // AI Signals
    std::cout << "\n--- AI Signals ---" << std::endl;
    test_ai_signal_register();
    test_ai_signal_read_write();
    test_ai_signal_missing();
    test_ai_signal_namespace();
    test_ai_signal_clear();

    // AI Memory
    std::cout << "\n--- AI Memory ---" << std::endl;
    test_ai_memory_store_recall();
    test_ai_memory_has();
    test_ai_memory_forget();
    test_ai_memory_decay();
    test_ai_memory_permanent();
    test_ai_memory_clear();

    // Relationship Model
    std::cout << "\n--- Relationship Model ---" << std::endl;
    test_relationship_set_get();
    test_relationship_default_zero();
    test_relationship_modify();
    test_relationship_has();
    test_relationship_remove();
    test_relationship_clear();

    // Noise
    std::cout << "\n--- Noise Generator ---" << std::endl;
    test_perlin_range();
    test_perlin_deterministic();
    test_perlin_seed_variation();
    test_fbm_octaves();
    test_fbm_deterministic();
    test_perlin_spatial_variation();

    // Streaming
    std::cout << "\n--- World Streaming ---" << std::endl;
    test_streamer_request_load();
    test_streamer_set_chunk_data();
    test_streamer_unload_chunk();
    test_streamer_get_loaded_chunks();
    test_streamer_disk_cache();
    test_streamer_duplicate_request();

    // Galaxy
    std::cout << "\n--- Galaxy Generator ---" << std::endl;
    test_galaxy_system_count();
    test_galaxy_deterministic();
    test_galaxy_seed_variation();
    test_galaxy_region_filter();
    test_galaxy_unique_ids();
    test_galaxy_star_classes();

    // Compiler
    std::cout << "\n--- Graph Compiler ---" << std::endl;
    test_compile_constants_and_add();
    test_compile_and_execute_full();
    test_compile_multiply();

    // Engine
    std::cout << "\n--- Engine ---" << std::endl;
    test_engine_init_and_shutdown();
    test_engine_run_loop_ticks();
    test_engine_capabilities();
    test_engine_net_mode_from_config();

    // Console
    std::cout << "\n--- Console ---" << std::endl;
    test_console_spawn_entity();
    test_console_ecs_dump();
    test_console_set_tickrate();
    test_console_net_mode();
    test_console_help();
    test_console_unknown_command();

    // Project
    std::cout << "\n--- Project System ---" << std::endl;
    test_project_load_valid();
    test_project_load_minimal();
    test_project_load_missing_file();
    test_project_invalid_schema();
    test_project_missing_name();
    test_project_missing_name_field();
    test_project_invalid_version();
    test_project_schema_validation();
    test_project_load_full_modules();
    test_project_resolve_module_path();
    test_project_unload();

    // Command
    std::cout << "\n--- Command System ---" << std::endl;
    test_command_execute();
    test_command_undo();
    test_command_redo();
    test_command_redo_cleared_on_execute();
    test_command_clear();
    test_command_last_executed();
    test_command_multiple_undo_redo();

    // WorldGraph
    std::cout << "\n--- World Graph ---" << std::endl;
    test_worldgraph_add_nodes();
    test_worldgraph_remove_node();
    test_worldgraph_compile_empty();
    test_worldgraph_compile_single_node();
    test_worldgraph_compile_chain();
    test_worldgraph_deterministic();
    test_worldgraph_clamp_node();

    // Interaction
    std::cout << "\n--- Interaction System ---" << std::endl;
    test_intent_registry_dispatch();
    test_intent_registry_missing();
    test_intent_registry_has_handler();
    test_pattern_resolver();
    test_pattern_resolver_no_match();
    test_pattern_resolver_case_insensitive();

    // Voice Commands
    std::cout << "\n--- Voice Commands ---" << std::endl;
    test_voice_register_command();
    test_voice_match_command();
    test_voice_no_match();
    test_voice_get_by_context();

    // Plugin System
    std::cout << "\n--- Plugin System ---" << std::endl;
    test_plugin_validate_valid();
    test_plugin_validate_no_name();
    test_plugin_validate_nondeterministic();
    test_plugin_validate_incompatible_version();
    test_plugin_registry_register();
    test_plugin_registry_find();
    test_plugin_registry_unregister();
    test_plugin_registry_get_by_type();

    // Heightfield
    std::cout << "\n--- Heightfield Mesher ---" << std::endl;
    test_heightfield_at();
    test_heightfield_mesh_generation();
    test_heightfield_mesh_lod();

    // Sound Graph
    std::cout << "\n--- Sound Graph ---" << std::endl;
    test_soundgraph_add_nodes();
    test_soundgraph_remove_node();
    test_soundgraph_compile_empty();
    test_soundgraph_compile_single_node();
    test_soundgraph_compile_chain();
    test_soundgraph_execute();
    test_soundgraph_deterministic();

    // Tile Graph
    std::cout << "\n--- Tile Graph ---" << std::endl;
    test_tilegraph_add_nodes();
    test_tilegraph_remove_node();
    test_tilegraph_compile_empty();
    test_tilegraph_compile_single_node();
    test_tilegraph_compile_chain();
    test_tilegraph_execute();
    test_tilegraph_deterministic();

    // Character Graph
    std::cout << "\n--- Character Graph ---" << std::endl;
    test_charactergraph_add_nodes();
    test_charactergraph_remove_node();
    test_charactergraph_compile_empty();
    test_charactergraph_compile_single_node();
    test_charactergraph_compile_chain();
    test_charactergraph_execute();
    test_charactergraph_deterministic();

    // Behavior Graph
    std::cout << "\n--- Behavior Graph ---" << std::endl;
    test_behaviorgraph_add_nodes();
    test_behaviorgraph_remove_node();
    test_behaviorgraph_compile_empty();
    test_behaviorgraph_compile_single_node();
    test_behaviorgraph_compile_chain();
    test_behaviorgraph_execute();
    test_behaviorgraph_deterministic();

    // Animation Graph
    std::cout << "\n--- Animation Graph ---" << std::endl;
    test_animationgraph_add_nodes();
    test_animationgraph_remove_node();
    test_animationgraph_compile_empty();
    test_animationgraph_compile_single_node();
    test_animationgraph_compile_chain();
    test_animationgraph_execute();
    test_animationgraph_modifier();
    test_animationgraph_deterministic();

    // Weapon Graph
    std::cout << "\n--- Weapon Graph ---" << std::endl;
    test_weapongraph_add_nodes();
    test_weapongraph_remove_node();
    test_weapongraph_compile_empty();
    test_weapongraph_compile_single_node();
    test_weapongraph_compile_chain();
    test_weapongraph_execute();
    test_weapongraph_wear_degrades_stats();
    test_weapongraph_deterministic();

    // UI Graph
    std::cout << "\n--- UI Graph ---" << std::endl;
    test_uigraph_add_nodes();
    test_uigraph_remove_node();
    test_uigraph_compile_empty();
    test_uigraph_compile_single_node();
    test_uigraph_compile_chain();
    test_uigraph_execute();
    test_uigraph_deterministic();

    // Game Flow Graph
    std::cout << "\n--- Game Flow Graph ---" << std::endl;
    test_gameflowgraph_add_nodes();
    test_gameflowgraph_remove_node();
    test_gameflowgraph_compile_empty();
    test_gameflowgraph_compile_single_node();
    test_gameflowgraph_compile_chain();
    test_gameflowgraph_execute();
    test_gameflowgraph_deterministic();

    // Schema Validator
    std::cout << "\n--- Schema Validator ---" << std::endl;
    test_schema_valid();
    test_schema_empty_id();
    test_schema_zero_version();
    test_schema_duplicate_node_id();
    test_schema_empty_node_id();
    test_schema_no_nodes();

    // Graph Cache
    std::cout << "\n--- Graph Cache ---" << std::endl;
    test_cache_store_and_get();
    test_cache_has();
    test_cache_invalidate();
    test_cache_invalidate_all();
    test_cache_evict_before();
    test_cache_hash_key();

    // Graph Serialization
    std::cout << "\n--- Graph Serialization ---" << std::endl;
    test_json_builder_object();
    test_json_builder_array();
    test_json_reader_parse();
    test_json_reader_array();
    test_json_roundtrip();

    // Graph Commands
    std::cout << "\n--- Graph Commands ---" << std::endl;
    test_graph_cmd_add_node();
    test_graph_cmd_add_node_undo();
    test_graph_cmd_add_node_redo();
    test_graph_cmd_remove_node();
    test_graph_cmd_remove_node_undo();
    test_graph_cmd_add_edge();
    test_graph_cmd_add_edge_undo();
    test_graph_cmd_remove_edge();
    test_graph_cmd_remove_edge_undo();
    test_graph_cmd_sequence();

    // Render Graph
    std::cout << "\n--- Render Graph ---" << std::endl;
    test_rendergraph_add_nodes();
    test_rendergraph_remove_node();
    test_rendergraph_compile_empty();
    test_rendergraph_compile_single_node();
    test_rendergraph_compile_chain();
    test_rendergraph_execute();
    test_rendergraph_deterministic();

    // Shader Graph
    std::cout << "\n--- Shader Graph ---" << std::endl;
    test_shadergraph_add_nodes();
    test_shadergraph_remove_node();
    test_shadergraph_compile_empty();
    test_shadergraph_compile_single_node();
    test_shadergraph_compile_chain();
    test_shadergraph_execute();
    test_shadergraph_lerp_node();
    test_shadergraph_deterministic();

    // Node Editor Model
    std::cout << "\n--- Node Editor Model ---" << std::endl;
    test_node_editor_add_node();
    test_node_editor_remove_node();
    test_node_editor_set_position();
    test_node_editor_add_link();
    test_node_editor_remove_link();
    test_node_editor_link_invalid_pins();
    test_node_editor_selection();
    test_node_editor_canvas();
    test_node_editor_hit_test();
    test_node_editor_clear();
    test_node_editor_get_node_ids();
    test_node_editor_pin_position();

    // AI Inspector
    std::cout << "\n--- AI Inspector ---" << std::endl;
    test_ai_inspector_create();
    test_ai_inspector_set_sources();
    test_ai_inspector_filter();
    test_ai_inspector_visibility();

    // Graph Diff
    std::cout << "\n--- Graph Diff ---" << std::endl;
    test_graph_diff_empty();
    test_graph_diff_added_node();
    test_graph_diff_removed_node();
    test_graph_diff_added_edge();
    test_graph_diff_removed_edge();
    test_graph_diff_no_changes();
    test_graph_diff_complex();

    // Graph Timeline
    std::cout << "\n--- Graph Timeline ---" << std::endl;
    test_timeline_empty();
    test_timeline_record_frame();
    test_timeline_seek();
    test_timeline_step();
    test_timeline_seek_to_end();
    test_timeline_diff_to_next();
    test_timeline_diff_from_previous();
    test_timeline_tick_range();
    test_timeline_clear();
    test_timeline_get_frame_at_tick();

    // LLM Context Builder
    std::cout << "\n--- LLM Context Builder ---" << std::endl;
    test_llm_context_builder_reset();
    test_llm_context_builder_add_layers();
    test_llm_context_builder_build_prompt();
    test_llm_context_builder_schema_content();
    test_llm_context_builder_empty_prompt();

    // LLM Request Types
    std::cout << "\n--- LLM Request Types ---" << std::endl;
    test_llm_request_type_allow();
    test_llm_request_type_defaults();
    test_llm_request_type_clear();
    test_llm_request_type_unknown_tool();

    // LLM Response Validator
    std::cout << "\n--- LLM Response Validator ---" << std::endl;
    test_llm_response_valid_structure();
    test_llm_response_empty();
    test_llm_response_not_json_object();
    test_llm_response_graph_target_valid();
    test_llm_response_graph_target_invalid();
    test_llm_response_safety_pass();
    test_llm_response_safety_fail();
    test_llm_response_full_validate();
    test_llm_response_validator_clear();

    // LLM Cache
    std::cout << "\n--- LLM Cache ---" << std::endl;
    test_llm_cache_store_and_lookup();
    test_llm_cache_has();
    test_llm_cache_evict_before();
    test_llm_cache_clear();
    test_llm_cache_deterministic_key();
    test_llm_cache_overwrite();

    // AI Prompt Debugger
    std::cout << "\n--- AI Prompt Debugger ---" << std::endl;
    test_ai_prompt_debug_create();
    test_ai_prompt_debug_set_sources();
    test_ai_prompt_debug_layer_count();
    test_ai_prompt_debug_raw_prompt();
    test_ai_prompt_debug_response();
    test_ai_prompt_debug_validate();
    test_ai_prompt_debug_visibility();

    // AI Graph Sandbox
    std::cout << "\n--- AI Graph Sandbox ---" << std::endl;
    test_sandbox_propose();
    test_sandbox_approve();
    test_sandbox_reject();
    test_sandbox_double_approve();
    test_sandbox_get_by_status();
    test_sandbox_get_by_graph();
    test_sandbox_purge_resolved();
    test_sandbox_clear();

    // Replay Capture
    std::cout << "\n--- Replay Capture ---" << std::endl;
    test_replay_record();
    test_replay_get_by_graph();
    test_replay_get_by_tick();
    test_replay_tick_range();
    test_replay_get_by_tick_range();
    test_replay_deterministic_hash();
    test_replay_clear();
    test_replay_metadata();

    // Replay Diff
    std::cout << "\n--- Replay Diff ---" << std::endl;
    test_replay_diff_identical();
    test_replay_diff_event_count_mismatch();
    test_replay_diff_snapshot_mismatch();
    test_replay_diff_event_type_mismatch();
    test_replay_diff_empty();
    test_replay_diff_hash_values();

    // Determinism Validator
    std::cout << "\n--- Determinism Validator ---" << std::endl;
    test_determinism_register();
    test_determinism_pass();
    test_determinism_run_all();
    test_determinism_not_found();
    test_determinism_hash_snapshot();
    test_determinism_clear();

    // AI Execution Model
    std::cout << "\n--- AI Execution Model ---" << std::endl;
    test_ai_exec_init();
    test_ai_exec_authority();
    test_ai_exec_submit();
    test_ai_exec_submit_rejected();
    test_ai_exec_results();
    test_ai_exec_receive_result();
    test_ai_exec_shutdown();
    test_ai_exec_clear();

    // AI Replication
    std::cout << "\n--- AI Replication ---" << std::endl;
    test_ai_repl_queue_state();
    test_ai_repl_flush_state();
    test_ai_repl_queue_signal();
    test_ai_repl_queue_memory();
    test_ai_repl_apply_state();
    test_ai_repl_apply_signal();
    test_ai_repl_apply_memory();
    test_ai_repl_clear();

    // AI Visualization
    std::cout << "\n--- AI Visualization ---" << std::endl;
    test_ai_viz_update_entity();
    test_ai_viz_has_entity();
    test_ai_viz_get_active();
    test_ai_viz_stale_detection();
    test_ai_viz_purge_stale();
    test_ai_viz_entity_count();
    test_ai_viz_clear();
    test_ai_viz_missing_entity();

    // Plugin Scanner
    std::cout << "\n--- Plugin Scanner ---" << std::endl;
    test_scanner_valid();
    test_scanner_missing_required();
    test_scanner_forbidden_found();
    test_scanner_empty_binary();
    test_scanner_missing_symbols_query();
    test_scanner_found_forbidden_query();
    test_scanner_clear();

    // Plugin Permission
    std::cout << "\n--- Plugin Permission ---" << std::endl;
    test_perm_register();
    test_perm_has_permission();
    test_perm_missing_permission();
    test_perm_validate_manifest();
    test_perm_validate_exceeds();
    test_perm_get_permissions();
    test_perm_clear();

    // Mod Manifest
    std::cout << "\n--- Mod Manifest ---" << std::endl;
    test_mod_parse();
    test_mod_validate_valid();
    test_mod_validate_empty_name();
    test_mod_validate_empty_version();
    test_mod_register();
    test_mod_sorted();
    test_mod_dependencies_met();
    test_mod_dependencies_missing();
    test_mod_clear();

    // Mod Overlay
    std::cout << "\n--- Mod Overlay ---" << std::endl;
    test_overlay_add_resolve();
    test_overlay_highest_wins();
    test_overlay_has_key();
    test_overlay_get_owner();
    test_overlay_get_overlays_for_key();
    test_overlay_key_count();
    test_overlay_clear();

    // Mod Signal Policy
    std::cout << "\n--- Mod Signal Policy ---" << std::endl;
    test_signal_policy_allowed();
    test_signal_policy_denied_namespace();
    test_signal_policy_denied_core();
    test_signal_policy_unregistered();
    test_signal_policy_core_locked();
    test_signal_policy_get_namespaces();
    test_signal_policy_clear();

    // ECS Inspector Panel
    std::cout << "\n--- ECS Inspector Panel ---" << std::endl;
    test_ecs_inspector_empty_world();
    test_ecs_inspector_entity_list();
    test_ecs_inspector_component_types();
    test_ecs_inspector_select_entity();
    test_ecs_inspector_draw_calls_refresh();

    // Net Inspector Panel
    std::cout << "\n--- Net Inspector Panel ---" << std::endl;
    test_net_inspector_standalone();
    test_net_inspector_server_mode();
    test_net_inspector_client_mode();
    test_net_inspector_peer_list();
    test_net_inspector_draw_calls_refresh();

    std::cout << "\n=== All tests passed! ===" << std::endl;
    return 0;
}
