#include "phantom_cone_twist_joint_3d.h"

#include "../jolt_physics_server_3d.h"

#include "core/object/class_db.h"
#include "core/typedefs.h"


namespace {

using ServerParam = PhysicsServer3D::ConeTwistJointParam;
using ServerParamJolt = JoltPhysicsServer3D::ConeTwistJointParamJolt;
using ServerFlagJolt = JoltPhysicsServer3D::ConeTwistJointFlagJolt;

} // namespace

void PhantomConeTwistJoint3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_swing_limit_enabled"), &PhantomConeTwistJoint3D::get_swing_limit_enabled);
	ClassDB::bind_method(D_METHOD("set_swing_limit_enabled", "enabled"), &PhantomConeTwistJoint3D::set_swing_limit_enabled);

	ClassDB::bind_method(D_METHOD("get_twist_limit_enabled"), &PhantomConeTwistJoint3D::get_twist_limit_enabled);
	ClassDB::bind_method(D_METHOD("set_twist_limit_enabled", "enabled"), &PhantomConeTwistJoint3D::set_twist_limit_enabled);

	ClassDB::bind_method(D_METHOD("get_swing_limit_span"), &PhantomConeTwistJoint3D::get_swing_limit_span);
	ClassDB::bind_method(D_METHOD("set_swing_limit_span", "value"), &PhantomConeTwistJoint3D::set_swing_limit_span);

	ClassDB::bind_method(D_METHOD("get_twist_limit_span"), &PhantomConeTwistJoint3D::get_twist_limit_span);
	ClassDB::bind_method(D_METHOD("set_twist_limit_span", "value"), &PhantomConeTwistJoint3D::set_twist_limit_span);

	ClassDB::bind_method(D_METHOD("get_swing_limit_shift_y"), &PhantomConeTwistJoint3D::get_swing_limit_shift_y);
	ClassDB::bind_method(D_METHOD("set_swing_limit_shift_y", "value"), &PhantomConeTwistJoint3D::set_swing_limit_shift_y);

	ClassDB::bind_method(D_METHOD("get_swing_limit_shift_z"), &PhantomConeTwistJoint3D::get_swing_limit_shift_z);
	ClassDB::bind_method(D_METHOD("set_swing_limit_shift_z", "value"), &PhantomConeTwistJoint3D::set_swing_limit_shift_z);

	ClassDB::bind_method(D_METHOD("get_twist_limit_shift"), &PhantomConeTwistJoint3D::get_twist_limit_shift);
	ClassDB::bind_method(D_METHOD("set_twist_limit_shift", "value"), &PhantomConeTwistJoint3D::set_twist_limit_shift);

	ClassDB::bind_method(D_METHOD("get_swing_motor_enabled"), &PhantomConeTwistJoint3D::get_swing_motor_enabled);
	ClassDB::bind_method(D_METHOD("set_swing_motor_enabled", "enabled"), &PhantomConeTwistJoint3D::set_swing_motor_enabled);

	ClassDB::bind_method(D_METHOD("get_twist_motor_enabled"), &PhantomConeTwistJoint3D::get_twist_motor_enabled);
	ClassDB::bind_method(D_METHOD("set_twist_motor_enabled", "enabled"), &PhantomConeTwistJoint3D::set_twist_motor_enabled);

	ClassDB::bind_method(D_METHOD("get_swing_spring_enabled"), &PhantomConeTwistJoint3D::get_swing_spring_enabled);
	ClassDB::bind_method(D_METHOD("set_swing_spring_enabled", "enabled"), &PhantomConeTwistJoint3D::set_swing_spring_enabled);

	ClassDB::bind_method(D_METHOD("get_twist_spring_enabled"), &PhantomConeTwistJoint3D::get_twist_spring_enabled);
	ClassDB::bind_method(D_METHOD("set_twist_spring_enabled", "enabled"), &PhantomConeTwistJoint3D::set_twist_spring_enabled);

	ClassDB::bind_method(D_METHOD("get_swing_spring_frequency_enabled"), &PhantomConeTwistJoint3D::get_swing_spring_frequency_enabled);
	ClassDB::bind_method(D_METHOD("set_swing_spring_frequency_enabled", "enabled"), &PhantomConeTwistJoint3D::set_swing_spring_frequency_enabled);

	ClassDB::bind_method(D_METHOD("get_twist_spring_frequency_enabled"), &PhantomConeTwistJoint3D::get_twist_spring_frequency_enabled);
	ClassDB::bind_method(D_METHOD("set_twist_spring_frequency_enabled", "enabled"), &PhantomConeTwistJoint3D::set_twist_spring_frequency_enabled);

	ClassDB::bind_method(D_METHOD("get_swing_motor_target_velocity_y"), &PhantomConeTwistJoint3D::get_swing_motor_target_velocity_y);
	ClassDB::bind_method(D_METHOD("set_swing_motor_target_velocity_y", "value"), &PhantomConeTwistJoint3D::set_swing_motor_target_velocity_y);

	ClassDB::bind_method(D_METHOD("get_swing_motor_target_velocity_z"), &PhantomConeTwistJoint3D::get_swing_motor_target_velocity_z);
	ClassDB::bind_method(D_METHOD("set_swing_motor_target_velocity_z", "value"), &PhantomConeTwistJoint3D::set_swing_motor_target_velocity_z);

	ClassDB::bind_method(D_METHOD("get_twist_motor_target_velocity"), &PhantomConeTwistJoint3D::get_twist_motor_target_velocity);
	ClassDB::bind_method(D_METHOD("set_twist_motor_target_velocity", "value"), &PhantomConeTwistJoint3D::set_twist_motor_target_velocity);

	ClassDB::bind_method(D_METHOD("get_swing_motor_max_torque"), &PhantomConeTwistJoint3D::get_swing_motor_max_torque);
	ClassDB::bind_method(D_METHOD("set_swing_motor_max_torque", "value"), &PhantomConeTwistJoint3D::set_swing_motor_max_torque);

	ClassDB::bind_method(D_METHOD("get_twist_motor_max_torque"), &PhantomConeTwistJoint3D::get_twist_motor_max_torque);
	ClassDB::bind_method(D_METHOD("set_twist_motor_max_torque", "value"), &PhantomConeTwistJoint3D::set_twist_motor_max_torque);

	ClassDB::bind_method(D_METHOD("get_swing_spring_frequency"), &PhantomConeTwistJoint3D::get_swing_spring_frequency);
	ClassDB::bind_method(D_METHOD("set_swing_spring_frequency", "value"), &PhantomConeTwistJoint3D::set_swing_spring_frequency);

	ClassDB::bind_method(D_METHOD("get_swing_spring_stiffness"), &PhantomConeTwistJoint3D::get_swing_spring_stiffness);
	ClassDB::bind_method(D_METHOD("set_swing_spring_stiffness", "value"), &PhantomConeTwistJoint3D::set_swing_spring_stiffness);

	ClassDB::bind_method(D_METHOD("get_swing_spring_damping"), &PhantomConeTwistJoint3D::get_swing_spring_damping);
	ClassDB::bind_method(D_METHOD("set_swing_spring_damping", "value"), &PhantomConeTwistJoint3D::set_swing_spring_damping);

	ClassDB::bind_method(D_METHOD("get_twist_spring_frequency"), &PhantomConeTwistJoint3D::get_twist_spring_frequency);
	ClassDB::bind_method(D_METHOD("set_twist_spring_frequency", "value"), &PhantomConeTwistJoint3D::set_twist_spring_frequency);

	ClassDB::bind_method(D_METHOD("get_twist_spring_stiffness"), &PhantomConeTwistJoint3D::get_twist_spring_stiffness);
	ClassDB::bind_method(D_METHOD("set_twist_spring_stiffness", "value"), &PhantomConeTwistJoint3D::set_twist_spring_stiffness);

	ClassDB::bind_method(D_METHOD("get_twist_spring_damping"), &PhantomConeTwistJoint3D::get_twist_spring_damping);
	ClassDB::bind_method(D_METHOD("set_twist_spring_damping", "value"), &PhantomConeTwistJoint3D::set_twist_spring_damping);

	ClassDB::bind_method(D_METHOD("get_applied_force"), &PhantomConeTwistJoint3D::get_applied_force);
	ClassDB::bind_method(D_METHOD("get_applied_torque"), &PhantomConeTwistJoint3D::get_applied_torque);

	ClassDB::bind_method(D_METHOD("set_target_rotation", "rotation"), &PhantomConeTwistJoint3D::set_target_rotation);

	ADD_GROUP("Swing Limit", "swing_limit_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "swing_limit_enabled"), "set_swing_limit_enabled", "get_swing_limit_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_limit_span", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_swing_limit_span", "get_swing_limit_span");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_limit_shift_y", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_swing_limit_shift_y", "get_swing_limit_shift_y");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_limit_shift_z", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_swing_limit_shift_z", "get_swing_limit_shift_z");

	ADD_GROUP("Twist Limit", "twist_limit_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "twist_limit_enabled"), "set_twist_limit_enabled", "get_twist_limit_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_limit_span", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_twist_limit_span", "get_twist_limit_span");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_limit_shift", PROPERTY_HINT_RANGE, "-180,180,0.1,radians_as_degrees"), "set_twist_limit_shift", "get_twist_limit_shift");

	ADD_GROUP("Swing Motor", "swing_motor_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "swing_motor_enabled"), "set_swing_motor_enabled", "get_swing_motor_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_motor_target_velocity_y", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_swing_motor_target_velocity_y", "get_swing_motor_target_velocity_y");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_motor_target_velocity_z", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_swing_motor_target_velocity_z", "get_swing_motor_target_velocity_z");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_motor_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_swing_motor_max_torque", "get_swing_motor_max_torque");

	ADD_GROUP("Twist Motor", "twist_motor_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "twist_motor_enabled"), "set_twist_motor_enabled", "get_twist_motor_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_motor_target_velocity", PROPERTY_HINT_NONE, U"radians_as_degrees,suffix:°/s"), "set_twist_motor_target_velocity", "get_twist_motor_target_velocity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_motor_max_torque", PROPERTY_HINT_NONE, U"suffix:kg\u22C5m\u00B2/s\u00B2 (Nm)"), "set_twist_motor_max_torque", "get_twist_motor_max_torque");

	ADD_GROUP("Swing Spring", "swing_spring_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "swing_spring_enabled"), "set_swing_spring_enabled", "get_swing_spring_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "swing_spring_frequency_enabled"), "set_swing_spring_frequency_enabled", "get_swing_spring_frequency_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_spring_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_swing_spring_frequency", "get_swing_spring_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_spring_stiffness", PROPERTY_HINT_NONE, ""), "set_swing_spring_stiffness", "get_swing_spring_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "swing_spring_damping"), "set_swing_spring_damping", "get_swing_spring_damping");

	ADD_GROUP("Twist Spring", "twist_spring_");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "twist_spring_enabled"), "set_twist_spring_enabled", "get_twist_spring_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "twist_spring_frequency_enabled"), "set_twist_spring_frequency_enabled", "get_twist_spring_frequency_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_spring_frequency", PROPERTY_HINT_NONE, "suffix:hz"), "set_twist_spring_frequency", "get_twist_spring_frequency");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_spring_stiffness", PROPERTY_HINT_NONE, ""), "set_twist_spring_stiffness", "get_twist_spring_stiffness");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "twist_spring_damping"), "set_twist_spring_damping", "get_twist_spring_damping");
}

