#include "../editor/panels/ProjectPickerPanel.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>

using namespace atlas::editor;

void test_project_picker_create() {
    ProjectPickerPanel panel;
    assert(std::string(panel.Name()) == "Project Picker");
    assert(!panel.HasProjectSelected());
    assert(panel.SelectedProjectPath().empty());
    assert(panel.RecentProjects().empty());
    std::cout << "[PASS] test_project_picker_create" << std::endl;
}

void test_project_picker_add_recent() {
    ProjectPickerPanel panel;
    panel.AddRecentProject("/path/to/project1.atlas");
    panel.AddRecentProject("/path/to/project2.atlas");
    assert(panel.RecentProjects().size() == 2);
    assert(panel.RecentProjects()[0] == "/path/to/project1.atlas");
    assert(panel.RecentProjects()[1] == "/path/to/project2.atlas");
    std::cout << "[PASS] test_project_picker_add_recent" << std::endl;
}

void test_project_picker_no_duplicate_recent() {
    ProjectPickerPanel panel;
    panel.AddRecentProject("/path/to/project.atlas");
    panel.AddRecentProject("/path/to/project.atlas");
    assert(panel.RecentProjects().size() == 1);
    std::cout << "[PASS] test_project_picker_no_duplicate_recent" << std::endl;
}

void test_project_picker_open_missing_file() {
    ProjectPickerPanel panel;
    assert(!panel.OpenProject("/nonexistent/path/missing.atlas"));
    assert(!panel.HasProjectSelected());
    std::cout << "[PASS] test_project_picker_open_missing_file" << std::endl;
}

void test_project_picker_visibility() {
    ProjectPickerPanel panel;
    assert(panel.IsVisible());
    panel.SetVisible(false);
    assert(!panel.IsVisible());
    std::cout << "[PASS] test_project_picker_visibility" << std::endl;
}
