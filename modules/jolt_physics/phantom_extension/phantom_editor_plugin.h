#pragma once

#include "core/object/object.h"

#if defined(TOOLS_ENABLED)

#include "editor/gui/editor_file_dialog.h"
#include "editor/plugins/editor_plugin.h"
#include "phantom_joint_gizmo_plugin_3d.h"

class PhantomEditorPlugin final : public EditorPlugin {
	GDCLASS(PhantomEditorPlugin, EditorPlugin)

private:
	static void _bind_methods() {}

protected:
	void _notification(int p_notification);

private:
	enum MenuOption {
		MENU_OPTION_DUMP_DEBUG_SNAPSHOTS
	};

	void _tool_menu_pressed(int32_t p_index);

	void _snapshots_dir_selected(const String &p_dir);

	void _dump_debug_snapshots();

	Ref<PhantomJointGizmoPlugin3D> joint_gizmo_plugin;

	EditorFileDialog *debug_snapshots_dialog = nullptr;
};

#endif