void PhantomConeTwistJoint3D::set_swing_limit_enabled(bool p_enabled) {
	if (swing_limit_enabled == p_enabled) {
		return;
	}

	swing_limit_enabled = p_enabled;

	_flag_changed(FLAG_USE_SWING_LIMIT);
}

void PhantomConeTwistJoint3D::set_twist_limit_enabled(bool p_enabled) {
	if (twist_limit_enabled == p_enabled) {
		return;
	}

	twist_limit_enabled = p_enabled;

	_flag_changed(FLAG_USE_TWIST_LIMIT);
}

void PhantomConeTwistJoint3D::set_swing_limit_span(double p_value) {
	if (swing_limit_span == p_value) {
		return;
	}

	swing_limit_span = p_value;

	_param_changed(PARAM_SWING_LIMIT_SPAN);
}

void PhantomConeTwistJoint3D::set_twist_limit_span(double p_value) {
	if (twist_limit_span == p_value) {
		return;
	}

	twist_limit_span = p_value;

	_param_changed(PARAM_TWIST_LIMIT_SPAN);
}

void PhantomConeTwistJoint3D::set_swing_limit_shift_y(double p_value) {
	if (swing_limit_shift_y == p_value) {
		return;
	}

	swing_limit_shift_y = p_value;

	_param_changed(PARAM_SWING_LIMIT_SHIFT_Y);
}

