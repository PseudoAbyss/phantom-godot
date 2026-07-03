#include "phantom_joint_gizmo_plugin_3d.h"

#if defined(TOOLS_ENABLED)

#include "phantom_cone_twist_joint_3d.h"
#include "phantom_generic_6dof_joint.h"
#include "phantom_hinge_joint_3d.h"
#include "phantom_pin_joint_3d.h"
#include "phantom_slider_joint_3d.h"

#include "core/math/math_defs.h"
#include "core/object/callable_mp.h"
#include "editor/editor_node.h"
#include "editor/scene/3d/node_3d_editor_gizmos.h"
#include "editor/settings/editor_settings.h"
#include "scene/main/timer.h"

namespace {

constexpr char MATERIAL_NAME[] = "joint";
constexpr char SETTING_NAME_COLOR[] = "editors/3d_gizmos/gizmo_colors/joint";

constexpr float GIZMO_RADIUS = 0.25f;

Vector3 to_3d(Vector3::Axis p_axis, float p_x, float p_y, float p_d = 0.0f) {
	switch (p_axis) {
		case Vector3::AXIS_X: {
			return { p_d, p_y, p_x };
		}
		case Vector3::AXIS_Y: {
			return { p_x, p_d, p_y };
		}
		case Vector3::AXIS_Z:
		default: {
			return { p_x, p_y, p_d };
		}
	}
}

void draw_linear_limits(
		Vector3::Axis p_axis,
		bool p_limit_enabled,
		float p_limit_upper,
		float p_limit_lower,
		PackedVector3Array &p_points) {
	auto draw_line = [&](float p_d1, float p_d2) {
		p_points.push_back(to_3d(p_axis, 0, 0, p_d1));
		p_points.push_back(to_3d(p_axis, 0, 0, p_d2));
	};

	auto draw_square = [&](float p_d) {
		p_points.push_back(to_3d(p_axis, -GIZMO_RADIUS, GIZMO_RADIUS, p_d));
		p_points.push_back(to_3d(p_axis, GIZMO_RADIUS, GIZMO_RADIUS, p_d));

		p_points.push_back(to_3d(p_axis, GIZMO_RADIUS, GIZMO_RADIUS, p_d));
		p_points.push_back(to_3d(p_axis, GIZMO_RADIUS, -GIZMO_RADIUS, p_d));

		p_points.push_back(to_3d(p_axis, GIZMO_RADIUS, -GIZMO_RADIUS, p_d));
		p_points.push_back(to_3d(p_axis, -GIZMO_RADIUS, -GIZMO_RADIUS, p_d));

		p_points.push_back(to_3d(p_axis, -GIZMO_RADIUS, -GIZMO_RADIUS, p_d));
		p_points.push_back(to_3d(p_axis, -GIZMO_RADIUS, GIZMO_RADIUS, p_d));
	};

	if (p_limit_enabled && p_limit_upper >= p_limit_lower) {
		draw_line(p_limit_lower, p_limit_upper);
		draw_square(p_limit_lower);
		draw_square(p_limit_upper);
	} else {
		draw_line(GIZMO_RADIUS, -GIZMO_RADIUS);
	}
}

void draw_angular_limits(
		Vector3::Axis p_axis,
		bool p_limit_enabled,
		float p_limit_upper,
		float p_limit_lower,
		PackedVector3Array &p_points) {
	constexpr int32_t line_count = 32;

	const bool limit_valid = p_limit_enabled && p_limit_upper >= p_limit_lower;
	const float limit_span = limit_valid ? p_limit_upper - p_limit_lower : Math::TAU;
	const bool limit_bounded = limit_valid && limit_span < (Math::TAU - 0.0001f);
	const float angle_step = limit_span / line_count;

	auto calculate_point = [&](int32_t p_index) {
		const float angle = p_limit_lower + angle_step * (float)p_index;

		const float x = GIZMO_RADIUS * Math::cos(angle);
		const float y = GIZMO_RADIUS * Math::sin(angle);

		return to_3d(p_axis, x, y);
	};

	const Vector3 start = limit_bounded ? Vector3() : calculate_point(0);

	p_points.push_back(start);

	for (int32_t i = 0; i < line_count + 1; ++i) {
		const Vector3 point = calculate_point(i);

		p_points.push_back(point);
		p_points.push_back(point);
	}

	p_points.push_back(start);
}

void draw_pin_joint([[maybe_unused]] const PhantomPinJoint3D &p_joint, PackedVector3Array &p_points) {
	draw_angular_limits(Vector3::AXIS_X, false, Math::PI, -Math::PI, p_points);
	draw_angular_limits(Vector3::AXIS_Y, false, Math::PI, -Math::PI, p_points);
	draw_angular_limits(Vector3::AXIS_Z, false, Math::PI, -Math::PI, p_points);
}

void draw_hinge_joint(const PhantomHingeJoint3D &p_joint, PackedVector3Array &p_points) {
	const bool limit_enabled = p_joint.get_limit_enabled();
	const auto limit_upper = (float)p_joint.get_limit_upper();
	const auto limit_lower = (float)p_joint.get_limit_lower();

	if (!limit_enabled || limit_upper != limit_lower) {
		draw_angular_limits(Vector3::AXIS_Z, limit_enabled, limit_upper, limit_lower, p_points);
	}
}

void draw_slider_joint(const PhantomSliderJoint3D &p_joint, PackedVector3Array &p_points) {
	const bool limit_enabled = p_joint.get_limit_enabled();
	const auto limit_upper = (float)p_joint.get_limit_upper();
	const auto limit_lower = (float)p_joint.get_limit_lower();

	if (!limit_enabled || limit_upper != limit_lower) {
		draw_linear_limits(Vector3::AXIS_X, limit_enabled, limit_upper, limit_lower, p_points);
	}
}

void draw_cone_twist_joint(const PhantomConeTwistJoint3D &p_joint, PackedVector3Array &p_points) {
	const bool swing_limit_enabled = p_joint.get_swing_limit_enabled();
	const auto swing_limit_span = (float)p_joint.get_swing_limit_span();

	if (!swing_limit_enabled || swing_limit_span != 0.0f) {
		draw_angular_limits(
				Vector3::AXIS_Y,
				swing_limit_enabled,
				swing_limit_span,
				-swing_limit_span,
				p_points);

		draw_angular_limits(
				Vector3::AXIS_Z,
				swing_limit_enabled,
				swing_limit_span,
				-swing_limit_span,
				p_points);
	}

	const bool twist_limit_enabled = p_joint.get_twist_limit_enabled();
	const auto twist_limit_span = (float)p_joint.get_twist_limit_span();

	if (!twist_limit_enabled || twist_limit_span != 0.0f) {
		draw_angular_limits(
				Vector3::AXIS_X,
				twist_limit_enabled,
				twist_limit_span,
				-twist_limit_span,
				p_points);
	}
}

void draw_g6dof_joint(const PhantomGeneric6DOFJoint3D &p_joint, PackedVector3Array &p_points) {
	const bool linear_limit_x_enabled = p_joint.get_linear_limit_x_enabled();
	const auto linear_limit_x_upper = (float)p_joint.get_linear_limit_x_upper();
	const auto linear_limit_x_lower = (float)p_joint.get_linear_limit_x_lower();

	if (!linear_limit_x_enabled || linear_limit_x_upper != linear_limit_x_lower) {
		draw_linear_limits(
				Vector3::AXIS_X,
				linear_limit_x_enabled,
				linear_limit_x_upper,
				linear_limit_x_lower,
				p_points);
	}

	const bool linear_limit_y_enabled = p_joint.get_linear_limit_y_enabled();
	const auto linear_limit_y_upper = (float)p_joint.get_linear_limit_y_upper();
	const auto linear_limit_y_lower = (float)p_joint.get_linear_limit_y_lower();

	if (!linear_limit_y_enabled || linear_limit_y_upper != linear_limit_y_lower) {
		draw_linear_limits(
				Vector3::AXIS_Y,
				linear_limit_y_enabled,
				linear_limit_y_upper,
				linear_limit_y_lower,
				p_points);
	}

	const bool linear_limit_z_enabled = p_joint.get_linear_limit_z_enabled();
	const auto linear_limit_z_upper = (float)p_joint.get_linear_limit_z_upper();
	const auto linear_limit_z_lower = (float)p_joint.get_linear_limit_z_lower();

	if (!linear_limit_z_enabled || linear_limit_z_upper != linear_limit_z_lower) {
		draw_linear_limits(
				Vector3::AXIS_Z,
				linear_limit_z_enabled,
				linear_limit_z_upper,
				linear_limit_z_lower,
				p_points);
	}

	const bool angular_limit_x_enabled = p_joint.get_angular_limit_x_enabled();
	const auto angular_limit_x_upper = (float)p_joint.get_angular_limit_x_upper();
	const auto angular_limit_x_lower = (float)p_joint.get_angular_limit_x_lower();

	if (!angular_limit_x_enabled || angular_limit_x_upper != angular_limit_x_lower) {
		draw_angular_limits(
				Vector3::AXIS_X,
				angular_limit_x_enabled,
				angular_limit_x_upper,
				angular_limit_x_lower,
				p_points);
	}

	const bool angular_limit_y_enabled = p_joint.get_angular_limit_y_enabled();
	const auto angular_limit_y_upper = (float)p_joint.get_angular_limit_y_upper();
	const auto angular_limit_y_lower = (float)p_joint.get_angular_limit_y_lower();

	if (!angular_limit_y_enabled || angular_limit_y_upper != angular_limit_y_lower) {
		draw_angular_limits(
				Vector3::AXIS_Y,
				angular_limit_y_enabled,
				angular_limit_y_upper,
				angular_limit_y_lower,
				p_points);
	}

	const bool angular_limit_z_enabled = p_joint.get_angular_limit_z_enabled();
	const auto angular_limit_z_upper = (float)p_joint.get_angular_limit_z_upper();
	const auto angular_limit_z_lower = (float)p_joint.get_angular_limit_z_lower();

	if (!angular_limit_z_enabled || angular_limit_z_upper != angular_limit_z_lower) {
		draw_angular_limits(
				Vector3::AXIS_Z,
				angular_limit_z_enabled,
				angular_limit_z_upper,
				angular_limit_z_lower,
				p_points);
	}
}

} // namespace

