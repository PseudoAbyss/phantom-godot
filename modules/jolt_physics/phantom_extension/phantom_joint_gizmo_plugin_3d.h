#pragma once

#include "core/templates/hash_set.h"
#include "core/variant/array.h"
#if defined(TOOLS_ENABLED)

#include "editor/editor_interface.h"
#include "editor/scene/3d/node_3d_editor_gizmos.h"
#include "scene/3d/node_3d.h"
#include "scene/3d/physics/physics_body_3d.h"

class PhantomJointGizmoPlugin3D final : public EditorNode3DGizmoPlugin {
	GDCLASS(PhantomJointGizmoPlugin3D, EditorNode3DGizmoPlugin)

protected:
	static void _bind_methods() {}

public:
	PhantomJointGizmoPlugin3D() = default;

	explicit PhantomJointGizmoPlugin3D(EditorInterface *p_editor_interface);

	bool has_gizmo(Node3D *p_spatial) override;

	Ref<EditorNode3DGizmo> create_gizmo(Node3D *p_spatial) override;

	String get_gizmo_name() const override;

	void redraw(EditorNode3DGizmo *p_gizmo) override;

private:
	void _create_materials();

	void _create_redraw_timer(const Ref<EditorNode3DGizmo> &p_gizmo);

	void _redraw_gizmos();

	mutable HashSet<Ref<EditorNode3DGizmo> > gizmos;

	EditorInterface *editor_interface = nullptr;

	bool initialized = false;
};

#endif // GDJ_CONFIG_EDITOR