void PhantomConeTwistJoint3D::set_swing_limit_shift_z(double p_value) {
	if (swing_limit_shift_z == p_value) {
		return;
	}

	swing_limit_shift_z = p_value;

	_param_changed(PARAM_SWING_LIMIT_SHIFT_Z);
}

void PhantomConeTwistJoint3D::set_twist_limit_shift(double p_value) {
	if (twist_limit_shift == p_value) {
		return;
	}

	twist_limit_shift = p_value;

	_param_changed(PARAM_TWIST_LIMIT_SHIFT);
}

void PhantomConeTwistJoint3D::set_swing_motor_enabled(bool p_enabled) {
	if (swing_motor_enabled == p_enabled) {
		return;
	}

	swing_motor_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_SWING_MOTOR);
}

void PhantomConeTwistJoint3D::set_twist_motor_enabled(bool p_enabled) {
	if (twist_motor_enabled == p_enabled) {
		return;
	}

	twist_motor_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_TWIST_MOTOR);
}

void PhantomConeTwistJoint3D::set_swing_spring_enabled(bool p_enabled) {
	if (swing_spring_enabled == p_enabled) {
		return;
	}

	swing_spring_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_SWING_SPRING);
}

void PhantomConeTwistJoint3D::set_twist_spring_enabled(bool p_enabled) {
	if (twist_spring_enabled == p_enabled) {
		return;
	}

	twist_spring_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_TWIST_SPRING);
}

