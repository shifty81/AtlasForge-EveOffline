add_executable(AtlasTests
    main.cpp
    test_graphvm.cpp
    test_ecs.cpp
    test_components.cpp
    test_asset.cpp
    test_net.cpp
    test_net_queue.cpp
    test_world.cpp
    test_compiler.cpp
    test_engine.cpp
    test_console.cpp
    test_terrain.cpp
    test_noise.cpp
    test_streaming.cpp
    test_galaxy.cpp
    test_project.cpp
    test_command.cpp
    test_worldgraph.cpp
    test_interaction.cpp
    test_voice.cpp
    test_plugin.cpp
    test_heightfield.cpp
    test_strategygraph.cpp
    test_server_rules.cpp
    test_conversation.cpp
    test_ai_signals.cpp
    test_ai_memory.cpp
    test_relationship.cpp
    test_tilegraph.cpp
    test_soundgraph.cpp
    test_behaviorgraph.cpp
    test_charactergraph.cpp
    test_graph_serializer.cpp
    test_animationgraph.cpp
    test_weapongraph.cpp
    test_uigraph.cpp
    test_gameflowgraph.cpp
    test_schema_validator.cpp
    test_graph_cache.cpp
    test_graph_commands.cpp
    test_rendergraph.cpp
    test_shadergraph.cpp
    ${CMAKE_SOURCE_DIR}/editor/panels/ConsolePanel.cpp
)

target_link_libraries(AtlasTests AtlasEngine)
target_include_directories(AtlasTests PRIVATE ${CMAKE_SOURCE_DIR}/editor)

add_test(NAME AtlasTests COMMAND AtlasTests)