PhantomJointGizmoPlugin3D::PhantomJointGizmoPlugin3D(EditorInterface *p_editor_interface) :
		editor_interface(p_editor_interface) {}

bool PhantomJointGizmoPlugin3D::has_gizmo(Node3D *p_node) {
	return Object::cast_to<PhantomJoint3D>(p_node) != nullptr;
}

Ref<EditorNode3DGizmo> PhantomJointGizmoPlugin3D::create_gizmo(Node3D *p_spatial) {
	Ref<EditorNode3DGizmo> gizmo;

	if (has_gizmo(p_spatial)) {
		gizmo = memnew(EditorNode3DGizmo);
		gizmos.insert(gizmo);
	}

	return gizmo;
}

String PhantomJointGizmoPlugin3D::get_gizmo_name() const {
	return "PhantomJoint3D";
}

void PhantomJointGizmoPlugin3D::redraw(EditorNode3DGizmo *p_gizmo) {
	if (unlikely(!initialized)) {
		_create_materials();
		_create_redraw_timer(p_gizmo);

		initialized = true;
	}

	p_gizmo->clear();

	auto *joint = Object::cast_to<PhantomJoint3D>(p_gizmo->get_node_3d());
	ERR_FAIL_NULL(joint);

	PackedVector3Array points;

	if (auto *pin = Object::cast_to<PhantomPinJoint3D>(joint)) {
		draw_pin_joint(*pin, points);
	} else if (auto *hinge = Object::cast_to<PhantomHingeJoint3D>(joint)) {
		draw_hinge_joint(*hinge, points);
	} else if (auto *slider = Object::cast_to<PhantomSliderJoint3D>(joint)) {
		draw_slider_joint(*slider, points);
	} else if (auto *cone_twist = Object::cast_to<PhantomConeTwistJoint3D>(joint)) {
		draw_cone_twist_joint(*cone_twist, points);
	} else if (auto *g6dof = Object::cast_to<PhantomGeneric6DOFJoint3D>(joint)) {
		draw_g6dof_joint(*g6dof, points);
	}

	p_gizmo->add_collision_segments(points);
	p_gizmo->add_lines(points, get_material(MATERIAL_NAME, p_gizmo));
}