void PhantomConeTwistJoint3D::set_swing_spring_frequency_enabled(bool p_enabled) {
	if (swing_spring_frequency_enabled == p_enabled) {
		return;
	}

	swing_spring_frequency_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_SWING_SPRING_FREQUENCY);
}

void PhantomConeTwistJoint3D::set_twist_spring_frequency_enabled(bool p_enabled) {
	if (twist_spring_frequency_enabled == p_enabled) {
		return;
	}

	twist_spring_frequency_enabled = p_enabled;

	_flag_changed(FLAG_ENABLE_TWIST_SPRING_FREQUENCY);
}

void PhantomConeTwistJoint3D::set_swing_motor_target_velocity_y(double p_value) {
	if (swing_motor_target_velocity_y == p_value) {
		return;
	}

	swing_motor_target_velocity_y = p_value;

	_param_changed(PARAM_SWING_MOTOR_TARGET_VELOCITY_Y);
}

void PhantomConeTwistJoint3D::set_swing_motor_target_velocity_z(double p_value) {
	if (swing_motor_target_velocity_z == p_value) {
		return;
	}

	swing_motor_target_velocity_z = p_value;

	_param_changed(PARAM_SWING_MOTOR_TARGET_VELOCITY_Z);
}

void PhantomConeTwistJoint3D::set_twist_motor_target_velocity(double p_value) {
	if (twist_motor_target_velocity == p_value) {
		return;
	}

	twist_motor_target_velocity = p_value;

	_param_changed(PARAM_TWIST_MOTOR_TARGET_VELOCITY);
}

void PhantomConeTwistJoint3D::set_swing_motor_max_torque(double p_value) {
	if (swing_motor_max_torque == p_value) {
		return;
	}

	swing_motor_max_torque = p_value;

	_param_changed(PARAM_SWING_MOTOR_MAX_TORQUE);
}

void PhantomConeTwistJoint3D::set_twist_motor_max_torque(double p_value) {
	if (twist_motor_max_torque == p_value) {
		return;
	}

	twist_motor_max_torque = p_value;

	_param_changed(PARAM_TWIST_MOTOR_MAX_TORQUE);
}

void PhantomConeTwistJoint3D::set_swing_spring_frequency(double p_value) {
	if (swing_spring_frequency == p_value) {
		return;
	}

	swing_spring_frequency = p_value;

	_param_changed(PARAM_SWING_SPRING_FREQUENCY);
}

void PhantomConeTwistJoint3D::set_swing_spring_stiffness(double p_value) {
	if (swing_spring_stiffness == p_value) {
		return;
	}

	swing_spring_stiffness = p_value;

	_param_changed(PARAM_SWING_SPRING_STIFFNESS);
}

void PhantomConeTwistJoint3D::set_swing_spring_damping(double p_value) {
	if (swing_spring_damping == p_value) {
		return;
	}

	swing_spring_damping = p_value;

	_param_changed(PARAM_SWING_SPRING_DAMPING);
}

void PhantomConeTwistJoint3D::set_twist_spring_frequency(double p_value) {
	if (twist_spring_frequency == p_value) {
		return;
	}

	twist_spring_frequency = p_value;

	_param_changed(PARAM_TWIST_SPRING_FREQUENCY);
}

void PhantomConeTwistJoint3D::set_twist_spring_stiffness(double p_value) {
	if (twist_spring_stiffness == p_value) {
		return;
	}

	twist_spring_stiffness = p_value;

	_param_changed(PARAM_TWIST_SPRING_STIFFNESS);
}

void PhantomConeTwistJoint3D::set_twist_spring_damping(double p_value) {
	if (twist_spring_damping == p_value) {
		return;
	}

	twist_spring_damping = p_value;

	_param_changed(PARAM_TWIST_SPRING_DAMPING);
}

float PhantomConeTwistJoint3D::get_applied_force() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->cone_twist_joint_get_applied_force(rid);
}

float PhantomConeTwistJoint3D::get_applied_torque() const {
	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return 0.0f;
	}

	return physics_server->cone_twist_joint_get_applied_torque(rid);
}

void PhantomConeTwistJoint3D::set_target_rotation(Basis p_rotation) {
	JoltPhysicsServer3D *server = _get_jolt_physics_server();
	if (unlikely(server == nullptr)) {
		return;
	}

	server->cone_twist_joint_set_target_rotation(rid, p_rotation);
}