void PhantomJointGizmoPlugin3D::_create_materials() {
	// HACK(mihe): Ideally we would do all this in the constructor, but the documentation generation
	// will instantiate this class too early in the program's flow, leading to a bunch of errors
	// about missing editor settings.

	Ref<EditorSettings> editor_settings = editor_interface->get_editor_settings();

	create_material(MATERIAL_NAME, editor_settings->get_setting(SETTING_NAME_COLOR));
}

void PhantomJointGizmoPlugin3D::_create_redraw_timer(const Ref<EditorNode3DGizmo> &p_gizmo) {
	// HACK(mihe): Since the `EditorNode` class isn't available through GDExtension, much less as a
	// singleton, we're forced to crawl up the node hierarchy of the gizmo to locate the
	// `EditorNode` node, which we need in order to have something for our timer to attach to.

	Node3D *joint = p_gizmo->get_node_3d();
	ERR_FAIL_NULL(joint);

	Node *ancestor = joint->get_parent();

	while (ancestor != nullptr && ancestor->get_class() != "EditorNode") {
		ancestor = ancestor->get_parent();
	}

	EditorNode *editor_node = EditorNode::get_singleton();

	ERR_FAIL_NULL_MSG(
			editor_node,
			"PhantomJointGizmoPlugin3D was unable to find EditorNode. "
			"Gizmos for Jolt joints won't be visible in any editor viewport.");

	Timer *timer = memnew(Timer);
	timer->set_name("JoltJointGizmoRedrawTimer");
	timer->set_wait_time(1.0 / 120.0);
	timer->connect("timeout", callable_mp(this, &PhantomJointGizmoPlugin3D::_redraw_gizmos));
	timer->set_autostart(true);

	editor_node->call_deferred("add_child", timer);
}

void PhantomJointGizmoPlugin3D::_redraw_gizmos() {
	Vector<Ref<EditorNode3DGizmo>> to_remove;

	for (const Ref<EditorNode3DGizmo> &p_gizmo : gizmos) {
		if (p_gizmo->get_reference_count() > 1) {
			redraw(*p_gizmo);
		} else {
			to_remove.append(p_gizmo);
		}
	}

	for (const Ref<EditorNode3DGizmo> &p_gizmo : to_remove) {
		gizmos.erase(p_gizmo);
	}
}

#endif // GDJ_CONFIG_EDITOR