void PhantomConeTwistJoint3D::_configure(PhysicsBody3D *p_body_a, PhysicsBody3D *p_body_b) {
	PhysicsServer3D *physics_server = _get_physics_server();
	ERR_FAIL_NULL(physics_server);

	physics_server->joint_make_cone_twist(
			rid,
			p_body_a->get_rid(),
			_get_body_local_transform(*p_body_a),
			p_body_b != nullptr ? p_body_b->get_rid() : RID(),
			p_body_b != nullptr ? _get_body_local_transform(*p_body_b) : get_global_transform().orthonormalized());

	_update_param(PARAM_SWING_LIMIT_SPAN);
	_update_param(PARAM_TWIST_LIMIT_SPAN);

	_update_jolt_param(PARAM_SWING_LIMIT_SHIFT_Y);
	_update_jolt_param(PARAM_SWING_LIMIT_SHIFT_Z);
	_update_jolt_param(PARAM_TWIST_LIMIT_SHIFT);
	_update_jolt_param(PARAM_SWING_MOTOR_TARGET_VELOCITY_Y);
	_update_jolt_param(PARAM_SWING_MOTOR_TARGET_VELOCITY_Z);
	_update_jolt_param(PARAM_TWIST_MOTOR_TARGET_VELOCITY);
	_update_jolt_param(PARAM_SWING_MOTOR_MAX_TORQUE);
	_update_jolt_param(PARAM_TWIST_MOTOR_MAX_TORQUE);
	_update_jolt_param(PARAM_SWING_SPRING_FREQUENCY);
	_update_jolt_param(PARAM_SWING_SPRING_STIFFNESS);
	_update_jolt_param(PARAM_SWING_SPRING_DAMPING);
	_update_jolt_param(PARAM_TWIST_SPRING_FREQUENCY);
	_update_jolt_param(PARAM_TWIST_SPRING_STIFFNESS);
	_update_jolt_param(PARAM_TWIST_SPRING_DAMPING);

	_update_jolt_flag(FLAG_USE_SWING_LIMIT);
	_update_jolt_flag(FLAG_USE_TWIST_LIMIT);
	_update_jolt_flag(FLAG_ENABLE_SWING_MOTOR);
	_update_jolt_flag(FLAG_ENABLE_TWIST_MOTOR);
	_update_jolt_flag(FLAG_ENABLE_SWING_SPRING);
	_update_jolt_flag(FLAG_ENABLE_TWIST_SPRING);
	_update_jolt_flag(FLAG_ENABLE_SWING_SPRING_FREQUENCY);
	_update_jolt_flag(FLAG_ENABLE_TWIST_SPRING_FREQUENCY);
}

void PhantomConeTwistJoint3D::_update_param(Param p_param) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	double *value = nullptr;

	switch (p_param) {
		case PARAM_SWING_LIMIT_SPAN: {
			value = &swing_limit_span;
		} break;
		case PARAM_TWIST_LIMIT_SPAN: {
			value = &twist_limit_span;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}

	physics_server->cone_twist_joint_set_param(rid, ServerParam(p_param), (real_t)*value);
}

void PhantomConeTwistJoint3D::_update_jolt_param(Param p_param) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	double *value = nullptr;

	switch (p_param) {
		case PARAM_SWING_LIMIT_SHIFT_Y: {
			value = &swing_limit_shift_y;
		} break;
		case PARAM_SWING_LIMIT_SHIFT_Z: {
			value = &swing_limit_shift_z;
		} break;
		case PARAM_TWIST_LIMIT_SHIFT: {
			value = &twist_limit_shift;
		} break;
		case PARAM_SWING_MOTOR_TARGET_VELOCITY_Y: {
			value = &swing_motor_target_velocity_y;
		} break;
		case PARAM_SWING_MOTOR_TARGET_VELOCITY_Z: {
			value = &swing_motor_target_velocity_z;
		} break;
		case PARAM_TWIST_MOTOR_TARGET_VELOCITY: {
			value = &twist_motor_target_velocity;
		} break;
		case PARAM_SWING_MOTOR_MAX_TORQUE: {
			value = &swing_motor_max_torque;
		} break;
		case PARAM_TWIST_MOTOR_MAX_TORQUE: {
			value = &twist_motor_max_torque;
		} break;
		case PARAM_SWING_SPRING_FREQUENCY: {
			value = &swing_spring_frequency;
		} break;
		case PARAM_SWING_SPRING_STIFFNESS: {
			value = &swing_spring_stiffness;
		} break;
		case PARAM_SWING_SPRING_DAMPING: {
			value = &swing_spring_damping;
		} break;
		case PARAM_TWIST_SPRING_FREQUENCY: {
			value = &twist_spring_frequency;
		} break;
		case PARAM_TWIST_SPRING_STIFFNESS: {
			value = &twist_spring_stiffness;
		} break;
		case PARAM_TWIST_SPRING_DAMPING: {
			value = &twist_spring_damping;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}

	physics_server->cone_twist_joint_set_jolt_param(rid, ServerParamJolt(p_param), *value);
}

void PhantomConeTwistJoint3D::_update_jolt_flag(Flag p_flag) {
	if (unlikely(_is_invalid())) {
		return;
	}

	JoltPhysicsServer3D *physics_server = _get_jolt_physics_server();
	if (unlikely(physics_server == nullptr)) {
		return;
	}

	bool *value = nullptr;

	switch (p_flag) {
		case FLAG_USE_SWING_LIMIT: {
			value = &swing_limit_enabled;
		} break;
		case FLAG_USE_TWIST_LIMIT: {
			value = &twist_limit_enabled;
		} break;
		case FLAG_ENABLE_SWING_MOTOR: {
			value = &swing_motor_enabled;
		} break;
		case FLAG_ENABLE_TWIST_MOTOR: {
			value = &twist_motor_enabled;
		} break;
		case FLAG_ENABLE_SWING_SPRING: {
			value = &swing_spring_enabled;
		} break;
		case FLAG_ENABLE_TWIST_SPRING: {
			value = &twist_spring_enabled;
		} break;
		case FLAG_ENABLE_SWING_SPRING_FREQUENCY: {
			value = &swing_spring_frequency_enabled;
		} break;
		case FLAG_ENABLE_TWIST_SPRING_FREQUENCY: {
			value = &twist_spring_frequency_enabled;
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}

	physics_server->cone_twist_joint_set_jolt_flag(rid, ServerFlagJolt(p_flag), *value);
}

void PhantomConeTwistJoint3D::_param_changed(Param p_param) {
	switch (p_param) {
		case PARAM_SWING_LIMIT_SPAN:
		case PARAM_TWIST_LIMIT_SPAN: {
			_update_param(p_param);
		} break;
		case PARAM_SWING_LIMIT_SHIFT_Y:
		case PARAM_SWING_LIMIT_SHIFT_Z:
		case PARAM_TWIST_LIMIT_SHIFT:
		case PARAM_SWING_MOTOR_TARGET_VELOCITY_Y:
		case PARAM_SWING_MOTOR_TARGET_VELOCITY_Z:
		case PARAM_TWIST_MOTOR_TARGET_VELOCITY:
		case PARAM_SWING_MOTOR_MAX_TORQUE:
		case PARAM_TWIST_MOTOR_MAX_TORQUE:
		case PARAM_SWING_SPRING_FREQUENCY:
		case PARAM_SWING_SPRING_STIFFNESS:
		case PARAM_SWING_SPRING_DAMPING:
		case PARAM_TWIST_SPRING_FREQUENCY:
		case PARAM_TWIST_SPRING_STIFFNESS:
		case PARAM_TWIST_SPRING_DAMPING: {
			_update_jolt_param(p_param);
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled parameter: '%d'.", p_param));
		} break;
	}
}

void PhantomConeTwistJoint3D::_flag_changed(Flag p_flag) {
	switch (p_flag) {
		case FLAG_USE_SWING_LIMIT:
		case FLAG_USE_TWIST_LIMIT:
		case FLAG_ENABLE_SWING_MOTOR:
		case FLAG_ENABLE_TWIST_MOTOR:
		case FLAG_ENABLE_SWING_SPRING:
		case FLAG_ENABLE_TWIST_SPRING:
		case FLAG_ENABLE_SWING_SPRING_FREQUENCY:
		case FLAG_ENABLE_TWIST_SPRING_FREQUENCY: {
			_update_jolt_flag(p_flag);
		} break;
		default: {
			ERR_FAIL_MSG(vformat("Unhandled flag: '%d'.", p_flag));
		} break;
	}
}
